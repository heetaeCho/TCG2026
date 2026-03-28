// =================================================================================================
// UNIT TESTS for Exiv2::isHex (./TestProjects/exiv2/src/types.cpp)
// TEST_ID: 1154
// =================================================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <string>

#include "exiv2/types.hpp"  // assumes Exiv2::isHex is declared here

namespace {

class IsHexTest_1154 : public ::testing::Test {};

TEST_F(IsHexTest_1154, ReturnsFalseWhenPrefixDoesNotMatch_1154) {
  EXPECT_FALSE(Exiv2::isHex("0x1A", 0, "0X"));      // wrong-case prefix
  EXPECT_FALSE(Exiv2::isHex("1A", 0, "0x"));        // missing prefix
  EXPECT_FALSE(Exiv2::isHex("xyz1A", 0, "0x"));     // unrelated prefix
  EXPECT_FALSE(Exiv2::isHex("", 0, "0x"));          // empty string can't start with non-empty prefix
  EXPECT_FALSE(Exiv2::isHex("0", 0, "0x"));         // too short
}

TEST_F(IsHexTest_1154, SizeZeroDoesNotEnforceLength_1154) {
  EXPECT_TRUE(Exiv2::isHex("0x0", 0, "0x"));
  EXPECT_TRUE(Exiv2::isHex("0x1a", 0, "0x"));
  EXPECT_TRUE(Exiv2::isHex("0xDEADBEEF", 0, "0x"));

  // With size==0, only prefix + all hex digits should matter; empty suffix is vacuously hex.
  EXPECT_TRUE(Exiv2::isHex("0x", 0, "0x"));
}

TEST_F(IsHexTest_1154, EnforcesExactLengthWhenSizeIsNonZero_1154) {
  // size counts only the hex-digit payload (excluding prefix)
  EXPECT_TRUE(Exiv2::isHex("0x1A", 2, "0x"));
  EXPECT_TRUE(Exiv2::isHex("0x00", 2, "0x"));
  EXPECT_TRUE(Exiv2::isHex("0xDEADBEEF", 8, "0x"));

  // Too short / too long
  EXPECT_FALSE(Exiv2::isHex("0x1", 2, "0x"));
  EXPECT_FALSE(Exiv2::isHex("0x1A3", 2, "0x"));
  EXPECT_FALSE(Exiv2::isHex("0xDEADBEE", 8, "0x"));
  EXPECT_FALSE(Exiv2::isHex("0xDEADBEEFF", 8, "0x"));
}

TEST_F(IsHexTest_1154, ReturnsFalseWhenAnyNonHexDigitIsPresent_1154) {
  EXPECT_FALSE(Exiv2::isHex("0x1G", 0, "0x"));      // G is not hex
  EXPECT_FALSE(Exiv2::isHex("0x-1", 0, "0x"));      // '-' is not hex
  EXPECT_FALSE(Exiv2::isHex("0x12 34", 0, "0x"));   // space is not hex
  EXPECT_FALSE(Exiv2::isHex("0x12_34", 0, "0x"));   // underscore not hex
  EXPECT_FALSE(Exiv2::isHex("0x\n", 0, "0x"));      // newline not hex
}

TEST_F(IsHexTest_1154, AcceptsUpperAndLowerCaseHexDigits_1154) {
  EXPECT_TRUE(Exiv2::isHex("0xabcdef", 0, "0x"));
  EXPECT_TRUE(Exiv2::isHex("0xABCDEF", 0, "0x"));
  EXPECT_TRUE(Exiv2::isHex("0xAaBbCc", 0, "0x"));
}

TEST_F(IsHexTest_1154, WorksWithCustomPrefix_1154) {
  EXPECT_TRUE(Exiv2::isHex("#FF", 2, "#"));
  EXPECT_TRUE(Exiv2::isHex("HEXDEAD", 4, "HEX"));

  EXPECT_FALSE(Exiv2::isHex("HEXDEAD", 3, "HEX"));     // length mismatch
  EXPECT_FALSE(Exiv2::isHex("HEXDEA-", 4, "HEX"));     // non-hex in payload
  EXPECT_FALSE(Exiv2::isHex("hexDEAD", 4, "HEX"));     // prefix mismatch (case-sensitive)
}

TEST_F(IsHexTest_1154, HandlesEmptyPrefixAsBoundaryCase_1154) {
  // Empty prefix means "whole string must be hex digits" (and optional size enforcement).
  EXPECT_TRUE(Exiv2::isHex("DEADBEEF", 0, ""));
  EXPECT_TRUE(Exiv2::isHex("", 0, ""));                // empty string is all_of over empty range => true

  EXPECT_TRUE(Exiv2::isHex("1A", 2, ""));
  EXPECT_FALSE(Exiv2::isHex("1A", 1, ""));
  EXPECT_FALSE(Exiv2::isHex("1G", 0, ""));
}

TEST_F(IsHexTest_1154, BoundaryWithSizeAndPrefixOnly_1154) {
  // When size>0, prefix-only string should fail because total length must be prefix.size()+size.
  EXPECT_FALSE(Exiv2::isHex("0x", 1, "0x"));
  EXPECT_FALSE(Exiv2::isHex("0x", 2, "0x"));

  // When size==0, prefix-only string should succeed (no digits to validate).
  EXPECT_TRUE(Exiv2::isHex("0x", 0, "0x"));
}

}  // namespace