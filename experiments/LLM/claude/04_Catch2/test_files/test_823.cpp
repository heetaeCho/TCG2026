#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <string>

// Include necessary headers
#include "catch2/reporters/catch_reporter_helpers.hpp"
#include "catch2/internal/catch_list.hpp"
#include "catch2/internal/catch_textflow.hpp"

using namespace Catch;

class DefaultListTagsTest_823 : public ::testing::Test {
protected:
    std::ostringstream out;
};

// Test: When isFiltered is true, the header should say "Tags for matching test cases:"
TEST_F(DefaultListTagsTest_823, FilteredHeaderOutput_823) {
    std::vector<TagInfo> tags;
    defaultListTags(out, tags, true);
    std::string result = out.str();
    EXPECT_NE(result.find("Tags for matching test cases:"), std::string::npos);
}

// Test: When isFiltered is false, the header should say "All available tags:"
TEST_F(DefaultListTagsTest_823, UnfilteredHeaderOutput_823) {
    std::vector<TagInfo> tags;
    defaultListTags(out, tags, false);
    std::string result = out.str();
    EXPECT_NE(result.find("All available tags:"), std::string::npos);
}

// Test: Empty tags vector should output "0 tags"
TEST_F(DefaultListTagsTest_823, EmptyTagsOutputsZeroTags_823) {
    std::vector<TagInfo> tags;
    defaultListTags(out, tags, false);
    std::string result = out.str();
    EXPECT_NE(result.find("0 tags"), std::string::npos);
}

// Test: Single tag should output "1 tag" (singular)
TEST_F(DefaultListTagsTest_823, SingleTagOutputsSingular_823) {
    std::vector<TagInfo> tags;
    TagInfo ti;
    ti.add("[test]"_sr);
    ti.count = 1;
    tags.push_back(ti);
    defaultListTags(out, tags, false);
    std::string result = out.str();
    EXPECT_NE(result.find("1 tag"), std::string::npos);
}

// Test: Multiple tags should output plural "tags"
TEST_F(DefaultListTagsTest_823, MultipleTagsOutputsPlural_823) {
    std::vector<TagInfo> tags;
    
    TagInfo ti1;
    ti1.add("[alpha]"_sr);
    ti1.count = 3;
    tags.push_back(ti1);
    
    TagInfo ti2;
    ti2.add("[beta]"_sr);
    ti2.count = 5;
    tags.push_back(ti2);
    
    defaultListTags(out, tags, false);
    std::string result = out.str();
    EXPECT_NE(result.find("2 tags"), std::string::npos);
}

// Test: Tag info is included in the output
TEST_F(DefaultListTagsTest_823, TagInfoAppearsInOutput_823) {
    std::vector<TagInfo> tags;
    TagInfo ti;
    ti.add("[myspecialtag]"_sr);
    ti.count = 7;
    tags.push_back(ti);
    defaultListTags(out, tags, false);
    std::string result = out.str();
    EXPECT_NE(result.find("[myspecialtag]"), std::string::npos);
    EXPECT_NE(result.find(" 7"), std::string::npos);
}

// Test: Tag count is displayed for each tag
TEST_F(DefaultListTagsTest_823, TagCountIsDisplayed_823) {
    std::vector<TagInfo> tags;
    TagInfo ti;
    ti.add("[counted]"_sr);
    ti.count = 42;
    tags.push_back(ti);
    defaultListTags(out, tags, false);
    std::string result = out.str();
    EXPECT_NE(result.find("42"), std::string::npos);
}

// Test: Output ends with flush (we verify it contains the expected trailing newlines)
TEST_F(DefaultListTagsTest_823, OutputEndsCorrectly_823) {
    std::vector<TagInfo> tags;
    defaultListTags(out, tags, false);
    std::string result = out.str();
    // Should end with "0 tags\n\n"
    EXPECT_GE(result.size(), 2u);
    EXPECT_EQ(result.back(), '\n');
    EXPECT_EQ(result[result.size() - 2], '\n');
}

// Test: Multiple spellings for a single tag
TEST_F(DefaultListTagsTest_823, MultipleSpellingsInTagInfo_823) {
    std::vector<TagInfo> tags;
    TagInfo ti;
    ti.add("[Foo]"_sr);
    ti.add("[foo]"_sr);
    ti.count = 10;
    tags.push_back(ti);
    defaultListTags(out, tags, false);
    std::string result = out.str();
    // The all() method should combine spellings; both should appear
    EXPECT_NE(result.find("10"), std::string::npos);
    EXPECT_NE(result.find("1 tag"), std::string::npos);
}

// Test: Filtered true does NOT contain "All available tags:"
TEST_F(DefaultListTagsTest_823, FilteredDoesNotContainAllAvailable_823) {
    std::vector<TagInfo> tags;
    defaultListTags(out, tags, true);
    std::string result = out.str();
    EXPECT_EQ(result.find("All available tags:"), std::string::npos);
}

// Test: Unfiltered does NOT contain "Tags for matching test cases:"
TEST_F(DefaultListTagsTest_823, UnfilteredDoesNotContainMatching_823) {
    std::vector<TagInfo> tags;
    defaultListTags(out, tags, false);
    std::string result = out.str();
    EXPECT_EQ(result.find("Tags for matching test cases:"), std::string::npos);
}

// Test: Large number of tags
TEST_F(DefaultListTagsTest_823, LargeNumberOfTags_823) {
    std::vector<TagInfo> tags;
    for (int i = 0; i < 100; ++i) {
        TagInfo ti;
        std::string tagName = "[tag" + std::to_string(i) + "]";
        ti.add(StringRef(tagName));
        ti.count = i + 1;
        tags.push_back(ti);
    }
    defaultListTags(out, tags, false);
    std::string result = out.str();
    EXPECT_NE(result.find("100 tags"), std::string::npos);
}

// Test: Tag with count of zero
TEST_F(DefaultListTagsTest_823, TagWithZeroCount_823) {
    std::vector<TagInfo> tags;
    TagInfo ti;
    ti.add("[empty]"_sr);
    ti.count = 0;
    tags.push_back(ti);
    defaultListTags(out, tags, false);
    std::string result = out.str();
    EXPECT_NE(result.find("[empty]"), std::string::npos);
    EXPECT_NE(result.find("1 tag"), std::string::npos);
}

// Test: Output to a fresh stream produces non-empty result
TEST_F(DefaultListTagsTest_823, OutputIsNonEmpty_823) {
    std::vector<TagInfo> tags;
    defaultListTags(out, tags, false);
    EXPECT_FALSE(out.str().empty());
}
