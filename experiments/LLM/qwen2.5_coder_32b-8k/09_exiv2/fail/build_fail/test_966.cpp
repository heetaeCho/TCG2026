#include <gtest/gtest.h>

#include "canonmn_int.cpp" // Assuming the function is included directly for testing purposes



using namespace Exiv2::Internal;



TEST(canonEvTest_966, PositiveValue_ReturnsCorrectFloat_966) {

    EXPECT_FLOAT_EQ(1.0F, canonEv(32));

}



TEST(canonEvTest_966, NegativeValue_ReturnsCorrectFloat_966) {

    EXPECT_FLOAT_EQ(-1.0F, canonEv(-32));

}



TEST(canonEvTest_966, FractionalValue_ReturnsCorrectFloat_966) {

    EXPECT_FLOAT_EQ(1.25F, canonEv(40)); // 32 + (8/32)

}



TEST(canonEvTest_966, SpecialFraction_ReturnsCorrectFloat_966) {

    EXPECT_FLOAT_EQ(5.375F, canonEv(172)); // 160 + (20/32) -> 160 + (5/8) -> 160 + (64/3)/32

}



TEST(canonEvTest_966, SigmaLensSpecialCase_ReturnsCorrectFloat_966) {

    EXPECT_FLOAT_EQ(5.375F, canonEv(176)); // 160 + (8/32) -> 160 + (1/4) -> 160 + (30/3)/32

}



TEST(canonEvTest_966, ZeroValue_ReturnsZero_966) {

    EXPECT_FLOAT_EQ(0.0F, canonEv(0));

}



TEST(canonEvTest_966, LargePositiveValue_ReturnsCorrectFloat_966) {

    EXPECT_FLOAT_EQ(128.5F, canonEv(4128)); // 4096 + (32/32)

}



TEST(canonEvTest_966, LargeNegativeValue_ReturnsCorrectFloat_966) {

    EXPECT_FLOAT_EQ(-128.5F, canonEv(-4128)); // -(4096 + (32/32))

}
