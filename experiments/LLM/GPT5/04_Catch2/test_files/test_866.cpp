// File: tests/JsonReporter_WriteCounts_866.tests.cpp

#include <gtest/gtest.h>
#include <sstream>
#include <string>

// Public interfaces we rely on
#include <catch2/catch_totals.hpp>
#include <catch2/internal/catch_jsonwriter.hpp>

// IMPORTANT: The function under test is a TU-local (static) helper inside
// catch_reporter_json.cpp. To treat it as a black-box but still reach it,
// we include the .cpp in this test TU. We only assert on observable output.
#include <catch2/reporters/catch_reporter_json.cpp>

namespace {

/// Small helpers to assert on output without depending on exact whitespace.
size_t findKey(const std::string& s, const std::string& key) {
    // Keys are JSON strings; ensure we search for the quoted key
    std::string needle = "\"" + key + "\"";
    return s.find(needle);
}

testing::AssertionResult containsFieldWithValue(const std::string& s,
                                                const std::string& key,
                                                const std::string& value) {
    const std::string keyQuoted = "\"" + key + "\"";
    const auto keyPos = s.find(keyQuoted);
    if (keyPos == std::string::npos) {
        return testing::AssertionFailure()
               << "Key not found: " << keyQuoted << " in: " << s;
    }
    const auto colonPos = s.find(':', keyPos + keyQuoted.size());
    if (colonPos == std::string::npos) {
        return testing::AssertionFailure()
               << "No ':' after key " << keyQuoted << " in: " << s;
    }
    const auto afterColon = s.substr(colonPos + 1);
    // Allow arbitrary whitespace between ':' and the value
    // Check the value appears somewhere after the colon
    const auto valuePos = afterColon.find(value);
    if (valuePos == std::string::npos) {
        return testing::AssertionFailure()
               << "Value '" << value << "' for key " << keyQuoted
               << " not found in: " << s;
    }
    return testing::AssertionSuccess();
}

} // namespace

// -----------------------------------------------------------------------------
// Normal operation: non-zero counts, verify keys, values, order, and well-formedness
// -----------------------------------------------------------------------------
TEST(JsonReporter_WriteCounts_866, NormalValues_866) {
    std::ostringstream os;
    {
        Catch::Counts counts;
        counts.passed = 3;
        counts.failed = 2;
        counts.failedButOk = 1;
        counts.skipped = 4;

        Catch::JsonObjectWriter obj(os);
        Catch::writeCounts(std::move(obj), counts);
        // obj's destructor should close the JSON object at scope end
    }
    const std::string out = os.str();

    // Contains the 4 fields with correct numeric values
    EXPECT_TRUE(containsFieldWithValue(out, "passed", "3"));
    EXPECT_TRUE(containsFieldWithValue(out, "failed", "2"));
    EXPECT_TRUE(containsFieldWithValue(out, "fail-but-ok", "1"));
    EXPECT_TRUE(containsFieldWithValue(out, "skipped", "4"));

    // Keys appear in the specified order
    const auto pPassed = findKey(out, "passed");
    const auto pFailed = findKey(out, "failed");
    const auto pFailOk = findKey(out, "fail-but-ok");
    const auto pSkipped = findKey(out, "skipped");
    ASSERT_NE(pPassed, std::string::npos);
    ASSERT_NE(pFailed, std::string::npos);
    ASSERT_NE(pFailOk, std::string::npos);
    ASSERT_NE(pSkipped, std::string::npos);
    EXPECT_LT(pPassed, pFailed);
    EXPECT_LT(pFailed, pFailOk);
    EXPECT_LT(pFailOk, pSkipped);

    // Basic well-formedness: starts with '{' and ends with '}'
    EXPECT_FALSE(out.empty());
    EXPECT_EQ(out.front(), '{');
    EXPECT_EQ(out.back(),  '}');

    // No trailing comma like ",}"
    EXPECT_EQ(out.find(",}"), std::string::npos);
}

// -----------------------------------------------------------------------------
// Boundary: all zeros
// -----------------------------------------------------------------------------
TEST(JsonReporter_WriteCounts_866, AllZeros_866) {
    std::ostringstream os;
    {
        Catch::Counts counts; // default-constructed: all zero

        Catch::JsonObjectWriter obj(os);
        Catch::writeCounts(std::move(obj), counts);
    }
    const std::string out = os.str();

    EXPECT_TRUE(containsFieldWithValue(out, "passed", "0"));
    EXPECT_TRUE(containsFieldWithValue(out, "failed", "0"));
    EXPECT_TRUE(containsFieldWithValue(out, "fail-but-ok", "0"));
    EXPECT_TRUE(containsFieldWithValue(out, "skipped", "0"));

    // Order remains unchanged
    const auto pPassed = findKey(out, "passed");
    const auto pFailed = findKey(out, "failed");
    const auto pFailOk = findKey(out, "fail-but-ok");
    const auto pSkipped = findKey(out, "skipped");
    ASSERT_NE(pPassed, std::string::npos);
    ASSERT_NE(pFailed, std::string::npos);
    ASSERT_NE(pFailOk, std::string::npos);
    ASSERT_NE(pSkipped, std::string::npos);
    EXPECT_LT(pPassed, pFailed);
    EXPECT_LT(pFailed, pFailOk);
    EXPECT_LT(pFailOk, pSkipped);
}

// -----------------------------------------------------------------------------
// Boundary: very large values (uint64_t)
// -----------------------------------------------------------------------------
TEST(JsonReporter_WriteCounts_866, LargeValues_866) {
    std::ostringstream os;
    {
        Catch::Counts counts;
        // Use diverse large values; include max for coverage
        const std::uint64_t U64_MAX = std::numeric_limits<std::uint64_t>::max();
        counts.passed = U64_MAX;
        counts.failed = U64_MAX - 1;
        counts.failedButOk = 42ULL * 1000000000000ULL; // 4.2e13
        counts.skipped = 9999999999ULL;

        Catch::JsonObjectWriter obj(os);
        Catch::writeCounts(std::move(obj), counts);
    }
    const std::string out = os.str();

    EXPECT_TRUE(containsFieldWithValue(out, "passed", std::to_string(std::numeric_limits<std::uint64_t>::max())));
    EXPECT_TRUE(containsFieldWithValue(out, "failed", std::to_string(std::numeric_limits<std::uint64_t>::max() - 1)));
    EXPECT_TRUE(containsFieldWithValue(out, "fail-but-ok", "42000000000000"));
    EXPECT_TRUE(containsFieldWithValue(out, "skipped", "9999999999"));

    // Still no trailing comma
    EXPECT_EQ(out.find(",}"), std::string::npos);
}

// -----------------------------------------------------------------------------
// Formatting sanity: exactly 3 commas for 4 fields (not strict on whitespace)
// -----------------------------------------------------------------------------
TEST(JsonReporter_WriteCounts_866, CommaCount_NoTrailingComma_866) {
    std::ostringstream os;
    {
        Catch::Counts counts;
        counts.passed = 1;
        counts.failed = 2;
        counts.failedButOk = 3;
        counts.skipped = 4;

        Catch::JsonObjectWriter obj(os);
        Catch::writeCounts(std::move(obj), counts);
    }
    const std::string out = os.str();

    // Count commas — for 4 fields there should be 3 commas separating entries.
    size_t commaCount = 0;
    for (char c : out) {
        if (c == ',') ++commaCount;
    }
    EXPECT_EQ(commaCount, 3u);

    // No trailing comma pattern
    EXPECT_EQ(out.find(",}"), std::string::npos);
}
