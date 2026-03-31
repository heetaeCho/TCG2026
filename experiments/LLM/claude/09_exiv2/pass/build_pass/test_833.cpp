#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <cstring>
#include <sstream>

using namespace Exiv2;

// XmpValue is abstract, so we need a concrete subclass for testing.
// We'll use XmpTextValue which is a concrete implementation of XmpValue.
// Alternatively, we can use Value::create to get concrete instances.

class XmpValueTest_833 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test creating an XmpTextValue via Value::create with xmpText type
TEST_F(XmpValueTest_833, CreateXmpTextValue_833) {
    auto value = Value::create(xmpText);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->typeId(), xmpText);
}

// Test reading a string into XmpTextValue
TEST_F(XmpValueTest_833, ReadStringAndSize_833) {
    auto value = Value::create(xmpText);
    ASSERT_NE(value, nullptr);
    int result = value->read("Hello World");
    EXPECT_EQ(result, 0);
    EXPECT_GT(value->size(), 0u);
}

// Test reading an empty string
TEST_F(XmpValueTest_833, ReadEmptyString_833) {
    auto value = Value::create(xmpText);
    ASSERT_NE(value, nullptr);
    int result = value->read("");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value->size(), 0u);
}

// Test toString after reading a string
TEST_F(XmpValueTest_833, ToStringAfterRead_833) {
    auto value = Value::create(xmpText);
    ASSERT_NE(value, nullptr);
    value->read("TestValue");
    std::string str = value->toString();
    EXPECT_EQ(str, "TestValue");
}

// Test count for XmpTextValue
TEST_F(XmpValueTest_833, CountForXmpTextValue_833) {
    auto value = Value::create(xmpText);
    ASSERT_NE(value, nullptr);
    value->read("SomeText");
    EXPECT_EQ(value->count(), 1u);
}

// Test size matches the string length for XmpTextValue
TEST_F(XmpValueTest_833, SizeMatchesStringLength_833) {
    auto value = Value::create(xmpText);
    ASSERT_NE(value, nullptr);
    std::string testStr = "Hello";
    value->read(testStr);
    EXPECT_EQ(value->size(), testStr.size());
}

// Test copy function
TEST_F(XmpValueTest_833, CopyToBuffer_833) {
    auto value = Value::create(xmpText);
    ASSERT_NE(value, nullptr);
    std::string testStr = "CopyTest";
    value->read(testStr);
    
    size_t sz = value->size();
    std::vector<byte> buf(sz + 1, 0);
    size_t copied = value->copy(buf.data(), littleEndian);
    EXPECT_EQ(copied, sz);
    
    std::string result(reinterpret_cast<char*>(buf.data()), copied);
    EXPECT_EQ(result, testStr);
}

// Test reading from byte buffer
TEST_F(XmpValueTest_833, ReadFromByteBuffer_833) {
    auto value = Value::create(xmpText);
    ASSERT_NE(value, nullptr);
    std::string testStr = "ByteData";
    int result = value->read(reinterpret_cast<const byte*>(testStr.c_str()), testStr.size(), littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value->toString(), testStr);
}

// Test clone
TEST_F(XmpValueTest_833, ClonePreservesValue_833) {
    auto value = Value::create(xmpText);
    ASSERT_NE(value, nullptr);
    value->read("CloneMe");
    
    auto cloned = value->clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->toString(), "CloneMe");
    EXPECT_EQ(cloned->typeId(), xmpText);
}

// Test XmpArrayType default is xaNone
TEST_F(XmpValueTest_833, DefaultXmpArrayTypeIsNone_833) {
    auto value = Value::create(xmpText);
    ASSERT_NE(value, nullptr);
    // We need to cast to access XmpValue-specific methods
    auto* xmpVal = dynamic_cast<XmpValue*>(value.get());
    ASSERT_NE(xmpVal, nullptr);
    EXPECT_EQ(xmpVal->xmpArrayType(), XmpValue::xaNone);
}

// Test XmpStruct default is xsNone
TEST_F(XmpValueTest_833, DefaultXmpStructIsNone_833) {
    auto value = Value::create(xmpText);
    ASSERT_NE(value, nullptr);
    auto* xmpVal = dynamic_cast<XmpValue*>(value.get());
    ASSERT_NE(xmpVal, nullptr);
    EXPECT_EQ(xmpVal->xmpStruct(), XmpValue::xsNone);
}

