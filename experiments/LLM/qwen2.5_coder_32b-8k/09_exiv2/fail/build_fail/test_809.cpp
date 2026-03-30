#include <gtest/gtest.h>

#include "exiv2/value.hpp"



namespace {



using namespace Exiv2;



class StringValueBaseTest : public ::testing::Test {

protected:

    StringValueBaseTest() : stringValueBase(TypeId::string, "12345") {}



    StringValueBase stringValueBase;

};



TEST_F(StringValueBaseTest_809, toInt64_NormalOperation_809) {

    EXPECT_EQ(stringValueBase.toInt64(0), 12345);

}



TEST_F(StringValueBaseTest_809, toInt64_OutOfBounds_809) {

    stringValueBase.value_ = "123";

    EXPECT_THROW(stringValueBase.toInt64(1), std::out_of_range);

}



TEST_F(StringValueBaseTest_809, toInt64_EmptyString_809) {

    stringValueBase.value_ = "";

    EXPECT_THROW(stringValueBase.toInt64(0), std::invalid_argument);

}



TEST_F(StringValueBaseTest_809, toInt64_NonNumericString_809) {

    stringValueBase.value_ = "abc";

    EXPECT_THROW(stringValueBase.toInt64(0), std::invalid_argument);

}



}  // namespace
