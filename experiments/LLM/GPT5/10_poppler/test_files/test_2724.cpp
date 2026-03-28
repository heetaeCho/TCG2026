// Copyright (C) 2026
// Unit tests for printInfoDate (utils/pdftotext.cc)

#include <gtest/gtest.h>

#include <cstdio>
#include <cstdlib>
#include <string>

// We want to test a static function inside pdftotext.cc. The simplest way is to
// include the implementation file into this test translation unit.
// pdftotext.cc typically defines a main(); rename it to avoid collisions.
#define main pdftotext_main_2724
#include "./TestProjects/poppler/utils/pdftotext.cc"
#undef main

#include "./TestProjects/poppler/poppler/Dict.h"
#include "./TestProjects/poppler/poppler/Object.h"

namespace {

class PrintInfoDateTest_2724 : public ::testing::Test {
protected:
  static std::string CapturePrintInfoDate(Dict *dict,
                                         const char *key,
                                         const char *text1,
                                         const char *text2) {
    char *buf = nullptr;
    size_t sz = 0;

    FILE *f = open_memstream(&buf, &sz);
    if (!f) {
      return std::string();
    }

    printInfoDate(f, dict, key, text1, text2);

    fflush(f);
    fclose(f);

    std::string out;
    if (buf) {
      out.assign(buf, sz);
      free(buf);
    }
    return out;
  }
};

TEST_F(PrintInfoDateTest_2724, MissingKeyProducesNoOutput_2724) {
  Dict dict(nullptr);

  const std::string out = CapturePrintInfoDate(&dict, "CreationDate", "(", ")");
  EXPECT_TRUE(out.empty());
}

TEST_F(PrintInfoDateTest_2724, NonStringValueProducesNoOutput_2724) {
  Dict dict(nullptr);
  dict.add("CreationDate", Object(123));

  const std::string out = CapturePrintInfoDate(&dict, "CreationDate", "(", ")");
  EXPECT_TRUE(out.empty());
}

TEST_F(PrintInfoDateTest_2724, UnparseableDateStringProducesNoOutput_2724) {
  Dict dict(nullptr);
  dict.add("CreationDate", Object(std::string("not-a-date")));

  const std::string out = CapturePrintInfoDate(&dict, "CreationDate", "(", ")");
  EXPECT_TRUE(out.empty());
}

TEST_F(PrintInfoDateTest_2724, ZuluTimezonePrintsTrailingZ_2724) {
  Dict dict(nullptr);
  dict.add("CreationDate", Object(std::string("D:20240224123456Z")));

  const std::string out = CapturePrintInfoDate(&dict, "CreationDate", "(", ")");
  EXPECT_EQ(out, "(2024-02-24T12:34:56Z)");
}

TEST_F(PrintInfoDateTest_2724, NonZeroOffsetWithZeroMinutesOmitsColonMinutes_2724) {
  Dict dict(nullptr);
  // tz_minute == 0 should print "+HH" with no ":00".
  dict.add("CreationDate", Object(std::string("D:20240224123456+09'00'")));

  const std::string out = CapturePrintInfoDate(&dict, "CreationDate", "[", "]");
  EXPECT_EQ(out, "[2024-02-24T12:34:56+09]");
}

TEST_F(PrintInfoDateTest_2724, NonZeroOffsetWithNonZeroMinutesPrintsColonMinutes_2724) {
  Dict dict(nullptr);
  dict.add("CreationDate", Object(std::string("D:20240224123456-05'30'")));

  const std::string out = CapturePrintInfoDate(&dict, "CreationDate", "<", ">");
  EXPECT_EQ(out, "<2024-02-24T12:34:56-05:30>");
}

TEST_F(PrintInfoDateTest_2724, EmptyTextWrappersStillPrintsJustTimestamp_2724) {
  Dict dict(nullptr);
  dict.add("CreationDate", Object(std::string("D:20240224123456Z")));

  const std::string out = CapturePrintInfoDate(&dict, "CreationDate", "", "");
  EXPECT_EQ(out, "2024-02-24T12:34:56Z");
}

} // namespace