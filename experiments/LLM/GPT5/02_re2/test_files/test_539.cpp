// File: ./TestProjects/re2/testing/prefilter_info_test_539.cc

#include "gtest/gtest.h"
#include "re2/prefilter.h"  // Public interface under test

namespace re2 {

class PrefilterInfoTest_539 : public ::testing::Test {
protected:
  // Utility to safely dispose Info* if destructor is public and ownership is clear.
  // We avoid deleting Prefilter* returned by TakeMatch(), since ownership is not
  // documented here; we only observe that a pointer is (non-)null.
  static void SafeDeleteInfo(Prefilter::Info* p) {
    // Treat as black box; only delete Info* created by static factories when non-null.
    delete p;
  }
};

// --- Normal operation: basic construction and observable state ---
TEST_F(PrefilterInfoTest_539, DefaultIsNotExact_539) {
  // Construct directly through public constructor and observe public accessors.
  Prefilter::Info info;
  // Observable behavior: is_exact() should be a valid call returning a bool.
  // We assert the specific value false based on public, observable state.
  EXPECT_FALSE(info.is_exact());
  // exact() must return a reference; merely take the address to confirm it exists.
  auto& sset_ref = info.exact();
  (void)&sset_ref;  // No behavioral assumption beyond existence.
}

// --- Factory methods: they should produce usable (non-null) objects with strings ---
TEST_F(PrefilterInfoTest_539, BasicFactoriesProduceUsableObjects_539) {
  Prefilter::Info* empty = Prefilter::Info::EmptyString();
  ASSERT_NE(nullptr, empty);
  EXPECT_FALSE(empty->ToString().empty());
  SafeDeleteInfo(empty);

  Prefilter::Info* anymatch = Prefilter::Info::AnyMatch();
  ASSERT_NE(nullptr, anymatch);
  EXPECT_FALSE(anymatch->ToString().empty());
  SafeDeleteInfo(anymatch);

  Prefilter::Info* anychar = Prefilter::Info::AnyCharOrAnyByte();
  ASSERT_NE(nullptr, anychar);
  EXPECT_FALSE(anychar->ToString().empty());
  SafeDeleteInfo(anychar);

  Prefilter::Info* lit = Prefilter::Info::LiteralLatin1('x');
  ASSERT_NE(nullptr, lit);
  EXPECT_FALSE(lit->ToString().empty());
  SafeDeleteInfo(lit);
}

// --- Literal vs AnyMatch: ToString should be observable and different ---
TEST_F(PrefilterInfoTest_539, ToStringDiffersForDifferentShapes_539) {
  Prefilter::Info* a = Prefilter::Info::LiteralLatin1('a');
  Prefilter::Info* b = Prefilter::Info::AnyMatch();

  ASSERT_NE(nullptr, a);
  ASSERT_NE(nullptr, b);

  std::string sa = a->ToString();
  std::string sb = b->ToString();

  EXPECT_FALSE(sa.empty());
  EXPECT_FALSE(sb.empty());
  EXPECT_NE(sa, sb) << "Different factory shapes should yield different ToString outputs.";

  SafeDeleteInfo(a);
  SafeDeleteInfo(b);
}

// --- NoMatch: observable that it represents an unmatchable pattern ---
// We avoid asserting internal details; instead we check reasonable observable signals:
// - object exists
// - ToString is available
// - TakeMatch (if meaningful) may yield a nullptr (no actual prefilter to match)
TEST_F(PrefilterInfoTest_539, NoMatchHasNoExecutablePrefilter_539) {
  Prefilter::Info* nm = Prefilter::Info::NoMatch();
  ASSERT_NE(nullptr, nm);
  EXPECT_FALSE(nm->ToString().empty());

  Prefilter* pf = nm->TakeMatch();
  EXPECT_EQ(nullptr, pf) << "NoMatch should not yield a runnable Prefilter.";

  SafeDeleteInfo(nm);
}

// --- TakeMatch on matchable shapes should yield a Prefilter pointer (observable) ---
TEST_F(PrefilterInfoTest_539, TakeMatchYieldsPrefilterForMatchableShapes_539) {
  Prefilter::Info* any = Prefilter::Info::AnyMatch();
  ASSERT_NE(nullptr, any);
  Prefilter* pf_any = any->TakeMatch();
  EXPECT_NE(nullptr, pf_any);
  // Ownership of pf_any is intentionally not assumed here.
  SafeDeleteInfo(any);

  Prefilter::Info* lit = Prefilter::Info::LiteralLatin1('Q');
  ASSERT_NE(nullptr, lit);
  Prefilter* pf_lit = lit->TakeMatch();
  EXPECT_NE(nullptr, pf_lit);
  SafeDeleteInfo(lit);
}

// --- Unary combinators: Star / Plus / Quest should return usable objects ---
TEST_F(PrefilterInfoTest_539, UnaryCombinatorsProduceUsableObjects_539) {
  Prefilter::Info* base = Prefilter::Info::LiteralLatin1('z');
  ASSERT_NE(nullptr, base);

  Prefilter::Info* st = Prefilter::Info::Star(base);
  ASSERT_NE(nullptr, st);
  EXPECT_FALSE(st->ToString().empty());

  Prefilter::Info* pl = Prefilter::Info::Plus(st);
  ASSERT_NE(nullptr, pl);
  EXPECT_FALSE(pl->ToString().empty());

  Prefilter::Info* q  = Prefilter::Info::Quest(pl);
  ASSERT_NE(nullptr, q);
  EXPECT_FALSE(q->ToString().empty());

  // Clean up in reverse (we treat them as independent black-box objects).
  SafeDeleteInfo(q);
  SafeDeleteInfo(pl);
  SafeDeleteInfo(st);
  SafeDeleteInfo(base);
}

// --- Binary combinators: Alt / Concat / And produce usable results and distinct strings ---
TEST_F(PrefilterInfoTest_539, BinaryCombinatorsProduceDistinctStrings_539) {
  Prefilter::Info* x = Prefilter::Info::LiteralLatin1('x');
  Prefilter::Info* y = Prefilter::Info::LiteralLatin1('y');
  ASSERT_NE(nullptr, x);
  ASSERT_NE(nullptr, y);

  Prefilter::Info* alt = Prefilter::Info::Alt(x, y);
  Prefilter::Info* cat = Prefilter::Info::Concat(x, y);
  Prefilter::Info* andi = Prefilter::Info::And(x, y);

  ASSERT_NE(nullptr, alt);
  ASSERT_NE(nullptr, cat);
  ASSERT_NE(nullptr, andi);

  std::string sa = alt->ToString();
  std::string sc = cat->ToString();
  std::string sd = andi->ToString();

  EXPECT_FALSE(sa.empty());
  EXPECT_FALSE(sc.empty());
  EXPECT_FALSE(sd.empty());

  // We only assert that different combinators are observably different via ToString.
  EXPECT_NE(sa, sc);
  EXPECT_NE(sa, sd);
  EXPECT_NE(sc, sd);

  SafeDeleteInfo(andi);
  SafeDeleteInfo(cat);
  SafeDeleteInfo(alt);
  SafeDeleteInfo(y);
  SafeDeleteInfo(x);
}

// --- Boundary-ish inputs: non-ASCII rune vs Latin1 literal factories ---
TEST_F(PrefilterInfoTest_539, LiteralVsLatin1FactoriesBothUsable_539) {
  // Latin1 range input
  Prefilter::Info* l1 = Prefilter::Info::LiteralLatin1(static_cast<Rune>('~'));
  ASSERT_NE(nullptr, l1);
  EXPECT_FALSE(l1->ToString().empty());

  // Non-Latin1 (depending on Rune width) — still should return a valid object.
  // Choose a typical non-Latin1 code point (e.g., U+20AC EURO SIGN).
  Prefilter::Info* lit = Prefilter::Info::Literal(static_cast<Rune>(0x20AC));
  ASSERT_NE(nullptr, lit);
  EXPECT_FALSE(lit->ToString().empty());

  // These should be observably different.
  EXPECT_NE(l1->ToString(), lit->ToString());

  SafeDeleteInfo(lit);
  SafeDeleteInfo(l1);
}

}  // namespace re2
