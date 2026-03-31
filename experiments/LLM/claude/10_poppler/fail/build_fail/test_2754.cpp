#include <gtest/gtest.h>
#include "Stream.h"
#include "Object.h"

// Type alias for convenience
using MemStream = BaseMemStream<const unsigned char>;
using MutableMemStream = BaseMemStream<unsigned char>;

class BaseMemStreamTest_2754 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test basic construction and getLength
TEST_F(BaseMemStreamTest_2754, ConstructionAndGetLength_2754) {
    const unsigned char data[] = "Hello, World!";
    Goffset length = 13;
    MemStream stream(data, 0, length, Object(objNull));
    EXPECT_EQ(stream.getLength(), length);
}

// Test getKind returns memStreamKind
TEST_F(BaseMemStreamTest_2754, GetKindReturnsMemStream_2754) {
    const unsigned char data[] = "Test";
    MemStream stream(data, 0, 4, Object(objNull));
    EXPECT_EQ(stream.getKind(), streamMem);
}

// Test getChar reads bytes sequentially
TEST_F(BaseMemStreamTest_2754, GetCharReadsSequentially_2754) {
    const unsigned char data[] = {0x41, 0x42, 0x43, 0x44}; // ABCD
    MemStream stream(data, 0, 4, Object(objNull));
    EXPECT_EQ(stream.getChar(), 0x41);
    EXPECT_EQ(stream.getChar(), 0x42);
    EXPECT_EQ(stream.getChar(), 0x43);
    EXPECT_EQ(stream.getChar(), 0x44);
}

// Test getChar returns EOF at end
TEST_F(BaseMemStreamTest_2754, GetCharReturnsEOFAtEnd_2754) {
    const unsigned char data[] = {0x41};
    MemStream stream(data, 0, 1, Object(objNull));
    EXPECT_EQ(stream.getChar(), 0x41);
    EXPECT_EQ(stream.getChar(), EOF);
}

// Test lookChar does not advance position
TEST_F(BaseMemStreamTest_2754, LookCharDoesNotAdvance_2754) {
    const unsigned char data[] = {0x41, 0x42};
    MemStream stream(data, 0, 2, Object(objNull));
    EXPECT_EQ(stream.lookChar(), 0x41);
    EXPECT_EQ(stream.lookChar(), 0x41);
    EXPECT_EQ(stream.getChar(), 0x41);
    EXPECT_EQ(stream.lookChar(), 0x42);
}

// Test getPos returns current position
TEST_F(BaseMemStreamTest_2754, GetPosReturnsCurrentPosition_2754) {
    const unsigned char data[] = {0x41, 0x42, 0x43};
    MemStream stream(data, 0, 3, Object(objNull));
    EXPECT_EQ(stream.getPos(), 0);
    stream.getChar();
    EXPECT_EQ(stream.getPos(), 1);
    stream.getChar();
    EXPECT_EQ(stream.getPos(), 2);
}

// Test rewind resets position to start
TEST_F(BaseMemStreamTest_2754, RewindResetsPosition_2754) {
    const unsigned char data[] = {0x41, 0x42, 0x43};
    MemStream stream(data, 0, 3, Object(objNull));
    stream.getChar();
    stream.getChar();
    EXPECT_EQ(stream.getPos(), 2);
    stream.rewind();
    EXPECT_EQ(stream.getPos(), 0);
    EXPECT_EQ(stream.getChar(), 0x41);
}

// Test setPos with dir=0 (from start)
TEST_F(BaseMemStreamTest_2754, SetPosFromStart_2754) {
    const unsigned char data[] = {0x41, 0x42, 0x43, 0x44, 0x45};
    MemStream stream(data, 0, 5, Object(objNull));
    stream.setPos(3, 0);
    EXPECT_EQ(stream.getChar(), 0x44);
}

// Test setPos with dir=-1 (from end)
TEST_F(BaseMemStreamTest_2754, SetPosFromEnd_2754) {
    const unsigned char data[] = {0x41, 0x42, 0x43, 0x44, 0x45};
    MemStream stream(data, 0, 5, Object(objNull));
    stream.setPos(1, -1);
    EXPECT_EQ(stream.getChar(), 0x45);
}

