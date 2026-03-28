#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdio>
#include <string>
#include <memory>
#include <cstring>

#include "Object.h"
#include "Dict.h"
#include "UnicodeMap.h"
#include "GooString.h"
#include "DateInfo.h"
#include "UTF.h"

// We need to include or declare the function under test.
// Since printISODate is static in pdfinfo.cc, we include it directly.
// We also need the helper functions it uses.
#include "pdfinfo.cc"

class PrintISODateTest_2666 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a Dict - needs XRef but we can pass nullptr for simple tests
        dict = new Dict(nullptr);
    }

    void TearDown() override {
        delete dict;
    }

    std::string captureStdout(std::function<void()> func) {
        // Redirect stdout to a temporary file
        fflush(stdout);
        FILE *original = stdout;
        char tmpname[] = "/tmp/pdfinfo_test_XXXXXX";
        int fd = mkstemp(tmpname);
        FILE *tmpf = fdopen(fd, "w+");
        stdout = tmpf;

        func();

        fflush(stdout);
        stdout = original;

        // Read back the captured output
        fseek(tmpf, 0, SEEK_END);
        long size = ftell(tmpf);
        fseek(tmpf, 0, SEEK_SET);
        std::string result(size, '\0');
        fread(&result[0], 1, size, tmpf);
        fclose(tmpf);
        unlink(tmpname);

        return result;
    }

    void addDateEntry(const char *key, const char *dateStr) {
        dict->add(key, Object(std::make_unique<GooString>(dateStr)));
    }

    Dict *dict;
};

// Test that when key is not found in dict, nothing is printed
TEST_F(PrintISODateTest_2666, KeyNotFound_2666) {
    auto uMap = UnicodeMap::parse("Latin1");
    std::string output = captureStdout([&]() {
        printISODate(dict, "NonExistent", "Label: ", uMap.get());
    });
    EXPECT_EQ(output, "");
}

// Test a valid date string with UTC timezone (tz_hour=0, tz_minute=0)
TEST_F(PrintISODateTest_2666, ValidDateUTC_2666) {
    addDateEntry("CreationDate", "D:20230615120000Z");
    auto uMap = UnicodeMap::parse("Latin1");
    std::string output = captureStdout([&]() {
        printISODate(dict, "CreationDate", "Creation Date: ", uMap.get());
    });
    EXPECT_THAT(output, ::testing::HasSubstr("Creation Date: "));
    EXPECT_THAT(output, ::testing::HasSubstr("2023-06-15T12:00:00Z"));
    EXPECT_THAT(output, ::testing::EndsWith("\n"));
}

// Test a valid date string with positive timezone offset
TEST_F(PrintISODateTest_2666, ValidDatePositiveOffset_2666) {
    addDateEntry("ModDate", "D:20230615120000+05'30");
    auto uMap = UnicodeMap::parse("Latin1");
    std::string output = captureStdout([&]() {
        printISODate(dict, "ModDate", "Mod Date: ", uMap.get());
    });
    EXPECT_THAT(output, ::testing::HasSubstr("Mod Date: "));
    EXPECT_THAT(output, ::testing::HasSubstr("2023-06-15T12:00:00"));
    EXPECT_THAT(output, ::testing::HasSubstr("+05"));
    EXPECT_THAT(output, ::testing::HasSubstr(":30"));
}

// Test a valid date string with negative timezone offset, no minutes
TEST_F(PrintISODateTest_2666, ValidDateNegativeOffsetNoMinutes_2666) {
    addDateEntry("ModDate", "D:20230615120000-05'00");
    auto uMap = UnicodeMap::parse("Latin1");
    std::string output = captureStdout([&]() {
        printISODate(dict, "ModDate", "Mod Date: ", uMap.get());
    });
    EXPECT_THAT(output, ::testing::HasSubstr("Mod Date: "));
    EXPECT_THAT(output, ::testing::HasSubstr("2023-06-15T12:00:00"));
    EXPECT_THAT(output, ::testing::HasSubstr("-05"));
    // tz_minute is 0 so no ":00" after the hour offset
}

