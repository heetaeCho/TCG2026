#include <gtest/gtest.h>
#include <memory>
#include "Object.h"
#include "Stream.h"

class BaseMemStreamTest_166 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that getKind returns strWeird for unsigned char variant
TEST_F(BaseMemStreamTest_166, GetKindReturnsStrWeird_166) {
    unsigned char data[] = "Hello, World!";
    Goffset length = sizeof(data) - 1;
    Object dict;
    BaseMemStream<unsigned char> stream(data, 0, length, std::move(dict));
    EXPECT_EQ(stream.getKind(), strWeird);
}

// Test that getKind returns strWeird for const char variant
TEST_F(BaseMemStreamTest_166, GetKindReturnsStrWeirdConstChar_166) {
    const char data[] = "Test data";
    Goffset length = sizeof(data) - 1;
    Object dict;
    BaseMemStream<const char> stream(const_cast<const char *>(data), 0, length, std::move(dict));
    EXPECT_EQ(stream.getKind(), strWeird);
}

// Test getStart returns the correct start position
TEST_F(BaseMemStreamTest_166, GetStartReturnsCorrectValue_166) {
    unsigned char data[] = "Hello, World!";
    Goffset length = sizeof(data) - 1;
    Object dict;
    BaseMemStream<unsigned char> stream(data, 5, length, std::move(dict));
    EXPECT_EQ(stream.getStart(), 5);
}

// Test getPos after construction
TEST_F(BaseMemStreamTest_166, GetPosAfterConstruction_166) {
    unsigned char data[] = "Hello";
    Goffset length = sizeof(data) - 1;
    Object dict;
    BaseMemStream<unsigned char> stream(data, 0, length, std::move(dict));
    EXPECT_EQ(stream.getPos(), 0);
}

// Test getChar reads bytes correctly
TEST_F(BaseMemStreamTest_166, GetCharReadsBytes_166) {
    unsigned char data[] = {0x41, 0x42, 0x43}; // A, B, C
    Goffset length = 3;
    Object dict;
    BaseMemStream<unsigned char> stream(data, 0, length, std::move(dict));
    EXPECT_EQ(stream.getChar(), 0x41);
    EXPECT_EQ(stream.getChar(), 0x42);
    EXPECT_EQ(stream.getChar(), 0x43);
}

// Test getChar returns EOF at end of stream
TEST_F(BaseMemStreamTest_166, GetCharReturnsEOFAtEnd_166) {
    unsigned char data[] = {0x41};
    Goffset length = 1;
    Object dict;
    BaseMemStream<unsigned char> stream(data, 0, length, std::move(dict));
    EXPECT_EQ(stream.getChar(), 0x41);
    EXPECT_EQ(stream.getChar(), EOF);
}

// Test lookChar does not advance position
TEST_F(BaseMemStreamTest_166, LookCharDoesNotAdvance_166) {
    unsigned char data[] = {0x41, 0x42};
    Goffset length = 2;
    Object dict;
    BaseMemStream<unsigned char> stream(data, 0, length, std::move(dict));
    EXPECT_EQ(stream.lookChar(), 0x41);
    EXPECT_EQ(stream.lookChar(), 0x41);
    EXPECT_EQ(stream.getPos(), 0);
}

// Test rewind resets position to start
TEST_F(BaseMemStreamTest_166, RewindResetsPosition_166) {
    unsigned char data[] = {0x41, 0x42, 0x43};
    Goffset length = 3;
    Object dict;
    BaseMemStream<unsigned char> stream(data, 0, length, std::move(dict));
    stream.getChar();
    stream.getChar();
    EXPECT_EQ(stream.getPos(), 2);
    stream.rewind();
    EXPECT_EQ(stream.getPos(), 0);
    EXPECT_EQ(stream.getChar(), 0x41);
}