// Test construction with non-zero start offset
TEST_F(BaseMemStreamTest_2754, NonZeroStartOffset_2754) {
    const unsigned char data[] = {0x00, 0x00, 0x41, 0x42, 0x43};
    MemStream stream(data, 2, 3, Object(objNull));
    EXPECT_EQ(stream.getChar(), 0x41);
    EXPECT_EQ(stream.getChar(), 0x42);
    EXPECT_EQ(stream.getChar(), 0x43);
    EXPECT_EQ(stream.getChar(), EOF);
}

// Test getStart returns start offset
TEST_F(BaseMemStreamTest_2754, GetStartReturnsStartOffset_2754) {
    const unsigned char data[] = {0x00, 0x00, 0x41, 0x42, 0x43};
    MemStream stream(data, 2, 3, Object(objNull));
    EXPECT_EQ(stream.getStart(), 2);
}

// Test zero length stream
TEST_F(BaseMemStreamTest_2754, ZeroLengthStream_2754) {
    const unsigned char data[] = {0x41};
    MemStream stream(data, 0, 0, Object(objNull));
    EXPECT_EQ(stream.getLength(), 0);
    EXPECT_EQ(stream.getChar(), EOF);
}

// Test moveStart shifts the start
TEST_F(BaseMemStreamTest_2754, MoveStartShiftsStart_2754) {
    const unsigned char data[] = {0x41, 0x42, 0x43, 0x44, 0x45};
    MemStream stream(data, 0, 5, Object(objNull));
    stream.moveStart(2);
    EXPECT_EQ(stream.getStart(), 2);
}

// Test close does not crash and can still be used after
TEST_F(BaseMemStreamTest_2754, CloseDoesNotCrash_2754) {
    const unsigned char data[] = {0x41, 0x42};
    MemStream stream(data, 0, 2, Object(objNull));
    stream.close();
    // After close, operations should still be valid
    SUCCEED();
}

// Test getDict returns the dictionary
TEST_F(BaseMemStreamTest_2754, GetDictReturnsDict_2754) {
    const unsigned char data[] = {0x41};
    MemStream stream(data, 0, 1, Object(objNull));
    // getDict() should return a non-null pointer (even if the dict is objNull-typed)
    // getDictObject should return the Object
    Object* dictObj = stream.getDictObject();
    ASSERT_NE(dictObj, nullptr);
}

// Test copy creates a valid copy
TEST_F(BaseMemStreamTest_2754, CopyCreatesValidStream_2754) {
    const unsigned char data[] = {0x41, 0x42, 0x43};
    MemStream stream(data, 0, 3, Object(objNull));
    auto copyStream = stream.copy();
    ASSERT_NE(copyStream, nullptr);
    EXPECT_EQ(copyStream->getLength(), 3);
}

// Test makeSubStream creates a valid sub stream
TEST_F(BaseMemStreamTest_2754, MakeSubStreamCreatesValidStream_2754) {
    const unsigned char data[] = {0x41, 0x42, 0x43, 0x44, 0x45};
    MemStream stream(data, 0, 5, Object(objNull));
    auto subStream = stream.makeSubStream(1, true, 3, Object(objNull));
    ASSERT_NE(subStream, nullptr);
}

// Test getUnfilteredChar behaves like getChar for base mem stream
TEST_F(BaseMemStreamTest_2754, GetUnfilteredCharReadsSequentially_2754) {
    const unsigned char data[] = {0x41, 0x42, 0x43};
    MemStream stream(data, 0, 3, Object(objNull));
    EXPECT_EQ(stream.getUnfilteredChar(), 0x41);
    EXPECT_EQ(stream.getUnfilteredChar(), 0x42);
}

// Test unfilteredRewind works
TEST_F(BaseMemStreamTest_2754, UnfilteredRewindResetsPosition_2754) {
    const unsigned char data[] = {0x41, 0x42, 0x43};
    MemStream stream(data, 0, 3, Object(objNull));
    stream.getChar();
    stream.getChar();
    stream.unfilteredRewind();
    EXPECT_EQ(stream.getChar(), 0x41);
}

// Test reading single byte data
TEST_F(BaseMemStreamTest_2754, SingleByteData_2754) {
    const unsigned char data[] = {0xFF};
    MemStream stream(data, 0, 1, Object(objNull));
    EXPECT_EQ(stream.getChar(), 0xFF);
    EXPECT_EQ(stream.getChar(), EOF);
}

