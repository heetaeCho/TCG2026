#include <gtest/gtest.h>
#include <memory>
#include "Object.h"
#include "Stream.h"

class BaseMemStreamTest_175 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a simple buffer for testing
        for (int i = 0; i < 256; i++) {
            testBuf[i] = static_cast<unsigned char>(i);
        }
    }

    unsigned char testBuf[256];
};

TEST_F(BaseMemStreamTest_175, ConstructionAndGetKind_175) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(testBuf), 0, 256, std::move(dict));
    EXPECT_EQ(stream->getKind(), strWeird);
}

TEST_F(BaseMemStreamTest_175, RewindReturnsTrue_175) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(testBuf), 0, 256, std::move(dict));
    EXPECT_TRUE(stream->rewind());
}

TEST_F(BaseMemStreamTest_175, UnfilteredRewindCallsRewind_175) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(testBuf), 0, 256, std::move(dict));
    EXPECT_TRUE(stream->unfilteredRewind());
}

TEST_F(BaseMemStreamTest_175, GetCharReadsSequentially_175) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(testBuf), 0, 256, std::move(dict));
    stream->rewind();
    EXPECT_EQ(stream->getChar(), 0);
    EXPECT_EQ(stream->getChar(), 1);
    EXPECT_EQ(stream->getChar(), 2);
}

TEST_F(BaseMemStreamTest_175, LookCharDoesNotAdvance_175) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(testBuf), 0, 256, std::move(dict));
    stream->rewind();
    int ch1 = stream->lookChar();
    int ch2 = stream->lookChar();
    EXPECT_EQ(ch1, ch2);
    EXPECT_EQ(ch1, 0);
}

TEST_F(BaseMemStreamTest_175, GetPosInitiallyZero_175) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(testBuf), 0, 256, std::move(dict));
    stream->rewind();
    EXPECT_EQ(stream->getPos(), 0);
}

TEST_F(BaseMemStreamTest_175, GetPosAdvancesAfterGetChar_175) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(testBuf), 0, 256, std::move(dict));
    stream->rewind();
    stream->getChar();
    EXPECT_EQ(stream->getPos(), 1);
    stream->getChar();
    EXPECT_EQ(stream->getPos(), 2);
}

TEST_F(BaseMemStreamTest_175, SetPosFromStart_175) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(testBuf), 0, 256, std::move(dict));
    stream->rewind();
    stream->setPos(10);
    EXPECT_EQ(stream->getPos(), 10);
    EXPECT_EQ(stream->getChar(), 10);
}

TEST_F(BaseMemStreamTest_175, GetStartReturnsZeroForZeroStart_175) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(testBuf), 0, 256, std::move(dict));
    EXPECT_EQ(stream->getStart(), 0);
}

TEST_F(BaseMemStreamTest_175, GetStartReturnsNonZeroStart_175) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(testBuf), 10, 100, std::move(dict));
    EXPECT_EQ(stream->getStart(), 10);
}

TEST_F(BaseMemStreamTest_175, MoveStartShiftsStart_175) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(testBuf), 0, 256, std::move(dict));
    stream->moveStart(5);
    EXPECT_EQ(stream->getStart(), 5);
}

TEST_F(BaseMemStreamTest_175, GetCharReturnsEOFAtEnd_175) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(testBuf), 0, 3, std::move(dict));
    stream->rewind();
    EXPECT_EQ(stream->getChar(), 0);
    EXPECT_EQ(stream->getChar(), 1);
    EXPECT_EQ(stream->getChar(), 2);
    EXPECT_EQ(stream->getChar(), EOF);
}

TEST_F(BaseMemStreamTest_175, LookCharReturnsEOFAtEnd_175) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(testBuf), 0, 1, std::move(dict));
    stream->rewind();
    stream->getChar(); // consume the only byte
    EXPECT_EQ(stream->lookChar(), EOF);
}

TEST_F(BaseMemStreamTest_175, RewindResetsPosition_175) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(testBuf), 0, 256, std::move(dict));
    stream->rewind();
    stream->getChar();
    stream->getChar();
    stream->getChar();
    stream->rewind();
    EXPECT_EQ(stream->getPos(), 0);
    EXPECT_EQ(stream->getChar(), 0);
}

