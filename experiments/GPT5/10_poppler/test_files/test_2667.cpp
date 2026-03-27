// File: printBox_test_2667.cc
#include <gtest/gtest.h>

#include <clocale>
#include <cstdio>
#include <string>

#include "poppler/PDFRectangle.h"

// pdfinfo.cc (in Poppler) is typically a utility with its own main().
// To unit-test the TU-local static helper `printBox`, we include the .cc
// into this test translation unit and rename main to avoid conflicts.
#define main pdfinfo_main_for_test_2667
#include "utils/pdfinfo.cc"
#undef main

namespace {

class PrintBoxTest_2667 : public ::testing::Test {
protected:
  void SetUp() override
  {
    // Make numeric formatting deterministic (decimal dot).
    std::setlocale(LC_NUMERIC, "C");
  }

  static std::string Expected(const char *text, const PDFRectangle *box)
  {
    char buf[256];
    std::snprintf(buf, sizeof(buf), "%s%8.2f %8.2f %8.2f %8.2f\n",
                  text, box->x1, box->y1, box->x2, box->y2);
    return std::string(buf);
  }
};

TEST_F(PrintBoxTest_2667, PrintsExpectedFormatting_2667)
{
  const PDFRectangle box(1.0, 2.0, 3.0, 4.0);
  const char *text = "MediaBox: ";

  testing::internal::CaptureStdout();
  printBox(text, &box);
  const std::string out = testing::internal::GetCapturedStdout();

  EXPECT_EQ(out, Expected(text, &box));
}

TEST_F(PrintBoxTest_2667, SupportsNegativeAndLargeValues_2667)
{
  const PDFRectangle box(-1.2, -3.456, 7890.1, 2.0);
  const char *text = "CropBox: ";

  testing::internal::CaptureStdout();
  printBox(text, &box);
  const std::string out = testing::internal::GetCapturedStdout();

  EXPECT_EQ(out, Expected(text, &box));
}

TEST_F(PrintBoxTest_2667, RoundsToTwoDecimals_2667)
{
  const PDFRectangle box(1.234, 5.235, 9.999, 0.004);
  const char *text = "TrimBox: ";

  testing::internal::CaptureStdout();
  printBox(text, &box);
  const std::string out = testing::internal::GetCapturedStdout();

  // Uses the same format specifier to avoid duplicating formatting logic.
  EXPECT_EQ(out, Expected(text, &box));
}

TEST_F(PrintBoxTest_2667, AllowsEmptyPrefixText_2667)
{
  const PDFRectangle box(0.0, 0.0, 0.0, 0.0);
  const char *text = "";

  testing::internal::CaptureStdout();
  printBox(text, &box);
  const std::string out = testing::internal::GetCapturedStdout();

  EXPECT_EQ(out, Expected(text, &box));
}

#if GTEST_HAS_DEATH_TEST
TEST_F(PrintBoxTest_2667, DeathOnNullBoxPointer_2667)
{
  // Passing a null PDFRectangle* is an error case observable as a crash.
  ASSERT_DEATH(
      {
        // Avoid stdout capture here; just exercise the failure.
        printBox("Box: ", nullptr);
      },
      ".*");
}
#endif

} // namespace