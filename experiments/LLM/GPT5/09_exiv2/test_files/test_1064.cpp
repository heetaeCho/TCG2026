// ============================================================================
// Test file for ./TestProjects/exiv2/src/image.cpp (partial)
// Target: Exiv2::typeValid(uint16_t)  [static internal linkage in this TU]
// TEST_ID: 1064
// ============================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>

// Include the implementation under test directly so we can access the TU-local
// `static` function (internal linkage) without re-implementing anything.
//
// NOTE: This is a common unit-testing pattern for testing TU-local (static)
// helpers while still treating them as a black box.
#include "image.cpp"

namespace {

class typeValidTest_1064 : public ::testing::Test {};

TEST_F(typeValidTest_1064, ReturnsTrueForLowerBound_1064) {
  EXPECT_TRUE(Exiv2::typeValid(static_cast<uint16_t>(1)));
}

TEST_F(typeValidTest_1064, ReturnsTrueForUpperBound_1064) {
  EXPECT_TRUE(Exiv2::typeValid(static_cast<uint16_t>(13)));
}

TEST_F(typeValidTest_1064, ReturnsTrueForTypicalInRangeValues_1064) {
  EXPECT_TRUE(Exiv2::typeValid(static_cast<uint16_t>(2)));
  EXPECT_TRUE(Exiv2::typeValid(static_cast<uint16_t>(7)));
  EXPECT_TRUE(Exiv2::typeValid(static_cast<uint16_t>(12)));
}

TEST_F(typeValidTest_1064, ReturnsFalseForJustBelowLowerBound_1064) {
  EXPECT_FALSE(Exiv2::typeValid(static_cast<uint16_t>(0)));
}

TEST_F(typeValidTest_1064, ReturnsFalseForJustAboveUpperBound_1064) {
  EXPECT_FALSE(Exiv2::typeValid(static_cast<uint16_t>(14)));
}

TEST_F(typeValidTest_1064, ReturnsFalseForFarOutOfRangeValues_1064) {
  EXPECT_FALSE(Exiv2::typeValid(static_cast<uint16_t>(100)));
  EXPECT_FALSE(Exiv2::typeValid(std::numeric_limits<uint16_t>::max()));
}

TEST_F(typeValidTest_1064, WorksWithVariousCastsAndBoundaryRelatedInputs_1064) {
  // Verify behavior remains consistent for values that may arise via casts.
  // (No UB here: casting to uint16_t is well-defined modulo 2^16.)
  EXPECT_FALSE(Exiv2::typeValid(static_cast<uint16_t>(-1))); // becomes 65535
  EXPECT_FALSE(Exiv2::typeValid(static_cast<uint16_t>(-2))); // becomes 65534
  EXPECT_TRUE(Exiv2::typeValid(static_cast<uint16_t>(13)));
  EXPECT_FALSE(Exiv2::typeValid(static_cast<uint16_t>(15)));
}

}  // namespace