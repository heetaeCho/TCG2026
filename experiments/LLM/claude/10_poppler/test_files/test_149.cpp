#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <cstdio>
#include <cstring>
#include <fstream>

#include "Stream.h"
#include "goo/GooFile.h"
#include "Object.h"

class FileStreamTest_149 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a temporary file with known content
        tmpFilePath = std::tmpnam(nullptr);
        std::ofstream ofs(tmpFilePath, std::ios::binary);
        // Write known content: "Hello, World!" followed by more bytes
        testContent = "Hello, World! This is a test file for FileStream unit testing.";
        ofs.write(testContent.c_str(), testContent.size());
        ofs.close();

        gooFile = GooFile::open(tmpFilePath);
        ASSERT_NE(gooFile, nullptr);
    }

    void TearDown() override {
        fileStream.reset();
        delete gooFile;
        std::remove(tmpFilePath.c_str());
    }

    void createStream(Goffset start, bool limited, Goffset length) {
        Object dict;
        fileStream = std::make_unique<FileStream>(gooFile, start, limited, length, std::move(dict));
        fileStream->rewind();
    }

    std::string tmpFilePath;
    std::string testContent;
    GooFile *gooFile = nullptr;
    std::unique_ptr<FileStream> fileStream;
};

// Test that getChar returns the first character of the file
TEST_F(FileStreamTest_149, GetCharReturnsFirstByte_149) {
    createStream(0, false, 0);
    int ch = fileStream->getChar();
    EXPECT_EQ(ch, 'H');
}

// Test that getChar reads sequential characters
TEST_F(FileStreamTest_149, GetCharReadsSequentially_149) {
    createStream(0, true, testContent.size());
    for (size_t i = 0; i < testContent.size(); i++) {
        int ch = fileStream->getChar();
        EXPECT_EQ(ch, (unsigned char)testContent[i]) << "Mismatch at index " << i;
    }
}

// Test that getChar returns EOF after reading all limited content
TEST_F(FileStreamTest_149, GetCharReturnsEOFAtEnd_149) {
    createStream(0, true, 5);
    for (int i = 0; i < 5; i++) {
        int ch = fileStream->getChar();
        EXPECT_NE(ch, EOF);
    }
    int ch = fileStream->getChar();
    EXPECT_EQ(ch, EOF);
}

// Test lookChar returns current byte without advancing
TEST_F(FileStreamTest_149, LookCharDoesNotAdvance_149) {
    createStream(0, false, 0);
    int ch1 = fileStream->lookChar();
    int ch2 = fileStream->lookChar();
    EXPECT_EQ(ch1, ch2);
    EXPECT_EQ(ch1, 'H');
}

// Test that lookChar followed by getChar returns the same character
TEST_F(FileStreamTest_149, LookCharThenGetCharSameValue_149) {
    createStream(0, false, 0);
    int looked = fileStream->lookChar();
    int got = fileStream->getChar();
    EXPECT_EQ(looked, got);
}

// Test getPos returns current position
TEST_F(FileStreamTest_149, GetPosReturnsCurrentPosition_149) {
    createStream(0, true, testContent.size());
    EXPECT_EQ(fileStream->getPos(), 0);
    fileStream->getChar();
    EXPECT_EQ(fileStream->getPos(), 1);
    fileStream->getChar();
    EXPECT_EQ(fileStream->getPos(), 2);
}

// Test getStart returns the start offset
TEST_F(FileStreamTest_149, GetStartReturnsStartOffset_149) {
    createStream(10, true, 5);
    EXPECT_EQ(fileStream->getStart(), 10);
}

// Test stream with offset
TEST_F(FileStreamTest_149, StreamWithOffset_149) {
    createStream(7, true, 5);
    // "Hello, World!..." - offset 7 is 'W'
    int ch = fileStream->getChar();
    EXPECT_EQ(ch, 'W');
}

// Test rewind resets position
TEST_F(FileStreamTest_149, RewindResetsPosition_149) {
    createStream(0, true, testContent.size());
    fileStream->getChar();
    fileStream->getChar();
    fileStream->getChar();
    EXPECT_EQ(fileStream->getPos(), 3);
    bool result = fileStream->rewind();
    EXPECT_TRUE(result);
    EXPECT_EQ(fileStream->getPos(), 0);
    int ch = fileStream->getChar();
    EXPECT_EQ(ch, 'H');
}

// Test getKind returns fileStream kind
TEST_F(FileStreamTest_149, GetKindReturnsFileStream_149) {
    createStream(0, false, 0);
    EXPECT_EQ(fileStream->getKind(), strFile);
}

// Test setPos with dir=0 (from start)
TEST_F(FileStreamTest_149, SetPosFromStart_149) {
    createStream(0, true, testContent.size());
    fileStream->setPos(5, 0);
    int ch = fileStream->getChar();
    EXPECT_EQ(ch, ',');
}

// Test moveStart moves the start offset
TEST_F(FileStreamTest_149, MoveStartMovesOffset_149) {
    createStream(0, true, testContent.size());
    fileStream->moveStart(5);
    EXPECT_EQ(fileStream->getStart(), 5);
}

// Test copy returns a valid stream
TEST_F(FileStreamTest_149, CopyReturnsValidStream_149) {
    createStream(0, true, testContent.size());
    auto copied = fileStream->copy();
    ASSERT_NE(copied, nullptr);
    copied->rewind();
    int ch = copied->getChar();
    EXPECT_EQ(ch, 'H');
}

