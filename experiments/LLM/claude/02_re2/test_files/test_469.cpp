#include "gtest/gtest.h"
#include "re2/prefilter_tree.h"
#include "re2/prefilter.h"

namespace re2 {

// Test fixture for PrefilterTree::PrefilterEqual tests
class PrefilterEqualTest_469 : public ::testing::Test {
 protected:
  PrefilterTree::PrefilterEqual equal_;
};

// Test that two NONE prefilters are equal
TEST_F(PrefilterEqualTest_469, TwoNonePrefiltersAreEqual_469) {
  Prefilter a(Prefilter::NONE);
  Prefilter b(Prefilter::NONE);
  EXPECT_TRUE(equal_(&a, &b));
}

// Test that two ALL prefilters are equal
TEST_F(PrefilterEqualTest_469, TwoAllPrefiltersAreEqual_469) {
  Prefilter a(Prefilter::ALL);
  Prefilter b(Prefilter::ALL);
  EXPECT_TRUE(equal_(&a, &b));
}

// Test that a NONE and an ALL prefilter are not equal
TEST_F(PrefilterEqualTest_469, NoneAndAllPrefiltersAreNotEqual_469) {
  Prefilter a(Prefilter::NONE);
  Prefilter b(Prefilter::ALL);
  EXPECT_FALSE(equal_(&a, &b));
}

// Test that an ALL and a NONE prefilter are not equal (reverse order)
TEST_F(PrefilterEqualTest_469, AllAndNonePrefiltersAreNotEqual_469) {
  Prefilter a(Prefilter::ALL);
  Prefilter b(Prefilter::NONE);
  EXPECT_FALSE(equal_(&a, &b));
}

// Test that same pointer returns true (reflexive)
TEST_F(PrefilterEqualTest_469, SamePointerIsEqual_469) {
  Prefilter a(Prefilter::NONE);
  EXPECT_TRUE(equal_(&a, &a));
}

// Test that two ATOM prefilters with same atom are equal
TEST_F(PrefilterEqualTest_469, TwoAtomPrefiltersWithSameAtomAreEqual_469) {
  Prefilter a(Prefilter::ATOM);
  Prefilter b(Prefilter::ATOM);
  // ATOM prefilters with default (empty) atoms should be equal
  EXPECT_TRUE(equal_(&a, &b));
}

// Test that ATOM and AND prefilters are not equal
TEST_F(PrefilterEqualTest_469, AtomAndAndPrefiltersAreNotEqual_469) {
  Prefilter a(Prefilter::ATOM);
  Prefilter b(Prefilter::AND);
  EXPECT_FALSE(equal_(&a, &b));
}

// Test that ATOM and OR prefilters are not equal
TEST_F(PrefilterEqualTest_469, AtomAndOrPrefiltersAreNotEqual_469) {
  Prefilter a(Prefilter::ATOM);
  Prefilter b(Prefilter::OR);
  EXPECT_FALSE(equal_(&a, &b));
}

// Test that two AND prefilters (with no subs) are equal
TEST_F(PrefilterEqualTest_469, TwoAndPrefiltersNoSubsAreEqual_469) {
  Prefilter a(Prefilter::AND);
  Prefilter b(Prefilter::AND);
  EXPECT_TRUE(equal_(&a, &b));
}

// Test that two OR prefilters (with no subs) are equal
TEST_F(PrefilterEqualTest_469, TwoOrPrefiltersNoSubsAreEqual_469) {
  Prefilter a(Prefilter::OR);
  Prefilter b(Prefilter::OR);
  EXPECT_TRUE(equal_(&a, &b));
}

// Test that AND and OR prefilters are not equal
TEST_F(PrefilterEqualTest_469, AndAndOrPrefiltersAreNotEqual_469) {
  Prefilter a(Prefilter::AND);
  Prefilter b(Prefilter::OR);
  EXPECT_FALSE(equal_(&a, &b));
}

}  // namespace re2
