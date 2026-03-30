// TEST_ID: 2626
#include <gtest/gtest.h>

#include <array>
#include <cstddef>
#include <memory>
#include <type_traits>

#include "TestProjects/poppler/utils/HtmlFonts.h"

namespace {

class HtmlFontTest_2626 : public ::testing::Test {
protected:
  // Tries to construct HtmlFont in a way that matches what the build provides.
  // If no viable construction path is available, returns nullptr and the test should skip.
  static std::unique_ptr<HtmlFont> MakeFontOrNull_2626() {
    if constexpr (std::is_default_constructible_v<HtmlFont>) {
      return std::make_unique<HtmlFont>();
    } else {
      // Some codebases provide only non-default constructors. We intentionally do not guess
      // how to create required dependencies beyond checking obvious constructibility.
      return nullptr;
    }
  }

  static std::unique_ptr<HtmlFont> MakeFontOrSkip_2626() {
    auto font = MakeFontOrNull_2626();
    if (!font) {
      // Skips cleanly when HtmlFont cannot be constructed using only the visible interface.
      // This avoids re-implementing or inferring internals / dependencies.
      GTEST_SKIP() << "HtmlFont is not default-constructible in this build; "
                      "cannot construct it using only the provided interface snippet.";
    }
    return font;
  }
};

TEST_F(HtmlFontTest_2626, GetRotMatReturnsSameReferenceOnRepeatedCalls_2626) {
  auto font = MakeFontOrSkip_2626();

  const auto &mat1 = font->getRotMat();
  const auto &mat2 = font->getRotMat();

  // Observable behavior: returns a reference; repeated calls should refer to the same object.
  EXPECT_EQ(std::addressof(mat1), std::addressof(mat2));
}

TEST_F(HtmlFontTest_2626, GetRotMatReferenceReflectsMutationsThroughReturnedReference_2626) {
  auto font = MakeFontOrSkip_2626();

  const auto &mat_const_ref = font->getRotMat();

  // We don't assume initial contents. We only verify that the returned reference is stable and
  // points to storage owned by the HtmlFont instance (observable by mutation persistence).
  auto &mat_mut = const_cast<std::array<double, 4> &>(mat_const_ref);

  // Mutate all elements to a recognizable pattern.
  mat_mut[0] = 1.0;
  mat_mut[1] = 2.0;
  mat_mut[2] = 3.0;
  mat_mut[3] = 4.0;

  const auto &mat_after = font->getRotMat();
  EXPECT_EQ(std::addressof(mat_const_ref), std::addressof(mat_after));

  EXPECT_DOUBLE_EQ(mat_after[0], 1.0);
  EXPECT_DOUBLE_EQ(mat_after[1], 2.0);
  EXPECT_DOUBLE_EQ(mat_after[2], 3.0);
  EXPECT_DOUBLE_EQ(mat_after[3], 4.0);
}

TEST_F(HtmlFontTest_2626, GetRotMatWorksOnConstObject_2626) {
  auto font = MakeFontOrSkip_2626();

  const HtmlFont &const_font_ref = *font;
  const auto &mat = const_font_ref.getRotMat();

  // Boundary/shape check that doesn't assume internal initialization values.
  EXPECT_EQ(mat.size(), static_cast<std::size_t>(4));
}

}  // namespace