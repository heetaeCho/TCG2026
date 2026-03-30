#include <gtest/gtest.h>

#include <exiv2/value.hpp>



namespace Exiv2 {

    class ValueTypeDoubleTest_172 : public ::testing::Test {

    protected:

        void SetUp() override {

            value = std::make_unique<ValueType<double>>(3.5, exvDouble);

        }



        std::unique_ptr<ValueType<double>> value;

    };



    TEST_F(ValueTypeDoubleTest_172, ToRationalValidIndex_172) {

        Rational result = value->toRational(0);

        EXPECT_TRUE(value->ok());

        EXPECT_EQ(result.first, 3500000);

        EXPECT_EQ(result.second, 1000000);

    }



    TEST_F(ValueTypeDoubleTest_172, ToRationalInvalidIndex_172) {

        Rational result = value->toRational(1);

        EXPECT_FALSE(value->ok());

        // Assuming the return value for an invalid index is (0, 0)

        EXPECT_EQ(result.first, 0);

        EXPECT_EQ(result.second, 0);

    }



    TEST_F(ValueTypeDoubleTest_172, ToRationalNegativeValue_172) {

        std::unique_ptr<ValueType<double>> negative_value = std::make_unique<ValueType<double>>(-3.5, exvDouble);

        Rational result = negative_value->toRational(0);

        EXPECT_TRUE(negative_value->ok());

        EXPECT_EQ(result.first, -3500000);

        EXPECT_EQ(result.second, 1000000);

    }



    TEST_F(ValueTypeDoubleTest_172, ToRationalBoundaryValue_172) {

        std::unique_ptr<ValueType<double>> boundary_value = std::make_unique<ValueType<double>>(0.0, exvDouble);

        Rational result = boundary_value->toRational(0);

        EXPECT_TRUE(boundary_value->ok());

        EXPECT_EQ(result.first, 0);

        EXPECT_EQ(result.second, 1);

    }



    TEST_F(ValueTypeDoubleTest_172, ToRationalLargeValue_172) {

        std::unique_ptr<ValueType<double>> large_value = std::make_unique<ValueType<double>>(1e6, exvDouble);

        Rational result = large_value->toRational(0);

        EXPECT_TRUE(large_value->ok());

        EXPECT_EQ(result.first, 1000000000000);

        EXPECT_EQ(result.second, 1000);

    }



    TEST_F(ValueTypeDoubleTest_172, ToRationalSmallValue_172) {

        std::unique_ptr<ValueType<double>> small_value = std::make_unique<ValueType<double>>(1e-6, exvDouble);

        Rational result = small_value->toRational(0);

        EXPECT_TRUE(small_value->ok());

        EXPECT_EQ(result.first, 1);

        EXPECT_EQ(result.second, 1000000);

    }

}
