#include <gtest/gtest.h>
#include <memory>
#include "Stream.h"
#include "Object.h"

// Type alias for convenience
using MemStream = BaseMemStream<const unsigned char>;

class BaseMemStreamTest_165 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize a buffer with known data
        for (int i = 0; i < 256; i++) {
            buffer[i] = static_cast<unsigned char>(i);
        }
    }

    unsigned char buffer[256];
};

// Test makeSubStream with limited=true and lengthA within bounds
TEST_F(BaseMemStreamTest_165, MakeSubStream_LimitedWithinBounds_165) {
    Object dict;
    auto stream = std::make_unique<MemStream>(buffer, 0, 256, Object());
    
    auto subStream = stream->makeSubStream(10, true, 50, Object());
    ASSERT_NE(subStream, nullptr);
    
    // The sub-stream should start at offset 10 and have length 50
    subStream->rewind();
    // Read first byte - should be buffer[10] = 10
    int ch = subStream->getChar();
    EXPECT_EQ(ch, 10);
}

// Test makeSubStream with limited=true but startA + lengthA exceeds start + length
TEST_F(BaseMemStreamTest_165, MakeSubStream_LimitedExceedsBounds_165) {
    Object dict;
    auto stream = std::make_unique<MemStream>(buffer, 0, 100, Object());
    
    // startA=50, lengthA=200 => 50+200=250 > 0+100=100, so newLength = 100 - 50 = 50
    auto subStream = stream->makeSubStream(50, true, 200, Object());
    ASSERT_NE(subStream, nullptr);
    
    subStream->rewind();
    int ch = subStream->getChar();
    EXPECT_EQ(ch, static_cast<int>(buffer[50]));
}

// Test makeSubStream with limited=false (unlimited)
TEST_F(BaseMemStreamTest_165, MakeSubStream_Unlimited_165) {
    Object dict;
    auto stream = std::make_unique<MemStream>(buffer, 0, 256, Object());
    
    // limited=false => newLength = start + length - startA = 0 + 256 - 10 = 246
    auto subStream = stream->makeSubStream(10, false, 0, Object());
    ASSERT_NE(subStream, nullptr);
    
    subStream->rewind();
    int ch = subStream->getChar();
    EXPECT_EQ(ch, 10);
}

// Test makeSubStream starting at offset 0 with full length
TEST_F(BaseMemStreamTest_165, MakeSubStream_FullRange_165) {
    auto stream = std::make_unique<MemStream>(buffer, 0, 256, Object());
    
    auto subStream = stream->makeSubStream(0, true, 256, Object());
    ASSERT_NE(subStream, nullptr);
    
    subStream->rewind();
    int ch = subStream->getChar();
    EXPECT_EQ(ch, 0);
}

// Test makeSubStream with zero length when limited
TEST_F(BaseMemStreamTest_165, MakeSubStream_ZeroLength_165) {
    auto stream = std::make_unique<MemStream>(buffer, 0, 256, Object());
    
    auto subStream = stream->makeSubStream(0, true, 0, Object());
    ASSERT_NE(subStream, nullptr);
    
    // With zero length, reading should return EOF
    subStream->rewind();
    int ch = subStream->getChar();
    EXPECT_EQ(ch, EOF);
}

// Test makeSubStream with startA equal to start + length (boundary)
TEST_F(BaseMemStreamTest_165, MakeSubStream_StartAtEnd_165) {
    auto stream = std::make_unique<MemStream>(buffer, 0, 100, Object());
    
    // startA=100, limited=false => newLength = 0 + 100 - 100 = 0
    auto subStream = stream->makeSubStream(100, false, 50, Object());
    ASSERT_NE(subStream, nullptr);
    
    subStream->rewind();
    int ch = subStream->getChar();
    EXPECT_EQ(ch, EOF);
}

