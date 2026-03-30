// =================================================================================================
// TEST_ID: 1133
// File: test_types_operator_output_1133.cpp
//
// Unit tests for:
//   Exiv2::operator<<(std::ostream&, const Exiv2::Rational&)
//
// Constraints respected:
// - Black-box: only observable behavior via public interface (stream output)
// - No private state access
// - Boundary + error-ish cases observable via streaming
// =================================================================================================

#include <gtest/gtest.h>

#include <limits>
#include <sstream>
#include <string>

// Include the library header that defines Exiv2::Rational and declares the operator<<.
// Depending on your Exiv2 layout, adjust this include if needed.
#include "exiv2/types.hpp"

namespace {

class RationalOstreamTest_1133 : public ::testing::Test {};

TEST_F(RationalOstreamTest_1133, FormatsAsFirstSlashSecond_1133) {
  const Exiv2::Rational r{1, 2};
  std::ostringstream oss;
  oss << r;
  EXPECT_EQ(oss.str(), "1/2");
}

TEST_F(RationalOstreamTest_1133, FormatsZeroNumerator_1133) {
  const Exiv2::Rational r{0, 5};
  std::ostringstream oss;
  oss << r;
  EXPECT_EQ(oss.str(), "0/5");
}

TEST_F(RationalOstreamTest_1133, FormatsNegativeNumerator_1133) {
  const Exiv2::Rational r{-3, 7};
  std::ostringstream oss;
  oss << r;
  EXPECT_EQ(oss.str(), "-3/7");
}

TEST_F(RationalOstreamTest_1133, FormatsNegativeDenominator_1133) {
  const Exiv2::Rational r{3, -7};
  std::ostringstream oss;
  oss << r;
  EXPECT_EQ(oss.str(), "3/-7");
}

TEST_F(RationalOstreamTest_1133, FormatsBothNegative_1133) {
  const Exiv2::Rational r{-3, -7};
  std::ostringstream oss;
  oss << r;
  EXPECT_EQ(oss.str(), "-3/-7");
}

TEST_F(RationalOstreamTest_1133, FormatsDenominatorZero_1133) {
  // Even if denominator 0 is mathematically odd, streaming should still be observable and stable.
  const Exiv2::Rational r{42, 0};
  std::ostringstream oss;
  oss << r;
  EXPECT_EQ(oss.str(), "42/0");
}

TEST_F(RationalOstreamTest_1133, HandlesIntLimits_1133) {
  // Exiv2::Rational is typically a pair of int32-ish; use numeric_limits of its element type.
  using FirstT = decltype(std::declval<Exiv2::Rational>().first);
  using SecondT = decltype(std::declval<Exiv2::Rational>().second);

  const Exiv2::Rational r{std::numeric_limits<FirstT>::min(), std::numeric_limits<SecondT>::max()};

  std::ostringstream oss;
  oss << r;

  std::ostringstream expected;
  expected << std::numeric_limits<FirstT>::min() << "/" << std::numeric_limits<SecondT>::max();

  EXPECT_EQ(oss.str(), expected.str());
}

TEST_F(RationalOstreamTest_1133, AppendsToExistingStreamContent_1133) {
  const Exiv2::Rational r{5, 9};
  std::ostringstream oss;
  oss << "prefix:" << r << ":suffix";
  EXPECT_EQ(oss.str(), "prefix:5/9:suffix");
}

TEST_F(RationalOstreamTest_1133, WorksWithChainedInsertions_1133) {
  const Exiv2::Rational r1{1, 3};
  const Exiv2::Rational r2{2, 5};

  std::ostringstream oss;
  oss << r1 << "," << r2;

  EXPECT_EQ(oss.str(), "1/3,2/5");
}

TEST_F(RationalOstreamTest_1133, ReturnsStreamSoFlagsCanBeObserved_1133) {
  // Observable external interaction: operator<< returns std::ostream& enabling chaining.
  const Exiv2::Rational r{10, 20};

  std::ostringstream oss;
  std::ostream& ret = (oss << r);
  EXPECT_EQ(&ret, &oss);

  // Also verify stream state remains good (observable).
  EXPECT_TRUE(oss.good());
  EXPECT_EQ(oss.str(), "10/20");
}

}  // namespace