#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <cstdint>

// Include necessary headers
#include "catch2/catch_totals.hpp"
#include "catch2/internal/catch_jsonwriter.hpp"
#include "catch2/internal/catch_string_manip.hpp"

// We need to access the writeCounts function. Since it's static in the .cpp file,
// we need to either include the cpp or test through the reporter interface.
// However, since writeCounts is a static (file-scope) function, we cannot directly
// call it from outside. We'll test it indirectly through the JsonReporter, or
// we'll include the cpp file to get access.

// Since writeCounts is static in the cpp file, we include it to get access for testing.
// This is a common technique for testing static/internal functions.
#include "catch2/reporters/catch_reporter_json.cpp"

class WriteCountsTest_866 : public ::testing::Test {
protected:
    std::stringstream ss;
};

TEST_F(WriteCountsTest_866, ZeroCounts_866) {
    Catch::Counts counts;
    counts.passed = 0;
    counts.failed = 0;
    counts.failedButOk = 0;
    counts.skipped = 0;

    {
        auto writer = Catch::JsonObjectWriter(ss);
        Catch::writeCounts(std::move(writer), counts);
    }

    std::string output = ss.str();
    // Verify that all four fields are present with value 0
    EXPECT_NE(output.find("\"passed\""), std::string::npos);
    EXPECT_NE(output.find("\"failed\""), std::string::npos);
    EXPECT_NE(output.find("\"fail-but-ok\""), std::string::npos);
    EXPECT_NE(output.find("\"skipped\""), std::string::npos);
    // Check zero values are present
    EXPECT_NE(output.find("0"), std::string::npos);
}

TEST_F(WriteCountsTest_866, NonZeroCounts_866) {
    Catch::Counts counts;
    counts.passed = 10;
    counts.failed = 5;
    counts.failedButOk = 3;
    counts.skipped = 2;

    {
        auto writer = Catch::JsonObjectWriter(ss);
        Catch::writeCounts(std::move(writer), counts);
    }

    std::string output = ss.str();
    EXPECT_NE(output.find("\"passed\""), std::string::npos);
    EXPECT_NE(output.find("10"), std::string::npos);
    EXPECT_NE(output.find("\"failed\""), std::string::npos);
    EXPECT_NE(output.find("5"), std::string::npos);
    EXPECT_NE(output.find("\"fail-but-ok\""), std::string::npos);
    EXPECT_NE(output.find("3"), std::string::npos);
    EXPECT_NE(output.find("\"skipped\""), std::string::npos);
    EXPECT_NE(output.find("2"), std::string::npos);
}

TEST_F(WriteCountsTest_866, LargeValues_866) {
    Catch::Counts counts;
    counts.passed = 1000000;
    counts.failed = 999999;
    counts.failedButOk = 500000;
    counts.skipped = 123456;

    {
        auto writer = Catch::JsonObjectWriter(ss);
        Catch::writeCounts(std::move(writer), counts);
    }

    std::string output = ss.str();
    EXPECT_NE(output.find("1000000"), std::string::npos);
    EXPECT_NE(output.find("999999"), std::string::npos);
    EXPECT_NE(output.find("500000"), std::string::npos);
    EXPECT_NE(output.find("123456"), std::string::npos);
}

TEST_F(WriteCountsTest_866, MaxUint64Values_866) {
    Catch::Counts counts;
    counts.passed = UINT64_MAX;
    counts.failed = 0;
    counts.failedButOk = 0;
    counts.skipped = 0;

    {
        auto writer = Catch::JsonObjectWriter(ss);
        Catch::writeCounts(std::move(writer), counts);
    }

    std::string output = ss.str();
    // UINT64_MAX = 18446744073709551615
    EXPECT_NE(output.find("18446744073709551615"), std::string::npos);
}

