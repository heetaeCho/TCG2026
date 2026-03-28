#include <gtest/gtest.h>
#include <memory>
#include "Object.h"
#include "Stream.h"

class BaseMemStreamTest_170 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getPos returns 0 for a newly created stream
TEST_F(BaseMemStreamTest_170, GetPosInitiallyZero_170) {
    unsigned char buf[] = { 'H', 'e', 'l', 'l', 'o' };
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buf), 0, 5, std::move(dict));
    stream->reset();
    EXPECT_EQ(stream->getPos(), 0);
}

// Test that getPos advances after reading characters
TEST_F(BaseMemStreamTest_170, GetPosAdvancesAfterGetChar_170) {
    unsigned char buf[] = { 'A', 'B', 'C', 'D', 'E' };
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buf), 0, 5, std::move(dict));
    stream->reset();
    stream->getChar();
    EXPECT_EQ(stream->getPos(), 1);
    stream->getChar();
    EXPECT_EQ(stream->getPos(), 2);
}

// Test that getPos returns correct value after reading all characters
TEST_F(BaseMemStreamTest_170, GetPosAtEnd_170) {
    unsigned char buf[] = { 'X', 'Y', 'Z' };
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buf), 0, 3, std::move(dict));
    stream->reset();
    stream->getChar();
    stream->getChar();
    stream->getChar();
    EXPECT_EQ(stream->getPos(), 3);
}

// Test getChar returns correct characters
TEST_F(BaseMemStreamTest_170, GetCharReturnsCorrectValues_170) {
    unsigned char buf[] = { 0x41, 0x42, 0x43 };
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buf), 0, 3, std::move(dict));
    stream->reset();
    EXPECT_EQ(stream->getChar(), 0x41);
    EXPECT_EQ(stream->getChar(), 0x42);
    EXPECT_EQ(stream->getChar(), 0x43);
}

// Test getChar returns EOF at end of stream
TEST_F(BaseMemStreamTest_170, GetCharReturnsEOFAtEnd_170) {
    unsigned char buf[] = { 'A' };
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buf), 0, 1, std::move(dict));
    stream->reset();
    stream->getChar();
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test lookChar does not advance position
TEST_F(BaseMemStreamTest_170, LookCharDoesNotAdvancePos_170) {
    unsigned char buf[] = { 'A', 'B', 'C' };
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buf), 0, 3, std::move(dict));
    stream->reset();
    int ch = stream->lookChar();
    EXPECT_EQ(ch, 'A');
    EXPECT_EQ(stream->getPos(), 0);
}

// Test lookChar returns same value as next getChar
TEST_F(BaseMemStreamTest_170, LookCharMatchesNextGetChar_170) {
    unsigned char buf[] = { 'H', 'i' };
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buf), 0, 2, std::move(dict));
    stream->reset();
    int looked = stream->lookChar();
    int got = stream->getChar();
    EXPECT_EQ(looked, got);
}

// Test rewind resets position to start
TEST_F(BaseMemStreamTest_170, RewindResetsPosition_170) {
    unsigned char buf[] = { 'A', 'B', 'C' };
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buf), 0, 3, std::move(dict));
    stream->reset();
    stream->getChar();
    stream->getChar();
    EXPECT_EQ(stream->getPos(), 2);
    bool result = stream->reset();
    EXPECT_EQ(stream->getPos(), 0);
}

// Test setPos sets position correctly
TEST_F(BaseMemStreamTest_170, SetPosSetsCorrectPosition_170) {
    unsigned char buf[] = { 'A', 'B', 'C', 'D', 'E' };
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buf), 0, 5, std::move(dict));
    stream->reset();
    stream->setPos(3);
    EXPECT_EQ(stream->getPos(), 3);
    EXPECT_EQ(stream->getChar(), 'D');
}

// Test setPos to 0
TEST_F(BaseMemStreamTest_170, SetPosToZero_170) {
    unsigned char buf[] = { 'A', 'B', 'C' };
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buf), 0, 3, std::move(dict));
    stream->reset();
    stream->getChar();
    stream->getChar();
    stream->setPos(0);
    EXPECT_EQ(stream->getPos(), 0);
    EXPECT_EQ(stream->getChar(), 'A');
}

// Test getKind returns streamMemStream
TEST_F(BaseMemStreamTest_170, GetKindReturnsMemStream_170) {
    unsigned char buf[] = { 'A' };
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buf), 0, 1, std::move(dict));
    EXPECT_EQ(stream->getKind(), strWeird);
}

// Test getStart returns starting position
TEST_F(BaseMemStreamTest_170, GetStartReturnsStart_170) {
    unsigned char buf[] = { 'A', 'B', 'C' };
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buf), 5, 3, std::move(dict));
    EXPECT_EQ(stream->getStart(), 5);
}

// Test moveStart changes start position
TEST_F(BaseMemStreamTest_170, MoveStartChangesStart_170) {
    unsigned char buf[] = { 'A', 'B', 'C', 'D', 'E' };
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buf), 0, 5, std::move(dict));
    Goffset originalStart = stream->getStart();
    stream->moveStart(2);
    EXPECT_EQ(stream->getStart(), originalStart + 2);
}

// Test empty stream - getChar returns EOF immediately
TEST_F(BaseMemStreamTest_170, EmptyStreamGetCharReturnsEOF_170) {
    unsigned char buf[] = { 0 };
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buf), 0, 0, std::move(dict));
    stream->reset();
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test empty stream - getPos is 0
TEST_F(BaseMemStreamTest_170, EmptyStreamGetPosIsZero_170) {
    unsigned char buf[] = { 0 };
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buf), 0, 0, std::move(dict));
    stream->reset();
    EXPECT_EQ(stream->getPos(), 0);
}

