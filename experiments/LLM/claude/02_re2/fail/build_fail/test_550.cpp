#include "gtest/gtest.h"
#include "re2/prefilter.h"
#include "util/utf.h"
#include <string>

// We need access to the RuneToString function. Since it's declared static in the .cc file,
// we cannot directly test it from outside. However, we can test it indirectly through
// the Prefilter public interface, or we need to find a way to access it.
// 
// Since RuneToString is a static function in prefilter.cc, it's not directly accessible.
// We'll test the Prefilter class's public interface instead, which uses RuneToString internally.

namespace re2 {

// Test Prefilter creation and basic operations through the public API
class PrefilterTest_550 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that a Prefilter can be created with NONE op
TEST_F(PrefilterTest_550, CreateNonePrefilter_550) {
  Prefilter* pf = new Prefilter(Prefilter::NONE);
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::NONE);
  delete pf;
}

// Test that a Prefilter can be created with ALL op
TEST_F(PrefilterTest_550, CreateAllPrefilter_550) {
  Prefilter* pf = new Prefilter(Prefilter::ALL);
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::ALL);
  delete pf;
}

// Test that a Prefilter can be created with ATOM op
TEST_F(PrefilterTest_550, CreateAtomPrefilter_550) {
  Prefilter* pf = new Prefilter(Prefilter::ATOM);
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::ATOM);
  delete pf;
}

// Test that a Prefilter can be created with AND op
TEST_F(PrefilterTest_550, CreateAndPrefilter_550) {
  Prefilter* pf = new Prefilter(Prefilter::AND);
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::AND);
  delete pf;
}

// Test that a Prefilter can be created with OR op
TEST_F(PrefilterTest_550, CreateOrPrefilter_550) {
  Prefilter* pf = new Prefilter(Prefilter::OR);
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::OR);
  delete pf;
}

// Test setting and getting the atom value
TEST_F(PrefilterTest_550, SetAtom_550) {
  Prefilter* pf = new Prefilter(Prefilter::ATOM);
  pf->set_atom("hello");
  EXPECT_EQ(pf->atom(), "hello");
  delete pf;
}

// Test atom with empty string
TEST_F(PrefilterTest_550, SetAtomEmpty_550) {
  Prefilter* pf = new Prefilter(Prefilter::ATOM);
  pf->set_atom("");
  EXPECT_EQ(pf->atom(), "");
  delete pf;
}

// Test FromRE2 with a simple literal pattern
TEST_F(PrefilterTest_550, FromRE2SimpleLiteral_550) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // A simple literal should produce a non-null prefilter
  if (pf != nullptr) {
    // The prefilter should be an ATOM with the literal string
    EXPECT_EQ(pf->op(), Prefilter::ATOM);
    EXPECT_EQ(pf->atom(), "hello");
    delete pf;
  }
}

// Test FromRE2 with a dot-star pattern (matches everything)
TEST_F(PrefilterTest_550, FromRE2DotStar_550) {
  RE2 re(".*");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // .* matches everything, so prefilter should be ALL or nullptr
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    delete pf;
  }
}

// Test FromRE2 with alternation
TEST_F(PrefilterTest_550, FromRE2Alternation_550) {
  RE2 re("hello|world");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    // Alternation should produce an OR prefilter
    EXPECT_EQ(pf->op(), Prefilter::OR);
    delete pf;
  }
}

// Test FromRE2 with concatenation containing mandatory literals
TEST_F(PrefilterTest_550, FromRE2Concatenation_550) {
  RE2 re("abc.*def");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    // Should produce some form of AND or ATOM
    EXPECT_TRUE(pf->op() == Prefilter::AND || 
                pf->op() == Prefilter::ATOM ||
                pf->op() == Prefilter::ALL);
    delete pf;
  }
}

// Test FromRE2 with single character
TEST_F(PrefilterTest_550, FromRE2SingleChar_550) {
  RE2 re("a");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ATOM);
    EXPECT_EQ(pf->atom(), "a");
    delete pf;
  }
}

// Test FromRE2 with case-insensitive pattern
TEST_F(PrefilterTest_550, FromRE2CaseInsensitive_550) {
  RE2 re("(?i)hello");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // Should still produce a valid prefilter
  if (pf != nullptr) {
    EXPECT_TRUE(pf->op() == Prefilter::ATOM || 
                pf->op() == Prefilter::OR ||
                pf->op() == Prefilter::AND ||
                pf->op() == Prefilter::ALL);
    delete pf;
  }
}

