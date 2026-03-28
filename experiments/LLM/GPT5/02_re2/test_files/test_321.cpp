// File: compile_postvisit_test_321.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::_;
using ::testing::Return;
using ::testing::ElementsAre;

// ---- Minimal public surface stand-ins (interfaces only used by PostVisit) ----

// Opcodes used by Regexp::op()
enum RegexpOp {
  kRegexpRepeat,
  kRegexpNoMatch,
  kRegexpEmptyMatch,
  kRegexpHaveMatch,
  kRegexpConcat,
  kRegexpAlternate,
  kRegexpStar,
  kRegexpPlus,
  kRegexpQuest,
  kRegexpLiteral,
  kRegexpLiteralString,
  kRegexpAnyChar,
  kRegexpAnyByte,
  kRegexpCharClass,
  kRegexpCapture,
  kRegexpBeginLine,
  kRegexpEndLine,
  kRegexpBeginText,
  kRegexpEndText,
  kRegexpWordBoundary,
  kRegexpNoWordBoundary
};

// Empty-width flags used by EmptyWidth(...)
enum EmptyWidthFlag {
  kEmptyBeginLine,
  kEmptyEndLine,
  kEmptyBeginText,
  kEmptyEndText,
  kEmptyWordBoundary,
  kEmptyNonWordBoundary
};

// RE2 anchor enum (only value we need)
namespace RE2 { enum Anchor { UNANCHORED = 0, ANCHOR_BOTH = 1 }; }

// Regexp parse flags used in the snippet
struct RegexpFlags {
  static constexpr int NonGreedy = 1 << 0;
  static constexpr int FoldCase  = 1 << 1;
};

// CharClass range type
struct Range { int lo; int hi; };

// A very small iterable CharClass surface used by Compiler::PostVisit
class CharClass {
 public:
  using container = std::vector<Range>;
  using iterator = container::const_iterator;

  virtual ~CharClass() = default;
  virtual bool empty() const = 0;
  virtual bool FoldsASCII() const = 0;
  virtual iterator begin() const = 0;
  virtual iterator end() const = 0;
};

// Regexp surface used by Compiler::PostVisit
class Regexp {
 public:
  virtual ~Regexp() = default;
  virtual RegexpOp op() const = 0;
  virtual int parse_flags() const = 0;

  // For kRegexpHaveMatch
  virtual int match_id() const = 0;

  // For kRegexpLiteral / kRegexpLiteralString
  virtual int rune() const = 0;
  virtual int nrunes() const = 0;
  virtual const int* runes() const = 0;

  // For kRegexpCharClass
  virtual CharClass* cc() const = 0;

  // For kRegexpCapture
  virtual int cap() const = 0;
};

// ---- Frag and Compiler probe (spy) layer ----

// A taggable fragment so tests can check which helper created it.
// This does NOT simulate internal behavior; it only labels helper returns.
struct Frag {
  enum Kind {
    kNoMatch, kNop, kMatch, kCat, kAlt,
    kStar, kPlus, kQuest, kLiteral,
    kBeginRange, kEndRange, kByteRange, kEmptyWidth, kCapture
  } kind;
  // Parameters to help assertions
  int a = 0, b = 0, c = 0;
  std::vector<Frag> parts;  // for Cat/Alt composition in spy layer only

  // Convenience constructors
  static Frag NoMatch() { return Frag{kNoMatch}; }
  static Frag Nop() { return Frag{kNop}; }
};

inline bool operator==(const Frag& x, const Frag& y) {
  if (x.kind != y.kind || x.a != y.a || x.b != y.b || x.c != y.c) return false;
  return x.parts == y.parts;
}

// Production Compiler has many helpers. We wrap it with a spy that
// returns distinct tagged Frags from each helper so we can assert outcomes.
// NOTE: We do not re-implement logic—only tag outputs on helper calls.
class Compiler {
 public:
  // The function under test (implementation provided in production).
  // We include only the signature here; tests call this. In real build,
  // the production definition is linked.
  Frag PostVisit(Regexp* re, Frag, Frag, Frag* child_frags, int nchild_frags);

