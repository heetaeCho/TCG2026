// File: prefilter_info_alt_test_546.cc
#include <gtest/gtest.h>
#include <set>
#include <string>
#include "re2/prefilter.h"   // Assumes this exposes re2::Prefilter::Info and needed types

namespace re2 {

class PrefilterInfoAltTest_546 : public ::testing::Test {};

// [Normal] Both inputs are exact: result stays exact and contains the union.
TEST_F(PrefilterInfoAltTest_546, ExactVsExactProducesExactUnion_546) {
  // Arrange: create two exact infos with distinct elements.
  Prefilter::Info* a = Prefilter::Info::EmptyString();  // expected exact
  ASSERT_NE(a, nullptr);
  a->exact().insert("a");

  Prefilter::Info* b = Prefilter::Info::EmptyString();  // expected exact
  ASSERT_NE(b, nullptr);
  b->exact().insert("b");

  // Act
  Prefilter::Info* ab = Prefilter::Info::Alt(a, b);

  // Assert
  ASSERT_NE(ab, nullptr);
  EXPECT_TRUE(ab->is_exact()) << "Alt of two exact infos must remain exact.";

  const auto& s = ab->exact();
  // Should contain "", "a", "b"
  EXPECT_EQ(s.count(std::string()), 1u);
  EXPECT_EQ(s.count("a"), 1u);
  EXPECT_EQ(s.count("b"), 1u);
  EXPECT_EQ(s.size(), 3u);
  delete ab;
}

// [Boundary] Duplicates should not multiply in a set-like union.
TEST_F(PrefilterInfoAltTest_546, UnionDeduplicatesOverlappingElements_546) {
  // Arrange
  Prefilter::Info* a = Prefilter::Info::EmptyString();
  ASSERT_NE(a, nullptr);
  a->exact().insert("x");

  Prefilter::Info* b = Prefilter::Info::EmptyString();
  ASSERT_NE(b, nullptr);
  b->exact().insert("x");  // duplicate across inputs

  // Act
  Prefilter::Info* ab = Prefilter::Info::Alt(a, b);

  // Assert
  ASSERT_NE(ab, nullptr);
  EXPECT_TRUE(ab->is_exact());

  const auto& s = ab->exact();
  // Expected unique elements: "" and "x"
  EXPECT_EQ(s.count(std::string()), 1u);
  EXPECT_EQ(s.count("x"), 1u);
  EXPECT_EQ(s.size(), 2u);
  delete ab;
}

// [Boundary] Different set sizes (exercises internal swap path indirectly).
TEST_F(PrefilterInfoAltTest_546, LargerRightSetStillUnionsCorrectly_546) {
  // Arrange: make 'a' smaller, 'b' larger.
  Prefilter::Info* a = Prefilter::Info::EmptyString();
  ASSERT_NE(a, nullptr);               // size likely 1: {""}

  Prefilter::Info* b = Prefilter::Info::EmptyString();
  ASSERT_NE(b, nullptr);
  b->exact().insert("p");
  b->exact().insert("q");              // larger set

  // Act
  Prefilter::Info* ab = Prefilter::Info::Alt(a, b);

  // Assert
  ASSERT_NE(ab, nullptr);
  EXPECT_TRUE(ab->is_exact());

  const auto& s = ab->exact();
  EXPECT_EQ(s.count(std::string()), 1u);
  EXPECT_EQ(s.count("p"), 1u);
  EXPECT_EQ(s.count("q"), 1u);
  EXPECT_EQ(s.size(), 3u);
  delete ab;
}

// [Exceptional/Observable] If either input is non-exact, the result is non-exact.
TEST_F(PrefilterInfoAltTest_546, NonExactWithExactProducesNonExact_546) {
  // Arrange: default-constructed Info is not exact per the public default ctor.
  Prefilter::Info* a = new Prefilter::Info();               // non-exact
  Prefilter::Info* b = Prefilter::Info::EmptyString();      // exact
  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);

  // Act
  Prefilter::Info* ab = Prefilter::Info::Alt(a, b);

  // Assert
  ASSERT_NE(ab, nullptr);
  EXPECT_FALSE(ab->is_exact()) << "Alt with any non-exact input should be non-exact.";
  // We do not assume anything about the returned match object beyond this flag.
  delete ab;
}

// [Exceptional/Observable] Both inputs non-exact should yield non-exact without crashing.
TEST_F(PrefilterInfoAltTest_546, NonExactWithNonExactProducesNonExact_546) {
  // Arrange
  Prefilter::Info* a = new Prefilter::Info();
  Prefilter::Info* b = new Prefilter::Info();
  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);

  // Act
  Prefilter::Info* ab = Prefilter::Info::Alt(a, b);

  // Assert
  ASSERT_NE(ab, nullptr);
  EXPECT_FALSE(ab->is_exact());
  delete ab;
}

}  // namespace re2
