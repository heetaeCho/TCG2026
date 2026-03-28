#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <memory>

#include "catch2/reporters/catch_reporter_xml.hpp"
#include "catch2/internal/catch_xmlwriter.hpp"
#include "catch2/internal/catch_list.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/catch_session.hpp"
#include "catch2/reporters/catch_reporter_registrars.hpp"
#include "catch2/internal/catch_reporter_spec_parser.hpp"

using namespace Catch;

namespace {

// Helper to create a minimal ReporterConfig pointing to our stringstream
class XmlReporterTestFixture_850 : public ::testing::Test {
protected:
    std::stringstream ss;
    
    std::unique_ptr<XmlReporter> createReporter() {
        // We need to create a proper ReporterConfig
        // Use a ConfigData and Config to build it
        auto configData = ConfigData{};
        auto config = std::make_shared<Config>(configData);
        auto prefs = ReporterConfig(config.get(), ss, ColourMode::None, {});
        m_config = config; // prevent destruction
        return std::make_unique<XmlReporter>(CATCH_MOVE(prefs));
    }
    
    std::shared_ptr<Config> m_config;
};

} // anonymous namespace

TEST_F(XmlReporterTestFixture_850, ListTagsEmptyVector_850) {
    auto reporter = createReporter();
    std::vector<TagInfo> tags;
    reporter->listTags(tags);
    
    std::string output = ss.str();
    // Should contain the outer element even if empty
    EXPECT_NE(output.find("TagsFromMatchingTests"), std::string::npos);
}

TEST_F(XmlReporterTestFixture_850, ListTagsSingleTagSingleAlias_850) {
    auto reporter = createReporter();
    
    std::vector<TagInfo> tags;
    TagInfo tag1;
    tag1.add("[unit]"_catch_sr);
    tag1.count = 5;
    tags.push_back(tag1);
    
    reporter->listTags(tags);
    
    std::string output = ss.str();
    EXPECT_NE(output.find("TagsFromMatchingTests"), std::string::npos);
    EXPECT_NE(output.find("<Tag"), std::string::npos);
    EXPECT_NE(output.find("<Count"), std::string::npos);
    EXPECT_NE(output.find("5"), std::string::npos);
    EXPECT_NE(output.find("<Aliases"), std::string::npos);
    EXPECT_NE(output.find("<Alias"), std::string::npos);
    EXPECT_NE(output.find("[unit]"), std::string::npos);
}

TEST_F(XmlReporterTestFixture_850, ListTagsSingleTagMultipleAliases_850) {
    auto reporter = createReporter();
    
    std::vector<TagInfo> tags;
    TagInfo tag1;
    tag1.add("[Unit]"_catch_sr);
    tag1.add("[UNIT]"_catch_sr);
    tag1.count = 3;
    tags.push_back(tag1);
    
    reporter->listTags(tags);
    
    std::string output = ss.str();
    EXPECT_NE(output.find("TagsFromMatchingTests"), std::string::npos);
    EXPECT_NE(output.find("3"), std::string::npos);
    EXPECT_NE(output.find("[Unit]"), std::string::npos);
    EXPECT_NE(output.find("[UNIT]"), std::string::npos);
}

TEST_F(XmlReporterTestFixture_850, ListTagsMultipleTags_850) {
    auto reporter = createReporter();
    
    std::vector<TagInfo> tags;
    
    TagInfo tag1;
    tag1.add("[unit]"_catch_sr);
    tag1.count = 2;
    tags.push_back(tag1);
    
    TagInfo tag2;
    tag2.add("[integration]"_catch_sr);
    tag2.count = 7;
    tags.push_back(tag2);
    
    reporter->listTags(tags);
    
    std::string output = ss.str();
    EXPECT_NE(output.find("TagsFromMatchingTests"), std::string::npos);
    EXPECT_NE(output.find("2"), std::string::npos);
    EXPECT_NE(output.find("[unit]"), std::string::npos);
    EXPECT_NE(output.find("7"), std::string::npos);
    EXPECT_NE(output.find("[integration]"), std::string::npos);
}

TEST_F(XmlReporterTestFixture_850, ListTagsCountZero_850) {
    auto reporter = createReporter();
    
    std::vector<TagInfo> tags;
    TagInfo tag1;
    tag1.add("[empty]"_catch_sr);
    tag1.count = 0;
    tags.push_back(tag1);
    
    reporter->listTags(tags);
    
    std::string output = ss.str();
    EXPECT_NE(output.find("TagsFromMatchingTests"), std::string::npos);
    EXPECT_NE(output.find("<Count"), std::string::npos);
    EXPECT_NE(output.find("0"), std::string::npos);
    EXPECT_NE(output.find("[empty]"), std::string::npos);
}

TEST_F(XmlReporterTestFixture_850, ListTagsLargeCount_850) {
    auto reporter = createReporter();
    
    std::vector<TagInfo> tags;
    TagInfo tag1;
    tag1.add("[perf]"_catch_sr);
    tag1.count = 999999;
    tags.push_back(tag1);
    
    reporter->listTags(tags);
    
    std::string output = ss.str();
    EXPECT_NE(output.find("999999"), std::string::npos);
    EXPECT_NE(output.find("[perf]"), std::string::npos);
}

TEST_F(XmlReporterTestFixture_850, ListTagsProducesWellFormedXml_850) {
    auto reporter = createReporter();
    
    std::vector<TagInfo> tags;
    TagInfo tag1;
    tag1.add("[test]"_catch_sr);
    tag1.count = 1;
    tags.push_back(tag1);
    
    reporter->listTags(tags);
    
    std::string output = ss.str();
    
    // Check that closing tags exist
    EXPECT_NE(output.find("</Count>"), std::string::npos);
    EXPECT_NE(output.find("</Alias>"), std::string::npos);
    EXPECT_NE(output.find("</Aliases>"), std::string::npos);
    EXPECT_NE(output.find("</Tag>"), std::string::npos);
    EXPECT_NE(output.find("</TagsFromMatchingTests>"), std::string::npos);
}

TEST_F(XmlReporterTestFixture_850, ListTagsNoSpellings_850) {
    auto reporter = createReporter();
    
    std::vector<TagInfo> tags;
    TagInfo tag1;
    // No spellings added, just a count
    tag1.count = 10;
    tags.push_back(tag1);
    
    reporter->listTags(tags);
    
    std::string output = ss.str();
    EXPECT_NE(output.find("TagsFromMatchingTests"), std::string::npos);
    EXPECT_NE(output.find("10"), std::string::npos);
    EXPECT_NE(output.find("<Aliases"), std::string::npos);
    // Aliases section should exist but have no Alias children
    // The closing tag should directly follow opening
}

TEST_F(XmlReporterTestFixture_850, ListTagsOrderOfElements_850) {
    auto reporter = createReporter();
    
    std::vector<TagInfo> tags;
    TagInfo tag1;
    tag1.add("[alpha]"_catch_sr);
    tag1.count = 42;
    tags.push_back(tag1);
    
    reporter->listTags(tags);
    
    std::string output = ss.str();
    
    // Count should appear before Aliases
    auto countPos = output.find("<Count");
    auto aliasesPos = output.find("<Aliases");
    ASSERT_NE(countPos, std::string::npos);
    ASSERT_NE(aliasesPos, std::string::npos);
    EXPECT_LT(countPos, aliasesPos);
}
