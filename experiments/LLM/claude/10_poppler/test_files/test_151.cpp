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
class FileStreamTest_151 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a temporary file with known content
        tmpFilePath = std::tmpnam(nullptr);
        std::ofstream ofs(tmpFilePath, std::ios::binary);
        testContent = "Hello, World! This is a test file for FileStream unit testing. "
                      "It contains enough data to test various operations including "
                      "reading characters, seeking positions, and boundary conditions. "
                      "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz";
        ofs.write(testContent.c_str(), testContent.size());
        ofs.close();

        gooFile = GooFile::open(tmpFilePath);
        ASSERT_NE(gooFile, nullptr);
    }

    void TearDown() override {
        gooFile = nullptr;
        std::remove(tmpFilePath.c_str());
    }

    std::unique_ptr<FileStream> createStream(Goffset start = 0, bool limited = false, Goffset length = 0) {
        Object dict;
        return std::make_unique<FileStream>(gooFile.get(), start, limited, length, std::move(dict));
    }

    std::string tmpFilePath;
    std::string testContent;
    std::unique_ptr<GooFile> gooFile;
};

// Test that getPos returns 0 initially after construction and reset
TEST_F(FileStreamTest_151, GetPosInitiallyZero_151) {
    auto stream = createStream(0, false, 0);
    stream->reset();
    EXPECT_EQ(stream->getPos(), 0);
}

// Test that getPos advances after reading a character
TEST_F(FileStreamTest_151, GetPosAdvancesAfterGetChar_151) {
    auto stream = createStream(0, false, 0);
    stream->reset();
    stream->getChar();
    EXPECT_EQ(stream->getPos(), 1);
}

// Test that getPos advances correctly after multiple reads
TEST_F(FileStreamTest_151, GetPosAdvancesAfterMultipleGetChars_151) {
    auto stream = createStream(0, false, 0);
    stream->reset();
    for (int i = 0; i < 10; i++) {
        stream->getChar();
    }
    EXPECT_EQ(stream->getPos(), 10);
}

// Test that getChar returns correct first character
TEST_F(FileStreamTest_151, GetCharReturnsCorrectFirstChar_151) {
    auto stream = createStream(0, false, 0);
    stream->reset();
    int ch = stream->getChar();
    EXPECT_EQ(ch, 'H');
}

// Test that lookChar returns current character without advancing
TEST_F(FileStreamTest_151, LookCharDoesNotAdvancePos_151) {
    auto stream = createStream(0, false, 0);
    stream->reset();
    Goffset posBefore = stream->getPos();
    int ch = stream->lookChar();
    Goffset posAfter = stream->getPos();
    EXPECT_EQ(posBefore, posAfter);
    EXPECT_EQ(ch, 'H');
}

// Test lookChar returns same value as subsequent getChar
TEST_F(FileStreamTest_151, LookCharMatchesGetChar_151) {
    auto stream = createStream(0, false, 0);
    stream->reset();
    int looked = stream->lookChar();
    int got = stream->getChar();
    EXPECT_EQ(looked, got);
}

// Test getStart returns the start offset
TEST_F(FileStreamTest_151, GetStartReturnsOffset_151) {
    auto stream = createStream(5, false, 0);
    stream->reset();
    EXPECT_EQ(stream->getStart(), 5);
}

// Test reading from a non-zero start offset
TEST_F(FileStreamTest_151, ReadFromNonZeroStart_151) {
    auto stream = createStream(7, false, 0);
    stream->reset();
    int ch = stream->getChar();
    EXPECT_EQ(ch, testContent[7]);
}

// Test limited stream reads only specified length
TEST_F(FileStreamTest_151, LimitedStreamRespectsLength_151) {
    Goffset len = 5;
    auto stream = createStream(0, true, len);
    stream->reset();
    int count = 0;
    while (stream->getChar() != EOF) {
        count++;
    }
    EXPECT_EQ(count, len);
}

// Test limited stream with zero length returns EOF immediately
TEST_F(FileStreamTest_151, LimitedStreamZeroLength_151) {
    auto stream = createStream(0, true, 0);
    stream->reset();
    int ch = stream->getChar();
    EXPECT_EQ(ch, EOF);
}

