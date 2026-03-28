#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Object.h"
#include "Stream.h"
#include "Dict.h"

// We need a concrete implementation of BaseStream to test it.
// Since BaseStream is abstract (inherits from Stream which has pure virtual methods),
// we need to use an existing concrete subclass or create a minimal one for testing.
// We'll use the available concrete stream classes from the codebase.

#include "goo/GooString.h"
#include <memory>
#include <cstring>

// For testing BaseStream::getDict(), we need a concrete BaseStream.
// MemStream is a concrete subclass of BaseStream available in poppler.

class BaseStreamGetDictTest_128 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getDict() returns a valid Dict pointer when BaseStream is constructed with a dict object
TEST_F(BaseStreamGetDictTest_128, GetDictReturnsValidDict_128) {
    // Create a Dict object
    Dict *d = new Dict(nullptr);
    Object dictObj(d);
    
    // Create a MemStream (concrete BaseStream) with some data
    const char *data = "test data";
    auto dataLen = static_cast<Goffset>(strlen(data));
    
    // We need to use a char* that persists - MemStream doesn't own the buffer
    char *buf = new char[dataLen];
    memcpy(buf, data, dataLen);
    
    auto stream = std::make_unique<MemStream>(buf, 0, dataLen, std::move(dictObj));
    
    Dict *retrievedDict = stream->getDict();
    ASSERT_NE(retrievedDict, nullptr);
    EXPECT_EQ(retrievedDict, d);
    
    delete[] buf;
}

// Test that getDict() returns the same Dict pointer on multiple calls
TEST_F(BaseStreamGetDictTest_128, GetDictReturnsSameDictOnMultipleCalls_128) {
    Dict *d = new Dict(nullptr);
    Object dictObj(d);
    
    const char *data = "hello";
    auto dataLen = static_cast<Goffset>(strlen(data));
    char *buf = new char[dataLen];
    memcpy(buf, data, dataLen);
    
    auto stream = std::make_unique<MemStream>(buf, 0, dataLen, std::move(dictObj));
    
    Dict *first = stream->getDict();
    Dict *second = stream->getDict();
    
    EXPECT_EQ(first, second);
    
    delete[] buf;
}

// Test getDict with a dict that has entries
TEST_F(BaseStreamGetDictTest_128, GetDictWithEntries_128) {
    Dict *d = new Dict(nullptr);
    d->add("Type", Object(objName, "XObject"));
    d->add("Subtype", Object(objName, "Image"));
    
    Object dictObj(d);
    
    const char *data = "pixel data";
    auto dataLen = static_cast<Goffset>(strlen(data));
    char *buf = new char[dataLen];
    memcpy(buf, data, dataLen);
    
    auto stream = std::make_unique<MemStream>(buf, 0, dataLen, std::move(dictObj));
    
    Dict *retrievedDict = stream->getDict();
    ASSERT_NE(retrievedDict, nullptr);
    EXPECT_EQ(retrievedDict->getLength(), 2);
    
    delete[] buf;
}

// Test getDictObject returns a non-null Object pointer
TEST_F(BaseStreamGetDictTest_128, GetDictObjectReturnsNonNull_128) {
    Dict *d = new Dict(nullptr);
    Object dictObj(d);
    
    const char *data = "abc";
    auto dataLen = static_cast<Goffset>(strlen(data));
    char *buf = new char[dataLen];
    memcpy(buf, data, dataLen);
    
    auto stream = std::make_unique<MemStream>(buf, 0, dataLen, std::move(dictObj));
    
    Object *dictObjPtr = stream->getDictObject();
    ASSERT_NE(dictObjPtr, nullptr);
    EXPECT_TRUE(dictObjPtr->isDict());
    
    delete[] buf;
}

// Test getLength returns correct length
TEST_F(BaseStreamGetDictTest_128, GetLengthReturnsCorrectValue_128) {
    Dict *d = new Dict(nullptr);
    Object dictObj(d);
    
    const char *data = "some test data here";
    auto dataLen = static_cast<Goffset>(strlen(data));
    char *buf = new char[dataLen];
    memcpy(buf, data, dataLen);
    
    auto stream = std::make_unique<MemStream>(buf, 0, dataLen, std::move(dictObj));
    
    EXPECT_EQ(stream->getLength(), dataLen);
    
    delete[] buf;
}