// Test getPos with start offset
TEST_F(BaseMemStreamTest_2754, GetPosWithStartOffset_2754) {
    const unsigned char data[] = {0x00, 0x00, 0x41, 0x42};
    MemStream stream(data, 2, 2, Object(objNull));
    EXPECT_EQ(stream.getPos(), 2);
    stream.getChar();
    EXPECT_EQ(stream.getPos(), 3);
}

// Test reading all 256 byte values
TEST_F(BaseMemStreamTest_2754, AllByteValues_2754) {
    unsigned char data[256];
    for (int i = 0; i < 256; i++) {
        data[i] = static_cast<unsigned char>(i);
    }
    MutableMemStream stream(data, 0, 256, Object(objNull));
    for (int i = 0; i < 256; i++) {
        EXPECT_EQ(stream.getChar(), i);
    }
    EXPECT_EQ(stream.getChar(), EOF);
}

// Test setPos to position 0
TEST_F(BaseMemStreamTest_2754, SetPosToZero_2754) {
    const unsigned char data[] = {0x41, 0x42, 0x43};
    MemStream stream(data, 0, 3, Object(objNull));
    stream.getChar();
    stream.getChar();
    stream.setPos(0, 0);
    EXPECT_EQ(stream.getChar(), 0x41);
}

// Test setPos beyond the end
TEST_F(BaseMemStreamTest_2754, SetPosBeyondEnd_2754) {
    const unsigned char data[] = {0x41, 0x42, 0x43};
    MemStream stream(data, 0, 3, Object(objNull));
    stream.setPos(100, 0);
    // After seeking beyond end, getChar should return EOF
    EXPECT_EQ(stream.getChar(), EOF);
}

// Test isBinary
TEST_F(BaseMemStreamTest_2754, IsBinaryReturnsFalse_2754) {
    const unsigned char data[] = {0x41};
    MemStream stream(data, 0, 1, Object(objNull));
    // BaseStream::isBinary default behavior
    EXPECT_FALSE(stream.isBinary());
}

// Test getBaseStream returns self
TEST_F(BaseMemStreamTest_2754, GetBaseStreamReturnsSelf_2754) {
    const unsigned char data[] = {0x41};
    MemStream stream(data, 0, 1, Object(objNull));
    EXPECT_EQ(stream.getBaseStream(), &stream);
}

// Test getUndecodedStream returns self
TEST_F(BaseMemStreamTest_2754, GetUndecodedStreamReturnsSelf_2754) {
    const unsigned char data[] = {0x41};
    MemStream stream(data, 0, 1, Object(objNull));
    EXPECT_EQ(stream.getUndecodedStream(), &stream);
}

// Test rewind returns true
TEST_F(BaseMemStreamTest_2754, RewindReturnsTrue_2754) {
    const unsigned char data[] = {0x41, 0x42};
    MemStream stream(data, 0, 2, Object(objNull));
    stream.getChar();
    EXPECT_TRUE(stream.rewind());
}

// Test lookChar returns EOF on empty stream
TEST_F(BaseMemStreamTest_2754, LookCharReturnsEOFOnEmpty_2754) {
    const unsigned char data[] = {0x41};
    MemStream stream(data, 0, 0, Object(objNull));
    EXPECT_EQ(stream.lookChar(), EOF);
}

// Test multiple rewind calls
TEST_F(BaseMemStreamTest_2754, MultipleRewindCalls_2754) {
    const unsigned char data[] = {0x41, 0x42, 0x43};
    MemStream stream(data, 0, 3, Object(objNull));
    stream.getChar();
    stream.rewind();
    stream.getChar();
    stream.getChar();
    stream.rewind();
    EXPECT_EQ(stream.getChar(), 0x41);
}

// Test large offset start
TEST_F(BaseMemStreamTest_2754, LargeBufferWithOffset_2754) {
    unsigned char data[1024];
    for (int i = 0; i < 1024; i++) {
        data[i] = static_cast<unsigned char>(i & 0xFF);
    }
    MutableMemStream stream(data, 512, 512, Object(objNull));
    EXPECT_EQ(stream.getStart(), 512);
    EXPECT_EQ(stream.getLength(), 512);
    EXPECT_EQ(stream.getChar(), static_cast<int>(data[512]));
}
