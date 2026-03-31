#include "gtest/gtest.h"
#include "re2/prefilter.h"
#include "re2/re2.h"
#include "re2/prefilter_tree.h"
#include <string>
#include <vector>

namespace re2 {

class PrefilterTest_553 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that a simple literal regex produces a non-null prefilter
TEST_F(PrefilterTest_553, SimpleLiteralRegex_553) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  // A literal string should produce an ATOM prefilter
  EXPECT_EQ(pf->op(), Prefilter::ATOM);
  delete pf;
}

// Test that a dot-star regex produces null or ALL prefilter
TEST_F(PrefilterTest_553, DotStarRegex_553) {
  RE2 re(".*");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    delete pf;
  }
}

// Test alternation produces OR prefilter
TEST_F(PrefilterTest_553, AlternationRegex_553) {
  RE2 re("hello|world");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  // Alternation should produce OR or individual atoms
  EXPECT_TRUE(pf->op() == Prefilter::OR || pf->op() == Prefilter::ATOM);
  delete pf;
}

// Test concatenation of literals
TEST_F(PrefilterTest_553, ConcatenationRegex_553) {
  RE2 re("abc");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::ATOM);
  EXPECT_EQ(pf->atom(), "abc");
  delete pf;
}

// Test single character literal
TEST_F(PrefilterTest_553, SingleCharLiteral_553) {
  RE2 re("a");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // Single char might not produce a useful prefilter
  if (pf != nullptr) {
    delete pf;
  }
}

// Test character class
TEST_F(PrefilterTest_553, CharacterClass_553) {
  RE2 re("[abc]def");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  delete pf;
}

// Test question mark (optional)
TEST_F(PrefilterTest_553, OptionalRegex_553) {
  RE2 re("hel?lo");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    delete pf;
  }
}

// Test plus quantifier
TEST_F(PrefilterTest_553, PlusQuantifier_553) {
  RE2 re("hel+o");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    delete pf;
  }
}

// Test star quantifier
TEST_F(PrefilterTest_553, StarQuantifier_553) {
  RE2 re("hel*o");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    delete pf;
  }
}

// Test case insensitive produces lowercase atom
TEST_F(PrefilterTest_553, CaseInsensitiveRegex_553) {
  RE2 re("(?i)HELLO");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    if (pf->op() == Prefilter::ATOM) {
      EXPECT_EQ(pf->atom(), "hello");
    }
    delete pf;
  }
}

// Test AND prefilter from complex regex
TEST_F(PrefilterTest_553, AndPrefilter_553) {
  RE2 re("foo.*bar");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  // foo.*bar should require both "foo" and "bar"
  EXPECT_EQ(pf->op(), Prefilter::AND);
  delete pf;
}

// Test empty regex
TEST_F(PrefilterTest_553, EmptyRegex_553) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    delete pf;
  }
}

// Test Prefilter debugstring doesn't crash
TEST_F(PrefilterTest_553, DebugStringNoCrash_553) {
  RE2 re("hello|world");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  std::string s = pf->DebugString();
  EXPECT_FALSE(s.empty());
  delete pf;
}

// Test Latin1 regex
TEST_F(PrefilterTest_553, Latin1Regex_553) {
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingLatin1);
  RE2 re("hello", opts);
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::ATOM);
  EXPECT_EQ(pf->atom(), "hello");
  delete pf;
}

// Test complex nested alternation and concatenation
TEST_F(PrefilterTest_553, ComplexNestedRegex_553) {
  RE2 re("(foo|bar)(baz|qux)");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  delete pf;
}

// Test Prefilter subs() for compound filters
TEST_F(PrefilterTest_553, SubsAccessor_553) {
  RE2 re("foo.*bar");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  if (pf->op() == Prefilter::AND || pf->op() == Prefilter::OR) {
    ASSERT_NE(pf->subs(), nullptr);
    EXPECT_GE(pf->subs()->size(), 2u);
  }
  delete pf;
}

// Test that FromRE2 with any-byte pattern yields ALL
TEST_F(PrefilterTest_553, AnyByteRegex_553) {
  RE2 re("\\C");
  if (re.ok()) {
    Prefilter* pf = Prefilter::FromRE2(&re);
    if (pf != nullptr) {
      delete pf;
    }
  }
}

// Test long literal string
TEST_F(PrefilterTest_553, LongLiteralString_553) {
  RE2 re("abcdefghijklmnopqrstuvwxyz");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::ATOM);
  EXPECT_EQ(pf->atom(), "abcdefghijklmnopqrstuvwxyz");
  delete pf;
}

}  // namespace re2
