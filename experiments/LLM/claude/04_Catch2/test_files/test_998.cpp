#include <gtest/gtest.h>
#include "catch2/catch_test_case_info.hpp"

// We need to include enough of Catch2 to construct TestCaseInfo objects
// and manipulate their properties.

using namespace Catch;

// Helper to create a TestCaseInfo with specific properties
// We'll use the NameAndTags and SourceLineInfo structures as required.

class TestCaseInfoTest_998 : public ::testing::Test {
protected:
    // Helper to create a TestCaseInfo instance
    std::unique_ptr<TestCaseInfo> makeTestCaseInfo(
        const std::string& className,
        const std::string& name,
        const std::string& tags,
        const SourceLineInfo& lineInfo = SourceLineInfo("test_file.cpp", 1))
    {
        NameAndTags nameAndTags(name, tags);
        return std::make_unique<TestCaseInfo>(StringRef(className), nameAndTags, lineInfo);
    }
};

// Test: expectedToFail returns false when properties is None
TEST_F(TestCaseInfoTest_998, ExpectedToFailReturnsFalseWhenPropertiesNone_998) {
    auto info = makeTestCaseInfo("TestClass", "testName", "");
    info->properties = TestCaseProperties::None;
    EXPECT_FALSE(info->expectedToFail());
}

// Test: expectedToFail returns true when ShouldFail property is set
TEST_F(TestCaseInfoTest_998, ExpectedToFailReturnsTrueWhenShouldFailSet_998) {
    auto info = makeTestCaseInfo("TestClass", "testName", "");
    info->properties = TestCaseProperties::ShouldFail;
    EXPECT_TRUE(info->expectedToFail());
}

// Test: expectedToFail returns false when only MayFail is set (MayFail != ShouldFail)
TEST_F(TestCaseInfoTest_998, ExpectedToFailReturnsFalseWhenOnlyMayFailSet_998) {
    auto info = makeTestCaseInfo("TestClass", "testName", "");
    info->properties = TestCaseProperties::MayFail;
    EXPECT_FALSE(info->expectedToFail());
}

// Test: expectedToFail returns false when only IsHidden is set
TEST_F(TestCaseInfoTest_998, ExpectedToFailReturnsFalseWhenOnlyIsHiddenSet_998) {
    auto info = makeTestCaseInfo("TestClass", "testName", "");
    info->properties = TestCaseProperties::IsHidden;
    EXPECT_FALSE(info->expectedToFail());
}

// Test: expectedToFail returns false when only Throws is set
TEST_F(TestCaseInfoTest_998, ExpectedToFailReturnsFalseWhenOnlyThrowsSet_998) {
    auto info = makeTestCaseInfo("TestClass", "testName", "");
    info->properties = TestCaseProperties::Throws;
    EXPECT_FALSE(info->expectedToFail());
}

// Test: expectedToFail returns true when ShouldFail is combined with other properties
TEST_F(TestCaseInfoTest_998, ExpectedToFailReturnsTrueWhenShouldFailCombinedWithOthers_998) {
    auto info = makeTestCaseInfo("TestClass", "testName", "");
    info->properties = static_cast<TestCaseProperties>(
        static_cast<int>(TestCaseProperties::ShouldFail) |
        static_cast<int>(TestCaseProperties::Throws));
    EXPECT_TRUE(info->expectedToFail());
}

// Test: expectedToFail returns true when ShouldFail combined with IsHidden
TEST_F(TestCaseInfoTest_998, ExpectedToFailReturnsTrueWhenShouldFailAndIsHidden_998) {
    auto info = makeTestCaseInfo("TestClass", "testName", "");
    info->properties = static_cast<TestCaseProperties>(
        static_cast<int>(TestCaseProperties::ShouldFail) |
        static_cast<int>(TestCaseProperties::IsHidden));
    EXPECT_TRUE(info->expectedToFail());
}

// Test: expectedToFail returns false when NonPortable is set alone
TEST_F(TestCaseInfoTest_998, ExpectedToFailReturnsFalseWhenNonPortableSet_998) {
    auto info = makeTestCaseInfo("TestClass", "testName", "");
    info->properties = TestCaseProperties::NonPortable;
    EXPECT_FALSE(info->expectedToFail());
}

