#include <gtest/gtest.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



// Test fixture for ValueType<float>

class ValueTypeFloatTest_160 : public ::testing::Test {

protected:

    ValueType<float> value_type_float;



    void SetUp() override {

        // Initialize with a sample float value

        value_type_float = ValueType<float>(3.14f, static_cast<TypeId>(0));

    }

};



// Test normal operation of toUint32

TEST_F(ValueTypeFloatTest_160, ToUint32_NormalOperation_160) {

    uint32_t result = value_type_float.toUint32(0);

    EXPECT_EQ(result, static_cast<uint32_t>(3.14f));

}



// Test boundary condition of toUint32 with n out of range

TEST_F(ValueTypeFloatTest_160, ToUint32_OutOfRange_160) {

    uint32_t result = value_type_float.toUint32(1); // Assuming 1 is out of range for a single float value

    EXPECT_EQ(result, 0u); // Expect default or boundary behavior

}



// Test toUint32 with zero value

TEST_F(ValueTypeFloatTest_160, ToUint32_ZeroValue_160) {

    ValueType<float> zero_value_type_float(0.0f, static_cast<TypeId>(0));

    uint32_t result = zero_value_type_float.toUint32(0);

    EXPECT_EQ(result, 0u);

}



// Test toUint32 with large float value

TEST_F(ValueTypeFloatTest_160, ToUint32_LargeValue_160) {

    ValueType<float> large_value_type_float(static_cast<float>(LARGE_INT), static_cast<TypeId>(0));

    uint32_t result = large_value_type_float.toUint32(0);

    EXPECT_EQ(result, LARGE_INT); // Assuming conversion doesn't overflow

}



// Test toUint32 with negative float value

TEST_F(ValueTypeFloatTest_160, ToUint32_NegativeValue_160) {

    ValueType<float> negative_value_type_float(-3.14f, static_cast<TypeId>(0));

    uint32_t result = negative_value_type_float.toUint32(0);

    EXPECT_EQ(result, 0u); // Assuming conversion to unsigned int results in zero

}



// Test toUint32 with maximum float value

TEST_F(ValueTypeFloatTest_160, ToUint32_MaxValue_160) {

    ValueType<float> max_value_type_float(std::numeric_limits<float>::max(), static_cast<TypeId>(0));

    uint32_t result = max_value_type_float.toUint32(0);

    EXPECT_EQ(result, std::numeric_limits<uint32_t>::max()); // Assuming conversion doesn't overflow

}



// Test toUint32 with minimum float value

TEST_F(ValueTypeFloatTest_160, ToUint32_MinValue_160) {

    ValueType<float> min_value_type_float(std::numeric_limits<float>::lowest(), static_cast<TypeId>(0));

    uint32_t result = min_value_type_float.toUint32(0);

    EXPECT_EQ(result, 0u); // Assuming conversion to unsigned int results in zero

}
