#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/prefilter.h"

#include <string>
#include <vector>

namespace re2 {

class PrefilterTest_545 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Clean up any allocated prefilters
  }
};

// Test basic construction with ALL op
TEST_F(PrefilterTest_545, ConstructWithAllOp_545) {
  Prefilter pf(Prefilter::ALL);
  EXPECT_EQ(pf.op(), Prefilter::ALL);
}

// Test basic construction with NONE op
TEST_F(PrefilterTest_545, ConstructWithNoneOp_545) {
  Prefilter pf(Prefilter::NONE);
  EXPECT_EQ(pf.op(), Prefilter::NONE);
}

// Test unique_id get/set
TEST_F(PrefilterTest_545, UniqueIdGetSet_545) {
  Prefilter pf(Prefilter::ALL);
  pf.set_unique_id(42);
  EXPECT_EQ(pf.unique_id(), 42);
}

// Test unique_id default value
TEST_F(PrefilterTest_545, UniqueIdDefault_545) {
  Prefilter pf(Prefilter::ALL);
  // The default unique_id should be some initial value (likely -1 or 0)
  // We just test that it's retrievable without crashing
  int id = pf.unique_id();
  (void)id;
}

// Test unique_id with negative value
TEST_F(PrefilterTest_545, UniqueIdNegative_545) {
  Prefilter pf(Prefilter::ALL);
  pf.set_unique_id(-1);
  EXPECT_EQ(pf.unique_id(), -1);
}

// Test unique_id with zero
TEST_F(PrefilterTest_545, UniqueIdZero_545) {
  Prefilter pf(Prefilter::ALL);
  pf.set_unique_id(0);
  EXPECT_EQ(pf.unique_id(), 0);
}

// Test atom() on a non-ATOM prefilter
TEST_F(PrefilterTest_545, AtomOnNonAtomPrefilter_545) {
  Prefilter pf(Prefilter::ALL);
  // atom() should return a reference to the string, likely empty for non-ATOM
  const std::string& a = pf.atom();
  (void)a;
}

// Test subs() on a prefilter without subs
TEST_F(PrefilterTest_545, SubsInitiallyNull_545) {
  Prefilter pf(Prefilter::ALL);
  // subs() may return NULL if not set
  // Just ensure it doesn't crash
  std::vector<Prefilter*>* s = pf.subs();
  (void)s;
}

// Test set_subs
TEST_F(PrefilterTest_545, SetSubs_545) {
  Prefilter* pf = new Prefilter(Prefilter::AND);
  std::vector<Prefilter*>* subs = new std::vector<Prefilter*>();
  pf->set_subs(subs);
  EXPECT_EQ(pf->subs(), subs);
  delete pf;  // destructor should clean up subs
}

// Test DebugString on ALL prefilter
TEST_F(PrefilterTest_545, DebugStringAll_545) {
  Prefilter pf(Prefilter::ALL);
  std::string debug = pf.DebugString();
  EXPECT_FALSE(debug.empty());
}

// Test DebugString on NONE prefilter
TEST_F(PrefilterTest_545, DebugStringNone_545) {
  Prefilter pf(Prefilter::NONE);
  std::string debug = pf.DebugString();
  EXPECT_FALSE(debug.empty());
}

// Test FromRE2 with a simple literal pattern
TEST_F(PrefilterTest_545, FromRE2SimpleLiteral_545) {
  RE2 re("hello");
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  // A simple literal should produce an ATOM prefilter
  EXPECT_EQ(pf->op(), Prefilter::ATOM);
  EXPECT_EQ(pf->atom(), "hello");
  delete pf;
}

// Test FromRE2 with alternation
TEST_F(PrefilterTest_545, FromRE2Alternation_545) {
  RE2 re("hello|world");
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  // Alternation should produce OR
  EXPECT_EQ(pf->op(), Prefilter::OR);
  delete pf;
}

// Test FromRE2 with concatenation of literals
TEST_F(PrefilterTest_545, FromRE2Concatenation_545) {
  RE2 re("abc");
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::ATOM);
  EXPECT_EQ(pf->atom(), "abc");
  delete pf;
}

// Test FromRE2 with dot star (match anything)
TEST_F(PrefilterTest_545, FromRE2DotStar_545) {
  RE2 re(".*");
  Prefilter* pf = Prefilter::FromRE2(&re);
  // .* matches everything, so prefilter should be ALL or NULL
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    delete pf;
  }
}

// Test FromRE2 with complex pattern
TEST_F(PrefilterTest_545, FromRE2ComplexPattern_545) {
  RE2 re("(foo|bar)baz");
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
  delete pf;
}

