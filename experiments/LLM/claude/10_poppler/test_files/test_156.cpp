#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "Stream.h"
#include "Object.h"

// We need to create a minimal test fixture that can construct FileStream objects.
// FileStream requires a GooFile*, so we need to work with actual files or mock them.

#include <cstdio>
#include <cstring>
#include <fstream>

#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

#include "goo/GooFile.h"

class FileStreamTest_156 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a temporary file with known content
        tmpFilePath = std::tmpnam(nullptr);
        std::ofstream ofs(tmpFilePath, std::ios::binary);
        testData = "Hello, World! This is a test file for FileStream unit testing. "
                   "It contains enough data to test various stream operations including "
                   "reading characters, seeking positions, and boundary conditions.";
        ofs.write(testData.c_str(), testData.size());
        ofs.close();

        gooFile = GooFile::open(tmpFilePath);
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
    std::string testData;
    std::unique_ptr<GooFile> gooFile;
};

// Test: setNeedsEncryptionOnSave and getNeedsEncryptionOnSave
TEST_F(FileStreamTest_156, SetNeedsEncryptionOnSaveTrue_156) {
    auto stream = createStream();
    stream->setNeedsEncryptionOnSave(true);
    EXPECT_TRUE(stream->getNeedsEncryptionOnSave());
}

TEST_F(FileStreamTest_156, SetNeedsEncryptionOnSaveFalse_156) {
    auto stream = createStream();
    stream->setNeedsEncryptionOnSave(false);
    EXPECT_FALSE(stream->getNeedsEncryptionOnSave());
}

TEST_F(FileStreamTest_156, SetNeedsEncryptionOnSaveToggle_156) {
    auto stream = createStream();
    stream->setNeedsEncryptionOnSave(true);
    EXPECT_TRUE(stream->getNeedsEncryptionOnSave());
    stream->setNeedsEncryptionOnSave(false);
    EXPECT_FALSE(stream->getNeedsEncryptionOnSave());
    stream->setNeedsEncryptionOnSave(true);
    EXPECT_TRUE(stream->getNeedsEncryptionOnSave());
}

// Test: getKind returns strFile
TEST_F(FileStreamTest_156, GetKindReturnsFileStream_156) {
    auto stream = createStream();
    EXPECT_EQ(stream->getKind(), strFile);
}

// Test: getStart returns the start offset
TEST_F(FileStreamTest_156, GetStartReturnsCorrectOffset_156) {
    auto stream = createStream(0, false, 0);
    EXPECT_EQ(stream->getStart(), 0);
}

TEST_F(FileStreamTest_156, GetStartWithOffset_156) {
    auto stream = createStream(10, false, 0);
    EXPECT_EQ(stream->getStart(), 10);
}

// Test: getChar reads first character correctly
TEST_F(FileStreamTest_156, GetCharReadsFirstChar_156) {
    auto stream = createStream(0, true, testData.size());
    stream->rewind();
    int ch = stream->getChar();
    EXPECT_EQ(ch, 'H');
}

// Test: getChar reads sequential characters
TEST_F(FileStreamTest_156, GetCharReadsSequentialChars_156) {
    auto stream = createStream(0, true, testData.size());
    stream->rewind();
    for (size_t i = 0; i < 5; i++) {
        int ch = stream->getChar();
        EXPECT_EQ(ch, static_cast<int>(testData[i]));
    }
}

// Test: lookChar does not advance position
TEST_F(FileStreamTest_156, LookCharDoesNotAdvance_156) {
    auto stream = createStream(0, true, testData.size());
    stream->rewind();
    int ch1 = stream->lookChar();
    int ch2 = stream->lookChar();
    EXPECT_EQ(ch1, ch2);
    EXPECT_EQ(ch1, 'H');
}

// Test: getPos after rewind
TEST_F(FileStreamTest_156, GetPosAfterRewind_156) {
    auto stream = createStream(0, true, testData.size());
    stream->rewind();
    EXPECT_EQ(stream->getPos(), 0);
}

// Test: getPos advances after getChar
TEST_F(FileStreamTest_156, GetPosAdvancesAfterGetChar_156) {
    auto stream = createStream(0, true, testData.size());
    stream->rewind();
    stream->getChar();
    EXPECT_EQ(stream->getPos(), 1);
    stream->getChar();
    EXPECT_EQ(stream->getPos(), 2);
}

// Test: rewind returns to beginning
TEST_F(FileStreamTest_156, RewindReturnsToBegining_156) {
    auto stream = createStream(0, true, testData.size());
    stream->rewind();
    stream->getChar();
    stream->getChar();
    stream->getChar();
    EXPECT_EQ(stream->getPos(), 3);
    stream->rewind();
    EXPECT_EQ(stream->getPos(), 0);
    int ch = stream->getChar();
    EXPECT_EQ(ch, 'H');
}