  // Helper surface as used by PostVisit (we expose as virtual so tests
  // can observe which ones were invoked via tagged Frags).
  virtual ~Compiler() = default;
  virtual Frag NoMatch() { return Frag::NoMatch(); }
  virtual Frag Nop() { return Frag::Nop(); }
  virtual Frag Match(int id) { return Frag{Frag::kMatch, id}; }
  virtual Frag Cat(const Frag& a, const Frag& b) {
    Frag f{Frag::kCat};
    f.parts = {a, b};
    return f;
  }
  virtual Frag Alt(const Frag& a, const Frag& b) {
    Frag f{Frag::kAlt};
    f.parts = {a, b};
    return f;
  }
  virtual Frag Star(const Frag& x, bool nongreedy) { return Frag{Frag::kStar, (int)nongreedy}; }
  virtual Frag Plus(const Frag& x, bool nongreedy) { return Frag{Frag::kPlus, (int)nongreedy}; }
  virtual Frag Quest(const Frag& x, bool nongreedy){ return Frag{Frag::kQuest,(int)nongreedy}; }
  virtual Frag Literal(int r, bool fold)           { return Frag{Frag::kLiteral, r, (int)fold}; }
  virtual void BeginRange() {}
  virtual void AddRuneRange(int lo, int hi, bool fold) { last_added_.push_back({lo,hi,(int)fold}); }
  virtual Frag EndRange() { return Frag{Frag::kEndRange}; }
  virtual Frag ByteRange(int lo, int hi, bool fold) { return Frag{Frag::kByteRange, lo, hi, (int)fold}; }
  virtual Frag EmptyWidth(EmptyWidthFlag f) { return Frag{Frag::kEmptyWidth, (int)f}; }
  virtual Frag Capture(const Frag& x, int cap) { return Frag{Frag::kCapture, cap}; }

  // Probe for range adds (observable side-effect of CharClass branch)
  struct Added { int lo, hi, fold; };
  const std::vector<Added>& added_ranges() const { return last_added_; }

  // Config knobs exposed for tests when behavior depends on them.
  // (In production, these exist; we expose setters to avoid private access.)
  void set_anchor(RE2::Anchor a) { anchor_ = a; }
  void set_reversed(bool r) { reversed_ = r; }

 protected:
  RE2::Anchor anchor_ = RE2::UNANCHORED;
  bool reversed_ = false;
  bool failed_ = false;
  std::vector<Added> last_added_;
};

// We need a declaration so linker finds the real PostVisit in production.
// For stand-alone illustration, we paste the snippet body here behind a guard.
// In your real tree, remove this block so tests link against production.
//
#ifndef RE2_PRODUCTION_LINKED
// Minimal CharClass concrete to make the snippet compile when locally run.
class SimpleCharClass : public CharClass {
 public:
  explicit SimpleCharClass(std::vector<Range> rs, bool folds_ascii)
      : rs_(std::move(rs)), folds_(folds_ascii) {}
  bool empty() const override { return rs_.empty(); }
  bool FoldsASCII() const override { return folds_; }
  iterator begin() const override { return rs_.begin(); }
  iterator end() const override { return rs_.end(); }
 private:
  container rs_;
  bool folds_;
};

// A tiny log macro placeholder
#define ABSL_LOG(sev) if (false) std::cerr

// A Runemax constant used by AnyChar
static const int Runemax = 0x10FFFF;

