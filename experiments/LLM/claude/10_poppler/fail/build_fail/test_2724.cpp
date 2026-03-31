#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <memory>

#include "Object.h"
#include "Dict.h"
#include "GooString.h"
#include "DateInfo.h"

// The function under test is static in pdftotext.cc, so we include the relevant portion
// or declare it. Since it's static, we need to include the source or replicate the declaration.
// For testing purposes, we extract/include it.

// Forward declaration - since the function is static, we need to include the source
// We'll define it here matching the implementation
static void printInfoDate(FILE *f, Dict *infoDict, const char *key, const char *text1, const char *text2)
{
    int year, mon, day, hour, min, sec, tz_hour, tz_minute;
    char tz;
    Object obj = infoDict->lookup(key);
    if (obj.isString()) {
        const GooString *s = obj.getString();
        if (parseDateString(s, &year, &mon, &day, &hour, &min, &sec, &tz, &tz_hour, &tz_minute)) {
            fputs(text1, f);
            fprintf(f, "%04d-%02d-%02dT%02d:%02d:%02d", year, mon, day, hour, min, sec);
            if (tz_hour == 0 && tz_minute == 0) {
                fprintf(f, "Z");
            } else {
                fprintf(f, "%c%02d", tz, tz_hour);
                if (tz_minute) {
                    fprintf(f, ":%02d", tz_minute);
                }
            }
            fputs(text2, f);
        }
    }
}

class PrintInfoDateTest_2724 : public ::testing::Test {
protected:
    void SetUp() override {
        dict = new Dict(nullptr);
    }

    void TearDown() override {
        delete dict;
    }

    std::string callPrintInfoDate(Dict *d, const char *key, const char *text1, const char *text2) {
        char *buf = nullptr;
        size_t bufSize = 0;
        FILE *f = open_memstream(&buf, &bufSize);
        EXPECT_NE(f, nullptr);

        printInfoDate(f, d, key, text1, text2);
        fclose(f);

        std::string result;
        if (buf) {
            result = std::string(buf, bufSize);
            free(buf);
        }
        return result;
    }

    Dict *dict;
};

// Test: Key not found in dictionary - should produce no output
TEST_F(PrintInfoDateTest_2724, KeyNotFound_2724) {
    std::string result = callPrintInfoDate(dict, "NonExistentKey", "prefix:", ":suffix");
    EXPECT_EQ(result, "");
}

// Test: Key exists but value is not a string (e.g., integer) - should produce no output
TEST_F(PrintInfoDateTest_2724, ValueNotString_2724) {
    dict->add("IntKey", Object(42));
    std::string result = callPrintInfoDate(dict, "IntKey", "prefix:", ":suffix");
    EXPECT_EQ(result, "");
}

// Test: Key exists with valid date string in UTC (timezone offset 0)
TEST_F(PrintInfoDateTest_2724, ValidDateUTC_2724) {
    // D:20230615120000Z format
    auto dateStr = std::make_unique<GooString>("D:20230615120000Z");
    dict->add("CreationDate", Object(std::move(dateStr)));
    std::string result = callPrintInfoDate(dict, "CreationDate", "Date: ", "\n");
    // Expect: "Date: 2023-06-15T12:00:00Z\n"
    EXPECT_EQ(result, "Date: 2023-06-15T12:00:00Z\n");
}

// Test: Key exists with valid date string with positive timezone offset
TEST_F(PrintInfoDateTest_2724, ValidDatePositiveTimezone_2724) {
    // D:20230615120000+05'30'
    auto dateStr = std::make_unique<GooString>("D:20230615120000+05'30'");
    dict->add("CreationDate", Object(std::move(dateStr)));
    std::string result = callPrintInfoDate(dict, "CreationDate", "", "");
    // Expect: "2023-06-15T12:00:00+05:30"
    EXPECT_EQ(result, "2023-06-15T12:00:00+05:30");
}

// Test: Key exists with valid date string with negative timezone offset, no minutes
TEST_F(PrintInfoDateTest_2724, ValidDateNegativeTimezoneNoMinutes_2724) {
    // D:20230615120000-08'00'
    auto dateStr = std::make_unique<GooString>("D:20230615120000-08'00'");
    dict->add("CreationDate", Object(std::move(dateStr)));
    std::string result = callPrintInfoDate(dict, "CreationDate", "", "");
    // Expect: "2023-06-15T12:00:00-08"
    EXPECT_EQ(result, "2023-06-15T12:00:00-08");
}

