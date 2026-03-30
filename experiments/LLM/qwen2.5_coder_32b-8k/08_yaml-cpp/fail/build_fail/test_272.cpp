#include <gtest/gtest.h>

#include <cstdint>



namespace YAML { namespace jkj { namespace dragonbox {



template <typename Format, typename CarrierUInt, typename ExponentInt>

struct ieee754_binary_traits;



using carrier_uint = uint64_t;

using exponent_int = int32_t;



// Mocking the template struct for testing purposes

template <>

struct ieee754_binary_traits<Format, carrier_uint, exponent_int> {

    public:

        static constexpr exponent_int extract_exponent_bits(carrier_uint u) noexcept { return 0; }

        static constexpr carrier_uint extract_significand_bits(carrier_uint u) noexcept { return 0; }

        static constexpr carrier_uint remove_exponent_bits(carrier_uint u) noexcept { return 0; }

        static constexpr carrier_uint remove_sign_bit_and_shift(carrier_uint u) noexcept;

        static constexpr exponent_int binary_exponent(exponent_int exponent_bits) noexcept { return 0; }

        static constexpr carrier_uint binary_significand(carrier_uint significand_bits, exponent_int exponent_bits) noexcept { return 0; }

        static constexpr bool is_nonzero(carrier_uint u) noexcept { return false; }

        static constexpr bool is_positive(carrier_uint u) noexcept { return false; }

        static constexpr bool is_negative(carrier_uint u) noexcept { return false; }

        static constexpr bool is_finite(exponent_int exponent_bits) noexcept { return false; }

        static constexpr bool has_all_zero_significand_bits(carrier_uint u) noexcept { return false; }

        static constexpr bool has_even_significand_bits(carrier_uint u) noexcept { return false; }

};



template <>

constexpr carrier_uint ieee754_binary_traits<Format, carrier_uint, exponent_int>::remove_sign_bit_and_shift(carrier_uint u) noexcept {

    return carrier_uint((carrier_uint(u) << 1) & ((((carrier_uint(1) << (63)) - 1u) << 1) | 1u));

}



} } }



using namespace YAML::jkj::dragonbox;



class DragonboxTest_272 : public ::testing::Test {

protected:

    using Format = void; // Placeholder for actual format type

};



TEST_F(DragonboxTest_272, RemoveSignBitAndShift_ZeroInput_272) {

    carrier_uint input = 0;

    carrier_uint expected_output = 0;

    EXPECT_EQ(ieee754_binary_traits<Format, carrier_uint, exponent_int>::remove_sign_bit_and_shift(input), expected_output);

}



TEST_F(DragonboxTest_272, RemoveSignBitAndShift_MaxInput_272) {

    carrier_uint input = std::numeric_limits<carrier_uint>::max();

    carrier_uint expected_output = (input << 1) & ((((carrier_uint(1) << 63)) - 1u) << 1) | 1u;

    EXPECT_EQ(ieee754_binary_traits<Format, carrier_uint, exponent_int>::remove_sign_bit_and_shift(input), expected_output);

}



TEST_F(DragonboxTest_272, RemoveSignBitAndShift_SingleBitSet_272) {

    carrier_uint input = 1;

    carrier_uint expected_output = 2 & ((((carrier_uint(1) << 63)) - 1u) << 1) | 1u;

    EXPECT_EQ(ieee754_binary_traits<Format, carrier_uint, exponent_int>::remove_sign_bit_and_shift(input), expected_output);

}



TEST_F(DragonboxTest_272, RemoveSignBitAndShift_SignBitSet_272) {

    carrier_uint input = (carrier_uint(1) << 63);

    carrier_uint expected_output = 0;

    EXPECT_EQ(ieee754_binary_traits<Format, carrier_uint, exponent_int>::remove_sign_bit_and_shift(input), expected_output);

}



TEST_F(DragonboxTest_272, RemoveSignBitAndShift_RandomInput_272) {

    carrier_uint input = 0b1101100110011001100110011001100110011001100110011001100110011001;

    carrier_uint expected_output = (input << 1) & ((((carrier_uint(1) << 63)) - 1u) << 1) | 1u;

    EXPECT_EQ(ieee754_binary_traits<Format, carrier_uint, exponent_int>::remove_sign_bit_and_shift(input), expected_output);

}
