#include <gtest/gtest.h>

#include <cstdint>

#include <cstring>



namespace Catch { namespace Detail {

    uint64_t convertToBits(double d);

} }



class ConvertToBitsTest_607 : public ::testing::Test {};



TEST_F(ConvertToBitsTest_607, PositiveZero_607) {

    double input = 0.0;

    uint64_t expectedOutput = 0x0000000000000000;

    EXPECT_EQ(Catch::Detail::convertToBits(input), expectedOutput);

}



TEST_F(ConvertToBitsTest_607, NegativeZero_607) {

    double input = -0.0;

    uint64_t expectedOutput = 0x8000000000000000;

    EXPECT_EQ(Catch::Detail::convertToBits(input), expectedOutput);

}



TEST_F(ConvertToBitsTest_607, PositiveOne_607) {

    double input = 1.0;

    uint64_t expectedOutput = 0x3FF0000000000000;

    EXPECT_EQ(Catch::Detail::convertToBits(input), expectedOutput);

}



TEST_F(ConvertToBitsTest_607, NegativeOne_607) {

    double input = -1.0;

    uint64_t expectedOutput = 0xBFF0000000000000;

    EXPECT_EQ(Catch::Detail::convertToBits(input), expectedOutput);

}



TEST_F(ConvertToBitsTest_607, PositiveInfinity_607) {

    double input = std::numeric_limits<double>::infinity();

    uint64_t expectedOutput = 0x7FF0000000000000;

    EXPECT_EQ(Catch::Detail::convertToBits(input), expectedOutput);

}



TEST_F(ConvertToBitsTest_607, NegativeInfinity_607) {

    double input = -std::numeric_limits<double>::infinity();

    uint64_t expectedOutput = 0xFFF0000000000000;

    EXPECT_EQ(Catch::Detail::convertToBits(input), expectedOutput);

}



TEST_F(ConvertToBitsTest_607, NaN_607) {

    double input = std::numeric_limits<double>::quiet_NaN();

    uint64_t result = Catch::Detail::convertToBits(input);

    EXPECT_TRUE((result & 0x7FF0000000000000) == 0x7FF0000000000000); // Check that the exponent bits are all 1s

    EXPECT_TRUE((result & 0x000FFFFFFFFFFFFF) != 0x0000000000000000); // Check that not all fraction bits are 0s

}



TEST_F(ConvertToBitsTest_607, LargePositiveNumber_607) {

    double input = 1.7976931348623157E+308; // Max finite value for double

    uint64_t expectedOutput = 0x7FEFFFFFFFFFFFFF;

    EXPECT_EQ(Catch::Detail::convertToBits(input), expectedOutput);

}



TEST_F(ConvertToBitsTest_607, LargeNegativeNumber_607) {

    double input = -1.7976931348623157E+308; // Min finite value for double

    uint64_t expectedOutput = 0xFFEFFFFFFFFFFFFF;

    EXPECT_EQ(Catch::Detail::convertToBits(input), expectedOutput);

}



TEST_F(ConvertToBitsTest_607, SmallPositiveNumber_607) {

    double input = 2.2250738585072014E-308; // Min positive normal value for double

    uint64_t expectedOutput = 0x0010000000000000;

    EXPECT_EQ(Catch::Detail::convertToBits(input), expectedOutput);

}



TEST_F(ConvertToBitsTest_607, SmallNegativeNumber_607) {

    double input = -2.2250738585072014E-308; // Min negative normal value for double

    uint64_t expectedOutput = 0x8010000000000000;

    EXPECT_EQ(Catch::Detail::convertToBits(input), expectedOutput);

}
