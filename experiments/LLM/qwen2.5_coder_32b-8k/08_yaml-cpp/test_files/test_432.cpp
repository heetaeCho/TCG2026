#include <gtest/gtest.h>

#include <yaml-cpp/src/fptostring.cpp>



namespace YAML {

    namespace detail {

        namespace fp_formatting {

            std::string FpToString(float v, size_t precision);

        }

    }

}



TEST(FpToStringTest_432, NormalOperation_432) {

    EXPECT_EQ(YAML::FpToString(1.2345f, 2), "1.23");

    EXPECT_EQ(YAML::FpToString(-0.9876f, 3), "-0.988");

}



TEST(FpToStringTest_432, BoundaryConditions_ZeroPrecision_432) {

    EXPECT_EQ(YAML::FpToString(1.2345f, 0), "1");

    EXPECT_EQ(YAML::FpToString(-1.2345f, 0), "-1");

}



TEST(FpToStringTest_432, BoundaryConditions_MaxPrecision_432) {

    EXPECT_EQ(YAML::FpToString(1.23456789f, 9), "1.234567890");

    EXPECT_EQ(YAML::FpToString(-1.23456789f, 9), "-1.234567890");

}



TEST(FpToStringTest_432, BoundaryConditions_LargeNumber_432) {

    EXPECT_EQ(YAML::FpToString(123456789.123456789f, 5), "123456789.12346");

}



TEST(FpToStringTest_432, BoundaryConditions_SmallNumber_432) {

    EXPECT_EQ(YAML::FpToString(0.000000001f, 10), "0.0000000010");

}



TEST(FpToStringTest_432, Exceptional_NegativePrecision_432) {

    // Assuming negative precision might lead to some default or error behavior

    EXPECT_THROW(YAML::FpToString(1.2345f, -1), std::invalid_argument);

}



TEST(FpToStringTest_432, VerificationOfExternalInteractions_432) {

    // Since the function does not involve any external collaborators,

    // this test case is not applicable here.

}
