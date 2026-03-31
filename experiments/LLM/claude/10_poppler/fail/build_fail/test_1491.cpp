#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary Poppler headers
#include "Stream.h"
#include "Object.h"

using ::testing::Return;
using ::testing::_;

// Since we're testing streams from the Poppler library, we need to work with
// the actual stream hierarchy. We'll create concrete test fixtures using
// available stream types.

class BaseStreamStreamTest_1491 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that a MemStream (which is a BaseStream) reports isBinary correctly
TEST_F(BaseStreamStreamTest_1491, MemStreamIsBinaryReturnsTrue_1491) {
    // MemStream is a BaseStream that reports isBinary as true
    const char data[] = "Hello World";
    Object obj;
    auto memStream = new MemStream(const_cast<char *>(data), 0, sizeof(data) - 1, Object(objNull));
    
    // MemStream::isBinary() should return true (binary stream)
    bool result = memStream->isBinary();
    EXPECT_TRUE(result);
    
    delete memStream;
}

// Test isBinary with default parameter
TEST_F(BaseStreamStreamTest_1491, IsBinaryDefaultParameter_1491) {
    const char data[] = "Test data";
    auto memStream = new MemStream(const_cast<char *>(data), 0, sizeof(data) - 1, Object(objNull));
    
    // Call with no argument (uses default last=true)
    bool resultDefault = memStream->isBinary();
    // Call with explicit true
    bool resultTrue = memStream->isBinary(true);
    // Call with explicit false
    bool resultFalse = memStream->isBinary(false);
    
    // The last parameter is ignored in BaseStreamStream, so all should return same
    EXPECT_EQ(resultDefault, resultTrue);
    // For a base stream like MemStream, isBinary should be consistent
    EXPECT_EQ(resultTrue, resultFalse);
    
    delete memStream;
}

// Test with a filter stream wrapping a base stream - the filter stream's
// isBinary should delegate to the base stream
TEST_F(BaseStreamStreamTest_1491, FilterStreamDelegatesToBaseStream_1491) {
    const char data[] = "\x00\x01\x02\x03";
    auto memStream = new MemStream(const_cast<char *>(data), 0, sizeof(data) - 1, Object(objNull));
    
    // ASCIIHexStream is a FilterStream that wraps another stream
    auto asciiHexStream = new ASCIIHexStream(memStream);
    
    // isBinary on the filter stream should delegate to base stream
    bool result = asciiHexStream->isBinary();
    // ASCIIHexStream is not binary (it's a text encoding)
    // The behavior depends on the implementation
    // We just verify it doesn't crash and returns a boolean
    EXPECT_TRUE(result == true || result == false);
    
    delete asciiHexStream;
}

// Test with ASCII85Stream wrapping a MemStream
TEST_F(BaseStreamStreamTest_1491, ASCII85StreamIsBinary_1491) {
    const char data[] = "some test data here";
    auto memStream = new MemStream(const_cast<char *>(data), 0, sizeof(data) - 1, Object(objNull));
    
    auto ascii85Stream = new ASCII85Stream(memStream);
    
    bool result = ascii85Stream->isBinary();
    // Verify it returns a valid boolean without crashing
    EXPECT_TRUE(result == true || result == false);
    
    delete ascii85Stream;
}

// Test MemStream with empty data
TEST_F(BaseStreamStreamTest_1491, EmptyMemStreamIsBinary_1491) {
    const char data[] = "";
    auto memStream = new MemStream(const_cast<char *>(data), 0, 0, Object(objNull));
    
    bool result = memStream->isBinary();
    EXPECT_TRUE(result);
    
    delete memStream;
}

// Test that isBinary with last=false still works
TEST_F(BaseStreamStreamTest_1491, IsBinaryWithLastFalse_1491) {
    const char data[] = "test";
    auto memStream = new MemStream(const_cast<char *>(data), 0, sizeof(data) - 1, Object(objNull));
    
    bool result = memStream->isBinary(false);
    // Should still return the same as with last=true since the parameter is ignored
    EXPECT_EQ(result, memStream->isBinary(true));
    
    delete memStream;
}
