#include "catch2/internal/catch_clara.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>

using namespace Catch::Clara;
using namespace Catch::Clara::Detail;

// Mock for BoundValueRefBase to verify setValue calls
class MockBoundValueRef : public BoundValueRefBase {
public:
    MOCK_METHOD(ParserResult, setValue, (const std::string& arg), (override));
};

class ExeNameTest_667 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default construction gives default name
TEST_F(ExeNameTest_667, DefaultConstructionGivesDefaultName_667) {
    ExeName exeName;
    // Default name should be "<executable>" based on the constructor
    EXPECT_EQ(exeName.name(), "<executable>");
}

// Test set with simple filename (no path separators)
TEST_F(ExeNameTest_667, SetSimpleFilename_667) {
    ExeName exeName;
    auto result = exeName.set("myprogram");
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(exeName.name(), "myprogram");
}

// Test set with Unix-style path
TEST_F(ExeNameTest_667, SetUnixStylePath_667) {
    ExeName exeName;
    auto result = exeName.set("/usr/local/bin/myprogram");
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(exeName.name(), "myprogram");
}

// Test set with Windows-style path using backslashes
TEST_F(ExeNameTest_667, SetWindowsStylePath_667) {
    ExeName exeName;
    auto result = exeName.set("C:\\Program Files\\myprogram.exe");
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(exeName.name(), "myprogram.exe");
}

// Test set with mixed separators
TEST_F(ExeNameTest_667, SetMixedSeparators_667) {
    ExeName exeName;
    auto result = exeName.set("C:\\Users/someone\\bin/myprogram");
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(exeName.name(), "myprogram");
}

// Test set with trailing slash
TEST_F(ExeNameTest_667, SetTrailingSlash_667) {
    ExeName exeName;
    auto result = exeName.set("/usr/bin/");
    EXPECT_TRUE(static_cast<bool>(result));
    // After last slash there's nothing, so filename should be empty
    EXPECT_EQ(exeName.name(), "");
}

// Test set with empty string
TEST_F(ExeNameTest_667, SetEmptyString_667) {
    ExeName exeName;
    auto result = exeName.set("");
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(exeName.name(), "");
}

// Test set with just a slash
TEST_F(ExeNameTest_667, SetJustSlash_667) {
    ExeName exeName;
    auto result = exeName.set("/");
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(exeName.name(), "");
}

// Test set with just a backslash
TEST_F(ExeNameTest_667, SetJustBackslash_667) {
    ExeName exeName;
    auto result = exeName.set("\\");
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(exeName.name(), "");
}

// Test construction with string reference
TEST_F(ExeNameTest_667, ConstructWithStringRef_667) {
    std::string ref;
    ExeName exeName(ref);
    auto result = exeName.set("/path/to/program");
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(exeName.name(), "program");
    // The ref should also be updated since m_ref is bound
    EXPECT_EQ(ref, "program");
}

// Test set updates the string ref correctly with simple name
TEST_F(ExeNameTest_667, SetUpdatesStringRef_667) {
    std::string ref;
    ExeName exeName(ref);
    exeName.set("simple_name");
    EXPECT_EQ(ref, "simple_name");
}

// Test set updates the string ref correctly with path
TEST_F(ExeNameTest_667, SetUpdatesStringRefWithPath_667) {
    std::string ref;
    ExeName exeName(ref);
    exeName.set("/usr/bin/test_program");
    EXPECT_EQ(ref, "test_program");
}

// Test multiple set calls update name correctly
TEST_F(ExeNameTest_667, MultipleSetCalls_667) {
    ExeName exeName;
    exeName.set("first");
    EXPECT_EQ(exeName.name(), "first");
    
    exeName.set("/path/to/second");
    EXPECT_EQ(exeName.name(), "second");
    
    exeName.set("C:\\third.exe");
    EXPECT_EQ(exeName.name(), "third.exe");
}

// Test result type is Matched when no ref is set
TEST_F(ExeNameTest_667, ResultTypeIsMatchedWithoutRef_667) {
    ExeName exeName;
    auto result = exeName.set("test");
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(result.type(), ResultBase::Ok);
}

// Test set with filename containing dots
TEST_F(ExeNameTest_667, SetFilenameWithDots_667) {
    ExeName exeName;
    exeName.set("/path/to/my.program.exe");
    EXPECT_EQ(exeName.name(), "my.program.exe");
}

// Test set with filename containing spaces
TEST_F(ExeNameTest_667, SetFilenameWithSpaces_667) {
    ExeName exeName;
    exeName.set("/path/to/my program");
    EXPECT_EQ(exeName.name(), "my program");
}

// Test set with multiple consecutive slashes
TEST_F(ExeNameTest_667, SetMultipleConsecutiveSlashes_667) {
    ExeName exeName;
    exeName.set("///path///to///program");
    EXPECT_EQ(exeName.name(), "program");
}

// Test name() returns const reference
TEST_F(ExeNameTest_667, NameReturnsConstRef_667) {
    ExeName exeName;
    exeName.set("testname");
    const std::string& nameRef = exeName.name();
    EXPECT_EQ(nameRef, "testname");
}

// Test set with string ref and Windows path
TEST_F(ExeNameTest_667, SetStringRefWindowsPath_667) {
    std::string ref;
    ExeName exeName(ref);
    exeName.set("C:\\Users\\test\\Desktop\\program.exe");
    EXPECT_EQ(ref, "program.exe");
    EXPECT_EQ(exeName.name(), "program.exe");
}
