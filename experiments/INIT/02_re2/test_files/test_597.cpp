// File: re2_constructor_string_view_test_597.cc

#include <gtest/gtest.h>
#include "re2/re2.h"
#include "absl/strings/string_view.h"

using re2::RE2;

class RE2CtorTest_597 : public ::testing::Test {};

// Normal operation: valid simple pattern via absl::string_view
TEST_F(RE2CtorTest_597, ConstructsWithStringView_StoresPatternAndOk_597) {
  std::string src = "a+b";
  absl::string_view sv(src);
  RE2 re(sv);

  // Observable behavior through the public interface
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "a+b");
}

// Boundary condition: empty pattern (should be constructible and typically valid)
TEST_F(RE2CtorTest_597, EmptyPattern_IsOkAndPatternAccessible_597) {
  std::string src = "";
  absl::string_view sv(src);
  RE2 re(sv);

  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "");
}

// Exceptional/error case: syntactically invalid regex (e.g., unmatched parenthesis)
TEST_F(RE2CtorTest_597, InvalidPattern_SetsNotOkAndProvidesError_597) {
  std::string src = "(";  // commonly invalid in regex syntax
  absl::string_view sv(src);
  RE2 re(sv);

  EXPECT_FALSE(re.ok());
  // Error text should be observable via the interface; exact contents are not assumed.
  // We only assert it's non-empty to confirm an error is exposed.
  EXPECT_FALSE(re.error().empty());
}

// Lifetime safety: constructing from a temporary backing string for string_view
// should leave the RE2 object usable via its public API (no dangling references).
TEST_F(RE2CtorTest_597, StringViewFromTempString_LifetimeSafety_597) {
  RE2 re([&]() {
    std::string temp = "hello.*world";
    return absl::string_view(temp);
  }());  // temp string destroyed after this expression

  // If the constructor mishandled ownership, accessing the pattern or ok()
  // would likely fail or produce undefined behavior. We only check public effects.
  (void)re.pattern();  // Access should be safe
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "hello.*world");
}
