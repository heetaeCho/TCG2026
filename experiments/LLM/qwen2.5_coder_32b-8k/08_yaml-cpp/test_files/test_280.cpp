#include <gtest/gtest.h>



namespace YAML { namespace jkj { namespace dragonbox {



using carrier_uint = uint64_t;



TEST_F(DragonboxTest_280, HasEvenSignificandBits_Zero_280) {

    EXPECT_TRUE(ieee754_binary_traits</*Format*/, carrier_uint, int>::has_even_significand_bits(0));

}



TEST_F(DragonboxTest_280, HasEvenSignificandBits_Even_280) {

    EXPECT_TRUE(ieee754_binary_traits</*Format*/, carrier_uint, int>::has_even_significand_bits(2));

}



TEST_F(DragonboxTest_280, HasEvenSignificandBits_Odd_280) {

    EXPECT_FALSE(ieee754_binary_traits</*Format*/, carrier_uint, int>::has_even_significand_bits(1));

}



TEST_F(DragonboxTest_280, HasEvenSignificandBits_Max_280) {

    EXPECT_EQ(ieee754_binary_traits</*Format*/, carrier_uint, int>::has_even_significand_bits(std::numeric_limits<carrier_uint>::max()), 

              (std::numeric_limits<carrier_uint>::max() % 2 == 0));

}



TEST_F(DragonboxTest_280, HasEvenSignificandBits_Boundary_280) {

    EXPECT_TRUE(ieee754_binary_traits</*Format*/, carrier_uint, int>::has_even_significand_bits(std::numeric_limits<carrier_uint>::max() - 1));

    EXPECT_FALSE(ieee754_binary_traits</*Format*/, carrier_uint, int>::has_even_significand_bits(std::numeric_limits<carrier_uint>::max()));

}



}}} // namespace YAML::jkj::dragonbox

```