// Test makeSubStream with limited=true and exact boundary (startA + lengthA == start + length)
TEST_F(BaseMemStreamTest_165, MakeSubStream_ExactBoundary_165) {
    auto stream = std::make_unique<MemStream>(buffer, 0, 100, Object());
    
    // startA=50, lengthA=50 => 50+50 = 100 = 0+100, so not > start+length
    // Therefore newLength = lengthA = 50
    auto subStream = stream->makeSubStream(50, true, 50, Object());
    ASSERT_NE(subStream, nullptr);
    
    subStream->rewind();
    int ch = subStream->getChar();
    EXPECT_EQ(ch, 50);
}

// Test makeSubStream with a non-zero start offset of the original stream
TEST_F(BaseMemStreamTest_165, MakeSubStream_NonZeroStart_165) {
    // Create a stream starting at offset 20 with length 100
    auto stream = std::make_unique<MemStream>(buffer, 20, 100, Object());
    
    // limited=true, startA=30, lengthA=50 => 30+50=80 < 20+100=120 => newLength = 50
    auto subStream = stream->makeSubStream(30, true, 50, Object());
    ASSERT_NE(subStream, nullptr);
    
    subStream->rewind();
    int ch = subStream->getChar();
    EXPECT_EQ(ch, static_cast<int>(buffer[30]));
}

// Test makeSubStream with non-zero start where sub exceeds bounds
TEST_F(BaseMemStreamTest_165, MakeSubStream_NonZeroStartExceedsBounds_165) {
    // Stream at offset 20, length 100 => covers [20, 120)
    auto stream = std::make_unique<MemStream>(buffer, 20, 100, Object());
    
    // startA=100, lengthA=50 => 100+50=150 > 20+100=120 => newLength = 120 - 100 = 20
    auto subStream = stream->makeSubStream(100, true, 50, Object());
    ASSERT_NE(subStream, nullptr);
    
    subStream->rewind();
    int ch = subStream->getChar();
    EXPECT_EQ(ch, static_cast<int>(buffer[100]));
}

// Test that multiple bytes can be read from the sub-stream
TEST_F(BaseMemStreamTest_165, MakeSubStream_ReadMultipleBytes_165) {
    auto stream = std::make_unique<MemStream>(buffer, 0, 256, Object());
    
    auto subStream = stream->makeSubStream(5, true, 10, Object());
    ASSERT_NE(subStream, nullptr);
    
    subStream->rewind();
    for (int i = 0; i < 10; i++) {
        int ch = subStream->getChar();
        EXPECT_EQ(ch, 5 + i) << "Mismatch at position " << i;
    }
    // After reading 10 bytes, should get EOF
    int ch = subStream->getChar();
    EXPECT_EQ(ch, EOF);
}

// Test makeSubStream returns a stream of correct kind
TEST_F(BaseMemStreamTest_165, MakeSubStream_StreamKind_165) {
    auto stream = std::make_unique<MemStream>(buffer, 0, 256, Object());
    
    auto subStream = stream->makeSubStream(0, true, 100, Object());
    ASSERT_NE(subStream, nullptr);
    
    // The returned stream should be a BaseMemStream, check its kind
    EXPECT_EQ(subStream->getKind(), strWeird);
}

// Test makeSubStream with limited=false ignores lengthA parameter
TEST_F(BaseMemStreamTest_165, MakeSubStream_UnlimitedIgnoresLength_165) {
    auto stream = std::make_unique<MemStream>(buffer, 0, 256, Object());
    
    // Two sub-streams with different lengthA but both unlimited
    auto sub1 = stream->makeSubStream(10, false, 0, Object());
    auto sub2 = stream->makeSubStream(10, false, 999, Object());
    
    ASSERT_NE(sub1, nullptr);
    ASSERT_NE(sub2, nullptr);
    
    // Both should behave identically since limited=false
    sub1->rewind();
    sub2->rewind();
    
    for (int i = 0; i < 246; i++) {
        int ch1 = sub1->getChar();
        int ch2 = sub2->getChar();
        EXPECT_EQ(ch1, ch2) << "Mismatch at position " << i;
    }
}

