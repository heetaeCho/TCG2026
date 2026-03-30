// File: StructElement_isRubyAlignName_test_1763.cc

#include <gtest/gtest.h>

#include "Object.h"

// NOTE:
// isRubyAlignName is a static function in StructElement.cc (translation-unit local).
// To test it as a black box without re-implementing logic, we include the .cc here
// so the test TU can call the static function directly.
#include "StructElement.cc"

class RubyAlignNameTest_1763 : public ::testing::Test {};

TEST_F(RubyAlignNameTest_1763, ReturnsTrueForAllowedNames_1763)
{
  struct Case {
    const char *name;
  };
  const Case kCases[] = {{"Start"}, {"End"}, {"Center"}, {"Justify"}, {"Distribute"}};

  for (const auto &tc : kCases) {
    Object o(objName, tc.name);
    EXPECT_TRUE(isRubyAlignName(&o)) << "name=" << tc.name;
  }
}

TEST_F(RubyAlignNameTest_1763, ReturnsFalseForOtherNames_1763)
{
  struct Case {
    const char *name;
  };
  const Case kCases[] = {{"None"},
                         {"start"},       // case-sensitive check
                         {"START"},       // case-sensitive check
                         {"Middle"},      // plausible-but-not-allowed
                         {"Distributed"}, // similar-but-not-allowed
                         {""}};           // boundary: empty name

  for (const auto &tc : kCases) {
    Object o(objName, tc.name);
    EXPECT_FALSE(isRubyAlignName(&o)) << "name=" << tc.name;
  }
}

TEST_F(RubyAlignNameTest_1763, ReturnsFalseForNonNameObjects_1763)
{
  Object b(true);
  EXPECT_FALSE(isRubyAlignName(&b));

  Object i(123);
  EXPECT_FALSE(isRubyAlignName(&i));

  Object r(3.14159);
  EXPECT_FALSE(isRubyAlignName(&r));

  Object n = Object::null();
  EXPECT_FALSE(isRubyAlignName(&n));

  Object e = Object::error();
  EXPECT_FALSE(isRubyAlignName(&e));

  Object eof = Object::eof();
  EXPECT_FALSE(isRubyAlignName(&eof));
}

#if GTEST_HAS_DEATH_TEST
TEST_F(RubyAlignNameTest_1763, DeathOnNullPointer_1763)
{
  // Exceptional/error case (observable): passing nullptr is undefined; verify it fails fast.
  // (If the implementation changes to handle nullptr safely, adjust accordingly.)
  EXPECT_DEATH({ (void)isRubyAlignName(nullptr); }, ".*");
}
#endif