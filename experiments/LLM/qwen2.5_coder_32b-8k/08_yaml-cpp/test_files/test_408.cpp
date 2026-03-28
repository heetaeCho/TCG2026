#include <gtest/gtest.h>

#include "dragonbox.h"



using namespace YAML::jkj::dragonbox;

using namespace YAML::jkj::dragonbox::detail;



// Mock policies for testing

struct MockSignPolicy {

    template <typename SignificandType, typename ExponentType>

    static auto handle_sign(SignificandType s, ExponentType e) {

        return std::make_pair(s, e);

    }

};



struct MockTrailingZeroPolicy {

    template <typename Format, typename DecimalSignificandType, typename DecimalExponentType>

    static auto on_trailing_zeros(DecimalSignificandType ds, DecimalExponentType de) {

        return std::make_pair(ds, de);

    }



    template <typename Format, typename DecimalSignificandType, typename DecimalExponentType>

    static auto no_trailing_zeros(DecimalSignificandType ds, DecimalExponentType de) {

        return std::make_pair(ds, de);

    }

};



struct MockCachePolicy {

    template <typename Format, typename ShiftAmountType, int K>

    static auto get_cache() {

        // Provide a mock cache entry

        return 0;

    }

};



struct MockPreferredIntegerTypesPolicy {

    using shift_amount_type = int;



    template <typename Format, typename CacheEntryType, int CacheBits>

    struct multiplication_traits {

        static auto compute_delta(int cache, int beta) {

            return 1;

        }



        static auto compute_mul(int significand, int cache) {

            return std::make_pair(1, false);

        }



        static auto compute_mul_parity(int significand, int cache, int beta) {

            return std::make_pair(1, false);

        }

    };

};



struct FormatTraitsMock {

    using format = struct {

        static constexpr int exponent_bias = 0;

        static constexpr int significand_bits = 53;

        static constexpr int min_exponent = -1023;

        static constexpr int max_exponent = 1024;

    };



    static constexpr int min(int x, int y) noexcept {

        return (x < y) ? x : y;

    }



    static constexpr int max(int x, int y) noexcept {

        return (x > y) ? x : y;

    }

};



using MockImpl = impl<FormatTraitsMock>;



TEST_F(DragonboxTest_408, NormalOperation_408) {

    auto result = MockImpl::template compute_right_closed_directed<MockSignPolicy, MockTrailingZeroPolicy, MockCachePolicy, MockPreferredIntegerTypesPolicy>(1LL << 52, 0);

    EXPECT_EQ(result.first, 1);

    EXPECT_EQ(result.second, -308);

}



TEST_F(DragonboxTest_408, BoundaryCondition_ZeroExponent_408) {

    auto result = MockImpl::template compute_right_closed_directed<MockSignPolicy, MockTrailingZeroPolicy, MockCachePolicy, MockPreferredIntegerTypesPolicy>(1LL << 52, -1023);

    EXPECT_EQ(result.first, 1);

    EXPECT_EQ(result.second, -308);

}



TEST_F(DragonboxTest_408, BoundaryCondition_MaxExponent_408) {

    auto result = MockImpl::template compute_right_closed_directed<MockSignPolicy, MockTrailingZeroPolicy, MockCachePolicy, MockPreferredIntegerTypesPolicy>(1LL << 52, 1024);

    EXPECT_EQ(result.first, 1);

    EXPECT_EQ(result.second, -308);

}



TEST_F(DragonboxTest_408, BoundaryCondition_ZeroSignificand_408) {

    auto result = MockImpl::template compute_right_closed_directed<MockSignPolicy, MockTrailingZeroPolicy, MockCachePolicy, MockPreferredIntegerTypesPolicy>(0, 0);

    EXPECT_EQ(result.first, 1);

    EXPECT_EQ(result.second, -308);

}



TEST_F(DragonboxTest_408, ExceptionalCase_ShorterInterval_408) {

    auto result = MockImpl::template compute_right_closed_directed<MockSignPolicy, MockTrailingZeroPolicy, MockCachePolicy, MockPreferredIntegerTypesPolicy>(1LL << 52, -1);

    EXPECT_EQ(result.first, 1);

    EXPECT_EQ(result.second, -308);

}



TEST_F(DragonboxTest_408, ExternalInteraction_SignPolicy_408) {

    auto result = MockImpl::template compute_right_closed_directed<MockSignPolicy, MockTrailingZeroPolicy, MockCachePolicy, MockPreferredIntegerTypesPolicy>(-(1LL << 52), 0);

    EXPECT_EQ(result.first, -1);

    EXPECT_EQ(result.second, -308);

}



TEST_F(DragonboxTest_408, ExternalInteraction_TrailingZeroPolicy_408) {

    auto result = MockImpl::template compute_right_closed_directed<MockSignPolicy, MockTrailingZeroPolicy, MockCachePolicy, MockPreferredIntegerTypesPolicy>(1LL << 52, 0);

    EXPECT_EQ(result.first, 1);

    EXPECT_EQ(result.second, -308);

}
