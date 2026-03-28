#include <gtest/gtest.h>

#include "dragonbox.h"



using namespace YAML::jkj::dragonbox::policy::sign;



class IgnoreSignTest : public ::testing::Test {

protected:

    using SignedSignificandBits = int;

    using UnsignedDecimalFp = unsigned int;

};



TEST_F(IgnoreSignTest_333, HandleSign_PositiveValue_ReturnsSameValue_333) {

    SignedSignificandBits input = 42;

    UnsignedDecimalFp result = ignore_sign::handle_sign(input, 100u);

    EXPECT_EQ(result, 100u);

}



TEST_F(IgnoreSignTest_333, HandleSign_NegativeValue_ReturnsSameResult_333) {

    SignedSignificandBits input = -42;

    UnsignedDecimalFp result = ignore_sign::handle_sign(input, 100u);

    EXPECT_EQ(result, 100u);

}



TEST_F(IgnoreSignTest_333, HandleSign_ZeroValue_ReturnsSameResult_333) {

    SignedSignificandBits input = 0;

    UnsignedDecimalFp result = ignore_sign::handle_sign(input, 100u);

    EXPECT_EQ(result, 100u);

}



TEST_F(IgnoreSignTest_333, HandleSign_MaxUnsigned_ReturnsSameResult_333) {

    SignedSignificandBits input = 42;

    UnsignedDecimalFp result = ignore_sign::handle_sign(input, UINT_MAX);

    EXPECT_EQ(result, UINT_MAX);

}
