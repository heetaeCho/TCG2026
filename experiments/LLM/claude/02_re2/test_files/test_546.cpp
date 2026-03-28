#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/prefilter.h"

namespace re2 {

// Test basic construction and destruction
TEST(PrefilterTest_546, ConstructWithAllOp_546) {
  Prefilter* pf = new Prefilter(Prefilter::ALL);
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::ALL);
  delete pf;
}

TEST(PrefilterTest_546, ConstructWithNoneOp_546) {
  Prefilter* pf = new Prefilter(Prefilter::NONE);
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::NONE);
  delete pf;
}

TEST(PrefilterTest_546, ConstructWithAtomOp_546) {
  Prefilter* pf = new Prefilter(Prefilter::ATOM);
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::ATOM);
  delete pf;
}

TEST(PrefilterTest_546, ConstructWithAndOp_546) {
  Prefilter* pf = new Prefilter(Prefilter::AND);
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::AND);
  delete pf;
}

TEST(PrefilterTest_546, ConstructWithOrOp_546) {
  Prefilter* pf = new Prefilter(Prefilter::OR);
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::OR);
  delete pf;
}

// Test unique_id get/set
TEST(PrefilterTest_546, UniqueIdDefaultValue_546) {
  Prefilter* pf = new Prefilter(Prefilter::ALL);
  // Check that unique_id can be set and retrieved
  pf->set_unique_id(42);
  EXPECT_EQ(pf->unique_id(), 42);
  delete pf;
}

TEST(PrefilterTest_546, SetUniqueIdMultipleTimes_546) {
  Prefilter* pf = new Prefilter(Prefilter::NONE);
  pf->set_unique_id(0);
  EXPECT_EQ(pf->unique_id(), 0);
  pf->set_unique_id(100);
  EXPECT_EQ(pf->unique_id(), 100);
  pf->set_unique_id(-1);
  EXPECT_EQ(pf->unique_id(), -1);
  delete pf;
}

// Test atom
TEST(PrefilterTest_546, AtomDefaultEmpty_546) {
  Prefilter* pf = new Prefilter(Prefilter::ATOM);
  EXPECT_TRUE(pf->atom().empty());
  delete pf;
}

// Test subs
TEST(PrefilterTest_546, SubsInitiallyNull_546) {
  Prefilter* pf = new Prefilter(Prefilter::AND);
  // subs might be null initially for a freshly constructed Prefilter
  // We just check it doesn't crash
  auto* s = pf->subs();
  (void)s;
  delete pf;
}

TEST(PrefilterTest_546, SetSubs_546) {
  Prefilter* pf = new Prefilter(Prefilter::AND);
  auto* vec = new std::vector<Prefilter*>();
  pf->set_subs(vec);
  EXPECT_EQ(pf->subs(), vec);
  delete pf;
}

// Test FromRE2 with simple literal pattern
TEST(PrefilterTest_546, FromRE2SimpleLiteral_546) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  // A simple literal should produce an ATOM prefilter
  EXPECT_EQ(pf->op(), Prefilter::ATOM);
  EXPECT_EQ(pf->atom(), "hello");
  delete pf;
}

TEST(PrefilterTest_546, FromRE2MatchAll_546) {
  RE2 re(".*");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // .* matches everything, so prefilter should be ALL
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    delete pf;
  }
}

TEST(PrefilterTest_546, FromRE2Alternation_546) {
  RE2 re("hello|world");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  // Alternation should produce an OR prefilter
  EXPECT_EQ(pf->op(), Prefilter::OR);
  delete pf;
}

TEST(PrefilterTest_546, FromRE2Concatenation_546) {
  RE2 re("abc.*def");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  // Should produce AND of "abc" and "def"
  EXPECT_EQ(pf->op(), Prefilter::AND);
  delete pf;
}

// Test DebugString
TEST(PrefilterTest_546, DebugStringAtom_546) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
  // The debug string should contain the atom
  EXPECT_NE(debug.find("hello"), std::string::npos);
  delete pf;
}

TEST(PrefilterTest_546, DebugStringAll_546) {
  Prefilter* pf = new Prefilter(Prefilter::ALL);
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
  delete pf;
}

