// File: prefilter_info_literal_test_552.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "re2/prefilter.h"  // Assuming this declares re2::Prefilter::Info

using ::testing::Contains;
using ::testing::Not;

namespace re2 {

class PrefilterInfoLiteralTest_552 : public ::testing::Test {
 protected:
  // Helper to safely delete and null a pointer.
  static void SafeDelete(Prefilter::Info*& p) {
    delete p;
    p = nullptr;
  }
};

// Normal operation: ensures a lowercase alphabetic rune is captured exactly once
// and is_exact() is true.
TEST_F(PrefilterInfoLiteralTest_552, LowercaseAlpha_ExactSetAndFlag_552) {
  Prefilter::Info* info = Prefilter::Info::Literal(static_cast<Rune>('a'));
  ASSERT_NE(info, nullptr);

  EXPECT_TRUE(info->is_exact());
  // exact() should contain the single-character string "a"
  EXPECT_EQ(info->exact().size(), 1u);
  EXPECT_THAT(info->exact(), Contains(std::string("a")));

  SafeDelete(info);
}

// Normal operation: uppercase input should appear in exact() as its lowercase
// form (observable via exact()) and still be a single-entry exact set.
TEST_F(PrefilterInfoLiteralTest_552, UppercaseAlpha_LoweredIntoExactSet_552) {
  Prefilter::Info* info = Prefilter::Info::Literal(static_cast<Rune>('A'));
  ASSERT_NE(info, nullptr);

  EXPECT_TRUE(info->is_exact());
  EXPECT_EQ(info->exact().size(), 1u);
  // Expect lowercase "a" present
  EXPECT_THAT(info->exact(), Contains(std::string("a")));
  // And not the uppercase "A"
  EXPECT_THAT(info->exact(), Not(Contains(std::string("A"))));

  SafeDelete(info);
}

// Boundary-ish / non-alphabetic: digits or punctuation should round-trip
// unchanged in the observable exact() set, with is_exact() true.
TEST_F(PrefilterInfoLiteralTest_552, NonAlphabetic_NoCaseChange_552) {
  Prefilter::Info* info_digit = Prefilter::Info::Literal(static_cast<Rune>('1'));
  ASSERT_NE(info_digit, nullptr);
  EXPECT_TRUE(info_digit->is_exact());
  EXPECT_EQ(info_digit->exact().size(), 1u);
  EXPECT_THAT(info_digit->exact(), Contains(std::string("1")));
  SafeDelete(info_digit);

  Prefilter::Info* info_punct = Prefilter::Info::Literal(static_cast<Rune>('.'));
  ASSERT_NE(info_punct, nullptr);
  EXPECT_TRUE(info_punct->is_exact());
  EXPECT_EQ(info_punct->exact().size(), 1u);
  EXPECT_THAT(info_punct->exact(), Contains(std::string(".")));
  SafeDelete(info_punct);
}

// Object identity / independence: repeated calls return distinct objects whose
// observable state (via exact() and is_exact()) is independent.
TEST_F(PrefilterInfoLiteralTest_552, MultipleCalls_YieldIndependentInstances_552) {
  Prefilter::Info* a = Prefilter::Info::Literal(static_cast<Rune>('X'));
  Prefilter::Info* b = Prefilter::Info::Literal(static_cast<Rune>('y'));

  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);
  EXPECT_NE(a, b);  // Distinct instances

  // Each is exact with a single element reflecting the observable literal.
  EXPECT_TRUE(a->is_exact());
  EXPECT_EQ(a->exact().size(), 1u);
  EXPECT_THAT(a->exact(), Contains(std::string("x")));  // lowercase of 'X'

  EXPECT_TRUE(b->is_exact());
  EXPECT_EQ(b->exact().size(), 1u);
  EXPECT_THAT(b->exact(), Contains(std::string("y")));

  SafeDelete(a);
  SafeDelete(b);
}

// Sanity on memory management / destructor: constructing and destroying the
// object created by Literal() should not crash or leak (observable here as
// successful creation/destruction; real leak checks handled by sanitizers).
TEST_F(PrefilterInfoLiteralTest_552, Destructor_SafeAfterLiteral_552) {
  Prefilter::Info* info = Prefilter::Info::Literal(static_cast<Rune>('Z'));
  ASSERT_NE(info, nullptr);
  // Touch observable interface before delete
  EXPECT_TRUE(info->is_exact());
  EXPECT_EQ(info->exact().size(), 1u);

  // Should be safe to destroy.
  delete info;
}

}  // namespace re2
