#include <gtest/gtest.h>
#include <memory>
#include "Object.h"
#include "Stream.h"

class BaseMemStreamTest_167 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test rewind resets position to start
TEST_F(BaseMemStreamTest_167, RewindResetsToStart_167) {
    unsigned char data[] = {0x41, 0x42, 0x43, 0x44, 0x45};
    Goffset length = sizeof(data);
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, length, std::move(dict));

    // Read some characters to advance position
    stream->getChar();
    stream->getChar();
    EXPECT_EQ(stream->getPos(), 2);

    // Rewind should return true and reset position
    bool result = stream->rewind();
    EXPECT_TRUE(result);
    EXPECT_EQ(stream->getPos(), 0);
}

// Test rewind on fresh stream (already at start)
TEST_F(BaseMemStreamTest_167, RewindOnFreshStream_167) {
    unsigned char data[] = {0x01, 0x02, 0x03};
    Goffset length = sizeof(data);
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, length, std::move(dict));

    bool result = stream->rewind();
    EXPECT_TRUE(result);
    EXPECT_EQ(stream->getPos(), 0);
}

// Test getChar returns correct bytes in sequence
TEST_F(BaseMemStreamTest_167, GetCharReturnsCorrectBytes_167) {
    unsigned char data[] = {0x48, 0x65, 0x6C, 0x6C, 0x6F};
    Goffset length = sizeof(data);
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, length, std::move(dict));

    EXPECT_EQ(stream->getChar(), 0x48);
    EXPECT_EQ(stream->getChar(), 0x65);
    EXPECT_EQ(stream->getChar(), 0x6C);
    EXPECT_EQ(stream->getChar(), 0x6C);
    EXPECT_EQ(stream->getChar(), 0x6F);
}

// Test getChar returns EOF at end of stream
TEST_F(BaseMemStreamTest_167, GetCharReturnsEOFAtEnd_167) {
    unsigned char data[] = {0x41};
    Goffset length = sizeof(data);
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, length, std::move(dict));

    EXPECT_EQ(stream->getChar(), 0x41);
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test lookChar does not advance position
TEST_F(BaseMemStreamTest_167, LookCharDoesNotAdvance_167) {
    unsigned char data[] = {0x42, 0x43};
    Goffset length = sizeof(data);
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, length, std::move(dict));

    int ch = stream->lookChar();
    EXPECT_EQ(ch, 0x42);
    EXPECT_EQ(stream->getPos(), 0);

    // lookChar again should return same value
    ch = stream->lookChar();
    EXPECT_EQ(ch, 0x42);
    EXPECT_EQ(stream->getPos(), 0);
}

// Test getPos tracks position correctly
TEST_F(BaseMemStreamTest_167, GetPosTracksCorrectly_167) {
    unsigned char data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    Goffset length = sizeof(data);
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, length, std::move(dict));

    EXPECT_EQ(stream->getPos(), 0);
    stream->getChar();
    EXPECT_EQ(stream->getPos(), 1);
    stream->getChar();
    EXPECT_EQ(stream->getPos(), 2);
    stream->getChar();
    EXPECT_EQ(stream->getPos(), 3);
}

// Test setPos sets position from beginning
TEST_F(BaseMemStreamTest_167, SetPosFromBeginning_167) {
    unsigned char data[] = {0x10, 0x20, 0x30, 0x40, 0x50};
    Goffset length = sizeof(data);
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, length, std::move(dict));

    stream->setPos(3);
    EXPECT_EQ(stream->getPos(), 3);
    EXPECT_EQ(stream->getChar(), 0x40);
}

// Test setPos with dir = -1 (from end)
TEST_F(BaseMemStreamTest_167, SetPosFromEnd_167) {
    unsigned char data[] = {0x10, 0x20, 0x30, 0x40, 0x50};
    Goffset length = sizeof(data);
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, length, std::move(dict));

    stream->setPos(2, -1);
    // From end, position should be at length - 2 = 3
    EXPECT_EQ(stream->getChar(), 0x40);
}

// Test getStart returns the starting offset
TEST_F(BaseMemStreamTest_167, GetStartReturnsStartOffset_167) {
    unsigned char data[] = {0x01, 0x02, 0x03};
    Goffset length = sizeof(data);
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, length, std::move(dict));

    EXPECT_EQ(stream->getStart(), 0);
}

// Test getStart with non-zero start
TEST_F(BaseMemStreamTest_167, GetStartWithNonZeroStart_167) {
    unsigned char data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    Goffset length = 3;
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 2, length, std::move(dict));

    EXPECT_EQ(stream->getStart(), 2);
}

// Test moveStart adjusts the start position
TEST_F(BaseMemStreamTest_167, MoveStartAdjustsStart_167) {
    unsigned char data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    Goffset length = 5;
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, length, std::move(dict));

    EXPECT_EQ(stream->getStart(), 0);
    stream->moveStart(2);
    EXPECT_EQ(stream->getStart(), 2);
}

