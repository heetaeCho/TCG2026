#include <gtest/gtest.h>
#include <string>
#include <memory>

// Include the necessary Catch2 headers
#include "catch2/internal/catch_stringref.hpp"
#include "catch2/internal/catch_source_line_info.hpp"
#include "catch2/internal/catch_test_registry.hpp"
#include "catch2/internal/catch_test_case_info.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"

// The function under test
namespace Catch {
    Detail::unique_ptr<TestCaseInfo> makeTestCaseInfo(
        StringRef _className,
        NameAndTags const& nameAndTags,
        SourceLineInfo const& _lineInfo);
}

class MakeTestCaseInfoTest_994 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that makeTestCaseInfo returns a non-null pointer with basic inputs
TEST_F(MakeTestCaseInfoTest_994, ReturnsNonNullPointer_994) {
    Catch::SourceLineInfo lineInfo("test_file.cpp", 42);
    Catch::NameAndTags nameAndTags("TestName", "[tag1]");

    auto result = Catch::makeTestCaseInfo("TestClass", nameAndTags, lineInfo);

    ASSERT_NE(result.get(), nullptr);
}

// Test that the returned TestCaseInfo has the correct name
TEST_F(MakeTestCaseInfoTest_994, CorrectName_994) {
    Catch::SourceLineInfo lineInfo("test_file.cpp", 42);
    Catch::NameAndTags nameAndTags("MyTestName", "[tag1]");

    auto result = Catch::makeTestCaseInfo("MyClass", nameAndTags, lineInfo);

    ASSERT_NE(result.get(), nullptr);
    EXPECT_EQ(result->name, std::string("MyTestName"));
}

// Test that the returned TestCaseInfo has the correct class name
TEST_F(MakeTestCaseInfoTest_994, CorrectClassName_994) {
    Catch::SourceLineInfo lineInfo("test_file.cpp", 42);
    Catch::NameAndTags nameAndTags("TestName", "[tag1]");

    auto result = Catch::makeTestCaseInfo("MyClassName", nameAndTags, lineInfo);

    ASSERT_NE(result.get(), nullptr);
    EXPECT_EQ(result->className, std::string("MyClassName"));
}

// Test that the returned TestCaseInfo has the correct line info
TEST_F(MakeTestCaseInfoTest_994, CorrectLineInfo_994) {
    Catch::SourceLineInfo lineInfo("my_test_file.cpp", 100);
    Catch::NameAndTags nameAndTags("TestName", "[tag1]");

    auto result = Catch::makeTestCaseInfo("TestClass", nameAndTags, lineInfo);

    ASSERT_NE(result.get(), nullptr);
    EXPECT_EQ(result->lineInfo.line, 100u);
    EXPECT_STREQ(result->lineInfo.file, "my_test_file.cpp");
}

// Test with empty class name
TEST_F(MakeTestCaseInfoTest_994, EmptyClassName_994) {
    Catch::SourceLineInfo lineInfo("test_file.cpp", 1);
    Catch::NameAndTags nameAndTags("TestName", "[tag1]");

    auto result = Catch::makeTestCaseInfo("", nameAndTags, lineInfo);

    ASSERT_NE(result.get(), nullptr);
    EXPECT_EQ(result->className, std::string(""));
}

// Test with empty test name
TEST_F(MakeTestCaseInfoTest_994, EmptyTestName_994) {
    Catch::SourceLineInfo lineInfo("test_file.cpp", 1);
    Catch::NameAndTags nameAndTags("", "[tag1]");

    auto result = Catch::makeTestCaseInfo("TestClass", nameAndTags, lineInfo);

    ASSERT_NE(result.get(), nullptr);
    EXPECT_EQ(result->name, std::string(""));
}

// Test with empty tags
TEST_F(MakeTestCaseInfoTest_994, EmptyTags_994) {
    Catch::SourceLineInfo lineInfo("test_file.cpp", 1);
    Catch::NameAndTags nameAndTags("TestName", "");

    auto result = Catch::makeTestCaseInfo("TestClass", nameAndTags, lineInfo);

    ASSERT_NE(result.get(), nullptr);
    // Tags should be empty when none are provided
    EXPECT_TRUE(result->tags.empty());
}

// Test with multiple tags
TEST_F(MakeTestCaseInfoTest_994, MultipleTags_994) {
    Catch::SourceLineInfo lineInfo("test_file.cpp", 1);
    Catch::NameAndTags nameAndTags("TestName", "[tag1][tag2][tag3]");

    auto result = Catch::makeTestCaseInfo("TestClass", nameAndTags, lineInfo);

    ASSERT_NE(result.get(), nullptr);
    // Should have parsed multiple tags
    EXPECT_FALSE(result->tags.empty());
}

// Test with all empty strings
TEST_F(MakeTestCaseInfoTest_994, AllEmptyStrings_994) {
    Catch::SourceLineInfo lineInfo("", 0);
    Catch::NameAndTags nameAndTags("", "");

    auto result = Catch::makeTestCaseInfo("", nameAndTags, lineInfo);

    ASSERT_NE(result.get(), nullptr);
}

