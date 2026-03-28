// File: yaml-cpp/node/convert_test_605.cpp

#include <gtest/gtest.h>

#include <limits>
#include <sstream>
#include <string>

#include "yaml-cpp/node/convert.h"

namespace {

class ConvertStreamToTest_605 : public ::testing::Test {
 protected:
  template <typename T>
  static bool CallConvert_605(const std::string& input, T& out) {
    std::stringstream ss;
    ss.str(input);
    ss.clear();  // ensure good() even if reused in future edits
    return YAML::conversion::ConvertStreamTo<T>(ss, out);
  }
};

TEST_F(ConvertStreamToTest_605, SignedChar_ParsesZero_605) {
  signed char out = static_cast<signed char>(42);
  EXPECT_TRUE(CallConvert_605("0", out));
  EXPECT_EQ(out, static_cast<signed char>(0));
}

TEST_F(ConvertStreamToTest_605, UnsignedChar_ParsesMax_605) {
  unsigned char out = static_cast<unsigned char>(7);
  const int max_v = (std::numeric_limits<unsigned char>::max)();
  EXPECT_TRUE(CallConvert_605(std::to_string(max_v), out));
  EXPECT_EQ(out, static_cast<unsigned char>(max_v));
}

TEST_F(ConvertStreamToTest_605, SignedChar_ParsesMin_605) {
  signed char out = static_cast<signed char>(7);
  const int min_v = (std::numeric_limits<signed char>::min)();
  EXPECT_TRUE(CallConvert_605(std::to_string(min_v), out));
  EXPECT_EQ(out, static_cast<signed char>(min_v));
}

TEST_F(ConvertStreamToTest_605, TrailingWhitespace_IsAllowed_605) {
  signed char out1 = static_cast<signed char>(1);
  unsigned char out2 = static_cast<unsigned char>(2);

  EXPECT_TRUE(CallConvert_605("12 ", out1));
  EXPECT_EQ(out1, static_cast<signed char>(12));

  EXPECT_TRUE(CallConvert_605("34\n\t", out2));
  EXPECT_EQ(out2, static_cast<unsigned char>(34));
}

TEST_F(ConvertStreamToTest_605, LeadingWhitespace_IsRejected_605) {
  signed char out = static_cast<signed char>(9);
  EXPECT_FALSE(CallConvert_605(" 1", out));
  EXPECT_EQ(out, static_cast<signed char>(9));  // unchanged on failure
}

TEST_F(ConvertStreamToTest_605, EmptyInput_IsRejected_605) {
  unsigned char out = static_cast<unsigned char>(9);
  EXPECT_FALSE(CallConvert_605("", out));
  EXPECT_EQ(out, static_cast<unsigned char>(9));  // unchanged on failure
}

TEST_F(ConvertStreamToTest_605, NonNumericInput_IsRejected_605) {
  signed char out = static_cast<signed char>(9);
  EXPECT_FALSE(CallConvert_605("abc", out));
  EXPECT_EQ(out, static_cast<signed char>(9));  // unchanged on failure
}

TEST_F(ConvertStreamToTest_605, TrailingNonWhitespace_IsRejected_605) {
  unsigned char out = static_cast<unsigned char>(9);

  EXPECT_FALSE(CallConvert_605("7x", out));
  EXPECT_EQ(out, static_cast<unsigned char>(9));  // unchanged on failure

  EXPECT_FALSE(CallConvert_605("7  x", out));
  EXPECT_EQ(out, static_cast<unsigned char>(9));  // unchanged on failure
}

TEST_F(ConvertStreamToTest_605, SignedChar_OutOfRange_IsRejected_605) {
  signed char out = static_cast<signed char>(11);

  const int min_v = (std::numeric_limits<signed char>::min)();
  const int max_v = (std::numeric_limits<signed char>::max)();

  EXPECT_FALSE(CallConvert_605(std::to_string(min_v - 1), out));
  EXPECT_EQ(out, static_cast<signed char>(11));

  EXPECT_FALSE(CallConvert_605(std::to_string(max_v + 1), out));
  EXPECT_EQ(out, static_cast<signed char>(11));
}

TEST_F(ConvertStreamToTest_605, UnsignedChar_OutOfRange_IsRejected_605) {
  unsigned char out = static_cast<unsigned char>(11);

  const int max_v = (std::numeric_limits<unsigned char>::max)();

  EXPECT_FALSE(CallConvert_605("-1", out));
  EXPECT_EQ(out, static_cast<unsigned char>(11));

  EXPECT_FALSE(CallConvert_605(std::to_string(max_v + 1), out));
  EXPECT_EQ(out, static_cast<unsigned char>(11));
}

}  // namespace