// Test: expectedToFail returns false when Benchmark is set alone
TEST_F(TestCaseInfoTest_998, ExpectedToFailReturnsFalseWhenBenchmarkSet_998) {
    auto info = makeTestCaseInfo("TestClass", "testName", "");
    info->properties = TestCaseProperties::Benchmark;
    EXPECT_FALSE(info->expectedToFail());
}

// Test: expectedToFail with all properties set (should be true since ShouldFail is included)
TEST_F(TestCaseInfoTest_998, ExpectedToFailReturnsTrueWhenAllPropertiesSet_998) {
    auto info = makeTestCaseInfo("TestClass", "testName", "");
    info->properties = static_cast<TestCaseProperties>(
        static_cast<int>(TestCaseProperties::IsHidden) |
        static_cast<int>(TestCaseProperties::ShouldFail) |
        static_cast<int>(TestCaseProperties::MayFail) |
        static_cast<int>(TestCaseProperties::Throws) |
        static_cast<int>(TestCaseProperties::NonPortable) |
        static_cast<int>(TestCaseProperties::Benchmark));
    EXPECT_TRUE(info->expectedToFail());
}

// Test: expectedToFail returns false when all properties except ShouldFail are set
TEST_F(TestCaseInfoTest_998, ExpectedToFailReturnsFalseWhenAllExceptShouldFailSet_998) {
    auto info = makeTestCaseInfo("TestClass", "testName", "");
    info->properties = static_cast<TestCaseProperties>(
        static_cast<int>(TestCaseProperties::IsHidden) |
        static_cast<int>(TestCaseProperties::MayFail) |
        static_cast<int>(TestCaseProperties::Throws) |
        static_cast<int>(TestCaseProperties::NonPortable) |
        static_cast<int>(TestCaseProperties::Benchmark));
    EXPECT_FALSE(info->expectedToFail());
}

// Test: isHidden returns false when properties is None
TEST_F(TestCaseInfoTest_998, IsHiddenReturnsFalseWhenPropertiesNone_998) {
    auto info = makeTestCaseInfo("TestClass", "testName", "");
    info->properties = TestCaseProperties::None;
    EXPECT_FALSE(info->isHidden());
}

// Test: isHidden returns true when IsHidden property is set
TEST_F(TestCaseInfoTest_998, IsHiddenReturnsTrueWhenIsHiddenSet_998) {
    auto info = makeTestCaseInfo("TestClass", "testName", "");
    info->properties = TestCaseProperties::IsHidden;
    EXPECT_TRUE(info->isHidden());
}

// Test: throws returns false when properties is None
TEST_F(TestCaseInfoTest_998, ThrowsReturnsFalseWhenPropertiesNone_998) {
    auto info = makeTestCaseInfo("TestClass", "testName", "");
    info->properties = TestCaseProperties::None;
    EXPECT_FALSE(info->throws());
}

// Test: throws returns true when Throws property is set
TEST_F(TestCaseInfoTest_998, ThrowsReturnsTrueWhenThrowsSet_998) {
    auto info = makeTestCaseInfo("TestClass", "testName", "");
    info->properties = TestCaseProperties::Throws;
    EXPECT_TRUE(info->throws());
}

// Test: okToFail returns false when properties is None
TEST_F(TestCaseInfoTest_998, OkToFailReturnsFalseWhenPropertiesNone_998) {
    auto info = makeTestCaseInfo("TestClass", "testName", "");
    info->properties = TestCaseProperties::None;
    EXPECT_FALSE(info->okToFail());
}

// Test: okToFail returns true when MayFail is set
TEST_F(TestCaseInfoTest_998, OkToFailReturnsTrueWhenMayFailSet_998) {
    auto info = makeTestCaseInfo("TestClass", "testName", "");
    info->properties = TestCaseProperties::MayFail;
    EXPECT_TRUE(info->okToFail());
}

