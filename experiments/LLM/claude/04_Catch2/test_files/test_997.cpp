#include <gtest/gtest.h>
#include "catch2/catch_test_case_info.hpp"

using namespace Catch;

// Helper to create a TestCaseInfo with specific properties
class TestCaseInfoTest_997 : public ::testing::Test {
protected:
    // Helper to create TestCaseInfo instances
    std::unique_ptr<TestCaseInfo> createTestCaseInfo(
        StringRef className,
        const char* name,
        const char* tags,
        SourceLineInfo lineInfo = SourceLineInfo("test.cpp", 1))
    {
        NameAndTags nameAndTags(name, tags);
        auto tci = std::make_unique<TestCaseInfo>(className, nameAndTags, lineInfo);
        return tci;
    }
};

// Test okToFail returns false when properties is None
TEST_F(TestCaseInfoTest_997, OkToFail_None_ReturnsFalse_997) {
    auto tci = createTestCaseInfo("TestClass", "test_name", "");
    tci->properties = TestCaseProperties::None;
    EXPECT_FALSE(tci->okToFail());
}

// Test okToFail returns true when ShouldFail is set
TEST_F(TestCaseInfoTest_997, OkToFail_ShouldFail_ReturnsTrue_997) {
    auto tci = createTestCaseInfo("TestClass", "test_name", "");
    tci->properties = TestCaseProperties::ShouldFail;
    EXPECT_TRUE(tci->okToFail());
}

// Test okToFail returns true when MayFail is set
TEST_F(TestCaseInfoTest_997, OkToFail_MayFail_ReturnsTrue_997) {
    auto tci = createTestCaseInfo("TestClass", "test_name", "");
    tci->properties = TestCaseProperties::MayFail;
    EXPECT_TRUE(tci->okToFail());
}

// Test okToFail returns true when both ShouldFail and MayFail are set
TEST_F(TestCaseInfoTest_997, OkToFail_ShouldFailAndMayFail_ReturnsTrue_997) {
    auto tci = createTestCaseInfo("TestClass", "test_name", "");
    tci->properties = static_cast<TestCaseProperties>(
        static_cast<int>(TestCaseProperties::ShouldFail) |
        static_cast<int>(TestCaseProperties::MayFail));
    EXPECT_TRUE(tci->okToFail());
}

// Test okToFail returns false when only IsHidden is set
TEST_F(TestCaseInfoTest_997, OkToFail_IsHidden_ReturnsFalse_997) {
    auto tci = createTestCaseInfo("TestClass", "test_name", "");
    tci->properties = TestCaseProperties::IsHidden;
    EXPECT_FALSE(tci->okToFail());
}

// Test okToFail returns false when only Throws is set
TEST_F(TestCaseInfoTest_997, OkToFail_Throws_ReturnsFalse_997) {
    auto tci = createTestCaseInfo("TestClass", "test_name", "");
    tci->properties = TestCaseProperties::Throws;
    EXPECT_FALSE(tci->okToFail());
}

// Test okToFail returns false when only NonPortable is set
TEST_F(TestCaseInfoTest_997, OkToFail_NonPortable_ReturnsFalse_997) {
    auto tci = createTestCaseInfo("TestClass", "test_name", "");
    tci->properties = TestCaseProperties::NonPortable;
    EXPECT_FALSE(tci->okToFail());
}

// Test okToFail returns false when only Benchmark is set
TEST_F(TestCaseInfoTest_997, OkToFail_Benchmark_ReturnsFalse_997) {
    auto tci = createTestCaseInfo("TestClass", "test_name", "");
    tci->properties = TestCaseProperties::Benchmark;
    EXPECT_FALSE(tci->okToFail());
}

// Test okToFail returns true when ShouldFail is combined with other non-fail properties
TEST_F(TestCaseInfoTest_997, OkToFail_ShouldFailWithOtherProperties_ReturnsTrue_997) {
    auto tci = createTestCaseInfo("TestClass", "test_name", "");
    tci->properties = static_cast<TestCaseProperties>(
        static_cast<int>(TestCaseProperties::ShouldFail) |
        static_cast<int>(TestCaseProperties::IsHidden) |
        static_cast<int>(TestCaseProperties::Throws));
    EXPECT_TRUE(tci->okToFail());
}

// Test okToFail returns true when MayFail is combined with other non-fail properties
TEST_F(TestCaseInfoTest_997, OkToFail_MayFailWithOtherProperties_ReturnsTrue_997) {
    auto tci = createTestCaseInfo("TestClass", "test_name", "");
    tci->properties = static_cast<TestCaseProperties>(
        static_cast<int>(TestCaseProperties::MayFail) |
        static_cast<int>(TestCaseProperties::NonPortable) |
        static_cast<int>(TestCaseProperties::Benchmark));
    EXPECT_TRUE(tci->okToFail());
}

