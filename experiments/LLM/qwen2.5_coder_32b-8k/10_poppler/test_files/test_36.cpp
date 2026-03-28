#include <gtest/gtest.h>

#include "TestProjects/poppler/goo/gbase64.h"



TEST(gbase64Encode_Test_36, EmptyInput_ReturnsEmptyString_36) {

    std::string result = gbase64Encode(nullptr, 0);

    EXPECT_EQ(result, "");

}



TEST(gbase64Encode_Test_36, SingleByteInput_ReturnsCorrectBase64_36) {

    unsigned char input[] = {0x12};

    std::string result = gbase64Encode(input, 1);

    EXPECT_EQ(result, "Eg==");

}



TEST(gbase64Encode_Test_36, TwoBytesInput_ReturnsCorrectBase64_36) {

    unsigned char input[] = {0x12, 0x34};

    std::string result = gbase64Encode(input, 2);

    EXPECT_EQ(result, "EjQ=");

}



TEST(gbase64Encode_Test_36, ThreeBytesInput_ReturnsCorrectBase64_36) {

    unsigned char input[] = {0x12, 0x34, 0x56};

    std::string result = gbase64Encode(input, 3);

    EXPECT_EQ(result, "EjR2");

}



TEST(gbase64Encode_Test_36, FourBytesInput_ReturnsCorrectBase64_36) {

    unsigned char input[] = {0x12, 0x34, 0x56, 0x78};

    std::string result = gbase64Encode(input, 4);

    EXPECT_EQ(result, "EjR2eA==");

}



TEST(gbase64Encode_Test_36, MultipleOfThreeBytes_ReturnsCorrectBase64_36) {

    unsigned char input[] = {0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc};

    std::string result = gbase64Encode(input, 6);

    EXPECT_EQ(result, "EjR2eGm8");

}



TEST(gbase64Encode_Test_36, ArbitraryBytes_ReturnsCorrectBase64_36) {

    unsigned char input[] = {0xde, 0xad, 0xbe, 0xef};

    std::string result = gbase64Encode(input, 4);

    EXPECT_EQ(result, "3q2+");

}



TEST(gbase64Encode_Test_36, AllFFBytes_ReturnsCorrectBase64_36) {

    unsigned char input[] = {0xff, 0xff, 0xff};

    std::string result = gbase64Encode(input, 3);

    EXPECT_EQ(result, "////");

}