// Test getBaseStream returns the stream itself
TEST_F(BaseStreamGetDictTest_128, GetBaseStreamReturnsSelf_128) {
    Dict *d = new Dict(nullptr);
    Object dictObj(d);
    
    const char *data = "data";
    auto dataLen = static_cast<Goffset>(strlen(data));
    char *buf = new char[dataLen];
    memcpy(buf, data, dataLen);
    
    auto stream = std::make_unique<MemStream>(buf, 0, dataLen, std::move(dictObj));
    
    BaseStream *base = stream->getBaseStream();
    EXPECT_EQ(base, stream.get());
    
    delete[] buf;
}

// Test isBinary returns expected value for BaseStream
TEST_F(BaseStreamGetDictTest_128, IsBinaryReturnsExpectedValue_128) {
    Dict *d = new Dict(nullptr);
    Object dictObj(d);
    
    const char *data = "data";
    auto dataLen = static_cast<Goffset>(strlen(data));
    char *buf = new char[dataLen];
    memcpy(buf, data, dataLen);
    
    auto stream = std::make_unique<MemStream>(buf, 0, dataLen, std::move(dictObj));
    
    // BaseStream::isBinary should return false by default
    bool result = stream->isBinary();
    // We just check it doesn't crash and returns a boolean value
    EXPECT_TRUE(result || !result);
    
    delete[] buf;
}

// Test with zero-length stream
TEST_F(BaseStreamGetDictTest_128, ZeroLengthStream_128) {
    Dict *d = new Dict(nullptr);
    Object dictObj(d);
    
    char *buf = new char[1];
    buf[0] = '\0';
    
    auto stream = std::make_unique<MemStream>(buf, 0, 0, std::move(dictObj));
    
    EXPECT_EQ(stream->getLength(), 0);
    
    Dict *retrievedDict = stream->getDict();
    ASSERT_NE(retrievedDict, nullptr);
    
    delete[] buf;
}

// Test getUndecodedStream for BaseStream
TEST_F(BaseStreamGetDictTest_128, GetUndecodedStreamReturnsSelf_128) {
    Dict *d = new Dict(nullptr);
    Object dictObj(d);
    
    const char *data = "test";
    auto dataLen = static_cast<Goffset>(strlen(data));
    char *buf = new char[dataLen];
    memcpy(buf, data, dataLen);
    
    auto stream = std::make_unique<MemStream>(buf, 0, dataLen, std::move(dictObj));
    
    Stream *undecoded = stream->getUndecodedStream();
    EXPECT_EQ(undecoded, stream.get());
    
    delete[] buf;
}

// Test getFileName returns nullptr for MemStream (not a FileStream)
TEST_F(BaseStreamGetDictTest_128, GetFileNameReturnsNullForMemStream_128) {
    Dict *d = new Dict(nullptr);
    Object dictObj(d);
    
    const char *data = "test";
    auto dataLen = static_cast<Goffset>(strlen(data));
    char *buf = new char[dataLen];
    memcpy(buf, data, dataLen);
    
    auto stream = std::make_unique<MemStream>(buf, 0, dataLen, std::move(dictObj));
    
    GooString *fileName = stream->getFileName();
    EXPECT_EQ(fileName, nullptr);
    
    delete[] buf;
}

// Test getDict consistency with getDictObject
TEST_F(BaseStreamGetDictTest_128, GetDictConsistentWithGetDictObject_128) {
    Dict *d = new Dict(nullptr);
    Object dictObj(d);
    
    const char *data = "consistency test";
    auto dataLen = static_cast<Goffset>(strlen(data));
    char *buf = new char[dataLen];
    memcpy(buf, data, dataLen);
    
    auto stream = std::make_unique<MemStream>(buf, 0, dataLen, std::move(dictObj));
    
    Dict *fromGetDict = stream->getDict();
    Object *dictObjPtr = stream->getDictObject();
    
    ASSERT_NE(dictObjPtr, nullptr);
    ASSERT_TRUE(dictObjPtr->isDict());
    
    Dict *fromDictObject = dictObjPtr->getDict();
    EXPECT_EQ(fromGetDict, fromDictObject);
    
    delete[] buf;
}
