// File: test_emittermanip_floatprecision_test.cpp

#include <gtest/gtest.h>

#include <climits>
#include <sstream>
#include <type_traits>

#include "yaml-cpp/emittermanip.h"

namespace {

using PrecisionT = YAML::_Precision;

template <typename T, typename = void>
struct has_equal_op : std::false_type {};
template <typename T>
struct has_equal_op<T, std::void_t<decltype(std::declval<const T&>() == std::declval<const T&>())>>
    : std::true_type {};

template <typename T, typename = void>
struct has_ostream_op : std::false_type {};
template <typename T>
struct has_ostream_op<T, std::void_t<decltype(std::declval<std::ostream&>() << std::declval<const T&>())>>
    : std::true_type {};

static void ExpectSamePrecision(const PrecisionT& actual, const PrecisionT& expected) {
  if constexpr (has_equal_op<PrecisionT>::value) {
    EXPECT_TRUE(actual == expected);
  } else if constexpr (has_ostream_op<PrecisionT>::value) {
    std::ostringstream a, e;
    a << actual;
    e << expected;
    EXPECT_EQ(a.str(), e.str());
  } else {
    GTEST_SKIP() << "YAML::_Precision provides neither operator== nor operator<<; "
                    "cannot compare observable behavior via public interface.";
  }
}

class FloatPrecisionTest_20 : public ::testing::Test {};

}  // namespace

TEST_F(FloatPrecisionTest_20, ReturnsPrecisionObjectForTypicalValue_20) {
  const int n = 3;
  const PrecisionT actual = YAML::FloatPrecision(n);
  const PrecisionT expected(n, -1);
  ExpectSamePrecision(actual, expected);
}

TEST_F(FloatPrecisionTest_20, HandlesZeroPrecision_20) {
  const int n = 0;
  const PrecisionT actual = YAML::FloatPrecision(n);
  const PrecisionT expected(n, -1);
  ExpectSamePrecision(actual, expected);
}

TEST_F(FloatPrecisionTest_20, HandlesNegativePrecision_20) {
  const int n = -7;
  const PrecisionT actual = YAML::FloatPrecision(n);
  const PrecisionT expected(n, -1);
  ExpectSamePrecision(actual, expected);
}

TEST_F(FloatPrecisionTest_20, HandlesLargePrecisionValue_20) {
  const int n = INT_MAX;
  const PrecisionT actual = YAML::FloatPrecision(n);
  const PrecisionT expected(n, -1);
  ExpectSamePrecision(actual, expected);
}

TEST_F(FloatPrecisionTest_20, DifferentInputsProduceDifferentResultsWhenComparable_20) {
  const PrecisionT a = YAML::FloatPrecision(2);
  const PrecisionT b = YAML::FloatPrecision(5);

  if constexpr (has_equal_op<PrecisionT>::value) {
    EXPECT_FALSE(a == b);
  } else if constexpr (has_ostream_op<PrecisionT>::value) {
    std::ostringstream sa, sb;
    sa << a;
    sb << b;
    EXPECT_NE(sa.str(), sb.str());
  } else {
    GTEST_SKIP() << "YAML::_Precision provides neither operator== nor operator<<; "
                    "cannot compare observable behavior via public interface.";
  }
}

TEST_F(FloatPrecisionTest_20, ReturnTypeIsPrecision_20) {
  using RetT = decltype(YAML::FloatPrecision(1));
  static_assert(std::is_same<RetT, PrecisionT>::value,
                "YAML::FloatPrecision(int) must return YAML::_Precision");
  SUCCEED();
}
