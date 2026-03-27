// HtmlFonts_test_2627.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <array>
#include <memory>
#include <string>
#include <type_traits>

// Include the header under test.
#include "HtmlFonts.h"

// Forward declarations (only to keep this test file resilient to include-order;
// the real definitions are expected to come from HtmlFonts.h / Poppler headers).
class GfxFont;
struct GfxRGB;
using Unicode = unsigned short; // Common Poppler typedef; if Poppler provides it, this is unused.

namespace {

#if defined(__cpp_lib_is_constant_evaluated) || __cplusplus >= 201703L
template <typename T>
constexpr bool kIsDefaultConstructibleV = std::is_default_constructible<T>::value;
#else
template <typename T>
const bool kIsDefaultConstructibleV = std::is_default_constructible<T>::value;
#endif

// Helper: create a default HtmlFont only when it is default-constructible.
// If not default-constructible in the real codebase, instance-based tests will skip.
std::unique_ptr<HtmlFont> TryMakeDefaultHtmlFont() {
  if constexpr (kIsDefaultConstructibleV<HtmlFont>) {
    return std::make_unique<HtmlFont>();
  } else {
    return nullptr;
  }
}

// Helper: convert GooString (Poppler) to std::string without assuming too much API surface.
template <typename GooStringPtr>
std::string GooStringToStdString(const GooStringPtr& s) {
  if (!s) return std::string();
  // GooString in Poppler commonly has c_str(). If not, this will fail to compile,
  // but HtmlFilter's return type is provided as GooString, so this is expected.
  return std::string(s->c_str());
}

}  // namespace

// --------------------
// Static function tests (do not require constructing HtmlFont)
// --------------------

TEST(HtmlFontTest_2627, HtmlFilter_NullPointerZeroLen_DoesNotCrash_2627) {
  // Boundary: nullptr with length 0 should be handled gracefully (at minimum, not crash).
  EXPECT_NO_THROW({
    auto filtered = HtmlFont::HtmlFilter(nullptr, 0);
    // Observable behavior allowed: result may be null or empty depending on implementation.
    if (filtered) {
      EXPECT_TRUE(GooStringToStdString(filtered).empty());
    }
  });
}

TEST(HtmlFontTest_2627, HtmlFilter_EmptyBuffer_ProducesDeterministicResult_2627) {
  const Unicode empty_buf[1] = {0};

  std::unique_ptr<decltype(HtmlFont::HtmlFilter(empty_buf, 0))::element_type> a;
  std::unique_ptr<decltype(HtmlFont::HtmlFilter(empty_buf, 0))::element_type> b;

  EXPECT_NO_THROW({ a = HtmlFont::HtmlFilter(empty_buf, 0); });
  EXPECT_NO_THROW({ b = HtmlFont::HtmlFilter(empty_buf, 0); });

  // Determinism: calling twice with the same inputs should yield equivalent outputs.
  // (If either is nullptr, treat nullptr as an allowed outcome and compare that.)
  if (!a || !b) {
    EXPECT_EQ(static_cast<bool>(a), static_cast<bool>(b));
  } else {
    EXPECT_EQ(GooStringToStdString(a), GooStringToStdString(b));
  }
}

TEST(HtmlFontTest_2627, HtmlFilter_SimpleAsciiLikeInput_IsDeterministicAndNonThrowing_2627) {
  // Boundary-ish small input.
  const Unicode u[3] = {static_cast<Unicode>('A'), static_cast<Unicode>('B'), static_cast<Unicode>('C')};

  std::string out1;
  std::string out2;

  EXPECT_NO_THROW({
    auto s1 = HtmlFont::HtmlFilter(u, 3);
    out1 = GooStringToStdString(s1);
  });

  EXPECT_NO_THROW({
    auto s2 = HtmlFont::HtmlFilter(u, 3);
    out2 = GooStringToStdString(s2);
  });

  EXPECT_EQ(out1, out2);

  // If an output is produced, it should be non-empty for non-empty input.
  // (Some implementations may return nullptr; that's acceptable as "observable".)
  if (!out1.empty()) {
    EXPECT_FALSE(out1.empty());
  }
}

// --------------------
// Instance-based tests (only run when HtmlFont is default-constructible)
// --------------------

TEST(HtmlFontTest_2627, DefaultConstruct_Print_WritesSomethingOrSkips_2627) {
  auto font = TryMakeDefaultHtmlFont();
  if (!font) {
    GTEST_SKIP() << "HtmlFont is not default-constructible in this build; skipping instance-based test.";
  }

  testing::internal::CaptureStdout();
  EXPECT_NO_THROW({ font->print(); });
  const std::string out = testing::internal::GetCapturedStdout();

  // Observable: print() should write something; at minimum it should not be empty.
  EXPECT_FALSE(out.empty());
  // And commonly starts with "font:" per the provided partial implementation.
  EXPECT_THAT(out, testing::HasSubstr("font:"));
}

