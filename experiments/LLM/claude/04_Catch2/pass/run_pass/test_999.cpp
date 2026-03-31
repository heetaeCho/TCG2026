#include <gtest/gtest.h>
#include "catch2/catch_test_case_info.hpp"
#include "catch2/internal/catch_source_line_info.hpp"

// We need to include enough of Catch2 to construct TestCaseInfo objects
// If the amalgamated header is available, use it; otherwise individual headers
#include "catch2/catch_all.hpp"

using namespace Catch;

class TestCaseInfoTest_999 : public ::testing::Test {
protected:
    // Helper to create a TestCaseInfo with given parameters
    std::unique_ptr<TestCaseInfo> makeTestCaseInfo(
        const char* className,
        const char* name,
        const char* tags,
        const char* file,
        std::size_t line)
    {
        SourceLineInfo lineInfo(file, line);
        NameAndTags nameAndTags(name, tags);
        // TestCaseInfo is NonCopyable, so we use a unique_ptr
        return std::make_unique<TestCaseInfo>(
            StringRef(className),
            nameAndTags,
            lineInfo
        );
    }
};

// Test that addFilenameTag adds a tag based on the filename
TEST_F(TestCaseInfoTest_999, AddFilenameTagAddsTagFromFilename_999) {
    auto info = makeTestCaseInfo("MyClass", "TestName", "", "/path/to/MyTestFile.cpp", 42);
    
    std::string tagsBefore = info->tagsAsString();
    info->addFilenameTag();
    std::string tagsAfter = info->tagsAsString();
    
    // After adding filename tag, the tags string should be non-empty and different
    EXPECT_NE(tagsBefore, tagsAfter);
    // The tag should contain the filename part (without path and extension typically)
    EXPECT_NE(tagsAfter.find("#"), std::string::npos);
}

// Test that addFilenameTag extracts just the filename portion
TEST_F(TestCaseInfoTest_999, AddFilenameTagExtractsFilenamePart_999) {
    auto info = makeTestCaseInfo("MyClass", "TestName", "", "/some/deep/path/SomeFile.cpp", 10);
    
    info->addFilenameTag();
    std::string tagsStr = info->tagsAsString();
    
    // Should contain the filename (without full path)
    // The tag format should be [#SomeFile.cpp] or similar extraction
    EXPECT_NE(tagsStr.find("#"), std::string::npos);
    // Should NOT contain the full path
    EXPECT_EQ(tagsStr.find("/some/deep/path/"), std::string::npos);
}

// Test addFilenameTag with a simple filename (no path)
TEST_F(TestCaseInfoTest_999, AddFilenameTagSimpleFilename_999) {
    auto info = makeTestCaseInfo("Class", "Test", "", "simple.cpp", 1);
    
    info->addFilenameTag();
    std::string tagsStr = info->tagsAsString();
    
    EXPECT_FALSE(tagsStr.empty());
    EXPECT_NE(tagsStr.find("#"), std::string::npos);
}

// Test addFilenameTag with Windows-style path
TEST_F(TestCaseInfoTest_999, AddFilenameTagWindowsPath_999) {
    auto info = makeTestCaseInfo("Class", "Test", "", "C:\\Users\\test\\file.cpp", 5);
    
    info->addFilenameTag();
    std::string tagsStr = info->tagsAsString();
    
    EXPECT_FALSE(tagsStr.empty());
    EXPECT_NE(tagsStr.find("#"), std::string::npos);
}

// Test that existing tags are preserved when addFilenameTag is called
TEST_F(TestCaseInfoTest_999, AddFilenameTagPreservesExistingTags_999) {
    auto info = makeTestCaseInfo("Class", "Test", "[existingTag]", "/path/file.cpp", 10);
    
    std::string tagsBefore = info->tagsAsString();
    EXPECT_NE(tagsBefore.find("existingTag"), std::string::npos);
    
    info->addFilenameTag();
    std::string tagsAfter = info->tagsAsString();
    
    // Existing tag should still be present
    EXPECT_NE(tagsAfter.find("existingTag"), std::string::npos);
    // New filename tag should also be present
    EXPECT_NE(tagsAfter.find("#"), std::string::npos);
}

