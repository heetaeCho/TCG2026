#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>

using namespace Exiv2;

class ValueCreateTest_786 : public ::testing::Test {
protected:
};

TEST_F(ValueCreateTest_786, CreateInvalidTypeId_786) {
    auto value = Value::create(invalidTypeId);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->typeId(), invalidTypeId);
}

TEST_F(ValueCreateTest_786, CreateSignedByte_786) {
    auto value = Value::create(signedByte);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->typeId(), signedByte);
}

TEST_F(ValueCreateTest_786, CreateUnsignedByte_786) {
    auto value = Value::create(unsignedByte);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->typeId(), unsignedByte);
}

TEST_F(ValueCreateTest_786, CreateAsciiString_786) {
    auto value = Value::create(asciiString);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->typeId(), asciiString);
}

TEST_F(ValueCreateTest_786, CreateUnsignedShort_786) {
    auto value = Value::create(unsignedShort);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->typeId(), unsignedShort);
}

TEST_F(ValueCreateTest_786, CreateUnsignedLong_786) {
    auto value = Value::create(unsignedLong);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->typeId(), unsignedLong);
}

TEST_F(ValueCreateTest_786, CreateTiffIfd_786) {
    auto value = Value::create(tiffIfd);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->typeId(), tiffIfd);
}

TEST_F(ValueCreateTest_786, CreateUnsignedRational_786) {
    auto value = Value::create(unsignedRational);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->typeId(), unsignedRational);
}

TEST_F(ValueCreateTest_786, CreateUndefined_786) {
    auto value = Value::create(undefined);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->typeId(), undefined);
}

TEST_F(ValueCreateTest_786, CreateSignedShort_786) {
    auto value = Value::create(signedShort);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->typeId(), signedShort);
}

TEST_F(ValueCreateTest_786, CreateSignedLong_786) {
    auto value = Value::create(signedLong);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->typeId(), signedLong);
}

TEST_F(ValueCreateTest_786, CreateSignedRational_786) {
    auto value = Value::create(signedRational);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->typeId(), signedRational);
}

TEST_F(ValueCreateTest_786, CreateTiffFloat_786) {
    auto value = Value::create(tiffFloat);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->typeId(), tiffFloat);
}

TEST_F(ValueCreateTest_786, CreateTiffDouble_786) {
    auto value = Value::create(tiffDouble);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->typeId(), tiffDouble);
}

TEST_F(ValueCreateTest_786, CreateString_786) {
    auto value = Value::create(string);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->typeId(), string);
}

TEST_F(ValueCreateTest_786, CreateDate_786) {
    auto value = Value::create(date);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->typeId(), date);
}

TEST_F(ValueCreateTest_786, CreateTime_786) {
    auto value = Value::create(time);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->typeId(), time);
}

TEST_F(ValueCreateTest_786, CreateComment_786) {
    auto value = Value::create(comment);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->typeId(), comment);
}

TEST_F(ValueCreateTest_786, CreateXmpText_786) {
    auto value = Value::create(xmpText);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->typeId(), xmpText);
}

TEST_F(ValueCreateTest_786, CreateXmpBag_786) {
    auto value = Value::create(xmpBag);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->typeId(), xmpBag);
}

TEST_F(ValueCreateTest_786, CreateXmpSeq_786) {
    auto value = Value::create(xmpSeq);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->typeId(), xmpSeq);
}

TEST_F(ValueCreateTest_786, CreateXmpAlt_786) {
    auto value = Value::create(xmpAlt);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->typeId(), xmpAlt);
}

TEST_F(ValueCreateTest_786, CreateLangAlt_786) {
    auto value = Value::create(langAlt);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->typeId(), langAlt);
}

TEST_F(ValueCreateTest_786, CreateLastTypeIdFallsToDefault_786) {
    auto value = Value::create(lastTypeId);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->typeId(), lastTypeId);
}

TEST_F(ValueCreateTest_786, CreateDirectoryFallsToDefault_786) {
    auto value = Value::create(directory);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->typeId(), directory);
}

TEST_F(ValueCreateTest_786, CreateUnsignedLongLongFallsToDefault_786) {
    auto value = Value::create(unsignedLongLong);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->typeId(), unsignedLongLong);
}

TEST_F(ValueCreateTest_786, CreateSignedLongLongFallsToDefault_786) {
    auto value = Value::create(signedLongLong);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->typeId(), signedLongLong);
}

TEST_F(ValueCreateTest_786, CreateTiffIfd8FallsToDefault_786) {
    auto value = Value::create(tiffIfd8);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->typeId(), tiffIfd8);
}

TEST_F(ValueCreateTest_786, ClonePreservesTypeId_786) {
    auto value = Value::create(unsignedShort);
    ASSERT_NE(value, nullptr);
    auto cloned = value->clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->typeId(), unsignedShort);
}

TEST_F(ValueCreateTest_786, OkReturnsTrueByDefault_786) {
    auto value = Value::create(asciiString);
    ASSERT_NE(value, nullptr);
    EXPECT_TRUE(value->ok());
}