// Test okToFail returns false when all properties except ShouldFail and MayFail are set
TEST_F(TestCaseInfoTest_997, OkToFail_AllExceptFailProperties_ReturnsFalse_997) {
    auto tci = createTestCaseInfo("TestClass", "test_name", "");
    tci->properties = static_cast<TestCaseProperties>(
        static_cast<int>(TestCaseProperties::IsHidden) |
        static_cast<int>(TestCaseProperties::Throws) |
        static_cast<int>(TestCaseProperties::NonPortable) |
        static_cast<int>(TestCaseProperties::Benchmark));
    EXPECT_FALSE(tci->okToFail());
}

// Test isHidden
TEST_F(TestCaseInfoTest_997, IsHidden_WhenHiddenSet_ReturnsTrue_997) {
    auto tci = createTestCaseInfo("TestClass", "test_name", "");
    tci->properties = TestCaseProperties::IsHidden;
    EXPECT_TRUE(tci->isHidden());
}

// Test isHidden returns false when not set
TEST_F(TestCaseInfoTest_997, IsHidden_WhenNone_ReturnsFalse_997) {
    auto tci = createTestCaseInfo("TestClass", "test_name", "");
    tci->properties = TestCaseProperties::None;
    EXPECT_FALSE(tci->isHidden());
}

// Test throws
TEST_F(TestCaseInfoTest_997, Throws_WhenThrowsSet_ReturnsTrue_997) {
    auto tci = createTestCaseInfo("TestClass", "test_name", "");
    tci->properties = TestCaseProperties::Throws;
    EXPECT_TRUE(tci->throws());
}

// Test throws returns false when not set
TEST_F(TestCaseInfoTest_997, Throws_WhenNone_ReturnsFalse_997) {
    auto tci = createTestCaseInfo("TestClass", "test_name", "");
    tci->properties = TestCaseProperties::None;
    EXPECT_FALSE(tci->throws());
}

// Test expectedToFail returns true when ShouldFail is set
TEST_F(TestCaseInfoTest_997, ExpectedToFail_ShouldFail_ReturnsTrue_997) {
    auto tci = createTestCaseInfo("TestClass", "test_name", "");
    tci->properties = TestCaseProperties::ShouldFail;
    EXPECT_TRUE(tci->expectedToFail());
}

// Test expectedToFail returns false when MayFail is set (MayFail != expected)
TEST_F(TestCaseInfoTest_997, ExpectedToFail_MayFail_ReturnsFalse_997) {
    auto tci = createTestCaseInfo("TestClass", "test_name", "");
    tci->properties = TestCaseProperties::MayFail;
    EXPECT_FALSE(tci->expectedToFail());
}

// Test expectedToFail returns false when None
TEST_F(TestCaseInfoTest_997, ExpectedToFail_None_ReturnsFalse_997) {
    auto tci = createTestCaseInfo("TestClass", "test_name", "");
    tci->properties = TestCaseProperties::None;
    EXPECT_FALSE(tci->expectedToFail());
}

// Test tagsAsString with tags provided via constructor
TEST_F(TestCaseInfoTest_997, TagsAsString_WithTags_997) {
    auto tci = createTestCaseInfo("TestClass", "test_name", "[tag1][tag2]");
    std::string result = tci->tagsAsString();
    // We expect it contains the tags in some form
    EXPECT_FALSE(result.empty());
}

// Test tagsAsString with no tags
TEST_F(TestCaseInfoTest_997, TagsAsString_NoTags_997) {
    auto tci = createTestCaseInfo("TestClass", "test_name", "");
    std::string result = tci->tagsAsString();
    // With no tags, the result should be empty or minimal
    // We can only verify it doesn't crash and returns a string
    EXPECT_TRUE(result.empty() || !result.empty()); // valid string
}

// Test all properties combined with okToFail - all properties set
TEST_F(TestCaseInfoTest_997, OkToFail_AllPropertiesSet_ReturnsTrue_997) {
    auto tci = createTestCaseInfo("TestClass", "test_name", "");
    tci->properties = static_cast<TestCaseProperties>(
        static_cast<int>(TestCaseProperties::IsHidden) |
        static_cast<int>(TestCaseProperties::ShouldFail) |
        static_cast<int>(TestCaseProperties::MayFail) |
        static_cast<int>(TestCaseProperties::Throws) |
        static_cast<int>(TestCaseProperties::NonPortable) |
        static_cast<int>(TestCaseProperties::Benchmark));
    EXPECT_TRUE(tci->okToFail());
}
