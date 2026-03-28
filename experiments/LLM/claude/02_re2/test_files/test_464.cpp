#include "gtest/gtest.h"
#include "re2/prefilter.h"
#include "re2/re2.h"
#include <vector>
#include <string>

namespace re2 {

// Test fixture for Prefilter tests
class PrefilterTest_464 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Clean up any allocated prefilters
  }
};

// Test constructor with NONE op
TEST_F(PrefilterTest_464, ConstructWithNoneOp_464) {
  Prefilter pf(Prefilter::NONE);
  EXPECT_EQ(pf.op(), Prefilter::NONE);
}

// Test constructor with ALL op
TEST_F(PrefilterTest_464, ConstructWithAllOp_464) {
  Prefilter pf(Prefilter::ALL);
  EXPECT_EQ(pf.op(), Prefilter::ALL);
}

// Test constructor with AND op
TEST_F(PrefilterTest_464, ConstructWithAndOp_464) {
  Prefilter pf(Prefilter::AND);
  EXPECT_EQ(pf.op(), Prefilter::AND);
}

// Test constructor with OR op
TEST_F(PrefilterTest_464, ConstructWithOrOp_464) {
  Prefilter pf(Prefilter::OR);
  EXPECT_EQ(pf.op(), Prefilter::OR);
}

// Test constructor with ATOM op
TEST_F(PrefilterTest_464, ConstructWithAtomOp_464) {
  Prefilter pf(Prefilter::ATOM);
  EXPECT_EQ(pf.op(), Prefilter::ATOM);
}

// Test set_unique_id and unique_id
TEST_F(PrefilterTest_464, SetAndGetUniqueId_464) {
  Prefilter pf(Prefilter::NONE);
  pf.set_unique_id(42);
  EXPECT_EQ(pf.unique_id(), 42);
}

// Test set_unique_id with zero
TEST_F(PrefilterTest_464, SetUniqueIdZero_464) {
  Prefilter pf(Prefilter::NONE);
  pf.set_unique_id(0);
  EXPECT_EQ(pf.unique_id(), 0);
}

// Test set_unique_id with negative value
TEST_F(PrefilterTest_464, SetUniqueIdNegative_464) {
  Prefilter pf(Prefilter::NONE);
  pf.set_unique_id(-1);
  EXPECT_EQ(pf.unique_id(), -1);
}

// Test set_unique_id overwrite
TEST_F(PrefilterTest_464, SetUniqueIdOverwrite_464) {
  Prefilter pf(Prefilter::NONE);
  pf.set_unique_id(10);
  EXPECT_EQ(pf.unique_id(), 10);
  pf.set_unique_id(20);
  EXPECT_EQ(pf.unique_id(), 20);
}

// Test subs accessor
TEST_F(PrefilterTest_464, SubsAccessor_464) {
  Prefilter pf(Prefilter::AND);
  // set_subs with a new vector
  auto* subs = new std::vector<Prefilter*>();
  pf.set_subs(subs);
  EXPECT_EQ(pf.subs(), subs);
  delete subs;
}

// Test set_subs with nullptr
TEST_F(PrefilterTest_464, SetSubsNull_464) {
  Prefilter pf(Prefilter::AND);
  pf.set_subs(nullptr);
  EXPECT_EQ(pf.subs(), nullptr);
}

// Test set_subs with non-empty vector
TEST_F(PrefilterTest_464, SetSubsNonEmpty_464) {
  Prefilter pf(Prefilter::AND);
  auto* subs = new std::vector<Prefilter*>();
  Prefilter* child = new Prefilter(Prefilter::ATOM);
  subs->push_back(child);
  pf.set_subs(subs);
  EXPECT_EQ(pf.subs(), subs);
  EXPECT_EQ(pf.subs()->size(), 1u);
  delete child;
  delete subs;
}

// Test atom accessor on NONE
TEST_F(PrefilterTest_464, AtomOnNone_464) {
  Prefilter pf(Prefilter::NONE);
  // atom should be empty for non-ATOM prefilters
  EXPECT_TRUE(pf.atom().empty());
}

// Test DebugString on NONE
TEST_F(PrefilterTest_464, DebugStringNone_464) {
  Prefilter pf(Prefilter::NONE);
  std::string debug = pf.DebugString();
  EXPECT_FALSE(debug.empty());
}