// Test makeSubStream with startA at 0 and limited with small length
TEST_F(BaseMemStreamTest_165, MakeSubStream_SmallSubStream_165) {
    auto stream = std::make_unique<MemStream>(buffer, 0, 256, Object());
    
    auto subStream = stream->makeSubStream(0, true, 1, Object());
    ASSERT_NE(subStream, nullptr);
    
    subStream->rewind();
    int ch = subStream->getChar();
    EXPECT_EQ(ch, 0);
    ch = subStream->getChar();
    EXPECT_EQ(ch, EOF);
}

// Test that the original stream is unaffected by making a sub-stream
TEST_F(BaseMemStreamTest_165, MakeSubStream_OriginalUnaffected_165) {
    auto stream = std::make_unique<MemStream>(buffer, 0, 256, Object());
    
    stream->rewind();
    int originalFirst = stream->getChar();
    
    // Make a sub-stream
    auto subStream = stream->makeSubStream(50, true, 50, Object());
    
    // Original stream should still work from where it was
    stream->rewind();
    int ch = stream->getChar();
    EXPECT_EQ(ch, originalFirst);
}

// Test getLength on original stream
TEST_F(BaseMemStreamTest_165, GetLength_165) {
    auto stream = std::make_unique<MemStream>(buffer, 0, 256, Object());
    EXPECT_EQ(stream->getLength(), 256);
}

// Test getStart on original stream
TEST_F(BaseMemStreamTest_165, GetStart_165) {
    auto stream = std::make_unique<MemStream>(buffer, 10, 100, Object());
    EXPECT_EQ(stream->getStart(), 10);
}

// Test rewind and getPos
TEST_F(BaseMemStreamTest_165, RewindAndGetPos_165) {
    auto stream = std::make_unique<MemStream>(buffer, 0, 256, Object());
    stream->rewind();
    EXPECT_EQ(stream->getPos(), 0);
    
    stream->getChar();
    EXPECT_EQ(stream->getPos(), 1);
}

// Test copy method
TEST_F(BaseMemStreamTest_165, Copy_165) {
    auto stream = std::make_unique<MemStream>(buffer, 0, 256, Object());
    auto copied = stream->copy();
    ASSERT_NE(copied, nullptr);
    
    copied->rewind();
    int ch = copied->getChar();
    EXPECT_EQ(ch, 0);
}

// Test lookChar doesn't advance position
TEST_F(BaseMemStreamTest_165, LookChar_165) {
    auto stream = std::make_unique<MemStream>(buffer, 0, 256, Object());
    stream->rewind();
    
    int looked = stream->lookChar();
    Goffset posAfterLook = stream->getPos();
    EXPECT_EQ(looked, 0);
    EXPECT_EQ(posAfterLook, 0);
    
    int got = stream->getChar();
    EXPECT_EQ(got, looked);
    EXPECT_EQ(stream->getPos(), 1);
}

// Test moveStart
TEST_F(BaseMemStreamTest_165, MoveStart_165) {
    auto stream = std::make_unique<MemStream>(buffer, 0, 256, Object());
    Goffset originalStart = stream->getStart();
    
    stream->moveStart(10);
    EXPECT_EQ(stream->getStart(), originalStart + 10);
}

// Test setPos
TEST_F(BaseMemStreamTest_165, SetPos_165) {
    auto stream = std::make_unique<MemStream>(buffer, 0, 256, Object());
    stream->setPos(50);
    EXPECT_EQ(stream->getPos(), 50);
    
    int ch = stream->getChar();
    EXPECT_EQ(ch, 50);
}

// Test close and then operations (stream should still be usable after close for mem stream)
TEST_F(BaseMemStreamTest_165, Close_165) {
    auto stream = std::make_unique<MemStream>(buffer, 0, 256, Object());
    stream->rewind();
    stream->close();
    // After close, rewind should still work for memory streams
    stream->rewind();
    int ch = stream->getChar();
    EXPECT_EQ(ch, 0);
}
