#include <gtest/gtest.h>

#include "catch2/internal/catch_random_integer_helpers.hpp"



class ExtendedMultResultTest_331 : public ::testing::Test {

protected:

    using UInt64 = std::uint64_t;

};



TEST_F(ExtendedMultResultTest_331, NormalOperation_331) {

    auto result = Catch::Detail::extendedMultPortable(0x123456789ABCDEF0, 0xFEDCBA9876543210);

    EXPECT_EQ(result.high, 0x1BDBE6F1AEC1B45D);

    EXPECT_EQ(result.low, 0x7613AFC9A95DD120);

}



TEST_F(ExtendedMultResultTest_331, ZeroMultiplication_331) {

    auto result = Catch::Detail::extendedMultPortable(0, 0xFEDCBA9876543210);

    EXPECT_EQ(result.high, 0);

    EXPECT_EQ(result.low, 0);



    result = Catch::Detail::extendedMultPortable(0x123456789ABCDEF0, 0);

    EXPECT_EQ(result.high, 0);

    EXPECT_EQ(result.low, 0);

}



TEST_F(ExtendedMultResultTest_331, MaxValueMultiplication_331) {

    auto result = Catch::Detail::extendedMultPortable(0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF);

    EXPECT_EQ(result.high, 0xFFFFFFFE00000001);

    EXPECT_EQ(result.low, 0);

}



TEST_F(ExtendedMultResultTest_331, BoundaryConditionLowHighBits_331) {

    auto result = Catch::Detail::extendedMultPortable(0x00000000FFFFFFFF, 0xFFFFFFFF00000000);

    EXPECT_EQ(result.high, 0xFFFFFFFF);

    EXPECT_EQ(result.low, 0);



    result = Catch::Detail::extendedMultPortable(0xFFFFFFFF00000000, 0x00000000FFFFFFFF);

    EXPECT_EQ(result.high, 0xFFFFFFFF);

    EXPECT_EQ(result.low, 0);

}
