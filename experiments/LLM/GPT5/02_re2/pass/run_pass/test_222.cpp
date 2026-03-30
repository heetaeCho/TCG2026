// File: empty_string_walker_postvisit_test_222.cc
#include "re2/regexp.h"
#include "gtest/gtest.h"

using namespace re2;

namespace {

// Small helper to parse a pattern into a Regexp* (black-box construction).
static Regexp* ParseRe(const std::string& pat) {
  RegexpStatus status;
  // Use default/zero flags to keep construction simple.
  Regexp* re = Regexp::Parse(pat, static_cast<Regexp::ParseFlags>(0), &status);
  // For tests we assert construction succeeded; if it doesn't in your setup,
  // you can switch to the specific factory that yields the node you need.
  EXPECT_NE(re, nullptr) << "Failed to parse pattern: " << pat;
  return re;
}

class EmptyStringWalkerTest_222 : public ::testing::Test {
protected:
  // The walker we’re testing
  class EmptyStringWalker {
  public:
    // Signature matches the provided partial code.
    bool PostVisit(Regexp* re, bool /*parent_arg*/, bool /*pre_arg*/,
                   bool* child_args, int nchild_args) {
      switch (re->op()) {
        case kRegexpNoMatch:  // never empty
        case kRegexpLiteral:
        case kRegexpAnyChar:
        case kRegexpAnyByte:
        case kRegexpCharClass:
        case kRegexpLiteralString:
          return false;

        case kRegexpEmptyMatch:  // always empty
        case kRegexpBeginLine:   // zero-width when they match
        case kRegexpEndLine:
        case kRegexpNoWordBoundary:
        case kRegexpWordBoundary:
        case kRegexpBeginText:
        case kRegexpEndText:
        case kRegexpStar:        // can always be empty
        case kRegexpQuest:
        case kRegexpHaveMatch:
          return true;

        case kRegexpConcat: {    // empty if all children empty
          for (int i = 0; i < nchild_args; ++i)
            if (!child_args[i]) return false;
          return true;
        }

        case kRegexpAlternate: { // empty if any child empty
          for (int i = 0; i < nchild_args; ++i)
            if (child_args[i]) return true;
          return false;
        }

        case kRegexpPlus:        // empty iff child empty
        case kRegexpCapture:
          return child_args[0];

        case kRegexpRepeat:      // empty if child empty OR min == 0
          return child_args[0] || re->min() == 0;
      }
      return false;
    }
  };

  EmptyStringWalker walker_;
};

}  // namespace

// ---------- Single-node categories ----------

TEST_F(EmptyStringWalkerTest_222, LiteralIsNotEmpty_222) {
  Regexp* re = ParseRe("a");
  ASSERT_NE(re, nullptr);
  bool out = walker_.PostVisit(re, false, false, nullptr, 0);
  EXPECT_FALSE(out);
  re->Decref();
}

TEST_F(EmptyStringWalkerTest_222, AnyCharIsNotEmpty_222) {
  Regexp* re = ParseRe(".");
  ASSERT_NE(re, nullptr);
  bool out = walker_.PostVisit(re, false, false, nullptr, 0);
  EXPECT_FALSE(out);
  re->Decref();
}

TEST_F(EmptyStringWalkerTest_222, CharClassIsNotEmpty_222) {
  Regexp* re = ParseRe("[a]");
  ASSERT_NE(re, nullptr);
  bool out = walker_.PostVisit(re, false, false, nullptr, 0);
  EXPECT_FALSE(out);
  re->Decref();
}

TEST_F(EmptyStringWalkerTest_222, EmptyMatchIsEmpty_222) {
  // (?=) is a zero-width (empty) assertion in PCRE/RE2 syntax.
  Regexp* re = ParseRe("(?=)");
  ASSERT_NE(re, nullptr);
  bool out = walker_.PostVisit(re, false, false, nullptr, 0);
  EXPECT_TRUE(out);
  re->Decref();
}

TEST_F(EmptyStringWalkerTest_222, BeginEndAnchorsAreEmpty_222) {
  Regexp* begin_line = ParseRe("^");
  Regexp* end_line   = ParseRe("$");
  ASSERT_NE(begin_line, nullptr);
  ASSERT_NE(end_line, nullptr);

  EXPECT_TRUE(walker_.PostVisit(begin_line, false, false, nullptr, 0));
  EXPECT_TRUE(walker_.PostVisit(end_line,   false, false, nullptr, 0));

  begin_line->Decref();
  end_line->Decref();
}

TEST_F(EmptyStringWalkerTest_222, WordBoundaryAndNoWordBoundaryAreEmpty_222) {
  Regexp* wb  = ParseRe("\\b");
  Regexp* nwb = ParseRe("\\B");
  ASSERT_NE(wb, nullptr);
  ASSERT_NE(nwb, nullptr);

  EXPECT_TRUE(walker_.PostVisit(wb,  false, false, nullptr, 0));
  EXPECT_TRUE(walker_.PostVisit(nwb, false, false, nullptr, 0));

  wb->Decref();
  nwb->Decref();
}