// Test makeSubStream creates a valid substream
TEST_F(FileStreamTest_149, MakeSubStreamCreatesValidStream_149) {
    createStream(0, true, testContent.size());
    Object dict;
    auto sub = fileStream->makeSubStream(7, true, 5, std::move(dict));
    ASSERT_NE(sub, nullptr);
    sub->rewind();
    int ch = sub->getChar();
    EXPECT_EQ(ch, 'W');
}

// Test limited stream of zero length returns EOF immediately
TEST_F(FileStreamTest_149, ZeroLengthLimitedStreamReturnsEOF_149) {
    createStream(0, true, 0);
    int ch = fileStream->getChar();
    EXPECT_EQ(ch, EOF);
}

// Test getUnfilteredChar behaves like getChar for FileStream
TEST_F(FileStreamTest_149, GetUnfilteredCharReturnsByte_149) {
    createStream(0, true, testContent.size());
    int ch = fileStream->getUnfilteredChar();
    EXPECT_EQ(ch, 'H');
}

// Test unfilteredRewind works
TEST_F(FileStreamTest_149, UnfilteredRewindWorks_149) {
    createStream(0, true, testContent.size());
    fileStream->getChar();
    fileStream->getChar();
    bool result = fileStream->unfilteredRewind();
    EXPECT_TRUE(result);
    int ch = fileStream->getChar();
    EXPECT_EQ(ch, 'H');
}

// Test getNeedsEncryptionOnSave default value
TEST_F(FileStreamTest_149, GetNeedsEncryptionOnSaveDefault_149) {
    createStream(0, false, 0);
    // By default it should be false (typical initialization)
    bool val = fileStream->getNeedsEncryptionOnSave();
    EXPECT_FALSE(val);
}

// Test setNeedsEncryptionOnSave
TEST_F(FileStreamTest_149, SetNeedsEncryptionOnSave_149) {
    createStream(0, false, 0);
    fileStream->setNeedsEncryptionOnSave(true);
    EXPECT_TRUE(fileStream->getNeedsEncryptionOnSave());
    fileStream->setNeedsEncryptionOnSave(false);
    EXPECT_FALSE(fileStream->getNeedsEncryptionOnSave());
}

// Test that getChar returns values in 0-255 range (unsigned byte)
TEST_F(FileStreamTest_149, GetCharReturnsUnsignedByte_149) {
    // Create a file with a byte value > 127
    std::string tmpPath2 = std::tmpnam(nullptr);
    {
        std::ofstream ofs(tmpPath2, std::ios::binary);
        unsigned char highByte = 0xFF;
        ofs.write(reinterpret_cast<char*>(&highByte), 1);
        ofs.close();
    }
    GooFile *gf2 = GooFile::open(tmpPath2);
    ASSERT_NE(gf2, nullptr);
    Object dict;
    FileStream fs(gf2, 0, true, 1, std::move(dict));
    fs.rewind();
    int ch = fs.getChar();
    EXPECT_EQ(ch, 0xFF);
    EXPECT_GE(ch, 0);
    EXPECT_LE(ch, 255);
    delete gf2;
    std::remove(tmpPath2.c_str());
}

// Test reading a large file that exceeds buffer size (16384 bytes)
TEST_F(FileStreamTest_149, LargeFileExceedsBufferSize_149) {
    std::string tmpPath3 = std::tmpnam(nullptr);
    const int totalSize = 20000; // > 16384 (fileStreamBufSize)
    {
        std::ofstream ofs(tmpPath3, std::ios::binary);
        for (int i = 0; i < totalSize; i++) {
            char c = (char)(i % 256);
            ofs.write(&c, 1);
        }
        ofs.close();
    }
    GooFile *gf3 = GooFile::open(tmpPath3);
    ASSERT_NE(gf3, nullptr);
    Object dict;
    FileStream fs(gf3, 0, true, totalSize, std::move(dict));
    fs.rewind();
    for (int i = 0; i < totalSize; i++) {
        int ch = fs.getChar();
        EXPECT_EQ(ch, i % 256) << "Mismatch at byte " << i;
    }
    int ch = fs.getChar();
    EXPECT_EQ(ch, EOF);
    delete gf3;
    std::remove(tmpPath3.c_str());
}

// Test close and then attempt to read
TEST_F(FileStreamTest_149, CloseStream_149) {
    createStream(0, true, testContent.size());
    fileStream->getChar(); // read one byte
    fileStream->close();
    // After close, behavior may vary, but we test it doesn't crash
    // Rewind and read again
    fileStream->rewind();
    int ch = fileStream->getChar();
    // After rewind post-close, it should still work for FileStream
    EXPECT_EQ(ch, 'H');
}

// Test setPos with dir from end (negative direction)
TEST_F(FileStreamTest_149, SetPosFromEnd_149) {
    createStream(0, true, testContent.size());
    // dir != 0 means from end
    fileStream->setPos(1, -1);
    int ch = fileStream->getChar();
    // Last character of testContent
    EXPECT_EQ(ch, (unsigned char)testContent[testContent.size() - 1]);
}

// Test limited stream with offset and length
TEST_F(FileStreamTest_149, LimitedStreamWithOffsetAndLength_149) {
    // Read "World" from "Hello, World!..."
    createStream(7, true, 5);
    std::string result;
    for (int i = 0; i < 5; i++) {
        int ch = fileStream->getChar();
        ASSERT_NE(ch, EOF);
        result += (char)ch;
    }
    EXPECT_EQ(result, "World");
    int ch = fileStream->getChar();
    EXPECT_EQ(ch, EOF);
}
