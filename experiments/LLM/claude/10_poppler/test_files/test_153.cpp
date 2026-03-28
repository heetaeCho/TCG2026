#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <cstdio>
#include <cstring>
#include <fstream>

#include "Stream.h"
#include "goo/GooFile.h"
#include "Object.h"

// Helper to create a temporary file with known content
class FileStreamTest_153 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a temporary file with known content
        tmpFilePath = std::tmpnam(nullptr);
        std::ofstream ofs(tmpFilePath, std::ios::binary);
        testContent = "Hello, World! This is a test file for FileStream unit tests.";
        ofs.write(testContent.c_str(), testContent.size());
        ofs.close();

        gooFile = GooFile::open(tmpFilePath);
        ASSERT_NE(gooFile, nullptr);
    }

    void TearDown() override {
        gooFile = nullptr;
        std::remove(tmpFilePath.c_str());
    }

    std::string tmpFilePath;
    std::string testContent;
    std::unique_ptr<GooFile> gooFile;
};

// Helper to create a larger temporary file
class FileStreamLargeTest_153 : public ::testing::Test {
protected:
    void SetUp() override {
        tmpFilePath = std::tmpnam(nullptr);
        std::ofstream ofs(tmpFilePath, std::ios::binary);
        // Create content larger than buffer size (16384)
        largeContent.resize(20000, 'A');
        for (size_t i = 0; i < largeContent.size(); i++) {
            largeContent[i] = static_cast<char>('A' + (i % 26));
        }
        ofs.write(largeContent.c_str(), largeContent.size());
        ofs.close();

        gooFile = GooFile::open(tmpFilePath);
        ASSERT_NE(gooFile, nullptr);
    }

    void TearDown() override {
        gooFile = nullptr;
        std::remove(tmpFilePath.c_str());
    }

    std::string tmpFilePath;
    std::string largeContent;
    std::unique_ptr<GooFile> gooFile;
};

// Helper for empty file tests
class FileStreamEmptyTest_153 : public ::testing::Test {
protected:
    void SetUp() override {
        tmpFilePath = std::tmpnam(nullptr);
        std::ofstream ofs(tmpFilePath, std::ios::binary);
        ofs.close();

        gooFile = GooFile::open(tmpFilePath);
        ASSERT_NE(gooFile, nullptr);
    }

    void TearDown() override {
        gooFile = nullptr;
        std::remove(tmpFilePath.c_str());
    }

    std::string tmpFilePath;
    std::unique_ptr<GooFile> gooFile;
};

TEST_F(FileStreamTest_153, ConstructionAndGetKind_153) {
    Object dict;
    FileStream fs(gooFile.get(), 0, true, testContent.size(), std::move(dict));
    EXPECT_EQ(fs.getKind(), strFile);
    fs.close();
}

TEST_F(FileStreamTest_153, GetCharReadsFirstCharacter_153) {
    Object dict;
    FileStream fs(gooFile.get(), 0, true, testContent.size(), std::move(dict));
    fs.rewind();
    int ch = fs.getChar();
    EXPECT_EQ(ch, 'H');
    fs.close();
}

TEST_F(FileStreamTest_153, GetCharReadsSequentially_153) {
    Object dict;
    FileStream fs(gooFile.get(), 0, true, testContent.size(), std::move(dict));
    fs.rewind();
    for (size_t i = 0; i < testContent.size(); i++) {
        int ch = fs.getChar();
        EXPECT_EQ(ch, static_cast<unsigned char>(testContent[i])) << "Mismatch at position " << i;
    }
    fs.close();
}

TEST_F(FileStreamTest_153, GetCharReturnsEOFAtEnd_153) {
    Object dict;
    FileStream fs(gooFile.get(), 0, true, testContent.size(), std::move(dict));
    fs.rewind();
    // Read all characters
    for (size_t i = 0; i < testContent.size(); i++) {
        fs.getChar();
    }
    int ch = fs.getChar();
    EXPECT_EQ(ch, EOF);
    fs.close();
}

TEST_F(FileStreamTest_153, LookCharDoesNotAdvancePosition_153) {
    Object dict;
    FileStream fs(gooFile.get(), 0, true, testContent.size(), std::move(dict));
    fs.rewind();
    int ch1 = fs.lookChar();
    int ch2 = fs.lookChar();
    EXPECT_EQ(ch1, ch2);
    EXPECT_EQ(ch1, 'H');
    fs.close();
}

TEST_F(FileStreamTest_153, LookCharThenGetChar_153) {
    Object dict;
    FileStream fs(gooFile.get(), 0, true, testContent.size(), std::move(dict));
    fs.rewind();
    int looked = fs.lookChar();
    int got = fs.getChar();
    EXPECT_EQ(looked, got);
    EXPECT_EQ(got, 'H');
    fs.close();
}

TEST_F(FileStreamTest_153, GetPosStartsAtZero_153) {
    Object dict;
    FileStream fs(gooFile.get(), 0, true, testContent.size(), std::move(dict));
    fs.rewind();
    EXPECT_EQ(fs.getPos(), 0);
    fs.close();
}

