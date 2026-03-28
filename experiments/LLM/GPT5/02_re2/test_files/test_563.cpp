// File: prefilter_fromre2_test_563.cc

#include "re2/prefilter.h"
#include "re2/re2.h"
#include "gtest/gtest.h"

namespace re2
{
// Minimal concrete type so we can hand out a Regexp* without touching internals.
class Regexp {};

// --- Test-controlled stubs --- //
// 1) Control what RE2::Regexp() returns, without accessing RE2 internals.
//    This definition satisfies the declaration in re2/re2.h.
static Regexp* g_fake_regexp_return = nullptr;
Regexp* RE2::Regexp() const {
  return g_fake_regexp_return;
}

// 2) Control what Prefilter::FromRegexp(...) returns.
//    We don't observe Prefilter's internals; we only validate pointer plumbing.
static Prefilter* g_fromregexp_return = nullptr;
Prefilter* Prefilter::FromRegexp(Regexp* /*unused*/) {
  return g_fromregexp_return;
}
}  // namespace re2

namespace {

// Helper to fabricate a non-null RE2* without invoking constructors.
// We never touch RE2 internals; our Regexp() ignores 'this' and is safe here.
re2::RE2* MakeRawRE2Pointer() {
  static alignas(re2::RE2) unsigned char storage[sizeof(re2::RE2)];
  return reinterpret_cast<re2::RE2*>(storage);
}

// -------------------- Tests --------------------

TEST(PrefilterFromRE2_563, ReturnsNullWhenInputIsNull_563) {
  // Act
  re2::Prefilter* out = re2::Prefilter::FromRE2(/*re2=*/nullptr);

  // Assert
  EXPECT_EQ(out, nullptr);
}

TEST(PrefilterFromRE2_563, ReturnsNullWhenRegexpIsNull_563) {
  // Arrange
  re2::g_fake_regexp_return = nullptr;  // RE2::Regexp() -> nullptr
  re2::RE2* fake_re2 = MakeRawRE2Pointer();

  // Act
  re2::Prefilter* out = re2::Prefilter::FromRE2(/*re2=*/fake_re2);

  // Assert
  EXPECT_EQ(out, nullptr);
}

TEST(PrefilterFromRE2_563, ForwardsResultFromFromRegexpWhenRegexpNonNull_563) {
  // Arrange
  static re2::Regexp dummy_regexp;                 // any non-null Regexp*
  re2::g_fake_regexp_return = &dummy_regexp;

  // Use a stable, distinct sentinel pointer to verify exact forwarding.
  // We never dereference this pointer; we only compare identity.
  static int sentinel;
  re2::Prefilter* expected =
      reinterpret_cast<re2::Prefilter*>(&sentinel);
  re2::g_fromregexp_return = expected;

  re2::RE2* fake_re2 = MakeRawRE2Pointer();

  // Act
  re2::Prefilter* out = re2::Prefilter::FromRE2(/*re2=*/fake_re2);

  // Assert
  EXPECT_EQ(out, expected);
}

}  // namespace