// Test DebugString on ALL
TEST_F(PrefilterTest_464, DebugStringAll_464) {
  Prefilter pf(Prefilter::ALL);
  std::string debug = pf.DebugString();
  EXPECT_FALSE(debug.empty());
}

// Test FromRE2 with a simple literal pattern
TEST_F(PrefilterTest_464, FromRE2SimpleLiteral_464) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // A simple literal should produce a non-null prefilter
  ASSERT_NE(pf, nullptr);
  // For a simple literal, we expect ATOM op
  EXPECT_EQ(pf->op(), Prefilter::ATOM);
  EXPECT_EQ(pf->atom(), "hello");
  delete pf;
}

// Test FromRE2 with alternation
TEST_F(PrefilterTest_464, FromRE2Alternation_464) {
  RE2 re("hello|world");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  // Alternation should give OR or some structure
  delete pf;
}

// Test FromRE2 with a pattern that matches everything
TEST_F(PrefilterTest_464, FromRE2MatchAll_464) {
  RE2 re(".*");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // .* can match anything, so prefilter might be ALL or nullptr
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    delete pf;
  }
}

// Test FromRE2 with concatenation
TEST_F(PrefilterTest_464, FromRE2Concatenation_464) {
  RE2 re("abc.*def");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  delete pf;
}

// Test FromRE2 with single character
TEST_F(PrefilterTest_464, FromRE2SingleChar_464) {
  RE2 re("a");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // Single character might be ALL since it's too short for a useful prefilter
  if (pf != nullptr) {
    delete pf;
  }
}

// Test FromRE2 with character class
TEST_F(PrefilterTest_464, FromRE2CharClass_464) {
  RE2 re("[abc]def");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    delete pf;
  }
}

// Test FromRE2 with complex pattern
TEST_F(PrefilterTest_464, FromRE2ComplexPattern_464) {
  RE2 re("(foo|bar)baz(qux|quux)");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  delete pf;
}

// Test DebugString for ATOM
TEST_F(PrefilterTest_464, DebugStringAtom_464) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  std::string debug = pf->DebugString();
  // The debug string for an atom should contain the atom text
  EXPECT_NE(debug.find("hello"), std::string::npos);
  delete pf;
}

// Test DebugString for OR
TEST_F(PrefilterTest_464, DebugStringOr_464) {
  RE2 re("hello|world");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
  delete pf;
}

// Test FromRE2 with case-insensitive pattern
TEST_F(PrefilterTest_464, FromRE2CaseInsensitive_464) {
  RE2 re("(?i)hello");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    delete pf;
  }
}

// Test FromRE2 with empty pattern
TEST_F(PrefilterTest_464, FromRE2EmptyPattern_464) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // Empty pattern matches everything
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    delete pf;
  }
}

// Test set_subs replaces pointer
TEST_F(PrefilterTest_464, SetSubsReplacesPointer_464) {
  Prefilter pf(Prefilter::AND);
  auto* subs1 = new std::vector<Prefilter*>();
  auto* subs2 = new std::vector<Prefilter*>();
  pf.set_subs(subs1);
  EXPECT_EQ(pf.subs(), subs1);
  pf.set_subs(subs2);
  EXPECT_EQ(pf.subs(), subs2);
  EXPECT_NE(pf.subs(), subs1);
  delete subs1;
  delete subs2;
}

// Test op accessor consistency after construction
TEST_F(PrefilterTest_464, OpConsistencyAfterConstruction_464) {
  Prefilter pf1(Prefilter::AND);
  Prefilter pf2(Prefilter::OR);
  Prefilter pf3(Prefilter::ATOM);
  EXPECT_EQ(pf1.op(), Prefilter::AND);
  EXPECT_EQ(pf2.op(), Prefilter::OR);
  EXPECT_EQ(pf3.op(), Prefilter::ATOM);
}

// Test FromRE2 with long literal
TEST_F(PrefilterTest_464, FromRE2LongLiteral_464) {
  RE2 re("abcdefghijklmnopqrstuvwxyz");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::ATOM);
  delete pf;
}

// Test FromRE2 with repetition
TEST_F(PrefilterTest_464, FromRE2Repetition_464) {
  RE2 re("ab+cd");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    delete pf;
  }
}

// Test FromRE2 with question mark
TEST_F(PrefilterTest_464, FromRE2QuestionMark_464) {
  RE2 re("ab?cd");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    delete pf;
  }
}

}  // namespace re2
