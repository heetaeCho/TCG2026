#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include "re2/prog.h"
#include "re2/testing/exhaustive_tester.h"
#include <string>

namespace re2 {

// Helper to create a CharClass via parsing a regexp character class
// We use the Regexp parser to create CharClass objects since the constructor is private.

class CharClassTest_148 : public ::testing::Test {
 protected:
  // Helper: parse a pattern and extract the CharClass from the resulting Regexp.
  // Returns nullptr if extraction fails.
  // The caller does NOT own the CharClass - it's owned by the Regexp.
  struct ParsedCC {
    Regexp* re;
    CharClass* cc;
  };

  ParsedCC ParseCharClass(const std::string& pattern) {
    ParsedCC result = {nullptr, nullptr};
    RegexpStatus status;
    result.re = Regexp::Parse(pattern, Regexp::ClassNL | Regexp::PerlX, &status);
    if (result.re != nullptr && result.re->op() == kRegexpCharClass) {
      result.cc = result.re->cc();
    }
    return result;
  }

  void TearDown() override {
    for (auto* re : to_decref_) {
      if (re) re->Decref();
    }
  }

  void TrackRegexp(Regexp* re) {
    if (re) to_decref_.push_back(re);
  }

  std::vector<Regexp*> to_decref_;
};

TEST_F(CharClassTest_148, ContainsMatchingRune_148) {
  auto parsed = ParseCharClass("[a-z]");
  TrackRegexp(parsed.re);
  ASSERT_NE(parsed.cc, nullptr);
  EXPECT_TRUE(parsed.cc->Contains('a'));
  EXPECT_TRUE(parsed.cc->Contains('m'));
  EXPECT_TRUE(parsed.cc->Contains('z'));
}

TEST_F(CharClassTest_148, ContainsNonMatchingRune_148) {
  auto parsed = ParseCharClass("[a-z]");
  TrackRegexp(parsed.re);
  ASSERT_NE(parsed.cc, nullptr);
  EXPECT_FALSE(parsed.cc->Contains('A'));
  EXPECT_FALSE(parsed.cc->Contains('0'));
  EXPECT_FALSE(parsed.cc->Contains('Z'));
}

TEST_F(CharClassTest_148, SingleCharContains_148) {
  auto parsed = ParseCharClass("[x]");
  TrackRegexp(parsed.re);
  ASSERT_NE(parsed.cc, nullptr);
  EXPECT_TRUE(parsed.cc->Contains('x'));
  EXPECT_FALSE(parsed.cc->Contains('y'));
  EXPECT_FALSE(parsed.cc->Contains('w'));
}

TEST_F(CharClassTest_148, DigitClass_148) {
  auto parsed = ParseCharClass("[0-9]");
  TrackRegexp(parsed.re);
  ASSERT_NE(parsed.cc, nullptr);
  EXPECT_TRUE(parsed.cc->Contains('0'));
  EXPECT_TRUE(parsed.cc->Contains('5'));
  EXPECT_TRUE(parsed.cc->Contains('9'));
  EXPECT_FALSE(parsed.cc->Contains('a'));
}

TEST_F(CharClassTest_148, MultiRangeContains_148) {
  auto parsed = ParseCharClass("[a-zA-Z0-9]");
  TrackRegexp(parsed.re);
  ASSERT_NE(parsed.cc, nullptr);
  EXPECT_TRUE(parsed.cc->Contains('a'));
  EXPECT_TRUE(parsed.cc->Contains('Z'));
  EXPECT_TRUE(parsed.cc->Contains('5'));
  EXPECT_FALSE(parsed.cc->Contains('!'));
  EXPECT_FALSE(parsed.cc->Contains(' '));
}

TEST_F(CharClassTest_148, SizeNonEmpty_148) {
  auto parsed = ParseCharClass("[a-z]");
  TrackRegexp(parsed.re);
  ASSERT_NE(parsed.cc, nullptr);
  EXPECT_EQ(parsed.cc->size(), 26);
}

TEST_F(CharClassTest_148, SizeSingleChar_148) {
  auto parsed = ParseCharClass("[x]");
  TrackRegexp(parsed.re);
  ASSERT_NE(parsed.cc, nullptr);
  EXPECT_EQ(parsed.cc->size(), 1);
}

TEST_F(CharClassTest_148, EmptyIsFalseForNonEmpty_148) {
  auto parsed = ParseCharClass("[a-z]");
  TrackRegexp(parsed.re);
  ASSERT_NE(parsed.cc, nullptr);
  EXPECT_FALSE(parsed.cc->empty());
}

TEST_F(CharClassTest_148, FullForDot_148) {
  // [^\n] is not full, but [\x00-\x{10ffff}] would be.
  // Let's test that a-z is not full.
  auto parsed = ParseCharClass("[a-z]");
  TrackRegexp(parsed.re);
  ASSERT_NE(parsed.cc, nullptr);
  EXPECT_FALSE(parsed.cc->full());
}

TEST_F(CharClassTest_148, BeginEndIteration_148) {
  auto parsed = ParseCharClass("[a-cf-h]");
  TrackRegexp(parsed.re);
  ASSERT_NE(parsed.cc, nullptr);
  int count = 0;
  for (auto it = parsed.cc->begin(); it != parsed.cc->end(); ++it) {
    count += it->hi - it->lo + 1;
  }
  // a-c = 3, f-h = 3 => 6
  EXPECT_EQ(count, 6);
  EXPECT_EQ(parsed.cc->size(), 6);
}

TEST_F(CharClassTest_148, NegateCharClass_148) {
  auto parsed = ParseCharClass("[a-z]");
  TrackRegexp(parsed.re);
  ASSERT_NE(parsed.cc, nullptr);
  
  CharClass* neg = parsed.cc->Negate();
  ASSERT_NE(neg, nullptr);
  
  // Negation should not contain 'a'-'z'
  EXPECT_FALSE(neg->Contains('a'));
  EXPECT_FALSE(neg->Contains('m'));
  EXPECT_FALSE(neg->Contains('z'));
  
  // But should contain things outside a-z
  EXPECT_TRUE(neg->Contains('A'));
  EXPECT_TRUE(neg->Contains('0'));
  EXPECT_TRUE(neg->Contains('!'));
  
  neg->Delete();
}

TEST_F(CharClassTest_148, NegatePreservesComplement_148) {
  auto parsed = ParseCharClass("[0-9]");
  TrackRegexp(parsed.re);
  ASSERT_NE(parsed.cc, nullptr);
  
  CharClass* neg = parsed.cc->Negate();
  ASSERT_NE(neg, nullptr);
  
  EXPECT_FALSE(neg->Contains('0'));
  EXPECT_FALSE(neg->Contains('9'));
  EXPECT_TRUE(neg->Contains('a'));
  
  neg->Delete();
}

TEST_F(CharClassTest_148, FoldsASCIIForCaseInsensitive_148) {
  // Parse with FoldCase to get a class that folds ASCII
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", 
      Regexp::ClassNL | Regexp::PerlX | Regexp::FoldCase, &status);
  TrackRegexp(re);
  ASSERT_NE(re, nullptr);
  if (re->op() == kRegexpCharClass) {
    CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    // When FoldCase is used on [a-z], it should include A-Z too
    EXPECT_TRUE(cc->Contains('A'));
    EXPECT_TRUE(cc->Contains('Z'));
    // FoldsASCII should reflect whether ASCII case folding was applied
    // This is implementation-dependent but we test the accessor works
    bool folds = cc->FoldsASCII();
    // Just verify it returns a bool without crashing
    (void)folds;
  }
}

