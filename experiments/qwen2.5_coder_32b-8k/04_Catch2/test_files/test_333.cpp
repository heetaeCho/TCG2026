#include <gtest/gtest.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_random_integer_helpers.hpp"



using namespace Catch::Detail;



template <typename UInt>

class ExtendedMultTest : public ::testing::Test {

protected:

    using TestType = UInt;

};



using TestTypes = ::testing::Types<std::uint8_t, std::uint16_t, std::uint32_t>;



TYPED_TEST_SUITE(ExtendedMultTest_333, TestTypes);



TYPED_TEST(ExtendedMultTest_333, NormalOperation_333) {

    using UInt = typename TestFixture::TestType;

    ExtendedMultResult<UInt> result = extendedMult(UInt(2), UInt(3));

    EXPECT_EQ(result.high, static_cast<UInt>(0));

    EXPECT_EQ(result.low, static_cast<UInt>(6));

}



TYPED_TEST(ExtendedMultTest_333, BoundaryCondition_MaxValue_333) {

    using UInt = typename TestFixture::TestType;

    ExtendedMultResult<UInt> result = extendedMult(UInt(-1), UInt(-1));

    EXPECT_EQ(result.high, static_cast<UInt>(-1));

    EXPECT_EQ(result.low, static_cast<UInt>(1));

}



TYPED_TEST(ExtendedMultTest_333, BoundaryCondition_Zero_333) {

    using UInt = typename TestFixture::TestType;

    ExtendedMultResult<UInt> result = extendedMult(UInt(0), UInt(5));

    EXPECT_EQ(result.high, static_cast<UInt>(0));

    EXPECT_EQ(result.low, static_cast<UInt>(0));



    result = extendedMult(UInt(7), UInt(0));

    EXPECT_EQ(result.high, static_cast<UInt>(0));

    EXPECT_EQ(result.low, static_cast<UInt>(0));

}



TYPED_TEST(ExtendedMultTest_333, BoundaryCondition_One_333) {

    using UInt = typename TestFixture::TestType;

    ExtendedMultResult<UInt> result = extendedMult(UInt(1), UInt(5));

    EXPECT_EQ(result.high, static_cast<UInt>(0));

    EXPECT_EQ(result.low, static_cast<UInt>(5));



    result = extendedMult(UInt(7), UInt(1));

    EXPECT_EQ(result.high, static_cast<UInt>(0));

    EXPECT_EQ(result.low, static_cast<UInt>(7));

}



TYPED_TEST(ExtendedMultTest_333, ExceptionalCase_TypeAssertion_333) {

    // This test case is more of a conceptual check since the type assertion will cause

    // compilation failure if violated. Thus, we rely on the compiler to enforce this.

    // No runtime check possible.

}



TYPED_TEST(ExtendedMultTest_333, ExceptionalCase_SizeAssertion_333) {

    // Similar to the type assertion, this is a compile-time check.

    // We ensure that the test is only run for types smaller than uint64_t.

    static_assert(sizeof(typename TestFixture::TestType) < sizeof(std::uint64_t), "Generic extendedMult can only handle types smaller than uint64_t");

}
