// TEST_ID: 91
// File: Object_getBool_test_91.cpp
//
// Unit tests for poppler::Object::getBool()
// Interface under test (partial):
//   bool Object::getBool() const { OBJECT_TYPE_CHECK(objBool); return booln; }
//
// Notes:
// - We treat Object as a black box.
// - We only assert observable behavior: correct return value for bool Objects.
// - For non-bool Objects, OBJECT_TYPE_CHECK may assert/abort/throw depending on build
//   configuration. We provide a death test that is compiled/enabled only when
//   death tests are supported (and not on platforms where they are flaky).
//
// If your build defines a specific behavior for OBJECT_TYPE_CHECK (e.g., throws),
// you can adapt the "NonBool_DeathOrFailure" test accordingly.

#include <gtest/gtest.h>

#include "poppler/Object.h"

namespace {

class ObjectGetBoolTest_91 : public ::testing::Test {};

TEST_F(ObjectGetBoolTest_91, ReturnsTrueWhenConstructedWithTrue_91)
{
  const Object o(true);
  EXPECT_TRUE(o.getBool());
}

TEST_F(ObjectGetBoolTest_91, ReturnsFalseWhenConstructedWithFalse_91)
{
  const Object o(false);
  EXPECT_FALSE(o.getBool());
}

TEST_F(ObjectGetBoolTest_91, ConstObjectReturnsSameValue_91)
{
  const Object o(true);
  const Object &cref = o;
  EXPECT_TRUE(cref.getBool());
}

// Boundary-ish: make sure repeated calls are stable/consistent (no mutation observable).
TEST_F(ObjectGetBoolTest_91, MultipleCallsReturnSameValue_91)
{
  const Object o(false);
  EXPECT_FALSE(o.getBool());
  EXPECT_FALSE(o.getBool());
  EXPECT_FALSE(o.getBool());
}

#if GTEST_HAS_DEATH_TEST
// Error/exceptional case (observable only if OBJECT_TYPE_CHECK fails loudly).
// We avoid assuming *how* it fails; we only check that it terminates.
// If your build uses exceptions instead of abort/assert, replace this with EXPECT_THROW.
TEST_F(ObjectGetBoolTest_91, NonBool_DeathOrFailure_91)
{
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";

  const Object notBool(123); // int Object
  EXPECT_DEATH(
      {
        // NOLINTNEXTLINE(clang-analyzer-deadcode.DeadStores)
        (void)notBool.getBool();
      },
      ".*");
}
#endif

} // namespace