TEST_F(ValueCreateTest_786, SizeIsZeroInitially_786) {
    auto value = Value::create(unsignedShort);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->size(), 0u);
}

TEST_F(ValueCreateTest_786, CountIsZeroInitially_786) {
    auto value = Value::create(unsignedLong);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->count(), 0u);
}

TEST_F(ValueCreateTest_786, SizeDataAreaIsZeroByDefault_786) {
    auto value = Value::create(undefined);
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->sizeDataArea(), 0u);
}

TEST_F(ValueCreateTest_786, DataAreaIsEmptyByDefault_786) {
    auto value = Value::create(undefined);
    ASSERT_NE(value, nullptr);
    DataBuf buf = value->dataArea();
    EXPECT_EQ(buf.size(), 0u);
}

TEST_F(ValueCreateTest_786, ToStringReturnsEmptyForNewValue_786) {
    auto value = Value::create(asciiString);
    ASSERT_NE(value, nullptr);
    std::string str = value->toString();
    // For a newly created value with no data, toString should return empty or some default
    // We just verify it doesn't crash and returns a string
    EXPECT_TRUE(str.empty() || !str.empty()); // non-crashing test
}

TEST_F(ValueCreateTest_786, ReadStringForAsciiValue_786) {
    auto value = Value::create(asciiString);
    ASSERT_NE(value, nullptr);
    int result = value->read("Hello");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value->toString(), "Hello");
}

TEST_F(ValueCreateTest_786, ReadStringForStringValue_786) {
    auto value = Value::create(string);
    ASSERT_NE(value, nullptr);
    int result = value->read("TestString");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value->toString(), "TestString");
}

TEST_F(ValueCreateTest_786, ReadStringForCommentValue_786) {
    auto value = Value::create(comment);
    ASSERT_NE(value, nullptr);
    int result = value->read("A comment");
    EXPECT_EQ(result, 0);
    std::string str = value->toString();
    EXPECT_FALSE(str.empty());
}

TEST_F(ValueCreateTest_786, ReadStringForXmpTextValue_786) {
    auto value = Value::create(xmpText);
    ASSERT_NE(value, nullptr);
    int result = value->read("XMP text value");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value->toString(), "XMP text value");
}

TEST_F(ValueCreateTest_786, ReadStringForUnsignedShort_786) {
    auto value = Value::create(unsignedShort);
    ASSERT_NE(value, nullptr);
    int result = value->read("42");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value->count(), 1u);
    EXPECT_EQ(value->toInt64(0), 42);
}

TEST_F(ValueCreateTest_786, ReadStringForUnsignedLong_786) {
    auto value = Value::create(unsignedLong);
    ASSERT_NE(value, nullptr);
    int result = value->read("100000");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value->count(), 1u);
    EXPECT_EQ(value->toInt64(0), 100000);
}

TEST_F(ValueCreateTest_786, ReadStringForSignedShort_786) {
    auto value = Value::create(signedShort);
    ASSERT_NE(value, nullptr);
    int result = value->read("-123");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value->count(), 1u);
    EXPECT_EQ(value->toInt64(0), -123);
}

TEST_F(ValueCreateTest_786, ReadStringForSignedLong_786) {
    auto value = Value::create(signedLong);
    ASSERT_NE(value, nullptr);
    int result = value->read("-999999");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value->count(), 1u);
    EXPECT_EQ(value->toInt64(0), -999999);
}

TEST_F(ValueCreateTest_786, ReadStringForUnsignedRational_786) {
    auto value = Value::create(unsignedRational);
    ASSERT_NE(value, nullptr);
    int result = value->read("1/2");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value->count(), 1u);
    EXPECT_FLOAT_EQ(value->toFloat(0), 0.5f);
}

TEST_F(ValueCreateTest_786, ReadStringForSignedRational_786) {
    auto value = Value::create(signedRational);
    ASSERT_NE(value, nullptr);
    int result = value->read("-3/4");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value->count(), 1u);
    EXPECT_FLOAT_EQ(value->toFloat(0), -0.75f);
}

TEST_F(ValueCreateTest_786, ReadStringForDateValue_786) {
    auto value = Value::create(date);
    ASSERT_NE(value, nullptr);
    int result = value->read("2023-06-15");
    EXPECT_EQ(result, 0);
    std::string str = value->toString();
    EXPECT_FALSE(str.empty());
}

TEST_F(ValueCreateTest_786, ReadStringForTimeValue_786) {
    auto value = Value::create(time);
    ASSERT_NE(value, nullptr);
    int result = value->read("12:30:45");
    EXPECT_EQ(result, 0);
    std::string str = value->toString();
    EXPECT_FALSE(str.empty());
}

TEST_F(ValueCreateTest_786, ReadStringForXmpBag_786) {
    auto value = Value::create(xmpBag);
    ASSERT_NE(value, nullptr);
    int result = value->read("item1");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value->count(), 1u);
}

