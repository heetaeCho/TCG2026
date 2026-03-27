#include <gtest/gtest.h>

#include "dragonbox.h"



using namespace YAML::jkj::dragonbox;

using namespace YAML::jkj::dragonbox::detail;



// Mocking policies for testing purposes

struct MockSignPolicy {

    template <typename SignificandType, typename ExponentType>

    static auto handle_sign(SignificandType s, ExponentType e) {

        return std::make_pair(s, e);

    }

};



struct MockTrailingZeroPolicy {

    template <typename FormatTraits, typename DecimalSignificandType, typename ExponentType>

    static auto on_trailing_zeros(DecimalSignificandType ds, ExponentType e) {

        return std::make_pair(ds, e);

    }



    template <typename FormatTraits, typename DecimalSignificandType, typename ExponentType>

    static auto no_trailing_zeros(DecimalSignificandType ds, ExponentType e) {

        return std::make_pair(ds, e);

    }

};



struct MockIntervalTypeProvider {

    static auto shorter_interval(signed_significand_bits<ieee754_binary64> s) {

        // Simplified interval type for testing

        return std::make_pair(false, true); // include_left_endpoint, include_right_endpoint

    }



    static auto normal_interval(signed_significand_bits<ieee754_binary64> s) {

        // Simplified interval type for testing

        return std::make_pair(true, false); // include_left_endpoint, include_right_endpoint

    }

};



struct MockBinaryToDecimalRoundingPolicy {

    static constexpr bool prefer_round_down(unsigned long long decimal_significand) {

        return false;

    }



    enum class tag_t { do_not_care };

    static constexpr tag_t tag = tag_t::do_not_care;

};



struct MockCachePolicy {

    template <typename Format, typename ShiftAmountType>

    static auto get_cache(int exponent) {

        // Simplified cache retrieval for testing

        return std::make_pair(1ull << 52, 0);

    }

};



struct MockPreferredIntegerTypesPolicy {

    using carrier_uint = unsigned long long;

    template <typename FormatTraits>

    using shift_amount_type = int;



    template <typename FormatTraits, typename CacheEntryType, int CacheBits>

    struct multiplication_traits {

        static auto compute_left_endpoint_for_shorter_interval_case(auto cache, auto beta) {

            return 1ull << (52 - beta);

        }



        static auto compute_right_endpoint_for_shorter_interval_case(auto cache, auto beta) {

            return (1ull << (53 - beta)) - 1;

        }



        static auto compute_round_up_for_shorter_interval_case(auto cache, auto beta) {

            return (1ull << (52 - beta)) + 1;

        }



        static auto compute_delta(auto cache, auto beta) {

            return 1ull << (beta - 3);

        }



        struct result_type {

            unsigned long long integer_part;

            bool is_integer;

        };



        static auto compute_mul(unsigned long long significand, auto cache) {

            return result_type{significand * cache.first, false};

        }



        static auto compute_mul_parity(unsigned long long significand, auto cache, int beta) {

            return result_type{(significand - 1) * cache.first, false};

        }

    };

};



// Test fixture for dragonbox::detail::impl

class DragonboxImplTest_406 : public ::testing::Test {

protected:

    using FormatTraits = ieee754_binary64;

    using SignPolicy = MockSignPolicy;

    using TrailingZeroPolicy = MockTrailingZeroPolicy;

    using IntervalTypeProvider = MockIntervalTypeProvider;

    using BinaryToDecimalRoundingPolicy = MockBinaryToDecimalRoundingPolicy;

    using CachePolicy = MockCachePolicy;

    using PreferredIntegerTypesPolicy = MockPreferredIntegerTypesPolicy;



    impl<FormatTraits> testImpl;

};



// Test case for normal operation

TEST_F(DragonboxImplTest_406, NormalOperationWithExponentBits_406) {

    signed_significand_bits<FormatTraits> s{1ull << 52};

    exponent_int exponent_bits = -10;



    auto result = testImpl.template compute_nearest<SignPolicy, TrailingZeroPolicy, IntervalTypeProvider, BinaryToDecimalRoundingPolicy, CachePolicy, PreferredIntegerTypesPolicy>(s, exponent_bits);



    // Verify the return value

    EXPECT_EQ(result.first, 4503599627370496ull); // Expected decimal significand

    EXPECT_EQ(result.second, -10); // Expected decimal exponent

}



// Test case for boundary condition with zero significand and non-zero exponent bits

TEST_F(DragonboxImplTest_406, BoundaryConditionZeroSignificand_406) {

    signed_significand_bits<FormatTraits> s{0};

    exponent_int exponent_bits = 127;



    auto result = testImpl.template compute_nearest<SignPolicy, TrailingZeroPolicy, IntervalTypeProvider, BinaryToDecimalRoundingPolicy, CachePolicy, PreferredIntegerTypesPolicy>(s, exponent_bits);



    // Verify the return value

    EXPECT_EQ(result.first, 0ull); // Expected decimal significand

    EXPECT_EQ(result.second, -127); // Expected decimal exponent

}



// Test case for boundary condition with maximum significand and zero exponent bits

TEST_F(DragonboxImplTest_406, BoundaryConditionMaxSignificandZeroExponentBits_406) {

    signed_significand_bits<FormatTraits> s{(1ull << 53) - 1};

    exponent_int exponent_bits = 0;



    auto result = testImpl.template compute_nearest<SignPolicy, TrailingZeroPolicy, IntervalTypeProvider, BinaryToDecimalRoundingPolicy, CachePolicy, PreferredIntegerTypesPolicy>(s, exponent_bits);



    // Verify the return value

    EXPECT_EQ(result.first, 9007199254740991ull); // Expected decimal significand

    EXPECT_EQ(result.second, -53); // Expected decimal exponent

}



// Test case for exceptional or error cases (if observable through the interface)

TEST_F(DragonboxImplTest_406, ExceptionalCaseInvalidExponentBits_406) {

    signed_significand_bits<FormatTraits> s{1ull << 52};

    exponent_int exponent_bits = -1074; // Below the minimum possible value for double precision



    auto result = testImpl.template compute_nearest<SignPolicy, TrailingZeroPolicy, IntervalTypeProvider, BinaryToDecimalRoundingPolicy, CachePolicy, PreferredIntegerTypesPolicy>(s, exponent_bits);



    // Verify the return value

    EXPECT_EQ(result.first, 0ull); // Expected decimal significand (underflow)

    EXPECT_EQ(result.second, -1074); // Expected decimal exponent

}
