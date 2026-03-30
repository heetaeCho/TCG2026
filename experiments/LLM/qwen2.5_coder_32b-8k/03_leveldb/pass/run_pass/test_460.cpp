#include <gtest/gtest.h>

#include "util/logging.cc"

#include "leveldb/slice.h"



using namespace leveldb;



TEST(ConsumeDecimalNumberTest_460, NormalOperation_460) {

  Slice input("12345");

  uint64_t value;

  EXPECT_TRUE(ConsumeDecimalNumber(&input, &value));

  EXPECT_EQ(value, 12345);

  EXPECT_EQ(input.ToString(), "");

}



TEST(ConsumeDecimalNumberTest_460, LeadingZeroes_460) {

  Slice input("00123");

  uint64_t value;

  EXPECT_TRUE(ConsumeDecimalNumber(&input, &value));

  EXPECT_EQ(value, 123);

  EXPECT_EQ(input.ToString(), "");

}



TEST(ConsumeDecimalNumberTest_460, NoDigits_460) {

  Slice input("abc");

  uint64_t value;

  EXPECT_FALSE(ConsumeDecimalNumber(&input, &value));

  EXPECT_EQ(value, 0);

  EXPECT_EQ(input.ToString(), "abc");

}



TEST(ConsumeDecimalNumberTest_460, MixedContent_460) {

  Slice input("123abc");

  uint64_t value;

  EXPECT_TRUE(ConsumeDecimalNumber(&input, &value));

  EXPECT_EQ(value, 123);

  EXPECT_EQ(input.ToString(), "abc");

}



TEST(ConsumeDecimalNumberTest_460, MaxUint64_460) {

  Slice input("18446744073709551615");

  uint64_t value;

  EXPECT_TRUE(ConsumeDecimalNumber(&input, &value));

  EXPECT_EQ(value, std::numeric_limits<uint64_t>::max());

  EXPECT_EQ(input.ToString(), "");

}



TEST(ConsumeDecimalNumberTest_460, Overflow_460) {

  Slice input("18446744073709551616");

  uint64_t value;

  EXPECT_FALSE(ConsumeDecimalNumber(&input, &value));

  EXPECT_EQ(value, 0);

  EXPECT_EQ(input.ToString(), "18446744073709551616");

}



TEST(ConsumeDecimalNumberTest_460, EmptyInput_460) {

  Slice input("");

  uint64_t value;

  EXPECT_FALSE(ConsumeDecimalNumber(&input, &value));

  EXPECT_EQ(value, 0);

  EXPECT_EQ(input.ToString(), "");

}
