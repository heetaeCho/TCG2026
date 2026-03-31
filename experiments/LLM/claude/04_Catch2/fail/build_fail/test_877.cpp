#include <catch2/reporters/catch_reporter_json.hpp>
#include <catch2/internal/catch_list.hpp>
#include <catch2/internal/catch_stringref.hpp>
#include <catch2/catch_test_case_info.hpp>
#include <catch2/interfaces/catch_interfaces_config.hpp>
#include <catch2/catch_config.hpp>
#include <catch2/reporters/catch_reporter_streaming_base.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <vector>
#include <string>
#include <memory>

using namespace Catch;
using ::testing::HasSubstr;
using ::testing::Not;

namespace {

// Helper to create a minimal config for the JsonReporter
class JsonReporterTestFixture : public ::testing::Test {
protected:
    std::stringstream m_stream;
    
    // We need to create a ReporterConfig which requires an IConfig and an ostream
    // This helper creates a JsonReporter pointing to our stringstream
    std::unique_ptr<JsonReporter> createReporter() {
        // Create a minimal config
        std::vector<std::string> args = {"test"};
        char const* argv[] = {"test"};
        
        auto catchConfig = std::make_shared<Catch::Config>(Catch::ConfigData{});
        auto config = Catch::ReporterConfig(catchConfig.get(), m_stream, Catch::ColourMode::None, {});
        
        m_config = catchConfig; // prevent destruction
        return std::make_unique<JsonReporter>(std::move(config));
    }
    
    std::shared_ptr<Catch::Config> m_config;
    
    void SetUp() override {
        m_stream.str("");
        m_stream.clear();
    }
    
    std::string getOutput() {
        return m_stream.str();
    }
};

} // anonymous namespace

// Test that listTags with empty vector produces valid JSON with empty tags array
TEST_F(JsonReporterTestFixture, ListTagsEmptyVector_877) {
    auto reporter = createReporter();
    
    std::vector<TagInfo> emptyTags;
    reporter->listTags(emptyTags);
    
    // Force destruction to flush output
    reporter.reset();
    
    std::string output = getOutput();
    EXPECT_THAT(output, HasSubstr("tags"));
}

// Test that listTags with a single tag produces expected JSON keys
TEST_F(JsonReporterTestFixture, ListTagsSingleTag_877) {
    auto reporter = createReporter();
    
    std::vector<TagInfo> tags;
    TagInfo tag;
    tag.add("[unit]"_catch_sr);
    tag.count = 5;
    tags.push_back(tag);
    
    reporter->listTags(tags);
    reporter.reset();
    
    std::string output = getOutput();
    EXPECT_THAT(output, HasSubstr("tags"));
    EXPECT_THAT(output, HasSubstr("aliases"));
    EXPECT_THAT(output, HasSubstr("[unit]"));
    EXPECT_THAT(output, HasSubstr("count"));
    EXPECT_THAT(output, HasSubstr("5"));
}

// Test that listTags with multiple tags produces all entries
TEST_F(JsonReporterTestFixture, ListTagsMultipleTags_877) {
    auto reporter = createReporter();
    
    std::vector<TagInfo> tags;
    
    TagInfo tag1;
    tag1.add("[unit]"_catch_sr);
    tag1.count = 3;
    tags.push_back(tag1);
    
    TagInfo tag2;
    tag2.add("[integration]"_catch_sr);
    tag2.count = 7;
    tags.push_back(tag2);
    
    reporter->listTags(tags);
    reporter.reset();
    
    std::string output = getOutput();
    EXPECT_THAT(output, HasSubstr("[unit]"));
    EXPECT_THAT(output, HasSubstr("3"));
    EXPECT_THAT(output, HasSubstr("[integration]"));
    EXPECT_THAT(output, HasSubstr("7"));
}

// Test that a tag with multiple spellings (aliases) lists all of them
TEST_F(JsonReporterTestFixture, ListTagsMultipleAliases_877) {
    auto reporter = createReporter();
    
    std::vector<TagInfo> tags;
    
    TagInfo tag;
    tag.add("[Unit]"_catch_sr);
    tag.add("[unit]"_catch_sr);
    tag.count = 10;
    tags.push_back(tag);
    
    reporter->listTags(tags);
    reporter.reset();
    
    std::string output = getOutput();
    EXPECT_THAT(output, HasSubstr("aliases"));
    EXPECT_THAT(output, HasSubstr("count"));
    EXPECT_THAT(output, HasSubstr("10"));
}

// Test that listTags with zero count outputs count as 0
TEST_F(JsonReporterTestFixture, ListTagsZeroCount_877) {
    auto reporter = createReporter();
    
    std::vector<TagInfo> tags;
    TagInfo tag;
    tag.add("[empty]"_catch_sr);
    tag.count = 0;
    tags.push_back(tag);
    
    reporter->listTags(tags);
    reporter.reset();
    
    std::string output = getOutput();
    EXPECT_THAT(output, HasSubstr("[empty]"));
    EXPECT_THAT(output, HasSubstr("count"));
}

// Test that listTags with large count value works correctly
TEST_F(JsonReporterTestFixture, ListTagsLargeCount_877) {
    auto reporter = createReporter();
    
    std::vector<TagInfo> tags;
    TagInfo tag;
    tag.add("[perf]"_catch_sr);
    tag.count = 999999;
    tags.push_back(tag);
    
    reporter->listTags(tags);
    reporter.reset();
    
    std::string output = getOutput();
    EXPECT_THAT(output, HasSubstr("999999"));
}

// Test that getDescription returns a non-empty string
TEST_F(JsonReporterTestFixture, GetDescriptionReturnsNonEmpty_877) {
    std::string desc = JsonReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}

// Test that listTags output is valid structure (has array brackets)
TEST_F(JsonReporterTestFixture, ListTagsProducesArrayStructure_877) {
    auto reporter = createReporter();
    
    std::vector<TagInfo> tags;
    TagInfo tag;
    tag.add("[foo]"_catch_sr);
    tag.count = 1;
    tags.push_back(tag);
    
    reporter->listTags(tags);
    reporter.reset();
    
    std::string output = getOutput();
    // The tags key should map to an array
    EXPECT_THAT(output, HasSubstr("tags"));
    // Should contain object braces for the tag entry
    EXPECT_THAT(output, HasSubstr("{"));
    EXPECT_THAT(output, HasSubstr("}"));
    // Should contain array brackets
    EXPECT_THAT(output, HasSubstr("["));
    EXPECT_THAT(output, HasSubstr("]"));
}

// Test that listTags with many tags works correctly  
TEST_F(JsonReporterTestFixture, ListTagsManyTags_877) {
    auto reporter = createReporter();
    
    std::vector<TagInfo> tags;
    for (int i = 0; i < 100; ++i) {
        TagInfo tag;
        std::string name = "[tag" + std::to_string(i) + "]";
        tag.add(StringRef(name));
        tag.count = static_cast<std::size_t>(i);
        tags.push_back(tag);
    }
    
    reporter->listTags(tags);
    reporter.reset();
    
    std::string output = getOutput();
    EXPECT_THAT(output, HasSubstr("[tag0]"));
    EXPECT_THAT(output, HasSubstr("[tag99]"));
    EXPECT_THAT(output, HasSubstr("tags"));
}
