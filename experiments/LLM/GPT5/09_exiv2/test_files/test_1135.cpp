// File: test_types_operator_ostream_1135.cpp
// TEST_ID: 1135

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <ostream>
#include <sstream>
#include <string>
#include <utility>

// Include Exiv2's public types (URational) and operator<< declaration.
// Adjust include if your tree uses a different header for URational.
#include "exiv2/types.hpp"

namespace {

// Helper to stringify any streamable object.
template <typename T>
std::string ToStringViaOstream(const T& v) {
  std::ostringstream oss;
  oss << v;
  return oss.str();
}

}  // namespace

class TypesOperatorOstreamTest_1135 : public ::testing::Test {};

TEST_F(TypesOperatorOstreamTest_1135, FormatsAsNumeratorSlashDenominator_1135) {
  Exiv2::URational r{1, 2};

  const std::string out = ToStringViaOstream(r);

  EXPECT_EQ(out, "1/2");
}

TEST_F(TypesOperatorOstreamTest_1135, HandlesZeroNumerator_1135) {
  Exiv2::URational r{0, 7};

  const std::string out = ToStringViaOstream(r);

  EXPECT_EQ(out, "0/7");
}

TEST_F(TypesOperatorOstreamTest_1135, HandlesZeroDenominator_1135) {
  // Even if denominator is 0, observable behavior for operator<< is formatting.
  Exiv2::URational r{5, 0};

  const std::string out = ToStringViaOstream(r);

  EXPECT_EQ(out, "5/0");
}

TEST_F(TypesOperatorOstreamTest_1135, HandlesNegativeNumerator_1135) {
  Exiv2::URational r{-3, 10};

  const std::string out = ToStringViaOstream(r);

  EXPECT_EQ(out, "-3/10");
}

TEST_F(TypesOperatorOstreamTest_1135, HandlesNegativeDenominator_1135) {
  Exiv2::URational r{3, -10};

  const std::string out = ToStringViaOstream(r);

  EXPECT_EQ(out, "3/-10");
}

TEST_F(TypesOperatorOstreamTest_1135, HandlesBothNegative_1135) {
  Exiv2::URational r{-3, -10};

  const std::string out = ToStringViaOstream(r);

  EXPECT_EQ(out, "-3/-10");
}

TEST_F(TypesOperatorOstreamTest_1135, HandlesIntMinMaxBoundaryValues_1135) {
  using Limits = std::numeric_limits<decltype(Exiv2::URational{}.first)>;
  const auto minv = Limits::min();
  const auto maxv = Limits::max();

  Exiv2::URational r{minv, maxv};

  const std::string out = ToStringViaOstream(r);

  std::ostringstream expected;
  expected << minv << "/" << maxv;
  EXPECT_EQ(out, expected.str());
}

TEST_F(TypesOperatorOstreamTest_1135, AppendsToExistingStreamContent_1135) {
  Exiv2::URational r{12, 34};

  std::ostringstream oss;
  oss << "prefix:" << r << ":suffix";

  EXPECT_EQ(oss.str(), "prefix:12/34:suffix");
}

TEST_F(TypesOperatorOstreamTest_1135, CanBeStreamedMultipleTimes_1135) {
  Exiv2::URational a{1, 3};
  Exiv2::URational b{2, 5};

  std::ostringstream oss;
  oss << a << "," << b << "," << a;

  EXPECT_EQ(oss.str(), "1/3,2/5,1/3");
}