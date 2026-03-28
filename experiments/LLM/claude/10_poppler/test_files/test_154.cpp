#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <cstdio>
#include <cstring>
#include <fstream>

#include "Stream.h"
#include "goo/GooFile.h"
#include "Object.h"

class FileStreamTest_154 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a temporary file with known content
        tmpFilename = "filestream_test_154.tmp";
        std::ofstream ofs(tmpFilename, std::ios::binary);
        testData = "Hello, World! This is a test file for FileStream unit tests. "
                   "It contains enough data to test various stream operations including "
                   "reading, seeking, and boundary conditions. 0123456789ABCDEF";
        ofs.write(testData.c_str(), testData.size());
        ofs.close();

        gooFile = GooFile::open(tmpFilename);
        ASSERT_NE(gooFile, nullptr);
    }

    void TearDown() override {
        gooFile = nullptr;
        std::remove(tmpFilename.c_str());
    }

    std::string tmpFilename;
    std::string testData;
    std::unique_ptr<GooFile> gooFile;
};

// Test that FileStream can be constructed and destroyed without crashing
TEST_F(FileStreamTest_154, ConstructAndDestruct_154) {
    Object dict;
    FileStream stream(gooFile.get(), 0, true, testData.size(), std::move(dict));
    stream.close();
}

// Test getKind returns strFile
TEST_F(FileStreamTest_154, GetKindReturnsFileStream_154) {
    Object dict;
    FileStream stream(gooFile.get(), 0, true, testData.size(), std::move(dict));
    EXPECT_EQ(stream.getKind(), strFile);
    stream.close();
}

// Test reading first character
TEST_F(FileStreamTest_154, GetCharReturnsFirstChar_154) {
    Object dict;
    FileStream stream(gooFile.get(), 0, true, testData.size(), std::move(dict));
    stream.rewind();
    int ch = stream.getChar();
    EXPECT_EQ(ch, 'H');
    stream.close();
}

// Test lookChar does not advance position
TEST_F(FileStreamTest_154, LookCharDoesNotAdvance_154) {
    Object dict;
    FileStream stream(gooFile.get(), 0, true, testData.size(), std::move(dict));
    stream.rewind();
    int ch1 = stream.lookChar();
    int ch2 = stream.lookChar();
    EXPECT_EQ(ch1, ch2);
    EXPECT_EQ(ch1, 'H');
    stream.close();
}

// Test sequential reads
TEST_F(FileStreamTest_154, SequentialReads_154) {
    Object dict;
    FileStream stream(gooFile.get(), 0, true, testData.size(), std::move(dict));
    stream.rewind();
    for (size_t i = 0; i < testData.size(); i++) {
        int ch = stream.getChar();
        EXPECT_EQ(ch, (unsigned char)testData[i]) << "Mismatch at position " << i;
    }
    stream.close();
}

// Test EOF after reading all data
TEST_F(FileStreamTest_154, ReturnsEOFAfterAllData_154) {
    Object dict;
    FileStream stream(gooFile.get(), 0, true, testData.size(), std::move(dict));
    stream.rewind();
    for (size_t i = 0; i < testData.size(); i++) {
        stream.getChar();
    }
    int ch = stream.getChar();
    EXPECT_EQ(ch, EOF);
    stream.close();
}

// Test rewind resets to beginning
TEST_F(FileStreamTest_154, RewindResetsPosition_154) {
    Object dict;
    FileStream stream(gooFile.get(), 0, true, testData.size(), std::move(dict));
    stream.rewind();
    stream.getChar();
    stream.getChar();
    stream.getChar();
    bool result = stream.rewind();
    EXPECT_TRUE(result);
    int ch = stream.getChar();
    EXPECT_EQ(ch, 'H');
    stream.close();
}

