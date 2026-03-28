#include <gtest/gtest.h>
#include <climits>
#include "Stream.h"
#include "Object.h"

class BaseMemStreamTest_168 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test getChar returns correct first byte from buffer
TEST_F(BaseMemStreamTest_168, GetCharReturnsFirstByte_168) {
    unsigned char data[] = {0x41, 0x42, 0x43}; // 'A', 'B', 'C'
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char*>(data), 0, 3, std::move(dict));
    stream->reset();
    
    int ch = stream->getChar();
    EXPECT_EQ(ch, 0x41);
}

// Test getChar reads sequential bytes correctly
TEST_F(BaseMemStreamTest_168, GetCharReadsSequentialBytes_168) {
    unsigned char data[] = {0x41, 0x42, 0x43};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char*>(data), 0, 3, std::move(dict));
    stream->reset();
    
    EXPECT_EQ(stream->getChar(), 0x41);
    EXPECT_EQ(stream->getChar(), 0x42);
    EXPECT_EQ(stream->getChar(), 0x43);
}

// Test getChar returns EOF when buffer is exhausted
TEST_F(BaseMemStreamTest_168, GetCharReturnsEOFAtEnd_168) {
    unsigned char data[] = {0x41};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char*>(data), 0, 1, std::move(dict));
    stream->reset();
    
    EXPECT_EQ(stream->getChar(), 0x41);
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test getChar returns EOF for empty stream
TEST_F(BaseMemStreamTest_168, GetCharReturnsEOFForEmptyStream_168) {
    unsigned char data[] = {0x00};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char*>(data), 0, 0, std::move(dict));
    stream->reset();
    
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test getChar masks byte to 0xff (high bit set byte)
TEST_F(BaseMemStreamTest_168, GetCharMasksByteTo0xFF_168) {
    unsigned char data[] = {0xFF, 0x80, 0xFE};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char*>(data), 0, 3, std::move(dict));
    stream->reset();
    
    EXPECT_EQ(stream->getChar(), 0xFF);
    EXPECT_EQ(stream->getChar(), 0x80);
    EXPECT_EQ(stream->getChar(), 0xFE);
}

// Test getChar returns EOF multiple times after exhaustion
TEST_F(BaseMemStreamTest_168, GetCharReturnsEOFRepeatedly_168) {
    unsigned char data[] = {0x41};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char*>(data), 0, 1, std::move(dict));
    stream->reset();
    
    stream->getChar(); // consume the only byte
    EXPECT_EQ(stream->getChar(), EOF);
    EXPECT_EQ(stream->getChar(), EOF);
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test lookChar returns byte without advancing
TEST_F(BaseMemStreamTest_168, LookCharDoesNotAdvance_168) {
    unsigned char data[] = {0x41, 0x42};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char*>(data), 0, 2, std::move(dict));
    stream->reset();
    
    int ch1 = stream->lookChar();
    int ch2 = stream->lookChar();
    EXPECT_EQ(ch1, 0x41);
    EXPECT_EQ(ch2, 0x41);
}

// Test getPos after reading
TEST_F(BaseMemStreamTest_168, GetPosAfterReading_168) {
    unsigned char data[] = {0x41, 0x42, 0x43, 0x44};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char*>(data), 0, 4, std::move(dict));
    stream->reset();
    
    EXPECT_EQ(stream->getPos(), 0);
    stream->getChar();
    EXPECT_EQ(stream->getPos(), 1);
    stream->getChar();
    EXPECT_EQ(stream->getPos(), 2);
}

// Test rewind resets position
TEST_F(BaseMemStreamTest_168, RewindResetsPosition_168) {
    unsigned char data[] = {0x41, 0x42, 0x43};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char*>(data), 0, 3, std::move(dict));
    stream->reset();
    
    stream->getChar();
    stream->getChar();
    
    bool result = stream->rewind();
    EXPECT_TRUE(result);
    EXPECT_EQ(stream->getChar(), 0x41);
}

// Test setPos sets to specific position
TEST_F(BaseMemStreamTest_168, SetPosSetsToSpecificPosition_168) {
    unsigned char data[] = {0x41, 0x42, 0x43, 0x44, 0x45};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char*>(data), 0, 5, std::move(dict));
    stream->reset();
    
    stream->setPos(2);
    EXPECT_EQ(stream->getChar(), 0x43);
}

// Test getStart returns start offset
TEST_F(BaseMemStreamTest_168, GetStartReturnsStartOffset_168) {
    unsigned char data[] = {0x41, 0x42, 0x43};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char*>(data), 10, 3, std::move(dict));
    stream->reset();
    
    EXPECT_EQ(stream->getStart(), 10);
}

// Test getKind returns correct stream kind
TEST_F(BaseMemStreamTest_168, GetKindReturnsMemStream_168) {
    unsigned char data[] = {0x41};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char*>(data), 0, 1, std::move(dict));
    
    EXPECT_EQ(stream->getKind(), strWeird);
}

// Test moveStart adjusts start position
TEST_F(BaseMemStreamTest_168, MoveStartAdjustsStart_168) {
    unsigned char data[] = {0x41, 0x42, 0x43, 0x44, 0x45};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char*>(data), 0, 5, std::move(dict));
    stream->reset();
    
    stream->moveStart(2);
    EXPECT_EQ(stream->getStart(), 2);
}

// Test getChar with zero byte value
TEST_F(BaseMemStreamTest_168, GetCharWithZeroByte_168) {
    unsigned char data[] = {0x00, 0x01, 0x00};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char*>(data), 0, 3, std::move(dict));
    stream->reset();
    
    EXPECT_EQ(stream->getChar(), 0x00);
    EXPECT_EQ(stream->getChar(), 0x01);
    EXPECT_EQ(stream->getChar(), 0x00);
}

