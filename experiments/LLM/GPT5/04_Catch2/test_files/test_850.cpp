// File: tests/xml_reporter_listTags_850.cpp

#include <gtest/gtest.h>
#include <sstream>
#include <regex>
#include <vector>
#include <set>

// Catch2 public headers (paths can vary by repo layout/version)
#include <catch2/reporters/catch_reporter_xml.hpp>
#include <catch2/internal/catch_list.hpp>
#include <catch2/internal/catch_xmlwriter.hpp>

// Depending on Catch2 version, ReporterConfig lives in helpers header:
#include <catch2/reporters/catch_reporter_helpers.hpp>

using namespace Catch;

namespace {

// Small helper that builds a ReporterConfig writing to 'os'.
// Catch2's exact constructor overloads differ by version, so this uses the
// common pattern available in v3.x. If your local signature differs, adjust
// the helper body to your project's ReporterConfig ctor.
ReporterConfig makeConfig(std::ostream& os) {
    // Default-constructed config data with stream override.
    // In Catch2 v3, ReporterConfig takes IConfig const*, ColourMode, std::ostream*, and
    // an optional 'benchmarkNoAnalysis' flag. The helpers header provides a convenience.
    // This overload is widely available:
    return ReporterConfig{ &os };
}

// Extracts the reporter's output after calling listTags
std::string runListTagsAndGetXml(XmlReporter& reporter,
                                 const std::vector<TagInfo>& tags) {
    // Act
    reporter.listTags(tags);
    // The reporter writes directly to the configured stream via XmlWriter.
    // We assume the underlying stream is an std::ostream we own, so the
    // test can read it afterwards via std::ostringstream.
    // (We fetch the stream’s buffer by dynamic_cast from ReporterConfig creation site.)
    // The actual retrieval is done by owning the ostringstream in the test fixture.
    return {}; // not used; see fixture version that returns from its ostringstream
}

} // namespace

class XmlReporter_ListTags_Test_850 : public ::testing::Test {
protected:
    std::ostringstream os;
    std::unique_ptr<XmlReporter> reporter;

    void SetUp() override {
        ReporterConfig cfg = makeConfig(os);
        reporter = std::make_unique<XmlReporter>(std::move(cfg));
    }

    std::string output() const {
        return os.str();
    }
};

// ========== Tests ==========

// Normal operation: emits container + one tag with count and aliases
TEST_F(XmlReporter_ListTags_Test_850, EmitsCountAndAliases_Simple_850) {
    TagInfo t;
    t.count = 3;
    // Public field: spellings is a set of StringRef — inserting via c-strings is fine
    t.spellings.insert(StringRef("[fast]"));
    t.spellings.insert(StringRef("[quick]"));

    std::vector<TagInfo> tags{ t };

    reporter->listTags(tags);
    const std::string xml = output();

    // Must have outer container
    EXPECT_NE(xml.find("TagsFromMatchingTests"), std::string::npos);

    // Must contain one Tag block with Count == 3
    // Keep assertions formatting-insensitive
    EXPECT_NE(xml.find("<Tag"), std::string::npos);

    // Count element with textual "3"
    // Use regex to be tolerant to whitespace/newlines/indent
    EXPECT_TRUE(std::regex_search(xml, std::regex("<Count>\\s*3\\s*</Count>")));

    // Aliases container exists (can be <Aliases>...</Aliases> or <Aliases/> if empty)
    EXPECT_NE(xml.find("Aliases"), std::string::npos);

    // Both aliases present
    EXPECT_NE(xml.find("<Alias>"), std::string::npos);
    EXPECT_NE(xml.find("[fast]"), std::string::npos);
    EXPECT_NE(xml.find("[quick]"), std::string::npos);
}

// Boundary: empty input => only the outer container, no <Tag> entries
TEST_F(XmlReporter_ListTags_Test_850, EmptyInput_EmitsOnlyContainer_850) {
    std::vector<TagInfo> tags; // empty

    reporter->listTags(tags);
    const std::string xml = output();

    // Outer container should be present
    EXPECT_NE(xml.find("TagsFromMatchingTests"), std::string::npos);

    // No Tag entries inside
    EXPECT_EQ(xml.find("<Tag"), std::string::npos);
    EXPECT_EQ(xml.find("</Tag>"), std::string::npos);
}

// Edge/observable behavior: 0-count & duplicate spellings (duplicates removed by set)
TEST_F(XmlReporter_ListTags_Test_850, ZeroCountAndDuplicateAliases_Deduplicated_850) {
    TagInfo t;
    t.count = 0;
    t.spellings.insert(StringRef("[db]"));
    t.spellings.insert(StringRef("[db]")); // duplicate — set keeps one

    std::vector<TagInfo> tags{ t };

    reporter->listTags(tags);
    const std::string xml = output();

    // Count should be "0"
    EXPECT_TRUE(std::regex_search(xml, std::regex("<Count>\\s*0\\s*</Count>")));

    // Aliases container present (may be empty/self-closing if no aliases, but here we have one)
    EXPECT_NE(xml.find("Aliases"), std::string::npos);

    // Exactly one <Alias>[db]</Alias> occurrence.
    // Count occurrences by scanning.
    size_t pos = 0, occurrences = 0;
    const std::string needle = "<Alias>[db]</Alias>";
    while ((pos = xml.find(needle, pos)) != std::string::npos) {
        ++occurrences;
        pos += needle.size();
    }
    EXPECT_EQ(occurrences, 1u);
}

// Multiple tags: preserves vector order for tags and includes each count & aliases
TEST_F(XmlReporter_ListTags_Test_850, MultipleTags_AllRendered_850) {
    TagInfo t1; t1.count = 2;
    t1.spellings.insert(StringRef("[a]"));
    t1.spellings.insert(StringRef("[b]"));

    TagInfo t2; t2.count = 1;
    t2.spellings.insert(StringRef("[x]"));

    std::vector<TagInfo> tags{ t1, t2 };

    reporter->listTags(tags);
    const std::string xml = output();

    // We expect two <Count> entries (2 and 1) and all three aliases present
    // (The relative order of aliases follows std::set ordering; we don't assert order.)
    EXPECT_TRUE(std::regex_search(xml, std::regex("<Count>\\s*2\\s*</Count>")));
    EXPECT_TRUE(std::regex_search(xml, std::regex("<Count>\\s*1\\s*</Count>")));
    EXPECT_NE(xml.find("[a]"), std::string::npos);
    EXPECT_NE(xml.find("[b]"), std::string::npos);
    EXPECT_NE(xml.find("[x]"), std::string::npos);

    // At least two <Tag> sections rendered
    // (Exact counting of tags is formatting-dependent; we conservatively check for 2+)
    size_t pos = 0, tagOpens = 0;
    while ((pos = xml.find("<Tag", pos)) != std::string::npos) {
        ++tagOpens;
        pos += 4;
    }
    EXPECT_GE(tagOpens, 2u);
}