// Test: Key exists with valid date string with +00'00' timezone (treated as Z)
TEST_F(PrintInfoDateTest_2724, ValidDateZeroTimezoneOffset_2724) {
    auto dateStr = std::make_unique<GooString>("D:20230101000000+00'00'");
    dict->add("CreationDate", Object(std::move(dateStr)));
    std::string result = callPrintInfoDate(dict, "CreationDate", "", "");
    // tz_hour=0 and tz_minute=0 => "Z"
    EXPECT_EQ(result, "2023-01-01T00:00:00Z");
}

// Test: Empty text1 and text2 parameters
TEST_F(PrintInfoDateTest_2724, EmptyPrefixAndSuffix_2724) {
    auto dateStr = std::make_unique<GooString>("D:20230615120000Z");
    dict->add("CreationDate", Object(std::move(dateStr)));
    std::string result = callPrintInfoDate(dict, "CreationDate", "", "");
    EXPECT_EQ(result, "2023-06-15T12:00:00Z");
}

// Test: Invalid date string - should produce no output
TEST_F(PrintInfoDateTest_2724, InvalidDateString_2724) {
    auto dateStr = std::make_unique<GooString>("not a date");
    dict->add("CreationDate", Object(std::move(dateStr)));
    std::string result = callPrintInfoDate(dict, "CreationDate", "prefix:", ":suffix");
    EXPECT_EQ(result, "");
}

// Test: Empty string value - should produce no output (parseDateString fails)
TEST_F(PrintInfoDateTest_2724, EmptyStringValue_2724) {
    auto dateStr = std::make_unique<GooString>("");
    dict->add("CreationDate", Object(std::move(dateStr)));
    std::string result = callPrintInfoDate(dict, "CreationDate", "prefix:", ":suffix");
    EXPECT_EQ(result, "");
}

// Test: Custom text1 and text2 wrapping
TEST_F(PrintInfoDateTest_2724, CustomTextWrapping_2724) {
    auto dateStr = std::make_unique<GooString>("D:20201231235959Z");
    dict->add("ModDate", Object(std::move(dateStr)));
    std::string result = callPrintInfoDate(dict, "ModDate", "<date>", "</date>");
    EXPECT_EQ(result, "<date>2020-12-31T23:59:59Z</date>");
}

// Test: Boundary date values - minimum date
TEST_F(PrintInfoDateTest_2724, BoundaryMinDate_2724) {
    auto dateStr = std::make_unique<GooString>("D:00010101000000Z");
    dict->add("CreationDate", Object(std::move(dateStr)));
    std::string result = callPrintInfoDate(dict, "CreationDate", "", "");
    // If parseDateString accepts this, it should format it
    if (!result.empty()) {
        EXPECT_EQ(result, "0001-01-01T00:00:00Z");
    }
}

// Test: Positive timezone with hours only, no minutes
TEST_F(PrintInfoDateTest_2724, PositiveTimezoneHoursOnly_2724) {
    auto dateStr = std::make_unique<GooString>("D:20230615120000+05'00'");
    dict->add("CreationDate", Object(std::move(dateStr)));
    std::string result = callPrintInfoDate(dict, "CreationDate", "", "");
    // tz_minute is 0, so no ":00" suffix, just "+05"
    EXPECT_EQ(result, "2023-06-15T12:00:00+05");
}

// Test: Null object type for key - should produce no output
TEST_F(PrintInfoDateTest_2724, NullObjectValue_2724) {
    dict->add("NullKey", Object(objNull));
    std::string result = callPrintInfoDate(dict, "NullKey", "prefix:", ":suffix");
    EXPECT_EQ(result, "");
}

// Test: Different key names
TEST_F(PrintInfoDateTest_2724, DifferentKeyName_2724) {
    auto dateStr = std::make_unique<GooString>("D:20230615120000Z");
    dict->add("ModDate", Object(std::move(dateStr)));
    // Looking up wrong key should produce no output
    std::string result = callPrintInfoDate(dict, "CreationDate", "", "");
    EXPECT_EQ(result, "");
}
