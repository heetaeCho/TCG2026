// File: prefilter_info_test_540.cc

#include <gtest/gtest.h>
#include "re2/prefilter.h"  // Assumes Prefilter::Info is visible via this header

namespace re2 {

class PrefilterInfoTest_540 : public ::testing::Test {};

// [540] Verifies the default-constructed Info reports its exactness state consistently.
TEST_F(PrefilterInfoTest_540, DefaultIsStableAndConsistent_540) {
  Prefilter::Info info;

  // Call is_exact() multiple times to ensure it is callable and stable (const).
  bool first = info.is_exact();
  bool second = info.is_exact();
  EXPECT_EQ(first, second);
}

// [540] Each factory should return a non-null Info pointer that is usable via the public API.
// We do NOT assume specific semantics (black box): we only verify construction succeeds
// and the object tolerates basic observable operations without crashing.
TEST_F(PrefilterInfoTest_540, FactoriesReturnUsableObjects_540) {
  // EmptyString
  {
    std::unique_ptr<Prefilter::Info> p(Prefilter::Info::EmptyString());
    ASSERT_NE(nullptr, p.get());
    // Observable calls (no assumptions on return values)
    (void)p->is_exact();
    (void)p->ToString();
    (void)p->TakeMatch();
  }

  // NoMatch
  {
    std::unique_ptr<Prefilter::Info> p(Prefilter::Info::NoMatch());
    ASSERT_NE(nullptr, p.get());
    (void)p->is_exact();
    (void)p->ToString();
    (void)p->TakeMatch();
  }

  // AnyMatch
  {
    std::unique_ptr<Prefilter::Info> p(Prefilter::Info::AnyMatch());
    ASSERT_NE(nullptr, p.get());
    (void)p->is_exact();
    (void)p->ToString();
    (void)p->TakeMatch();
  }

  // AnyCharOrAnyByte
  {
    std::unique_ptr<Prefilter::Info> p(Prefilter::Info::AnyCharOrAnyByte());
    ASSERT_NE(nullptr, p.get());
    (void)p->is_exact();
    (void)p->ToString();
    (void)p->TakeMatch();
  }

  // Literal (Unicode)
  {
    std::unique_ptr<Prefilter::Info> p(Prefilter::Info::Literal(static_cast<Rune>('A')));
    ASSERT_NE(nullptr, p.get());
    (void)p->is_exact();
    (void)p->ToString();
    (void)p->TakeMatch();
  }

  // LiteralLatin1
  {
    std::unique_ptr<Prefilter::Info> p(Prefilter::Info::LiteralLatin1(static_cast<Rune>('B')));
    ASSERT_NE(nullptr, p.get());
    (void)p->is_exact();
    (void)p->ToString();
    (void)p->TakeMatch();
  }
}

// [540] Binary combinators should return usable (non-null) objects when given valid inputs.
// We deliberately avoid asserting any internal semantics; we only verify observable construction.
TEST_F(PrefilterInfoTest_540, CombinatorsYieldUsableObjects_540) {
  std::unique_ptr<Prefilter::Info> a(Prefilter::Info::Literal(static_cast<Rune>('x')));
  std::unique_ptr<Prefilter::Info> b(Prefilter::Info::Literal(static_cast<Rune>('y')));
  ASSERT_NE(nullptr, a.get());
  ASSERT_NE(nullptr, b.get());

  // Alt
  {
    std::unique_ptr<Prefilter::Info> r(Prefilter::Info::Alt(a.get(), b.get()));
    ASSERT_NE(nullptr, r.get());
    (void)r->is_exact();
    (void)r->ToString();
    (void)r->TakeMatch();
  }

  // Concat
  {
    std::unique_ptr<Prefilter::Info> r(Prefilter::Info::Concat(a.get(), b.get()));
    ASSERT_NE(nullptr, r.get());
    (void)r->is_exact();
    (void)r->ToString();
    (void)r->TakeMatch();
  }

  // And
  {
    std::unique_ptr<Prefilter::Info> r(Prefilter::Info::And(a.get(), b.get()));
    ASSERT_NE(nullptr, r.get());
    (void)r->is_exact();
    (void)r->ToString();
    (void)r->TakeMatch();
  }
}

// [540] Unary quantifiers should return usable (non-null) objects when given valid input.
TEST_F(PrefilterInfoTest_540, QuantifiersYieldUsableObjects_540) {
  std::unique_ptr<Prefilter::Info> base(Prefilter::Info::Literal(static_cast<Rune>('z')));
  ASSERT_NE(nullptr, base.get());

  // Star
  {
    std::unique_ptr<Prefilter::Info> r(Prefilter::Info::Star(base.get()));
    ASSERT_NE(nullptr, r.get());
    (void)r->is_exact();
    (void)r->ToString();
    (void)r->TakeMatch();
  }

  // Plus
  {
    std::unique_ptr<Prefilter::Info> r(Prefilter::Info::Plus(base.get()));
    ASSERT_NE(nullptr, r.get());
    (void)r->is_exact();
    (void)r->ToString();
    (void)r->TakeMatch();
  }

  // Quest (?)
  {
    std::unique_ptr<Prefilter::Info> r(Prefilter::Info::Quest(base.get()));
    ASSERT_NE(nullptr, r.get());
    (void)r->is_exact();
    (void)r->ToString();
    (void)r->TakeMatch();
  }
}

// [540] Basic lifecycle: Ensure Info can be created and destroyed without leaks or crashes,
// and its observable API remains callable after simple transformations.
TEST_F(PrefilterInfoTest_540, LifecycleAndBasicAPI_540) {
  // Build with a couple of combinators to exercise more code paths.
  std::unique_ptr<Prefilter::Info> a(Prefilter::Info::Literal(static_cast<Rune>('m')));
  std::unique_ptr<Prefilter::Info> b(Prefilter::Info::LiteralLatin1(static_cast<Rune>('n')));
  ASSERT_NE(nullptr, a.get());
  ASSERT_NE(nullptr, b.get());

  std::unique_ptr<Prefilter::Info> ab(Prefilter::Info::Concat(a.get(), b.get()));
  ASSERT_NE(nullptr, ab.get());

  std::unique_ptr<Prefilter::Info> alt(Prefilter::Info::Alt(ab.get(), Prefilter::Info::AnyMatch()));
  ASSERT_NE(nullptr, alt.get());

  // Observable API usage; we do not assume specific values.
  (void)alt->is_exact();
  (void)alt->ToString();

  // TakeMatch returns a Prefilter* (may be nullptr or non-null; both are valid black-box outcomes).
  Prefilter* pm = alt->TakeMatch();
  // We only check type-safety by allowing any pointer value.
  (void)pm;

  // No explicit delete needed for pm—ownership semantics are not specified here.
  // We avoid deleting pm to respect possible ownership transfer rules.
}

}  // namespace re2
