// File: empty_string_walker_shortvisit_test_221.cc

#include <gtest/gtest.h>

// We include the implementation file to ensure the test can see the class.
// If your build already compiles this .cc into a library, switch this to
// include the proper header instead (e.g., #include "re2/mimics_pcre.h")
// to avoid multiple-definition issues in your build system.
#include "re2/mimics_pcre.cc"

namespace {

// Forward-declare re2::Regexp to satisfy the pointer type in the interface.
// The function under test does not require a concrete Regexp instance for
// observable behavior, based on the provided interface.
namespace re2 {
class Regexp;
}  // namespace re2

using re2::EmptyStringWalker;
using re2::Regexp;

class EmptyStringWalkerTest_221 : public ::testing::Test {
protected:
  EmptyStringWalker walker_;
};

// [Behavior] ShortVisit returns the boolean input as-is (true path).
TEST_F(EmptyStringWalkerTest_221, ShortVisit_ReturnsTrueWhenInputTrue_221) {
  Regexp* re = nullptr;  // Parameter is unused per interface surface.
  const bool in = true;

  bool out = walker_.ShortVisit(re, in);

  EXPECT_TRUE(out);
}

// [Behavior] ShortVisit returns the boolean input as-is (false path).
TEST_F(EmptyStringWalkerTest_221, ShortVisit_ReturnsFalseWhenInputFalse_221) {
  Regexp* re = nullptr;  // Parameter is unused per interface surface.
  const bool in = false;

  bool out = walker_.ShortVisit(re, in);

  EXPECT_FALSE(out);
}

// [Boundary] Passing a null Regexp* does not alter the observable result.
TEST_F(EmptyStringWalkerTest_221, ShortVisit_IgnoresRegexpPointer_221) {
  Regexp* re_null = nullptr;

  EXPECT_TRUE(walker_.ShortVisit(re_null, true));
  EXPECT_FALSE(walker_.ShortVisit(re_null, false));
}

}  // namespace
