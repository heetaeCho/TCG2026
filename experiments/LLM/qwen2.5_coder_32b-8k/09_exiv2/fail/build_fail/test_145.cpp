#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"



namespace {



using ::testing::_;

using namespace Exiv2;



class ToDataFloatTest : public ::testing::Test {

protected:

    // No setup or teardown required for this simple function test

};



TEST_F(ToDataFloatTest_145, NormalOperationLittleEndian_145) {

    byte buf[sizeof(float)];

    float value = 1.0f;

    ByteOrder byteOrder = littleEndian;



    size_t result = toData(buf, value, byteOrder);



    // Assuming the function returns the number of bytes written

    EXPECT_EQ(result, sizeof(float));

}



TEST_F(ToDataFloatTest_145, NormalOperationBigEndian_145) {

    byte buf[sizeof(float)];

    float value = 1.0f;

    ByteOrder byteOrder = bigEndian;



    size_t result = toData(buf, value, byteOrder);



    // Assuming the function returns the number of bytes written

    EXPECT_EQ(result, sizeof(float));

}



TEST_F(ToDataFloatTest_145, BoundaryConditionZeroValue_145) {

    byte buf[sizeof(float)];

    float value = 0.0f;

    ByteOrder byteOrder = littleEndian;



    size_t result = toData(buf, value, byteOrder);



    EXPECT_EQ(result, sizeof(float));

}



TEST_F(ToDataFloatTest_145, BoundaryConditionMaxValue_145) {

    byte buf[sizeof(float)];

    float value = std::numeric_limits<float>::max();

    ByteOrder byteOrder = bigEndian;



    size_t result = toData(buf, value, byteOrder);



    EXPECT_EQ(result, sizeof(float));

}



TEST_F(ToDataFloatTest_145, BoundaryConditionMinValue_145) {

    byte buf[sizeof(float)];

    float value = std::numeric_limits<float>::lowest();

    ByteOrder byteOrder = littleEndian;



    size_t result = toData(buf, value, byteOrder);



    EXPECT_EQ(result, sizeof(float));

}



// Since the function does not have observable side effects or error cases

// other than returning the number of bytes written, we do not need additional tests.



}  // namespace
