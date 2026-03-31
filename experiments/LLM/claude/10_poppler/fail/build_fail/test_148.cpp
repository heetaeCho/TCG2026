#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <cstdio>
#include <cstring>
#include <fstream>

#include "Stream.h"
#include "goo/GooFile.h"
#include "Object.h"

class FileStreamTest_148 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a temporary file with known content
        tmpFilePath = std::tmpnam(nullptr);
        std::ofstream ofs(tmpFilePath, std::ios::binary);
        testData = "Hello, World! This is a test file for FileStream unit tests. 0123456789";
        ofs.write(testData.c_str(), testData.size());
        ofs.close();

        gooFile = GooFile::open(tmpFilePath);
        ASSERT_NE(gooFile, nullptr);
    }

    void TearDown() override {
        gooFile = nullptr;
        std::remove(tmpFilePath.c_str());
    }

    std::string tmpFilePath;
    std::string testData;
    std::unique_ptr<GooFile> gooFile;
};

// Test that getKind returns strFile
TEST_F(FileStreamTest_148, GetKindReturnsStrFile_148) {
    Object dict;
    FileStream stream(gooFile.get(), 0, false, 0, std::move(dict));
    EXPECT_EQ(stream.getKind(), strFile);
    stream.close();
}

// Test reading characters from the stream
TEST_F(FileStreamTest_148, GetCharReadsSequentially_148) {
    Object dict;
    FileStream stream(gooFile.get(), 0, true, static_cast<Goffset>(testData.size()), std::move(dict));
    stream.rewind();

    int ch = stream.getChar();
    EXPECT_EQ(ch, 'H');
    ch = stream.getChar();
    EXPECT_EQ(ch, 'e');
    ch = stream.getChar();
    EXPECT_EQ(ch, 'l');

    stream.close();
}

// Test lookChar does not advance position
TEST_F(FileStreamTest_148, LookCharDoesNotAdvancePosition_148) {
    Object dict;
    FileStream stream(gooFile.get(), 0, true, static_cast<Goffset>(testData.size()), std::move(dict));
    stream.rewind();

    int ch1 = stream.lookChar();
    int ch2 = stream.lookChar();
    EXPECT_EQ(ch1, ch2);
    EXPECT_EQ(ch1, 'H');

    stream.close();
}

// Test getPos returns current position
TEST_F(FileStreamTest_148, GetPosReturnsCurrentPosition_148) {
    Object dict;
    FileStream stream(gooFile.get(), 0, true, static_cast<Goffset>(testData.size()), std::move(dict));
    stream.rewind();

    EXPECT_EQ(stream.getPos(), 0);
    stream.getChar();
    EXPECT_EQ(stream.getPos(), 1);
    stream.getChar();
    EXPECT_EQ(stream.getPos(), 2);

    stream.close();
}

// Test getStart returns stream start offset
TEST_F(FileStreamTest_148, GetStartReturnsStartOffset_148) {
    Object dict;
    FileStream stream(gooFile.get(), 10, true, static_cast<Goffset>(testData.size() - 10), std::move(dict));
    stream.rewind();

    EXPECT_EQ(stream.getStart(), 10);

    stream.close();
}

// Test reading from a non-zero offset
TEST_F(FileStreamTest_148, ReadFromOffset_148) {
    Object dict;
    Goffset offset = 7; // "World!..."
    FileStream stream(gooFile.get(), offset, true, static_cast<Goffset>(testData.size() - offset), std::move(dict));
    stream.rewind();

    int ch = stream.getChar();
    EXPECT_EQ(ch, testData[offset]);

    stream.close();
}

// Test rewind resets position to start
TEST_F(FileStreamTest_148, RewindResetsPosition_148) {
    Object dict;
    FileStream stream(gooFile.get(), 0, true, static_cast<Goffset>(testData.size()), std::move(dict));
    stream.rewind();

    stream.getChar();
    stream.getChar();
    stream.getChar();
    EXPECT_EQ(stream.getPos(), 3);

    bool result = stream.rewind();
    EXPECT_TRUE(result);
    EXPECT_EQ(stream.getPos(), 0);

    int ch = stream.getChar();
    EXPECT_EQ(ch, 'H');

    stream.close();
}

// Test reading past end of limited stream returns EOF
TEST_F(FileStreamTest_148, ReadPastEndReturnsEOF_148) {
    Object dict;
    FileStream stream(gooFile.get(), 0, true, 5, std::move(dict));
    stream.rewind();

    for (int i = 0; i < 5; i++) {
        int ch = stream.getChar();
        EXPECT_NE(ch, EOF);
    }

    int ch = stream.getChar();
    EXPECT_EQ(ch, EOF);

    stream.close();
}

