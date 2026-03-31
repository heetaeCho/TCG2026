#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"
#include "Object.h"
#include "goo/GooFile.h"

#include <memory>
#include <cstdio>
#include <string>

// Helper to create a temporary file for testing
class FileStreamTest_155 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a temporary file with some content
        tmpFilePath = std::tmpnam(nullptr);
        FILE *f = fopen(tmpFilePath.c_str(), "wb");
        if (f) {
            const char *data = "Hello, World! This is test data for FileStream unit tests.";
            fwrite(data, 1, strlen(data), f);
            fclose(f);
        }
        gooFile = GooFile::open(tmpFilePath);
    }

    void TearDown() override {
        gooFile = nullptr;
        std::remove(tmpFilePath.c_str());
    }

    std::string tmpFilePath;
    std::unique_ptr<GooFile> gooFile;

    std::unique_ptr<FileStream> createStream(Goffset start = 0, bool limited = false, Goffset length = 0) {
        Object dict;
        auto stream = std::make_unique<FileStream>(gooFile.get(), start, limited, length, std::move(dict));
        return stream;
    }
};

// Test that getNeedsEncryptionOnSave returns false by default
TEST_F(FileStreamTest_155, GetNeedsEncryptionOnSaveDefaultFalse_155) {
    auto stream = createStream();
    EXPECT_FALSE(stream->getNeedsEncryptionOnSave());
}

// Test that setNeedsEncryptionOnSave(true) is reflected by getNeedsEncryptionOnSave
TEST_F(FileStreamTest_155, SetNeedsEncryptionOnSaveTrue_155) {
    auto stream = createStream();
    stream->setNeedsEncryptionOnSave(true);
    EXPECT_TRUE(stream->getNeedsEncryptionOnSave());
}

// Test that setNeedsEncryptionOnSave(false) works after setting true
TEST_F(FileStreamTest_155, SetNeedsEncryptionOnSaveFalseAfterTrue_155) {
    auto stream = createStream();
    stream->setNeedsEncryptionOnSave(true);
    EXPECT_TRUE(stream->getNeedsEncryptionOnSave());
    stream->setNeedsEncryptionOnSave(false);
    EXPECT_FALSE(stream->getNeedsEncryptionOnSave());
}

// Test that setNeedsEncryptionOnSave(false) on default state remains false
TEST_F(FileStreamTest_155, SetNeedsEncryptionOnSaveFalseOnDefault_155) {
    auto stream = createStream();
    stream->setNeedsEncryptionOnSave(false);
    EXPECT_FALSE(stream->getNeedsEncryptionOnSave());
}

// Test getKind returns fileStream
TEST_F(FileStreamTest_155, GetKindReturnsFileStream_155) {
    auto stream = createStream();
    EXPECT_EQ(stream->getKind(), strFile);
}

// Test getStart returns the start offset
TEST_F(FileStreamTest_155, GetStartReturnsStartOffset_155) {
    auto stream = createStream(10, false, 0);
    EXPECT_EQ(stream->getStart(), 10);
}

// Test getStart with zero offset
TEST_F(FileStreamTest_155, GetStartReturnsZeroOffset_155) {
    auto stream = createStream(0, false, 0);
    EXPECT_EQ(stream->getStart(), 0);
}

// Test reading characters from stream
TEST_F(FileStreamTest_155, GetCharReadsFirstCharacter_155) {
    auto stream = createStream(0, true, 5);
    stream->reset();
    int ch = stream->getChar();
    EXPECT_EQ(ch, 'H');
}

// Test lookChar does not advance position
TEST_F(FileStreamTest_155, LookCharDoesNotAdvancePosition_155) {
    auto stream = createStream(0, true, 5);
    stream->reset();
    int ch1 = stream->lookChar();
    int ch2 = stream->lookChar();
    EXPECT_EQ(ch1, ch2);
    EXPECT_EQ(ch1, 'H');
}

// Test getPos after reading
TEST_F(FileStreamTest_155, GetPosAfterReading_155) {
    auto stream = createStream(0, true, 10);
    stream->reset();
    Goffset posBefore = stream->getPos();
    stream->getChar();
    Goffset posAfter = stream->getPos();
    EXPECT_EQ(posAfter, posBefore + 1);
}