TEST_F(CharClassTest_148, FoldsASCIIBasicClass_148) {
  auto parsed = ParseCharClass("[a-z]");
  TrackRegexp(parsed.re);
  ASSERT_NE(parsed.cc, nullptr);
  // A simple [a-z] without fold should not fold ASCII
  // (This depends on implementation but we test the accessor)
  bool folds = parsed.cc->FoldsASCII();
  // Without FoldCase flag, this should be false
  EXPECT_FALSE(folds);
}

TEST_F(CharClassTest_148, ContainsBoundaryRunes_148) {
  auto parsed = ParseCharClass("[a-z]");
  TrackRegexp(parsed.re);
  ASSERT_NE(parsed.cc, nullptr);
  // Test boundary: just before 'a' and just after 'z'
  EXPECT_FALSE(parsed.cc->Contains('a' - 1));  // '`'
  EXPECT_TRUE(parsed.cc->Contains('a'));
  EXPECT_TRUE(parsed.cc->Contains('z'));
  EXPECT_FALSE(parsed.cc->Contains('z' + 1));  // '{'
}

TEST_F(CharClassTest_148, MultipleDisjointRanges_148) {
  auto parsed = ParseCharClass("[ace]");
  TrackRegexp(parsed.re);
  ASSERT_NE(parsed.cc, nullptr);
  EXPECT_TRUE(parsed.cc->Contains('a'));
  EXPECT_FALSE(parsed.cc->Contains('b'));
  EXPECT_TRUE(parsed.cc->Contains('c'));
  EXPECT_FALSE(parsed.cc->Contains('d'));
  EXPECT_TRUE(parsed.cc->Contains('e'));
  EXPECT_EQ(parsed.cc->size(), 3);
}

TEST_F(CharClassTest_148, IteratorCountMatchesSize_148) {
  auto parsed = ParseCharClass("[a-zA-Z]");
  TrackRegexp(parsed.re);
  ASSERT_NE(parsed.cc, nullptr);
  
  int count = 0;
  for (auto it = parsed.cc->begin(); it != parsed.cc->end(); ++it) {
    count += it->hi - it->lo + 1;
  }
  EXPECT_EQ(count, parsed.cc->size());
  EXPECT_EQ(count, 52);  // 26 + 26
}

TEST_F(CharClassTest_148, NewAndDeleteViaParseNegate_148) {
  // Test that Negate creates a new CharClass that can be deleted
  auto parsed = ParseCharClass("[a]");
  TrackRegexp(parsed.re);
  ASSERT_NE(parsed.cc, nullptr);
  
  CharClass* neg = parsed.cc->Negate();
  ASSERT_NE(neg, nullptr);
  EXPECT_FALSE(neg->Contains('a'));
  EXPECT_FALSE(neg->empty());
  
  // Double negate should give us back something containing 'a'
  CharClass* neg2 = neg->Negate();
  ASSERT_NE(neg2, nullptr);
  EXPECT_TRUE(neg2->Contains('a'));
  EXPECT_EQ(neg2->size(), 1);
  
  neg2->Delete();
  neg->Delete();
}

}  // namespace re2
