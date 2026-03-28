// File: re2_regexp_nrunes_test_161.cc

#include "re2/regexp.h"
#include <gtest/gtest.h>

namespace {

using re2::Regexp;

TEST(RegexpNrunesTest_161, LiteralStringReturnsCount_161) {
  // Arrange: build a LiteralString via the public factory.
  // We avoid any assumptions about internal fields; we only use the interface.
  Rune runes[] = { 'a', 'b', 'c' };
  const int kCount = static_cast<int>(sizeof(runes) / sizeof(runes[0]));
  auto flags = static_cast<Regexp::ParseFlags>(0);

  Regexp* re = Regexp::LiteralString(runes, kCount, flags);
  ASSERT_NE(re, nullptr) << "LiteralString factory should return a valid Regexp*";

  // Act + Assert: nrunes() should report the number passed to the factory.
  EXPECT_EQ(re->nrunes(), kCount);

  // Clean up per the public refcounting API.
  re->Decref();
}

TEST(RegexpNrunesTest_161, NrunesDCHECKsWhenNotLiteralString_161) {
  // Arrange: build a non-LiteralString node via a public factory.
  auto flags = static_cast<Regexp::ParseFlags>(0);
  Regexp* re = Regexp::NewLiteral('x', flags);
  ASSERT_NE(re, nullptr);

#ifndef NDEBUG
  // In debug builds, ABSL_DCHECK should fire because the precondition
  // (op_ == kRegexpLiteralString) isn’t met. We verify via a death test.
  EXPECT_DEATH(
      {
        // Calling nrunes() violates the documented precondition in debug mode.
        (void)re->nrunes();
      },
      "");  // Don’t assert on the message; just that it dies.
#else
  // In release builds, ABSL_DCHECK is a no-op; behavior is unspecified.
  // We do not assert anything about the return value to avoid inferring internals.
  SUCCEED();
#endif

  re->Decref();
}

}  // namespace