// Test unfilteredRewind calls rewind
TEST_F(FileStreamTest_154, UnfilteredRewindWorks_154) {
    Object dict;
    FileStream stream(gooFile.get(), 0, true, testData.size(), std::move(dict));
    stream.rewind();
    stream.getChar();
    stream.getChar();
    bool result = stream.unfilteredRewind();
    EXPECT_TRUE(result);
    int ch = stream.getChar();
    EXPECT_EQ(ch, 'H');
    stream.close();
}

// Test getPos returns current position
TEST_F(FileStreamTest_154, GetPosReturnsCurrentPosition_154) {
    Object dict;
    FileStream stream(gooFile.get(), 0, true, testData.size(), std::move(dict));
    stream.rewind();
    EXPECT_EQ(stream.getPos(), 0);
    stream.getChar();
    EXPECT_EQ(stream.getPos(), 1);
    stream.getChar();
    EXPECT_EQ(stream.getPos(), 2);
    stream.close();
}

// Test getStart returns start offset
TEST_F(FileStreamTest_154, GetStartReturnsStartOffset_154) {
    Object dict;
    FileStream stream(gooFile.get(), 0, true, testData.size(), std::move(dict));
    EXPECT_EQ(stream.getStart(), 0);
    stream.close();
}

// Test getStart with non-zero offset
TEST_F(FileStreamTest_154, GetStartWithOffset_154) {
    Object dict;
    Goffset offset = 5;
    FileStream stream(gooFile.get(), offset, true, testData.size() - offset, std::move(dict));
    EXPECT_EQ(stream.getStart(), offset);
    stream.close();
}

// Test reading with non-zero start offset
TEST_F(FileStreamTest_154, ReadWithOffset_154) {
    Object dict;
    Goffset offset = 7;
    FileStream stream(gooFile.get(), offset, true, testData.size() - offset, std::move(dict));
    stream.rewind();
    int ch = stream.getChar();
    EXPECT_EQ(ch, (unsigned char)testData[offset]);
    stream.close();
}

// Test setPos with forward direction (dir=0)
TEST_F(FileStreamTest_154, SetPosForward_154) {
    Object dict;
    FileStream stream(gooFile.get(), 0, true, testData.size(), std::move(dict));
    stream.rewind();
    stream.setPos(5, 0);
    int ch = stream.getChar();
    EXPECT_EQ(ch, (unsigned char)testData[5]);
    stream.close();
}

// Test moveStart
TEST_F(FileStreamTest_154, MoveStartDelta_154) {
    Object dict;
    FileStream stream(gooFile.get(), 0, true, testData.size(), std::move(dict));
    Goffset origStart = stream.getStart();
    stream.moveStart(3);
    EXPECT_EQ(stream.getStart(), origStart + 3);
    stream.close();
}

// Test copy creates a new stream
TEST_F(FileStreamTest_154, CopyCreatesNewStream_154) {
    Object dict;
    FileStream stream(gooFile.get(), 0, true, testData.size(), std::move(dict));
    auto copied = stream.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getKind(), strFile);
    stream.close();
}

// Test makeSubStream
TEST_F(FileStreamTest_154, MakeSubStream_154) {
    Object dict;
    FileStream stream(gooFile.get(), 0, true, testData.size(), std::move(dict));
    Object subDict;
    auto subStream = stream.makeSubStream(5, true, 10, std::move(subDict));
    ASSERT_NE(subStream, nullptr);
    subStream->reset();
    int ch = subStream->getChar();
    EXPECT_EQ(ch, (unsigned char)testData[5]);
    stream.close();
}

// Test getNeedsEncryptionOnSave default value
TEST_F(FileStreamTest_154, GetNeedsEncryptionOnSaveDefault_154) {
    Object dict;
    FileStream stream(gooFile.get(), 0, true, testData.size(), std::move(dict));
    // Default should be false
    EXPECT_FALSE(stream.getNeedsEncryptionOnSave());
    stream.close();
}

