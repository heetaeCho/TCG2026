// File: re2_regexp_accessor_test.cc

#include <gtest/gtest.h>
#include <string>
#include "re2/re2.h"

using re2::RE2;

class RE2_RegexpAccessorTest_6 : public ::testing::Test {};

// Normal operation: valid pattern should produce a stable, non-null Regexp() pointer.
TEST_F(RE2_RegexpAccessorTest_6, ValidPattern_ReturnsStableNonNullPointer_6) {
  RE2 re("abc");
  ASSERT_TRUE(re.ok()) << "Expected RE2 to report ok() for a valid pattern.";
  auto* p1 = re.Regexp();
  auto* p2 = re.Regexp();

  EXPECT_NE(nullptr, p1) << "Regexp() should return a non-null pointer for a valid pattern.";
  EXPECT_EQ(p1, p2) << "Repeated calls to Regexp() should return the same pointer.";
}

// Boundary condition: empty pattern should be acceptable and return a stable pointer.
TEST_F(RE2_RegexpAccessorTest_6, EmptyPattern_RegexpNonNullAndStable_6) {
  RE2 re("");
  ASSERT_TRUE(re.ok()) << "Empty pattern should be valid in RE2.";
  auto* p1 = re.Regexp();
  auto* p2 = re.Regexp();

  EXPECT_NE(nullptr, p1) << "Regexp() should return non-null for an empty (valid) pattern.";
  EXPECT_EQ(p1, p2) << "Regexp() should be stable across calls.";
}

// Exceptional/error case: syntactically invalid pattern should surface via ok()==false.
// For such a case, Regexp() should reasonably be nullptr (observable behavior).
TEST_F(RE2_RegexpAccessorTest_6, InvalidPattern_ErrorAndNullRegexp_6) {
  RE2 re("(");  // Unbalanced parenthesis is typically invalid.
  EXPECT_FALSE(re.ok()) << "Invalid pattern should cause ok() to be false.";
  EXPECT_EQ(nullptr, re.Regexp()) << "For invalid patterns, Regexp() is expected to be nullptr.";
}

// Independence across instances: each valid instance should keep its own stable pointer.
// We don't assert cross-instance equality/inequality (implementation detail).
TEST_F(RE2_RegexpAccessorTest_6, MultipleInstances_HaveStableOwnPointers_6) {
  RE2 re1("foo");
  RE2 re2("bar");
  ASSERT_TRUE(re1.ok());
  ASSERT_TRUE(re2.ok());

  auto* r1a = re1.Regexp();
  auto* r1b = re1.Regexp();
  auto* r2a = re2.Regexp();
  auto* r2b = re2.Regexp();

  EXPECT_NE(nullptr, r1a);
  EXPECT_NE(nullptr, r2a);
  EXPECT_EQ(r1a, r1b) << "re1's Regexp() should be stable within the same instance.";
  EXPECT_EQ(r2a, r2b) << "re2's Regexp() should be stable within the same instance.";
  // No assertion about r1* vs r2* to avoid relying on internal sharing/uniqueness.
}
