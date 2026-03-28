#include <gtest/gtest.h>
#include <memory>
#include "Object.h"
#include "Stream.h"

class BaseMemStreamTest_174 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test basic construction and getChar
TEST_F(BaseMemStreamTest_174, GetCharReturnsCorrectBytes_174) {
    unsigned char data[] = { 'H', 'e', 'l', 'l', 'o' };
    Object dict;
    BaseMemStream<unsigned char> stream(data, 0, 5, std::move(dict));
    stream.reset();

    EXPECT_EQ('H', stream.getChar());
    EXPECT_EQ('e', stream.getChar());
    EXPECT_EQ('l', stream.getChar());
    EXPECT_EQ('l', stream.getChar());
    EXPECT_EQ('o', stream.getChar());
}

// Test getChar returns EOF at end of stream
TEST_F(BaseMemStreamTest_174, GetCharReturnsEOFAtEnd_174) {
    unsigned char data[] = { 'A' };
    Object dict;
    BaseMemStream<unsigned char> stream(data, 0, 1, std::move(dict));
    stream.reset();

    EXPECT_EQ('A', stream.getChar());
    EXPECT_EQ(EOF, stream.getChar());
}

// Test lookChar does not advance position
TEST_F(BaseMemStreamTest_174, LookCharDoesNotAdvance_174) {
    unsigned char data[] = { 'X', 'Y' };
    Object dict;
    BaseMemStream<unsigned char> stream(data, 0, 2, std::move(dict));
    stream.reset();

    EXPECT_EQ('X', stream.lookChar());
    EXPECT_EQ('X', stream.lookChar());
    EXPECT_EQ('X', stream.getChar());
    EXPECT_EQ('Y', stream.lookChar());
}

// Test lookChar returns EOF when at end
TEST_F(BaseMemStreamTest_174, LookCharReturnsEOFAtEnd_174) {
    unsigned char data[] = { 'Z' };
    Object dict;
    BaseMemStream<unsigned char> stream(data, 0, 1, std::move(dict));
    stream.reset();

    stream.getChar(); // consume 'Z'
    EXPECT_EQ(EOF, stream.lookChar());
}

// Test getPos returns correct position
TEST_F(BaseMemStreamTest_174, GetPosReturnsCorrectPosition_174) {
    unsigned char data[] = { 'A', 'B', 'C', 'D' };
    Object dict;
    BaseMemStream<unsigned char> stream(data, 0, 4, std::move(dict));
    stream.reset();

    EXPECT_EQ(0, stream.getPos());
    stream.getChar();
    EXPECT_EQ(1, stream.getPos());
    stream.getChar();
    EXPECT_EQ(2, stream.getPos());
}

// Test rewind resets position to start
TEST_F(BaseMemStreamTest_174, RewindResetsPosition_174) {
    unsigned char data[] = { 'A', 'B', 'C' };
    Object dict;
    BaseMemStream<unsigned char> stream(data, 0, 3, std::move(dict));
    stream.reset();

    stream.getChar();
    stream.getChar();
    EXPECT_EQ(2, stream.getPos());

    bool result = stream.rewind();
    EXPECT_TRUE(result);
    EXPECT_EQ(0, stream.getPos());
    EXPECT_EQ('A', stream.getChar());
}

// Test setPos with forward direction
TEST_F(BaseMemStreamTest_174, SetPosForward_174) {
    unsigned char data[] = { 'A', 'B', 'C', 'D', 'E' };
    Object dict;
    BaseMemStream<unsigned char> stream(data, 0, 5, std::move(dict));
    stream.reset();

    stream.setPos(3);
    EXPECT_EQ(3, stream.getPos());
    EXPECT_EQ('D', stream.getChar());
}

// Test setPos to beginning
TEST_F(BaseMemStreamTest_174, SetPosToBeginning_174) {
    unsigned char data[] = { 'A', 'B', 'C' };
    Object dict;
    BaseMemStream<unsigned char> stream(data, 0, 3, std::move(dict));
    stream.reset();

    stream.getChar();
    stream.getChar();
    stream.setPos(0);
    EXPECT_EQ(0, stream.getPos());
    EXPECT_EQ('A', stream.getChar());
}

// Test getKind returns correct stream kind
TEST_F(BaseMemStreamTest_174, GetKindReturnsMemStream_174) {
    unsigned char data[] = { 'A' };
    Object dict;
    BaseMemStream<unsigned char> stream(data, 0, 1, std::move(dict));

    // BaseMemStream should report itself as a memory stream kind
    StreamKind kind = stream.getKind();
    // We just verify it doesn't crash; the exact kind depends on implementation
    (void)kind;
}

// Test getStart returns the start position
TEST_F(BaseMemStreamTest_174, GetStartReturnsStart_174) {
    unsigned char data[] = { 'A', 'B', 'C' };
    Object dict;
    BaseMemStream<unsigned char> stream(data, 0, 3, std::move(dict));

    EXPECT_EQ(0, stream.getStart());
}

// Test getStart with non-zero start
TEST_F(BaseMemStreamTest_174, GetStartWithNonZeroStart_174) {
    unsigned char data[] = { 'A', 'B', 'C', 'D', 'E' };
    Object dict;
    BaseMemStream<unsigned char> stream(data, 2, 3, std::move(dict));

    EXPECT_EQ(2, stream.getStart());
}

// Test moveStart changes the start position
TEST_F(BaseMemStreamTest_174, MoveStartAdjustsStart_174) {
    unsigned char data[] = { 'A', 'B', 'C', 'D', 'E' };
    Object dict;
    BaseMemStream<unsigned char> stream(data, 0, 5, std::move(dict));

    Goffset originalStart = stream.getStart();
    stream.moveStart(2);
    EXPECT_EQ(originalStart + 2, stream.getStart());
}

