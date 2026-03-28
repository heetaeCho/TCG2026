#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Decrypt.cc"



TEST(Sha512Sigma0Test_1641, NormalOperation_1641) {

    uint64_t input = 0x0123456789abcdef;

    uint64_t expected_output = (rotr(input, 1) ^ rotr(input, 8) ^ (input >> 7));

    EXPECT_EQ(sha512sigma0(input), expected_output);

}



TEST(Sha512Sigma0Test_1641, BoundaryConditionZero_1641) {

    uint64_t input = 0x0;

    uint64_t expected_output = (rotr(input, 1) ^ rotr(input, 8) ^ (input >> 7));

    EXPECT_EQ(sha512sigma0(input), expected_output);

}



TEST(Sha512Sigma0Test_1641, BoundaryConditionMax_1641) {

    uint64_t input = 0xffffffffffffffff;

    uint64_t expected_output = (rotr(input, 1) ^ rotr(input, 8) ^ (input >> 7));

    EXPECT_EQ(sha512sigma0(input), expected_output);

}



TEST(Sha512Sigma0Test_1641, RandomValue_1641) {

    uint64_t input = 0xdeadbeefcafebabe;

    uint64_t expected_output = (rotr(input, 1) ^ rotr(input, 8) ^ (input >> 7));

    EXPECT_EQ(sha512sigma0(input), expected_output);

}

```