TEST_F(FileStreamTest_153, GetPosAdvancesAfterGetChar_153) {
    Object dict;
    FileStream fs(gooFile.get(), 0, true, testContent.size(), std::move(dict));
    fs.rewind();
    fs.getChar();
    EXPECT_EQ(fs.getPos(), 1);
    fs.getChar();
    EXPECT_EQ(fs.getPos(), 2);
    fs.close();
}

TEST_F(FileStreamTest_153, GetStartReturnsStartOffset_153) {
    Object dict;
    FileStream fs(gooFile.get(), 5, true, testContent.size() - 5, std::move(dict));
    EXPECT_EQ(fs.getStart(), 5);
    fs.close();
}

TEST_F(FileStreamTest_153, RewindResetsPosition_153) {
    Object dict;
    FileStream fs(gooFile.get(), 0, true, testContent.size(), std::move(dict));
    fs.rewind();
    fs.getChar();
    fs.getChar();
    fs.getChar();
    EXPECT_GT(fs.getPos(), 0);
    bool result = fs.rewind();
    EXPECT_TRUE(result);
    EXPECT_EQ(fs.getPos(), 0);
    fs.close();
}

TEST_F(FileStreamTest_153, SetPosFromStart_153) {
    Object dict;
    FileStream fs(gooFile.get(), 0, true, testContent.size(), std::move(dict));
    fs.rewind();
    fs.setPos(5, 0);
    int ch = fs.getChar();
    EXPECT_EQ(ch, static_cast<unsigned char>(testContent[5]));
    fs.close();
}

TEST_F(FileStreamTest_153, MoveStartDelta_153) {
    Object dict;
    FileStream fs(gooFile.get(), 0, true, testContent.size(), std::move(dict));
    EXPECT_EQ(fs.getStart(), 0);
    fs.moveStart(3);
    EXPECT_EQ(fs.getStart(), 3);
    fs.close();
}

TEST_F(FileStreamTest_153, GetUnfilteredCharSameAsGetChar_153) {
    Object dict1, dict2;
    FileStream fs1(gooFile.get(), 0, true, testContent.size(), std::move(dict1));
    FileStream fs2(gooFile.get(), 0, true, testContent.size(), std::move(dict2));
    fs1.rewind();
    fs2.rewind();
    for (size_t i = 0; i < 10; i++) {
        int ch1 = fs1.getChar();
        int ch2 = fs2.getUnfilteredChar();
        EXPECT_EQ(ch1, ch2) << "Mismatch at position " << i;
    }
    fs1.close();
    fs2.close();
}

TEST_F(FileStreamTest_153, UnfilteredRewind_153) {
    Object dict;
    FileStream fs(gooFile.get(), 0, true, testContent.size(), std::move(dict));
    fs.rewind();
    fs.getChar();
    fs.getChar();
    bool result = fs.unfilteredRewind();
    EXPECT_TRUE(result);
    fs.close();
}

TEST_F(FileStreamTest_153, ReadFromOffset_153) {
    Object dict;
    Goffset startOffset = 7; // "World! ..."
    FileStream fs(gooFile.get(), startOffset, true, testContent.size() - startOffset, std::move(dict));
    fs.rewind();
    int ch = fs.getChar();
    EXPECT_EQ(ch, static_cast<unsigned char>(testContent[startOffset]));
    fs.close();
}

TEST_F(FileStreamTest_153, CopyProducesEquivalentStream_153) {
    Object dict;
    FileStream fs(gooFile.get(), 0, true, testContent.size(), std::move(dict));
    fs.rewind();

    auto copied = fs.copy();
    ASSERT_NE(copied, nullptr);

    // The copied stream should produce the same kind
    EXPECT_EQ(copied->getKind(), strFile);
    fs.close();
}

TEST_F(FileStreamTest_153, MakeSubStream_153) {
    Object dict;
    FileStream fs(gooFile.get(), 0, true, testContent.size(), std::move(dict));
    fs.rewind();

    Object subDict;
    auto sub = fs.makeSubStream(5, true, 10, std::move(subDict));
    ASSERT_NE(sub, nullptr);
    sub->reset();
    int ch = sub->getChar();
    EXPECT_EQ(ch, static_cast<unsigned char>(testContent[5]));
    sub->close();
    fs.close();
}

TEST_F(FileStreamTest_153, NeedsEncryptionOnSaveDefaultFalse_153) {
    Object dict;
    FileStream fs(gooFile.get(), 0, true, testContent.size(), std::move(dict));
    // Default should typically be false
    EXPECT_FALSE(fs.getNeedsEncryptionOnSave());
    fs.close();
}

