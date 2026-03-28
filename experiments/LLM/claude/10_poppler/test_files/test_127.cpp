#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler/Stream.h"
#include "poppler/Object.h"

// We need a concrete implementation of BaseStream to test it.
// FileStream is a concrete subclass available in poppler.
#include "poppler/Stream.h"
#include <cstring>
#include <memory>
#include <sstream>

// Since BaseStream is abstract, we need to use a concrete subclass.
// We'll use MemStream which is a concrete BaseStream in poppler.

class BaseStreamTest_127 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getUndecodedStream returns this (the BaseStream itself)
TEST_F(BaseStreamTest_127, GetUndecodedStreamReturnsSelf_127) {
    // Create a MemStream as a concrete BaseStream
    const char *data = "Hello, World!";
    auto len = static_cast<Goffset>(strlen(data));
    Object dictObj(objNull);
    
    // MemStream takes ownership-like semantics; data must persist
    char *buf = new char[len];
    memcpy(buf, data, len);
    
    MemStream *memStream = new MemStream(buf, 0, len, std::move(dictObj));
    
    // getUndecodedStream should return this
    Stream *undecoded = memStream->getUndecodedStream();
    EXPECT_EQ(undecoded, memStream);
    
    delete memStream;
    delete[] buf;
}

// Test that getBaseStream returns this
TEST_F(BaseStreamTest_127, GetBaseStreamReturnsSelf_127) {
    const char *data = "Test data";
    auto len = static_cast<Goffset>(strlen(data));
    Object dictObj(objNull);
    
    char *buf = new char[len];
    memcpy(buf, data, len);
    
    MemStream *memStream = new MemStream(buf, 0, len, std::move(dictObj));
    
    BaseStream *base = memStream->getBaseStream();
    EXPECT_EQ(base, memStream);
    
    delete memStream;
    delete[] buf;
}

// Test getLength returns the correct length
TEST_F(BaseStreamTest_127, GetLengthReturnsCorrectLength_127) {
    const char *data = "Hello, World!";
    Goffset len = static_cast<Goffset>(strlen(data));
    Object dictObj(objNull);
    
    char *buf = new char[len];
    memcpy(buf, data, len);
    
    MemStream *memStream = new MemStream(buf, 0, len, std::move(dictObj));
    
    EXPECT_EQ(memStream->getLength(), len);
    
    delete memStream;
    delete[] buf;
}

// Test getLength with zero length
TEST_F(BaseStreamTest_127, GetLengthZero_127) {
    Object dictObj(objNull);
    char *buf = new char[1]; // Need at least some buffer
    buf[0] = '\0';
    
    MemStream *memStream = new MemStream(buf, 0, 0, std::move(dictObj));
    
    EXPECT_EQ(memStream->getLength(), 0);
    
    delete memStream;
    delete[] buf;
}

// Test isBinary returns expected value
TEST_F(BaseStreamTest_127, IsBinaryDefault_127) {
    const char *data = "Some data";
    Goffset len = static_cast<Goffset>(strlen(data));
    Object dictObj(objNull);
    
    char *buf = new char[len];
    memcpy(buf, data, len);
    
    MemStream *memStream = new MemStream(buf, 0, len, std::move(dictObj));
    
    // isBinary should return a bool
    bool result = memStream->isBinary();
    // BaseStream::isBinary returns true for last=true
    EXPECT_TRUE(result);
    
    delete memStream;
    delete[] buf;
}

// Test getStart returns expected start position
TEST_F(BaseStreamTest_127, GetStartReturnsStart_127) {
    const char *data = "Hello, World!";
    Goffset len = static_cast<Goffset>(strlen(data));
    Object dictObj(objNull);
    
    char *buf = new char[len];
    memcpy(buf, data, len);
    
    Goffset startPos = 5;
    MemStream *memStream = new MemStream(buf, startPos, len - startPos, std::move(dictObj));
    
    EXPECT_EQ(memStream->getStart(), startPos);
    
    delete memStream;
    delete[] buf;
}

