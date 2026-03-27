#include <gtest/gtest.h>

#include <cstdint>

#include <cstring>



namespace Catch { namespace Detail {

    uint32_t convertToBits(float f);

} }



class ConvertToBitsTest_606 : public ::testing::Test {

protected:

    using Converter = decltype(&Catch::Detail::convertToBits);



    Converter converter = &Catch::Detail::convertToBits;

};



TEST_F(ConvertToBitsTest_606, PositiveNormalNumber_606) {

    float input = 1.5f; // Binary representation: 0x3FC00000

    uint32_t expectedOutput = 0x3FC00000;

    EXPECT_EQ(converter(input), expectedOutput);

}



TEST_F(ConvertToBitsTest_606, NegativeNormalNumber_606) {

    float input = -1.5f; // Binary representation: 0xBFC00000

    uint32_t expectedOutput = 0xBFC00000;

    EXPECT_EQ(converter(input), expectedOutput);

}



TEST_F(ConvertToBitsTest_606, Zero_606) {

    float input = 0.0f; // Binary representation: 0x00000000

    uint32_t expectedOutput = 0x00000000;

    EXPECT_EQ(converter(input), expectedOutput);

}



TEST_F(ConvertToBitsTest_606, NegativeZero_606) {

    float input = -0.0f; // Binary representation: 0x80000000

    uint32_t expectedOutput = 0x80000000;

    EXPECT_EQ(converter(input), expectedOutput);

}



TEST_F(ConvertToBitsTest_606, PositiveInfinity_606) {

    float input = std::numeric_limits<float>::infinity(); // Binary representation: 0x7F800000

    uint32_t expectedOutput = 0x7F800000;

    EXPECT_EQ(converter(input), expectedOutput);

}



TEST_F(ConvertToBitsTest_606, NegativeInfinity_606) {

    float input = -std::numeric_limits<float>::infinity(); // Binary representation: 0xFF800000

    uint32_t expectedOutput = 0xFF800000;

    EXPECT_EQ(converter(input), expectedOutput);

}



TEST_F(ConvertToBitsTest_606, NaN_606) {

    float input = std::numeric_limits<float>::quiet_NaN(); // Binary representation: varies but should have exponent of all 1s and non-zero fraction

    uint32_t output = converter(input);

    EXPECT_EQ((output & 0x7F800000), 0x7F800000); // Exponent should be all 1s

    EXPECT_NE((output & 0x007FFFFF), 0x00000000); // Fraction should not be zero

}
