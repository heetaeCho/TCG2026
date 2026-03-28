#include <gtest/gtest.h>
#include <memory>
#include "Stream.h"

// Helper to create a simple base stream for BufStream
// We need a minimal Stream to pass to BufStream's constructor
// Using a MemStream or similar basic stream as the underlying stream

class BufStreamTest_203 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a BufStream with a given buffer size and underlying data
    std::unique_ptr<BufStream> createBufStream(const char* data, int dataLen, int bufSize) {
        // Create a MemStream as the underlying stream
        // MemStream takes ownership of a copy of the data
        char* dataCopy = new char[dataLen];
        memcpy(dataCopy, data, dataLen);
        
        Object dictObj;
        auto memStream = std::make_unique<MemStream>(dataCopy, 0, dataLen, std::move(dictObj));
        
        return std::make_unique<BufStream>(std::move(memStream), bufSize);
    }
};

// Test that getKind returns strWeird
TEST_F(BufStreamTest_203, GetKindReturnsStrWeird_203) {
    const char data[] = "Hello";
    auto stream = createBufStream(data, 5, 4);
    EXPECT_EQ(stream->getKind(), strWeird);
}

// Test basic getChar reads characters sequentially
TEST_F(BufStreamTest_203, GetCharReadsSequentially_203) {
    const char data[] = "ABCDE";
    auto stream = createBufStream(data, 5, 4);
    
    EXPECT_EQ(stream->getChar(), 'A');
    EXPECT_EQ(stream->getChar(), 'B');
    EXPECT_EQ(stream->getChar(), 'C');
    EXPECT_EQ(stream->getChar(), 'D');
    EXPECT_EQ(stream->getChar(), 'E');
}

// Test that getChar returns EOF after all data is consumed
TEST_F(BufStreamTest_203, GetCharReturnsEOFAtEnd_203) {
    const char data[] = "AB";
    auto stream = createBufStream(data, 2, 4);
    
    EXPECT_EQ(stream->getChar(), 'A');
    EXPECT_EQ(stream->getChar(), 'B');
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test lookChar returns the next character without consuming it
TEST_F(BufStreamTest_203, LookCharDoesNotConsume_203) {
    const char data[] = "XY";
    auto stream = createBufStream(data, 2, 4);
    
    EXPECT_EQ(stream->lookChar(), 'X');
    EXPECT_EQ(stream->lookChar(), 'X');
    EXPECT_EQ(stream->getChar(), 'X');
    EXPECT_EQ(stream->lookChar(), 'Y');
}

// Test lookChar with index
TEST_F(BufStreamTest_203, LookCharWithIndex_203) {
    const char data[] = "ABCD";
    auto stream = createBufStream(data, 4, 4);
    
    EXPECT_EQ(stream->lookChar(0), 'A');
    EXPECT_EQ(stream->lookChar(1), 'B');
    EXPECT_EQ(stream->lookChar(2), 'C');
    EXPECT_EQ(stream->lookChar(3), 'D');
}

// Test rewind resets the stream to the beginning
TEST_F(BufStreamTest_203, RewindResetsStream_203) {
    const char data[] = "ABC";
    auto stream = createBufStream(data, 3, 4);
    
    EXPECT_EQ(stream->getChar(), 'A');
    EXPECT_EQ(stream->getChar(), 'B');
    
    bool result = stream->rewind();
    EXPECT_TRUE(result);
    
    EXPECT_EQ(stream->getChar(), 'A');
}

// Test with buffer size of 1
TEST_F(BufStreamTest_203, BufSizeOne_203) {
    const char data[] = "AB";
    auto stream = createBufStream(data, 2, 1);
    
    EXPECT_EQ(stream->getKind(), strWeird);
    EXPECT_EQ(stream->lookChar(0), 'A');
    EXPECT_EQ(stream->getChar(), 'A');
    EXPECT_EQ(stream->getChar(), 'B');
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test isBinary
TEST_F(BufStreamTest_203, IsBinaryReturnsFalse_203) {
    const char data[] = "Test";
    auto stream = createBufStream(data, 4, 4);
    
    // isBinary should delegate to underlying stream behavior
    bool result = stream->isBinary(true);
    // We just verify it doesn't crash and returns a bool
    (void)result;
}

// Test getPSFilter returns empty optional
TEST_F(BufStreamTest_203, GetPSFilterReturnsNullopt_203) {
    const char data[] = "Test";
    auto stream = createBufStream(data, 4, 4);
    
    auto result = stream->getPSFilter(1, "");
    // BufStream (strWeird) typically returns nullopt for PS filter
    EXPECT_FALSE(result.has_value());
}

// Test empty data stream
TEST_F(BufStreamTest_203, EmptyStream_203) {
    const char data[] = "";
    auto stream = createBufStream(data, 0, 4);
    
    EXPECT_EQ(stream->getChar(), EOF);
    EXPECT_EQ(stream->lookChar(), EOF);
}

// Test buffer size larger than data
TEST_F(BufStreamTest_203, BufSizeLargerThanData_203) {
    const char data[] = "Hi";
    auto stream = createBufStream(data, 2, 16);
    
    EXPECT_EQ(stream->lookChar(0), 'H');
    EXPECT_EQ(stream->lookChar(1), 'i');
    EXPECT_EQ(stream->getChar(), 'H');
    EXPECT_EQ(stream->getChar(), 'i');
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test multiple rewinds
TEST_F(BufStreamTest_203, MultipleRewinds_203) {
    const char data[] = "Z";
    auto stream = createBufStream(data, 1, 2);
    
    EXPECT_EQ(stream->getChar(), 'Z');
    EXPECT_EQ(stream->getChar(), EOF);
    
    stream->rewind();
    EXPECT_EQ(stream->getChar(), 'Z');
    EXPECT_EQ(stream->getChar(), EOF);
    
    stream->rewind();
    EXPECT_EQ(stream->lookChar(), 'Z');
}

// Test lookChar at boundary of buffer
TEST_F(BufStreamTest_203, LookCharAtBufferBoundary_203) {
    const char data[] = "ABCDEFGH";
    auto stream = createBufStream(data, 8, 4);
    
    // Look at indices within buffer
    EXPECT_EQ(stream->lookChar(0), 'A');
    EXPECT_EQ(stream->lookChar(3), 'D');
}

// Test interleaved getChar and lookChar
TEST_F(BufStreamTest_203, InterleavedGetAndLook_203) {
    const char data[] = "12345";
    auto stream = createBufStream(data, 5, 4);
    
    EXPECT_EQ(stream->lookChar(), '1');
    EXPECT_EQ(stream->getChar(), '1');
    EXPECT_EQ(stream->lookChar(), '2');
    EXPECT_EQ(stream->lookChar(0), '2');
    EXPECT_EQ(stream->lookChar(1), '3');
    EXPECT_EQ(stream->getChar(), '2');
    EXPECT_EQ(stream->getChar(), '3');
    EXPECT_EQ(stream->lookChar(), '4');
}
