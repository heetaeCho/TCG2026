// poppler_signing_data_get_font_color_test_2369.cc

#include <gtest/gtest.h>

#include <glib.h>

#if __has_include(<poppler.h>)
#include <poppler.h>
#elif __has_include("poppler.h")
#include "poppler.h"
#endif

// Try to pull in the struct definition of PopplerSigningData if it is available
// in the build (often via private headers in Poppler GLib).
#if __has_include("poppler-form-field-private.h")
#include "poppler-form-field-private.h"
#elif __has_include("poppler-private.h")
#include "poppler-private.h"
#elif __has_include("poppler-form-field.h")
#include "poppler-form-field.h"
#endif

extern "C" {
const PopplerColor* poppler_signing_data_get_font_color(const PopplerSigningData* signing_data);
}  // extern "C"

namespace {

template <typename T, typename = void>
struct is_complete : std::false_type {};
template <typename T>
struct is_complete<T, decltype(void(sizeof(T)))> : std::true_type {};

template <typename T, typename = void>
struct has_member_font_color : std::false_type {};
template <typename T>
struct has_member_font_color<T, decltype(void(&T::font_color))> : std::true_type {};

class PopplerSigningDataGetFontColorTest_2369 : public ::testing::Test {
protected:
  static PopplerSigningData* CreateSigningDataOrSkip() {
    if constexpr (!is_complete<PopplerSigningData>::value) {
      return nullptr;
    } else {
      // Plain struct allocation (no assumptions about initialization beyond zeroing).
      return static_cast<PopplerSigningData*>(g_malloc0(sizeof(PopplerSigningData)));
    }
  }

  static void DestroySigningData(PopplerSigningData* data) {
    g_free(data);
  }
};

}  // namespace

TEST_F(PopplerSigningDataGetFontColorTest_2369, NullSigningDataReturnsNull_2369) {
  EXPECT_EQ(poppler_signing_data_get_font_color(nullptr), nullptr);
}

TEST_F(PopplerSigningDataGetFontColorTest_2369, NonNullReturnsNonNullPointer_2369) {
  PopplerSigningData* data = CreateSigningDataOrSkip();
  if (!data) {
    GTEST_SKIP() << "PopplerSigningData is an incomplete type in this build; cannot instantiate.";
  }

  const PopplerColor* color = poppler_signing_data_get_font_color(data);
  EXPECT_NE(color, nullptr);

  DestroySigningData(data);
}

TEST_F(PopplerSigningDataGetFontColorTest_2369, RepeatedCallsReturnSamePointerForSameObject_2369) {
  PopplerSigningData* data = CreateSigningDataOrSkip();
  if (!data) {
    GTEST_SKIP() << "PopplerSigningData is an incomplete type in this build; cannot instantiate.";
  }

  const PopplerColor* c1 = poppler_signing_data_get_font_color(data);
  const PopplerColor* c2 = poppler_signing_data_get_font_color(data);

  EXPECT_NE(c1, nullptr);
  EXPECT_NE(c2, nullptr);
  EXPECT_EQ(c1, c2);

  DestroySigningData(data);
}

TEST_F(PopplerSigningDataGetFontColorTest_2369, DifferentObjectsReturnDifferentAddresses_2369) {
  PopplerSigningData* d1 = CreateSigningDataOrSkip();
  PopplerSigningData* d2 = CreateSigningDataOrSkip();
  if (!d1 || !d2) {
    if (d1) DestroySigningData(d1);
    if (d2) DestroySigningData(d2);
    GTEST_SKIP() << "PopplerSigningData is an incomplete type in this build; cannot instantiate.";
  }

  const PopplerColor* c1 = poppler_signing_data_get_font_color(d1);
  const PopplerColor* c2 = poppler_signing_data_get_font_color(d2);

  EXPECT_NE(c1, nullptr);
  EXPECT_NE(c2, nullptr);
  EXPECT_NE(c1, c2);

  DestroySigningData(d1);
  DestroySigningData(d2);
}

TEST_F(PopplerSigningDataGetFontColorTest_2369, ReturnedColorMatchesStoredValueWhenAccessible_2369) {
  PopplerSigningData* data = CreateSigningDataOrSkip();
  if (!data) {
    GTEST_SKIP() << "PopplerSigningData is an incomplete type in this build; cannot instantiate.";
  }

  // Only perform a value check if the struct exposes a 'font_color' member in this build.
  if constexpr (!has_member_font_color<PopplerSigningData>::value) {
    DestroySigningData(data);
    GTEST_SKIP() << "PopplerSigningData::font_color is not accessible in this build.";
  } else {
    // Boundary-ish values for a PopplerColor (commonly guint16 channels).
    // We only set fields that exist in PopplerColor; if PopplerColor differs in this build,
    // compilation will fail and should be adjusted to the actual PopplerColor definition.
    PopplerColor expected{};
    expected.red = 0;
    expected.green = 65535;
    expected.blue = 1;

    data->font_color = expected;

    const PopplerColor* got = poppler_signing_data_get_font_color(data);
    ASSERT_NE(got, nullptr);

    EXPECT_EQ(got->red, expected.red);
    EXPECT_EQ(got->green, expected.green);
    EXPECT_EQ(got->blue, expected.blue);

    DestroySigningData(data);
  }
}