// SplashOutputDevNoTextTest_2715.cc
#include <gtest/gtest.h>

// pdftohtml.cc is a utility (likely defines its own main). To unit-test internal
// classes defined in that .cc, we include it into this test TU while renaming
// its main symbol to avoid a multiple-definition link error.
#define main pdftohtml_cc_main_for_tests_2715
#include "./TestProjects/poppler/utils/pdftohtml.cc"
#undef main

// NOTE: We treat SplashOutputDevNoText as a black box. We only test behavior
// observable through its public interface (interpretType3Chars()).

namespace {

class SplashOutputDevNoTextTest_2715 : public ::testing::Test {
protected:
  // Helper to build a minimal paper color object compatible with Splash APIs.
  // (Avoids any assumptions about internals; just provides a value to satisfy
  // the constructor signature.)
  static SplashColorPtr MakePaperColor_2715() {
    // SplashColor is typically an array type; zero-initialize for safety.
    static SplashColor paperColor = {};
    return paperColor;
  }
};

TEST_F(SplashOutputDevNoTextTest_2715, InterpretType3CharsReturnsFalse_2715) {
  SplashOutputDevNoText dev(splashModeRGB8, /*bitmapRowPadA=*/4,
                           MakePaperColor_2715(),
                           /*bitmapTopDownA=*/true);

  EXPECT_FALSE(dev.interpretType3Chars());
}

TEST_F(SplashOutputDevNoTextTest_2715, InterpretType3CharsReturnsFalseRepeatedly_2715) {
  SplashOutputDevNoText dev(splashModeRGB8, /*bitmapRowPadA=*/0,
                           MakePaperColor_2715(),
                           /*bitmapTopDownA=*/true);

  EXPECT_FALSE(dev.interpretType3Chars());
  EXPECT_FALSE(dev.interpretType3Chars());
  EXPECT_FALSE(dev.interpretType3Chars());
}

TEST_F(SplashOutputDevNoTextTest_2715, InterpretType3CharsPolymorphicCallReturnsFalse_2715) {
  SplashOutputDevNoText dev(splashModeRGB8, /*bitmapRowPadA=*/4,
                           MakePaperColor_2715(),
                           /*bitmapTopDownA=*/false);

  SplashOutputDev* base = &dev;  // Verify override via base-class dispatch.
  ASSERT_NE(base, nullptr);
  EXPECT_FALSE(base->interpretType3Chars());
}

}  // namespace