// Test setNeedsEncryptionOnSave
TEST_F(FileStreamTest_154, SetNeedsEncryptionOnSave_154) {
    Object dict;
    FileStream stream(gooFile.get(), 0, true, testData.size(), std::move(dict));
    stream.setNeedsEncryptionOnSave(true);
    EXPECT_TRUE(stream.getNeedsEncryptionOnSave());
    stream.setNeedsEncryptionOnSave(false);
    EXPECT_FALSE(stream.getNeedsEncryptionOnSave());
    stream.close();
}

// Test getUnfilteredChar
TEST_F(FileStreamTest_154, GetUnfilteredChar_154) {
    Object dict;
    FileStream stream(gooFile.get(), 0, true, testData.size(), std::move(dict));
    stream.rewind();
    int ch = stream.getUnfilteredChar();
    EXPECT_EQ(ch, 'H');
    stream.close();
}

// Test zero-length stream
TEST_F(FileStreamTest_154, ZeroLengthStream_154) {
    Object dict;
    FileStream stream(gooFile.get(), 0, true, 0, std::move(dict));
    stream.rewind();
    int ch = stream.getChar();
    EXPECT_EQ(ch, EOF);
    stream.close();
}

// Test unlimited stream (limited = false)
TEST_F(FileStreamTest_154, UnlimitedStream_154) {
    Object dict;
    FileStream stream(gooFile.get(), 0, false, 0, std::move(dict));
    stream.rewind();
    int ch = stream.getChar();
    EXPECT_EQ(ch, 'H');
    stream.close();
}

// Test reading with limited length shorter than file
TEST_F(FileStreamTest_154, LimitedLengthShorterThanFile_154) {
    Object dict;
    Goffset limitedLen = 5;
    FileStream stream(gooFile.get(), 0, true, limitedLen, std::move(dict));
    stream.rewind();
    for (Goffset i = 0; i < limitedLen; i++) {
        int ch = stream.getChar();
        EXPECT_EQ(ch, (unsigned char)testData[i]);
    }
    int ch = stream.getChar();
    EXPECT_EQ(ch, EOF);
    stream.close();
}

// Test setPos to position 0
TEST_F(FileStreamTest_154, SetPosToZero_154) {
    Object dict;
    FileStream stream(gooFile.get(), 0, true, testData.size(), std::move(dict));
    stream.rewind();
    stream.getChar();
    stream.getChar();
    stream.setPos(0, 0);
    int ch = stream.getChar();
    EXPECT_EQ(ch, 'H');
    stream.close();
}

// Test lookChar at EOF
TEST_F(FileStreamTest_154, LookCharAtEOF_154) {
    Object dict;
    FileStream stream(gooFile.get(), 0, true, 1, std::move(dict));
    stream.rewind();
    stream.getChar(); // consume the one byte
    int ch = stream.lookChar();
    EXPECT_EQ(ch, EOF);
    stream.close();
}

// Test large file reading across buffer boundary
TEST_F(FileStreamTest_154, LargeFileAcrossBufferBoundary_154) {
    // Create a larger temp file
    std::string largeTmpFile = "filestream_large_test_154.tmp";
    {
        std::ofstream ofs(largeTmpFile, std::ios::binary);
        // Write more than fileStreamBufSize (16384) bytes
        std::string largeData(20000, 'A');
        for (int i = 0; i < 20000; i++) {
            largeData[i] = 'A' + (i % 26);
        }
        ofs.write(largeData.c_str(), largeData.size());
        ofs.close();

        auto largeGooFile = GooFile::open(largeTmpFile);
        ASSERT_NE(largeGooFile, nullptr);

        Object dict;
        FileStream stream(largeGooFile.get(), 0, true, 20000, std::move(dict));
        stream.rewind();

        // Read across the buffer boundary
        for (int i = 0; i < 20000; i++) {
            int ch = stream.getChar();
            EXPECT_EQ(ch, (unsigned char)('A' + (i % 26))) << "Mismatch at position " << i;
        }
        int ch = stream.getChar();
        EXPECT_EQ(ch, EOF);
        stream.close();
    }
    std::remove(largeTmpFile.c_str());
}