// Test that calling addFilenameTag multiple times adds the tag each time
TEST_F(TestCaseInfoTest_999, AddFilenameTagCalledMultipleTimes_999) {
    auto info = makeTestCaseInfo("Class", "Test", "", "/path/myfile.cpp", 10);
    
    info->addFilenameTag();
    std::string tagsAfterFirst = info->tagsAsString();
    std::size_t tagCountFirst = info->tags.size();
    
    info->addFilenameTag();
    std::size_t tagCountSecond = info->tags.size();
    
    // Calling it again should add another tag entry
    EXPECT_GE(tagCountSecond, tagCountFirst);
}

// Test isHidden when no hidden tag is provided
TEST_F(TestCaseInfoTest_999, IsHiddenReturnsFalseForNormalTest_999) {
    auto info = makeTestCaseInfo("Class", "NormalTest", "[tag1]", "file.cpp", 1);
    
    EXPECT_FALSE(info->isHidden());
}

// Test isHidden when the hidden tag [.] is provided
TEST_F(TestCaseInfoTest_999, IsHiddenReturnsTrueForHiddenTest_999) {
    auto info = makeTestCaseInfo("Class", "HiddenTest", "[.]", "file.cpp", 1);
    
    EXPECT_TRUE(info->isHidden());
}

// Test isHidden with a tag starting with dot like [.integration]
TEST_F(TestCaseInfoTest_999, IsHiddenReturnsTrueForDotPrefixedTag_999) {
    auto info = makeTestCaseInfo("Class", "HiddenTest", "[.integration]", "file.cpp", 1);
    
    EXPECT_TRUE(info->isHidden());
}

// Test throws() returns false for normal test
TEST_F(TestCaseInfoTest_999, ThrowsReturnsFalseForNormalTest_999) {
    auto info = makeTestCaseInfo("Class", "Test", "[normal]", "file.cpp", 1);
    
    EXPECT_FALSE(info->throws());
}

// Test throws() returns true when !throws tag is present
TEST_F(TestCaseInfoTest_999, ThrowsReturnsTrueForThrowsTag_999) {
    auto info = makeTestCaseInfo("Class", "Test", "[!throws]", "file.cpp", 1);
    
    EXPECT_TRUE(info->throws());
}

// Test okToFail returns false for normal test
TEST_F(TestCaseInfoTest_999, OkToFailReturnsFalseForNormalTest_999) {
    auto info = makeTestCaseInfo("Class", "Test", "[normal]", "file.cpp", 1);
    
    EXPECT_FALSE(info->okToFail());
}

// Test okToFail returns true when !mayfail tag is present
TEST_F(TestCaseInfoTest_999, OkToFailReturnsTrueForMayFailTag_999) {
    auto info = makeTestCaseInfo("Class", "Test", "[!mayfail]", "file.cpp", 1);
    
    EXPECT_TRUE(info->okToFail());
}

// Test expectedToFail returns false for normal test
TEST_F(TestCaseInfoTest_999, ExpectedToFailReturnsFalseForNormalTest_999) {
    auto info = makeTestCaseInfo("Class", "Test", "[normal]", "file.cpp", 1);
    
    EXPECT_FALSE(info->expectedToFail());
}

// Test expectedToFail returns true when !shouldfail tag is present
TEST_F(TestCaseInfoTest_999, ExpectedToFailReturnsTrueForShouldFailTag_999) {
    auto info = makeTestCaseInfo("Class", "Test", "[!shouldfail]", "file.cpp", 1);
    
    EXPECT_TRUE(info->expectedToFail());
}

// Test tagsAsString returns empty for no tags
TEST_F(TestCaseInfoTest_999, TagsAsStringEmptyWhenNoTags_999) {
    auto info = makeTestCaseInfo("Class", "Test", "", "file.cpp", 1);
    
    std::string tagsStr = info->tagsAsString();
    // With no tags provided, the tags string should be empty
    EXPECT_TRUE(tagsStr.empty());
}

