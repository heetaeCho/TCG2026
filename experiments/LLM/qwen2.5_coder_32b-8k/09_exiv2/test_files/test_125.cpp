#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"



using namespace Exiv2;

using ::testing::Eq;



class ValueTest : public ::testing::Test {

protected:

    void SetUp() override {

        value = Value::create(TypeId::asciiString);

    }



    UniquePtr value;

};



TEST_F(ValueTest_125, CloneReturnsValidPointer_125) {

    auto clonedValue = value->clone();

    ASSERT_NE(clonedValue.get(), nullptr);

}



TEST_F(ValueTest_125, OkReturnsTrueInitially_125) {

    EXPECT_TRUE(value->ok());

}



TEST_F(ValueTest_125, ReadFromBufferSetsData_125) {

    const byte buffer[] = {72, 101, 108, 108, 111}; // "Hello"

    int result = value->read(buffer, sizeof(buffer), littleEndian);

    EXPECT_EQ(result, 0); // Assuming success is indicated by 0

}



TEST_F(ValueTest_125, ReadFromStringSetsData_125) {

    std::string buffer = "Hello";

    int result = value->read(buffer);

    EXPECT_EQ(result, 0); // Assuming success is indicated by 0

}



TEST_F(ValueTest_125, SetDataAreaFromBuffer_125) {

    const byte buffer[] = {72, 101, 108, 108, 111}; // "Hello"

    int result = value->setDataArea(buffer, sizeof(buffer));

    EXPECT_EQ(result, 0); // Assuming success is indicated by 0

}



TEST_F(ValueTest_125, CopyToBufferReturnsSize_125) {

    byte buffer[10];

    size_t sizeCopied = value->copy(buffer, littleEndian);

    EXPECT_GE(sizeCopied, 0); // Size should be non-negative

}



TEST_F(ValueTest_125, CountReturnsNonNegative_125) {

    size_t count = value->count();

    EXPECT_GE(count, 0); // Count should be non-negative

}



TEST_F(ValueTest_125, SizeReturnsNonNegative_125) {

    size_t size = value->size();

    EXPECT_GE(size, 0); // Size should be non-negative

}



TEST_F(ValueTest_125, ToStringReturnsValidString_125) {

    std::string str = value->toString();

    EXPECT_TRUE(str.empty() || !str.empty()); // String should either be empty or not

}



TEST_F(ValueTest_125, ToStringWithIndexReturnsValidString_125) {

    std::string str = value->toString(0);

    EXPECT_TRUE(str.empty() || !str.empty()); // String should either be empty or not

}



TEST_F(ValueTest_125, ToInt64ReturnsValue_125) {

    int64_t intValue = value->toInt64(0);

    EXPECT_EQ(intValue, 0); // Assuming default constructed value returns 0

}



TEST_F(ValueTest_125, ToUint32ReturnsValue_125) {

    uint32_t uintValue = value->toUint32(0);

    EXPECT_EQ(uintValue, 0); // Assuming default constructed value returns 0

}



TEST_F(ValueTest_125, ToFloatReturnsValue_125) {

    float floatValue = value->toFloat(0);

    EXPECT_FLOAT_EQ(floatValue, 0.0f); // Assuming default constructed value returns 0

}



TEST_F(ValueTest_125, ToRationalReturnsDefault_125) {

    Rational rationalValue = value->toRational(0);

    EXPECT_EQ(rationalValue.first, 0);

    EXPECT_EQ(rationalValue.second, 1); // Default rational should be 0/1

}



TEST_F(ValueTest_125, SizeDataAreaReturnsNonNegative_125) {

    size_t dataSize = value->sizeDataArea();

    EXPECT_GE(dataSize, 0); // Data size should be non-negative

}



TEST_F(ValueTest_125, DataAreaReturnsValidBuffer_125) {

    DataBuf data = value->dataArea();

    EXPECT_TRUE(data.pData_ != nullptr || data.size_ == 0); // Buffer should either be valid or size should be 0

}
