// =================================================================================================
// TEST_ID: 1191
// File: test_iloc_toString_1191.cpp
//
// Unit tests for Exiv2::Iloc::toString() const
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <string>

#include "exiv2/bmffimage.hpp"

namespace {

class IlocTest_1191 : public ::testing::Test {};

TEST_F(IlocTest_1191, DefaultConstructedFormatsAllZeros_1191) {
  const Exiv2::Iloc iloc;
  const std::string s = iloc.toString();

  // Verify presence of expected labeled fields (observable behavior).
  EXPECT_NE(s.find("ID"), std::string::npos);
  EXPECT_NE(s.find("from"), std::string::npos);
  EXPECT_NE(s.find("length"), std::string::npos);

  // Verify default values appear somewhere in the output.
  EXPECT_NE(s.find("0"), std::string::npos);
}

TEST_F(IlocTest_1191, FormatsProvidedValuesAndPreservesAllNumbers_1191) {
  const Exiv2::Iloc iloc(/*ID=*/1u, /*start=*/2u, /*length=*/3u);
  const std::string s = iloc.toString();

  EXPECT_NE(s.find("1"), std::string::npos);
  EXPECT_NE(s.find("2"), std::string::npos);
  EXPECT_NE(s.find("3"), std::string::npos);

  // Should still contain the labels.
  EXPECT_NE(s.find("ID"), std::string::npos);
  EXPECT_NE(s.find("from"), std::string::npos);
  EXPECT_NE(s.find("length"), std::string::npos);
}

TEST_F(IlocTest_1191, DifferentInstancesProduceDifferentStringsWhenFieldsDiffer_1191) {
  const Exiv2::Iloc a(/*ID=*/10u, /*start=*/20u, /*length=*/30u);
  const Exiv2::Iloc b(/*ID=*/10u, /*start=*/21u, /*length=*/30u);

  const std::string sa = a.toString();
  const std::string sb = b.toString();

  EXPECT_NE(sa, sb);
}

TEST_F(IlocTest_1191, BoundaryValuesAreRenderable_1191) {
  const Exiv2::Iloc iloc(/*ID=*/0u, /*start=*/0u, /*length=*/0u);
  const std::string s0 = iloc.toString();
  EXPECT_FALSE(s0.empty());

  const Exiv2::Iloc ilocMax(/*ID=*/UINT32_MAX, /*start=*/UINT32_MAX, /*length=*/UINT32_MAX);
  const std::string sMax = ilocMax.toString();

  EXPECT_FALSE(sMax.empty());
  // Expect the max value in decimal representation to appear somewhere.
  // (Do not assume exact formatting beyond observable inclusion.)
  const std::string maxDec = "4294967295";
  EXPECT_NE(sMax.find(maxDec), std::string::npos);
}

TEST_F(IlocTest_1191, ToStringIsStableAcrossRepeatedCalls_1191) {
  const Exiv2::Iloc iloc(/*ID=*/7u, /*start=*/8u, /*length=*/9u);

  const std::string s1 = iloc.toString();
  const std::string s2 = iloc.toString();

  EXPECT_EQ(s1, s2);
  EXPECT_FALSE(s1.empty());
}

}  // namespace