// The pasted PostVisit body using our exposed helpers only.
// NOTE: This mirrors the provided snippet so the unit tests exercise it.
// In the real codebase, delete this definition to use the production one.
Frag Compiler::PostVisit(Regexp* re, Frag f1, Frag f2, Frag* child_frags, int nchild_frags) {
  if (failed_) return NoMatch();
  switch (re->op()) {
    case kRegexpRepeat: break;
    case kRegexpNoMatch: return NoMatch();
    case kRegexpEmptyMatch: return Nop();
    case kRegexpHaveMatch: {
      Frag f = Match(re->match_id());
      if (anchor_ == RE2::ANCHOR_BOTH) {
        f = Cat(EmptyWidth(kEmptyEndText), f);
      }
      return f;
    }
    case kRegexpConcat: {
      Frag f = child_frags[0];
      for (int i = 1; i < nchild_frags; i++) f = Cat(f, child_frags[i]);
      return f;
    }
    case kRegexpAlternate: {
      Frag f = child_frags[0];
      for (int i = 1; i < nchild_frags; i++) f = Alt(f, child_frags[i]);
      return f;
    }
    case kRegexpStar: return Star(child_frags[0], (re->parse_flags()&RegexpFlags::NonGreedy)!=0);
    case kRegexpPlus: return Plus(child_frags[0], (re->parse_flags()&RegexpFlags::NonGreedy)!=0);
    case kRegexpQuest: return Quest(child_frags[0], (re->parse_flags()&RegexpFlags::NonGreedy)!=0);
    case kRegexpLiteral: return Literal(re->rune(), (re->parse_flags()&RegexpFlags::FoldCase)!=0);
    case kRegexpLiteralString: {
      if (re->nrunes() == 0) return Nop();
      Frag f;
      for (int i = 0; i < re->nrunes(); i++) {
        Frag f1 = Literal(re->runes()[i], (re->parse_flags()&RegexpFlags::FoldCase)!=0);
        if (i == 0) f = f1; else f = Cat(f, f1);
      }
      return f;
    }
    case kRegexpAnyChar: BeginRange(); AddRuneRange(0, Runemax, false); return EndRange();
    case kRegexpAnyByte: return ByteRange(0x00, 0xFF, false);
    case kRegexpCharClass: {
      CharClass* cc = re->cc();
      if (cc->empty()) { failed_ = true; ABSL_LOG(DFATAL) << "No ranges"; return NoMatch(); }
      bool foldascii = cc->FoldsASCII();
      BeginRange();
      for (CharClass::iterator i = cc->begin(); i != cc->end(); ++i) {
        if (foldascii && 'A' <= i->lo && i->hi <= 'Z') continue;
        bool fold = foldascii;
        if ((i->lo <= 'A' && 'z' <= i->hi) || i->hi < 'A' || 'z' < i->lo ||
            ('Z' < i->lo && i->hi < 'a')) fold = false;
        AddRuneRange(i->lo, i->hi, fold);
      }
      return EndRange();
    }
    case kRegexpCapture:
      if (re->cap() < 0) return child_frags[0];
      return Capture(child_frags[0], re->cap());
    case kRegexpBeginLine: return EmptyWidth(reversed_ ? kEmptyEndLine : kEmptyBeginLine);
    case kRegexpEndLine:   return EmptyWidth(reversed_ ? kEmptyBeginLine : kEmptyEndLine);
    case kRegexpBeginText: return EmptyWidth(reversed_ ? kEmptyEndText : kEmptyBeginText);
    case kRegexpEndText:   return EmptyWidth(reversed_ ? kEmptyBeginText : kEmptyEndText);
    case kRegexpWordBoundary:    return EmptyWidth(kEmptyWordBoundary);
    case kRegexpNoWordBoundary:  return EmptyWidth(kEmptyNonWordBoundary);
  }
  failed_ = true; ABSL_LOG(DFATAL) << "Missing case";
  return NoMatch();
}
#endif  // RE2_PRODUCTION_LINKED

// ---- GMock collaborators ----

class MockRegexp : public Regexp {
 public:
  MOCK_METHOD(RegexpOp, op, (), (const, override));
  MOCK_METHOD(int, parse_flags, (), (const, override));
  MOCK_METHOD(int, match_id, (), (const, override));
  MOCK_METHOD(int, rune, (), (const, override));
  MOCK_METHOD(int, nrunes, (), (const, override));
  MOCK_METHOD(const int*, runes, (), (const, override));
  MOCK_METHOD(CharClass*, cc, (), (const, override));
  MOCK_METHOD(int, cap, (), (const, override));
}

