#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



class XmpArrayValueTest : public ::testing::Test {

protected:

    TypeId typeId = ttString;  // Example type ID, can be adjusted as needed

    std::unique_ptr<XmpArrayValue> xmpArrayValue;



    void SetUp() override {

        xmpArrayValue = std::make_unique<XmpArrayValue>(typeId);

    }

};



TEST_F(XmpArrayValueTest_2169, ConstructorSetsXmpArrayType_2169) {

    EXPECT_EQ(xmpArrayValue->xmpArrayType(), XmpValue::xmpArrayType(typeId));

}



TEST_F(XmpArrayValueTest_2169, CountInitiallyZero_2169) {

    EXPECT_EQ(xmpArrayValue->count(), 0);

}



TEST_F(XmpArrayValueTest_2169, ReadEmptyStringDoesNotChangeCount_2169) {

    xmpArrayValue->read("");

    EXPECT_EQ(xmpArrayValue->count(), 0);

}



// Assuming read with valid data increases count

TEST_F(XmpArrayValueTest_2169, ReadValidStringIncreasesCount_2169) {

    std::string testData = "some_valid_data";  // Adjust as per actual format requirements

    xmpArrayValue->read(testData);

    EXPECT_EQ(xmpArrayValue->count(), 1);  // Assuming one element is added

}



TEST_F(XmpArrayValueTest_2169, ToStringReturnsEmptyForIndexOutOfRange_2169) {

    std::string result = xmpArrayValue->toString(0);

    EXPECT_EQ(result, "");

}



TEST_F(XmpArrayValueTest_2169, ToInt64ReturnsZeroForIndexOutOfRange_2169) {

    int64_t result = xmpArrayValue->toInt64(0);

    EXPECT_EQ(result, 0);

}



TEST_F(XmpArrayValueTest_2169, ToUint32ReturnsZeroForIndexOutOfRange_2169) {

    uint32_t result = xmpArrayValue->toUint32(0);

    EXPECT_EQ(result, 0);

}



TEST_F(XmpArrayValueTest_2169, ToFloatReturnsZeroForIndexOutOfRange_2169) {

    float result = xmpArrayValue->toFloat(0);

    EXPECT_FLOAT_EQ(result, 0.0f);

}



TEST_F(XmpArrayValueTest_2169, ToRationalThrowsForIndexOutOfRange_2169) {

    EXPECT_THROW(xmpArrayValue->toRational(0), std::out_of_range);

}