// Test: setPos with absolute position
TEST_F(FileStreamTest_156, SetPosAbsolute_156) {
    auto stream = createStream(0, true, testData.size());
    stream->rewind();
    stream->setPos(5, 0);
    int ch = stream->getChar();
    EXPECT_EQ(ch, static_cast<int>(testData[5]));
}

// Test: reading with offset start
TEST_F(FileStreamTest_156, ReadWithOffset_156) {
    auto stream = createStream(7, true, testData.size() - 7);
    stream->rewind();
    int ch = stream->getChar();
    EXPECT_EQ(ch, static_cast<int>(testData[7]));
}

// Test: getChar returns EOF when limited stream is exhausted
TEST_F(FileStreamTest_156, GetCharReturnsEOFWhenExhausted_156) {
    auto stream = createStream(0, true, 3);
    stream->rewind();
    stream->getChar(); // 'H'
    stream->getChar(); // 'e'
    stream->getChar(); // 'l'
    int ch = stream->getChar();
    EXPECT_EQ(ch, EOF);
}

// Test: lookChar returns EOF when stream is exhausted
TEST_F(FileStreamTest_156, LookCharReturnsEOFWhenExhausted_156) {
    auto stream = createStream(0, true, 1);
    stream->rewind();
    stream->getChar(); // consume the only char
    int ch = stream->lookChar();
    EXPECT_EQ(ch, EOF);
}

// Test: copy creates a valid copy
TEST_F(FileStreamTest_156, CopyClonesStream_156) {
    auto stream = createStream(0, true, testData.size());
    stream->setNeedsEncryptionOnSave(true);
    auto copied = stream->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getKind(), strFile);
}

// Test: makeSubStream creates a valid substream
TEST_F(FileStreamTest_156, MakeSubStreamCreatesValidStream_156) {
    auto stream = createStream(0, true, testData.size());
    stream->rewind();
    Object dict;
    auto subStream = stream->makeSubStream(5, true, 10, std::move(dict));
    ASSERT_NE(subStream, nullptr);
    subStream->rewind();
    int ch = subStream->getChar();
    EXPECT_EQ(ch, static_cast<int>(testData[5]));
}

// Test: moveStart changes the start position
TEST_F(FileStreamTest_156, MoveStartChangesStart_156) {
    auto stream = createStream(0, true, testData.size());
    stream->rewind();
    stream->moveStart(5);
    EXPECT_EQ(stream->getStart(), 5);
}

// Test: unfilteredRewind works
TEST_F(FileStreamTest_156, UnfilteredRewindWorks_156) {
    auto stream = createStream(0, true, testData.size());
    stream->rewind();
    stream->getChar();
    stream->getChar();
    bool result = stream->unfilteredRewind();
    EXPECT_TRUE(result);
}

// Test: getUnfilteredChar reads like getChar
TEST_F(FileStreamTest_156, GetUnfilteredCharReadsChar_156) {
    auto stream = createStream(0, true, testData.size());
    stream->rewind();
    int ch = stream->getUnfilteredChar();
    EXPECT_EQ(ch, 'H');
}

// Test: limited stream with zero length returns EOF immediately
TEST_F(FileStreamTest_156, ZeroLengthStreamReturnsEOF_156) {
    auto stream = createStream(0, true, 0);
    stream->rewind();
    int ch = stream->getChar();
    EXPECT_EQ(ch, EOF);
}

// Test: setPos from end of file (dir != 0)
TEST_F(FileStreamTest_156, SetPosFromEnd_156) {
    auto stream = createStream(0, false, 0);
    stream->rewind();
    // Set position from the end: negative offset from end
    stream->setPos(-1, 1);
    int ch = stream->getChar();
    // Should be the last character of testData
    EXPECT_EQ(ch, static_cast<int>(testData[testData.size() - 1]));
}

// Test: close and then rewind
TEST_F(FileStreamTest_156, CloseAndRewind_156) {
    auto stream = createStream(0, true, testData.size());
    stream->rewind();
    stream->getChar();
    stream->close();
    // After close and rewind, should be able to read again
    stream->rewind();
    int ch = stream->getChar();
    EXPECT_EQ(ch, 'H');
}

// Test: reading entire limited stream
TEST_F(FileStreamTest_156, ReadEntireLimitedStream_156) {
    Goffset len = 20;
    auto stream = createStream(0, true, len);
    stream->rewind();
    std::string result;
    for (Goffset i = 0; i < len; i++) {
        int ch = stream->getChar();
        ASSERT_NE(ch, EOF);
        result += static_cast<char>(ch);
    }
    EXPECT_EQ(result, testData.substr(0, len));
    // Next char should be EOF
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test: default needsEncryptionOnSave value
TEST_F(FileStreamTest_156, DefaultNeedsEncryptionOnSave_156) {
    auto stream = createStream();
    // By default, needsEncryptionOnSave should be false
    EXPECT_FALSE(stream->getNeedsEncryptionOnSave());
}
