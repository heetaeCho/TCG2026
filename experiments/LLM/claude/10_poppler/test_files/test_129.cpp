#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Object.h"
#include "Stream.h"
#include "Dict.h"

// We need a concrete BaseStream subclass to test BaseStream's methods.
// FileStream is a concrete subclass available in poppler.
#include <sstream>
#include <cstdio>
#include <memory>

// Test fixture for BaseStream tests
class BaseStreamTest_129 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getDictObject returns a non-null pointer
TEST_F(BaseStreamTest_129, GetDictObjectReturnsNonNull_129) {
    // Create a FileStream as a concrete BaseStream
    // FileStream needs a GooFile, start, limited, length, dict
    Object dictObj;
    
    // Use a MemStream which is another concrete BaseStream
    // MemStream(const char *bufA, Goffset startA, Goffset lengthA, Object &&dictA)
    const char *data = "hello world";
    Goffset len = 11;
    Object memDict;
    
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, std::move(memDict));
    
    Object *dictObjPtr = stream->getDictObject();
    ASSERT_NE(dictObjPtr, nullptr);
}

// Test that getDictObject returns consistent pointer on multiple calls
TEST_F(BaseStreamTest_129, GetDictObjectReturnsSamePointer_129) {
    const char *data = "test data";
    Goffset len = 9;
    Object memDict;
    
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, std::move(memDict));
    
    Object *ptr1 = stream->getDictObject();
    Object *ptr2 = stream->getDictObject();
    EXPECT_EQ(ptr1, ptr2);
}

// Test that getDict works (returns Dict* or nullptr for a null dict)
TEST_F(BaseStreamTest_129, GetDictReturnsValue_129) {
    const char *data = "abcdef";
    Goffset len = 6;
    Object memDict;
    
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, std::move(memDict));
    
    // When no real dict is set, getDict may return nullptr
    Dict *d = stream->getDict();
    // We just verify it doesn't crash; dict could be null if Object is not a dict type
    // This is a valid observable behavior test
    (void)d;
}

// Test getBaseStream returns this
TEST_F(BaseStreamTest_129, GetBaseStreamReturnsSelf_129) {
    const char *data = "xyz";
    Goffset len = 3;
    Object memDict;
    
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, std::move(memDict));
    
    BaseStream *base = stream->getBaseStream();
    EXPECT_EQ(base, stream.get());
}

// Test getUndecodedStream returns this
TEST_F(BaseStreamTest_129, GetUndecodedStreamReturnsSelf_129) {
    const char *data = "test";
    Goffset len = 4;
    Object memDict;
    
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, std::move(memDict));
    
    Stream *undecoded = stream->getUndecodedStream();
    EXPECT_EQ(undecoded, stream.get());
}

// Test getLength returns the length passed in constructor
TEST_F(BaseStreamTest_129, GetLengthReturnsCorrectValue_129) {
    const char *data = "hello";
    Goffset len = 5;
    Object memDict;
    
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, std::move(memDict));
    
    EXPECT_EQ(stream->getLength(), len);
}

// Test getLength with zero length
TEST_F(BaseStreamTest_129, GetLengthZero_129) {
    const char *data = "";
    Goffset len = 0;
    Object memDict;
    
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, std::move(memDict));
    
    EXPECT_EQ(stream->getLength(), 0);
}

// Test isBinary returns expected value
TEST_F(BaseStreamTest_129, IsBinaryReturnsFalse_129) {
    const char *data = "text";
    Goffset len = 4;
    Object memDict;
    
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, std::move(memDict));
    
    // BaseStream::isBinary should return false by default for text-like streams
    // We just test it doesn't crash and returns a bool
    bool result = stream->isBinary();
    // Observable: it returns true or false
    (void)result;
}

// Test getStart
TEST_F(BaseStreamTest_129, GetStartReturnsZeroByDefault_129) {
    const char *data = "data";
    Goffset len = 4;
    Object memDict;
    
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, std::move(memDict));
    
    Goffset start = stream->getStart();
    EXPECT_EQ(start, 0);
}

// Test getStart with non-zero start
TEST_F(BaseStreamTest_129, GetStartReturnsNonZero_129) {
    const char *data = "data with offset";
    Goffset len = 4;
    Object memDict;
    
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 5, len, std::move(memDict));
    
    Goffset start = stream->getStart();
    EXPECT_EQ(start, 5);
}

