// File: re2_regexp_cc_test_157.cc
#include <gtest/gtest.h>
#include "re2/regexp.h"
#include "re2/regexp_status.h"
#include "re2/charclass.h"  // For CharClassBuilder

using re2::Regexp;
using re2::RegexpStatus;
using re2::CharClass;
using re2::CharClassBuilder;

// A small helper for zero/neutral parse flags without relying on specific values.
static inline Regexp::ParseFlags ZF() {
  return static_cast<Regexp::ParseFlags>(0);
}

class RegexpCcTest_157 : public ::testing::Test {};

// ------------------------------------------------------------
// Normal operation: cc() on a parsed character class like "[a]".
// ------------------------------------------------------------
TEST_F(RegexpCcTest_157, ParseBracketClass_CcIsNonNull_157) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a]", ZF(), &status);
  ASSERT_NE(re, nullptr) << "Parse should succeed for a simple char class";
  // Ensure it's actually a CharClass node before calling cc().
  ASSERT_EQ(re->op(), re2::kRegexpCharClass);

  CharClass* cc = re->cc();
  EXPECT_NE(cc, nullptr) << "cc() should return a valid CharClass pointer";

  re->Decref();
}

// ------------------------------------------------------------
// Normal operation: building a CharClass via CharClassBuilder,
// then wrapping it with NewCharClass and verifying cc().
// ------------------------------------------------------------
TEST_F(RegexpCcTest_157, NewCharClass_ReturnsSamePointer_157) {
  // Build a simple [a-z] class.
  CharClassBuilder ccb;
  ccb.AddRange('a', 'z');
  CharClass* built = ccb.GetCharClass();  // Observable: returns a CharClass*

  Regexp* re = Regexp::NewCharClass(built, ZF());
  ASSERT_NE(re, nullptr);
  ASSERT_EQ(re->op(), re2::kRegexpCharClass);

  // Observable behavior: accessor returns the stored CharClass pointer.
  EXPECT_EQ(re->cc(), built);

  re->Decref();
}

// ------------------------------------------------------------
// Boundary/exceptional behavior: calling cc() when op != kRegexpCharClass
// should trigger the DCHECK in debug builds. We wrap this as a death test
// and compile-condition it out for non-debug builds.
// ------------------------------------------------------------
#if GTEST_HAS_DEATH_TEST && !defined(NDEBUG)
TEST_F(RegexpCcTest_157, NonCharClassAccessorDiesInDebug_157) {
  // Construct a non-charclass regexp, e.g., a literal 'x'.
  Regexp* lit = Regexp::NewLiteral('x', ZF());
  ASSERT_NE(lit, nullptr);
  ASSERT_NE(lit->op(), re2::kRegexpCharClass) << "Sanity check: must be non-charclass";

  // EXPECT/ASSERT_DEATH requires a regex for stderr message; empty matches anything.
  EXPECT_DEATH({ (void)lit->cc(); }, "");

  lit->Decref();
}
#endif  // GTEST_HAS_DEATH_TEST && !defined(NDEBUG)

// ------------------------------------------------------------
// Additional boundary: verify cc() remains stable (same pointer)
// across a simple Ref/Decref roundtrip observable via Incref().
// ------------------------------------------------------------
TEST_F(RegexpCcTest_157, CcPointerStableAcrossRefcountOps_157) {
  CharClassBuilder ccb;
  ccb.AddRange('0', '9');
  CharClass* built = ccb.GetCharClass();

  Regexp* re = Regexp::NewCharClass(built, ZF());
  ASSERT_NE(re, nullptr);
  ASSERT_EQ(re->op(), re2::kRegexpCharClass);

  CharClass* before = re->cc();
  ASSERT_NE(before, nullptr);

  // Observable interactions with public refcount API.
  re->Incref();
  CharClass* during = re->cc();
  EXPECT_EQ(during, before);

  re->Decref();  // balances Incref()
  CharClass* after = re->cc();
  EXPECT_EQ(after, before);

  re->Decref();  // final release
}