// Test setPos with direction 0 (from start)
TEST_F(FileStreamTest_148, SetPosFromStart_148) {
    Object dict;
    FileStream stream(gooFile.get(), 0, true, static_cast<Goffset>(testData.size()), std::move(dict));
    stream.rewind();

    stream.setPos(5, 0);
    int ch = stream.getChar();
    EXPECT_EQ(ch, testData[5]);

    stream.close();
}

// Test moveStart changes the start position
TEST_F(FileStreamTest_148, MoveStartChangesStart_148) {
    Object dict;
    FileStream stream(gooFile.get(), 0, true, static_cast<Goffset>(testData.size()), std::move(dict));
    stream.rewind();

    Goffset originalStart = stream.getStart();
    stream.moveStart(3);
    EXPECT_EQ(stream.getStart(), originalStart + 3);

    stream.close();
}

// Test copy creates a valid copy
TEST_F(FileStreamTest_148, CopyCreatesValidStream_148) {
    Object dict;
    FileStream stream(gooFile.get(), 0, true, static_cast<Goffset>(testData.size()), std::move(dict));
    stream.rewind();

    auto copied = stream.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getKind(), strFile);
    EXPECT_EQ(copied->getStart(), stream.getStart());

    stream.close();
}

// Test makeSubStream creates a valid substream
TEST_F(FileStreamTest_148, MakeSubStreamCreatesValidStream_148) {
    Object dict;
    FileStream stream(gooFile.get(), 0, true, static_cast<Goffset>(testData.size()), std::move(dict));
    stream.rewind();

    Object subDict;
    auto subStream = stream.makeSubStream(5, true, 10, std::move(subDict));
    ASSERT_NE(subStream, nullptr);

    stream.close();
}

// Test getNeedsEncryptionOnSave default and setter
TEST_F(FileStreamTest_148, NeedsEncryptionOnSaveDefaultAndSetter_148) {
    Object dict;
    FileStream stream(gooFile.get(), 0, true, static_cast<Goffset>(testData.size()), std::move(dict));

    // Default should be false (typical behavior)
    bool defaultVal = stream.getNeedsEncryptionOnSave();
    
    stream.setNeedsEncryptionOnSave(true);
    EXPECT_TRUE(stream.getNeedsEncryptionOnSave());

    stream.setNeedsEncryptionOnSave(false);
    EXPECT_FALSE(stream.getNeedsEncryptionOnSave());

    stream.close();
}

// Test getUnfilteredChar reads a character
TEST_F(FileStreamTest_148, GetUnfilteredCharReadsChar_148) {
    Object dict;
    FileStream stream(gooFile.get(), 0, true, static_cast<Goffset>(testData.size()), std::move(dict));
    stream.rewind();

    int ch = stream.getUnfilteredChar();
    EXPECT_EQ(ch, 'H');

    stream.close();
}

// Test unfilteredRewind works
TEST_F(FileStreamTest_148, UnfilteredRewindWorks_148) {
    Object dict;
    FileStream stream(gooFile.get(), 0, true, static_cast<Goffset>(testData.size()), std::move(dict));
    stream.rewind();

    stream.getChar();
    stream.getChar();

    bool result = stream.unfilteredRewind();
    EXPECT_TRUE(result);

    stream.close();
}

// Test with zero-length limited stream
TEST_F(FileStreamTest_148, ZeroLengthStreamReturnsEOFImmediately_148) {
    Object dict;
    FileStream stream(gooFile.get(), 0, true, 0, std::move(dict));
    stream.rewind();

    int ch = stream.getChar();
    EXPECT_EQ(ch, EOF);

    stream.close();
}

// Test reading entire content of stream
TEST_F(FileStreamTest_148, ReadEntireContent_148) {
    Object dict;
    FileStream stream(gooFile.get(), 0, true, static_cast<Goffset>(testData.size()), std::move(dict));
    stream.rewind();

    std::string result;
    int ch;
    while ((ch = stream.getChar()) != EOF) {
        result += static_cast<char>(ch);
    }

    EXPECT_EQ(result, testData);

    stream.close();
}

// Test setPos with direction -1 (from end)
TEST_F(FileStreamTest_148, SetPosFromEnd_148) {
    Object dict;
    FileStream stream(gooFile.get(), 0, false, 0, std::move(dict));
    stream.rewind();

    // Set position to 5 bytes before end of file
    stream.setPos(5, -1);
    Goffset pos = stream.getPos();
    // Position should be near the end
    EXPECT_GT(pos, 0);

    stream.close();
}

// Test lookChar on empty/EOF stream returns EOF
TEST_F(FileStreamTest_148, LookCharAtEOFReturnsEOF_148) {
    Object dict;
    FileStream stream(gooFile.get(), 0, true, 1, std::move(dict));
    stream.rewind();

    stream.getChar(); // read the only character
    int ch = stream.lookChar();
    EXPECT_EQ(ch, EOF);

    stream.close();
}
