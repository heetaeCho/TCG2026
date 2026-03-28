// File: regexp_name_test_159.cc
#include "re2/regexp.h"
#include <gtest/gtest.h>

using re2::Regexp;

class RegexpNameTest_159 : public ::testing::Test {
protected:
  // Helper to safely decref a Regexp* if non-null.
  static void SafeDecref(Regexp* re) {
    if (re) re->Decref();
  }
};

// Normal operation: an unnamed capture created via the factory should have no name.
TEST_F(RegexpNameTest_159, UnnamedCaptureReturnsNullName_159) {
  // Build: capture( literal('a') )
  Regexp* lit = Regexp::NewLiteral('a', /*flags=*/0);
  ASSERT_NE(lit, nullptr) << "NewLiteral should return a valid node";

  Regexp* cap = Regexp::Capture(lit, /*flags=*/0, /*cap=*/1);
  ASSERT_NE(cap, nullptr) << "Capture should return a valid node";

  // name() is only valid on capture nodes; the factory created one.
  // For an unnamed capture, we expect no name to be present (nullptr).
  EXPECT_EQ(cap->name(), nullptr);

  // Clean up: only decref the top-level if ownership of sub was transferred.
  // The API is refcounted; Decref() on the top node is the correct visible action.
  RegexpNameTest_159::SafeDecref(cap);
}

// Boundary / structure check: nested captures both unnamed -> both names should be null.
TEST_F(RegexpNameTest_159, NestedUnnamedCapturesBothNull_159) {
  // inner = capture(literal('x'))
  Regexp* inner_lit = Regexp::NewLiteral('x', /*flags=*/0);
  ASSERT_NE(inner_lit, nullptr);

  Regexp* inner_cap = Regexp::Capture(inner_lit, /*flags=*/0, /*cap=*/1);
  ASSERT_NE(inner_cap, nullptr);

  // outer = capture(inner)
  Regexp* outer_cap = Regexp::Capture(inner_cap, /*flags=*/0, /*cap=*/2);
  ASSERT_NE(outer_cap, nullptr);

  // Both captures are unnamed when built via the factory.
  EXPECT_EQ(outer_cap->name(), nullptr);

  // Access the inner capture through the public tree interface.
  ASSERT_GT(outer_cap->nsub(), 0);
  Regexp** subs = outer_cap->sub();
  ASSERT_NE(subs, nullptr);
  Regexp* child = subs[0];

  // Sanity: child should itself be a capture node, making name() valid to call.
  // We avoid asserting on op() values beyond using the public API behavior.
  // Calling name() is the observable we care about:
  EXPECT_EQ(child->name(), nullptr);

  RegexpNameTest_159::SafeDecref(outer_cap);
}

// Robustness: capture around a multi-rune literal string remains unnamed -> null name.
// (Ensures behavior isn’t dependent on sub-kind.)
TEST_F(RegexpNameTest_159, UnnamedCaptureOverLiteralStringNullName_159) {
  // Build a small rune array "ab".
  int nrunes = 2;
  Rune runes[2] = { 'a', 'b' };

  Regexp* litstr = Regexp::LiteralString(runes, nrunes, /*flags=*/0);
  ASSERT_NE(litstr, nullptr);

  Regexp* cap = Regexp::Capture(litstr, /*flags=*/0, /*cap=*/1);
  ASSERT_NE(cap, nullptr);

  EXPECT_EQ(cap->name(), nullptr);

  RegexpNameTest_159::SafeDecref(cap);
}