// Test with default NameAndTags
TEST_F(MakeTestCaseInfoTest_994, DefaultNameAndTags_994) {
    Catch::SourceLineInfo lineInfo("test_file.cpp", 42);
    Catch::NameAndTags nameAndTags;

    auto result = Catch::makeTestCaseInfo("TestClass", nameAndTags, lineInfo);

    ASSERT_NE(result.get(), nullptr);
}

// Test line number boundary - line 0
TEST_F(MakeTestCaseInfoTest_994, LineNumberZero_994) {
    Catch::SourceLineInfo lineInfo("test_file.cpp", 0);
    Catch::NameAndTags nameAndTags("TestName", "[tag]");

    auto result = Catch::makeTestCaseInfo("TestClass", nameAndTags, lineInfo);

    ASSERT_NE(result.get(), nullptr);
    EXPECT_EQ(result->lineInfo.line, 0u);
}

// Test with very large line number
TEST_F(MakeTestCaseInfoTest_994, LargeLineNumber_994) {
    Catch::SourceLineInfo lineInfo("test_file.cpp", 999999);
    Catch::NameAndTags nameAndTags("TestName", "[tag]");

    auto result = Catch::makeTestCaseInfo("TestClass", nameAndTags, lineInfo);

    ASSERT_NE(result.get(), nullptr);
    EXPECT_EQ(result->lineInfo.line, 999999u);
}

// Test with special characters in name
TEST_F(MakeTestCaseInfoTest_994, SpecialCharactersInName_994) {
    Catch::SourceLineInfo lineInfo("test_file.cpp", 10);
    Catch::NameAndTags nameAndTags("Test with spaces & special chars!@#$", "[tag]");

    auto result = Catch::makeTestCaseInfo("TestClass", nameAndTags, lineInfo);

    ASSERT_NE(result.get(), nullptr);
    EXPECT_EQ(result->name, std::string("Test with spaces & special chars!@#$"));
}

// Test with hidden tag
TEST_F(MakeTestCaseInfoTest_994, HiddenTag_994) {
    Catch::SourceLineInfo lineInfo("test_file.cpp", 10);
    Catch::NameAndTags nameAndTags("TestName", "[.hidden]");

    auto result = Catch::makeTestCaseInfo("TestClass", nameAndTags, lineInfo);

    ASSERT_NE(result.get(), nullptr);
    // The test should be marked as hidden when using the [.] tag notation
    EXPECT_FALSE(result->tags.empty());
}

// Test that two calls with same arguments produce equivalent TestCaseInfo objects
TEST_F(MakeTestCaseInfoTest_994, ConsistentResults_994) {
    Catch::SourceLineInfo lineInfo("test_file.cpp", 42);
    Catch::NameAndTags nameAndTags("TestName", "[tag1]");

    auto result1 = Catch::makeTestCaseInfo("TestClass", nameAndTags, lineInfo);
    auto result2 = Catch::makeTestCaseInfo("TestClass", nameAndTags, lineInfo);

    ASSERT_NE(result1.get(), nullptr);
    ASSERT_NE(result2.get(), nullptr);
    EXPECT_EQ(result1->name, result2->name);
    EXPECT_EQ(result1->className, result2->className);
    EXPECT_EQ(result1->lineInfo.line, result2->lineInfo.line);
    EXPECT_STREQ(result1->lineInfo.file, result2->lineInfo.file);
    EXPECT_EQ(result1->tags.size(), result2->tags.size());
}

// Test with std::string inputs (implicit StringRef conversion)
TEST_F(MakeTestCaseInfoTest_994, StdStringInputs_994) {
    std::string className = "StdStringClass";
    std::string testName = "StdStringTest";
    std::string tags = "[stdtag]";

    Catch::SourceLineInfo lineInfo("test_file.cpp", 42);
    Catch::NameAndTags nameAndTags(testName, tags);

    auto result = Catch::makeTestCaseInfo(className, nameAndTags, lineInfo);

    ASSERT_NE(result.get(), nullptr);
    EXPECT_EQ(result->name, std::string("StdStringTest"));
    EXPECT_EQ(result->className, std::string("StdStringClass"));
}

// Test with long name and tags
TEST_F(MakeTestCaseInfoTest_994, LongNameAndTags_994) {
    std::string longName(1000, 'A');
    std::string longTag = "[" + std::string(500, 'b') + "]";

    Catch::SourceLineInfo lineInfo("test_file.cpp", 42);
    Catch::NameAndTags nameAndTags(longName, longTag);

    auto result = Catch::makeTestCaseInfo("TestClass", nameAndTags, lineInfo);

    ASSERT_NE(result.get(), nullptr);
    EXPECT_EQ(result->name, longName);
}

// Test unique pointer ownership - result can be moved
TEST_F(MakeTestCaseInfoTest_994, OwnershipTransfer_994) {
    Catch::SourceLineInfo lineInfo("test_file.cpp", 42);
    Catch::NameAndTags nameAndTags("TestName", "[tag]");

    auto result = Catch::makeTestCaseInfo("TestClass", nameAndTags, lineInfo);
    ASSERT_NE(result.get(), nullptr);

    auto moved = std::move(result);
    EXPECT_NE(moved.get(), nullptr);
}
