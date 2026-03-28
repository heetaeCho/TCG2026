#include "gtest/gtest.h"
#include "re2/prefilter.h"
#include "re2/re2.h"
#include <string>
#include <vector>

namespace re2 {

// Test fixture for Prefilter tests
class PrefilterTest_542 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Clean up any allocated prefilters
  }
};

// Test basic construction with different Op values
TEST_F(PrefilterTest_542, ConstructWithAllOp_542) {
  Prefilter* pf_all = new Prefilter(Prefilter::ALL);
  EXPECT_EQ(Prefilter::ALL, pf_all->op());
  delete pf_all;
}

TEST_F(PrefilterTest_542, ConstructWithNoneOp_542) {
  Prefilter* pf_none = new Prefilter(Prefilter::NONE);
  EXPECT_EQ(Prefilter::NONE, pf_none->op());
  delete pf_none;
}

TEST_F(PrefilterTest_542, ConstructWithAtomOp_542) {
  Prefilter* pf_atom = new Prefilter(Prefilter::ATOM);
  EXPECT_EQ(Prefilter::ATOM, pf_atom->op());
  delete pf_atom;
}

TEST_F(PrefilterTest_542, ConstructWithAndOp_542) {
  Prefilter* pf_and = new Prefilter(Prefilter::AND);
  EXPECT_EQ(Prefilter::AND, pf_and->op());
  delete pf_and;
}

TEST_F(PrefilterTest_542, ConstructWithOrOp_542) {
  Prefilter* pf_or = new Prefilter(Prefilter::OR);
  EXPECT_EQ(Prefilter::OR, pf_or->op());
  delete pf_or;
}

// Test unique_id default and set/get
TEST_F(PrefilterTest_542, DefaultUniqueId_542) {
  Prefilter* pf = new Prefilter(Prefilter::NONE);
  // Default unique_id should be some initial value (typically -1 or 0)
  // We just test that set/get works consistently
  pf->set_unique_id(42);
  EXPECT_EQ(42, pf->unique_id());
  delete pf;
}

TEST_F(PrefilterTest_542, SetUniqueIdMultipleTimes_542) {
  Prefilter* pf = new Prefilter(Prefilter::NONE);
  pf->set_unique_id(0);
  EXPECT_EQ(0, pf->unique_id());
  pf->set_unique_id(100);
  EXPECT_EQ(100, pf->unique_id());
  pf->set_unique_id(-1);
  EXPECT_EQ(-1, pf->unique_id());
  delete pf;
}

// Test atom() accessor
TEST_F(PrefilterTest_542, AtomDefaultEmpty_542) {
  Prefilter* pf = new Prefilter(Prefilter::ATOM);
  // A newly constructed ATOM prefilter should have an empty atom
  EXPECT_TRUE(pf->atom().empty());
  delete pf;
}

// Test subs() accessor
TEST_F(PrefilterTest_542, SubsAccessor_542) {
  Prefilter* pf = new Prefilter(Prefilter::AND);
  // Initially subs might be NULL for a freshly constructed prefilter
  // We can set subs and verify
  std::vector<Prefilter*>* subs = new std::vector<Prefilter*>();
  subs->push_back(new Prefilter(Prefilter::NONE));
  pf->set_subs(subs);
  EXPECT_EQ(subs, pf->subs());
  EXPECT_EQ(1u, pf->subs()->size());
  delete pf;
}

// Test set_subs
TEST_F(PrefilterTest_542, SetSubsNullptr_542) {
  Prefilter* pf = new Prefilter(Prefilter::AND);
  pf->set_subs(nullptr);
  EXPECT_EQ(nullptr, pf->subs());
  delete pf;
}

// Test FromRE2 with a simple literal pattern
TEST_F(PrefilterTest_542, FromRE2SimpleLiteral_542) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(nullptr, pf);
  // A literal string should produce an ATOM prefilter
  EXPECT_EQ(Prefilter::ATOM, pf->op());
  EXPECT_EQ("hello", pf->atom());
  delete pf;
}

// Test FromRE2 with alternation
TEST_F(PrefilterTest_542, FromRE2Alternation_542) {
  RE2 re("hello|world");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(nullptr, pf);
  // Alternation should produce OR prefilter
  // The actual structure depends on internals, but it should not be NULL
  delete pf;
}

// Test FromRE2 with concatenation
TEST_F(PrefilterTest_542, FromRE2Concatenation_542) {
  RE2 re("abc.*def");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(nullptr, pf);
  // Should produce AND or some combined prefilter
  delete pf;
}

// Test FromRE2 with dot star (matches everything)
TEST_F(PrefilterTest_542, FromRE2DotStar_542) {
  RE2 re(".*");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // .* matches everything, prefilter might be ALL
  if (pf != nullptr) {
    EXPECT_EQ(Prefilter::ALL, pf->op());
    delete pf;
  }
}

// Test FromRE2 with character class
TEST_F(PrefilterTest_542, FromRE2CharClass_542) {
  RE2 re("[abc]def");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(nullptr, pf);
  delete pf;
}

// Test FromRE2 with empty pattern
TEST_F(PrefilterTest_542, FromRE2EmptyPattern_542) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // Empty pattern - prefilter may be ALL since it matches everything
  if (pf != nullptr) {
    delete pf;
  }
}