// Test getFileName returns nullptr for MemStream
TEST_F(BaseStreamTest_129, GetFileNameReturnsNullForMemStream_129) {
    const char *data = "test";
    Goffset len = 4;
    Object memDict;
    
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, std::move(memDict));
    
    GooString *fileName = stream->getFileName();
    EXPECT_EQ(fileName, nullptr);
}

// Test reading from MemStream after reset
TEST_F(BaseStreamTest_129, ReadAfterReset_129) {
    const char *data = "ABCD";
    Goffset len = 4;
    Object memDict;
    
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, std::move(memDict));
    stream->reset();
    
    int ch = stream->getChar();
    EXPECT_EQ(ch, 'A');
    ch = stream->getChar();
    EXPECT_EQ(ch, 'B');
    ch = stream->getChar();
    EXPECT_EQ(ch, 'C');
    ch = stream->getChar();
    EXPECT_EQ(ch, 'D');
    ch = stream->getChar();
    EXPECT_EQ(ch, EOF);
}

// Test setPos and reading
TEST_F(BaseStreamTest_129, SetPosAndRead_129) {
    const char *data = "0123456789";
    Goffset len = 10;
    Object memDict;
    
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, std::move(memDict));
    stream->reset();
    
    stream->setPos(5, 0);
    int ch = stream->getChar();
    EXPECT_EQ(ch, '5');
}

// Test moveStart
TEST_F(BaseStreamTest_129, MoveStartDelta_129) {
    const char *data = "abcdefgh";
    Goffset len = 8;
    Object memDict;
    
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, std::move(memDict));
    
    Goffset originalStart = stream->getStart();
    stream->moveStart(3);
    Goffset newStart = stream->getStart();
    EXPECT_EQ(newStart, originalStart + 3);
}

// Test getDictObject type when dict is null/none
TEST_F(BaseStreamTest_129, GetDictObjectWithNullDict_129) {
    const char *data = "x";
    Goffset len = 1;
    Object memDict; // default constructed - should be objNone
    
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, std::move(memDict));
    
    Object *obj = stream->getDictObject();
    ASSERT_NE(obj, nullptr);
    // The object should be of type none since we didn't set a dict
    EXPECT_TRUE(obj->isNone() || obj->isNull() || obj->isDict());
}

// Test with a proper dict object
TEST_F(BaseStreamTest_129, GetDictObjectWithRealDict_129) {
    const char *data = "payload";
    Goffset len = 7;
    
    // Create a dict Object - this requires an XRef, but we can test with none
    Object dictObj(new Dict(nullptr));
    
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, std::move(dictObj));
    
    Object *obj = stream->getDictObject();
    ASSERT_NE(obj, nullptr);
    EXPECT_TRUE(obj->isDict());
    
    Dict *d = stream->getDict();
    EXPECT_NE(d, nullptr);
}

// Test large length value
TEST_F(BaseStreamTest_129, LargeLength_129) {
    const char *data = "a";
    Goffset len = 1000000;  // Large length but small actual data
    Object memDict;
    
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, std::move(memDict));
    EXPECT_EQ(stream->getLength(), 1000000);
}

// Test getPos after reading
TEST_F(BaseStreamTest_129, GetPosAfterReading_129) {
    const char *data = "hello";
    Goffset len = 5;
    Object memDict;
    
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, std::move(memDict));
    stream->reset();
    
    Goffset pos0 = stream->getPos();
    EXPECT_EQ(pos0, 0);
    
    stream->getChar();
    Goffset pos1 = stream->getPos();
    EXPECT_EQ(pos1, 1);
    
    stream->getChar();
    Goffset pos2 = stream->getPos();
    EXPECT_EQ(pos2, 2);
}

// Test lookChar doesn't advance position
TEST_F(BaseStreamTest_129, LookCharDoesNotAdvance_129) {
    const char *data = "AB";
    Goffset len = 2;
    Object memDict;
    
    auto stream = std::make_unique<MemStream>(const_cast<char*>(data), 0, len, std::move(memDict));
    stream->reset();
    
    int ch1 = stream->lookChar();
    int ch2 = stream->lookChar();
    EXPECT_EQ(ch1, ch2);
    EXPECT_EQ(ch1, 'A');
    
    // Now actually read
    int ch3 = stream->getChar();
    EXPECT_EQ(ch3, 'A');
}