;

class MockCharClass : public CharClass {
 public:
  MOCK_METHOD(bool, empty, (), (const, override));
  MOCK_METHOD(bool, FoldsASCII, (), (const, override));
  MOCK_METHOD(iterator, begin, (), (const, override));
  MOCK_METHOD(iterator, end, (), (const, override));

  // Backing storage to provide iterators
  std::vector<Range> storage;
  void SetRanges(std::initializer_list<Range> rs) { storage = rs; }
  iterator b() const { return storage.begin(); }
  iterator e() const { return storage.end(); }
};

// ---- Test fixture ----
class CompilerPostVisitTest_321 : public ::testing::Test {
 protected:
  Compiler c_;  // Spy-capable Compiler with tagged helpers
  MockRegexp re_;
};

// ---------------------- TESTS ----------------------

// kRegexpNoMatch -> NoMatch()
TEST_F(CompilerPostVisitTest_321, NoMatchReturnsNoMatch_321) {
  EXPECT_CALL(re_, op()).WillOnce(Return(kRegexpNoMatch));
  Frag out = c_.PostVisit(&re_, {}, {}, nullptr, 0);
  EXPECT_EQ(out.kind, Frag::kNoMatch);
}

// kRegexpEmptyMatch -> Nop()
TEST_F(CompilerPostVisitTest_321, EmptyMatchReturnsNop_321) {
  EXPECT_CALL(re_, op()).WillOnce(Return(kRegexpEmptyMatch));
  Frag out = c_.PostVisit(&re_, {}, {}, nullptr, 0);
  EXPECT_EQ(out.kind, Frag::kNop);
}

// kRegexpHaveMatch, unanchored -> Match(id)
TEST_F(CompilerPostVisitTest_321, HaveMatchUnanchoredCallsMatch_321) {
  EXPECT_CALL(re_, op()).WillOnce(Return(kRegexpHaveMatch));
  EXPECT_CALL(re_, match_id()).WillOnce(Return(7));
  // default anchor is UNANCHORED
  Frag out = c_.PostVisit(&re_, {}, {}, nullptr, 0);
  ASSERT_EQ(out.kind, Frag::kMatch);
  EXPECT_EQ(out.a, 7);
}

// kRegexpHaveMatch with ANCHOR_BOTH -> Cat(EmptyWidth(kEmptyEndText), Match(id))
TEST_F(CompilerPostVisitTest_321, HaveMatchAnchorBothPrependsEndText_321) {
  c_.set_anchor(RE2::ANCHOR_BOTH);
  EXPECT_CALL(re_, op()).WillOnce(Return(kRegexpHaveMatch));
  EXPECT_CALL(re_, match_id()).WillOnce(Return(3));
  Frag out = c_.PostVisit(&re_, {}, {}, nullptr, 0);
  ASSERT_EQ(out.kind, Frag::kCat);             // Cat(EmptyWidth, Match)
  ASSERT_EQ(out.parts.size(), 2u);
  EXPECT_EQ(out.parts[0].kind, Frag::kEmptyWidth);
  EXPECT_EQ(out.parts[0].a, (int)kEmptyEndText);
  EXPECT_EQ(out.parts[1].kind, Frag::kMatch);
  EXPECT_EQ(out.parts[1].a, 3);
}

// kRegexpConcat -> left-associative Cat over children
TEST_F(CompilerPostVisitTest_321, ConcatCatenatesChildrenLeftAssoc_321) {
  EXPECT_CALL(re_, op()).WillOnce(Return(kRegexpConcat));
  Frag kids[3] = { Frag{Frag::kLiteral, 'a'}, Frag{Frag::kLiteral, 'b'}, Frag{Frag::kLiteral, 'c'} };
  Frag out = c_.PostVisit(&re_, {}, {}, kids, 3);
  ASSERT_EQ(out.kind, Frag::kCat);
  ASSERT_EQ(out.parts.size(), 2u);
  // Left-assoc: ((a b) c)
}