TEST_F(FileStreamTest_153, SetAndGetNeedsEncryptionOnSave_153) {
    Object dict;
    FileStream fs(gooFile.get(), 0, true, testContent.size(), std::move(dict));
    fs.setNeedsEncryptionOnSave(true);
    EXPECT_TRUE(fs.getNeedsEncryptionOnSave());
    fs.setNeedsEncryptionOnSave(false);
    EXPECT_FALSE(fs.getNeedsEncryptionOnSave());
    fs.close();
}

TEST_F(FileStreamEmptyTest_153, GetCharReturnsEOFOnEmptyFile_153) {
    Object dict;
    FileStream fs(gooFile.get(), 0, true, 0, std::move(dict));
    fs.rewind();
    int ch = fs.getChar();
    EXPECT_EQ(ch, EOF);
    fs.close();
}

TEST_F(FileStreamEmptyTest_153, LookCharReturnsEOFOnEmptyFile_153) {
    Object dict;
    FileStream fs(gooFile.get(), 0, true, 0, std::move(dict));
    fs.rewind();
    int ch = fs.lookChar();
    EXPECT_EQ(ch, EOF);
    fs.close();
}

TEST_F(FileStreamEmptyTest_153, GetPosOnEmptyFile_153) {
    Object dict;
    FileStream fs(gooFile.get(), 0, true, 0, std::move(dict));
    fs.rewind();
    EXPECT_EQ(fs.getPos(), 0);
    fs.close();
}

TEST_F(FileStreamLargeTest_153, ReadAcrossBufferBoundary_153) {
    Object dict;
    FileStream fs(gooFile.get(), 0, true, largeContent.size(), std::move(dict));
    fs.rewind();

    // Read across the buffer boundary (buf size is 16384)
    for (size_t i = 0; i < largeContent.size(); i++) {
        int ch = fs.getChar();
        EXPECT_EQ(ch, static_cast<unsigned char>(largeContent[i]))
            << "Mismatch at position " << i;
    }
    // Should get EOF after all content
    EXPECT_EQ(fs.getChar(), EOF);
    fs.close();
}

TEST_F(FileStreamLargeTest_153, SetPosAndReadLargeFile_153) {
    Object dict;
    FileStream fs(gooFile.get(), 0, true, largeContent.size(), std::move(dict));
    fs.rewind();

    // Jump to position past the first buffer
    Goffset pos = 17000;
    fs.setPos(pos, 0);
    int ch = fs.getChar();
    EXPECT_EQ(ch, static_cast<unsigned char>(largeContent[pos]));
    fs.close();
}

TEST_F(FileStreamTest_153, LimitedStreamRespectsLength_153) {
    Object dict;
    Goffset limitedLength = 5;
    FileStream fs(gooFile.get(), 0, true, limitedLength, std::move(dict));
    fs.rewind();

    for (Goffset i = 0; i < limitedLength; i++) {
        int ch = fs.getChar();
        EXPECT_EQ(ch, static_cast<unsigned char>(testContent[i]));
    }
    int ch = fs.getChar();
    EXPECT_EQ(ch, EOF);
    fs.close();
}

TEST_F(FileStreamTest_153, RewindAfterClose_153) {
    Object dict;
    FileStream fs(gooFile.get(), 0, true, testContent.size(), std::move(dict));
    fs.rewind();
    fs.getChar();
    fs.close();
    // Rewind after close should still work (re-open internally)
    bool result = fs.rewind();
    EXPECT_TRUE(result);
    int ch = fs.getChar();
    EXPECT_EQ(ch, static_cast<unsigned char>(testContent[0]));
    fs.close();
}

TEST_F(FileStreamTest_153, MultipleRewinds_153) {
    Object dict;
    FileStream fs(gooFile.get(), 0, true, testContent.size(), std::move(dict));

    for (int round = 0; round < 3; round++) {
        fs.rewind();
        EXPECT_EQ(fs.getPos(), 0);
        int ch = fs.getChar();
        EXPECT_EQ(ch, static_cast<unsigned char>(testContent[0]));
    }
    fs.close();
}

TEST_F(FileStreamTest_153, SetPosFromEnd_153) {
    Object dict;
    FileStream fs(gooFile.get(), 0, false, 0, std::move(dict));
    fs.rewind();

    // dir = -1 means from end of file
    fs.setPos(1, -1);
    int ch = fs.getChar();
    // Should read the last character
    EXPECT_EQ(ch, static_cast<unsigned char>(testContent[testContent.size() - 1]));
    fs.close();
}

TEST_F(FileStreamTest_153, GetStartWithZeroOffset_153) {
    Object dict;
    FileStream fs(gooFile.get(), 0, true, testContent.size(), std::move(dict));
    EXPECT_EQ(fs.getStart(), 0);
    fs.close();
}

TEST_F(FileStreamTest_153, MoveStartMultipleTimes_153) {
    Object dict;
    FileStream fs(gooFile.get(), 0, true, testContent.size(), std::move(dict));
    fs.moveStart(2);
    EXPECT_EQ(fs.getStart(), 2);
    fs.moveStart(3);
    EXPECT_EQ(fs.getStart(), 5);
    fs.close();
}