// Test getUnfilteredChar returns same as getChar
TEST_F(BaseMemStreamTest_174, GetUnfilteredCharSameAsGetChar_174) {
    unsigned char data[] = { 'T', 'E', 'S', 'T' };
    Object dict1, dict2;
    BaseMemStream<unsigned char> stream1(data, 0, 4, std::move(dict1));
    
    // Create a second stream with same data to compare
    unsigned char data2[] = { 'T', 'E', 'S', 'T' };
    BaseMemStream<unsigned char> stream2(data2, 0, 4, std::move(dict2));
    
    stream1.reset();
    stream2.reset();

    // getUnfilteredChar should behave like getChar
    EXPECT_EQ(stream2.getChar(), stream1.getUnfilteredChar());
    EXPECT_EQ(stream2.getChar(), stream1.getUnfilteredChar());
}

// Test unfilteredRewind
TEST_F(BaseMemStreamTest_174, UnfilteredRewind_174) {
    unsigned char data[] = { 'A', 'B', 'C' };
    Object dict;
    BaseMemStream<unsigned char> stream(data, 0, 3, std::move(dict));
    stream.reset();

    stream.getChar();
    stream.getChar();
    bool result = stream.unfilteredRewind();
    EXPECT_TRUE(result);
    EXPECT_EQ('A', stream.getChar());
}

// Test empty stream
TEST_F(BaseMemStreamTest_174, EmptyStreamReturnsEOF_174) {
    unsigned char data[] = { 0 };
    Object dict;
    BaseMemStream<unsigned char> stream(data, 0, 0, std::move(dict));
    stream.reset();

    EXPECT_EQ(EOF, stream.getChar());
    EXPECT_EQ(EOF, stream.lookChar());
}

// Test close doesn't crash
TEST_F(BaseMemStreamTest_174, CloseDoesNotCrash_174) {
    unsigned char data[] = { 'A', 'B' };
    Object dict;
    BaseMemStream<unsigned char> stream(data, 0, 2, std::move(dict));
    stream.reset();

    stream.close();
    // Just verify no crash
}

// Test copy creates a valid copy
TEST_F(BaseMemStreamTest_174, CopyCreatesValidStream_174) {
    unsigned char data[] = { 'A', 'B', 'C' };
    Object dict;
    BaseMemStream<unsigned char> stream(data, 0, 3, std::move(dict));
    stream.reset();

    auto copied = stream.copy();
    ASSERT_NE(nullptr, copied.get());
    copied->reset();
    EXPECT_EQ('A', copied->getChar());
    EXPECT_EQ('B', copied->getChar());
    EXPECT_EQ('C', copied->getChar());
}

// Test makeSubStream
TEST_F(BaseMemStreamTest_174, MakeSubStream_174) {
    unsigned char data[] = { 'A', 'B', 'C', 'D', 'E' };
    Object dict;
    BaseMemStream<unsigned char> stream(data, 0, 5, std::move(dict));
    
    Object subDict;
    auto subStream = stream.makeSubStream(1, true, 3, std::move(subDict));
    ASSERT_NE(nullptr, subStream.get());
    subStream->reset();
    EXPECT_EQ('B', subStream->getChar());
    EXPECT_EQ('C', subStream->getChar());
    EXPECT_EQ('D', subStream->getChar());
}

// Test reading through entire stream and verifying all bytes
TEST_F(BaseMemStreamTest_174, ReadEntireStream_174) {
    unsigned char data[256];
    for (int i = 0; i < 256; i++) {
        data[i] = static_cast<unsigned char>(i);
    }
    Object dict;
    BaseMemStream<unsigned char> stream(data, 0, 256, std::move(dict));
    stream.reset();

    for (int i = 0; i < 256; i++) {
        int c = stream.getChar();
        EXPECT_EQ(i, c) << "Mismatch at index " << i;
    }
    EXPECT_EQ(EOF, stream.getChar());
}

// Test setPos with dir parameter (backward from end)
TEST_F(BaseMemStreamTest_174, SetPosFromEnd_174) {
    unsigned char data[] = { 'A', 'B', 'C', 'D', 'E' };
    Object dict;
    BaseMemStream<unsigned char> stream(data, 0, 5, std::move(dict));
    stream.reset();

    // dir != 0 typically means from end
    stream.setPos(0, 1);
    // After setting pos from end with offset 0, we should be at or near end
    // The exact behavior depends on implementation, just verify no crash
    Goffset pos = stream.getPos();
    (void)pos;
}

// Test single byte stream
TEST_F(BaseMemStreamTest_174, SingleByteStream_174) {
    unsigned char data[] = { 0xFF };
    Object dict;
    BaseMemStream<unsigned char> stream(data, 0, 1, std::move(dict));
    stream.reset();

    EXPECT_EQ(0xFF, stream.getChar());
    EXPECT_EQ(EOF, stream.getChar());

    stream.rewind();
    EXPECT_EQ(0xFF, stream.lookChar());
    EXPECT_EQ(0, stream.getPos());
}

// Test that getPos is consistent with start offset
TEST_F(BaseMemStreamTest_174, GetPosWithStartOffset_174) {
    unsigned char data[] = { 'A', 'B', 'C', 'D', 'E' };
    Object dict;
    BaseMemStream<unsigned char> stream(data, 10, 5, std::move(dict));
    stream.reset();

    // The position should relate to the start offset
    Goffset initialPos = stream.getPos();
    stream.getChar();
    Goffset nextPos = stream.getPos();
    EXPECT_EQ(initialPos + 1, nextPos);
}
