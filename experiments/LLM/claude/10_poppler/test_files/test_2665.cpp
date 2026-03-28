#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <memory>
#include <string>

#include "poppler/Dict.h"
#include "poppler/Object.h"
#include "poppler/UnicodeMap.h"
#include "poppler/GooString.h"
#include "poppler/DateInfo.h"

// Forward declaration - the function under test is static in pdfinfo.cc
// We need to include it or make it accessible for testing.
// Since it's static, we include the source or use a test wrapper.
// For the purpose of this test, we assume we can access printInfoDate.

// We'll include the source file to get access to the static function
// This is a common technique for testing static functions
#include "utils/pdfinfo.cc"

class PrintInfoDateTest_2665 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a basic UnicodeMap for testing
        // Using Latin1 encoding as a simple encoding
        uMap = UnicodeMap::parse("Latin1");
    }

    void TearDown() override {
    }

    std::string captureStdout(std::function<void()> func) {
        // Redirect stdout to a temporary file
        fflush(stdout);
        int saved_stdout = dup(fileno(stdout));
        
        char tmpfile[] = "/tmp/test_stdout_XXXXXX";
        int fd = mkstemp(tmpfile);
        dup2(fd, fileno(stdout));
        
        func();
        
        fflush(stdout);
        dup2(saved_stdout, fileno(stdout));
        close(saved_stdout);
        
        // Read the captured output
        lseek(fd, 0, SEEK_SET);
        char buf[4096] = {};
        ssize_t n = read(fd, buf, sizeof(buf) - 1);
        close(fd);
        unlink(tmpfile);
        
        if (n > 0) {
            buf[n] = '\0';
            return std::string(buf);
        }
        return "";
    }

    std::unique_ptr<UnicodeMap> uMap;
};

// Test that when key is not found in dict, nothing is printed
TEST_F(PrintInfoDateTest_2665, KeyNotFound_NoOutput_2665) {
    Dict dict(nullptr);
    // Don't add any entries - lookup should return a non-string Object
    
    std::string output = captureStdout([&]() {
        printInfoDate(&dict, "CreationDate", "CreationDate:  ", uMap.get());
    });
    
    EXPECT_TRUE(output.empty());
}

// Test that when key exists but is not a string (e.g., integer), nothing is printed
TEST_F(PrintInfoDateTest_2665, KeyExistsButNotString_NoOutput_2665) {
    Dict dict(nullptr);
    dict.add("SomeKey", Object(42));
    
    std::string output = captureStdout([&]() {
        printInfoDate(&dict, "SomeKey", "SomeKey:  ", uMap.get());
    });
    
    EXPECT_TRUE(output.empty());
}

// Test with a valid PDF date string
TEST_F(PrintInfoDateTest_2665, ValidDateString_PrintsFormattedDate_2665) {
    Dict dict(nullptr);
    // PDF date format: D:YYYYMMDDHHmmSSOHH'mm
    auto dateStr = std::make_unique<GooString>("D:20230615120000+00'00");
    dict.add("CreationDate", Object(std::move(dateStr)));
    
    std::string output = captureStdout([&]() {
        printInfoDate(&dict, "CreationDate", "CreationDate:  ", uMap.get());
    });
    
    // Should start with the text prefix
    EXPECT_TRUE(output.find("CreationDate:  ") == 0);
    // Should end with newline
    EXPECT_FALSE(output.empty());
    EXPECT_EQ(output.back(), '\n');
}

// Test with an invalid date string (not parseable as date)
TEST_F(PrintInfoDateTest_2665, InvalidDateString_PrintsRawString_2665) {
    Dict dict(nullptr);
    auto dateStr = std::make_unique<GooString>("not-a-date");
    dict.add("CreationDate", Object(std::move(dateStr)));
    
    std::string output = captureStdout([&]() {
        printInfoDate(&dict, "CreationDate", "CreationDate:  ", uMap.get());
    });
    
    // Should start with the text prefix
    EXPECT_TRUE(output.find("CreationDate:  ") == 0);
    // Should end with newline
    EXPECT_FALSE(output.empty());
    EXPECT_EQ(output.back(), '\n');
}