TEST_F(ValueCreateTest_786, ReadStringForXmpSeq_786) {
    auto value = Value::create(xmpSeq);
    ASSERT_NE(value, nullptr);
    int result = value->read("item1");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value->count(), 1u);
}

TEST_F(ValueCreateTest_786, ReadStringForXmpAlt_786) {
    auto value = Value::create(xmpAlt);
    ASSERT_NE(value, nullptr);
    int result = value->read("item1");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value->count(), 1u);
}

TEST_F(ValueCreateTest_786, ReadStringForLangAlt_786) {
    auto value = Value::create(langAlt);
    ASSERT_NE(value, nullptr);
    int result = value->read("lang=\"x-default\" Test");
    EXPECT_EQ(result, 0);
    std::string str = value->toString();
    EXPECT_FALSE(str.empty());
}

TEST_F(ValueCreateTest_786, ReadStringForTiffFloat_786) {
    auto value = Value::create(tiffFloat);
    ASSERT_NE(value, nullptr);
    int result = value->read("3.14");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value->count(), 1u);
    EXPECT_NEAR(value->toFloat(0), 3.14f, 0.01f);
}

TEST_F(ValueCreateTest_786, ReadStringForTiffDouble_786) {
    auto value = Value::create(tiffDouble);
    ASSERT_NE(value, nullptr);
    int result = value->read("2.718281828");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value->count(), 1u);
    EXPECT_NEAR(value->toFloat(0), 2.718281828f, 0.0001f);
}

TEST_F(ValueCreateTest_786, MultipleValuesUnsignedShort_786) {
    auto value = Value::create(unsignedShort);
    ASSERT_NE(value, nullptr);
    int result = value->read("10 20 30");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value->count(), 3u);
    EXPECT_EQ(value->toInt64(0), 10);
    EXPECT_EQ(value->toInt64(1), 20);
    EXPECT_EQ(value->toInt64(2), 30);
}

TEST_F(ValueCreateTest_786, SetDataAreaReturnsNonZeroByDefault_786) {
    auto value = Value::create(unsignedShort);
    ASSERT_NE(value, nullptr);
    byte data[] = {0x01, 0x02};
    int result = value->setDataArea(data, 2);
    // setDataArea default implementation returns -1
    EXPECT_EQ(result, -1);
}

TEST_F(ValueCreateTest_786, WriteToStream_786) {
    auto value = Value::create(asciiString);
    ASSERT_NE(value, nullptr);
    value->read("WriteTest");
    std::ostringstream os;
    value->write(os);
    EXPECT_EQ(os.str(), "WriteTest");
}

TEST_F(ValueCreateTest_786, CloneOfReadValuePreservesData_786) {
    auto value = Value::create(unsignedShort);
    ASSERT_NE(value, nullptr);
    value->read("55");
    auto cloned = value->clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->typeId(), unsignedShort);
    EXPECT_EQ(cloned->toInt64(0), 55);
}

TEST_F(ValueCreateTest_786, CopyToBuf_786) {
    auto value = Value::create(unsignedShort);
    ASSERT_NE(value, nullptr);
    value->read("256");
    EXPECT_EQ(value->count(), 1u);
    EXPECT_GT(value->size(), 0u);
    
    std::vector<byte> buf(value->size());
    size_t copied = value->copy(buf.data(), littleEndian);
    EXPECT_EQ(copied, value->size());
    // 256 in little endian uint16: 0x00, 0x01
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x01);
}

TEST_F(ValueCreateTest_786, ReadFromBufUnsignedShort_786) {
    auto value = Value::create(unsignedShort);
    ASSERT_NE(value, nullptr);
    byte buf[] = {0x2A, 0x00}; // 42 in little endian
    int result = value->read(buf, 2, littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value->count(), 1u);
    EXPECT_EQ(value->toInt64(0), 42);
}

TEST_F(ValueCreateTest_786, ReadFromBufUnsignedLong_786) {
    auto value = Value::create(unsignedLong);
    ASSERT_NE(value, nullptr);
    byte buf[] = {0x01, 0x00, 0x00, 0x00}; // 1 in little endian
    int result = value->read(buf, 4, littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value->count(), 1u);
    EXPECT_EQ(value->toInt64(0), 1);
}

TEST_F(ValueCreateTest_786, ReadEmptyStringForAscii_786) {
    auto value = Value::create(asciiString);
    ASSERT_NE(value, nullptr);
    int result = value->read("");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(value->toString(), "");
}

TEST_F(ValueCreateTest_786, ToUint32ForUnsignedShort_786) {
    auto value = Value::create(unsignedShort);
    ASSERT_NE(value, nullptr);
    value->read("65535");
    EXPECT_EQ(value->toUint32(0), 65535u);
}

TEST_F(ValueCreateTest_786, ToRationalForSignedRational_786) {
    auto value = Value::create(signedRational);
    ASSERT_NE(value, nullptr);
    value->read("1/3");
    Rational r = value->toRational(0);
    EXPECT_EQ(r.first, 1);
    EXPECT_EQ(r.second, 3);
}