TEST_F(EmptyStringWalkerTest_222, BeginEndTextAreEmpty_222) {
  // \A and \z are begin/end of text in RE2.
  Regexp* bt = ParseRe("\\A");
  Regexp* et = ParseRe("\\z");
  ASSERT_NE(bt, nullptr);
  ASSERT_NE(et, nullptr);

  EXPECT_TRUE(walker_.PostVisit(bt, false, false, nullptr, 0));
  EXPECT_TRUE(walker_.PostVisit(et, false, false, nullptr, 0));

  bt->Decref();
  et->Decref();
}

TEST_F(EmptyStringWalkerTest_222, StarAndQuestAlwaysEmpty_222) {
  Regexp* star  = ParseRe("a*");
  Regexp* quest = ParseRe("a?");
  ASSERT_NE(star, nullptr);
  ASSERT_NE(quest, nullptr);

  EXPECT_TRUE(walker_.PostVisit(star,  false, false, nullptr, 0));
  EXPECT_TRUE(walker_.PostVisit(quest, false, false, nullptr, 0));

  star->Decref();
  quest->Decref();
}

// ---------- Nodes that depend on children ----------

TEST_F(EmptyStringWalkerTest_222, ConcatEmptyIffAllChildrenEmpty_222) {
  // Use a concat node by parsing "ab".
  Regexp* concat = ParseRe("ab");
  ASSERT_NE(concat, nullptr);

  bool all_empty[2]   = {true, true};
  bool one_not[2]     = {true, false};
  bool none_empty[2]  = {false, false};

  EXPECT_TRUE(walker_.PostVisit(concat, false, false, all_empty, 2));
  EXPECT_FALSE(walker_.PostVisit(concat, false, false, one_not,   2));
  EXPECT_FALSE(walker_.PostVisit(concat, false, false, none_empty,2));

  concat->Decref();
}

TEST_F(EmptyStringWalkerTest_222, AlternateEmptyIfAnyChildEmpty_222) {
  // Use an alternate node by parsing "a|b".
  Regexp* alt = ParseRe("a|b");
  ASSERT_NE(alt, nullptr);

  bool any_empty1[2]  = {true, false};
  bool any_empty2[2]  = {false, true};
  bool none_empty[2]  = {false, false};

  EXPECT_TRUE(walker_.PostVisit(alt, false, false, any_empty1, 2));
  EXPECT_TRUE(walker_.PostVisit(alt, false, false, any_empty2, 2));
  EXPECT_FALSE(walker_.PostVisit(alt, false, false, none_empty, 2));

  alt->Decref();
}

TEST_F(EmptyStringWalkerTest_222, PlusEmptyIffChildEmpty_222) {
  Regexp* plus = ParseRe("a+");
  ASSERT_NE(plus, nullptr);

  bool child_empty_true[1]  = {true};
  bool child_empty_false[1] = {false};

  EXPECT_TRUE(walker_.PostVisit(plus, false, false, child_empty_true, 1));
  EXPECT_FALSE(walker_.PostVisit(plus, false, false, child_empty_false, 1));

  plus->Decref();
}

TEST_F(EmptyStringWalkerTest_222, CapturePropagatesChildEmptiness_222) {
  Regexp* cap = ParseRe("(a)");
  ASSERT_NE(cap, nullptr);

  bool child_empty_true[1]  = {true};
  bool child_empty_false[1] = {false};

  EXPECT_TRUE(walker_.PostVisit(cap, false, false, child_empty_true, 1));
  EXPECT_FALSE(walker_.PostVisit(cap, false, false, child_empty_false, 1));

  cap->Decref();
}

TEST_F(EmptyStringWalkerTest_222, RepeatEmptyIfChildEmptyOrMinZero_222) {
  // min == 0 case: "a{0,3}"
  Regexp* rep_min0 = ParseRe("a{0,3}");
  ASSERT_NE(rep_min0, nullptr);

  bool child_not_empty[1] = {false};  // child cannot be empty
  // min==0 => true regardless of child emptiness
  EXPECT_TRUE(walker_.PostVisit(rep_min0, false, false, child_not_empty, 1));

  rep_min0->Decref();

  // min > 0 case: "a{2,5}"
  Regexp* rep_min2 = ParseRe("a{2,5}");
  ASSERT_NE(rep_min2, nullptr);

  bool child_empty_true[1]  = {true};
  bool child_empty_false[1] = {false};

  // If child empty -> true; if not empty and min>0 -> false
  EXPECT_TRUE(walker_.PostVisit(rep_min2, false, false, child_empty_true, 1));
  EXPECT_FALSE(walker_.PostVisit(rep_min2, false, false, child_empty_false, 1));

  rep_min2->Decref();
}

// ---------- Edge/Exceptional observable cases ----------

TEST_F(EmptyStringWalkerTest_222, NoMatchIsNotEmpty_222) {
  // "(?!)" is the standard never-match construct.
  Regexp* nomatch = ParseRe("(?!)");
  ASSERT_NE(nomatch, nullptr);

  bool out = walker_.PostVisit(nomatch, false, false, nullptr, 0);
  EXPECT_FALSE(out);

  nomatch->Decref();
}

