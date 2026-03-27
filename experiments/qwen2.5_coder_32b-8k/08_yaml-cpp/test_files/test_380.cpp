#include <gtest/gtest.h>

#include "dragonbox.h"



using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding;



// Mock function to verify behavior

struct MockFunc {

    template <class RoundingMode, class... Args>

    static constexpr int operator()(RoundingMode rm, Args... args) noexcept {

        if (std::is_same_v<RoundingMode, nearest_toward_zero_t>) {

            return 0;

        } else if (std::is_same_v<RoundingMode, nearest_away_from_zero_t>) {

            return 1;

        }

        return -1; // Default case should not happen

    }

};



class NearestTowardMinusInfinityStaticBoundaryTest_380 : public ::testing::Test {};



TEST_F(NearestTowardMinusInfinityStaticBoundaryTest_380, PositiveSignificandUsesNearestTowardZero_380) {

    auto result = nearest_toward_minus_infinity_static_boundary_t::delegate(1, MockFunc{});

    EXPECT_EQ(result, 0);

}



TEST_F(NearestTowardMinusInfinityStaticBoundaryTest_380, NegativeSignificandUsesNearestAwayFromZero_380) {

    auto result = nearest_toward_minus_infinity_static_boundary_t::delegate(-1, MockFunc{});

    EXPECT_EQ(result, 1);

}



TEST_F(NearestTowardMinusInfinityStaticBoundaryTest_380, ZeroSignificandUsesNearestTowardZero_380) {

    auto result = nearest_toward_minus_infinity_static_boundary_t::delegate(0, MockFunc{});

    EXPECT_EQ(result, 0);

}