// Test rewind brings position back to start
TEST_F(FileStreamTest_151, RewindResetsPosition_151) {
    auto stream = createStream(0, false, 0);
    stream->reset();
    stream->getChar();
    stream->getChar();
    stream->getChar();
    EXPECT_EQ(stream->getPos(), 3);
    bool result = stream->rewind();
    // After rewind, position should be back to start
    // Note: rewind may behave like reset
    EXPECT_EQ(stream->getPos(), 0);
}

// Test getKind returns fileStream
TEST_F(FileStreamTest_151, GetKindReturnsFileStream_151) {
    auto stream = createStream(0, false, 0);
    EXPECT_EQ(stream->getKind(), strFile);
}

// Test setPos with absolute position
TEST_F(FileStreamTest_151, SetPosAbsolute_151) {
    auto stream = createStream(0, false, 0);
    stream->reset();
    stream->setPos(10, 0);
    int ch = stream->getChar();
    EXPECT_EQ(ch, testContent[10]);
}

// Test setPos from end of file (dir != 0)
TEST_F(FileStreamTest_151, SetPosFromEnd_151) {
    auto stream = createStream(0, false, 0);
    stream->reset();
    Goffset fileSize = static_cast<Goffset>(testContent.size());
    // Setting pos from end: negative offset from end
    stream->setPos(1, -1);
    int ch = stream->getChar();
    // Should read the last character
    EXPECT_EQ(ch, testContent[testContent.size() - 1]);
}

// Test moveStart moves the start position
TEST_F(FileStreamTest_151, MoveStartChangesStart_151) {
    auto stream = createStream(0, false, 0);
    stream->reset();
    Goffset originalStart = stream->getStart();
    stream->moveStart(5);
    EXPECT_EQ(stream->getStart(), originalStart + 5);
}

// Test copy creates a distinct stream
TEST_F(FileStreamTest_151, CopyCreatesDistinctStream_151) {
    auto stream = createStream(0, false, 0);
    stream->reset();
    auto copied = stream->copy();
    ASSERT_NE(copied, nullptr);
    copied->reset();
    // Both should read the same first character
    int ch1 = stream->getChar();
    int ch2 = copied->getChar();
    // Reset the original to position 0 first
    stream->reset();
    ch1 = stream->getChar();
    EXPECT_EQ(ch1, ch2);
}

// Test makeSubStream creates a valid sub-stream
TEST_F(FileStreamTest_151, MakeSubStreamCreatesValidStream_151) {
    auto stream = createStream(0, false, 0);
    stream->reset();
    Object dict;
    auto subStream = stream->makeSubStream(5, true, 10, std::move(dict));
    ASSERT_NE(subStream, nullptr);
    subStream->reset();
    int ch = subStream->getChar();
    EXPECT_EQ(ch, testContent[5]);
}

// Test makeSubStream respects length limit
TEST_F(FileStreamTest_151, MakeSubStreamRespectsLength_151) {
    auto stream = createStream(0, false, 0);
    stream->reset();
    Object dict;
    Goffset subLen = 3;
    auto subStream = stream->makeSubStream(0, true, subLen, std::move(dict));
    subStream->reset();
    int count = 0;
    while (subStream->getChar() != EOF) {
        count++;
    }
    EXPECT_EQ(count, subLen);
}

// Test getUnfilteredChar works same as getChar for base stream
TEST_F(FileStreamTest_151, GetUnfilteredCharReturnsChar_151) {
    auto stream = createStream(0, false, 0);
    stream->reset();
    int ch = stream->getUnfilteredChar();
    EXPECT_EQ(ch, 'H');
}

// Test unfilteredRewind works
TEST_F(FileStreamTest_151, UnfilteredRewindWorks_151) {
    auto stream = createStream(0, false, 0);
    stream->reset();
    stream->getChar();
    stream->getChar();
    bool result = stream->unfilteredRewind();
    // Should be able to rewind
    // After rewind, reading should give first char again
    int ch = stream->getUnfilteredChar();
    EXPECT_EQ(ch, 'H');
}

