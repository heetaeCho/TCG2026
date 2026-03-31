#include "gtest/gtest.h"
#include "re2/prefilter.h"
#include "re2/re2.h"

namespace re2 {

// Test fixture for Prefilter tests
class PrefilterTest_461 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Test constructing a Prefilter with NONE op
TEST_F(PrefilterTest_461, ConstructWithNONE_461) {
  Prefilter pf(Prefilter::NONE);
  EXPECT_EQ(pf.op(), Prefilter::NONE);
}

// Test constructing a Prefilter with AND op
TEST_F(PrefilterTest_461, ConstructWithAND_461) {
  Prefilter pf(Prefilter::AND);
  EXPECT_EQ(pf.op(), Prefilter::AND);
}

// Test constructing a Prefilter with OR op
TEST_F(PrefilterTest_461, ConstructWithOR_461) {
  Prefilter pf(Prefilter::OR);
  EXPECT_EQ(pf.op(), Prefilter::OR);
}

// Test constructing a Prefilter with ATOM op
TEST_F(PrefilterTest_461, ConstructWithATOM_461) {
  Prefilter pf(Prefilter::ATOM);
  EXPECT_EQ(pf.op(), Prefilter::ATOM);
}

// Test constructing a Prefilter with ALL op
TEST_F(PrefilterTest_461, ConstructWithALL_461) {
  Prefilter pf(Prefilter::ALL);
  EXPECT_EQ(pf.op(), Prefilter::ALL);
}

// Test set_unique_id and unique_id
TEST_F(PrefilterTest_461, SetAndGetUniqueId_461) {
  Prefilter pf(Prefilter::NONE);
  pf.set_unique_id(42);
  EXPECT_EQ(pf.unique_id(), 42);
}

// Test set_unique_id with zero
TEST_F(PrefilterTest_461, SetUniqueIdZero_461) {
  Prefilter pf(Prefilter::NONE);
  pf.set_unique_id(0);
  EXPECT_EQ(pf.unique_id(), 0);
}

// Test set_unique_id with negative value
TEST_F(PrefilterTest_461, SetUniqueIdNegative_461) {
  Prefilter pf(Prefilter::NONE);
  pf.set_unique_id(-1);
  EXPECT_EQ(pf.unique_id(), -1);
}

// Test set_unique_id overwrite
TEST_F(PrefilterTest_461, SetUniqueIdOverwrite_461) {
  Prefilter pf(Prefilter::NONE);
  pf.set_unique_id(10);
  EXPECT_EQ(pf.unique_id(), 10);
  pf.set_unique_id(20);
  EXPECT_EQ(pf.unique_id(), 20);
}

// Test atom() returns empty string for non-ATOM prefilter
TEST_F(PrefilterTest_461, AtomEmptyForNonAtom_461) {
  Prefilter pf(Prefilter::NONE);
  EXPECT_TRUE(pf.atom().empty());
}

// Test subs() for a freshly constructed prefilter
TEST_F(PrefilterTest_461, SubsInitialState_461) {
  Prefilter pf(Prefilter::AND);
  // subs may or may not be null depending on implementation, but we can call it
  // For AND/OR ops without children, subs could be null or empty
  auto* subs = pf.subs();
  if (subs != nullptr) {
    EXPECT_TRUE(subs->empty());
  }
}

// Test set_subs
TEST_F(PrefilterTest_461, SetSubs_461) {
  Prefilter pf(Prefilter::AND);
  auto* new_subs = new std::vector<Prefilter*>();
  new_subs->push_back(new Prefilter(Prefilter::NONE));
  pf.set_subs(new_subs);
  EXPECT_EQ(pf.subs(), new_subs);
  EXPECT_EQ(pf.subs()->size(), 1u);
}

// Test DebugString for NONE op
TEST_F(PrefilterTest_461, DebugStringNone_461) {
  Prefilter pf(Prefilter::NONE);
  std::string debug = pf.DebugString();
  // DebugString should return some non-empty representation
  EXPECT_FALSE(debug.empty());
}

// Test DebugString for ALL op
TEST_F(PrefilterTest_461, DebugStringAll_461) {
  Prefilter pf(Prefilter::ALL);
  std::string debug = pf.DebugString();
  EXPECT_FALSE(debug.empty());
}

// Test FromRE2 with a simple literal regex
TEST_F(PrefilterTest_461, FromRE2SimpleLiteral_461) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // For a simple literal, FromRE2 should return a non-null prefilter
  if (pf != nullptr) {
    // For a literal string, we expect ATOM op
    EXPECT_EQ(pf->op(), Prefilter::ATOM);
    EXPECT_EQ(pf->atom(), "hello");
    delete pf;
  }
}

