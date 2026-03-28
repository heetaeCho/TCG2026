#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"
#include "Object.h"

// We need a concrete implementation of BaseStream to test it.
// FileStream is a concrete subclass available in poppler.
// However, since we're testing BaseStream::getLength(), we can use
// any concrete subclass. Let's try to use the available concrete classes.

// Since BaseStream is abstract (has pure virtual methods from Stream),
// we need a concrete subclass. We'll use a minimal test approach
// by creating instances through available factory methods or concrete classes.

// FileStream and MemStream are concrete subclasses of BaseStream in poppler.

class BaseStreamTest_131 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getLength returns the length passed to the constructor
TEST_F(BaseStreamTest_131, GetLengthReturnsConstructedLength_131) {
    // MemStream is a concrete subclass of BaseStream
    // MemStream(const char *bufA, Goffset startA, Goffset lengthA, Object &&dictA)
    const char data[] = "Hello, World!";
    Goffset expectedLength = 13;
    Object dict;
    
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, expectedLength, std::move(dict));
    
    EXPECT_EQ(stream->getLength(), expectedLength);
}

// Test getLength with zero length
TEST_F(BaseStreamTest_131, GetLengthReturnsZeroForEmptyStream_131) {
    const char data[] = "";
    Goffset expectedLength = 0;
    Object dict;
    
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, expectedLength, std::move(dict));
    
    EXPECT_EQ(stream->getLength(), expectedLength);
}

// Test getLength with a large length value
TEST_F(BaseStreamTest_131, GetLengthReturnsLargeLength_131) {
    // We create a MemStream with a large length value
    // The actual data doesn't need to be that large for testing getLength
    char data[64] = {0};
    Goffset expectedLength = 1000000;
    Object dict;
    
    auto stream = std::make_unique<MemStream>(data, 0, expectedLength, std::move(dict));
    
    EXPECT_EQ(stream->getLength(), expectedLength);
}

// Test getLength with length of 1
TEST_F(BaseStreamTest_131, GetLengthReturnsSingleByte_131) {
    const char data[] = "A";
    Goffset expectedLength = 1;
    Object dict;
    
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, expectedLength, std::move(dict));
    
    EXPECT_EQ(stream->getLength(), expectedLength);
}

// Test that getBaseStream returns the stream itself
TEST_F(BaseStreamTest_131, GetBaseStreamReturnsSelf_131) {
    const char data[] = "Test data";
    Goffset length = 9;
    Object dict;
    
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, length, std::move(dict));
    
    EXPECT_EQ(stream->getBaseStream(), stream.get());
}

// Test that getUndecodedStream returns the stream itself for a BaseStream
TEST_F(BaseStreamTest_131, GetUndecodedStreamReturnsSelf_131) {
    const char data[] = "Test data";
    Goffset length = 9;
    Object dict;
    
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, length, std::move(dict));
    
    EXPECT_EQ(stream->getUndecodedStream(), stream.get());
}

// Test isBinary returns expected value
TEST_F(BaseStreamTest_131, IsBinaryReturnsTrue_131) {
    const char data[] = "Test data";
    Goffset length = 9;
    Object dict;
    
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, length, std::move(dict));
    
    // BaseStream::isBinary should return true by default
    EXPECT_TRUE(stream->isBinary());
}

// Test getDict with null/empty dict
TEST_F(BaseStreamTest_131, GetDictWithNullDict_131) {
    const char data[] = "Test";
    Goffset length = 4;
    Object dict;  // null/none object
    
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, length, std::move(dict));
    
    // getDict should return nullptr when dict is not a dictionary
    Dict* d = stream->getDict();
    EXPECT_EQ(d, nullptr);
}

// Test getDictObject returns a valid pointer
TEST_F(BaseStreamTest_131, GetDictObjectReturnsNonNull_131) {
    const char data[] = "Test";
    Goffset length = 4;
    Object dict;
    
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, length, std::move(dict));
    
    Object* dictObj = stream->getDictObject();
    EXPECT_NE(dictObj, nullptr);
}

// Test getStart returns the start position
TEST_F(BaseStreamTest_131, GetStartReturnsStartPosition_131) {
    const char data[] = "Hello, World!";
    Goffset start = 5;
    Goffset length = 8;
    Object dict;
    
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), start, length, std::move(dict));
    
    EXPECT_EQ(stream->getStart(), start);
}

// Test getStart with zero start
TEST_F(BaseStreamTest_131, GetStartReturnsZero_131) {
    const char data[] = "Hello";
    Object dict;
    
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, 5, std::move(dict));
    
    EXPECT_EQ(stream->getStart(), 0);
}

// Test moveStart adjusts the start position
TEST_F(BaseStreamTest_131, MoveStartAdjustsStart_131) {
    const char data[] = "Hello, World!";
    Goffset start = 0;
    Goffset length = 13;
    Object dict;
    
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), start, length, std::move(dict));
    
    Goffset delta = 5;
    stream->moveStart(delta);
    
    EXPECT_EQ(stream->getStart(), start + delta);
}

// Test getFileName returns nullptr for MemStream
TEST_F(BaseStreamTest_131, GetFileNameReturnsNullForMemStream_131) {
    const char data[] = "Test";
    Object dict;
    
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, 4, std::move(dict));
    
    EXPECT_EQ(stream->getFileName(), nullptr);
}