TEST(PrefilterTest_546, DebugStringNone_546) {
  Prefilter* pf = new Prefilter(Prefilter::NONE);
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
  delete pf;
}

// Test FromRE2 with single character
TEST(PrefilterTest_546, FromRE2SingleChar_546) {
  RE2 re("a");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // Single character might result in ALL since it's too short
  if (pf != nullptr) {
    delete pf;
  }
}

// Test FromRE2 with character class
TEST(PrefilterTest_546, FromRE2CharClass_546) {
  RE2 re("[abc]def");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  delete pf;
}

// Test FromRE2 with complex pattern
TEST(PrefilterTest_546, FromRE2ComplexPattern_546) {
  RE2 re("(foo|bar).*baz");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  delete pf;
}

// Test FromRE2 with empty pattern
TEST(PrefilterTest_546, FromRE2EmptyPattern_546) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    delete pf;
  }
}

// Test FromRE2 with repetition
TEST(PrefilterTest_546, FromRE2Repetition_546) {
  RE2 re("abc+def");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  delete pf;
}

// Test FromRE2 with optional
TEST(PrefilterTest_546, FromRE2Optional_546) {
  RE2 re("abc?def");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  delete pf;
}

// Test FromRE2 with case insensitive
TEST(PrefilterTest_546, FromRE2CaseInsensitive_546) {
  RE2 re("(?i)hello");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    delete pf;
  }
}

// Test FromRE2 with long literal
TEST(PrefilterTest_546, FromRE2LongLiteral_546) {
  RE2 re("abcdefghijklmnop");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::ATOM);
  EXPECT_EQ(pf->atom(), "abcdefghijklmnop");
  delete pf;
}

// Test subs for OR prefilter
TEST(PrefilterTest_546, SubsForOrPrefilter_546) {
  RE2 re("hello|world");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  if (pf->op() == Prefilter::OR) {
    ASSERT_NE(pf->subs(), nullptr);
    EXPECT_GE(pf->subs()->size(), 2u);
  }
  delete pf;
}

// Test subs for AND prefilter
TEST(PrefilterTest_546, SubsForAndPrefilter_546) {
  RE2 re("abc.*def");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  if (pf->op() == Prefilter::AND) {
    ASSERT_NE(pf->subs(), nullptr);
    EXPECT_GE(pf->subs()->size(), 2u);
  }
  delete pf;
}

// Test DebugString for OR prefilter
TEST(PrefilterTest_546, DebugStringOr_546) {
  RE2 re("hello|world");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
  delete pf;
}

// Test DebugString for AND prefilter
TEST(PrefilterTest_546, DebugStringAnd_546) {
  RE2 re("abc.*def");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
  delete pf;
}

// Test FromRE2 with dot star
TEST(PrefilterTest_546, FromRE2DotStar_546) {
  RE2 re(".*");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    delete pf;
  }
}

// Test FromRE2 with unicode
TEST(PrefilterTest_546, FromRE2Unicode_546) {
  RE2 re("café");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  delete pf;
}

// Test boundary: set_unique_id with large value
TEST(PrefilterTest_546, UniqueIdLargeValue_546) {
  Prefilter* pf = new Prefilter(Prefilter::ALL);
  pf->set_unique_id(2147483647);  // INT_MAX
  EXPECT_EQ(pf->unique_id(), 2147483647);
  delete pf;
}

// Test FromRE2 with nested groups
TEST(PrefilterTest_546, FromRE2NestedGroups_546) {
  RE2 re("((abc)(def))");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::ATOM);
  EXPECT_EQ(pf->atom(), "abcdef");
  delete pf;
}

// Test FromRE2 with multiple alternations
TEST(PrefilterTest_546, FromRE2MultipleAlternations_546) {
  RE2 re("aaa|bbb|ccc|ddd");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  if (pf->op() == Prefilter::OR) {
    ASSERT_NE(pf->subs(), nullptr);
    EXPECT_GE(pf->subs()->size(), 2u);
  }
  delete pf;
}

}  // namespace re2
