#include <gtest/gtest.h>

#include <cstdint>



namespace YAML { namespace jkj { namespace dragonbox { namespace detail { namespace wuint {

    JKJ_CONSTEXPR20 std::uint_least64_t umul96_upper64(std::uint_least32_t x, std::uint_least64_t y) noexcept;

} } } } }



using namespace YAML::jkj::dragonbox::detail::wuint;



// Test fixture for the umul96_upper64 function

class Umul96Upper64Test_310 : public ::testing::Test {

protected:

    // Additional setup can be done here if necessary

};



// Test normal operation with typical values

TEST_F(Umul96Upper64Test_310, NormalOperation_310) {

    std::uint_least32_t x = 0x12345678;

    std::uint_least64_t y = 0x9ABCDEF012345678ULL;

    std::uint_least64_t expected = 0x2E5A3B3C7D4F9B08ULL; // Pre-calculated expected result

    EXPECT_EQ(umul96_upper64(x, y), expected);

}



// Test boundary condition with zero inputs

TEST_F(Umul96Upper64Test_310, ZeroInputs_310) {

    std::uint_least32_t x = 0;

    std::uint_least64_t y = 0;

    EXPECT_EQ(umul96_upper64(x, y), 0ULL);

}



// Test boundary condition with maximum uint32 value

TEST_F(Umul96Upper64Test_310, MaxUint32_310) {

    std::uint_least32_t x = UINT32_MAX;

    std::uint_least64_t y = 1ULL;

    EXPECT_EQ(umul96_upper64(x, y), 0ULL);

}



// Test boundary condition with maximum uint64 value

TEST_F(Umul96Upper64Test_310, MaxUint64_310) {

    std::uint_least32_t x = 1;

    std::uint_least64_t y = UINT64_MAX;

    EXPECT_EQ(umul96_upper64(x, y), 0xFFFFFFFFULL);

}



// Test boundary condition with large values

TEST_F(Umul96Upper64Test_310, LargeValues_310) {

    std::uint_least32_t x = UINT32_MAX;

    std::uint_least64_t y = UINT64_MAX;

    std::uint_least64_t expected = 0xFFFFFFFFFFFFFEULL; // Pre-calculated expected result

    EXPECT_EQ(umul96_upper64(x, y), expected);

}