// Test getChar after setPos to end of buffer
TEST_F(BaseMemStreamTest_168, GetCharAfterSetPosToEnd_168) {
    unsigned char data[] = {0x41, 0x42, 0x43};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char*>(data), 0, 3, std::move(dict));
    stream->reset();
    
    stream->setPos(3);
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test getUnfilteredChar behaves like getChar
TEST_F(BaseMemStreamTest_168, GetUnfilteredCharReturnsCorrectByte_168) {
    unsigned char data[] = {0x41, 0x42};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char*>(data), 0, 2, std::move(dict));
    stream->reset();
    
    int ch = stream->getUnfilteredChar();
    EXPECT_EQ(ch, 0x41);
}

// Test unfilteredRewind
TEST_F(BaseMemStreamTest_168, UnfilteredRewindWorks_168) {
    unsigned char data[] = {0x41, 0x42, 0x43};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char*>(data), 0, 3, std::move(dict));
    stream->reset();
    
    stream->getChar();
    stream->getChar();
    
    bool result = stream->unfilteredRewind();
    EXPECT_TRUE(result);
    EXPECT_EQ(stream->getChar(), 0x41);
}

// Test copy creates independent stream
TEST_F(BaseMemStreamTest_168, CopyCreatesIndependentStream_168) {
    unsigned char data[] = {0x41, 0x42, 0x43};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char*>(data), 0, 3, std::move(dict));
    stream->reset();
    
    auto copied = stream->copy();
    ASSERT_NE(copied, nullptr);
    copied->reset();
    
    EXPECT_EQ(copied->getChar(), 0x41);
}

// Test makeSubStream creates sub-range stream
TEST_F(BaseMemStreamTest_168, MakeSubStreamCreatesSubRange_168) {
    unsigned char data[] = {0x41, 0x42, 0x43, 0x44, 0x45};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char*>(data), 0, 5, std::move(dict));
    stream->reset();
    
    Object subDict;
    auto subStream = stream->makeSubStream(1, true, 3, std::move(subDict));
    ASSERT_NE(subStream, nullptr);
    subStream->reset();
    
    EXPECT_EQ(subStream->getChar(), 0x42);
    EXPECT_EQ(subStream->getChar(), 0x43);
    EXPECT_EQ(subStream->getChar(), 0x44);
    EXPECT_EQ(subStream->getChar(), EOF);
}

// Test reading all 256 possible byte values
TEST_F(BaseMemStreamTest_168, GetCharAllByteValues_168) {
    unsigned char data[256];
    for (int i = 0; i < 256; i++) {
        data[i] = static_cast<unsigned char>(i);
    }
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char*>(data), 0, 256, std::move(dict));
    stream->reset();
    
    for (int i = 0; i < 256; i++) {
        int ch = stream->getChar();
        EXPECT_EQ(ch, i) << "Failed at byte index " << i;
    }
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test close and re-reset
TEST_F(BaseMemStreamTest_168, CloseAndReset_168) {
    unsigned char data[] = {0x41, 0x42, 0x43};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char*>(data), 0, 3, std::move(dict));
    stream->reset();
    
    stream->getChar();
    stream->close();
    stream->reset();
    
    EXPECT_EQ(stream->getChar(), 0x41);
}

// Test setPos with dir parameter (from end)
TEST_F(BaseMemStreamTest_168, SetPosFromEnd_168) {
    unsigned char data[] = {0x41, 0x42, 0x43, 0x44, 0x45};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char*>(data), 0, 5, std::move(dict));
    stream->reset();
    
    // dir != 0 typically means from end
    stream->setPos(1, -1);
    // After setting from end, we should be near the end
    // The exact behavior depends on implementation, but we verify no crash
    int ch = stream->getChar();
    // ch should be a valid byte or EOF
    EXPECT_TRUE(ch == EOF || (ch >= 0 && ch <= 0xFF));
}

// Test single byte stream
TEST_F(BaseMemStreamTest_168, SingleByteStream_168) {
    unsigned char data[] = {0xAB};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char*>(data), 0, 1, std::move(dict));
    stream->reset();
    
    EXPECT_EQ(stream->getPos(), 0);
    EXPECT_EQ(stream->getChar(), 0xAB);
    EXPECT_EQ(stream->getPos(), 1);
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test lookChar on empty stream returns EOF
TEST_F(BaseMemStreamTest_168, LookCharOnEmptyStreamReturnsEOF_168) {
    unsigned char data[] = {0x00};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char*>(data), 0, 0, std::move(dict));
    stream->reset();
    
    EXPECT_EQ(stream->lookChar(), EOF);
}

// Test interleaving getChar and lookChar
TEST_F(BaseMemStreamTest_168, InterleavedGetCharAndLookChar_168) {
    unsigned char data[] = {0x41, 0x42, 0x43};
    Object dict;
    auto stream = std::make_unique<MemStream>(reinterpret_cast<char*>(data), 0, 3, std::move(dict));
    stream->reset();
    
    EXPECT_EQ(stream->lookChar(), 0x41); // peek, no advance
    EXPECT_EQ(stream->getChar(), 0x41);  // consume
    EXPECT_EQ(stream->lookChar(), 0x42); // peek next
    EXPECT_EQ(stream->lookChar(), 0x42); // peek again, same
    EXPECT_EQ(stream->getChar(), 0x42);  // consume
    EXPECT_EQ(stream->getChar(), 0x43);  // consume last
    EXPECT_EQ(stream->lookChar(), EOF);  // peek past end
    EXPECT_EQ(stream->getChar(), EOF);   // consume past end
}
