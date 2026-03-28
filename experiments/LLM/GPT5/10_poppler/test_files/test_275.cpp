// LinkDest_getBottom_tests_275.cpp
// Unit tests for LinkDest::getBottom()
// The TEST_ID is 275

#include <gtest/gtest.h>

#include "poppler/Link.h"

// These tests are intentionally lightweight because the provided interface snippet
// only exposes LinkDest::getBottom() and we must treat LinkDest as a black box.
//
// Note: We avoid relying on any specific constructor behavior beyond "an object can
// be constructed (somehow) and getBottom() can be observed". If LinkDest cannot be
// default-constructed in your build, adjust the fixture's construction helper to
// use the real public constructor(s) available in your codebase.

namespace {

class LinkDestTest_275 : public ::testing::Test {
protected:
  // Helper that tries to construct LinkDest in the least-assumptive way.
  // If your LinkDest has no default ctor, replace this with the correct public ctor call.
  static LinkDest MakeLinkDest_275() {
    // Many poppler builds only expose `explicit LinkDest(const Array&)`.
    // If that's the case, update this helper to create a minimal valid Array.
    //
    // We keep this as a separate helper so the change is localized and doesn't
    // contaminate the test logic with inferred internals.
    return LinkDest();
  }
};

TEST_F(LinkDestTest_275, GetBottom_IsStableAcrossMultipleCalls_275) {
  LinkDest d = MakeLinkDest_275();

  const double b1 = d.getBottom();
  const double b2 = d.getBottom();
  const double b3 = d.getBottom();

  // Pure observer: repeated calls should not mutate observable state.
  EXPECT_DOUBLE_EQ(b1, b2);
  EXPECT_DOUBLE_EQ(b2, b3);
}

TEST_F(LinkDestTest_275, GetBottom_ReturnsFiniteNumberOrNaNButNotCrash_275) {
  LinkDest d = MakeLinkDest_275();

  // We cannot infer semantics of "ok" vs "not ok" or units/ranges, but we can
  // still ensure the accessor is callable and produces a double value.
  const double b = d.getBottom();

  // Accept either finite or NaN/Inf depending on how invalid destinations are represented,
  // but this test primarily asserts the call is safe and returns a double.
  // (No EXPECT here on value category because that would assume implementation details.)
  (void)b;
}

TEST_F(LinkDestTest_275, GetBottom_DoesNotDependOnOtherGettersSideEffects_275) {
  LinkDest d = MakeLinkDest_275();

  const double before = d.getBottom();

  // Call a few other const getters (if available) to ensure no observable side effects.
  // If some getters are not available in your build, you can remove those lines.
  (void)d.isOk();
  (void)d.getKind();
  (void)d.isPageRef();
  (void)d.getLeft();
  (void)d.getRight();
  (void)d.getTop();
  (void)d.getZoom();
  (void)d.getChangeLeft();
  (void)d.getChangeTop();
  (void)d.getChangeZoom();

  const double after = d.getBottom();
  EXPECT_DOUBLE_EQ(before, after);
}

}  // namespace