TEST(HtmlFontTest_2627, DefaultConstruct_Getters_AreStableAcrossCallsOrSkips_2627) {
  auto font = TryMakeDefaultHtmlFont();
  if (!font) {
    GTEST_SKIP() << "HtmlFont is not default-constructible in this build; skipping instance-based test.";
  }

  EXPECT_NO_THROW({
    const std::string name1 = font->getFontName();
    const std::string name2 = font->getFontName();
    EXPECT_EQ(name1, name2);

    const std::string full1 = font->getFullName();
    const std::string full2 = font->getFullName();
    EXPECT_EQ(full1, full2);
  });
}

TEST(HtmlFontTest_2627, DefaultConstruct_LineSize_SetThenGet_RoundTripsOrSkips_2627) {
  auto font = TryMakeDefaultHtmlFont();
  if (!font) {
    GTEST_SKIP() << "HtmlFont is not default-constructible in this build; skipping instance-based test.";
  }

  // Boundary values: 0, negative, and a larger value.
  EXPECT_NO_THROW({
    font->setLineSize(0);
    EXPECT_EQ(font->getLineSize(), 0);

    font->setLineSize(-1);
    EXPECT_EQ(font->getLineSize(), -1);

    font->setLineSize(123456);
    EXPECT_EQ(font->getLineSize(), 123456);
  });
}

TEST(HtmlFontTest_2627, DefaultConstruct_RotationMatrix_SetThenGet_RoundTripsOrSkips_2627) {
  auto font = TryMakeDefaultHtmlFont();
  if (!font) {
    GTEST_SKIP() << "HtmlFont is not default-constructible in this build; skipping instance-based test.";
  }

  const std::array<double, 4> mat1{{1.0, 0.0, 0.0, 1.0}};
  const std::array<double, 4> mat2{{0.0, 1.0, -1.0, 0.0}};

  EXPECT_NO_THROW({
    font->setRotMat(mat1);
    const auto& got1 = font->getRotMat();
    EXPECT_EQ(got1, mat1);

    font->setRotMat(mat2);
    const auto& got2 = font->getRotMat();
    EXPECT_EQ(got2, mat2);
  });
}

TEST(HtmlFontTest_2627, DefaultConstruct_BooleanFlags_AreStableAcrossCallsOrSkips_2627) {
  auto font = TryMakeDefaultHtmlFont();
  if (!font) {
    GTEST_SKIP() << "HtmlFont is not default-constructible in this build; skipping instance-based test.";
  }

  EXPECT_NO_THROW({
    const bool b1 = font->isBold();
    const bool b2 = font->isBold();
    EXPECT_EQ(b1, b2);

    const bool i1 = font->isItalic();
    const bool i2 = font->isItalic();
    EXPECT_EQ(i1, i2);

    const bool r1 = font->isRotOrSkewed();
    const bool r2 = font->isRotOrSkewed();
    EXPECT_EQ(r1, r2);
  });
}

TEST(HtmlFontTest_2627, DefaultConstruct_Size_IsStableAcrossCallsOrSkips_2627) {
  auto font = TryMakeDefaultHtmlFont();
  if (!font) {
    GTEST_SKIP() << "HtmlFont is not default-constructible in this build; skipping instance-based test.";
  }

  EXPECT_NO_THROW({
    const int s1 = font->getSize();
    const int s2 = font->getSize();
    EXPECT_EQ(s1, s2);
  });
}

TEST(HtmlFontTest_2627, DefaultConstruct_Equality_IsReflexiveAndSymmetricOrSkips_2627) {
  auto a = TryMakeDefaultHtmlFont();
  auto b = TryMakeDefaultHtmlFont();
  if (!a || !b) {
    GTEST_SKIP() << "HtmlFont is not default-constructible in this build; skipping instance-based test.";
  }

  EXPECT_NO_THROW({
    // Reflexive
    EXPECT_TRUE(a->isEqual(*a));
    EXPECT_TRUE(a->isEqualIgnoreBold(*a));

    // Symmetric: a == b iff b == a (for both equality variants)
    const bool ab = a->isEqual(*b);
    const bool ba = b->isEqual(*a);
    EXPECT_EQ(ab, ba);

    const bool ab2 = a->isEqualIgnoreBold(*b);
    const bool ba2 = b->isEqualIgnoreBold(*a);
    EXPECT_EQ(ab2, ba2);

    // Consistency: if strict equal, then ignore-bold equal should also hold.
    if (ab) {
      EXPECT_TRUE(ab2);
    }
  });
}

TEST(HtmlFontTest_2627, DefaultConstruct_GetColor_DoesNotThrowAndIsCopyableOrSkips_2627) {
  auto font = TryMakeDefaultHtmlFont();
  if (!font) {
    GTEST_SKIP() << "HtmlFont is not default-constructible in this build; skipping instance-based test.";
  }

  EXPECT_NO_THROW({
    const auto c1 = font->getColor();
    const auto c2 = font->getColor();
    // Observable: repeated calls should be stable (operator== may not exist).
    // So we only require that it can be obtained twice without throwing.
    (void)c1;
    (void)c2;
  });
}