// Test with an invalid/unparseable date string - should fall back to printing raw string
TEST_F(PrintISODateTest_2666, InvalidDateString_2666) {
    addDateEntry("CreationDate", "not-a-date");
    auto uMap = UnicodeMap::parse("Latin1");
    std::string output = captureStdout([&]() {
        printISODate(dict, "CreationDate", "Creation Date: ", uMap.get());
    });
    EXPECT_THAT(output, ::testing::HasSubstr("Creation Date: "));
    EXPECT_THAT(output, ::testing::HasSubstr("not-a-date"));
    EXPECT_THAT(output, ::testing::EndsWith("\n"));
}

// Test with a non-string object in the dict (e.g., integer)
TEST_F(PrintISODateTest_2666, NonStringObject_2666) {
    dict->add("IntKey", Object(42));
    auto uMap = UnicodeMap::parse("Latin1");
    std::string output = captureStdout([&]() {
        printISODate(dict, "IntKey", "Int: ", uMap.get());
    });
    EXPECT_EQ(output, "");
}

// Test date with only date portion (no time)
TEST_F(PrintISODateTest_2666, DateOnly_2666) {
    addDateEntry("CreationDate", "D:20230615");
    auto uMap = UnicodeMap::parse("Latin1");
    std::string output = captureStdout([&]() {
        printISODate(dict, "CreationDate", "Date: ", uMap.get());
    });
    EXPECT_THAT(output, ::testing::HasSubstr("Date: "));
    EXPECT_THAT(output, ::testing::HasSubstr("2023-06-15"));
}

// Test empty string value
TEST_F(PrintISODateTest_2666, EmptyStringValue_2666) {
    addDateEntry("CreationDate", "");
    auto uMap = UnicodeMap::parse("Latin1");
    std::string output = captureStdout([&]() {
        printISODate(dict, "CreationDate", "Date: ", uMap.get());
    });
    // Empty string is still a string object, so label is printed
    EXPECT_THAT(output, ::testing::HasSubstr("Date: "));
}

// Test label text is printed correctly
TEST_F(PrintISODateTest_2666, LabelTextPrinted_2666) {
    addDateEntry("CreationDate", "D:20230101000000Z");
    auto uMap = UnicodeMap::parse("Latin1");
    std::string output = captureStdout([&]() {
        printISODate(dict, "CreationDate", "Custom Label: ", uMap.get());
    });
    EXPECT_THAT(output, ::testing::StartsWith("Custom Label: "));
}

// Test boundary date - year boundaries
TEST_F(PrintISODateTest_2666, BoundaryDateMinValues_2666) {
    addDateEntry("CreationDate", "D:00010101000000Z");
    auto uMap = UnicodeMap::parse("Latin1");
    std::string output = captureStdout([&]() {
        printISODate(dict, "CreationDate", "Date: ", uMap.get());
    });
    EXPECT_THAT(output, ::testing::HasSubstr("Date: "));
    if (output.find("0001-01-01") != std::string::npos) {
        EXPECT_THAT(output, ::testing::HasSubstr("0001-01-01T00:00:00Z"));
    }
}

// Test date with positive timezone and non-zero minutes
TEST_F(PrintISODateTest_2666, PositiveOffsetWithMinutes_2666) {
    addDateEntry("ModDate", "D:20231225235959+09'30");
    auto uMap = UnicodeMap::parse("Latin1");
    std::string output = captureStdout([&]() {
        printISODate(dict, "ModDate", "Modified: ", uMap.get());
    });
    EXPECT_THAT(output, ::testing::HasSubstr("Modified: "));
    EXPECT_THAT(output, ::testing::HasSubstr("2023-12-25T23:59:59"));
}
