#include "gtest/gtest.h"
#include "re2/prefilter.h"
#include "re2/re2.h"
#include <string>
#include <vector>

namespace re2 {

// Test basic construction with different Op types
TEST(PrefilterTest_543, ConstructWithAllOp_543) {
  Prefilter* pf_all = new Prefilter(Prefilter::ALL);
  EXPECT_EQ(Prefilter::ALL, pf_all->op());
  delete pf_all;
}

TEST(PrefilterTest_543, ConstructWithNoneOp_543) {
  Prefilter* pf_none = new Prefilter(Prefilter::NONE);
  EXPECT_EQ(Prefilter::NONE, pf_none->op());
  delete pf_none;
}

TEST(PrefilterTest_543, ConstructWithAtomOp_543) {
  Prefilter* pf_atom = new Prefilter(Prefilter::ATOM);
  EXPECT_EQ(Prefilter::ATOM, pf_atom->op());
  delete pf_atom;
}

TEST(PrefilterTest_543, ConstructWithAndOp_543) {
  Prefilter* pf_and = new Prefilter(Prefilter::AND);
  EXPECT_EQ(Prefilter::AND, pf_and->op());
  delete pf_and;
}

TEST(PrefilterTest_543, ConstructWithOrOp_543) {
  Prefilter* pf_or = new Prefilter(Prefilter::OR);
  EXPECT_EQ(Prefilter::OR, pf_or->op());
  delete pf_or;
}

// Test unique_id getter and setter
TEST(PrefilterTest_543, UniqueIdDefaultValue_543) {
  Prefilter* pf = new Prefilter(Prefilter::ALL);
  // Default unique_id should be some initial value (commonly -1 or 0)
  // We just test set/get roundtrip
  pf->set_unique_id(42);
  EXPECT_EQ(42, pf->unique_id());
  delete pf;
}

TEST(PrefilterTest_543, SetUniqueIdMultipleTimes_543) {
  Prefilter* pf = new Prefilter(Prefilter::ALL);
  pf->set_unique_id(0);
  EXPECT_EQ(0, pf->unique_id());
  pf->set_unique_id(100);
  EXPECT_EQ(100, pf->unique_id());
  pf->set_unique_id(-1);
  EXPECT_EQ(-1, pf->unique_id());
  delete pf;
}

// Test atom getter
TEST(PrefilterTest_543, AtomDefaultEmpty_543) {
  Prefilter* pf = new Prefilter(Prefilter::ATOM);
  EXPECT_TRUE(pf->atom().empty());
  delete pf;
}

// Test subs getter and setter
TEST(PrefilterTest_543, SubsDefaultNull_543) {
  Prefilter* pf = new Prefilter(Prefilter::AND);
  // subs may or may not be null initially depending on op; just test set/get
  auto* subs = new std::vector<Prefilter*>();
  pf->set_subs(subs);
  EXPECT_EQ(subs, pf->subs());
  delete pf;  // Prefilter destructor should handle cleanup of subs
}

TEST(PrefilterTest_543, SetSubsWithElements_543) {
  Prefilter* pf = new Prefilter(Prefilter::AND);
  auto* subs = new std::vector<Prefilter*>();
  subs->push_back(new Prefilter(Prefilter::ALL));
  subs->push_back(new Prefilter(Prefilter::NONE));
  pf->set_subs(subs);
  EXPECT_EQ(subs, pf->subs());
  EXPECT_EQ(2u, pf->subs()->size());
  delete pf;
}

// Test DebugString
TEST(PrefilterTest_543, DebugStringAll_543) {
  Prefilter* pf = new Prefilter(Prefilter::ALL);
  std::string debug = pf->DebugString();
  // Should return some non-crash string representation
  // For ALL, it's typically "*"
  EXPECT_FALSE(debug.empty());
  delete pf;
}

TEST(PrefilterTest_543, DebugStringNone_543) {
  Prefilter* pf = new Prefilter(Prefilter::NONE);
  std::string debug = pf->DebugString();
  // NONE should produce some string
  EXPECT_FALSE(debug.empty());
  delete pf;
}

// Test FromRE2 with simple literal pattern
TEST(PrefilterTest_543, FromRE2SimpleLiteral_543) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // A simple literal should produce a non-null prefilter
  ASSERT_NE(nullptr, pf);
  // It should be an ATOM with the literal string
  EXPECT_EQ(Prefilter::ATOM, pf->op());
  EXPECT_EQ("hello", pf->atom());
  delete pf;
}

// Test FromRE2 with alternation
TEST(PrefilterTest_543, FromRE2Alternation_543) {
  RE2 re("hello|world");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(nullptr, pf);
  // Alternation typically produces OR
  EXPECT_EQ(Prefilter::OR, pf->op());
  ASSERT_NE(nullptr, pf->subs());
  EXPECT_EQ(2u, pf->subs()->size());
  delete pf;
}

// Test FromRE2 with concatenation that should produce AND
TEST(PrefilterTest_543, FromRE2Concatenation_543) {
  RE2 re("hello.*world");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(nullptr, pf);
  // Concatenation with .* should produce AND of the two atoms
  EXPECT_EQ(Prefilter::AND, pf->op());
  delete pf;
}

// Test FromRE2 with dot-star (matches everything)
TEST(PrefilterTest_543, FromRE2DotStar_543) {
  RE2 re(".*");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // .* should return ALL prefilter (everything matches)
  if (pf != nullptr) {
    EXPECT_EQ(Prefilter::ALL, pf->op());
    delete pf;
  }
  // It's also acceptable for pf to be null for "match everything"
}

