#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/prefilter.h"

namespace re2 {

class PrefilterTest_563 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Test that FromRE2 with a NULL pointer returns NULL
TEST_F(PrefilterTest_563, FromRE2WithNullReturnsNull_563) {
  Prefilter* result = Prefilter::FromRE2(nullptr);
  EXPECT_EQ(result, nullptr);
}

// Test that FromRE2 with a valid simple literal pattern returns non-null
TEST_F(PrefilterTest_563, FromRE2WithSimpleLiteral_563) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  Prefilter* result = Prefilter::FromRE2(&re);
  EXPECT_NE(result, nullptr);
  if (result) {
    // A simple literal should produce an ATOM
    EXPECT_EQ(result->op(), Prefilter::ATOM);
    delete result;
  }
}

// Test that FromRE2 with a simple alternation pattern returns non-null
TEST_F(PrefilterTest_563, FromRE2WithAlternation_563) {
  RE2 re("hello|world");
  ASSERT_TRUE(re.ok());
  Prefilter* result = Prefilter::FromRE2(&re);
  EXPECT_NE(result, nullptr);
  if (result) {
    delete result;
  }
}

// Test that FromRE2 with a pattern that matches everything (like ".*") 
// may return a special ALL prefilter or NULL
TEST_F(PrefilterTest_563, FromRE2WithMatchAll_563) {
  RE2 re(".*");
  ASSERT_TRUE(re.ok());
  Prefilter* result = Prefilter::FromRE2(&re);
  // ".*" matches everything, so the prefilter might be ALL or NULL
  if (result != nullptr) {
    EXPECT_EQ(result->op(), Prefilter::ALL);
    delete result;
  }
}

// Test that FromRE2 with a concatenation pattern
TEST_F(PrefilterTest_563, FromRE2WithConcatenation_563) {
  RE2 re("abc.*def");
  ASSERT_TRUE(re.ok());
  Prefilter* result = Prefilter::FromRE2(&re);
  EXPECT_NE(result, nullptr);
  if (result) {
    delete result;
  }
}

// Test DebugString on a prefilter from a simple pattern
TEST_F(PrefilterTest_563, DebugStringSimpleLiteral_563) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  Prefilter* result = Prefilter::FromRE2(&re);
  ASSERT_NE(result, nullptr);
  std::string debug = result->DebugString();
  EXPECT_FALSE(debug.empty());
  delete result;
}

// Test unique_id default and set_unique_id
TEST_F(PrefilterTest_563, UniqueIdDefaultAndSet_563) {
  Prefilter pf(Prefilter::ALL);
  // Default unique_id is typically -1 based on common convention
  // but we just test the setter/getter roundtrip
  pf.set_unique_id(42);
  EXPECT_EQ(pf.unique_id(), 42);
}

// Test unique_id with different values
TEST_F(PrefilterTest_563, UniqueIdMultipleValues_563) {
  Prefilter pf(Prefilter::NONE);
  pf.set_unique_id(0);
  EXPECT_EQ(pf.unique_id(), 0);
  pf.set_unique_id(-1);
  EXPECT_EQ(pf.unique_id(), -1);
  pf.set_unique_id(999);
  EXPECT_EQ(pf.unique_id(), 999);
}

// Test op() returns what was set in constructor
TEST_F(PrefilterTest_563, OpReturnsConstructedOp_563) {
  Prefilter pf_all(Prefilter::ALL);
  EXPECT_EQ(pf_all.op(), Prefilter::ALL);

  Prefilter pf_none(Prefilter::NONE);
  EXPECT_EQ(pf_none.op(), Prefilter::NONE);

  Prefilter pf_atom(Prefilter::ATOM);
  EXPECT_EQ(pf_atom.op(), Prefilter::ATOM);

  Prefilter pf_and(Prefilter::AND);
  EXPECT_EQ(pf_and.op(), Prefilter::AND);

  Prefilter pf_or(Prefilter::OR);
  EXPECT_EQ(pf_or.op(), Prefilter::OR);
}

// Test atom() on an ATOM prefilter created from a literal pattern
TEST_F(PrefilterTest_563, AtomFromLiteralPattern_563) {
  RE2 re("teststring");
  ASSERT_TRUE(re.ok());
  Prefilter* result = Prefilter::FromRE2(&re);
  ASSERT_NE(result, nullptr);
  if (result->op() == Prefilter::ATOM) {
    EXPECT_FALSE(result->atom().empty());
  }
  delete result;
}