// Test tagsAsString returns proper format for single tag
TEST_F(TestCaseInfoTest_999, TagsAsStringReturnsSingleTag_999) {
    auto info = makeTestCaseInfo("Class", "Test", "[myTag]", "file.cpp", 1);
    
    std::string tagsStr = info->tagsAsString();
    EXPECT_NE(tagsStr.find("myTag"), std::string::npos);
}

// Test tagsAsString returns proper format for multiple tags
TEST_F(TestCaseInfoTest_999, TagsAsStringReturnsMultipleTags_999) {
    auto info = makeTestCaseInfo("Class", "Test", "[tag1][tag2][tag3]", "file.cpp", 1);
    
    std::string tagsStr = info->tagsAsString();
    EXPECT_NE(tagsStr.find("tag1"), std::string::npos);
    EXPECT_NE(tagsStr.find("tag2"), std::string::npos);
    EXPECT_NE(tagsStr.find("tag3"), std::string::npos);
}

// Test default name is generated when name is empty
TEST_F(TestCaseInfoTest_999, DefaultNameGeneratedWhenEmpty_999) {
    auto info = makeTestCaseInfo("Class", "", "", "file.cpp", 1);
    
    // The name should not be empty even if we pass empty string
    EXPECT_FALSE(info->name.empty());
}

// Test that the name is set correctly when provided
TEST_F(TestCaseInfoTest_999, NameSetCorrectlyWhenProvided_999) {
    auto info = makeTestCaseInfo("Class", "MyTestName", "", "file.cpp", 1);
    
    EXPECT_EQ(info->name, "MyTestName");
}

// Test that lineInfo is correctly stored
TEST_F(TestCaseInfoTest_999, LineInfoStoredCorrectly_999) {
    auto info = makeTestCaseInfo("Class", "Test", "", "myfile.cpp", 42);
    
    EXPECT_STREQ(info->lineInfo.file, "myfile.cpp");
    EXPECT_EQ(info->lineInfo.line, 42u);
}

// Test that className is stored correctly
TEST_F(TestCaseInfoTest_999, ClassNameStoredCorrectly_999) {
    auto info = makeTestCaseInfo("MyClassName", "Test", "", "file.cpp", 1);
    
    EXPECT_EQ(info->className, StringRef("MyClassName"));
}

// Test that tags vector is populated correctly
TEST_F(TestCaseInfoTest_999, TagsVectorPopulated_999) {
    auto info = makeTestCaseInfo("Class", "Test", "[alpha][beta]", "file.cpp", 1);
    
    EXPECT_GE(info->tags.size(), 2u);
}

// Test that tags vector is empty when no tags provided
TEST_F(TestCaseInfoTest_999, TagsVectorEmptyWhenNoTags_999) {
    auto info = makeTestCaseInfo("Class", "Test", "", "file.cpp", 1);
    
    EXPECT_EQ(info->tags.size(), 0u);
}

// Test addFilenameTag increases tags count
TEST_F(TestCaseInfoTest_999, AddFilenameTagIncreasesTagCount_999) {
    auto info = makeTestCaseInfo("Class", "Test", "", "/some/path/test.cpp", 1);
    
    std::size_t countBefore = info->tags.size();
    info->addFilenameTag();
    std::size_t countAfter = info->tags.size();
    
    EXPECT_GT(countAfter, countBefore);
}

// Test addFilenameTag with deeply nested path
TEST_F(TestCaseInfoTest_999, AddFilenameTagDeepPath_999) {
    auto info = makeTestCaseInfo("Class", "Test", "", "/a/b/c/d/e/f/g/deep.cpp", 1);
    
    info->addFilenameTag();
    std::string tagsStr = info->tagsAsString();
    
    EXPECT_NE(tagsStr.find("#"), std::string::npos);
    // Should not contain intermediate path components
    EXPECT_EQ(tagsStr.find("/a/b/"), std::string::npos);
}

// Test that okToFail also returns true for shouldfail (since shouldfail implies okToFail)
TEST_F(TestCaseInfoTest_999, OkToFailTrueForShouldFail_999) {
    auto info = makeTestCaseInfo("Class", "Test", "[!shouldfail]", "file.cpp", 1);
    
    // shouldfail implies it's ok to fail
    EXPECT_TRUE(info->okToFail());
}