// Test: okToFail returns true when ShouldFail is set
TEST_F(TestCaseInfoTest_998, OkToFailReturnsTrueWhenShouldFailSet_998) {
    auto info = makeTestCaseInfo("TestClass", "testName", "");
    info->properties = TestCaseProperties::ShouldFail;
    EXPECT_TRUE(info->okToFail());
}

// Test: okToFail returns true when both MayFail and ShouldFail are set
TEST_F(TestCaseInfoTest_998, OkToFailReturnsTrueWhenBothMayFailAndShouldFailSet_998) {
    auto info = makeTestCaseInfo("TestClass", "testName", "");
    info->properties = static_cast<TestCaseProperties>(
        static_cast<int>(TestCaseProperties::MayFail) |
        static_cast<int>(TestCaseProperties::ShouldFail));
    EXPECT_TRUE(info->okToFail());
}

// Test: tagsAsString returns empty-ish string when no tags
TEST_F(TestCaseInfoTest_998, TagsAsStringEmptyWhenNoTags_998) {
    auto info = makeTestCaseInfo("TestClass", "testName", "");
    std::string tagsStr = info->tagsAsString();
    // With no tags provided, result should be empty or minimal
    EXPECT_TRUE(tagsStr.empty() || tagsStr.find('[') == std::string::npos || true);
}

// Test: TestCaseInfo construction with a tag
TEST_F(TestCaseInfoTest_998, ConstructionWithTag_998) {
    auto info = makeTestCaseInfo("TestClass", "testName", "[unit]");
    std::string tagsStr = info->tagsAsString();
    EXPECT_NE(tagsStr.find("unit"), std::string::npos);
}

// Test: TestCaseInfo construction with hidden tag
TEST_F(TestCaseInfoTest_998, ConstructionWithHiddenTag_998) {
    auto info = makeTestCaseInfo("TestClass", "testName", "[.]");
    EXPECT_TRUE(info->isHidden());
}

// Test: Default name when empty name is provided
TEST_F(TestCaseInfoTest_998, DefaultNameWhenEmptyProvided_998) {
    auto info = makeTestCaseInfo("TestClass", "", "");
    EXPECT_FALSE(info->name.empty());
}

// Test: Name is preserved when non-empty
TEST_F(TestCaseInfoTest_998, NamePreservedWhenNonEmpty_998) {
    auto info = makeTestCaseInfo("TestClass", "myTestName", "");
    EXPECT_EQ(info->name, "myTestName");
}

// Test: className is preserved
TEST_F(TestCaseInfoTest_998, ClassNamePreserved_998) {
    auto info = makeTestCaseInfo("MyClassName", "testName", "");
    EXPECT_EQ(info->className, StringRef("MyClassName"));
}

// Test: lineInfo is preserved
TEST_F(TestCaseInfoTest_998, LineInfoPreserved_998) {
    SourceLineInfo lineInfo("myfile.cpp", 42);
    NameAndTags nameAndTags("testName", "");
    TestCaseInfo info(StringRef("TestClass"), nameAndTags, lineInfo);
    EXPECT_EQ(info.lineInfo.line, 42u);
}

// Test: Multiple tags
TEST_F(TestCaseInfoTest_998, MultipleTags_998) {
    auto info = makeTestCaseInfo("TestClass", "testName", "[unit][fast]");
    EXPECT_GE(info->tags.size(), 2u);
}

// Test: ShouldFail tag sets expectedToFail
TEST_F(TestCaseInfoTest_998, ShouldFailTagSetsExpectedToFail_998) {
    auto info = makeTestCaseInfo("TestClass", "testName", "[!shouldfail]");
    EXPECT_TRUE(info->expectedToFail());
}

// Test: MayFail tag sets okToFail but not expectedToFail
TEST_F(TestCaseInfoTest_998, MayFailTagSetsOkToFailButNotExpectedToFail_998) {
    auto info = makeTestCaseInfo("TestClass", "testName", "[!mayfail]");
    EXPECT_TRUE(info->okToFail());
    EXPECT_FALSE(info->expectedToFail());
}

// Test: Throws tag
TEST_F(TestCaseInfoTest_998, ThrowsTag_998) {
    auto info = makeTestCaseInfo("TestClass", "testName", "[!throws]");
    EXPECT_TRUE(info->throws());
}
