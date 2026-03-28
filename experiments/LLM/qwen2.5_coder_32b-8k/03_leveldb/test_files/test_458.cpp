#include <gtest/gtest.h>

#include "util/logging.cc"



namespace leveldb {



class NumberToStringTest_458 : public ::testing::Test {

protected:

    // You can set up any necessary preconditions here

};



TEST_F(NumberToStringTest_458, NormalOperation_458) {

    EXPECT_EQ("123", NumberToString(123));

}



TEST_F(NumberToStringTest_458, ZeroValue_458) {

    EXPECT_EQ("0", NumberToString(0));

}



TEST_F(NumberToStringTest_458, LargeNumber_458) {

    EXPECT_EQ("18446744073709551615", NumberToString(uint64_t(-1))); // uint64_max

}



TEST_F(NumberToStringTest_458, MaxValue_458) {

    EXPECT_EQ("18446744073709551615", NumberToString(18446744073709551615));

}



}  // namespace leveldb