// Test subs() on an AND/OR prefilter created from alternation
TEST_F(PrefilterTest_563, SubsFromAlternation_563) {
  RE2 re("alpha|beta|gamma");
  ASSERT_TRUE(re.ok());
  Prefilter* result = Prefilter::FromRE2(&re);
  ASSERT_NE(result, nullptr);
  if (result->op() == Prefilter::OR || result->op() == Prefilter::AND) {
    EXPECT_NE(result->subs(), nullptr);
    EXPECT_GT(result->subs()->size(), 0u);
  }
  delete result;
}

// Test set_subs
TEST_F(PrefilterTest_563, SetSubs_563) {
  Prefilter pf(Prefilter::AND);
  auto* subs = new std::vector<Prefilter*>();
  subs->push_back(new Prefilter(Prefilter::ALL));
  pf.set_subs(subs);
  EXPECT_EQ(pf.subs(), subs);
  // Destructor should handle cleanup
}

// Test FromRE2 with a single character pattern
TEST_F(PrefilterTest_563, FromRE2SingleChar_563) {
  RE2 re("a");
  ASSERT_TRUE(re.ok());
  Prefilter* result = Prefilter::FromRE2(&re);
  // Single character might be too short for a meaningful prefilter atom
  // Result could be ALL or an ATOM
  if (result != nullptr) {
    delete result;
  }
}

// Test FromRE2 with empty pattern
TEST_F(PrefilterTest_563, FromRE2EmptyPattern_563) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  Prefilter* result = Prefilter::FromRE2(&re);
  // Empty pattern matches empty string; prefilter may be ALL or NULL
  if (result != nullptr) {
    delete result;
  }
}

// Test FromRE2 with character class
TEST_F(PrefilterTest_563, FromRE2CharClass_563) {
  RE2 re("[a-z]+foo");
  ASSERT_TRUE(re.ok());
  Prefilter* result = Prefilter::FromRE2(&re);
  EXPECT_NE(result, nullptr);
  if (result) {
    delete result;
  }
}

// Test FromRE2 with a complex regex
TEST_F(PrefilterTest_563, FromRE2ComplexRegex_563) {
  RE2 re("(abc|def).*ghi(jkl|mno)");
  ASSERT_TRUE(re.ok());
  Prefilter* result = Prefilter::FromRE2(&re);
  EXPECT_NE(result, nullptr);
  if (result) {
    std::string debug = result->DebugString();
    EXPECT_FALSE(debug.empty());
    delete result;
  }
}

// Test FromRE2 with optional/repetition patterns
TEST_F(PrefilterTest_563, FromRE2WithRepetition_563) {
  RE2 re("hello?world+");
  ASSERT_TRUE(re.ok());
  Prefilter* result = Prefilter::FromRE2(&re);
  if (result != nullptr) {
    delete result;
  }
}

// Test FromRE2 with case-insensitive pattern
TEST_F(PrefilterTest_563, FromRE2CaseInsensitive_563) {
  RE2 re("(?i)hello");
  ASSERT_TRUE(re.ok());
  Prefilter* result = Prefilter::FromRE2(&re);
  if (result != nullptr) {
    delete result;
  }
}

// Test DebugString on ALL prefilter
TEST_F(PrefilterTest_563, DebugStringALL_563) {
  Prefilter pf(Prefilter::ALL);
  std::string debug = pf.DebugString();
  EXPECT_FALSE(debug.empty());
}

// Test DebugString on NONE prefilter
TEST_F(PrefilterTest_563, DebugStringNONE_563) {
  Prefilter pf(Prefilter::NONE);
  std::string debug = pf.DebugString();
  EXPECT_FALSE(debug.empty());
}

// Test FromRE2 with an invalid RE2 pattern
TEST_F(PrefilterTest_563, FromRE2WithInvalidPattern_563) {
  RE2 re("(unclosed");
  // If pattern is invalid, RE2 may still construct but with error
  if (!re.ok()) {
    // Regexp() likely returns NULL for invalid pattern
    Prefilter* result = Prefilter::FromRE2(&re);
    EXPECT_EQ(result, nullptr);
  }
}

// Test FromRE2 with anchored pattern
TEST_F(PrefilterTest_563, FromRE2AnchoredPattern_563) {
  RE2 re("^hello$");
  ASSERT_TRUE(re.ok());
  Prefilter* result = Prefilter::FromRE2(&re);
  if (result != nullptr) {
    delete result;
  }
}

// Test FromRE2 with a long literal string
TEST_F(PrefilterTest_563, FromRE2LongLiteral_563) {
  RE2 re("thisisaverylongliteralstringforprefiltertest");
  ASSERT_TRUE(re.ok());
  Prefilter* result = Prefilter::FromRE2(&re);
  EXPECT_NE(result, nullptr);
  if (result) {
    EXPECT_EQ(result->op(), Prefilter::ATOM);
    delete result;
  }
}

}  // namespace re2