// Test FromRE2 with character class
TEST_F(PrefilterTest_550, FromRE2CharClass_550) {
  RE2 re("[abc]def");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    EXPECT_TRUE(pf->op() == Prefilter::ATOM || 
                pf->op() == Prefilter::OR ||
                pf->op() == Prefilter::AND ||
                pf->op() == Prefilter::ALL);
    delete pf;
  }
}

// Test FromRE2 with empty pattern
TEST_F(PrefilterTest_550, FromRE2EmptyPattern_550) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // Empty pattern matches everything
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    delete pf;
  }
}

// Test DebugString for ATOM
TEST_F(PrefilterTest_550, DebugStringAtom_550) {
  Prefilter* pf = new Prefilter(Prefilter::ATOM);
  pf->set_atom("test");
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
  // The debug string should contain the atom
  EXPECT_NE(debug.find("test"), std::string::npos);
  delete pf;
}

// Test DebugString for ALL
TEST_F(PrefilterTest_550, DebugStringAll_550) {
  Prefilter* pf = new Prefilter(Prefilter::ALL);
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
  delete pf;
}

// Test DebugString for NONE
TEST_F(PrefilterTest_550, DebugStringNone_550) {
  Prefilter* pf = new Prefilter(Prefilter::NONE);
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
  delete pf;
}

// Test subs accessor
TEST_F(PrefilterTest_550, SubsAccessor_550) {
  Prefilter* pf = new Prefilter(Prefilter::AND);
  ASSERT_NE(pf->subs(), nullptr);
  EXPECT_TRUE(pf->subs()->empty());
  delete pf;
}

// Test unique_id functionality
TEST_F(PrefilterTest_550, UniqueId_550) {
  Prefilter* pf = new Prefilter(Prefilter::ATOM);
  pf->set_unique_id(42);
  EXPECT_EQ(pf->unique_id(), 42);
  delete pf;
}

// Test unique_id with zero
TEST_F(PrefilterTest_550, UniqueIdZero_550) {
  Prefilter* pf = new Prefilter(Prefilter::ATOM);
  pf->set_unique_id(0);
  EXPECT_EQ(pf->unique_id(), 0);
  delete pf;
}

// Test unique_id with negative value
TEST_F(PrefilterTest_550, UniqueIdNegative_550) {
  Prefilter* pf = new Prefilter(Prefilter::ATOM);
  pf->set_unique_id(-1);
  EXPECT_EQ(pf->unique_id(), -1);
  delete pf;
}

// Test FromRE2 with Unicode pattern
TEST_F(PrefilterTest_550, FromRE2Unicode_550) {
  RE2 re("café");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    EXPECT_TRUE(pf->op() == Prefilter::ATOM ||
                pf->op() == Prefilter::AND ||
                pf->op() == Prefilter::OR ||
                pf->op() == Prefilter::ALL);
    delete pf;
  }
}

// Test FromRE2 with complex regex
TEST_F(PrefilterTest_550, FromRE2ComplexRegex_550) {
  RE2 re("(foo|bar)baz[0-9]+");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    EXPECT_TRUE(pf->op() == Prefilter::ATOM ||
                pf->op() == Prefilter::AND ||
                pf->op() == Prefilter::OR ||
                pf->op() == Prefilter::ALL);
    delete pf;
  }
}

// Test FromRE2 with plus quantifier
TEST_F(PrefilterTest_550, FromRE2PlusQuantifier_550) {
  RE2 re("a+b");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    EXPECT_TRUE(pf->op() == Prefilter::ATOM ||
                pf->op() == Prefilter::AND ||
                pf->op() == Prefilter::OR ||
                pf->op() == Prefilter::ALL);
    delete pf;
  }
}

// Test FromRE2 with question mark quantifier
TEST_F(PrefilterTest_550, FromRE2QuestionQuantifier_550) {
  RE2 re("ab?c");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    EXPECT_TRUE(pf->op() == Prefilter::ATOM ||
                pf->op() == Prefilter::AND ||
                pf->op() == Prefilter::OR ||
                pf->op() == Prefilter::ALL);
    delete pf;
  }
}

// Test op values are distinct
TEST_F(PrefilterTest_550, OpValuesDistinct_550) {
  EXPECT_NE(Prefilter::ALL, Prefilter::NONE);
  EXPECT_NE(Prefilter::ALL, Prefilter::ATOM);
  EXPECT_NE(Prefilter::ALL, Prefilter::AND);
  EXPECT_NE(Prefilter::ALL, Prefilter::OR);
  EXPECT_NE(Prefilter::NONE, Prefilter::ATOM);
  EXPECT_NE(Prefilter::AND, Prefilter::OR);
}

}  // namespace re2
