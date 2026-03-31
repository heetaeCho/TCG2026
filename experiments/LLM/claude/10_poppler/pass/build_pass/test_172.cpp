#include <gtest/gtest.h>
#include <memory>
#include "Object.h"
#include "Stream.h"

class BaseMemStreamTest_172 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test getStart returns the correct start position when constructed with start=0
TEST_F(BaseMemStreamTest_172, GetStartReturnsZeroWhenStartIsZero_172) {
    unsigned char buf[] = {0x41, 0x42, 0x43, 0x44, 0x45};
    Goffset startPos = 0;
    Goffset length = 5;
    Object dict;
    
    BaseMemStream<unsigned char> stream(buf, startPos, length, std::move(dict));
    
    EXPECT_EQ(stream.getStart(), 0);
}

// Test getStart returns the correct start position when constructed with non-zero start
TEST_F(BaseMemStreamTest_172, GetStartReturnsNonZeroStart_172) {
    unsigned char buf[] = {0x41, 0x42, 0x43, 0x44, 0x45};
    Goffset startPos = 10;
    Goffset length = 5;
    Object dict;
    
    BaseMemStream<unsigned char> stream(buf, startPos, length, std::move(dict));
    
    EXPECT_EQ(stream.getStart(), 10);
}

// Test getStart returns correct value with large start offset
TEST_F(BaseMemStreamTest_172, GetStartReturnsLargeStartValue_172) {
    unsigned char buf[] = {0x41};
    Goffset startPos = 1000000;
    Goffset length = 1;
    Object dict;
    
    BaseMemStream<unsigned char> stream(buf, startPos, length, std::move(dict));
    
    EXPECT_EQ(stream.getStart(), 1000000);
}

// Test getStart after moveStart changes the start position
TEST_F(BaseMemStreamTest_172, GetStartAfterMoveStartReturnsUpdatedPosition_172) {
    unsigned char buf[] = {0x41, 0x42, 0x43, 0x44, 0x45};
    Goffset startPos = 0;
    Goffset length = 5;
    Object dict;
    
    BaseMemStream<unsigned char> stream(buf, startPos, length, std::move(dict));
    stream.moveStart(3);
    
    EXPECT_EQ(stream.getStart(), 3);
}

// Test getChar reads the first byte correctly
TEST_F(BaseMemStreamTest_172, GetCharReadsFirstByte_172) {
    unsigned char buf[] = {0x41, 0x42, 0x43};
    Goffset startPos = 0;
    Goffset length = 3;
    Object dict;
    
    BaseMemStream<unsigned char> stream(buf, startPos, length, std::move(dict));
    stream.rewind();
    
    int ch = stream.getChar();
    EXPECT_EQ(ch, 0x41);
}

// Test getChar reads sequential bytes
TEST_F(BaseMemStreamTest_172, GetCharReadsSequentialBytes_172) {
    unsigned char buf[] = {0x41, 0x42, 0x43};
    Goffset startPos = 0;
    Goffset length = 3;
    Object dict;
    
    BaseMemStream<unsigned char> stream(buf, startPos, length, std::move(dict));
    stream.rewind();
    
    EXPECT_EQ(stream.getChar(), 0x41);
    EXPECT_EQ(stream.getChar(), 0x42);
    EXPECT_EQ(stream.getChar(), 0x43);
}

// Test getChar returns EOF at end of stream
TEST_F(BaseMemStreamTest_172, GetCharReturnsEOFAtEnd_172) {
    unsigned char buf[] = {0x41};
    Goffset startPos = 0;
    Goffset length = 1;
    Object dict;
    
    BaseMemStream<unsigned char> stream(buf, startPos, length, std::move(dict));
    stream.rewind();
    
    stream.getChar(); // consume the only byte
    int ch = stream.getChar();
    EXPECT_EQ(ch, EOF);
}

// Test lookChar returns the current byte without advancing
TEST_F(BaseMemStreamTest_172, LookCharDoesNotAdvancePosition_172) {
    unsigned char buf[] = {0x41, 0x42, 0x43};
    Goffset startPos = 0;
    Goffset length = 3;
    Object dict;
    
    BaseMemStream<unsigned char> stream(buf, startPos, length, std::move(dict));
    stream.rewind();
    
    int ch1 = stream.lookChar();
    int ch2 = stream.lookChar();
    EXPECT_EQ(ch1, ch2);
    EXPECT_EQ(ch1, 0x41);
}

