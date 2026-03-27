#include <gtest/gtest.h>

#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"



namespace YAML { namespace jkj { namespace dragonbox { namespace detail {



using namespace log;



class DragonboxLogTest_318 : public ::testing::Test {

protected:

    // Additional setup can be done here if needed

};



TEST_F(DragonboxLogTest_318, Compute_ReturnsCorrectValueForBoundaryConditionLower_318) {

    constexpr auto result = compute<int, int>(min_exponent);

    // Expected value is calculated based on the formula in the function

    constexpr auto expected = (min_exponent * info::multiply - info::subtract) >> info::shift;

    EXPECT_EQ(result, expected);

}



TEST_F(DragonboxLogTest_318, Compute_ReturnsCorrectValueForBoundaryConditionUpper_318) {

    constexpr auto result = compute<int, int>(max_exponent);

    // Expected value is calculated based on the formula in the function

    constexpr auto expected = (max_exponent * info::multiply - info::subtract) >> info::shift;

    EXPECT_EQ(result, expected);

}



TEST_F(DragonboxLogTest_318, Compute_ReturnsCorrectValueForNormalOperation_318) {

    constexpr int e = 0; // Example value within the range

    constexpr auto result = compute<int, int>(e);

    // Expected value is calculated based on the formula in the function

    constexpr auto expected = (e * info::multiply - info::subtract) >> info::shift;

    EXPECT_EQ(result, expected);

}



TEST_F(DragonboxLogTest_318, Compute_ReturnsCorrectValueForAnotherNormalOperation_318) {

    constexpr int e = 42; // Another example value within the range

    constexpr auto result = compute<int, int>(e);

    // Expected value is calculated based on the formula in the function

    constexpr auto expected = (e * info::multiply - info::subtract) >> info::shift;

    EXPECT_EQ(result, expected);

}



// Assuming min_exponent and max_exponent are defined such that they have a range

TEST_F(DragonboxLogTest_318, Compute_HandlesFullRangeOfValues_318) {

    for (int e = min_exponent; e <= max_exponent; ++e) {

        constexpr auto result = compute<int, int>(e);

        // Expected value is calculated based on the formula in the function

        constexpr auto expected = (e * info::multiply - info::subtract) >> info::shift;

        EXPECT_EQ(result, expected);

    }

}



} } } } // namespace YAML::jkj::dragonbox::detail
