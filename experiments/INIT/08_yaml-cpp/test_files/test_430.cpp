// File: ./TestProjects/yaml-cpp/test/fptostring_converttochars_test.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <cstring>
#include <limits>
#include <string>

namespace YAML {
namespace detail {
namespace fp_formatting {

// Forward declaration (the implementation lives in src/fptostring.cpp)
int ConvertToChars(char* begin, char* end, size_t value, int width = 1);

}  // namespace fp_formatting
}  // namespace detail
}  // namespace YAML

namespace {

class ConvertToCharsTest_430 : public ::testing::Test {
 protected:
  static constexpr size_t kBufSize = 64;

  void SetUp() override {
    std::memset(buf_, 'X', sizeof(buf_));
  }

  char* begin() { return buf_; }
  char* end_ptr(size_t n) { return buf_ + n; }

  char buf_[kBufSize];
};

TEST_F(ConvertToCharsTest_430, ConvertsSingleDigitWithDefaultWidth_430) {
  int n = YAML::detail::fp_formatting::ConvertToChars(begin(), end_ptr(32), 7);
  EXPECT_EQ(n, 1);
  EXPECT_EQ(std::string(begin(), begin() + n), "7");
  EXPECT_EQ(buf_[n], 'X');  // only first n bytes should be moved to begin
}

TEST_F(ConvertToCharsTest_430, ConvertsMultiDigitNoPaddingWhenWidthIsOne_430) {
  int n = YAML::detail::fp_formatting::ConvertToChars(begin(), end_ptr(32), 12345, 1);
  EXPECT_EQ(n, 5);
  EXPECT_EQ(std::string(begin(), begin() + n), "12345");
  EXPECT_EQ(buf_[n], 'X');
}

TEST_F(ConvertToCharsTest_430, PadsWithLeadingZerosWhenWidthExceedsDigits_430) {
  int n = YAML::detail::fp_formatting::ConvertToChars(begin(), end_ptr(32), 42, 5);
  EXPECT_EQ(n, 5);
  EXPECT_EQ(std::string(begin(), begin() + n), "00042");
  EXPECT_EQ(buf_[n], 'X');
}

TEST_F(ConvertToCharsTest_430, ValueZeroPadsToWidth_430) {
  int n = YAML::detail::fp_formatting::ConvertToChars(begin(), end_ptr(32), 0u, 1);
  EXPECT_EQ(n, 1);
  EXPECT_EQ(std::string(begin(), begin() + n), "0");

  std::memset(buf_, 'X', sizeof(buf_));
  n = YAML::detail::fp_formatting::ConvertToChars(begin(), end_ptr(32), 0u, 6);
  EXPECT_EQ(n, 6);
  EXPECT_EQ(std::string(begin(), begin() + n), "000000");
  EXPECT_EQ(buf_[n], 'X');
}

TEST_F(ConvertToCharsTest_430, UsesAtLeastTwentyBytesOfAvailableSpace_430) {
  // end-begin == 20 is allowed per checks/asserts.
  int n = YAML::detail::fp_formatting::ConvertToChars(begin(), end_ptr(20), 999u, 3);
  EXPECT_EQ(n, 3);
  EXPECT_EQ(std::string(begin(), begin() + n), "999");
  EXPECT_EQ(buf_[n], 'X');
}

TEST_F(ConvertToCharsTest_430, ConvertsMaxSizeT_430) {
  const size_t v = std::numeric_limits<size_t>::max();
  const std::string expected = std::to_string(v);

  int n = YAML::detail::fp_formatting::ConvertToChars(begin(), end_ptr(32), v, 1);
  EXPECT_EQ(n, static_cast<int>(expected.size()));
  EXPECT_EQ(std::string(begin(), begin() + n), expected);
  EXPECT_EQ(buf_[n], 'X');
}

TEST_F(ConvertToCharsTest_430, WidthGreaterThanDigitsStillReturnsWidth_430) {
  // Using a max-ish value but ask for width 20; expect leading zeros if digits < 20.
  // (For 64-bit size_t max, digits should be 20, so this also covers exact-width case.)
  const size_t v = std::numeric_limits<size_t>::max();
  const std::string s = std::to_string(v);

  int n = YAML::detail::fp_formatting::ConvertToChars(begin(), end_ptr(64), v, 20);
  EXPECT_EQ(n, 20);
  EXPECT_EQ(std::string(begin(), begin() + n), (s.size() >= 20 ? s : std::string(20 - s.size(), '0') + s));
}

#ifndef NDEBUG

TEST_F(ConvertToCharsTest_430, DeathWhenWidthLessThanOne_430) {
  // First assertion is width >= 1
  EXPECT_DEATH(
      (void)YAML::detail::fp_formatting::ConvertToChars(begin(), end_ptr(32), 1u, 0),
      "");
}

TEST_F(ConvertToCharsTest_430, DeathWhenEndBeforeBegin_430) {
  // Assertion: end >= begin
  EXPECT_DEATH(
      (void)YAML::detail::fp_formatting::ConvertToChars(end_ptr(32), begin(), 1u, 1),
      "");
}

TEST_F(ConvertToCharsTest_430, DeathWhenBufferSmallerThanWidth_430) {
  // Assertion: end-begin >= width
  EXPECT_DEATH(
      (void)YAML::detail::fp_formatting::ConvertToChars(begin(), end_ptr(20), 1u, 21),
      "");
}

TEST_F(ConvertToCharsTest_430, DeathWhenBufferSmallerThanTwenty_430) {
  // Assertion: end-begin >= 20
  EXPECT_DEATH(
      (void)YAML::detail::fp_formatting::ConvertToChars(begin(), end_ptr(19), 1u, 1),
      "");
}

#else  // NDEBUG

TEST_F(ConvertToCharsTest_430, ReturnsMinusOneWhenWidthLessThanOne_430) {
  int n = YAML::detail::fp_formatting::ConvertToChars(begin(), end_ptr(32), 1u, 0);
  EXPECT_EQ(n, -1);
}

TEST_F(ConvertToCharsTest_430, ReturnsMinusOneWhenEndBeforeBegin_430) {
  int n = YAML::detail::fp_formatting::ConvertToChars(end_ptr(32), begin(), 1u, 1);
  EXPECT_EQ(n, -1);
}

TEST_F(ConvertToCharsTest_430, ReturnsMinusOneWhenBufferSmallerThanWidth_430) {
  int n = YAML::detail::fp_formatting::ConvertToChars(begin(), end_ptr(20), 1u, 21);
  EXPECT_EQ(n, -1);
}

TEST_F(ConvertToCharsTest_430, ReturnsMinusOneWhenBufferSmallerThanTwenty_430) {
  int n = YAML::detail::fp_formatting::ConvertToChars(begin(), end_ptr(19), 1u, 1);
  EXPECT_EQ(n, -1);
}

#endif  // NDEBUG

}  // namespa