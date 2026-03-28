#include "gtest/gtest.h"
#include "re2/prefilter.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/prog.h"
#include <string>
#include <memory>

namespace re2 {

// Since Prefilter::Info is a private nested class, we test through Prefilter's
// public interface which uses Info internally.

class PrefilterTest_549 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that FromRE2 returns a non-null Prefilter for a simple literal pattern
TEST_F(PrefilterTest_549, FromRE2SimpleLiteral_549) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // A simple literal should produce a prefilter
  ASSERT_NE(pf, nullptr);
  delete pf;
}

// Test that FromRE2 returns a prefilter for alternation
TEST_F(PrefilterTest_549, FromRE2Alternation_549) {
  RE2 re("hello|world");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  delete pf;
}

// Test that FromRE2 handles dot-star (any match)
TEST_F(PrefilterTest_549, FromRE2DotStar_549) {
  RE2 re(".*");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // .* matches everything, prefilter may be ALL or null
  delete pf;
}

// Test that FromRE2 handles concatenation
TEST_F(PrefilterTest_549, FromRE2Concatenation_549) {
  RE2 re("abc.*def");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  delete pf;
}

// Test that FromRE2 handles character class
TEST_F(PrefilterTest_549, FromRE2CharClass_549) {
  RE2 re("[abc]def");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  delete pf;
}

// Test that FromRE2 handles plus quantifier
TEST_F(PrefilterTest_549, FromRE2PlusQuantifier_549) {
  RE2 re("a+");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // a+ should produce a prefilter with at least "a"
  delete pf;
}

// Test that FromRE2 handles question mark quantifier
TEST_F(PrefilterTest_549, FromRE2QuestQuantifier_549) {
  RE2 re("ab?c");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  delete pf;
}

// Test that FromRE2 handles star quantifier
TEST_F(PrefilterTest_549, FromRE2StarQuantifier_549) {
  RE2 re("ab*c");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  delete pf;
}

// Test Prefilter DebugString on a simple literal
TEST_F(PrefilterTest_549, DebugStringLiteral_549) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
  delete pf;
}

// Test empty string pattern
TEST_F(PrefilterTest_549, FromRE2EmptyString_549) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // Empty string - prefilter could be null or ALL
  delete pf;
}

// Test complex nested expression
TEST_F(PrefilterTest_549, FromRE2ComplexExpression_549) {
  RE2 re("(foo|bar).*baz");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  delete pf;
}

// Test single character
TEST_F(PrefilterTest_549, FromRE2SingleChar_549) {
  RE2 re("x");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  delete pf;
}

// Test that AND type prefilter is produced for concatenation with alternation
TEST_F(PrefilterTest_549, FromRE2AndType_549) {
  RE2 re("hello.*world");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  // Should be AND of "hello" and "world"
  EXPECT_EQ(pf->op(), Prefilter::AND);
  delete pf;
}

// Test that OR type prefilter is produced for alternation
TEST_F(PrefilterTest_549, FromRE2OrType_549) {
  RE2 re("hello|world");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::OR);
  delete pf;
}

// Test ATOM type for simple literal
TEST_F(PrefilterTest_549, FromRE2AtomType_549) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::ATOM);
  EXPECT_EQ(pf->atom(), "hello");
  delete pf;
}

// Test with Unicode/Latin1 characters
TEST_F(PrefilterTest_549, FromRE2Latin1_549) {
  RE2::Options opt;
  opt.set_encoding(RE2::Options::EncodingLatin1);
  RE2 re("caf\xe9", opt);
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  delete pf;
}

// Test ALL type for .* pattern
TEST_F(PrefilterTest_549, FromRE2AllType_549) {
  RE2 re(".*");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
  }
  delete pf;
}

// Test single dot (any char)
TEST_F(PrefilterTest_549, FromRE2AnyChar_549) {
  RE2 re(".");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // Single any char - likely ALL
  delete pf;
}

}  // namespace re2
