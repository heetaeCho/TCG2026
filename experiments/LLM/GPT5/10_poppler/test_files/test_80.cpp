// TEST_ID: 80
// File: test_object_isdict_80.cpp
//
// Unit tests for poppler::Object::isDict() const
// Interface under test (partial):
//   bool Object::isDict() const { CHECK_NOT_DEAD; return type == objDict; }
//
// Notes:
// - Treat Object as a black box: only exercise public constructors / public API.
// - We avoid relying on any private state or internal layout.
// - "Exceptional/error cases": CHECK_NOT_DEAD likely aborts on "dead" objects; death tests are used.

#include <gtest/gtest.h>

#include "poppler/Object.h"

// Poppler's CHECK_NOT_DEAD is typically implemented via an assert-like abort.
// Death tests require gtest death test support; they are safe to include even if
// they get compiled out in release builds (they may then be skipped / not die).
// If your build disables assertions, these tests may become non-fatal and will
// need to be adjusted in your environment.

namespace {

TEST(ObjectIsDictTest_80, DefaultConstructedIsNotDict_80) {
  Object o;
  EXPECT_FALSE(o.isDict());
}

TEST(ObjectIsDictTest_80, BoolConstructedIsNotDict_80) {
  Object o_true(true);
  Object o_false(false);
  EXPECT_FALSE(o_true.isDict());
  EXPECT_FALSE(o_false.isDict());
}

TEST(ObjectIsDictTest_80, IntConstructedIsNotDict_80) {
  Object o0(0);
  Object o1(1);
  Object ominus(-1);
  EXPECT_FALSE(o0.isDict());
  EXPECT_FALSE(o1.isDict());
  EXPECT_FALSE(ominus.isDict());
}

TEST(ObjectIsDictTest_80, RealConstructedIsNotDict_80) {
  Object o0(0.0);
  Object o1(1.25);
  Object ominus(-3.5);
  EXPECT_FALSE(o0.isDict());
  EXPECT_FALSE(o1.isDict());
  EXPECT_FALSE(ominus.isDict());
}

TEST(ObjectIsDictTest_80, NullStaticIsNotDict_80) {
  Object n = Object::null();
  EXPECT_FALSE(n.isDict());
}

TEST(ObjectIsDictTest_80, ErrorStaticIsNotDict_80) {
  Object e = Object::error();
  EXPECT_FALSE(e.isDict());
}

TEST(ObjectIsDictTest_80, EofStaticIsNotDict_80) {
  Object e = Object::eof();
  EXPECT_FALSE(e.isDict());
}

TEST(ObjectIsDictTest_80, MovedFromObjectRemainsCallableOrDiesPredictably_80) {
  // Boundary/robustness around move operations.
  // We don't assume anything about moved-from state beyond it being valid to destroy.
  Object src(123);
  Object dst(std::move(src));

  // dst should behave like a non-dict (it was created from int).
  EXPECT_FALSE(dst.isDict());

  // For src (moved-from), behavior is implementation-defined.
  // We only assert that calling isDict() does not crash the test process in
  // non-assert builds; in assert builds it should still generally be safe unless
  // moved-from becomes "dead". So we just call it.
  (void)src.isDict();
}

TEST(ObjectIsDictDeathTest_80, IsDictOnDeadObjectCausesDeath_80) {
  // Exceptional case (observable): CHECK_NOT_DEAD is expected to terminate
  // when called on an object whose type is objDead.
  //
  // We can create a "dead" object by moving into it and then destroying its content
  // indirectly; however we must not touch internals. The public API includes a
  // destructor and move assignment; Poppler commonly marks moved-from as objDead.
  //
  // So we attempt to provoke "dead" via move assignment, then call isDict().
  // If your build doesn't make moved-from "dead" (or disables CHECK_NOT_DEAD),
  // this test may need to be disabled in your CI configuration.
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";

  Object a(1);
  Object b(2);

  b = std::move(a);

  // If 'a' becomes "dead" after move, isDict should trigger CHECK_NOT_DEAD.
  // Use ASSERT_DEATH to validate termination without assuming message text.
  ASSERT_DEATH({ (void)a.isDict(); }, "");
}

} // namespace