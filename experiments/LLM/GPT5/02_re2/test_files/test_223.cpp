// File: mimics_pcre_can_be_empty_string_test_223.cc

#include <gtest/gtest.h>
#include "re2/regexp.h"

// IMPORTANT: CanBeEmptyString is a file-static in mimics_pcre.cc.
// To test its observable behavior directly, include the .cc here so the
// symbol is available in this translation unit without altering its logic.
#include "re2/mimics_pcre.cc"

namespace re2 {

// Helper alias for readability.
using PF = Regexp::ParseFlags;

// Convenience: default flags as zero (do not assume any specific bits).
static constexpr PF kNoFlags = static_cast<PF>(0);

// Utility that ensures top-level Decref even if assertions fail.
class RegexpHolder {
 public:
  explicit RegexpHolder(Regexp* r) : r_(r) {}
  ~RegexpHolder() { if (r_) r_->Decref(); }
  Regexp* get() const { return r_; }
  Regexp* release() { Regexp* t = r_; r_ = nullptr; return t; }
 private:
  Regexp* r_;
};

// =============== Tests ===============

TEST(CanBeEmptyStringTest_223, StarOfLiteral_AllowsEmpty_223) {
  RegexpHolder lit(Regexp::NewLiteral('a', kNoFlags));
  ASSERT_NE(lit.get(), nullptr);

  RegexpHolder star(Regexp::Star(lit.get(), kNoFlags));
  // After Star consumes ownership of sub, null out lit to avoid double Decref.
  (void)lit.release();
  ASSERT_NE(star.get(), nullptr);

  EXPECT_TRUE(CanBeEmptyString(star.get()));
}

TEST(CanBeEmptyStringTest_223, PlusOfLiteral_DisallowsEmpty_223) {
  RegexpHolder lit(Regexp::NewLiteral('a', kNoFlags));
  ASSERT_NE(lit.get(), nullptr);

  RegexpHolder plus(Regexp::Plus(lit.get(), kNoFlags));
  (void)lit.release();
  ASSERT_NE(plus.get(), nullptr);

  EXPECT_FALSE(CanBeEmptyString(plus.get()));
}

TEST(CanBeEmptyStringTest_223, QuestionOfLiteral_AllowsEmpty_223) {
  RegexpHolder lit(Regexp::NewLiteral('a', kNoFlags));
  ASSERT_NE(lit.get(), nullptr);

  RegexpHolder q(Regexp::Quest(lit.get(), kNoFlags));
  (void)lit.release();
  ASSERT_NE(q.get(), nullptr);

  EXPECT_TRUE(CanBeEmptyString(q.get()));
}

TEST(CanBeEmptyStringTest_223, Concat_AllPartsMustAllowEmpty_223) {
  // a* concatenated with b?  -> overall can be empty (true && true)
  Regexp* subs1[2];
  subs1[0] = Regexp::Star(Regexp::NewLiteral('a', kNoFlags), kNoFlags);
  subs1[1] = Regexp::Quest(Regexp::NewLiteral('b', kNoFlags), kNoFlags);
  ASSERT_NE(subs1[0], nullptr);
  ASSERT_NE(subs1[1], nullptr);

  RegexpHolder concat1(Regexp::Concat(subs1, 2, kNoFlags));
  ASSERT_NE(concat1.get(), nullptr);
  EXPECT_TRUE(CanBeEmptyString(concat1.get()));

  // a+ concatenated with b*  -> cannot be empty (false && true)
  Regexp* subs2[2];
  subs2[0] = Regexp::Plus(Regexp::NewLiteral('a', kNoFlags), kNoFlags);
  subs2[1] = Regexp::Star(Regexp::NewLiteral('b', kNoFlags), kNoFlags);
  ASSERT_NE(subs2[0], nullptr);
  ASSERT_NE(subs2[1], nullptr);

  RegexpHolder concat2(Regexp::Concat(subs2, 2, kNoFlags));
  ASSERT_NE(concat2.get(), nullptr);
  EXPECT_FALSE(CanBeEmptyString(concat2.get()));
}

TEST(CanBeEmptyStringTest_223, Alternate_AnyBranchAllowingEmpty_Suffices_223) {
  // (a+ | b*) -> can be empty because b* allows empty
  Regexp* subs[2];
  subs[0] = Regexp::Plus(Regexp::NewLiteral('a', kNoFlags), kNoFlags);
  subs[1] = Regexp::Star(Regexp::NewLiteral('b', kNoFlags), kNoFlags);
  ASSERT_NE(subs[0], nullptr);
  ASSERT_NE(subs[1], nullptr);

  RegexpHolder alt(Regexp::Alternate(subs, 2, kNoFlags));
  ASSERT_NE(alt.get(), nullptr);

  EXPECT_TRUE(CanBeEmptyString(alt.get()));
}

TEST(CanBeEmptyStringTest_223, Repeat_MinZero_AllowsEmpty_MinPositive_Disallows_223) {
  // a{0,3} -> allows empty
  {
    RegexpHolder rpt(Regexp::Repeat(Regexp::NewLiteral('a', kNoFlags), kNoFlags, /*min=*/0, /*max=*/3));
    ASSERT_NE(rpt.get(), nullptr);
    EXPECT_TRUE(CanBeEmptyString(rpt.get()));
  }
  // a{2,5} -> cannot be empty
  {
    RegexpHolder rpt(Regexp::Repeat(Regexp::NewLiteral('a', kNoFlags), kNoFlags, /*min=*/2, /*max=*/5));
    ASSERT_NE(rpt.get(), nullptr);
    EXPECT_FALSE(CanBeEmptyString(rpt.get()));
  }
}

TEST(CanBeEmptyStringTest_223, Capture_WrapperDoesNotChangeEmptiness_223) {
  // (a*) with a capturing group -> still allows empty
  RegexpHolder inner(Regexp::Star(Regexp::NewLiteral('a', kNoFlags), kNoFlags));
  ASSERT_NE(inner.get(), nullptr);

  RegexpHolder cap(Regexp::Capture(inner.get(), kNoFlags, /*cap id=*/1));
  (void)inner.release();
  ASSERT_NE(cap.get(), nullptr);

  EXPECT_TRUE(CanBeEmptyString(cap.get()));
}

TEST(CanBeEmptyStringTest_223, Literal_DisallowsEmpty_223) {
  RegexpHolder lit(Regexp::NewLiteral('z', kNoFlags));
  ASSERT_NE(lit.get(), nullptr);
  EXPECT_FALSE(CanBeEmptyString(lit.get()));
}

// (Optional sanity) WalkExponential shouldn’t affect correctness for small trees.
// We can indirectly exercise it by building a slightly larger tree and ensuring
// the result remains correct (still black-box: we only assert the outcome).
TEST(CanBeEmptyStringTest_223, LargerTree_Sanity_223) {
  // ((a* b?) | (c{0,2})) -> Either branch allows empty.
  Regexp* left_subs[2];
  left_subs[0] = Regexp::Star(Regexp::NewLiteral('a', kNoFlags), kNoFlags);
  left_subs[1] = Regexp::Quest(Regexp::NewLiteral('b', kNoFlags), kNoFlags);
  ASSERT_NE(left_subs[0], nullptr);
  ASSERT_NE(left_subs[1], nullptr);
  Regexp* left = Regexp::Concat(left_subs, 2, kNoFlags);
  ASSERT_NE(left, nullptr);

  Regexp* right = Regexp::Repeat(Regexp::NewLiteral('c', kNoFlags), kNoFlags, 0, 2);
  ASSERT_NE(right, nullptr);

  Regexp* top_subs[2] = {left, right};
  RegexpHolder alt(Regexp::Alternate(top_subs, 2, kNoFlags));
  ASSERT_NE(alt.get(), nullptr);

  EXPECT_TRUE(CanBeEmptyString(alt.get()));
}

} // namespace re2