// Test FromRE2 with single character
TEST_F(PrefilterTest_545, FromRE2SingleChar_545) {
  RE2 re("a");
  Prefilter* pf = Prefilter::FromRE2(&re);
  // Single character might produce ATOM or ALL depending on implementation
  if (pf != nullptr) {
    delete pf;
  }
}

// Test FromRE2 with character class
TEST_F(PrefilterTest_545, FromRE2CharClass_545) {
  RE2 re("[abc]def");
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  delete pf;
}

// Test FromRE2 with question mark (optional)
TEST_F(PrefilterTest_545, FromRE2Optional_545) {
  RE2 re("hello?world");
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  delete pf;
}

// Test FromRE2 with plus
TEST_F(PrefilterTest_545, FromRE2Plus_545) {
  RE2 re("hel+o");
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  delete pf;
}

// Test FromRE2 with star
TEST_F(PrefilterTest_545, FromRE2Star_545) {
  RE2 re("hel*o");
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  delete pf;
}

// Test DebugString on FromRE2 result
TEST_F(PrefilterTest_545, DebugStringFromRE2_545) {
  RE2 re("(foo|bar).*baz");
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
  delete pf;
}

// Test FromRE2 with empty pattern
TEST_F(PrefilterTest_545, FromRE2EmptyPattern_545) {
  RE2 re("");
  Prefilter* pf = Prefilter::FromRE2(&re);
  // Empty pattern matches empty string, prefilter could be ALL or NULL
  if (pf != nullptr) {
    delete pf;
  }
}

// Test multiple unique_id set operations
TEST_F(PrefilterTest_545, UniqueIdMultipleSet_545) {
  Prefilter pf(Prefilter::ALL);
  pf.set_unique_id(1);
  EXPECT_EQ(pf.unique_id(), 1);
  pf.set_unique_id(100);
  EXPECT_EQ(pf.unique_id(), 100);
  pf.set_unique_id(999999);
  EXPECT_EQ(pf.unique_id(), 999999);
}

// Test FromRE2 with AND-producing pattern
TEST_F(PrefilterTest_545, FromRE2AndPattern_545) {
  RE2 re("foo.*bar");
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  // foo.*bar should produce AND(foo, bar)
  if (pf->op() == Prefilter::AND) {
    ASSERT_NE(pf->subs(), nullptr);
    EXPECT_GE(pf->subs()->size(), 2u);
  }
  delete pf;
}

// Test FromRE2 with OR-producing pattern - verify subs
TEST_F(PrefilterTest_545, FromRE2OrPatternSubs_545) {
  RE2 re("foo|bar|baz");
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  if (pf->op() == Prefilter::OR) {
    ASSERT_NE(pf->subs(), nullptr);
    EXPECT_GE(pf->subs()->size(), 2u);
  }
  delete pf;
}

// Test FromRE2 with case insensitive pattern
TEST_F(PrefilterTest_545, FromRE2CaseInsensitive_545) {
  RE2 re("(?i)hello");
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    std::string debug = pf->DebugString();
    EXPECT_FALSE(debug.empty());
    delete pf;
  }
}

// Test FromRE2 with word boundary
TEST_F(PrefilterTest_545, FromRE2WithAnchors_545) {
  RE2 re("^hello$");
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  // Anchors don't affect prefilter; should still find "hello"
  EXPECT_EQ(pf->op(), Prefilter::ATOM);
  EXPECT_EQ(pf->atom(), "hello");
  delete pf;
}

// Test construction and destruction (no leak)
TEST_F(PrefilterTest_545, ConstructDestruct_545) {
  Prefilter* pf = new Prefilter(Prefilter::AND);
  std::vector<Prefilter*>* subs = new std::vector<Prefilter*>();
  subs->push_back(new Prefilter(Prefilter::ALL));
  subs->push_back(new Prefilter(Prefilter::ALL));
  pf->set_subs(subs);
  delete pf;
}

// Test op() returns what was passed to constructor
TEST_F(PrefilterTest_545, OpMatchesConstructor_545) {
  Prefilter pf_all(Prefilter::ALL);
  EXPECT_EQ(pf_all.op(), Prefilter::ALL);

  Prefilter pf_none(Prefilter::NONE);
  EXPECT_EQ(pf_none.op(), Prefilter::NONE);

  Prefilter pf_and(Prefilter::AND);
  EXPECT_EQ(pf_and.op(), Prefilter::AND);

  Prefilter pf_or(Prefilter::OR);
  EXPECT_EQ(pf_or.op(), Prefilter::OR);
}

}  // namespace re2
