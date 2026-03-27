#include <gtest/gtest.h>

#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

#include <limits>



namespace YAML { namespace jkj { namespace dragonbox { namespace detail { namespace div {



using namespace ::testing;



template <int N, class UInt>

class DragonboxDivTest : public Test {

protected:

    using DivFunc = UInt(*)(UInt n) noexcept;

    DivFunc func;



    DragonboxDivTest() : func(&small_division_by_pow10<N, UInt>) {}

};



using Types = Types<int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t>;

TYPED_TEST_SUITE(DragonboxDivTest, Types);



TYPED_TEST(DragonboxDivTest, SmallValueDivision_326) {

    // Test with a small value

    TypeParam value = 1;

    EXPECT_EQ(this->func(value), static_cast<TypeParam>(0.1 * value));

}



TYPED_TEST(DragonboxDivTest, MaxBoundaryValueDivision_326) {

    // Test with the maximum boundary value that can be divided by pow(10, N)

    TypeParam max_val = compute_power<N + 1>(TypeParam(10)) - 1;

    EXPECT_EQ(this->func(max_val), static_cast<TypeParam>(max_val / std::pow(10, N)));

}



TYPED_TEST(DragonboxDivTest, ZeroValueDivision_326) {

    // Test with zero value

    TypeParam value = 0;

    EXPECT_EQ(this->func(value), static_cast<TypeParam>(0));

}



// This test assumes that the function should not accept values greater than the boundary.

TYPED_TEST(DragonboxDivTest, ValueExceedingBoundary_326) {

    // Test with a value exceeding the maximum boundary

    TypeParam max_val = compute_power<N + 1>(TypeParam(10));

    EXPECT_THROW(this->func(max_val), std::exception);

}



}}}}} // namespace YAML::jkj::dragonbox::detail::div