// Test FromRE2 with single character
TEST_F(PrefilterTest_542, FromRE2SingleChar_542) {
  RE2 re("a");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // Single character might be too short for a useful prefilter
  if (pf != nullptr) {
    delete pf;
  }
}

// Test FromRE2 with question mark (optional)
TEST_F(PrefilterTest_542, FromRE2Optional_542) {
  RE2 re("hello?world");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(nullptr, pf);
  delete pf;
}

// Test FromRE2 with plus (one or more)
TEST_F(PrefilterTest_542, FromRE2Plus_542) {
  RE2 re("hel+o");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(nullptr, pf);
  delete pf;
}

// Test FromRE2 with star (zero or more)
TEST_F(PrefilterTest_542, FromRE2Star_542) {
  RE2 re("hel*o");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(nullptr, pf);
  delete pf;
}

// Test DebugString on ATOM
TEST_F(PrefilterTest_542, DebugStringAtom_542) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(nullptr, pf);
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
  delete pf;
}

// Test DebugString on ALL
TEST_F(PrefilterTest_542, DebugStringAll_542) {
  Prefilter* pf = new Prefilter(Prefilter::ALL);
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
  delete pf;
}

// Test DebugString on NONE
TEST_F(PrefilterTest_542, DebugStringNone_542) {
  Prefilter* pf = new Prefilter(Prefilter::NONE);
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
  delete pf;
}

// Test FromRE2 with complex pattern
TEST_F(PrefilterTest_542, FromRE2ComplexPattern_542) {
  RE2 re("(foo|bar).*baz");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(nullptr, pf);
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
  delete pf;
}

// Test FromRE2 with nested groups
TEST_F(PrefilterTest_542, FromRE2NestedGroups_542) {
  RE2 re("((abc)(def))");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(nullptr, pf);
  delete pf;
}

// Test FromRE2 case insensitive
TEST_F(PrefilterTest_542, FromRE2CaseInsensitive_542) {
  RE2 re("(?i)hello");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // Case insensitive may produce different prefilter structure
  if (pf != nullptr) {
    delete pf;
  }
}

// Test FromRE2 with anchors
TEST_F(PrefilterTest_542, FromRE2WithAnchors_542) {
  RE2 re("^hello$");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(nullptr, pf);
  delete pf;
}

// Test FromRE2 with long literal
TEST_F(PrefilterTest_542, FromRE2LongLiteral_542) {
  RE2 re("thisisaverylongstringpattern");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(nullptr, pf);
  EXPECT_EQ(Prefilter::ATOM, pf->op());
  EXPECT_EQ("thisisaverylongstringpattern", pf->atom());
  delete pf;
}

// Test set_subs and subs with multiple children
TEST_F(PrefilterTest_542, SetSubsMultipleChildren_542) {
  Prefilter* pf = new Prefilter(Prefilter::AND);
  std::vector<Prefilter*>* subs = new std::vector<Prefilter*>();
  subs->push_back(new Prefilter(Prefilter::NONE));
  subs->push_back(new Prefilter(Prefilter::ALL));
  subs->push_back(new Prefilter(Prefilter::ATOM));
  pf->set_subs(subs);
  EXPECT_EQ(3u, pf->subs()->size());
  delete pf;
}

// Test FromRE2 with unicode
TEST_F(PrefilterTest_542, FromRE2Unicode_542) {
  RE2 re("café");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(nullptr, pf);
  delete pf;
}

// Test FromRE2 with repetition
TEST_F(PrefilterTest_542, FromRE2Repetition_542) {
  RE2 re("a{3,5}bcd");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(nullptr, pf);
  delete pf;
}

// Test that destructor handles NULL subs gracefully
TEST_F(PrefilterTest_542, DestructorWithNullSubs_542) {
  Prefilter* pf = new Prefilter(Prefilter::AND);
  pf->set_subs(nullptr);
  // Should not crash on delete
  delete pf;
}

// Test DebugString on OR with subs
TEST_F(PrefilterTest_542, DebugStringOrWithSubs_542) {
  RE2 re("foo|bar|baz");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(nullptr, pf);
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
  delete pf;
}

// Test FromRE2 with only wildcards
TEST_F(PrefilterTest_542, FromRE2OnlyWildcard_542) {
  RE2 re(".");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    EXPECT_EQ(Prefilter::ALL, pf->op());
    delete pf;
  }
}

// Test unique_id with boundary values
TEST_F(PrefilterTest_542, UniqueIdBoundaryValues_542) {
  Prefilter* pf = new Prefilter(Prefilter::NONE);
  pf->set_unique_id(0);
  EXPECT_EQ(0, pf->unique_id());
  pf->set_unique_id(INT32_MAX);
  EXPECT_EQ(INT32_MAX, pf->unique_id());
  pf->set_unique_id(INT32_MIN);
  EXPECT_EQ(INT32_MIN, pf->unique_id());
  delete pf;
}

// Test FromRE2 AND structure
TEST_F(PrefilterTest_542, FromRE2AndStructure_542) {
  RE2 re("abcdef");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(nullptr, pf);
  // A long literal should be a single ATOM
  EXPECT_EQ(Prefilter::ATOM, pf->op());
  delete pf;
}

}  // namespace re2