// Test FromRE2 with character class
TEST(PrefilterTest_543, FromRE2CharClass_543) {
  RE2 re("[abc]def");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(nullptr, pf);
  // Should produce some meaningful prefilter
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
  delete pf;
}

// Test FromRE2 with single character
TEST(PrefilterTest_543, FromRE2SingleChar_543) {
  RE2 re("a");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // Single character might not produce a prefilter (too short atom)
  // or might produce ALL
  if (pf != nullptr) {
    delete pf;
  }
}

// Test FromRE2 with longer pattern
TEST(PrefilterTest_543, FromRE2LongerPattern_543) {
  RE2 re("abcdef");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(nullptr, pf);
  EXPECT_EQ(Prefilter::ATOM, pf->op());
  EXPECT_EQ("abcdef", pf->atom());
  delete pf;
}

// Test FromRE2 with case-insensitive pattern
TEST(PrefilterTest_543, FromRE2CaseInsensitive_543) {
  RE2 re("(?i)hello");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // Case-insensitive could produce OR of all case combinations or ALL
  if (pf != nullptr) {
    std::string debug = pf->DebugString();
    EXPECT_FALSE(debug.empty());
    delete pf;
  }
}

// Test FromRE2 with question mark (optional)
TEST(PrefilterTest_543, FromRE2Optional_543) {
  RE2 re("hel?lo");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    std::string debug = pf->DebugString();
    EXPECT_FALSE(debug.empty());
    delete pf;
  }
}

// Test FromRE2 with plus (one or more)
TEST(PrefilterTest_543, FromRE2Plus_543) {
  RE2 re("hel+o");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    std::string debug = pf->DebugString();
    EXPECT_FALSE(debug.empty());
    delete pf;
  }
}

// Test FromRE2 with complex pattern
TEST(PrefilterTest_543, FromRE2ComplexPattern_543) {
  RE2 re("(abc|def).*ghi");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(nullptr, pf);
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
  delete pf;
}

// Test DebugString for AND node
TEST(PrefilterTest_543, DebugStringAndNode_543) {
  RE2 re("hello.*world");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(nullptr, pf);
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
  // AND debug string should contain both atoms
  delete pf;
}

// Test DebugString for OR node
TEST(PrefilterTest_543, DebugStringOrNode_543) {
  RE2 re("hello|world");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(nullptr, pf);
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
  delete pf;
}

// Test that FromRE2 with null is handled (if applicable)
// This might crash, so we're testing with valid RE2 objects only

// Test unique_id boundary values
TEST(PrefilterTest_543, UniqueIdBoundaryValues_543) {
  Prefilter* pf = new Prefilter(Prefilter::ALL);
  pf->set_unique_id(0);
  EXPECT_EQ(0, pf->unique_id());

  pf->set_unique_id(INT32_MAX);
  EXPECT_EQ(INT32_MAX, pf->unique_id());

  pf->set_unique_id(INT32_MIN);
  EXPECT_EQ(INT32_MIN, pf->unique_id());
  delete pf;
}

// Test FromRE2 with empty string pattern
TEST(PrefilterTest_543, FromRE2EmptyPattern_543) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // Empty pattern matches everything, should return ALL or null
  if (pf != nullptr) {
    EXPECT_EQ(Prefilter::ALL, pf->op());
    delete pf;
  }
}

// Test FromRE2 with anchored pattern
TEST(PrefilterTest_543, FromRE2AnchoredPattern_543) {
  RE2 re("^hello$");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(nullptr, pf);
  EXPECT_EQ(Prefilter::ATOM, pf->op());
  EXPECT_EQ("hello", pf->atom());
  delete pf;
}

// Test destruction with subs (no crash)
TEST(PrefilterTest_543, DestructionWithSubs_543) {
  Prefilter* pf = new Prefilter(Prefilter::AND);
  auto* subs = new std::vector<Prefilter*>();
  subs->push_back(new Prefilter(Prefilter::ALL));
  subs->push_back(new Prefilter(Prefilter::NONE));
  subs->push_back(new Prefilter(Prefilter::ALL));
  pf->set_subs(subs);
  // Should not crash
  delete pf;
}

// Test FromRE2 with Unicode pattern
TEST(PrefilterTest_543, FromRE2UnicodePattern_543) {
  RE2 re("héllo");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    std::string debug = pf->DebugString();
    EXPECT_FALSE(debug.empty());
    delete pf;
  }
}

// Test FromRE2 with repeated alternations
TEST(PrefilterTest_543, FromRE2MultipleAlternations_543) {
  RE2 re("abc|def|ghi|jkl");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(nullptr, pf);
  EXPECT_EQ(Prefilter::OR, pf->op());
  ASSERT_NE(nullptr, pf->subs());
  EXPECT_EQ(4u, pf->subs()->size());
  delete pf;
}

// Test that op() returns the correct value after construction
TEST(PrefilterTest_543, OpConsistency_543) {
  for (auto op : {Prefilter::ALL, Prefilter::NONE, Prefilter::ATOM,
                   Prefilter::AND, Prefilter::OR}) {
    Prefilter* pf = new Prefilter(op);
    EXPECT_EQ(op, pf->op());
    delete pf;
  }
}

}  // namespace re2
