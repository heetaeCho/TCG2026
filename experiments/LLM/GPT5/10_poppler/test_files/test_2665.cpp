// printInfoDate_test_2665.cc
#include <gtest/gtest.h>

#include <clocale>
#include <cstdlib>
#include <memory>
#include <string>

#include "poppler/Dict.h"
#include "poppler/Object.h"
#include "poppler/UnicodeMap.h"

// pdfinfo.cc is a utility program and typically defines a main(). We include it to
// access the internal-linkage helper (static) printInfoDate() for black-box testing.
// Rename main to avoid ODR/link conflicts with gtest main.
#define main pdfinfo_main_2665
#include "utils/pdfinfo.cc"
#undef main

namespace {

// Small helper to create a usable UnicodeMap when available.
static const UnicodeMap *GetUtf8UnicodeMapOrSkip() {
  static std::unique_ptr<UnicodeMap> uMap = UnicodeMap::parse("UTF-8");
  if (!uMap) {
    GTEST_SKIP() << "UnicodeMap::parse(\"UTF-8\") returned null; cannot safely "
                    "exercise printTextString fallback paths.";
  }
  return uMap.get();
}

class PrintInfoDateTest_2665 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Stabilize formatting as much as possible.
    // %c output is locale-dependent; enforce "C".
    std::setlocale(LC_TIME, "C");

    // Force timezone to UTC to make %Z stable and to avoid dependence on runner TZ.
#if defined(_WIN32)
    // Best-effort on Windows runners; harmless if unsupported in the environment.
    _putenv_s("TZ", "UTC");
#else
    setenv("TZ", "UTC", 1);
#endif
    tzset();
  }
};

TEST_F(PrintInfoDateTest_2665, PrintsNothingWhenKeyMissing_2665) {
  Dict infoDict(nullptr);

  testing::internal::CaptureStdout();
  printInfoDate(&infoDict, "CreationDate", "CreationDate: ", /*uMap=*/nullptr);
  const std::string out = testing::internal::GetCapturedStdout();

  EXPECT_TRUE(out.empty());
}

TEST_F(PrintInfoDateTest_2665, PrintsNothingWhenValueIsNotString_2665) {
  Dict infoDict(nullptr);
  infoDict.add("CreationDate", Object(42));  // non-string

  testing::internal::CaptureStdout();
  printInfoDate(&infoDict, "CreationDate", "CreationDate: ", /*uMap=*/nullptr);
  const std::string out = testing::internal::GetCapturedStdout();

  EXPECT_TRUE(out.empty());
}

TEST_F(PrintInfoDateTest_2665, PrintsPrefixAndNewlineForParseableDate_2665) {
  Dict infoDict(nullptr);
  // Use a conventional PDF date string that should be parseable by typical PDF parsers.
  // (We treat parsing as a black box; this test only asserts observable stdout shape.)
  infoDict.add("CreationDate", Object(std::string("D:19700101000000Z")));

  testing::internal::CaptureStdout();
  printInfoDate(&infoDict, "CreationDate", "CreationDate: ", /*uMap=*/nullptr);
  const std::string out = testing::internal::GetCapturedStdout();

  // Must print the prefix when the value is a string.
  ASSERT_GE(out.size(), std::string("CreationDate: \n").size());
  EXPECT_EQ(out.rfind("CreationDate: ", 0), 0u) << out;  // starts with prefix
  EXPECT_EQ(out.back(), '\n');

  // When TZ is forced to UTC, successful date formatting should typically include "UTC".
  // (If the environment formats differently, this still remains a non-fatal check.)
  EXPECT_NE(out.find("UTC"), std::string::npos) << out;
}

TEST_F(PrintInfoDateTest_2665, FallsBackToPrintingTextWhenDateIsUnparseable_2665) {
  const UnicodeMap *uMap = GetUtf8UnicodeMapOrSkip();

  Dict infoDict(nullptr);
  infoDict.add("ModDate", Object(std::string("NotADateString")));

  testing::internal::CaptureStdout();
  printInfoDate(&infoDict, "ModDate", "ModDate: ", uMap);
  const std::string out = testing::internal::GetCapturedStdout();

  // Prefix printed for string values, always ends with newline.
  ASSERT_GE(out.size(), std::string("ModDate: \n").size());
  EXPECT_EQ(out.rfind("ModDate: ", 0), 0u) << out;
  EXPECT_EQ(out.back(), '\n');

  // In fallback paths, the raw text should be printed (after any text decoding).
  EXPECT_NE(out.find("NotADateString"), std::string::npos) << out;
}

TEST_F(PrintInfoDateTest_2665, HandlesLargePositiveTimezoneOffsetWithoutCrashing_2665) {
  Dict infoDict(nullptr);
  // Boundary-ish timezone offset; we only assert it produces some output.
  infoDict.add("CreationDate", Object(std::string("D:20240229120000+14'00'")));

  testing::internal::CaptureStdout();
  printInfoDate(&infoDict, "CreationDate", "CreationDate: ", /*uMap=*/nullptr);
  const std::string out = testing::internal::GetCapturedStdout();

  EXPECT_EQ(out.rfind("CreationDate: ", 0), 0u) << out;
  EXPECT_EQ(out.back(), '\n');
  EXPECT_FALSE(out.empty());
}

}  // namespace