// Test FromRE2 with alternation
TEST_F(PrefilterTest_461, FromRE2Alternation_461) {
  RE2 re("hello|world");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    // Alternation could produce OR
    // We just verify it's valid
    EXPECT_TRUE(pf->op() == Prefilter::OR || pf->op() == Prefilter::ATOM ||
                pf->op() == Prefilter::ALL || pf->op() == Prefilter::NONE);
    delete pf;
  }
}

// Test FromRE2 with dot star (matches everything)
TEST_F(PrefilterTest_461, FromRE2DotStar_461) {
  RE2 re(".*");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // .* matches everything, so prefilter might be ALL or null
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    delete pf;
  }
}

// Test FromRE2 with concatenation
TEST_F(PrefilterTest_461, FromRE2Concatenation_461) {
  RE2 re("abc.*def");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    // Should have some meaningful prefilter
    std::string debug = pf->DebugString();
    EXPECT_FALSE(debug.empty());
    delete pf;
  }
}

// Test FromRE2 with character class
TEST_F(PrefilterTest_461, FromRE2CharClass_461) {
  RE2 re("[abc]def");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    std::string debug = pf->DebugString();
    EXPECT_FALSE(debug.empty());
    delete pf;
  }
}

// Test FromRE2 with a case-insensitive regex
TEST_F(PrefilterTest_461, FromRE2CaseInsensitive_461) {
  RE2 re("(?i)hello");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    std::string debug = pf->DebugString();
    EXPECT_FALSE(debug.empty());
    delete pf;
  }
}

// Test FromRE2 with empty pattern
TEST_F(PrefilterTest_461, FromRE2EmptyPattern_461) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // Empty pattern matches everything
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    delete pf;
  }
}

// Test FromRE2 with plus operator
TEST_F(PrefilterTest_461, FromRE2PlusOperator_461) {
  RE2 re("abc+");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    // abc+ requires at least "abc", so prefilter should capture "abc"
    std::string debug = pf->DebugString();
    EXPECT_FALSE(debug.empty());
    delete pf;
  }
}

// Test FromRE2 with question mark (optional)
TEST_F(PrefilterTest_461, FromRE2QuestionMark_461) {
  RE2 re("abc?def");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    std::string debug = pf->DebugString();
    EXPECT_FALSE(debug.empty());
    delete pf;
  }
}

// Test unique_id with large value
TEST_F(PrefilterTest_461, SetUniqueIdLargeValue_461) {
  Prefilter pf(Prefilter::NONE);
  pf.set_unique_id(2147483647);  // INT_MAX
  EXPECT_EQ(pf.unique_id(), 2147483647);
}

// Test DebugString for ATOM
TEST_F(PrefilterTest_461, DebugStringFromRE2Literal_461) {
  RE2 re("test");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    std::string debug = pf->DebugString();
    // For a literal, debug string should contain the atom
    EXPECT_NE(debug.find("test"), std::string::npos);
    delete pf;
  }
}

// Test set_subs with nullptr
TEST_F(PrefilterTest_461, SetSubsNullptr_461) {
  Prefilter pf(Prefilter::AND);
  pf.set_subs(nullptr);
  EXPECT_EQ(pf.subs(), nullptr);
}

// Test set_subs with empty vector
TEST_F(PrefilterTest_461, SetSubsEmptyVector_461) {
  Prefilter pf(Prefilter::OR);
  auto* empty_subs = new std::vector<Prefilter*>();
  pf.set_subs(empty_subs);
  EXPECT_EQ(pf.subs(), empty_subs);
  EXPECT_TRUE(pf.subs()->empty());
}

// Test FromRE2 with complex regex
TEST_F(PrefilterTest_461, FromRE2ComplexRegex_461) {
  RE2 re("(foo|bar)baz[0-9]+");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    std::string debug = pf->DebugString();
    EXPECT_FALSE(debug.empty());
    delete pf;
  }
}

// Test FromRE2 with single character
TEST_F(PrefilterTest_461, FromRE2SingleChar_461) {
  RE2 re("a");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // Single char might not produce a useful prefilter (too short for atom)
  if (pf != nullptr) {
    delete pf;
  }
}

}  // namespace re2