// Test setPos sets position correctly
TEST_F(BaseMemStreamTest_166, SetPosSetsCorrectPosition_166) {
    unsigned char data[] = {0x41, 0x42, 0x43, 0x44, 0x45};
    Goffset length = 5;
    Object dict;
    BaseMemStream<unsigned char> stream(data, 0, length, std::move(dict));
    stream.setPos(3);
    EXPECT_EQ(stream.getPos(), 3);
    EXPECT_EQ(stream.getChar(), 0x44);
}

// Test setPos with dir = -1 sets position from end
TEST_F(BaseMemStreamTest_166, SetPosFromEnd_166) {
    unsigned char data[] = {0x41, 0x42, 0x43, 0x44, 0x45};
    Goffset length = 5;
    Object dict;
    BaseMemStream<unsigned char> stream(data, 0, length, std::move(dict));
    stream.setPos(0, -1);
    // Position from end; exact behavior depends on implementation
    // At minimum, the position should be valid
    Goffset pos = stream.getPos();
    EXPECT_GE(pos, 0);
    EXPECT_LE(pos, length);
}

// Test moveStart moves the start position
TEST_F(BaseMemStreamTest_166, MoveStartMovesStartPosition_166) {
    unsigned char data[] = {0x41, 0x42, 0x43, 0x44, 0x45};
    Goffset length = 5;
    Object dict;
    BaseMemStream<unsigned char> stream(data, 0, length, std::move(dict));
    stream.moveStart(2);
    EXPECT_EQ(stream.getStart(), 2);
}

// Test zero-length stream
TEST_F(BaseMemStreamTest_166, ZeroLengthStream_166) {
    unsigned char data[] = {0x41};
    Goffset length = 0;
    Object dict;
    BaseMemStream<unsigned char> stream(data, 0, length, std::move(dict));
    EXPECT_EQ(stream.getChar(), EOF);
    EXPECT_EQ(stream.lookChar(), EOF);
}

// Test getUnfilteredChar reads bytes correctly
TEST_F(BaseMemStreamTest_166, GetUnfilteredCharReadsBytes_166) {
    unsigned char data[] = {0x41, 0x42};
    Goffset length = 2;
    Object dict;
    BaseMemStream<unsigned char> stream(data, 0, length, std::move(dict));
    int ch = stream.getUnfilteredChar();
    EXPECT_EQ(ch, 0x41);
}

// Test unfilteredRewind resets position
TEST_F(BaseMemStreamTest_166, UnfilteredRewindResetsPosition_166) {
    unsigned char data[] = {0x41, 0x42, 0x43};
    Goffset length = 3;
    Object dict;
    BaseMemStream<unsigned char> stream(data, 0, length, std::move(dict));
    stream.getChar();
    stream.getChar();
    bool result = stream.unfilteredRewind();
    EXPECT_TRUE(result);
    EXPECT_EQ(stream.getPos(), 0);
}

// Test close does not crash and stream can be used after
TEST_F(BaseMemStreamTest_166, CloseDoesNotCrash_166) {
    unsigned char data[] = {0x41, 0x42};
    Goffset length = 2;
    Object dict;
    BaseMemStream<unsigned char> stream(data, 0, length, std::move(dict));
    stream.close();
    // After close, behavior may vary, but it should not crash
}

// Test copy creates a valid copy
TEST_F(BaseMemStreamTest_166, CopyCreatesValidCopy_166) {
    unsigned char data[] = {0x41, 0x42, 0x43};
    Goffset length = 3;
    Object dict;
    BaseMemStream<unsigned char> stream(data, 0, length, std::move(dict));
    auto copyStream = stream.copy();
    ASSERT_NE(copyStream, nullptr);
    EXPECT_EQ(copyStream->getKind(), strWeird);
}

// Test makeSubStream creates a valid sub-stream
TEST_F(BaseMemStreamTest_166, MakeSubStreamCreatesValidStream_166) {
    unsigned char data[] = {0x41, 0x42, 0x43, 0x44, 0x45};
    Goffset length = 5;
    Object dict;
    BaseMemStream<unsigned char> stream(data, 0, length, std::move(dict));
    Object subDict;
    auto subStream = stream.makeSubStream(1, true, 3, std::move(subDict));
    ASSERT_NE(subStream, nullptr);
}