// Test getNeedsEncryptionOnSave default
TEST_F(FileStreamTest_151, GetNeedsEncryptionOnSaveDefault_151) {
    auto stream = createStream(0, false, 0);
    // Default should be false (typical initialization)
    EXPECT_FALSE(stream->getNeedsEncryptionOnSave());
}

// Test setNeedsEncryptionOnSave changes the value
TEST_F(FileStreamTest_151, SetNeedsEncryptionOnSave_151) {
    auto stream = createStream(0, false, 0);
    stream->setNeedsEncryptionOnSave(true);
    EXPECT_TRUE(stream->getNeedsEncryptionOnSave());
    stream->setNeedsEncryptionOnSave(false);
    EXPECT_FALSE(stream->getNeedsEncryptionOnSave());
}

// Test reading sequential characters matches test content
TEST_F(FileStreamTest_151, SequentialReadMatchesContent_151) {
    auto stream = createStream(0, false, 0);
    stream->reset();
    for (size_t i = 0; i < testContent.size(); i++) {
        int ch = stream->getChar();
        EXPECT_EQ(ch, static_cast<unsigned char>(testContent[i])) << "Mismatch at position " << i;
    }
}

// Test that reading past end returns EOF
TEST_F(FileStreamTest_151, ReadPastEndReturnsEOF_151) {
    auto stream = createStream(0, true, static_cast<Goffset>(testContent.size()));
    stream->reset();
    // Read all content
    for (size_t i = 0; i < testContent.size(); i++) {
        stream->getChar();
    }
    // Next read should be EOF
    int ch = stream->getChar();
    EXPECT_EQ(ch, EOF);
}

// Test close and then operations
TEST_F(FileStreamTest_151, CloseStream_151) {
    auto stream = createStream(0, false, 0);
    stream->reset();
    stream->getChar();
    stream->close();
    // After close, getPos behavior should still be defined
    // (implementation may vary, but shouldn't crash)
}

// Test getPos with start offset
TEST_F(FileStreamTest_151, GetPosWithStartOffset_151) {
    auto stream = createStream(10, false, 0);
    stream->reset();
    EXPECT_EQ(stream->getPos(), 10);
    stream->getChar();
    EXPECT_EQ(stream->getPos(), 11);
}

// Test reading across buffer boundary (buffer size is 16384)
TEST_F(FileStreamTest_151, ReadAcrossBufferBoundary_151) {
    // Create a larger temp file
    std::string largeTmpPath = std::tmpnam(nullptr);
    {
        std::ofstream ofs(largeTmpPath, std::ios::binary);
        std::string largeContent(20000, 'A');
        for (size_t i = 0; i < largeContent.size(); i++) {
            largeContent[i] = 'A' + (i % 26);
        }
        ofs.write(largeContent.c_str(), largeContent.size());
        ofs.close();

        auto largeFile = GooFile::open(largeTmpPath);
        ASSERT_NE(largeFile, nullptr);

        Object dict;
        FileStream largeStream(largeFile.get(), 0, false, 0, std::move(dict));
        largeStream.reset();

        // Read past the buffer size boundary
        for (int i = 0; i < 17000; i++) {
            int ch = largeStream.getChar();
            EXPECT_NE(ch, EOF) << "Unexpected EOF at position " << i;
            EXPECT_EQ(ch, 'A' + (i % 26)) << "Mismatch at position " << i;
        }
        EXPECT_EQ(largeStream.getPos(), 17000);
        largeStream.close();
    }
    std::remove(largeTmpPath.c_str());
}

// Test setPos to position 0
TEST_F(FileStreamTest_151, SetPosToZero_151) {
    auto stream = createStream(0, false, 0);
    stream->reset();
    stream->getChar();
    stream->getChar();
    stream->setPos(0, 0);
    int ch = stream->getChar();
    EXPECT_EQ(ch, 'H');
}

// Test multiple rewinds
TEST_F(FileStreamTest_151, MultipleRewinds_151) {
    auto stream = createStream(0, false, 0);
    stream->reset();
    
    for (int round = 0; round < 3; round++) {
        int ch = stream->getChar();
        EXPECT_EQ(ch, 'H') << "Failed on round " << round;
        stream->rewind();
        stream->reset();
    }
}
