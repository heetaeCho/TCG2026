#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "Stream.h"
#include "Object.h"
#include "GooFile.h"

// Helper to create a temporary file for testing
#include <cstdio>
#include <cstring>
#include <fstream>
#include <string>

class FileStreamTest_152 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a temporary file with known content
        tmpFilePath = std::tmpnam(nullptr);
        std::ofstream ofs(tmpFilePath, std::ios::binary);
        testContent = "Hello, World! This is a test file for FileStream unit tests. "
                      "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz.";
        ofs.write(testContent.c_str(), testContent.size());
        ofs.close();

        gooFile = GooFile::open(tmpFilePath);
    }

    void TearDown() override {
        gooFile = nullptr;
        std::remove(tmpFilePath.c_str());
    }

    std::string tmpFilePath;
    std::string testContent;
    std::unique_ptr<GooFile> gooFile;
};

// Test getStart returns the start position passed during construction
TEST_F(FileStreamTest_152, GetStartReturnsInitialStart_152) {
    ASSERT_NE(gooFile, nullptr);
    Object dict;
    Goffset startPos = 0;
    FileStream fs(gooFile.get(), startPos, false, 0, std::move(dict));
    EXPECT_EQ(fs.getStart(), startPos);
    fs.close();
}

// Test getStart with a non-zero start position
TEST_F(FileStreamTest_152, GetStartReturnsNonZeroStart_152) {
    ASSERT_NE(gooFile, nullptr);
    Object dict;
    Goffset startPos = 10;
    FileStream fs(gooFile.get(), startPos, false, 0, std::move(dict));
    EXPECT_EQ(fs.getStart(), startPos);
    fs.close();
}

// Test getKind returns fileStream
TEST_F(FileStreamTest_152, GetKindReturnsFileStream_152) {
    ASSERT_NE(gooFile, nullptr);
    Object dict;
    FileStream fs(gooFile.get(), 0, false, 0, std::move(dict));
    EXPECT_EQ(fs.getKind(), strFile);
    fs.close();
}

// Test reading a character with getChar
TEST_F(FileStreamTest_152, GetCharReadsFirstCharacter_152) {
    ASSERT_NE(gooFile, nullptr);
    Object dict;
    FileStream fs(gooFile.get(), 0, true, static_cast<Goffset>(testContent.size()), std::move(dict));
    fs.rewind();
    int ch = fs.getChar();
    EXPECT_EQ(ch, 'H');
    fs.close();
}

// Test lookChar returns the next character without advancing
TEST_F(FileStreamTest_152, LookCharDoesNotAdvancePosition_152) {
    ASSERT_NE(gooFile, nullptr);
    Object dict;
    FileStream fs(gooFile.get(), 0, true, static_cast<Goffset>(testContent.size()), std::move(dict));
    fs.rewind();
    int ch1 = fs.lookChar();
    int ch2 = fs.lookChar();
    EXPECT_EQ(ch1, ch2);
    EXPECT_EQ(ch1, 'H');
    fs.close();
}

// Test getPos reflects position after reading
TEST_F(FileStreamTest_152, GetPosAdvancesAfterGetChar_152) {
    ASSERT_NE(gooFile, nullptr);
    Object dict;
    FileStream fs(gooFile.get(), 0, true, static_cast<Goffset>(testContent.size()), std::move(dict));
    fs.rewind();
    EXPECT_EQ(fs.getPos(), 0);
    fs.getChar();
    EXPECT_EQ(fs.getPos(), 1);
    fs.getChar();
    EXPECT_EQ(fs.getPos(), 2);
    fs.close();
}