// Test setXmpArrayType
TEST_F(XmpValueTest_833, SetXmpArrayType_833) {
    auto value = Value::create(xmpText);
    ASSERT_NE(value, nullptr);
    auto* xmpVal = dynamic_cast<XmpValue*>(value.get());
    ASSERT_NE(xmpVal, nullptr);
    
    xmpVal->setXmpArrayType(XmpValue::xaAlt);
    EXPECT_EQ(xmpVal->xmpArrayType(), XmpValue::xaAlt);
    
    xmpVal->setXmpArrayType(XmpValue::xaBag);
    EXPECT_EQ(xmpVal->xmpArrayType(), XmpValue::xaBag);
    
    xmpVal->setXmpArrayType(XmpValue::xaSeq);
    EXPECT_EQ(xmpVal->xmpArrayType(), XmpValue::xaSeq);
}

// Test setXmpStruct
TEST_F(XmpValueTest_833, SetXmpStruct_833) {
    auto value = Value::create(xmpText);
    ASSERT_NE(value, nullptr);
    auto* xmpVal = dynamic_cast<XmpValue*>(value.get());
    ASSERT_NE(xmpVal, nullptr);
    
    xmpVal->setXmpStruct(XmpValue::xsStruct);
    EXPECT_EQ(xmpVal->xmpStruct(), XmpValue::xsStruct);
}

// Test static xmpArrayType(TypeId)
TEST_F(XmpValueTest_833, StaticXmpArrayTypeFromTypeId_833) {
    // xmpBag should map to xaBag
    EXPECT_EQ(XmpValue::xmpArrayType(xmpBag), XmpValue::xaBag);
    // xmpSeq should map to xaSeq
    EXPECT_EQ(XmpValue::xmpArrayType(xmpSeq), XmpValue::xaSeq);
    // xmpAlt should map to xaAlt
    EXPECT_EQ(XmpValue::xmpArrayType(xmpAlt), XmpValue::xaAlt);
    // xmpText should map to xaNone
    EXPECT_EQ(XmpValue::xmpArrayType(xmpText), XmpValue::xaNone);
}

// Test ok() returns true by default
TEST_F(XmpValueTest_833, OkReturnsTrueByDefault_833) {
    auto value = Value::create(xmpText);
    ASSERT_NE(value, nullptr);
    EXPECT_TRUE(value->ok());
}

// Test sizeDataArea returns 0 by default
TEST_F(XmpValueTest_833, SizeDataAreaIsZeroByDefault_833) {
    auto value = Value::create(xmpText);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->sizeDataArea(), 0u);
}

// Test dataArea returns empty DataBuf by default
TEST_F(XmpValueTest_833, DataAreaIsEmptyByDefault_833) {
    auto value = Value::create(xmpText);
    ASSERT_NE(value, nullptr);
    DataBuf buf = value->dataArea();
    EXPECT_EQ(buf.size(), 0u);
}

// Test write to ostream
TEST_F(XmpValueTest_833, WriteToOstream_833) {
    auto value = Value::create(xmpText);
    ASSERT_NE(value, nullptr);
    value->read("WriteTest");
    
    std::ostringstream os;
    value->write(os);
    EXPECT_EQ(os.str(), "WriteTest");
}

// Test size consistency with write output
TEST_F(XmpValueTest_833, SizeConsistentWithWrite_833) {
    auto value = Value::create(xmpText);
    ASSERT_NE(value, nullptr);
    value->read("ConsistencyCheck");
    
    std::ostringstream os;
    value->write(os);
    EXPECT_EQ(value->size(), os.str().size());
}

// Test with special characters
TEST_F(XmpValueTest_833, ReadSpecialCharacters_833) {
    auto value = Value::create(xmpText);
    ASSERT_NE(value, nullptr);
    std::string specialStr = "Special chars: <>&\"'";
    value->read(specialStr);
    EXPECT_EQ(value->toString(), specialStr);
}

// Test with very long string
TEST_F(XmpValueTest_833, ReadLongString_833) {
    auto value = Value::create(xmpText);
    ASSERT_NE(value, nullptr);
    std::string longStr(10000, 'A');
    value->read(longStr);
    EXPECT_EQ(value->size(), longStr.size());
    EXPECT_EQ(value->toString(), longStr);
}

// Test reading a unicode-like string (UTF-8 encoded)
TEST_F(XmpValueTest_833, ReadUtf8String_833) {
    auto value = Value::create(xmpText);
    ASSERT_NE(value, nullptr);
    std::string utf8Str = u8"Ünïcödé Tëst";
    value->read(utf8Str);
    EXPECT_EQ(value->toString(), utf8Str);
}

// Test overwriting a value with a new read
TEST_F(XmpValueTest_833, OverwriteWithNewRead_833) {
    auto value = Value::create(xmpText);
    ASSERT_NE(value, nullptr);
    value->read("First");
    EXPECT_EQ(value->toString(), "First");
    
    value->read("Second");
    EXPECT_EQ(value->toString(), "Second");
}