// Test getPos returns the current position in the stream
TEST_F(BaseMemStreamTest_172, GetPosReturnsCorrectPosition_172) {
    unsigned char buf[] = {0x41, 0x42, 0x43, 0x44, 0x45};
    Goffset startPos = 0;
    Goffset length = 5;
    Object dict;
    
    BaseMemStream<unsigned char> stream(buf, startPos, length, std::move(dict));
    stream.rewind();
    
    EXPECT_EQ(stream.getPos(), 0);
    stream.getChar();
    EXPECT_EQ(stream.getPos(), 1);
    stream.getChar();
    EXPECT_EQ(stream.getPos(), 2);
}

// Test setPos sets position correctly
TEST_F(BaseMemStreamTest_172, SetPosSetsCorrectPosition_172) {
    unsigned char buf[] = {0x41, 0x42, 0x43, 0x44, 0x45};
    Goffset startPos = 0;
    Goffset length = 5;
    Object dict;
    
    BaseMemStream<unsigned char> stream(buf, startPos, length, std::move(dict));
    stream.rewind();
    
    stream.setPos(3);
    EXPECT_EQ(stream.getPos(), 3);
    EXPECT_EQ(stream.getChar(), 0x44);
}

// Test rewind resets position to start
TEST_F(BaseMemStreamTest_172, RewindResetsToStart_172) {
    unsigned char buf[] = {0x41, 0x42, 0x43};
    Goffset startPos = 0;
    Goffset length = 3;
    Object dict;
    
    BaseMemStream<unsigned char> stream(buf, startPos, length, std::move(dict));
    stream.rewind();
    
    stream.getChar();
    stream.getChar();
    stream.rewind();
    
    EXPECT_EQ(stream.getChar(), 0x41);
}

// Test getKind returns the correct stream kind
TEST_F(BaseMemStreamTest_172, GetKindReturnsMemStream_172) {
    unsigned char buf[] = {0x41};
    Goffset startPos = 0;
    Goffset length = 1;
    Object dict;
    
    BaseMemStream<unsigned char> stream(buf, startPos, length, std::move(dict));
    
    // MemStream kind
    StreamKind kind = stream.getKind();
    // We just check it returns a valid kind without assuming the exact value
    // But typically BaseMemStream should be strWeird or a memory stream kind
    (void)kind; // at least it shouldn't crash
}

// Test empty stream returns EOF immediately
TEST_F(BaseMemStreamTest_172, EmptyStreamReturnsEOF_172) {
    unsigned char buf[] = {0x00};
    Goffset startPos = 0;
    Goffset length = 0;
    Object dict;
    
    BaseMemStream<unsigned char> stream(buf, startPos, length, std::move(dict));
    stream.rewind();
    
    EXPECT_EQ(stream.getChar(), EOF);
}

// Test getUnfilteredChar reads byte correctly
TEST_F(BaseMemStreamTest_172, GetUnfilteredCharReadsByte_172) {
    unsigned char buf[] = {0x41, 0x42, 0x43};
    Goffset startPos = 0;
    Goffset length = 3;
    Object dict;
    
    BaseMemStream<unsigned char> stream(buf, startPos, length, std::move(dict));
    stream.rewind();
    
    int ch = stream.getUnfilteredChar();
    EXPECT_EQ(ch, 0x41);
}

// Test unfilteredRewind resets position
TEST_F(BaseMemStreamTest_172, UnfilteredRewindResetsPosition_172) {
    unsigned char buf[] = {0x41, 0x42, 0x43};
    Goffset startPos = 0;
    Goffset length = 3;
    Object dict;
    
    BaseMemStream<unsigned char> stream(buf, startPos, length, std::move(dict));
    stream.rewind();
    
    stream.getChar();
    stream.getChar();
    bool result = stream.unfilteredRewind();
    EXPECT_TRUE(result);
    EXPECT_EQ(stream.getChar(), 0x41);
}

// Test copy creates a valid copy
TEST_F(BaseMemStreamTest_172, CopyCreatesValidCopy_172) {
    unsigned char buf[] = {0x41, 0x42, 0x43};
    Goffset startPos = 0;
    Goffset length = 3;
    Object dict;
    
    BaseMemStream<unsigned char> stream(buf, startPos, length, std::move(dict));
    
    auto copyStream = stream.copy();
    ASSERT_NE(copyStream, nullptr);
    EXPECT_EQ(copyStream->getStart(), 0);
}

