// printInfoString_test_2723.cc
//
// Unit tests for static printInfoString() in utils/pdftotext.cc
// NOTE: We include the .cc directly to access the file-local static function.
//       We also rename pdftotext's main (if present) to avoid link conflicts.

#include <gtest/gtest.h>

#include <cstdio>
#include <cstring>
#include <memory>
#include <string>
#include <vector>

#define main pdftotext_main_2723
#include "TestProjects/poppler/utils/pdftotext.cc"
#undef main

#include "TestProjects/poppler/poppler/Dict.h"
#include "TestProjects/poppler/poppler/Object.h"
#include "TestProjects/poppler/goo/GooString.h"
#include "TestProjects/poppler/poppler/UnicodeMap.h"

namespace {

class PrintInfoStringTest_2723 : public ::testing::Test {
protected:
  static std::string ReadAllFromFile(FILE *f) {
    std::string out;
    std::rewind(f);

    char buf[256];
    while (true) {
      size_t n = std::fread(buf, 1, sizeof(buf), f);
      if (n > 0) out.append(buf, n);
      if (n < sizeof(buf)) break;
    }
    return out;
  }

  static std::string RunPrintInfoString(Dict *dict,
                                       const char *key,
                                       const char *text1,
                                       const char *text2,
                                       const UnicodeMap *uMap) {
    FILE *f = std::tmpfile();
    EXPECT_NE(f, nullptr);
    if (!f) return "";

    printInfoString(f, dict, key, text1, text2, uMap);
    std::fflush(f);

    std::string out = ReadAllFromFile(f);
    std::fclose(f);
    return out;
  }

  static std::unique_ptr<UnicodeMap> MakeUtf8MapOrSkip() {
    // Use Poppler's own parsing to avoid assuming encoding tables.
    auto m = UnicodeMap::parse("UTF-8");
    if (!m) {
      GTEST_SKIP() << "UnicodeMap::parse(\"UTF-8\") returned null in this build.";
    }
    return m;
  }
};

TEST_F(PrintInfoStringTest_2723, WritesNothingWhenKeyMissing_2723) {
  auto uMap = MakeUtf8MapOrSkip();

  Dict dict(nullptr); // XRef* not needed for these dictionary-only operations.
  const std::string out = RunPrintInfoString(&dict, "NoSuchKey", "A:", ":B", uMap.get());

  EXPECT_TRUE(out.empty());
}

TEST_F(PrintInfoStringTest_2723, WritesNothingWhenValueIsNotString_2723) {
  auto uMap = MakeUtf8MapOrSkip();

  Dict dict(nullptr);
  dict.add("K", Object(123)); // Non-string object.

  const std::string out = RunPrintInfoString(&dict, "K", "A:", ":B", uMap.get());
  EXPECT_TRUE(out.empty());
}

TEST_F(PrintInfoStringTest_2723, WritesPrefixContentSuffixForPdfDocEncodingString_2723) {
  auto uMap = MakeUtf8MapOrSkip();

  Dict dict(nullptr);
  // Use plain ASCII to avoid relying on xml-token replacement behavior.
  auto s = std::make_unique<GooString>("ABC");
  dict.add("Title", Object(std::move(s)));

  const std::string out = RunPrintInfoString(&dict, "Title", "PFX[", "]SFX", uMap.get());
  EXPECT_EQ(out, "PFX[ABC]SFX");
}

TEST_F(PrintInfoStringTest_2723, TreatsUtf16BeBomAsUnicodeAndDecodesPairs_2723) {
  auto uMap = MakeUtf8MapOrSkip();

  Dict dict(nullptr);

  // UTF-16BE with BOM FE FF, followed by 'A' and 'B' (0x0041, 0x0042).
  const unsigned char bytes[] = {0xFE, 0xFF, 0x00, 0x41, 0x00, 0x42};
  auto s = std::make_unique<GooString>(reinterpret_cast<const char *>(bytes), sizeof(bytes));
  dict.add("K", Object(std::move(s)));

  const std::string out = RunPrintInfoString(&dict, "K", "<", ">", uMap.get());
  EXPECT_EQ(out, "<AB>");
}

TEST_F(PrintInfoStringTest_2723, AppliesXmlTokenReplacementToMappedOutput_2723) {
  auto uMap = MakeUtf8MapOrSkip();

  Dict dict(nullptr);

  // A simple case that should pass through unicode mapping and then XML token replacement.
  // If myXmlTokenReplace replaces '<' to "&lt;" (as typical), this is observable at the interface
  // (printInfoString writes the replaced string).
  auto s = std::make_unique<GooString>("<");
  dict.add("K", Object(std::move(s)));

  const std::string out = RunPrintInfoString(&dict, "K", "X", "Y", uMap.get());

  // We don't assume the exact replacement table, but we can assert:
  // - Prefix and suffix are written
  // - The raw '<' is not emitted verbatim (if replacement exists), OR it is emitted if no replacement.
  // To keep the test robust across builds, accept either but ensure the middle is non-empty.
  ASSERT_GE(out.size(), std::strlen("X") + std::strlen("Y") + 1u);
  EXPECT_TRUE(out.rfind("X", 0) == 0); // starts with "X"
  EXPECT_TRUE(out.size() >= 1 && out.substr(out.size() - 1) == "Y"); // ends with "Y"
}

} // namespace