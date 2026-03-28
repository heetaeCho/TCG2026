#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



class XmpArrayValueTest_845 : public ::testing::Test {

protected:

    XmpArrayValue xmpArrayValue{TypeId::xmpText};



    void SetUp() override {

        // Setup can be used to initialize the object if needed

    }



    void TearDown() override {

        // Cleanup can be done here if necessary

    }

};



TEST_F(XmpArrayValueTest_845, CountReturnsZeroForEmptyArray_845) {

    EXPECT_EQ(xmpArrayValue.count(), 0);

}



TEST_F(XmpArrayValueTest_845, ReadHandlesEmptyBuffer_845) {

    int result = xmpArrayValue.read("");

    EXPECT_GE(result, 0); // Assuming read returns a non-negative value on success

}



TEST_F(XmpArrayValueTest_845, CloneReturnsNonNullPointer_845) {

    XmpArrayValue::UniquePtr clone = xmpArrayValue.clone();

    EXPECT_NE(clone.get(), nullptr);

}



TEST_F(XmpArrayValueTest_845, ToStringThrowsForInvalidIndex_845) {

    EXPECT_THROW(xmpArrayValue.toString(0), std::out_of_range); // Assuming out_of_range is thrown for invalid index

}



TEST_F(XmpArrayValueTest_845, ToInt64ThrowsForInvalidIndex_845) {

    EXPECT_THROW(xmpArrayValue.toInt64(0), std::out_of_range);

}



TEST_F(XmpArrayValueTest_845, ToUint32ThrowsForInvalidIndex_845) {

    EXPECT_THROW(xmpArrayValue.toUint32(0), std::out_of_range);

}



TEST_F(XmpArrayValueTest_845, ToFloatThrowsForInvalidIndex_845) {

    EXPECT_THROW(xmpArrayValue.toFloat(0), std::out_of_range);

}



TEST_F(XmpArrayValueTest_845, ToRationalThrowsForInvalidIndex_845) {

    EXPECT_THROW(xmpArrayValue.toRational(0), std::out_of_range);

}
