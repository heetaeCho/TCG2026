// File: re2_regexp_newcharclass_test_348.cc
#include <gtest/gtest.h>

#include "re2/regexp.h"

namespace {

using re2::CharClass;
using re2::Regexp;
using re2::RegexpOp;

// Helper to call NewCharClass via the public interface.
// The headers declare a public static Regexp::NewCharClass(...).
// We call it statically to avoid depending on any particular constructor.
static Regexp* MakeCharClassRegexp(CharClass* cc, Regexp::ParseFlags flags) {
  return Regexp::NewCharClass(cc, flags);
}

// --- Tests ---

// Normal case: creates a Regexp node representing a char class and sets fields.
TEST(Regexp_NewCharClassTest_348, CreatesCharClassNodeAndSetsFields_348) {
  CharClass* cc = nullptr;  // treat CharClass as an opaque dependency (allowed)
  auto flags = static_cast<Regexp::ParseFlags>(0x1234);

  Regexp* re = MakeCharClassRegexp(cc, flags);
  ASSERT_NE(re, nullptr);

  // Observable behavior through public accessors only.
  EXPECT_EQ(re->op(), re2::kRegexpCharClass);
  EXPECT_EQ(re->parse_flags(), flags);
  EXPECT_EQ(re->cc(), cc);

  // Ownership of 're' and 'cc' is unspecified; do not delete to avoid guessing.
  // (Per constraints, we avoid relying on internal refcount/destruction behavior.)
}

// Boundary case: non-null CharClass* pointer is preserved exactly.
TEST(Regexp_NewCharClassTest_348, StoresProvidedCharClassPointer_348) {
  // Create an opaque, non-null pointer without invoking CharClass internals.
  alignas(alignof(CharClass)) unsigned char storage[sizeof(CharClass)];
  CharClass* fake_cc = reinterpret_cast<CharClass*>(storage);

  auto flags = static_cast<Regexp::ParseFlags>(0);
  Regexp* re = MakeCharClassRegexp(fake_cc, flags);
  ASSERT_NE(re, nullptr);

  EXPECT_EQ(re->op(), re2::kRegexpCharClass);
  EXPECT_EQ(re->cc(), fake_cc);
}

// Behavioral check: each call returns a distinct allocation (observable via pointer inequality).
TEST(Regexp_NewCharClassTest_348, ReturnsDistinctObjectsOnEachCall_348) {
  auto flags_a = static_cast<Regexp::ParseFlags>(0x1);
  auto flags_b = static_cast<Regexp::ParseFlags>(0x2);

  Regexp* re1 = MakeCharClassRegexp(nullptr, flags_a);
  Regexp* re2p = MakeCharClassRegexp(nullptr, flags_b);

  ASSERT_NE(re1, nullptr);
  ASSERT_NE(re2p, nullptr);
  EXPECT_NE(re1, re2p);

  // Do not attempt to free; ownership semantics are not part of the public contract here.
}

}  // namespace
