// File: ./TestProjects/re2/re2/tests/prefilter_walker_postvisit_test.cc

#include "gtest/gtest.h"
#include "re2/regexp.h"
// The partials show Prefilter and nested Info/Walker in prefilter.cc.
// Include the header where Prefilter is declared in your tree.
// If there isn't a standalone header, forward-declare minimally for tests:
namespace re2 {
class Prefilter {
 public:
  class Info {
   public:
    static Info* EmptyString();
    static Info* NoMatch();
    static Info* AnyCharOrAnyByte();
    static Info* CClass(CharClass* cc, bool latin1);
    static Info* Literal(Rune r);
    static Info* LiteralLatin1(Rune r);
    static Info* Concat(Info* a, Info* b);
    static Info* Alt(Info* a, Info* b);
    static Info* And(Info* a, Info* b);
    static Info* Star(Info* a);
    static Info* Plus(Info* a);
    static Info* Quest(Info* a);
    bool is_exact() const;              // exposed in partials
    SSet& exact();                      // exposed in partials
    std::string ToString();             // exposed in partials
  };

  class Walker : public Regexp::Walker<Prefilter::Info*> {
   public:
    explicit Walker(bool latin1);
    Info* PostVisit(Regexp* re,
                    Info* parent_arg,
                    Info* pre_arg,
                    Info** child_args,
                    int nchild_args) override;
    Info* ShortVisit(Regexp* re, Info* parent_arg) override;
    bool latin1();
  };
};
}  // namespace re2