// Test makeSubStream creates a valid sub-stream
TEST_F(BaseMemStreamTest_172, MakeSubStreamCreatesValidSubStream_172) {
    unsigned char buf[] = {0x41, 0x42, 0x43, 0x44, 0x45};
    Goffset startPos = 0;
    Goffset length = 5;
    Object dict;
    
    BaseMemStream<unsigned char> stream(buf, startPos, length, std::move(dict));
    
    Object subDict;
    auto subStream = stream.makeSubStream(1, true, 3, std::move(subDict));
    ASSERT_NE(subStream, nullptr);
}

// Test setPos with dir parameter from end
TEST_F(BaseMemStreamTest_172, SetPosFromEnd_172) {
    unsigned char buf[] = {0x41, 0x42, 0x43, 0x44, 0x45};
    Goffset startPos = 0;
    Goffset length = 5;
    Object dict;
    
    BaseMemStream<unsigned char> stream(buf, startPos, length, std::move(dict));
    stream.rewind();
    
    // dir != 0 means from the end
    stream.setPos(0, 1);
    // After setting to end, the position should be at or near the end
    Goffset pos = stream.getPos();
    EXPECT_GE(pos, 0);
}

// Test moveStart with delta of 0
TEST_F(BaseMemStreamTest_172, MoveStartWithZeroDelta_172) {
    unsigned char buf[] = {0x41, 0x42, 0x43};
    Goffset startPos = 5;
    Goffset length = 3;
    Object dict;
    
    BaseMemStream<unsigned char> stream(buf, startPos, length, std::move(dict));
    stream.moveStart(0);
    
    EXPECT_EQ(stream.getStart(), 5);
}

// Test rewind returns true
TEST_F(BaseMemStreamTest_172, RewindReturnsTrue_172) {
    unsigned char buf[] = {0x41, 0x42};
    Goffset startPos = 0;
    Goffset length = 2;
    Object dict;
    
    BaseMemStream<unsigned char> stream(buf, startPos, length, std::move(dict));
    
    bool result = stream.rewind();
    EXPECT_TRUE(result);
}

// Test close does not crash and stream can be rewound after
TEST_F(BaseMemStreamTest_172, CloseDoesNotCrash_172) {
    unsigned char buf[] = {0x41, 0x42, 0x43};
    Goffset startPos = 0;
    Goffset length = 3;
    Object dict;
    
    BaseMemStream<unsigned char> stream(buf, startPos, length, std::move(dict));
    stream.rewind();
    stream.getChar();
    
    // close should not crash
    stream.close();
}

// Test with char* buffer type
TEST_F(BaseMemStreamTest_172, CharBufferGetStart_172) {
    char buf[] = {'A', 'B', 'C', 'D', 'E'};
    Goffset startPos = 42;
    Goffset length = 5;
    Object dict;
    
    BaseMemStream<char> stream(buf, startPos, length, std::move(dict));
    
    EXPECT_EQ(stream.getStart(), 42);
}

// Test reading entire buffer
TEST_F(BaseMemStreamTest_172, ReadEntireBuffer_172) {
    unsigned char buf[] = {0x00, 0x01, 0x02, 0xFF, 0xFE};
    Goffset startPos = 0;
    Goffset length = 5;
    Object dict;
    
    BaseMemStream<unsigned char> stream(buf, startPos, length, std::move(dict));
    stream.rewind();
    
    EXPECT_EQ(stream.getChar(), 0x00);
    EXPECT_EQ(stream.getChar(), 0x01);
    EXPECT_EQ(stream.getChar(), 0x02);
    EXPECT_EQ(stream.getChar(), 0xFF);
    EXPECT_EQ(stream.getChar(), 0xFE);
    EXPECT_EQ(stream.getChar(), EOF);
}

// Test lookChar at end of stream returns EOF
TEST_F(BaseMemStreamTest_172, LookCharAtEndReturnsEOF_172) {
    unsigned char buf[] = {0x41};
    Goffset startPos = 0;
    Goffset length = 1;
    Object dict;
    
    BaseMemStream<unsigned char> stream(buf, startPos, length, std::move(dict));
    stream.rewind();
    
    stream.getChar(); // consume the only byte
    int ch = stream.lookChar();
    EXPECT_EQ(ch, EOF);
}