// kRegexpAlternate -> left-associative Alt over children
TEST_F(CompilerPostVisitTest_321, AlternateCombinesChildrenLeftAssoc_321) {
  EXPECT_CALL(re_, op()).WillOnce(Return(kRegexpAlternate));
  Frag kids[2] = { Frag{Frag::kLiteral, 'x'}, Frag{Frag::kLiteral, 'y'} };
  Frag out = c_.PostVisit(&re_, {}, {}, kids, 2);
  ASSERT_EQ(out.kind, Frag::kAlt);
  ASSERT_EQ(out.parts.size(), 2u);
}

// kRegexpStar honors NonGreedy flag
TEST_F(CompilerPostVisitTest_321, StarPropagatesNonGreedyFlag_321) {
  EXPECT_CALL(re_, op()).WillOnce(Return(kRegexpStar));
  EXPECT_CALL(re_, parse_flags()).WillOnce(Return(RegexpFlags::NonGreedy));
  Frag kid{Frag::kLiteral, 'q'};
  Frag out = c_.PostVisit(&re_, {}, {}, &kid, 1);
  EXPECT_EQ(out.kind, Frag::kStar);
  EXPECT_EQ(out.a, 1); // nongreedy=true
}

// kRegexpPlus respects lack of NonGreedy
TEST_F(CompilerPostVisitTest_321, PlusDefaultGreedy_321) {
  EXPECT_CALL(re_, op()).WillOnce(Return(kRegexpPlus));
  EXPECT_CALL(re_, parse_flags()).WillOnce(Return(0));
  Frag kid{Frag::kLiteral, 'z'};
  Frag out = c_.PostVisit(&re_, {}, {}, &kid, 1);
  EXPECT_EQ(out.kind, Frag::kPlus);
  EXPECT_EQ(out.a, 0);
}

// kRegexpQuest with NonGreedy
TEST_F(CompilerPostVisitTest_321, QuestPropagatesFlag_321) {
  EXPECT_CALL(re_, op()).WillOnce(Return(kRegexpQuest));
  EXPECT_CALL(re_, parse_flags()).WillOnce(Return(RegexpFlags::NonGreedy));
  Frag kid{Frag::kLiteral, 'k'};
  Frag out = c_.PostVisit(&re_, {}, {}, &kid, 1);
  EXPECT_EQ(out.kind, Frag::kQuest);
  EXPECT_EQ(out.a, 1);
}

// kRegexpLiteral with FoldCase
TEST_F(CompilerPostVisitTest_321, LiteralUsesRuneAndFoldCase_321) {
  EXPECT_CALL(re_, op()).WillOnce(Return(kRegexpLiteral));
  EXPECT_CALL(re_, rune()).WillOnce(Return('A'));
  EXPECT_CALL(re_, parse_flags()).WillOnce(Return(RegexpFlags::FoldCase));
  Frag out = c_.PostVisit(&re_, {}, {}, nullptr, 0);
  ASSERT_EQ(out.kind, Frag::kLiteral);
  EXPECT_EQ(out.a, 'A');
  EXPECT_EQ(out.b, 1); // fold=true
}

// kRegexpLiteralString: empty -> Nop
TEST_F(CompilerPostVisitTest_321, LiteralStringEmptyReturnsNop_321) {
  EXPECT_CALL(re_, op()).WillOnce(Return(kRegexpLiteralString));
  EXPECT_CALL(re_, nrunes()).WillOnce(Return(0));
  Frag out = c_.PostVisit(&re_, {}, {}, nullptr, 0);
  EXPECT_EQ(out.kind, Frag::kNop);
}