TEST_F(BaseMemStreamTest_175, CopyCreatesValidCopy_175) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(testBuf), 0, 256, std::move(dict));
    auto copy = stream->copy();
    ASSERT_NE(copy, nullptr);
    copy->rewind();
    EXPECT_EQ(copy->getChar(), 0);
    EXPECT_EQ(copy->getChar(), 1);
}

TEST_F(BaseMemStreamTest_175, MakeSubStreamCreatesSubStream_175) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(testBuf), 0, 256, std::move(dict));
    Object subDict;
    auto subStream = stream->makeSubStream(5, true, 10, std::move(subDict));
    ASSERT_NE(subStream, nullptr);
    subStream->rewind();
    EXPECT_EQ(subStream->getChar(), 5);
    EXPECT_EQ(subStream->getChar(), 6);
}

TEST_F(BaseMemStreamTest_175, CloseDoesNotCrash_175) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(testBuf), 0, 256, std::move(dict));
    EXPECT_NO_FATAL_FAILURE(stream->close());
}

TEST_F(BaseMemStreamTest_175, GetUnfilteredChar_175) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(testBuf), 0, 256, std::move(dict));
    stream->rewind();
    int ch = stream->getUnfilteredChar();
    EXPECT_EQ(ch, 0);
}

TEST_F(BaseMemStreamTest_175, ZeroLengthStream_175) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(testBuf), 0, 0, std::move(dict));
    stream->rewind();
    EXPECT_EQ(stream->getChar(), EOF);
    EXPECT_EQ(stream->lookChar(), EOF);
}

TEST_F(BaseMemStreamTest_175, SingleByteStream_175) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(testBuf), 0, 1, std::move(dict));
    stream->rewind();
    EXPECT_EQ(stream->lookChar(), 0);
    EXPECT_EQ(stream->getChar(), 0);
    EXPECT_EQ(stream->getChar(), EOF);
}

TEST_F(BaseMemStreamTest_175, SetPosFromEnd_175) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(testBuf), 0, 256, std::move(dict));
    stream->rewind();
    // dir = -1 means from end
    stream->setPos(0, -1);
    // After setting pos from end with offset 0, we should be at the end
    EXPECT_EQ(stream->getChar(), EOF);
}

TEST_F(BaseMemStreamTest_175, SetPosFromEndWithOffset_175) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(testBuf), 0, 256, std::move(dict));
    stream->rewind();
    // Setting pos from end with some offset
    stream->setPos(5, -1);
    int ch = stream->getChar();
    // Should read near the end of stream
    EXPECT_EQ(ch, 251);
}

TEST_F(BaseMemStreamTest_175, SetPosBeyondEnd_175) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(testBuf), 0, 10, std::move(dict));
    stream->rewind();
    stream->setPos(100);
    // Reading past end should return EOF
    EXPECT_EQ(stream->getChar(), EOF);
}

TEST_F(BaseMemStreamTest_175, MultipleRewinds_175) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(testBuf), 0, 256, std::move(dict));
    for (int i = 0; i < 5; i++) {
        stream->rewind();
        EXPECT_EQ(stream->getChar(), 0);
    }
}

TEST_F(BaseMemStreamTest_175, ReadEntireStream_175) {
    Object dict;
    const int len = 50;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(testBuf), 0, len, std::move(dict));
    stream->rewind();
    for (int i = 0; i < len; i++) {
        int ch = stream->getChar();
        EXPECT_EQ(ch, i);
    }
    EXPECT_EQ(stream->getChar(), EOF);
}

TEST_F(BaseMemStreamTest_175, NonZeroStartOffset_175) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(testBuf), 5, 10, std::move(dict));
    stream->rewind();
    // The first char should be at offset 5 in the buffer
    EXPECT_EQ(stream->getChar(), 5);
    EXPECT_EQ(stream->getChar(), 6);
}

TEST_F(BaseMemStreamTest_175, MoveStartAndRewind_175) {
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(testBuf), 0, 256, std::move(dict));
    stream->moveStart(10);
    stream->rewind();
    EXPECT_EQ(stream->getChar(), 10);
}
