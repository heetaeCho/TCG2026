#include <gtest/gtest.h>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"



namespace YAML { namespace jkj { namespace dragonbox { namespace policy { namespace decimal_to_binary_rounding {



// Mock function to verify delegate behavior

struct MockFunc {

    template <class RoundingMode, class... Args>

    JKJ_FORCEINLINE JKJ_SAFEBUFFERS constexpr auto operator()(RoundingMode mode, Args... args) const noexcept {

        if (mode == nearest_toward_zero) {

            called_with_nearest_toward_zero = true;

        } else if (mode == nearest_away_from_zero) {

            called_with_nearest_away_from_zero = true;

        }

        return 0; // Return value does not matter for this test

    }



    mutable bool called_with_nearest_toward_zero = false;

    mutable bool called_with_nearest_away_from_zero = false;

};



// Test fixture

class NearestTowardPlusInfinityStaticBoundaryTest : public ::testing::Test {

protected:

    MockFunc mock_func;



    template <class SignedSignificandBits>

    constexpr void TestDelegateBehavior(SignedSignificandBits s, bool expected_nearest_toward_zero) const {

        nearest_toward_plus_infinity_static_boundary_t::delegate(s, mock_func);

        EXPECT_EQ(mock_func.called_with_nearest_toward_zero, expected_nearest_toward_zero);

        EXPECT_EQ(mock_func.called_with_nearest_away_from_zero, !expected_nearest_toward_zero);

    }

};



// Test cases

TEST_F(NearestTowardPlusInfinityStaticBoundaryTest_379, DelegateCallsNearestTowardZeroForNegativeSignificand_379) {

    struct NegativeSignificandBits { static constexpr bool is_negative() noexcept { return true; } };

    TestDelegateBehavior(NegativeSignificandBits{}, true);

}



TEST_F(NearestTowardPlusInfinityStaticBoundaryTest_379, DelegateCallsNearestAwayFromZeroForPositiveSignificand_379) {

    struct PositiveSignificandBits { static constexpr bool is_negative() noexcept { return false; } };

    TestDelegateBehavior(PositiveSignificandBits{}, false);

}



TEST_F(NearestTowardPlusInfinityStaticBoundaryTest_379, DelegateCallsNearestAwayFromZeroForZeroSignificand_379) {

    struct ZeroSignificandBits { static constexpr bool is_negative() noexcept { return false; } };

    TestDelegateBehavior(ZeroSignificandBits{}, false);

}



} } } } }