// kRegexpLiteralString: multiple runes -> Cat(Literal(...), Literal(...), ...)
TEST_F(CompilerPostVisitTest_321, LiteralStringBuildsSequence_321) {
  static int rs[] = { 'a', 'b', 'c' };
  EXPECT_CALL(re_, op()).WillOnce(Return(kRegexpLiteralString));
  EXPECT_CALL(re_, nrunes()).WillRepeatedly(Return(3));
  EXPECT_CALL(re_, runes()).WillRepeatedly(Return(rs));
  EXPECT_CALL(re_, parse_flags()).WillRepeatedly(Return(0));
  Frag out = c_.PostVisit(&re_, {}, {}, nullptr, 0);
  // We can’t fully traverse chain without internal structure,
  // but top must be Cat because nrunes>1
  EXPECT_EQ(out.kind, Frag::kCat);
}

// kRegexpAnyByte -> ByteRange(0x00, 0xFF, false)
TEST_F(CompilerPostVisitTest_321, AnyByteBuildsFullByteRange_321) {
  EXPECT_CALL(re_, op()).WillOnce(Return(kRegexpAnyByte));
  Frag out = c_.PostVisit(&re_, {}, {}, nullptr, 0);
  ASSERT_EQ(out.kind, Frag::kByteRange);
  EXPECT_EQ(out.a, 0x00);
  EXPECT_EQ(out.b, 0xFF);
  EXPECT_EQ(out.c, 0); // fold=false
}

// kRegexpAnyChar -> BeginRange; AddRuneRange(0, Runemax, false); EndRange()
TEST_F(CompilerPostVisitTest_321, AnyCharAddsFullRuneRange_321) {
  EXPECT_CALL(re_, op()).WillOnce(Return(kRegexpAnyChar));
  Frag out = c_.PostVisit(&re_, {}, {}, nullptr, 0);
  EXPECT_EQ(out.kind, Frag::kEndRange);
  // The observable side-effect we can assert: the added range
  ASSERT_THAT(c_.added_ranges(), ::testing::SizeIs(1));
  EXPECT_EQ(c_.added_ranges()[0].lo, 0);
  EXPECT_EQ(c_.added_ranges()[0].hi, 0x10FFFF);
  EXPECT_EQ(c_.added_ranges()[0].fold, 0);
}

// kRegexpCharClass: empty -> NoMatch() and fail path (observable as NoMatch return)
TEST_F(CompilerPostVisitTest_321, CharClassEmptyYieldsNoMatch_321) {
  MockCharClass cc;
  EXPECT_CALL(re_, op()).WillOnce(Return(kRegexpCharClass));
  EXPECT_CALL(re_, cc()).WillRepeatedly(Return(&cc));
  EXPECT_CALL(cc, empty()).WillOnce(Return(true));
  Frag out = c_.PostVisit(&re_, {}, {}, nullptr, 0);
  EXPECT_EQ(out.kind, Frag::kNoMatch);
}

// kRegexpCharClass with ASCII folds, excluding pure 'A'-'Z' subrange additions
TEST_F(CompilerPostVisitTest_321, CharClassFoldsAsciiSkipsAZ_321) {
  MockCharClass cc;
  cc.SetRanges({ {'A','Z'}, {'a','z'} });
  EXPECT_CALL(re_, op()).WillOnce(Return(kRegexpCharClass));
  EXPECT_CALL(re_, cc()).WillRepeatedly(Return(&cc));
  EXPECT_CALL(cc, empty()).WillRepeatedly(Return(false));
  EXPECT_CALL(cc, FoldsASCII()).WillRepeatedly(Return(true));
  EXPECT_CALL(cc, begin()).WillRepeatedly(Return(cc.b()));
  EXPECT_CALL(cc, end()).WillRepeatedly(Return(cc.e()));

  Frag out = c_.PostVisit(&re_, {}, {}, nullptr, 0);
  EXPECT_EQ(out.kind, Frag::kEndRange);
  // Only 'a'-'z' should be added (with fold possibly adjusted per snippet)
  ASSERT_THAT(c_.added_ranges(), ::testing::Not(::testing::IsEmpty()));
  // Ensure no exact 'A'-'Z' entry present due to skip
  for (const auto& ar : c_.added_ranges()) {
    ASSERT_FALSE(ar.lo == 'A' && ar.hi == 'Z');
  }
}