TEST_F(WriteCountsTest_866, OnlyPassedNonZero_866) {
    Catch::Counts counts;
    counts.passed = 42;
    counts.failed = 0;
    counts.failedButOk = 0;
    counts.skipped = 0;

    {
        auto writer = Catch::JsonObjectWriter(ss);
        Catch::writeCounts(std::move(writer), counts);
    }

    std::string output = ss.str();
    EXPECT_NE(output.find("\"passed\""), std::string::npos);
    EXPECT_NE(output.find("42"), std::string::npos);
}

TEST_F(WriteCountsTest_866, OnlyFailedNonZero_866) {
    Catch::Counts counts;
    counts.passed = 0;
    counts.failed = 7;
    counts.failedButOk = 0;
    counts.skipped = 0;

    {
        auto writer = Catch::JsonObjectWriter(ss);
        Catch::writeCounts(std::move(writer), counts);
    }

    std::string output = ss.str();
    EXPECT_NE(output.find("\"failed\""), std::string::npos);
    EXPECT_NE(output.find("7"), std::string::npos);
}

TEST_F(WriteCountsTest_866, OnlyFailedButOkNonZero_866) {
    Catch::Counts counts;
    counts.passed = 0;
    counts.failed = 0;
    counts.failedButOk = 15;
    counts.skipped = 0;

    {
        auto writer = Catch::JsonObjectWriter(ss);
        Catch::writeCounts(std::move(writer), counts);
    }

    std::string output = ss.str();
    EXPECT_NE(output.find("\"fail-but-ok\""), std::string::npos);
    EXPECT_NE(output.find("15"), std::string::npos);
}

TEST_F(WriteCountsTest_866, OnlySkippedNonZero_866) {
    Catch::Counts counts;
    counts.passed = 0;
    counts.failed = 0;
    counts.failedButOk = 0;
    counts.skipped = 99;

    {
        auto writer = Catch::JsonObjectWriter(ss);
        Catch::writeCounts(std::move(writer), counts);
    }

    std::string output = ss.str();
    EXPECT_NE(output.find("\"skipped\""), std::string::npos);
    EXPECT_NE(output.find("99"), std::string::npos);
}

TEST_F(WriteCountsTest_866, OutputContainsAllFourKeys_866) {
    Catch::Counts counts;
    counts.passed = 1;
    counts.failed = 2;
    counts.failedButOk = 3;
    counts.skipped = 4;

    {
        auto writer = Catch::JsonObjectWriter(ss);
        Catch::writeCounts(std::move(writer), counts);
    }

    std::string output = ss.str();

    // Verify all keys exist
    EXPECT_NE(output.find("\"passed\""), std::string::npos);
    EXPECT_NE(output.find("\"failed\""), std::string::npos);
    EXPECT_NE(output.find("\"fail-but-ok\""), std::string::npos);
    EXPECT_NE(output.find("\"skipped\""), std::string::npos);

    // Verify the ordering: passed before failed before fail-but-ok before skipped
    auto pos_passed = output.find("\"passed\"");
    auto pos_failed = output.find("\"failed\"");
    auto pos_failbutok = output.find("\"fail-but-ok\"");
    auto pos_skipped = output.find("\"skipped\"");

    EXPECT_LT(pos_passed, pos_failed);
    EXPECT_LT(pos_failed, pos_failbutok);
    EXPECT_LT(pos_failbutok, pos_skipped);
}

TEST_F(WriteCountsTest_866, OutputIsValidJsonStructure_866) {
    Catch::Counts counts;
    counts.passed = 1;
    counts.failed = 2;
    counts.failedButOk = 3;
    counts.skipped = 4;

    {
        auto writer = Catch::JsonObjectWriter(ss);
        Catch::writeCounts(std::move(writer), counts);
    }

    std::string output = ss.str();

    // Should start with { and end with }
    // Trim whitespace
    auto first_brace = output.find('{');
    auto last_brace = output.rfind('}');
    EXPECT_NE(first_brace, std::string::npos);
    EXPECT_NE(last_brace, std::string::npos);
    EXPECT_LT(first_brace, last_brace);
}