// Test rewind resets position to start
TEST_F(FileStreamTest_152, RewindResetsPosition_152) {
    ASSERT_NE(gooFile, nullptr);
    Object dict;
    FileStream fs(gooFile.get(), 0, true, static_cast<Goffset>(testContent.size()), std::move(dict));
    fs.rewind();
    fs.getChar();
    fs.getChar();
    fs.getChar();
    EXPECT_EQ(fs.getPos(), 3);
    bool result = fs.rewind();
    EXPECT_TRUE(result);
    EXPECT_EQ(fs.getPos(), 0);
    fs.close();
}

// Test reading from a non-zero start position
TEST_F(FileStreamTest_152, ReadFromNonZeroStart_152) {
    ASSERT_NE(gooFile, nullptr);
    Object dict;
    Goffset startPos = 7; // "World!..."
    FileStream fs(gooFile.get(), startPos, true, static_cast<Goffset>(testContent.size() - startPos), std::move(dict));
    fs.rewind();
    int ch = fs.getChar();
    EXPECT_EQ(ch, testContent[startPos]);
    fs.close();
}

// Test moveStart changes the start position
TEST_F(FileStreamTest_152, MoveStartChangesStart_152) {
    ASSERT_NE(gooFile, nullptr);
    Object dict;
    FileStream fs(gooFile.get(), 0, true, static_cast<Goffset>(testContent.size()), std::move(dict));
    fs.moveStart(5);
    EXPECT_EQ(fs.getStart(), 5);
    fs.close();
}

// Test getChar returns EOF when limited stream is exhausted
TEST_F(FileStreamTest_152, GetCharReturnsEOFAtEnd_152) {
    ASSERT_NE(gooFile, nullptr);
    Object dict;
    Goffset length = 3;
    FileStream fs(gooFile.get(), 0, true, length, std::move(dict));
    fs.rewind();
    // Read exactly 'length' characters
    for (Goffset i = 0; i < length; i++) {
        int ch = fs.getChar();
        EXPECT_NE(ch, EOF);
    }
    // Next read should be EOF
    int ch = fs.getChar();
    EXPECT_EQ(ch, EOF);
    fs.close();
}

// Test setPos with absolute position
TEST_F(FileStreamTest_152, SetPosAbsolute_152) {
    ASSERT_NE(gooFile, nullptr);
    Object dict;
    FileStream fs(gooFile.get(), 0, true, static_cast<Goffset>(testContent.size()), std::move(dict));
    fs.rewind();
    fs.setPos(5, 0);
    int ch = fs.getChar();
    EXPECT_EQ(ch, testContent[5]);
    fs.close();
}

// Test copy creates a valid copy
TEST_F(FileStreamTest_152, CopyCreatesValidStream_152) {
    ASSERT_NE(gooFile, nullptr);
    Object dict;
    FileStream fs(gooFile.get(), 0, true, static_cast<Goffset>(testContent.size()), std::move(dict));
    auto copyStream = fs.copy();
    ASSERT_NE(copyStream, nullptr);
    EXPECT_EQ(copyStream->getKind(), strFile);
    EXPECT_EQ(copyStream->getStart(), 0);
    fs.close();
}

// Test makeSubStream creates a valid sub-stream
TEST_F(FileStreamTest_152, MakeSubStreamCreatesValidStream_152) {
    ASSERT_NE(gooFile, nullptr);
    Object dict;
    FileStream fs(gooFile.get(), 0, true, static_cast<Goffset>(testContent.size()), std::move(dict));
    Object subDict;
    auto subStream = fs.makeSubStream(5, true, 10, std::move(subDict));
    ASSERT_NE(subStream, nullptr);
    fs.close();
}

// Test getNeedsEncryptionOnSave default and setter
TEST_F(FileStreamTest_152, NeedsEncryptionOnSaveDefaultFalse_152) {
    ASSERT_NE(gooFile, nullptr);
    Object dict;
    FileStream fs(gooFile.get(), 0, false, 0, std::move(dict));
    EXPECT_FALSE(fs.getNeedsEncryptionOnSave());
    fs.close();
}

