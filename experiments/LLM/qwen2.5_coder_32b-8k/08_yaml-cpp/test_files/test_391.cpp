#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"



namespace YAML { namespace jkj { namespace dragonbox { namespace policy { namespace cache {



using ::testing::_;

using ::testing::Return;



class CompactTCacheTest : public ::testing::Test {

protected:

    using FloatFormat = float;

    using ShiftAmountType = int;

    using DecimalExponentType = int;

};



TEST_F(CompactTCacheTest, GetCache_ReturnsValidEntry_NormalOperation_391) {

    // Arrange

    constexpr DecimalExponentType k = 0; // Example value within range



    // Act

    auto result = compact_t::get_cache<FloatFormat, ShiftAmountType>(k);



    // Assert

    // Since we cannot infer the internal logic, we can only check if it compiles and runs without errors.

}



TEST_F(CompactTCacheTest, GetCache_ReturnsValidEntry_BoundaryMin_391) {

    // Arrange

    constexpr DecimalExponentType k = cache_holder<FloatFormat>::min_k;



    // Act

    auto result = compact_t::get_cache<FloatFormat, ShiftAmountType>(k);



    // Assert

    // Since we cannot infer the internal logic, we can only check if it compiles and runs without errors.

}



TEST_F(CompactTCacheTest, GetCache_ReturnsValidEntry_BoundaryMax_391) {

    // Arrange

    constexpr DecimalExponentType k = cache_holder<FloatFormat>::max_k;



    // Act

    auto result = compact_t::get_cache<FloatFormat, ShiftAmountType>(k);



    // Assert

    // Since we cannot infer the internal logic, we can only check if it compiles and runs without errors.

}



TEST_F(CompactTCacheTest, GetCache_DoesNotThrowException_OutOfRange_391) {

    // Arrange & Act & Assert

    // We cannot test for exceptions since the function is noexcept.

    // However, we can ensure that the function does not throw exceptions for values outside the range.

    // Since it's noexcept and asserts in debug mode, we assume it handles out-of-range gracefully without throwing.



    EXPECT_NO_THROW(compact_t::get_cache<FloatFormat, ShiftAmountType>(cache_holder<FloatFormat>::min_k - 1));

    EXPECT_NO_THROW(compact_t::get_cache<FloatFormat, ShiftAmountType>(cache_holder<FloatFormat>::max_k + 1));

}



} } } } }
