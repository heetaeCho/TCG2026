// File: html_font_getlinesize_test_2623.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "TestProjects/poppler/utils/HtmlFonts.h"

namespace {

class HtmlFontTest_2623 : public ::testing::Test {};

// Compile-time interface verification: return type is int.
TEST_F(HtmlFontTest_2623, GetLineSize_ReturnTypeIsInt_2623) {
  static_assert(std::is_same_v<decltype(std::declval<const HtmlFont&>().getLineSize()), int>,
                "HtmlFont::getLineSize() must return int");
  SUCCEED();
}

// Compile-time interface verification: callable on const object and is a const member function.
TEST_F(HtmlFontTest_2623, GetLineSize_IsCallableOnConst_2623) {
  // If getLineSize is const, calling it on a const HtmlFont& is well-formed (checked by decltype above).
  static_assert(std::is_invocable_r_v<int, decltype(&HtmlFont::getLineSize), const HtmlFont*>,
                "HtmlFont::getLineSize() must be invocable on const HtmlFont* and return int");
  SUCCEED();
}

// Runtime behavior verification when possible: if HtmlFont is default-constructible in this build,
// verify the call works and yields a stable result across repeated calls.
TEST_F(HtmlFontTest_2623, GetLineSize_RuntimeSmokeIfDefaultConstructible_2623) {
  if constexpr (std::is_default_constructible_v<HtmlFont>) {
    const HtmlFont font{};
    const int v1 = font.getLineSize();
    const int v2 = font.getLineSize();
    EXPECT_EQ(v1, v2);
  } else {
    GTEST_SKIP() << "HtmlFont is not default-constructible; creating an instance requires Poppler "
                    "types (GfxFont/GfxRGB) not constructible from this black-box interface test.";
  }
}

}  // namespace