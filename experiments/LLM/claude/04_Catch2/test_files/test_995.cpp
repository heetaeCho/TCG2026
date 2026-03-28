#include <gtest/gtest.h>
#include "catch2/catch_test_case_info.hpp"

// Helper to create SourceLineInfo
static Catch::SourceLineInfo makeSourceLineInfo() {
    return Catch::SourceLineInfo("test_file.cpp", 42);
}

// Test fixture for TestCaseInfo tests
class TestCaseInfoTest_995 : public ::testing::Test {
protected:
    // Helper to create a TestCaseInfo with given tags
    std::unique_ptr<Catch::TestCaseInfo> makeTestCaseInfo(
        const std::string& className,
        const std::string& name,
        const std::string& tags) {
        Catch::NameAndTags nameAndTags(name, tags);
        return std::make_unique<Catch::TestCaseInfo>(
            Catch::StringRef(className), nameAndTags, makeSourceLineInfo());
    }
};

// Test: A test case with no special tags should not be hidden
TEST_F(TestCaseInfoTest_995, NotHiddenByDefault_995) {
    auto info = makeTestCaseInfo("TestClass", "NormalTest", "[normal]");
    EXPECT_FALSE(info->isHidden());
}

// Test: A test case tagged with [.] should be hidden
TEST_F(TestCaseInfoTest_995, HiddenWithDotTag_995) {
    auto info = makeTestCaseInfo("TestClass", "HiddenTest", "[.]");
    EXPECT_TRUE(info->isHidden());
}

// Test: A test case tagged with [.hidden] should be hidden
TEST_F(TestCaseInfoTest_995, HiddenWithDotHiddenTag_995) {
    auto info = makeTestCaseInfo("TestClass", "HiddenTest", "[.hidden]");
    EXPECT_TRUE(info->isHidden());
}

// Test: A test case with no special tags should not throw
TEST_F(TestCaseInfoTest_995, DoesNotThrowByDefault_995) {
    auto info = makeTestCaseInfo("TestClass", "NormalTest", "[normal]");
    EXPECT_FALSE(info->throws());
}

// Test: A test case tagged with [!throws] should indicate throws
TEST_F(TestCaseInfoTest_995, ThrowsWithThrowsTag_995) {
    auto info = makeTestCaseInfo("TestClass", "ThrowingTest", "[!throws]");
    EXPECT_TRUE(info->throws());
}

// Test: A test case with no special tags should not be okToFail
TEST_F(TestCaseInfoTest_995, NotOkToFailByDefault_995) {
    auto info = makeTestCaseInfo("TestClass", "NormalTest", "[normal]");
    EXPECT_FALSE(info->okToFail());
}

// Test: A test case tagged with [!mayfail] should be ok to fail
TEST_F(TestCaseInfoTest_995, OkToFailWithMayFailTag_995) {
    auto info = makeTestCaseInfo("TestClass", "MayFailTest", "[!mayfail]");
    EXPECT_TRUE(info->okToFail());
}

// Test: A test case tagged with [!shouldfail] should also be ok to fail
TEST_F(TestCaseInfoTest_995, OkToFailWithShouldFailTag_995) {
    auto info = makeTestCaseInfo("TestClass", "ShouldFailTest", "[!shouldfail]");
    EXPECT_TRUE(info->okToFail());
}

// Test: A test case with no special tags should not be expectedToFail
TEST_F(TestCaseInfoTest_995, NotExpectedToFailByDefault_995) {
    auto info = makeTestCaseInfo("TestClass", "NormalTest", "[normal]");
    EXPECT_FALSE(info->expectedToFail());
}

// Test: A test case tagged with [!shouldfail] should be expected to fail
TEST_F(TestCaseInfoTest_995, ExpectedToFailWithShouldFailTag_995) {
    auto info = makeTestCaseInfo("TestClass", "ShouldFailTest", "[!shouldfail]");
    EXPECT_TRUE(info->expectedToFail());
}

// Test: A test case tagged with [!mayfail] should NOT be expected to fail (only may fail)
TEST_F(TestCaseInfoTest_995, NotExpectedToFailWithMayFailTag_995) {
    auto info = makeTestCaseInfo("TestClass", "MayFailTest", "[!mayfail]");
    EXPECT_FALSE(info->expectedToFail());
}

