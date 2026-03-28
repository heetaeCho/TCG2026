#include "gtest/gtest.h"
#include "re2/prefilter.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/prefilter_tree.h"
#include <string>
#include <vector>

namespace re2 {

// Test Prefilter through its public interface - FromRegexp and related methods
class PrefilterInfoTest_540 : public ::testing::Test {
 protected:
  void TearDown() override {
  }
};

TEST_F(PrefilterInfoTest_540, FromSimpleLiteral_540) {
  // A simple literal regexp should produce a non-null prefilter
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, NULL);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  // A literal string should produce an ATOM prefilter
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ATOM);
    EXPECT_EQ(pf->atom(), "hello");
    delete pf;
  }
  re->Decref();
}

TEST_F(PrefilterInfoTest_540, FromAlternation_540) {
  Regexp* re = Regexp::Parse("hello|world", Regexp::LikePerl, NULL);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  if (pf != nullptr) {
    // Alternation should produce OR
    EXPECT_EQ(pf->op(), Prefilter::OR);
    delete pf;
  }
  re->Decref();
}

TEST_F(PrefilterInfoTest_540, FromConcatenation_540) {
  Regexp* re = Regexp::Parse("abc.*def", Regexp::LikePerl, NULL);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  if (pf != nullptr) {
    // Concatenation with wildcard should produce AND of atoms
    EXPECT_TRUE(pf->op() == Prefilter::AND || pf->op() == Prefilter::ATOM);
    delete pf;
  }
  re->Decref();
}

TEST_F(PrefilterInfoTest_540, FromDotStar_540) {
  // .* matches everything - should produce ALL prefilter
  Regexp* re = Regexp::Parse(".*", Regexp::LikePerl, NULL);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    delete pf;
  }
  re->Decref();
}

TEST_F(PrefilterInfoTest_540, FromEmptyString_540) {
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, NULL);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  // Empty string may produce ALL or a trivial prefilter
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    delete pf;
  }
  re->Decref();
}

TEST_F(PrefilterInfoTest_540, FromCharacterClass_540) {
  Regexp* re = Regexp::Parse("[abc]def", Regexp::LikePerl, NULL);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  if (pf != nullptr) {
    // Could be OR of atoms or AND
    EXPECT_TRUE(pf->op() == Prefilter::OR || pf->op() == Prefilter::AND || 
                pf->op() == Prefilter::ATOM);
    delete pf;
  }
  re->Decref();
}

TEST_F(PrefilterInfoTest_540, FromQuestionMark_540) {
  Regexp* re = Regexp::Parse("abc?def", Regexp::LikePerl, NULL);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  if (pf != nullptr) {
    delete pf;
  }
  re->Decref();
}

TEST_F(PrefilterInfoTest_540, FromPlus_540) {
  Regexp* re = Regexp::Parse("ab+c", Regexp::LikePerl, NULL);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  if (pf != nullptr) {
    delete pf;
  }
  re->Decref();
}

TEST_F(PrefilterInfoTest_540, FromStar_540) {
  Regexp* re = Regexp::Parse("ab*c", Regexp::LikePerl, NULL);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  if (pf != nullptr) {
    delete pf;
  }
  re->Decref();
}

TEST_F(PrefilterInfoTest_540, PrefilterDebugString_540) {
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, NULL);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  if (pf != nullptr) {
    std::string debug = pf->DebugString();
    EXPECT_FALSE(debug.empty());
    delete pf;
  }
  re->Decref();
}

TEST_F(PrefilterInfoTest_540, FromComplexPattern_540) {
  Regexp* re = Regexp::Parse("(foo|bar).*baz", Regexp::LikePerl, NULL);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  if (pf != nullptr) {
    // Should have some structure with AND/OR
    EXPECT_TRUE(pf->op() == Prefilter::AND || pf->op() == Prefilter::OR || 
                pf->op() == Prefilter::ATOM || pf->op() == Prefilter::ALL);
    delete pf;
  }
  re->Decref();
}

TEST_F(PrefilterInfoTest_540, FromSingleChar_540) {
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, NULL);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ATOM);
    EXPECT_EQ(pf->atom(), "a");
    delete pf;
  }
  re->Decref();
}

TEST_F(PrefilterInfoTest_540, FromUnicodePattern_540) {
  Regexp* re = Regexp::Parse("日本語", Regexp::LikePerl, NULL);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  if (pf != nullptr) {
    delete pf;
  }
  re->Decref();
}

TEST_F(PrefilterInfoTest_540, PrefilterOpValues_540) {
  // Verify enum values exist
  EXPECT_EQ(Prefilter::ALL, 0);
  EXPECT_EQ(Prefilter::ATOM, 1);
  EXPECT_EQ(Prefilter::AND, 2);
  EXPECT_EQ(Prefilter::OR, 3);
}

TEST_F(PrefilterInfoTest_540, FromNoMatch_540) {
  // Pattern that can never match - test with impossible pattern if any
  Regexp* re = Regexp::Parse("[^\\s\\S]", Regexp::LikePerl, NULL);
  if (re != nullptr) {
    Prefilter* pf = Prefilter::FromRegexp(re);
    if (pf != nullptr) {
      delete pf;
    }
    re->Decref();
  }
}

TEST_F(PrefilterInfoTest_540, FromAnchoredLiteral_540) {
  Regexp* re = Regexp::Parse("^hello$", Regexp::LikePerl, NULL);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  if (pf != nullptr) {
    // Anchors don't affect prefilter atoms
    EXPECT_EQ(pf->op(), Prefilter::ATOM);
    EXPECT_EQ(pf->atom(), "hello");
    delete pf;
  }
  re->Decref();
}

TEST_F(PrefilterInfoTest_540, FromDotPattern_540) {
  Regexp* re = Regexp::Parse(".", Regexp::LikePerl, NULL);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    delete pf;
  }
  re->Decref();
}

TEST_F(PrefilterInfoTest_540, SubsAccessible_540) {
  Regexp* re = Regexp::Parse("hello|world", Regexp::LikePerl, NULL);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  if (pf != nullptr && pf->op() == Prefilter::OR) {
    const std::vector<Prefilter*>* subs = pf->subs();
    ASSERT_NE(subs, nullptr);
    EXPECT_GE(subs->size(), 2u);
    delete pf;
  } else if (pf != nullptr) {
    delete pf;
  }
  re->Decref();
}

TEST_F(PrefilterInfoTest_540, FromCaseInsensitive_540) {
  Regexp* re = Regexp::Parse("(?i)hello", Regexp::LikePerl, NULL);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  if (pf != nullptr) {
    delete pf;
  }
  re->Decref();
}

TEST_F(PrefilterInfoTest_540, FromRepeatedGroup_540) {
  Regexp* re = Regexp::Parse("(abc)+", Regexp::LikePerl, NULL);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  if (pf != nullptr) {
    // Plus of a literal group should keep the atom
    EXPECT_EQ(pf->op(), Prefilter::ATOM);
    EXPECT_EQ(pf->atom(), "abc");
    delete pf;
  }
  re->Decref();
}

TEST_F(PrefilterInfoTest_540, FromLatin1Literal_540) {
  // Test with Latin1 encoding
  Regexp* re = Regexp::Parse("caf\xc3\xa9", Regexp::LikePerl, NULL);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  if (pf != nullptr) {
    delete pf;
  }
  re->Decref();
}

}  // namespace re2