// Test creating XmpBag type value
TEST_F(XmpValueTest_833, CreateXmpBagValue_833) {
    auto value = Value::create(xmpBag);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->typeId(), xmpBag);
}

// Test creating XmpSeq type value
TEST_F(XmpValueTest_833, CreateXmpSeqValue_833) {
    auto value = Value::create(xmpSeq);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->typeId(), xmpSeq);
}

// Test creating XmpAlt type value
TEST_F(XmpValueTest_833, CreateXmpAltValue_833) {
    auto value = Value::create(xmpAlt);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->typeId(), xmpAlt);
}

// Test reading byte buffer with zero length
TEST_F(XmpValueTest_833, ReadByteBufferZeroLength_833) {
    auto value = Value::create(xmpText);
    ASSERT_NE(value, nullptr);
    const byte dummy = 0;
    int result = value->read(&dummy, 0, littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value->size(), 0u);
}

// Test setXmpArrayType back to xaNone
TEST_F(XmpValueTest_833, SetXmpArrayTypeBackToNone_833) {
    auto value = Value::create(xmpText);
    ASSERT_NE(value, nullptr);
    auto* xmpVal = dynamic_cast<XmpValue*>(value.get());
    ASSERT_NE(xmpVal, nullptr);
    
    xmpVal->setXmpArrayType(XmpValue::xaBag);
    EXPECT_EQ(xmpVal->xmpArrayType(), XmpValue::xaBag);
    
    xmpVal->setXmpArrayType(XmpValue::xaNone);
    EXPECT_EQ(xmpVal->xmpArrayType(), XmpValue::xaNone);
}

// Test setXmpStruct back to xsNone
TEST_F(XmpValueTest_833, SetXmpStructBackToNone_833) {
    auto value = Value::create(xmpText);
    ASSERT_NE(value, nullptr);
    auto* xmpVal = dynamic_cast<XmpValue*>(value.get());
    ASSERT_NE(xmpVal, nullptr);
    
    xmpVal->setXmpStruct(XmpValue::xsStruct);
    EXPECT_EQ(xmpVal->xmpStruct(), XmpValue::xsStruct);
    
    xmpVal->setXmpStruct(XmpValue::xsNone);
    EXPECT_EQ(xmpVal->xmpStruct(), XmpValue::xsNone);
}

// Test that clone preserves XmpArrayType
TEST_F(XmpValueTest_833, ClonePreservesXmpArrayType_833) {
    auto value = Value::create(xmpText);
    ASSERT_NE(value, nullptr);
    auto* xmpVal = dynamic_cast<XmpValue*>(value.get());
    ASSERT_NE(xmpVal, nullptr);
    
    xmpVal->setXmpArrayType(XmpValue::xaSeq);
    value->read("ArrayTest");
    
    auto cloned = value->clone();
    auto* clonedXmp = dynamic_cast<XmpValue*>(cloned.get());
    ASSERT_NE(clonedXmp, nullptr);
    EXPECT_EQ(clonedXmp->xmpArrayType(), XmpValue::xaSeq);
}

// Test that clone preserves XmpStruct
TEST_F(XmpValueTest_833, ClonePreservesXmpStruct_833) {
    auto value = Value::create(xmpText);
    ASSERT_NE(value, nullptr);
    auto* xmpVal = dynamic_cast<XmpValue*>(value.get());
    ASSERT_NE(xmpVal, nullptr);
    
    xmpVal->setXmpStruct(XmpValue::xsStruct);
    value->read("StructTest");
    
    auto cloned = value->clone();
    auto* clonedXmp = dynamic_cast<XmpValue*>(cloned.get());
    ASSERT_NE(clonedXmp, nullptr);
    EXPECT_EQ(clonedXmp->xmpStruct(), XmpValue::xsStruct);
}

// Test copy with bigEndian byte order (should not affect XMP text)
TEST_F(XmpValueTest_833, CopyWithBigEndian_833) {
    auto value = Value::create(xmpText);
    ASSERT_NE(value, nullptr);
    std::string testStr = "EndianTest";
    value->read(testStr);
    
    size_t sz = value->size();
    std::vector<byte> buf(sz + 1, 0);
    size_t copied = value->copy(buf.data(), bigEndian);
    EXPECT_EQ(copied, sz);
    
    std::string result(reinterpret_cast<char*>(buf.data()), copied);
    EXPECT_EQ(result, testStr);
}

// Test that size and copy give consistent results
TEST_F(XmpValueTest_833, SizeAndCopyConsistency_833) {
    auto value = Value::create(xmpText);
    ASSERT_NE(value, nullptr);
    value->read("Consistency");
    
    size_t sz = value->size();
    std::vector<byte> buf(sz + 1, 0);
    size_t copied = value->copy(buf.data(), littleEndian);
    EXPECT_EQ(sz, copied);
}