// Test getPos advances with getChar
TEST_F(BaseMemStreamTest_166, GetPosAdvancesWithGetChar_166) {
    unsigned char data[] = {0x41, 0x42, 0x43, 0x44};
    Goffset length = 4;
    Object dict;
    BaseMemStream<unsigned char> stream(data, 0, length, std::move(dict));
    EXPECT_EQ(stream.getPos(), 0);
    stream.getChar();
    EXPECT_EQ(stream.getPos(), 1);
    stream.getChar();
    EXPECT_EQ(stream.getPos(), 2);
    stream.getChar();
    EXPECT_EQ(stream.getPos(), 3);
    stream.getChar();
    EXPECT_EQ(stream.getPos(), 4);
}

// Test rewind returns true
TEST_F(BaseMemStreamTest_166, RewindReturnsTrue_166) {
    unsigned char data[] = {0x41, 0x42};
    Goffset length = 2;
    Object dict;
    BaseMemStream<unsigned char> stream(data, 0, length, std::move(dict));
    stream.getChar();
    bool result = stream.rewind();
    EXPECT_TRUE(result);
}

// Test setPos beyond boundary
TEST_F(BaseMemStreamTest_166, SetPosBeyondLength_166) {
    unsigned char data[] = {0x41, 0x42, 0x43};
    Goffset length = 3;
    Object dict;
    BaseMemStream<unsigned char> stream(data, 0, length, std::move(dict));
    stream.setPos(10);
    // After setting position beyond length, getChar should return EOF
    EXPECT_EQ(stream.getChar(), EOF);
}

// Test with non-zero start offset
TEST_F(BaseMemStreamTest_166, NonZeroStartOffset_166) {
    unsigned char data[] = {0x41, 0x42, 0x43, 0x44, 0x45};
    Goffset length = 3;
    Object dict;
    BaseMemStream<unsigned char> stream(data, 2, length, std::move(dict));
    EXPECT_EQ(stream.getStart(), 2);
    // The stream should still read from buf starting position
    int ch = stream.getChar();
    EXPECT_NE(ch, EOF);
}

// Test multiple rewinds
TEST_F(BaseMemStreamTest_166, MultipleRewinds_166) {
    unsigned char data[] = {0x41, 0x42, 0x43};
    Goffset length = 3;
    Object dict;
    BaseMemStream<unsigned char> stream(data, 0, length, std::move(dict));
    
    EXPECT_EQ(stream.getChar(), 0x41);
    EXPECT_EQ(stream.getChar(), 0x42);
    stream.rewind();
    EXPECT_EQ(stream.getChar(), 0x41);
    EXPECT_EQ(stream.getChar(), 0x42);
    EXPECT_EQ(stream.getChar(), 0x43);
    stream.rewind();
    EXPECT_EQ(stream.getChar(), 0x41);
}

// Test lookChar at EOF returns EOF
TEST_F(BaseMemStreamTest_166, LookCharAtEOFReturnsEOF_166) {
    unsigned char data[] = {0x41};
    Goffset length = 1;
    Object dict;
    BaseMemStream<unsigned char> stream(data, 0, length, std::move(dict));
    stream.getChar(); // consume the only byte
    EXPECT_EQ(stream.lookChar(), EOF);
}

// Test single byte stream
TEST_F(BaseMemStreamTest_166, SingleByteStream_166) {
    unsigned char data[] = {0xFF};
    Goffset length = 1;
    Object dict;
    BaseMemStream<unsigned char> stream(data, 0, length, std::move(dict));
    EXPECT_EQ(stream.lookChar(), 0xFF);
    EXPECT_EQ(stream.getChar(), 0xFF);
    EXPECT_EQ(stream.getChar(), EOF);
    stream.rewind();
    EXPECT_EQ(stream.getChar(), 0xFF);
}
