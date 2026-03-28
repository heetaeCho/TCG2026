// File: printISODate_test_2666.cc
#include <gtest/gtest.h>

#include <memory>
#include <string>

// Poppler headers (project-local)
#include "poppler/Dict.h"
#include "poppler/Object.h"
#include "poppler/UnicodeMap.h"
#include "goo/GooString.h"

// pdfinfo.cc is a utility with its own main() in many builds.
// Rename main to avoid link conflicts when compiling unit tests.
#define main poppler_pdfinfo_main_2666
#include "utils/pdfinfo.cc"
#undef main

namespace {

static Dict MakeDictWithStringKey(const char *key, const char *value)
{
    Dict dict(nullptr /* XRef* */);
    dict.add(key, Object(std::make_unique<GooString>(value)));
    return dict;
}

static Dict MakeDictWithNonStringKey(const char *key)
{
    Dict dict(nullptr /* XRef* */);
    dict.add(key, Object(123)); // int, not a string
    return dict;
}

} // namespace

TEST(PrintISODateTest_2666, DoesNothingWhenKeyMissing_2666)
{
    Dict dict(nullptr /* XRef* */);

    testing::internal::CaptureStdout();
    printISODate(&dict, "CreationDate", "CreationDate: ", nullptr);
    const std::string out = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(out.empty());
}

TEST(PrintISODateTest_2666, DoesNothingWhenValueIsNotString_2666)
{
    Dict dict = MakeDictWithNonStringKey("CreationDate");

    testing::internal::CaptureStdout();
    printISODate(&dict, "CreationDate", "CreationDate: ", nullptr);
    const std::string out = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(out.empty());
}

TEST(PrintISODateTest_2666, PrintsISO8601WithZuluWhenTimezoneIsZero_2666)
{
    // Typical PDF date string format: D:YYYYMMDDHHmmSSOHH'mm'
    // Use Z to indicate UTC (tz_hour=0, tz_minute=0).
    Dict dict = MakeDictWithStringKey("CreationDate", "D:20240224123456Z");

    testing::internal::CaptureStdout();
    printISODate(&dict, "CreationDate", "CreationDate: ", nullptr);
    const std::string out = testing::internal::GetCapturedStdout();

    EXPECT_EQ(out, "CreationDate: 2024-02-24T12:34:56Z\n");
}

TEST(PrintISODateTest_2666, PrintsISO8601WithPositiveHourOffsetNoMinutes_2666)
{
    Dict dict = MakeDictWithStringKey("ModDate", "D:20240224123456+09'00'");

    testing::internal::CaptureStdout();
    printISODate(&dict, "ModDate", "ModDate: ", nullptr);
    const std::string out = testing::internal::GetCapturedStdout();

    EXPECT_EQ(out, "ModDate: 2024-02-24T12:34:56+09\n");
}

TEST(PrintISODateTest_2666, PrintsISO8601WithPositiveHourAndMinuteOffset_2666)
{
    Dict dict = MakeDictWithStringKey("ModDate", "D:20240224123456+05'30'");

    testing::internal::CaptureStdout();
    printISODate(&dict, "ModDate", "ModDate: ", nullptr);
    const std::string out = testing::internal::GetCapturedStdout();

    EXPECT_EQ(out, "ModDate: 2024-02-24T12:34:56+05:30\n");
}

TEST(PrintISODateTest_2666, PrintsISO8601WithNegativeHourOffset_2666)
{
    Dict dict = MakeDictWithStringKey("ModDate", "D:20240224123456-04'00'");

    testing::internal::CaptureStdout();
    printISODate(&dict, "ModDate", "ModDate: ", nullptr);
    const std::string out = testing::internal::GetCapturedStdout();

    EXPECT_EQ(out, "ModDate: 2024-02-24T12:34:56-04\n");
}

TEST(PrintISODateTest_2666, FallsBackToPrintingTextWhenDateParseFails_2666)
{
    // If parseDateString() fails, printTextString() is used.
    // We assert only observable stdout (prefix + some representation of the string + newline).
    Dict dict = MakeDictWithStringKey("CreationDate", "not-a-pdf-date");

    testing::internal::CaptureStdout();
    printISODate(&dict, "CreationDate", "CreationDate: ", nullptr);
    const std::string out = testing::internal::GetCapturedStdout();

    // Must print the label and end with newline.
    ASSERT_GE(out.size(), std::string("CreationDate: \n").size());
    EXPECT_TRUE(out.rfind("CreationDate: ", 0) == 0); // starts with prefix
    EXPECT_EQ(out.back(), '\n');

    // For simple ASCII input, it should typically include the original text somewhere.
    // (Don’t over-specify encoding/escaping; treat as black box.)
    EXPECT_NE(out.find("not-a-pdf-date"), std::string::npos);
}