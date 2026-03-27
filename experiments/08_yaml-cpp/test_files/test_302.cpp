#include <gtest/gtest.h>

#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"



namespace YAML { namespace jkj { namespace dragonbox { namespace detail { namespace bits {



using namespace std;



TEST(rotr_Test_302, RotateZeroBits_302) {

    constexpr size_t bit_width = 8;

    uint8_t n = 0b10101010;

    unsigned int r = 0;

    EXPECT_EQ(rotr<bit_width>(n, r), 0b10101010);

}



TEST(rotr_Test_302, RotateFullBits_302) {

    constexpr size_t bit_width = 8;

    uint8_t n = 0b10101010;

    unsigned int r = 8;

    EXPECT_EQ(rotr<bit_width>(n, r), 0b10101010);

}



TEST(rotr_Test_302, RotateOneBitLeft_302) {

    constexpr size_t bit_width = 8;

    uint8_t n = 0b00000001;

    unsigned int r = 1;

    EXPECT_EQ(rotr<bit_width>(n, r), 0b10000000);

}



TEST(rotr_Test_302, RotateOneBitRight_302) {

    constexpr size_t bit_width = 8;

    uint8_t n = 0b10000000;

    unsigned int r = 1;

    EXPECT_EQ(rotr<bit_width>(n, r), 0b00000001);

}



TEST(rotr_Test_302, RotateMultipleBits_302) {

    constexpr size_t bit_width = 8;

    uint8_t n = 0b10101010;

    unsigned int r = 3;

    EXPECT_EQ(rotr<bit_width>(n, r), 0b01010101);

}



TEST(rotr_Test_302, RotateWithMasking_302) {

    constexpr size_t bit_width = 8;

    uint8_t n = 0b10101010;

    unsigned int r = 9; // Effective rotation of 1

    EXPECT_EQ(rotr<bit_width>(n, r), 0b01010101);

}



TEST(rotr_Test_302, RotateLargerBitWidth_302) {

    constexpr size_t bit_width = 16;

    uint16_t n = 0b0000000100000000;

    unsigned int r = 1;

    EXPECT_EQ(rotr<bit_width>(n, r), 0b1000000000000000);

}



TEST(rotr_Test_302, RotateAllOnes_302) {

    constexpr size_t bit_width = 8;

    uint8_t n = 0b11111111;

    unsigned int r = 4;

    EXPECT_EQ(rotr<bit_width>(n, r), 0b11111111);

}



TEST(rotr_Test_302, RotateAllZeros_302) {

    constexpr size_t bit_width = 8;

    uint8_t n = 0b00000000;

    unsigned int r = 4;

    EXPECT_EQ(rotr<bit_width>(n, r), 0b00000000);

}



}}}}} // namespace YAML::jkj::dragonbox::detail::bits