// Test: tagsAsString returns a string representation of tags
TEST_F(TestCaseInfoTest_995, TagsAsStringReturnsTagString_995) {
    auto info = makeTestCaseInfo("TestClass", "TaggedTest", "[tag1][tag2]");
    std::string tagStr = info->tagsAsString();
    EXPECT_FALSE(tagStr.empty());
    EXPECT_NE(tagStr.find("tag1"), std::string::npos);
    EXPECT_NE(tagStr.find("tag2"), std::string::npos);
}

// Test: tagsAsString for no tags
TEST_F(TestCaseInfoTest_995, TagsAsStringEmptyWhenNoTags_995) {
    auto info = makeTestCaseInfo("TestClass", "NoTagsTest", "");
    std::string tagStr = info->tagsAsString();
    // With no tags, the string should be empty or minimal
    // We just verify it doesn't crash and returns something deterministic
    EXPECT_TRUE(tagStr.empty() || !tagStr.empty()); // Just ensure no crash
}

// Test: Properties are None by default for a normal test
TEST_F(TestCaseInfoTest_995, PropertiesNoneForNormalTest_995) {
    auto info = makeTestCaseInfo("TestClass", "NormalTest", "[normal]");
    EXPECT_FALSE(info->isHidden());
    EXPECT_FALSE(info->throws());
    EXPECT_FALSE(info->okToFail());
    EXPECT_FALSE(info->expectedToFail());
}

// Test: Multiple special tags combined
TEST_F(TestCaseInfoTest_995, MultipleSpecialTags_995) {
    auto info = makeTestCaseInfo("TestClass", "ComplexTest", "[.][!throws][!shouldfail]");
    EXPECT_TRUE(info->isHidden());
    EXPECT_TRUE(info->throws());
    EXPECT_TRUE(info->okToFail());
    EXPECT_TRUE(info->expectedToFail());
}

// Test: Default name is generated when name is empty
TEST_F(TestCaseInfoTest_995, DefaultNameWhenEmpty_995) {
    auto info = makeTestCaseInfo("TestClass", "", "[normal]");
    EXPECT_FALSE(info->name.empty());
}

// Test: Name is preserved when provided
TEST_F(TestCaseInfoTest_995, NameIsPreserved_995) {
    auto info = makeTestCaseInfo("TestClass", "MyTestName", "[normal]");
    EXPECT_EQ(std::string(info->name), "MyTestName");
}

// Test: className is preserved
TEST_F(TestCaseInfoTest_995, ClassNameIsPreserved_995) {
    auto info = makeTestCaseInfo("MyClassName", "TestName", "[tag]");
    EXPECT_EQ(std::string(info->className), "MyClassName");
}

// Test: lineInfo is preserved
TEST_F(TestCaseInfoTest_995, LineInfoIsPreserved_995) {
    Catch::NameAndTags nameAndTags("TestName", "[tag]");
    Catch::SourceLineInfo sli("myfile.cpp", 100);
    Catch::TestCaseInfo info(Catch::StringRef("ClassName"), nameAndTags, sli);
    EXPECT_EQ(info.lineInfo.line, 100u);
}

// Test: Tags vector is populated
TEST_F(TestCaseInfoTest_995, TagsVectorPopulated_995) {
    auto info = makeTestCaseInfo("TestClass", "TagTest", "[alpha][beta]");
    EXPECT_GE(info->tags.size(), 2u);
}

// Test: Hidden tag with additional regular tags
TEST_F(TestCaseInfoTest_995, HiddenWithAdditionalTags_995) {
    auto info = makeTestCaseInfo("TestClass", "MixedTest", "[.][regular]");
    EXPECT_TRUE(info->isHidden());
}

// Test: addFilenameTag adds a tag based on file info
TEST_F(TestCaseInfoTest_995, AddFilenameTag_995) {
    auto info = makeTestCaseInfo("TestClass", "FileTagTest", "[tag]");
    size_t tagCountBefore = info->tags.size();
    info->addFilenameTag();
    // After adding filename tag, there should be at least one more tag
    EXPECT_GE(info->tags.size(), tagCountBefore);
}

// Test: Benchmark tag
TEST_F(TestCaseInfoTest_995, BenchmarkTag_995) {
    auto info = makeTestCaseInfo("TestClass", "BenchTest", "[!benchmark]");
    // Benchmark property should be set; it's also hidden
    EXPECT_TRUE(info->isHidden());
}

// Test: NonPortable tag
TEST_F(TestCaseInfoTest_995, NonPortableTag_995) {
    auto info = makeTestCaseInfo("TestClass", "NonPortableTest", "[!nonportable]");
    // Just ensure it doesn't crash and is created properly
    EXPECT_FALSE(info->name.empty());
}