// Test rewind resets position
TEST_F(FileStreamTest_155, RewindResetsPosition_155) {
    auto stream = createStream(0, true, 10);
    stream->reset();
    stream->getChar();
    stream->getChar();
    EXPECT_GT(stream->getPos(), 0);
    bool result = stream->rewind();
    EXPECT_TRUE(result);
    EXPECT_EQ(stream->getPos(), 0);
}

// Test reading with an offset start
TEST_F(FileStreamTest_155, ReadFromOffset_155) {
    // "Hello, World!..." - offset 7 should give 'W'
    auto stream = createStream(7, true, 5);
    stream->reset();
    int ch = stream->getChar();
    EXPECT_EQ(ch, 'W');
}

// Test EOF when limited stream is exhausted
TEST_F(FileStreamTest_155, ReturnsEOFWhenExhausted_155) {
    auto stream = createStream(0, true, 2);
    stream->reset();
    stream->getChar(); // 'H'
    stream->getChar(); // 'e'
    int ch = stream->getChar(); // should be EOF
    EXPECT_EQ(ch, EOF);
}

// Test moveStart adjusts the start
TEST_F(FileStreamTest_155, MoveStartAdjustsStart_155) {
    auto stream = createStream(0, true, 20);
    stream->reset();
    Goffset originalStart = stream->getStart();
    stream->moveStart(5);
    EXPECT_EQ(stream->getStart(), originalStart + 5);
}

// Test copy creates a valid copy
TEST_F(FileStreamTest_155, CopyCreatesValidStream_155) {
    auto stream = createStream(0, true, 10);
    stream->reset();
    auto copied = stream->copy();
    ASSERT_NE(copied, nullptr);
    copied->reset();
    int ch = copied->getChar();
    EXPECT_EQ(ch, 'H');
}

// Test makeSubStream creates a sub stream
TEST_F(FileStreamTest_155, MakeSubStreamCreatesSubStream_155) {
    auto stream = createStream(0, false, 0);
    stream->reset();
    Object dict;
    auto sub = stream->makeSubStream(5, true, 5, std::move(dict));
    ASSERT_NE(sub, nullptr);
    sub->reset();
    int ch = sub->getChar();
    EXPECT_EQ(ch, ','); // "Hello," - index 5 is ','
}

// Test unfilteredRewind
TEST_F(FileStreamTest_155, UnfilteredRewind_155) {
    auto stream = createStream(0, true, 10);
    stream->reset();
    stream->getChar();
    stream->getChar();
    bool result = stream->unfilteredRewind();
    EXPECT_TRUE(result);
}

// Test getUnfilteredChar reads character
TEST_F(FileStreamTest_155, GetUnfilteredChar_155) {
    auto stream = createStream(0, true, 10);
    stream->reset();
    int ch = stream->getUnfilteredChar();
    EXPECT_EQ(ch, 'H');
}

// Test setPos with absolute position
TEST_F(FileStreamTest_155, SetPosAbsolute_155) {
    auto stream = createStream(0, true, 20);
    stream->reset();
    stream->setPos(3, 0); // set to absolute position 3
    int ch = stream->getChar();
    EXPECT_EQ(ch, 'l'); // "Hello" -> index 3 is 'l'
}

// Test close does not crash
TEST_F(FileStreamTest_155, CloseDoesNotCrash_155) {
    auto stream = createStream(0, true, 10);
    stream->reset();
    stream->close();
    // No crash expected
    SUCCEED();
}

// Test multiple toggle of needsEncryptionOnSave
TEST_F(FileStreamTest_155, MultipleToggleEncryptionOnSave_155) {
    auto stream = createStream();
    for (int i = 0; i < 10; ++i) {
        stream->setNeedsEncryptionOnSave(true);
        EXPECT_TRUE(stream->getNeedsEncryptionOnSave());
        stream->setNeedsEncryptionOnSave(false);
        EXPECT_FALSE(stream->getNeedsEncryptionOnSave());
    }
}

// Test reading entire limited stream
TEST_F(FileStreamTest_155, ReadEntireLimitedStream_155) {
    auto stream = createStream(0, true, 5);
    stream->reset();
    std::string result;
    int ch;
    while ((ch = stream->getChar()) != EOF) {
        result += static_cast<char>(ch);
    }
    EXPECT_EQ(result, "Hello");
}