// Test with a valid date string with negative timezone offset
TEST_F(PrintInfoDateTest_2665, ValidDateNegativeTimezone_PrintsFormattedDate_2665) {
    Dict dict(nullptr);
    auto dateStr = std::make_unique<GooString>("D:20230615120000-05'00");
    dict.add("ModDate", Object(std::move(dateStr)));
    
    std::string output = captureStdout([&]() {
        printInfoDate(&dict, "ModDate", "ModDate:       ", uMap.get());
    });
    
    EXPECT_TRUE(output.find("ModDate:       ") == 0);
    EXPECT_FALSE(output.empty());
    EXPECT_EQ(output.back(), '\n');
}

// Test with a valid date string with positive timezone offset
TEST_F(PrintInfoDateTest_2665, ValidDatePositiveTimezone_PrintsFormattedDate_2665) {
    Dict dict(nullptr);
    auto dateStr = std::make_unique<GooString>("D:20230101000000+05'30");
    dict.add("CreationDate", Object(std::move(dateStr)));
    
    std::string output = captureStdout([&]() {
        printInfoDate(&dict, "CreationDate", "Created:  ", uMap.get());
    });
    
    EXPECT_TRUE(output.find("Created:  ") == 0);
    EXPECT_EQ(output.back(), '\n');
}

// Test with different text labels
TEST_F(PrintInfoDateTest_2665, DifferentTextLabel_PrintsCorrectPrefix_2665) {
    Dict dict(nullptr);
    auto dateStr = std::make_unique<GooString>("D:20200101120000Z");
    dict.add("ModDate", Object(std::move(dateStr)));
    
    std::string output = captureStdout([&]() {
        printInfoDate(&dict, "ModDate", "Modified: ", uMap.get());
    });
    
    EXPECT_TRUE(output.find("Modified: ") == 0);
    EXPECT_EQ(output.back(), '\n');
}

// Test with empty string value
TEST_F(PrintInfoDateTest_2665, EmptyStringValue_PrintsTextAndNewline_2665) {
    Dict dict(nullptr);
    auto dateStr = std::make_unique<GooString>("");
    dict.add("CreationDate", Object(std::move(dateStr)));
    
    std::string output = captureStdout([&]() {
        printInfoDate(&dict, "CreationDate", "Date: ", uMap.get());
    });
    
    // Should still print the prefix and a newline since it's a string object
    EXPECT_TRUE(output.find("Date: ") == 0);
    EXPECT_EQ(output.back(), '\n');
}

// Test with a date string that starts with D: but has partial info
TEST_F(PrintInfoDateTest_2665, PartialDateString_2665) {
    Dict dict(nullptr);
    auto dateStr = std::make_unique<GooString>("D:2023");
    dict.add("CreationDate", Object(std::move(dateStr)));
    
    std::string output = captureStdout([&]() {
        printInfoDate(&dict, "CreationDate", "Date: ", uMap.get());
    });
    
    EXPECT_TRUE(output.find("Date: ") == 0);
    EXPECT_EQ(output.back(), '\n');
}

// Test with null Object (key present but null value)
TEST_F(PrintInfoDateTest_2665, NullObjectValue_NoOutput_2665) {
    Dict dict(nullptr);
    dict.add("CreationDate", Object(objNull));
    
    std::string output = captureStdout([&]() {
        printInfoDate(&dict, "CreationDate", "Date: ", uMap.get());
    });
    
    EXPECT_TRUE(output.empty());
}

// Test with a well-known date to verify timezone handling
TEST_F(PrintInfoDateTest_2665, SpecificDateUTC_2665) {
    Dict dict(nullptr);
    // UTC date: June 15, 2023, 12:00:00 UTC
    auto dateStr = std::make_unique<GooString>("D:20230615120000+00'00");
    dict.add("CreationDate", Object(std::move(dateStr)));
    
    std::string output = captureStdout([&]() {
        printInfoDate(&dict, "CreationDate", "Created: ", uMap.get());
    });
    
    // Verify prefix is present
    EXPECT_TRUE(output.find("Created: ") == 0);
    // Verify it contains some date-like content (year should appear)
    // The exact format depends on locale, but the year should be present
    EXPECT_TRUE(output.find("2023") != std::string::npos || output.find("23") != std::string::npos);
    EXPECT_EQ(output.back(), '\n');
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
