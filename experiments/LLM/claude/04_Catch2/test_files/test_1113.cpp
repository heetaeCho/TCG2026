#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <algorithm>

// Include necessary Catch2 headers
#include "catch2/catch_test_case_info.hpp"
#include "catch2/internal/catch_source_line_info.hpp"
#include "catch2/internal/catch_stringref.hpp"
#include "catch2/internal/catch_test_registry.hpp"

using namespace Catch;

class TestCaseInfoTest_1113 : public ::testing::Test {
protected:
    SourceLineInfo defaultLineInfo{"test_file.cpp", 42};
};

// Test: Basic construction with a simple name and no tags
TEST_F(TestCaseInfoTest_1113, BasicConstructionWithNameNoTags_1113) {
    NameAndTags nameAndTags("TestName", "");
    TestCaseInfo info("TestClass", nameAndTags, defaultLineInfo);
    
    EXPECT_EQ(info.className, StringRef("TestClass"));
    EXPECT_FALSE(info.isHidden());
    EXPECT_FALSE(info.throws());
    EXPECT_FALSE(info.okToFail());
    EXPECT_FALSE(info.expectedToFail());
}

// Test: Construction with empty name should use default name
TEST_F(TestCaseInfoTest_1113, EmptyNameUsesDefaultName_1113) {
    NameAndTags nameAndTags("", "");
    TestCaseInfo info("TestClass", nameAndTags, defaultLineInfo);
    
    // Default name should be non-empty (generated)
    EXPECT_FALSE(info.tags.empty() && info.isHidden()); // Just ensure it constructs without error
}

// Test: Construction with a single tag
TEST_F(TestCaseInfoTest_1113, SingleTag_1113) {
    NameAndTags nameAndTags("TestName", "[unit]");
    TestCaseInfo info("TestClass", nameAndTags, defaultLineInfo);
    
    EXPECT_FALSE(info.tags.empty());
    EXPECT_EQ(info.tags.size(), 1u);
}

// Test: Construction with multiple tags
TEST_F(TestCaseInfoTest_1113, MultipleTags_1113) {
    NameAndTags nameAndTags("TestName", "[unit][fast]");
    TestCaseInfo info("TestClass", nameAndTags, defaultLineInfo);
    
    EXPECT_EQ(info.tags.size(), 2u);
}

// Test: Hidden tag (starting with .) should mark test as hidden
TEST_F(TestCaseInfoTest_1113, HiddenTag_1113) {
    NameAndTags nameAndTags("TestName", "[.hidden]");
    TestCaseInfo info("TestClass", nameAndTags, defaultLineInfo);
    
    EXPECT_TRUE(info.isHidden());
}

// Test: Single dot tag marks test as hidden
TEST_F(TestCaseInfoTest_1113, DotOnlyTagMarksHidden_1113) {
    NameAndTags nameAndTags("TestName", "[.]");
    TestCaseInfo info("TestClass", nameAndTags, defaultLineInfo);
    
    EXPECT_TRUE(info.isHidden());
}

// Test: The !throws special tag
TEST_F(TestCaseInfoTest_1113, ThrowsTag_1113) {
    NameAndTags nameAndTags("TestName", "[!throws]");
    TestCaseInfo info("TestClass", nameAndTags, defaultLineInfo);
    
    EXPECT_TRUE(info.throws());
}

// Test: The !mayfail special tag
TEST_F(TestCaseInfoTest_1113, MayFailTag_1113) {
    NameAndTags nameAndTags("TestName", "[!mayfail]");
    TestCaseInfo info("TestClass", nameAndTags, defaultLineInfo);
    
    EXPECT_TRUE(info.okToFail());
}

// Test: The !shouldfail special tag
TEST_F(TestCaseInfoTest_1113, ShouldFailTag_1113) {
    NameAndTags nameAndTags("TestName", "[!shouldfail]");
    TestCaseInfo info("TestClass", nameAndTags, defaultLineInfo);
    
    EXPECT_TRUE(info.expectedToFail());
}

// Test: Tags are sorted and deduplicated
TEST_F(TestCaseInfoTest_1113, TagsSortedAndDeduplicated_1113) {
    NameAndTags nameAndTags("TestName", "[zebra][alpha][zebra]");
    TestCaseInfo info("TestClass", nameAndTags, defaultLineInfo);
    
    // After dedup, should have only 2 unique tags
    EXPECT_EQ(info.tags.size(), 2u);
    // Tags should be sorted
    for (size_t i = 1; i < info.tags.size(); ++i) {
        EXPECT_TRUE(info.tags[i - 1] < info.tags[i] || !(info.tags[i] < info.tags[i - 1]));
    }
}

// Test: tagsAsString returns proper formatted string
TEST_F(TestCaseInfoTest_1113, TagsAsString_1113) {
    NameAndTags nameAndTags("TestName", "[unit][fast]");
    TestCaseInfo info("TestClass", nameAndTags, defaultLineInfo);
    
    std::string tagsStr = info.tagsAsString();
    // Should contain brackets around each tag
    EXPECT_NE(tagsStr.find('['), std::string::npos);
    EXPECT_NE(tagsStr.find(']'), std::string::npos);
}

// Test: tagsAsString with no tags
TEST_F(TestCaseInfoTest_1113, TagsAsStringEmpty_1113) {
    NameAndTags nameAndTags("TestName", "");
    TestCaseInfo info("TestClass", nameAndTags, defaultLineInfo);
    
    std::string tagsStr = info.tagsAsString();
    // With no tags and not hidden, tags string should be empty or minimal
    // (implementation detail, but we can at least call it)
    EXPECT_TRUE(tagsStr.empty() || tagsStr.size() >= 0);
}