TEST_F(FileStreamTest_152, SetNeedsEncryptionOnSave_152) {
    ASSERT_NE(gooFile, nullptr);
    Object dict;
    FileStream fs(gooFile.get(), 0, false, 0, std::move(dict));
    fs.setNeedsEncryptionOnSave(true);
    EXPECT_TRUE(fs.getNeedsEncryptionOnSave());
    fs.setNeedsEncryptionOnSave(false);
    EXPECT_FALSE(fs.getNeedsEncryptionOnSave());
    fs.close();
}

// Test unfilteredRewind
TEST_F(FileStreamTest_152, UnfilteredRewind_152) {
    ASSERT_NE(gooFile, nullptr);
    Object dict;
    FileStream fs(gooFile.get(), 0, true, static_cast<Goffset>(testContent.size()), std::move(dict));
    fs.rewind();
    fs.getChar();
    fs.getChar();
    bool result = fs.unfilteredRewind();
    EXPECT_TRUE(result);
    fs.close();
}

// Test getUnfilteredChar
TEST_F(FileStreamTest_152, GetUnfilteredChar_152) {
    ASSERT_NE(gooFile, nullptr);
    Object dict;
    FileStream fs(gooFile.get(), 0, true, static_cast<Goffset>(testContent.size()), std::move(dict));
    fs.rewind();
    int ch = fs.getUnfilteredChar();
    EXPECT_EQ(ch, 'H');
    fs.close();
}

// Test reading sequential characters matches expected content
TEST_F(FileStreamTest_152, SequentialReadMatchesContent_152) {
    ASSERT_NE(gooFile, nullptr);
    Object dict;
    FileStream fs(gooFile.get(), 0, true, static_cast<Goffset>(testContent.size()), std::move(dict));
    fs.rewind();
    for (size_t i = 0; i < testContent.size(); i++) {
        int ch = fs.getChar();
        EXPECT_EQ(ch, static_cast<unsigned char>(testContent[i])) << "Mismatch at position " << i;
    }
    fs.close();
}

// Test lookChar after getChar returns the next character
TEST_F(FileStreamTest_152, LookCharAfterGetChar_152) {
    ASSERT_NE(gooFile, nullptr);
    Object dict;
    FileStream fs(gooFile.get(), 0, true, static_cast<Goffset>(testContent.size()), std::move(dict));
    fs.rewind();
    fs.getChar(); // 'H'
    int ch = fs.lookChar();
    EXPECT_EQ(ch, 'e'); // second character
    // Position should not advance after lookChar
    int ch2 = fs.getChar();
    EXPECT_EQ(ch2, 'e');
    fs.close();
}

// Test limited stream with zero length
TEST_F(FileStreamTest_152, ZeroLengthLimitedStream_152) {
    ASSERT_NE(gooFile, nullptr);
    Object dict;
    FileStream fs(gooFile.get(), 0, true, 0, std::move(dict));
    fs.rewind();
    int ch = fs.getChar();
    EXPECT_EQ(ch, EOF);
    fs.close();
}

// Test moveStart with delta of 0
TEST_F(FileStreamTest_152, MoveStartZeroDelta_152) {
    ASSERT_NE(gooFile, nullptr);
    Object dict;
    FileStream fs(gooFile.get(), 10, true, static_cast<Goffset>(testContent.size() - 10), std::move(dict));
    Goffset originalStart = fs.getStart();
    fs.moveStart(0);
    EXPECT_EQ(fs.getStart(), originalStart);
    fs.close();
}

// Test close and then operations (boundary)
TEST_F(FileStreamTest_152, CloseStream_152) {
    ASSERT_NE(gooFile, nullptr);
    Object dict;
    FileStream fs(gooFile.get(), 0, true, static_cast<Goffset>(testContent.size()), std::move(dict));
    fs.rewind();
    fs.close();
    // getStart should still work after close since it just returns a member
    EXPECT_EQ(fs.getStart(), 0);
}