// Test lookChar on empty stream returns EOF
TEST_F(BaseMemStreamTest_170, EmptyStreamLookCharReturnsEOF_170) {
    unsigned char buf[] = { 0 };
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buf), 0, 0, std::move(dict));
    stream->reset();
    EXPECT_EQ(stream->lookChar(), EOF);
}

// Test setPos with dir parameter (from end)
TEST_F(BaseMemStreamTest_170, SetPosFromEnd_170) {
    unsigned char buf[] = { 'A', 'B', 'C', 'D', 'E' };
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buf), 0, 5, std::move(dict));
    stream->reset();
    stream->setPos(0, 1); // from end
    // After setPos from end with pos=0, should be at end
    EXPECT_EQ(stream->getPos(), 5);
}

// Test copy creates a valid copy
TEST_F(BaseMemStreamTest_170, CopyCreatesValidStream_170) {
    unsigned char buf[] = { 'A', 'B', 'C' };
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buf), 0, 3, std::move(dict));
    auto copied = stream->copy();
    ASSERT_NE(copied, nullptr);
    copied->reset();
    EXPECT_EQ(copied->getChar(), 'A');
    EXPECT_EQ(copied->getChar(), 'B');
    EXPECT_EQ(copied->getChar(), 'C');
}

// Test single byte stream
TEST_F(BaseMemStreamTest_170, SingleByteStream_170) {
    unsigned char buf[] = { 0xFF };
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buf), 0, 1, std::move(dict));
    stream->reset();
    EXPECT_EQ(stream->getPos(), 0);
    int ch = stream->getChar();
    EXPECT_EQ(ch, 0xFF);
    EXPECT_EQ(stream->getPos(), 1);
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test getUnfilteredChar
TEST_F(BaseMemStreamTest_170, GetUnfilteredChar_170) {
    unsigned char buf[] = { 'A', 'B', 'C' };
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buf), 0, 3, std::move(dict));
    stream->reset();
    int ch = stream->getUnfilteredChar();
    EXPECT_EQ(ch, 'A');
}

// Test unfilteredRewind
TEST_F(BaseMemStreamTest_170, UnfilteredRewind_170) {
    unsigned char buf[] = { 'A', 'B', 'C' };
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buf), 0, 3, std::move(dict));
    stream->reset();
    stream->getChar();
    stream->getChar();
    bool result = stream->unfilteredRewind();
    EXPECT_TRUE(result);
    EXPECT_EQ(stream->getPos(), 0);
}

// Test multiple reset calls
TEST_F(BaseMemStreamTest_170, MultipleResetCalls_170) {
    unsigned char buf[] = { 'A', 'B', 'C' };
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buf), 0, 3, std::move(dict));
    stream->reset();
    stream->getChar();
    stream->reset();
    EXPECT_EQ(stream->getPos(), 0);
    EXPECT_EQ(stream->getChar(), 'A');
    stream->reset();
    EXPECT_EQ(stream->getPos(), 0);
    EXPECT_EQ(stream->getChar(), 'A');
}

// Test close followed by reset
TEST_F(BaseMemStreamTest_170, CloseAndReset_170) {
    unsigned char buf[] = { 'A', 'B', 'C' };
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buf), 0, 3, std::move(dict));
    stream->reset();
    stream->getChar();
    stream->close();
    stream->reset();
    EXPECT_EQ(stream->getPos(), 0);
    EXPECT_EQ(stream->getChar(), 'A');
}

// Test sequential read of entire buffer
TEST_F(BaseMemStreamTest_170, SequentialReadEntireBuffer_170) {
    const int size = 256;
    unsigned char buf[size];
    for (int i = 0; i < size; i++) {
        buf[i] = static_cast<unsigned char>(i);
    }
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buf), 0, size, std::move(dict));
    stream->reset();
    for (int i = 0; i < size; i++) {
        EXPECT_EQ(stream->getChar(), i);
        EXPECT_EQ(stream->getPos(), i + 1);
    }
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test makeSubStream creates a valid sub-stream
TEST_F(BaseMemStreamTest_170, MakeSubStreamCreatesValidStream_170) {
    unsigned char buf[] = { 'A', 'B', 'C', 'D', 'E' };
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buf), 0, 5, std::move(dict));
    Object subDict;
    auto subStream = stream->makeSubStream(1, true, 3, std::move(subDict));
    ASSERT_NE(subStream, nullptr);
    subStream->reset();
    EXPECT_EQ(subStream->getChar(), 'B');
    EXPECT_EQ(subStream->getChar(), 'C');
    EXPECT_EQ(subStream->getChar(), 'D');
}

// Test setPos beyond buffer length
TEST_F(BaseMemStreamTest_170, SetPosBeyondLength_170) {
    unsigned char buf[] = { 'A', 'B', 'C' };
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buf), 0, 3, std::move(dict));
    stream->reset();
    stream->setPos(10);
    // After setting pos beyond length, getChar should return EOF
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test binary data with null bytes
TEST_F(BaseMemStreamTest_170, BinaryDataWithNullBytes_170) {
    unsigned char buf[] = { 0x00, 0x01, 0x00, 0x02 };
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(buf), 0, 4, std::move(dict));
    stream->reset();
    EXPECT_EQ(stream->getChar(), 0x00);
    EXPECT_EQ(stream->getChar(), 0x01);
    EXPECT_EQ(stream->getChar(), 0x00);
    EXPECT_EQ(stream->getChar(), 0x02);
    EXPECT_EQ(stream->getChar(), EOF);
}