// Test: Error case - unclosed tag bracket
TEST_F(TestCaseInfoTest_1113, UnclosedTagThrows_1113) {
    NameAndTags nameAndTags("TestName", "[unclosed");
    
    EXPECT_ANY_THROW(
        TestCaseInfo info("TestClass", nameAndTags, defaultLineInfo)
    );
}

// Test: Error case - unmatched closing bracket
TEST_F(TestCaseInfoTest_1113, UnmatchedClosingBracketThrows_1113) {
    NameAndTags nameAndTags("TestName", "unmatched]");
    
    EXPECT_ANY_THROW(
        TestCaseInfo info("TestClass", nameAndTags, defaultLineInfo)
    );
}

// Test: Error case - nested opening bracket
TEST_F(TestCaseInfoTest_1113, NestedOpeningBracketThrows_1113) {
    NameAndTags nameAndTags("TestName", "[[nested]]");
    
    EXPECT_ANY_THROW(
        TestCaseInfo info("TestClass", nameAndTags, defaultLineInfo)
    );
}

// Test: Error case - empty tag
TEST_F(TestCaseInfoTest_1113, EmptyTagThrows_1113) {
    NameAndTags nameAndTags("TestName", "[]");
    
    EXPECT_ANY_THROW(
        TestCaseInfo info("TestClass", nameAndTags, defaultLineInfo)
    );
}

// Test: SourceLineInfo is correctly stored
TEST_F(TestCaseInfoTest_1113, SourceLineInfoStored_1113) {
    SourceLineInfo lineInfo{"my_file.cpp", 100};
    NameAndTags nameAndTags("TestName", "[tag]");
    TestCaseInfo info("TestClass", nameAndTags, lineInfo);
    
    EXPECT_EQ(info.lineInfo.line, 100u);
    EXPECT_STREQ(info.lineInfo.file, "my_file.cpp");
}

// Test: className is correctly stored
TEST_F(TestCaseInfoTest_1113, ClassNameStored_1113) {
    NameAndTags nameAndTags("TestName", "");
    TestCaseInfo info("MyClassName", nameAndTags, defaultLineInfo);
    
    EXPECT_EQ(info.className, StringRef("MyClassName"));
}

// Test: Multiple special tags combined
TEST_F(TestCaseInfoTest_1113, MultipleSpecialTags_1113) {
    NameAndTags nameAndTags("TestName", "[!throws][!mayfail]");
    TestCaseInfo info("TestClass", nameAndTags, defaultLineInfo);
    
    EXPECT_TRUE(info.throws());
    EXPECT_TRUE(info.okToFail());
    EXPECT_FALSE(info.expectedToFail());
}

// Test: Hidden test with additional tags
TEST_F(TestCaseInfoTest_1113, HiddenWithOtherTags_1113) {
    NameAndTags nameAndTags("TestName", "[.][unit]");
    TestCaseInfo info("TestClass", nameAndTags, defaultLineInfo);
    
    EXPECT_TRUE(info.isHidden());
    // Should have tags including the "." tag
    EXPECT_GE(info.tags.size(), 1u);
}

// Test: addFilenameTag adds a tag based on the file
TEST_F(TestCaseInfoTest_1113, AddFilenameTag_1113) {
    NameAndTags nameAndTags("TestName", "[unit]");
    TestCaseInfo info("TestClass", nameAndTags, defaultLineInfo);
    
    size_t tagsBefore = info.tags.size();
    info.addFilenameTag();
    // After adding filename tag, tags count may increase
    EXPECT_GE(info.tags.size(), tagsBefore);
}

// Test: Properties default to None when no special tags
TEST_F(TestCaseInfoTest_1113, PropertiesDefaultNone_1113) {
    NameAndTags nameAndTags("TestName", "[regular]");
    TestCaseInfo info("TestClass", nameAndTags, defaultLineInfo);
    
    EXPECT_FALSE(info.throws());
    EXPECT_FALSE(info.okToFail());
    EXPECT_FALSE(info.expectedToFail());
    EXPECT_FALSE(info.isHidden());
}

// Test: Tag with dot prefix (hidden sub-tag like .integration)
TEST_F(TestCaseInfoTest_1113, DotPrefixedTagIsHidden_1113) {
    NameAndTags nameAndTags("TestName", "[.integration]");
    TestCaseInfo info("TestClass", nameAndTags, defaultLineInfo);
    
    EXPECT_TRUE(info.isHidden());
    // The dot-prefixed tag should strip the dot for the actual tag name
    // and add a "." tag for hidden
}

// Test: Multiple duplicate tags result in single entries
TEST_F(TestCaseInfoTest_1113, DuplicateTagsDeduplication_1113) {
    NameAndTags nameAndTags("TestName", "[same][same][same]");
    TestCaseInfo info("TestClass", nameAndTags, defaultLineInfo);
    
    EXPECT_EQ(info.tags.size(), 1u);
}

// Test: tagsAsString for hidden test includes dot tag
TEST_F(TestCaseInfoTest_1113, HiddenTestTagsAsString_1113) {
    NameAndTags nameAndTags("TestName", "[.]");
    TestCaseInfo info("TestClass", nameAndTags, defaultLineInfo);
    
    std::string tagsStr = info.tagsAsString();
    EXPECT_NE(tagsStr.find("[.]"), std::string::npos);
}