// Test getFileName returns nullptr for MemStream
TEST_F(BaseStreamTest_127, GetFileNameReturnsNull_127) {
    const char *data = "data";
    Goffset len = static_cast<Goffset>(strlen(data));
    Object dictObj(objNull);
    
    char *buf = new char[len];
    memcpy(buf, data, len);
    
    MemStream *memStream = new MemStream(buf, 0, len, std::move(dictObj));
    
    GooString *fileName = memStream->getFileName();
    EXPECT_EQ(fileName, nullptr);
    
    delete memStream;
    delete[] buf;
}

// Test getDictObject returns a valid pointer
TEST_F(BaseStreamTest_127, GetDictObjectReturnsNonNull_127) {
    const char *data = "data";
    Goffset len = static_cast<Goffset>(strlen(data));
    Object dictObj(objNull);
    
    char *buf = new char[len];
    memcpy(buf, data, len);
    
    MemStream *memStream = new MemStream(buf, 0, len, std::move(dictObj));
    
    Object *obj = memStream->getDictObject();
    EXPECT_NE(obj, nullptr);
    
    delete memStream;
    delete[] buf;
}

// Test moveStart adjusts the start position
TEST_F(BaseStreamTest_127, MoveStartAdjustsStart_127) {
    const char *data = "Hello, World!";
    Goffset len = static_cast<Goffset>(strlen(data));
    Object dictObj(objNull);
    
    char *buf = new char[len];
    memcpy(buf, data, len);
    
    MemStream *memStream = new MemStream(buf, 0, len, std::move(dictObj));
    
    Goffset originalStart = memStream->getStart();
    Goffset delta = 3;
    memStream->moveStart(delta);
    
    EXPECT_EQ(memStream->getStart(), originalStart + delta);
    
    delete memStream;
    delete[] buf;
}

// Test that getUndecodedStream and getBaseStream return consistent pointers
TEST_F(BaseStreamTest_127, UndecodedAndBaseStreamConsistent_127) {
    const char *data = "consistency test";
    Goffset len = static_cast<Goffset>(strlen(data));
    Object dictObj(objNull);
    
    char *buf = new char[len];
    memcpy(buf, data, len);
    
    MemStream *memStream = new MemStream(buf, 0, len, std::move(dictObj));
    
    Stream *undecoded = memStream->getUndecodedStream();
    BaseStream *base = memStream->getBaseStream();
    
    // Both should point to the same object
    EXPECT_EQ(static_cast<Stream*>(base), undecoded);
    
    delete memStream;
    delete[] buf;
}

// Test with large data
TEST_F(BaseStreamTest_127, LargeDataLength_127) {
    Goffset len = 100000;
    Object dictObj(objNull);
    
    char *buf = new char[len];
    memset(buf, 'A', len);
    
    MemStream *memStream = new MemStream(buf, 0, len, std::move(dictObj));
    
    EXPECT_EQ(memStream->getLength(), len);
    
    Stream *undecoded = memStream->getUndecodedStream();
    EXPECT_EQ(undecoded, memStream);
    
    delete memStream;
    delete[] buf;
}

// Test setPos and reading behavior
TEST_F(BaseStreamTest_127, SetPosFromBeginning_127) {
    const char *data = "ABCDEFGHIJ";
    Goffset len = static_cast<Goffset>(strlen(data));
    Object dictObj(objNull);
    
    char *buf = new char[len];
    memcpy(buf, data, len);
    
    MemStream *memStream = new MemStream(buf, 0, len, std::move(dictObj));
    memStream->reset();
    
    // Set position to 5 from start
    memStream->setPos(5, 0);
    
    int ch = memStream->getChar();
    EXPECT_EQ(ch, 'F');
    
    delete memStream;
    delete[] buf;
}

// Test setPos from end
TEST_F(BaseStreamTest_127, SetPosFromEnd_127) {
    const char *data = "ABCDEFGHIJ";
    Goffset len = static_cast<Goffset>(strlen(data));
    Object dictObj(objNull);
    
    char *buf = new char[len];
    memcpy(buf, data, len);
    
    MemStream *memStream = new MemStream(buf, 0, len, std::move(dictObj));
    memStream->reset();
    
    // Set position from end (dir != 0 means from end)
    memStream->setPos(3, -1);
    
    int ch = memStream->getChar();
    // Position from end: len - 3 = 7, so 'H'
    EXPECT_EQ(ch, 'H');
    
    delete memStream;
    delete[] buf;
}
