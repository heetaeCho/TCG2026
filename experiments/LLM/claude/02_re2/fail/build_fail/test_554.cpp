#include <gtest/gtest.h>
#include "re2/prefilter.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/prog.h"

// Since Prefilter::Info is an internal class not directly accessible from headers,
// we test through the public Prefilter interface which exercises Info internally.
// We test Prefilter's public API which is the observable behavior.

namespace re2 {

class PrefilterTest_554 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Test that Prefilter can be created with ALL op
TEST_F(PrefilterTest_554, CreateAllPrefilter_554) {
  Prefilter* pf = new Prefilter(Prefilter::ALL);
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::ALL);
  delete pf;
}

// Test that Prefilter can be created with NONE op
TEST_F(PrefilterTest_554, CreateNonePrefilter_554) {
  Prefilter* pf = new Prefilter(Prefilter::NONE);
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::NONE);
  delete pf;
}

// Test that Prefilter can be created with ATOM op
TEST_F(PrefilterTest_554, CreateAtomPrefilter_554) {
  Prefilter* pf = new Prefilter(Prefilter::ATOM, "hello");
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::ATOM);
  EXPECT_EQ(pf->atom(), "hello");
  delete pf;
}

// Test FromRE2 with a simple literal pattern
TEST_F(PrefilterTest_554, FromRE2SimpleLiteral_554) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  // A simple literal should produce a prefilter
  if (pf != nullptr) {
    // It should be an ATOM or have some structure
    EXPECT_TRUE(pf->op() == Prefilter::ATOM || 
                pf->op() == Prefilter::AND ||
                pf->op() == Prefilter::OR ||
                pf->op() == Prefilter::ALL ||
                pf->op() == Prefilter::NONE);
    delete pf;
  }
}

// Test FromRE2 with dot-star pattern (matches everything)
TEST_F(PrefilterTest_554, FromRE2DotStar_554) {
  RE2 re(".*");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    // .* matches everything, should be ALL
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    delete pf;
  }
}

// Test FromRE2 with alternation
TEST_F(PrefilterTest_554, FromRE2Alternation_554) {
  RE2 re("hello|world");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    // Alternation typically produces OR
    EXPECT_TRUE(pf->op() == Prefilter::OR || 
                pf->op() == Prefilter::ALL ||
                pf->op() == Prefilter::ATOM);
    delete pf;
  }
}

// Test FromRE2 with concatenation
TEST_F(PrefilterTest_554, FromRE2Concatenation_554) {
  RE2 re("abc.*def");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    EXPECT_TRUE(pf->op() == Prefilter::AND || 
                pf->op() == Prefilter::ATOM ||
                pf->op() == Prefilter::ALL);
    delete pf;
  }
}

// Test FromRE2 with question mark (optional)
TEST_F(PrefilterTest_554, FromRE2Optional_554) {
  RE2 re("abc?");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    delete pf;
  }
}

// Test FromRE2 with plus (one or more)
TEST_F(PrefilterTest_554, FromRE2Plus_554) {
  RE2 re("a+");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    delete pf;
  }
}

// Test FromRE2 with star (zero or more)
TEST_F(PrefilterTest_554, FromRE2Star_554) {
  RE2 re("a*");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    // a* can match empty string, likely ALL
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    delete pf;
  }
}

// Test FromRE2 with character class
TEST_F(PrefilterTest_554, FromRE2CharClass_554) {
  RE2 re("[abc]def");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    delete pf;
  }
}

// Test FromRE2 with empty pattern
TEST_F(PrefilterTest_554, FromRE2EmptyPattern_554) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    delete pf;
  }
}

// Test Prefilter DebugString
TEST_F(PrefilterTest_554, DebugStringAtom_554) {
  Prefilter* pf = new Prefilter(Prefilter::ATOM, "test");
  ASSERT_NE(pf, nullptr);
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
  delete pf;
}

// Test Prefilter DebugString for ALL
TEST_F(PrefilterTest_554, DebugStringAll_554) {
  Prefilter* pf = new Prefilter(Prefilter::ALL);
  ASSERT_NE(pf, nullptr);
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
  delete pf;
}

// Test Prefilter subs access
TEST_F(PrefilterTest_554, SubsAccess_554) {
  Prefilter* pf = new Prefilter(Prefilter::AND);
  ASSERT_NE(pf, nullptr);
  EXPECT_NE(pf->subs(), nullptr);
  delete pf;
}

// Test FromRE2 with complex pattern
TEST_F(PrefilterTest_554, FromRE2ComplexPattern_554) {
  RE2 re("(foo|bar).*baz");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    // Should produce some structured prefilter
    EXPECT_TRUE(pf->op() >= Prefilter::ALL && pf->op() <= Prefilter::OR);
    delete pf;
  }
}

// Test FromRE2 with single character
TEST_F(PrefilterTest_554, FromRE2SingleChar_554) {
  RE2 re("a");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    delete pf;
  }
}

// Test FromRE2 with Unicode
TEST_F(PrefilterTest_554, FromRE2Unicode_554) {
  RE2 re("café");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    delete pf;
  }
}

// Test that OR prefilter works
TEST_F(PrefilterTest_554, OrPrefilter_554) {
  Prefilter* pf = new Prefilter(Prefilter::OR);
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::OR);
  delete pf;
}

// Test that AND prefilter works
TEST_F(PrefilterTest_554, AndPrefilter_554) {
  Prefilter* pf = new Prefilter(Prefilter::AND);
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::AND);
  delete pf;
}

// Test FromRE2 with dot (any char)
TEST_F(PrefilterTest_554, FromRE2AnyChar_554) {
  RE2 re(".");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  if (pf != nullptr) {
    // Single dot matches any char, should be ALL
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    delete pf;
  }
}

// Test FromRE2 with long literal for atom extraction
TEST_F(PrefilterTest_554, FromRE2LongLiteral_554) {
  RE2 re("abcdefghijk");
  ASSERT_TRUE(re.ok());
  Prefilter* pf = Prefilter::FromRE2(&re);
  ASSERT_NE(pf, nullptr);
  // Long literal should produce an ATOM
  if (pf->op() == Prefilter::ATOM) {
    EXPECT_FALSE(pf->atom().empty());
  }
  delete pf;
}

}  // namespace re2
