#include <gtest/gtest.h>

#include <exiv2/value.hpp>



using namespace Exiv2;



class ValueTypeFloatTest : public ::testing::Test {

protected:

    ValueType<float> value_type_float;



    ValueTypeFloatTest() : value_type_float(TypeId::floatId) {

        // Initialize with some default values if necessary

    }

};



TEST_F(ValueTypeFloatTest_171, toRational_NormalOperation_171) {

    float test_value = 0.5f;

    value_type_float.value_.push_back(test_value);

    Rational result = value_type_float.toRational(0);

    EXPECT_EQ(result.first, static_cast<int32_t>(test_value * 1000000));

    EXPECT_EQ(result.second, 1000000);

}



TEST_F(ValueTypeFloatTest_171, toRational_BoundaryCondition_Zero_171) {

    float test_value = 0.0f;

    value_type_float.value_.push_back(test_value);

    Rational result = value_type_float.toRational(0);

    EXPECT_EQ(result.first, 0);

    EXPECT_EQ(result.second, 1);

}



TEST_F(ValueTypeFloatTest_171, toRational_BoundaryCondition_MaxValue_171) {

    float test_value = std::numeric_limits<float>::max();

    value_type_float.value_.push_back(test_value);

    Rational result = value_type_float.toRational(0);

    EXPECT_EQ(result.first, static_cast<int32_t>(test_value * 1000000));

    EXPECT_EQ(result.second, 1000000);

}



TEST_F(ValueTypeFloatTest_171, toRational_BoundaryCondition_MinValue_171) {

    float test_value = std::numeric_limits<float>::min();

    value_type_float.value_.push_back(test_value);

    Rational result = value_type_float.toRational(0);

    EXPECT_EQ(result.first, static_cast<int32_t>(test_value * 1000000));

    EXPECT_EQ(result.second, 1000000);

}



TEST_F(ValueTypeFloatTest_171, toRational_OutOfBounds_171) {

    float test_value = 0.5f;

    value_type_float.value_.push_back(test_value);

    EXPECT_THROW(value_type_float.toRational(1), std::out_of_range);

}