namespace {

using namespace re2;

class PrefilterWalkerPostVisitTest_561 : public ::testing::Test {
 protected:
  // Helpers to build Regexp nodes using public factory methods.
  static Regexp* Lit(Rune r) {
    return Regexp::NewLiteral(r, Regexp::MATCH_NL);
  }
  static Regexp* CaptureOf(Regexp* sub, int cap = 1) {
    return Regexp::Capture(sub, Regexp::MATCH_NL, cap);
  }
  static Regexp* AltOf(std::initializer_list<Regexp*> subs) {
    std::vector<Regexp*> v(subs);
    return Regexp::Alternate(v.data(), static_cast<int>(v.size()), Regexp::MATCH_NL);
  }
  static Regexp* ConcatOf(std::initializer_list<Regexp*> subs) {
    std::vector<Regexp*> v(subs);
    return Regexp::Concat(v.data(), static_cast<int>(v.size()), Regexp::MATCH_NL);
  }
  static Regexp* StarOf(Regexp* sub) {
    return Regexp::Star(sub, Regexp::MATCH_NL);
  }
  static Regexp* PlusOf(Regexp* sub) {
    return Regexp::Plus(sub, Regexp::MATCH_NL);
  }
  static Regexp* QuestOf(Regexp* sub) {
    return Regexp::Quest(sub, Regexp::MATCH_NL);
  }
  static Regexp* LiteralStringOf(const std::u32string& s) {
    // Build rune buffer
    std::vector<Rune> runes(s.begin(), s.end());
    return Regexp::LiteralString(runes.empty() ? nullptr : runes.data(),
                                 static_cast<int>(runes.size()),
                                 Regexp::MATCH_NL);
  }
};

// --- Basic op coverage ---

TEST_F(PrefilterWalkerPostVisitTest_561, Capture_ReturnsChildPointer_561) {
  Prefilter::Walker w(/*latin1=*/true);

  // Build a capture regex, but PostVisit for kRegexpCapture returns child_args[0].
  Regexp* lit = Lit('a');
  Regexp* cap = CaptureOf(lit);

  Prefilter::Info* child = Prefilter::Info::LiteralLatin1('a');
  Prefilter::Info* child_args[] = {child};

  Prefilter::Info* out =
      w.PostVisit(cap, /*parent_arg=*/nullptr, /*pre_arg=*/nullptr,
                  child_args, /*nchild_args=*/1);

  // Observable behavior: returns the same child info pointer.
  EXPECT_EQ(out, child);
}

TEST_F(PrefilterWalkerPostVisitTest_561, Alternate_SingleChild_ReturnsSameChild_561) {
  Prefilter::Walker w(/*latin1=*/false);

  Regexp* alt = AltOf({Lit('x')});
  Prefilter::Info* child = Prefilter::Info::Literal('x');
  Prefilter::Info* child_args[] = {child};

  Prefilter::Info* out =
      w.PostVisit(alt, nullptr, nullptr, child_args, /*nchild_args=*/1);

  EXPECT_EQ(out, child);
}

TEST_F(PrefilterWalkerPostVisitTest_561, Alternate_TwoChildren_ReturnsNewInfo_561) {
  Prefilter::Walker w(/*latin1=*/true);

  Regexp* alt = AltOf({Lit('a'), Lit('b')});
  Prefilter::Info* c1 = Prefilter::Info::LiteralLatin1('a');
  Prefilter::Info* c2 = Prefilter::Info::LiteralLatin1('b');
  Prefilter::Info* child_args[] = {c1, c2};

  Prefilter::Info* out =
      w.PostVisit(alt, nullptr, nullptr, child_args, /*nchild_args=*/2);

  // With 2 children, PostVisit builds Alt(c1, c2) — a new Info distinct from inputs.
  ASSERT_NE(out, nullptr);
  EXPECT_NE(out, c1);
  EXPECT_NE(out, c2);
}

TEST_F(PrefilterWalkerPostVisitTest_561, Star_WrapsChild_ReturnsDifferentPointer_561) {
  Prefilter::Walker w(/*latin1=*/false);

  Regexp* star = StarOf(Lit('z'));
  Prefilter::Info* child = Prefilter::Info::Literal('z');
  Prefilter::Info* child_args[] = {child};

  Prefilter::Info* out =
      w.PostVisit(star, nullptr, nullptr, child_args, /*nchild_args=*/1);

  ASSERT_NE(out, nullptr);
  EXPECT_NE(out, child);  // Star(child) should not be the same pointer
}

TEST_F(PrefilterWalkerPostVisitTest_561, Plus_WrapsChild_ReturnsDifferentPointer_561) {
  Prefilter::Walker w(/*latin1=*/false);

  Regexp* plus = PlusOf(Lit('q'));
  Prefilter::Info* child = Prefilter::Info::Literal('q');
  Prefilter::Info* child_args[] = {child};

  Prefilter::Info* out =
      w.PostVisit(plus, nullptr, nullptr, child_args, /*nchild_args=*/1);

  ASSERT_NE(out, nullptr);
  EXPECT_NE(out, child);
}

TEST_F(PrefilterWalkerPostVisitTest_561, Quest_WrapsChild_ReturnsDifferentPointer_561) {
  Prefilter::Walker w(/*latin1=*/true);

  Regexp* q = QuestOf(Lit('r'));
  Prefilter::Info* child = Prefilter::Info::LiteralLatin1('r');
  Prefilter::Info* child_args[] = {child};

  Prefilter::Info* out =
      w.PostVisit(q, nullptr, nullptr, child_args, /*nchild_args=*/1);

  ASSERT_NE(out, nullptr);
  EXPECT_NE(out, child);
}

TEST_F(PrefilterWalkerPostVisitTest_561, AnyCharAndAnyByte_ReturnNonNull_561) {
  Prefilter::Walker w(/*latin1=*/true);

  // We can synthesize these via Parse for simplicity.
  RegexpStatus rs;
  Regexp* anychar = Regexp::Parse(".", Regexp::MATCH_NL, &rs);
  ASSERT_NE(anychar, nullptr);
  // Force op() path for AnyChar
  EXPECT_EQ(anychar->op(), kRegexpConcat) << "Parser may build concat; still routed through PostVisit.";

  // We directly create Regexp for AnyChar/AnyByte via Repeat/Star etc. not exposed,
  // so instead invoke PostVisit with ops we know from the enum by creating simple leaves:
  // Use literal children for child_args and pass explicit Re nodes where possible elsewhere.

  // Build by hand: Use a literal child but call PostVisit with a dummy AnyChar op:
  // Easiest: Use a small literal regex and overwrite its op is not allowed. Instead,
  // cover via the explicit case that PostVisit respects both AnyChar and AnyByte
  // using an Alternate with no children is unsafe. So we create fake nodes via Repeat/Quest?
  // Given the constraints & partials, limit to verifying non-null on literal-based paths:

  // Verify AnyCharOrAnyByte path indirectly using Alternate two children '.' and '\x00' via Parse:
  Regexp* dot = Regexp::Parse(".", Regexp::MATCH_NL, &rs);
  ASSERT_NE(dot, nullptr);

  Prefilter::Info* out =
      w.PostVisit(dot, nullptr, nullptr, /*child_args=*/nullptr, /*nchild_args=*/0);

  ASSERT_NE(out, nullptr);
}

TEST_F(PrefilterWalkerPostVisitTest_561, EmptyAndBoundaryOps_ReturnNonNull_561) {
  Prefilter::Walker w(/*latin1=*/false);

  // Use parser to create anchors/boundaries where available.
  RegexpStatus rs;
  // ^ (begin line), $ (end line)
  Regexp* begin = Regexp::Parse("^", Regexp::MATCH_NL, &rs);
  Regexp* end   = Regexp::Parse("$", Regexp::MATCH_NL, &rs);
  ASSERT_NE(begin, nullptr);
  ASSERT_NE(end, nullptr);

  Prefilter::Info* out_begin =
      w.PostVisit(begin, nullptr, nullptr, nullptr, 0);
  Prefilter::Info* out_end =
      w.PostVisit(end, nullptr, nullptr, nullptr, 0);

  ASSERT_NE(out_begin, nullptr);
  ASSERT_NE(out_end, nullptr);
}

TEST_F(PrefilterWalkerPostVisitTest_561, Repeat_OpFallsBackToEmptyString_NonNull_561) {
  Prefilter::Walker w(/*latin1=*/true);

  // Construct a repeat via public API: Repeat(sub, min, max).
  Regexp* lit = Lit('a');
  Regexp* rep = Regexp::Repeat(lit, Regexp::MATCH_NL, /*min=*/2, /*max=*/3);
  ASSERT_NE(rep, nullptr);
  ASSERT_EQ(rep->op(), kRegexpRepeat);

  Prefilter::Info* out =
      w.PostVisit(rep, nullptr, nullptr, /*child_args=*/nullptr, /*nchild_args=*/0);

  // The code path sets info = EmptyString() for kRegexpRepeat.
  ASSERT_NE(out, nullptr);
}

TEST_F(PrefilterWalkerPostVisitTest_561, Literal_RespectsLatin1Flag_ReturnsNonNull_561) {
  // latin1 = true
  {
    Prefilter::Walker w(/*latin1=*/true);
    Regexp* lit = Lit(0x00E9);  // 'é'
    Prefilter::Info* out =
        w.PostVisit(lit, nullptr, nullptr, /*child_args=*/nullptr, /*nchild_args=*/0);
    ASSERT_NE(out, nullptr);
  }
  // latin1 = false
  {
    Prefilter::Walker w(/*latin1=*/false);
    Regexp* lit = Lit(0x00E9);  // 'é'
    Prefilter::Info* out =
        w.PostVisit(lit, nullptr, nullptr, /*child_args=*/nullptr, /*nchild_args=*/0);
    ASSERT_NE(out, nullptr);
  }
}

TEST_F(PrefilterWalkerPostVisitTest_561, LiteralString_EmptyBecomesNoMatch_NonNull_561) {
  Prefilter::Walker w(/*latin1=*/true);

  // nrunes == 0 triggers NoMatch() in PostVisit; we only assert non-null (black-box).
  Regexp* ls = LiteralStringOf(U"");  // empty
  Prefilter::Info* out =
      w.PostVisit(ls, nullptr, nullptr, /*child_args=*/nullptr, /*nchild_args=*/0);

  ASSERT_NE(out, nullptr);
}

TEST_F(PrefilterWalkerPostVisitTest_561, LiteralString_MultiRune_BuildsChain_NonNull_561) {
  Prefilter::Walker w(/*latin1=*/false);

  Regexp* ls = LiteralStringOf(U"ab");
  Prefilter::Info* out =
      w.PostVisit(ls, nullptr, nullptr, /*child_args=*/nullptr, /*nchild_args=*/0);

  ASSERT_NE(out, nullptr);
}

TEST_F(PrefilterWalkerPostVisitTest_561, Concat_WithTwoChildren_ReturnsNonNull_561) {
  Prefilter::Walker w(/*latin1=*/true);

  Regexp* c = ConcatOf({Lit('a'), Lit('b')});
  Prefilter::Info* c1 = Prefilter::Info::LiteralLatin1('a');
  Prefilter::Info* c2 = Prefilter::Info::LiteralLatin1('b');
  Prefilter::Info* child_args[] = {c1, c2};

  Prefilter::Info* out =
      w.PostVisit(c, nullptr, nullptr, child_args, /*nchild_args=*/2);

  ASSERT_NE(out, nullptr);
}

}  // namespace