// Test rewind after reading full stream
TEST_F(BaseMemStreamTest_167, RewindAfterFullRead_167) {
    unsigned char data[] = {0xAA, 0xBB, 0xCC};
    Goffset length = sizeof(data);
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, length, std::move(dict));

    // Read all bytes
    stream->getChar();
    stream->getChar();
    stream->getChar();
    EXPECT_EQ(stream->getChar(), EOF);

    // Rewind and re-read
    EXPECT_TRUE(stream->rewind());
    EXPECT_EQ(stream->getPos(), 0);
    EXPECT_EQ(stream->getChar(), 0xAA);
    EXPECT_EQ(stream->getChar(), 0xBB);
    EXPECT_EQ(stream->getChar(), 0xCC);
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test getKind returns correct stream kind
TEST_F(BaseMemStreamTest_167, GetKindReturnsMemStream_167) {
    unsigned char data[] = {0x01};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, 1, std::move(dict));

    EXPECT_EQ(stream->getKind(), strWeird);
}

// Test empty stream
TEST_F(BaseMemStreamTest_167, EmptyStream_167) {
    unsigned char data[] = {0x00};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, 0, std::move(dict));

    EXPECT_EQ(stream->getChar(), EOF);
    EXPECT_TRUE(stream->rewind());
    EXPECT_EQ(stream->getPos(), 0);
}

// Test close method doesn't crash
TEST_F(BaseMemStreamTest_167, CloseDoesNotCrash_167) {
    unsigned char data[] = {0x01, 0x02};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, 2, std::move(dict));

    stream->close();
    // After close, rewind should still work
    EXPECT_TRUE(stream->rewind());
}

// Test getUnfilteredChar
TEST_F(BaseMemStreamTest_167, GetUnfilteredChar_167) {
    unsigned char data[] = {0x55, 0x66};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, 2, std::move(dict));

    int ch = stream->getUnfilteredChar();
    EXPECT_EQ(ch, 0x55);
}

// Test unfilteredRewind
TEST_F(BaseMemStreamTest_167, UnfilteredRewind_167) {
    unsigned char data[] = {0x77, 0x88};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, 2, std::move(dict));

    stream->getChar();
    bool result = stream->unfilteredRewind();
    EXPECT_TRUE(result);
    EXPECT_EQ(stream->getPos(), 0);
}

// Test copy creates a valid copy
TEST_F(BaseMemStreamTest_167, CopyCreatesValidStream_167) {
    unsigned char data[] = {0xDE, 0xAD, 0xBE, 0xEF};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, 4, std::move(dict));

    auto copyStream = stream->copy();
    ASSERT_NE(copyStream, nullptr);

    copyStream->rewind();
    EXPECT_EQ(copyStream->getChar(), 0xDE);
    EXPECT_EQ(copyStream->getChar(), 0xAD);
    EXPECT_EQ(copyStream->getChar(), 0xBE);
    EXPECT_EQ(copyStream->getChar(), 0xEF);
}

// Test makeSubStream
TEST_F(BaseMemStreamTest_167, MakeSubStream_167) {
    unsigned char data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, 5, std::move(dict));

    Object subDict;
    auto subStream = stream->makeSubStream(1, true, 3, std::move(subDict));
    ASSERT_NE(subStream, nullptr);

    subStream->rewind();
    EXPECT_EQ(subStream->getChar(), 0x02);
    EXPECT_EQ(subStream->getChar(), 0x03);
    EXPECT_EQ(subStream->getChar(), 0x04);
    EXPECT_EQ(subStream->getChar(), EOF);
}

// Test rewind with non-zero start offset
TEST_F(BaseMemStreamTest_167, RewindWithNonZeroStartOffset_167) {
    unsigned char data[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE};
    Object dict;
    // Stream starts at offset 2, length 3
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 2, 3, std::move(dict));

    stream->getChar(); // Read one char
    EXPECT_TRUE(stream->rewind());
    EXPECT_EQ(stream->getPos(), 2);
    EXPECT_EQ(stream->getChar(), 0xCC);
}

// Test multiple rewinds
TEST_F(BaseMemStreamTest_167, MultipleRewinds_167) {
    unsigned char data[] = {0x11, 0x22, 0x33};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, 3, std::move(dict));

    for (int i = 0; i < 5; i++) {
        EXPECT_TRUE(stream->rewind());
        EXPECT_EQ(stream->getPos(), 0);
        EXPECT_EQ(stream->getChar(), 0x11);
    }
}

// Test setPos to position 0
TEST_F(BaseMemStreamTest_167, SetPosToZero_167) {
    unsigned char data[] = {0xAB, 0xCD, 0xEF};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, 3, std::move(dict));

    stream->getChar();
    stream->getChar();
    stream->setPos(0);
    EXPECT_EQ(stream->getPos(), 0);
    EXPECT_EQ(stream->getChar(), 0xAB);
}

// Test single byte stream
TEST_F(BaseMemStreamTest_167, SingleByteStream_167) {
    unsigned char data[] = {0xFF};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char *>(data), 0, 1, std::move(dict));

    EXPECT_EQ(stream->lookChar(), 0xFF);
    EXPECT_EQ(stream->getChar(), 0xFF);
    EXPECT_EQ(stream->getChar(), EOF);
    EXPECT_TRUE(stream->rewind());
    EXPECT_EQ(stream->getChar(), 0xFF);
}
