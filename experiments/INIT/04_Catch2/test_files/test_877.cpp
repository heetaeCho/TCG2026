// File: tests/JsonReporter_ListTags_877_Test.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <regex>
#include <vector>
#include <set>

// Catch2 headers (paths may differ slightly in your tree)
#include "catch2/reporters/catch_reporter_json.hpp"
#include "catch2/internal/catch_list.hpp"
#include "catch2/internal/catch_stringref.hpp"

using ::testing::HasSubstr;

namespace {

class JsonReporter_ListTags_Fixture_877 : public ::testing::Test {
protected:
    std::ostringstream out;

    // Helper to create a reporter configured to write into `out`.
    // We rely only on the public JsonReporter constructor signature from the header.
    std::unique_ptr<Catch::JsonReporter> makeReporter() {
        // ReporterConfig’s exact ctor differs slightly across Catch2 versions.
        // In most v3 trees it accepts (IConfig const*, std::ostream&, ColourImpl* = nullptr).
        // Passing nullptr for config is fine for list-only operations.
        Catch::ReporterConfig cfg{ /*fullConfig*/ nullptr, /*stream*/ out };
        return std::make_unique<Catch::JsonReporter>(std::move(cfg));
    }

    static Catch::TagInfo makeTag(std::size_t count,
                                  std::initializer_list<const char*> aliases) {
        Catch::TagInfo ti;
        ti.count = count;
        for (auto* a : aliases) {
            ti.spellings.insert(Catch::StringRef(a));
        }
        return ti;
    }
};

} // namespace

// --- Tests ---

// Normal operation: multiple tags with multiple aliases -> JSON contains "tags" array,
// each entry contains "aliases" array with all spellings and a "count" value.
TEST_F(JsonReporter_ListTags_Fixture_877, MultipleTagsWithAliases_877) {
    auto reporter = makeReporter();

    std::vector<Catch::TagInfo> tags;
    tags.push_back(makeTag(/*count*/3, {"[fast]", "[f]"}));
    tags.push_back(makeTag(/*count*/1, {"[slow]"}));

    reporter->listTags(tags);
    const std::string json = out.str();

    // High-level structure
    EXPECT_THAT(json, HasSubstr("\"tags\"")) << "Output should contain a top-level \"tags\" key";

    // Tag #1 expectations
    EXPECT_THAT(json, HasSubstr("\"aliases\"")) << "Each tag object should contain an \"aliases\" array";
    EXPECT_THAT(json, HasSubstr("[fast]"));
    EXPECT_THAT(json, HasSubstr("[f]"));
    EXPECT_THAT(json, HasSubstr("\"count\"")) << "Each tag object should contain a \"count\" field";
    EXPECT_THAT(json, HasSubstr("3")) << "Tag #1 count should be present";

    // Tag #2 expectations
    EXPECT_THAT(json, HasSubstr("[slow]"));
    EXPECT_THAT(json, HasSubstr("1")) << "Tag #2 count should be present";
}

// Boundary: empty input vector -> still starts listing, but "tags" array is present
// and is empty (we check for the presence of the key and an array delimiter).
TEST_F(JsonReporter_ListTags_Fixture_877, EmptyTagsVector_ProducesEmptyArray_877) {
    auto reporter = makeReporter();

    std::vector<Catch::TagInfo> tags; // empty
    reporter->listTags(tags);
    const std::string json = out.str();

    EXPECT_THAT(json, HasSubstr("\"tags\"")) << "Should still write a \"tags\" key";
    // Loosely verify an empty array without depending on whitespace/formatting
    std::regex emptyArray(R"(\"tags\"\s*:\s*\[\s*\])");
    EXPECT_TRUE(std::regex_search(json, emptyArray))
        << "Expected an empty tags array; got: " << json;
}

// Boundary: a tag with zero aliases -> "aliases" is an empty array; "count" is written.
TEST_F(JsonReporter_ListTags_Fixture_877, SingleTagWithNoAliases_877) {
    auto reporter = makeReporter();

    std::vector<Catch::TagInfo> tags;
    tags.push_back(makeTag(/*count*/5, {})); // no aliases

    reporter->listTags(tags);
    const std::string json = out.str();

    EXPECT_THAT(json, HasSubstr("\"tags\""));

    // Check that the aliases array exists and is empty
    std::regex emptyAliases(R"(\"aliases\"\s*:\s*\[\s*\])");
    EXPECT_TRUE(std::regex_search(json, emptyAliases))
        << "Expected the tag's aliases array to be empty; got: " << json;

    // Count should be present and correct
    std::regex countFive(R"(\"count\"\s*:\s*5)");
    EXPECT_TRUE(std::regex_search(json, countFive))
        << "Expected \"count\": 5; got: " << json;
}

// Exceptional-ish observable case: very large count should still be serialized as a number.
TEST_F(JsonReporter_ListTags_Fixture_877, LargeCountIsSerialized_877) {
    auto reporter = makeReporter();

    std::vector<Catch::TagInfo> tags;
    tags.push_back(makeTag(/*count*/static_cast<std::size_t>(1ULL << 40), {"[huge]"}));

    reporter->listTags(tags);
    const std::string json = out.str();

    EXPECT_THAT(json, HasSubstr("[huge]"));
    // Not relying on exact formatting; just check the decimal is present.
    // We'll stringify the expected value:
    const auto expected = std::to_string(static_cast<unsigned long long>(1ULL << 40));
    EXPECT_THAT(json, HasSubstr(expected)) << "Expected large count to be present";
}
