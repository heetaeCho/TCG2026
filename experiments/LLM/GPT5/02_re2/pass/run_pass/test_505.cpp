// File: parse_do_finish_test_505.cc
#include "gtest/gtest.h"
#include "re2/regexp.h"

using re2::Regexp;
using re2::RegexpStatus;
using re2::kRegexpMissingParen;

namespace {

static inline Regexp::ParseFlags kNoFlags =
    static_cast<Regexp::ParseFlags>(0);

// Normal operation: simple literal parses successfully.
TEST(DoFinishTest_505, ParseSimpleLiteral_OK_505) {
  RegexpStatus st;
  Regexp* re = Regexp::Parse("a", kNoFlags, &st);
  ASSERT_TRUE(st.ok());
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Boundary condition: empty pattern parses successfully.
TEST(DoFinishTest_505, ParseEmpty_OK_505) {
  RegexpStatus st;
  Regexp* re = Regexp::Parse("", kNoFlags, &st);
  ASSERT_TRUE(st.ok());
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Normal operation with grouping: balanced parentheses.
TEST(DoFinishTest_505, ParseBalancedParens_OK_505) {
  RegexpStatus st;
  Regexp* re = Regexp::Parse("(a)", kNoFlags, &st);
  ASSERT_TRUE(st.ok());
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Error case: missing right parenthesis should set status to kRegexpMissingParen,
// set error_arg to the whole regexp, and return nullptr.
TEST(DoFinishTest_505, MissingRightParen_SetsStatusAndReturnsNull_505) {
  RegexpStatus st;
  Regexp* re = Regexp::Parse("(a", kNoFlags, &st);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(st.ok());
  EXPECT_EQ(st.code(), kRegexpMissingParen);
  EXPECT_EQ(std::string(st.error_arg()), "(a");
}

// Another observable missing-paren scenario (ensures detection when other tokens exist).
TEST(DoFinishTest_505, MissingRightParenWithTrailingLiteral_SetsStatus_505) {
  RegexpStatus st;
  Regexp* re = Regexp::Parse("a(", kNoFlags, &st);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(st.ok());
  EXPECT_EQ(st.code(), kRegexpMissingParen);
  EXPECT_EQ(std::string(st.error_arg()), "a(");
}

}  // namespace
