// File: tests/test_testcaseinfo_tags_1000.cpp

#include <gtest/gtest.h>
#include <string>
#include <vector>

// Assume the project’s public headers are available:
#include <catch2/catch_test_case_info.hpp>
#include <catch2/internal/catch_source_line_info.hpp>
#include <catch2/internal/catch_stringref.hpp>

namespace {

using Catch::StringRef;
using Catch::Tag;
using Catch::TestCaseInfo;
using Catch::SourceLineInfo;

// Helper: create a minimally valid TestCaseInfo and let tests fill its public `tags`.
static TestCaseInfo makeEmptyTCI() {
    // `NameAndTags` is defined by Catch2; construct with an empty name/tags.
    Catch::NameAndTags nt;
    nt.name = "";
    nt.tags = "";

    // Any reasonable source location is fine; behavior under test does not depend on it.
    SourceLineInfo sli{"dummy.cpp", 1};

    return TestCaseInfo(StringRef(""), nt, sli);
}

struct TestCaseInfoTags_1000 : ::testing::Test {
    TestCaseInfo tci = makeEmptyTCI();
};

} // namespace

// [Normal] No tags -> empty string
TEST_F(TestCaseInfoTags_1000, EmptyTags_ReturnsEmptyString_1000) {
    tci.tags.clear();

    const std::string out = tci.tagsAsString();

    EXPECT_TRUE(out.empty());
}

// [Normal] Single tag -> bracketed once
TEST_F(TestCaseInfoTags_1000, SingleTag_ReturnsBracketed_1000) {
    tci.tags = { Tag{StringRef("fast")} };

    const std::string out = tci.tagsAsString();

    EXPECT_EQ(out, "[fast]");
}

// [Normal] Multiple tags -> concatenated in insertion order
TEST_F(TestCaseInfoTags_1000, MultipleTags_ConcatenatedInOrder_1000) {
    tci.tags = {
        Tag{StringRef("fast")},
        Tag{StringRef("db")},
        Tag{StringRef("integration")}
    };

    const std::string out = tci.tagsAsString();

    EXPECT_EQ(out, "[fast][db][integration]");
}

// [Boundary] Handles empty and unicode-like tag text without crashing; preserves content verbatim
TEST_F(TestCaseInfoTags_1000, EmptyAndUnicodeTags_PreservedVerbatim_1000) {
    // An empty tag is legal via interface (Tag holds a StringRef). Also include multi-byte content.
    tci.tags = {
        Tag{StringRef("")},                // empty
        Tag{StringRef("🚀")},              // emoji (UTF-8)
        Tag{StringRef("Καλό")},            // Greek
        Tag{StringRef("space tag")}        // includes space
    };

    const std::string out = tci.tagsAsString();

    // Expect brackets around each original, in order, with no extra separators.
    EXPECT_EQ(out, "[][🚀][Καλό][space tag]");
}

// [Boundary/Scale] Many tags -> length and pattern consistent (no extra delimiters)
TEST_F(TestCaseInfoTags_1000, ManyTags_NoExtraDelimiters_1000) {
    // Build 100 simple tags: t0, t1, ..., t99
    std::vector<Tag> many;
    many.reserve(100);
    size_t expected_len = 0;

    for (int i = 0; i < 100; ++i) {
        const std::string label = "t" + std::to_string(i);
        many.emplace_back(Tag{StringRef(label)});
        expected_len += 2 /*brackets*/ + label.size();
    }
    tci.tags = std::move(many);

    const std::string out = tci.tagsAsString();

    // Check exact size and a couple of sentinel positions to ensure no extra characters are present.
    ASSERT_EQ(out.size(), expected_len);
    // Spot-check start, middle, end
    EXPECT_EQ(out.substr(0, 4), "[t0]");
    EXPECT_NE(out.find("[t50]"), std::string::npos);
    EXPECT_TRUE(out.size() >= 5);
    EXPECT_EQ(out.substr(out.size() - 5), "[t99]");
}