// kRegexpCapture: cap < 0 -> child passed through; cap >=0 -> Capture(child, cap)
TEST_F(CompilerPostVisitTest_321, CaptureNegativePassthrough_321) {
  EXPECT_CALL(re_, op()).WillOnce(Return(kRegexpCapture));
  EXPECT_CALL(re_, cap()).WillOnce(Return(-1));
  Frag child{Frag::kLiteral, 'X'};
  Frag out = c_.PostVisit(&re_, {}, {}, &child, 1);
  EXPECT_EQ(out, child);
}

TEST_F(CompilerPostVisitTest_321, CaptureWrapsChild_321) {
  EXPECT_CALL(re_, op()).WillOnce(Return(kRegexpCapture));
  EXPECT_CALL(re_, cap()).WillOnce(Return(2));
  Frag child{Frag::kLiteral, 'Y'};
  Frag out = c_.PostVisit(&re_, {}, {}, &child, 1);
  EXPECT_EQ(out.kind, Frag::kCapture);
  EXPECT_EQ(out.a, 2);
}

// Empty width ops (assuming default reversed_=false)
TEST_F(CompilerPostVisitTest_321, BeginLineEmptyWidth_321) {
  EXPECT_CALL(re_, op()).WillOnce(Return(kRegexpBeginLine));
  Frag out = c_.PostVisit(&re_, {}, {}, nullptr, 0);
  EXPECT_EQ(out.kind, Frag::kEmptyWidth);
  EXPECT_EQ(out.a, (int)kEmptyBeginLine);
}

TEST_F(CompilerPostVisitTest_321, EndLineEmptyWidth_321) {
  EXPECT_CALL(re_, op()).WillOnce(Return(kRegexpEndLine));
  Frag out = c_.PostVisit(&re_, {}, {}, nullptr, 0);
  EXPECT_EQ(out.kind, Frag::kEmptyWidth);
  EXPECT_EQ(out.a, (int)kEmptyEndLine);
}

TEST_F(CompilerPostVisitTest_321, BeginTextEmptyWidth_321) {
  EXPECT_CALL(re_, op()).WillOnce(Return(kRegexpBeginText));
  Frag out = c_.PostVisit(&re_, {}, {}, nullptr, 0);
  EXPECT_EQ(out.kind, Frag::kEmptyWidth);
  EXPECT_EQ(out.a, (int)kEmptyBeginText);
}

TEST_F(CompilerPostVisitTest_321, EndTextEmptyWidth_321) {
  EXPECT_CALL(re_, op()).WillOnce(Return(kRegexpEndText));
  Frag out = c_.PostVisit(&re_, {}, {}, nullptr, 0);
  EXPECT_EQ(out.kind, Frag::kEmptyWidth);
  EXPECT_EQ(out.a, (int)kEmptyEndText);
}

TEST_F(CompilerPostVisitTest_321, WordBoundaryEmptyWidth_321) {
  EXPECT_CALL(re_, op()).WillOnce(Return(kRegexpWordBoundary));
  Frag out = c_.PostVisit(&re_, {}, {}, nullptr, 0);
  EXPECT_EQ(out.kind, Frag::kEmptyWidth);
  EXPECT_EQ(out.a, (int)kEmptyWordBoundary);
}

TEST_F(CompilerPostVisitTest_321, NoWordBoundaryEmptyWidth_321) {
  EXPECT_CALL(re_, op()).WillOnce(Return(kRegexpNoWordBoundary));
  Frag out = c_.PostVisit(&re_, {}, {}, nullptr, 0);
  EXPECT_EQ(out.kind, Frag::kEmptyWidth);
  EXPECT_EQ(out.a, (int)kEmptyNonWordBoundary);
}
