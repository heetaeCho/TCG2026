#include <gtest/gtest.h>
#include <string>

// Include the header for XmpPropertyInfo
#include "exiv2/properties.hpp"

namespace {

// Test fixture for XmpPropertyInfo tests
class XmpPropertyInfoTest_1242 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that operator== returns true when the name matches
TEST_F(XmpPropertyInfoTest_1242, OperatorEqualsReturnsTrueForMatchingName_1242) {
    Exiv2::XmpPropertyInfo info{};
    // We need to set up name_ to a known value.
    // Since XmpPropertyInfo is a struct with public members, we can initialize it.
    // Based on the struct definition, name_ should be a const char* member.
    // Let's create an instance with a known name.
    
    // XmpPropertyInfo is typically a POD-like struct with public fields.
    // We'll try to create one with aggregate initialization.
    // The typical fields order in XmpPropertyInfo based on Exiv2 codebase:
    // const char* name_, const char* title_, const char* xmpValueType_, 
    // XmpCategory xmpCategory_, const char* desc_
    
    Exiv2::XmpPropertyInfo info2 = {"TestName", "TestTitle", "XmpText", Exiv2::xmpInternal, "Description"};
    
    std::string matchingName("TestName");
    EXPECT_TRUE(info2 == matchingName);
}

// Test that operator== returns false when the name does not match
TEST_F(XmpPropertyInfoTest_1242, OperatorEqualsReturnsFalseForNonMatchingName_1242) {
    Exiv2::XmpPropertyInfo info = {"TestName", "TestTitle", "XmpText", Exiv2::xmpInternal, "Description"};
    
    std::string nonMatchingName("DifferentName");
    EXPECT_FALSE(info == nonMatchingName);
}

// Test that operator== returns false for an empty string when name is non-empty
TEST_F(XmpPropertyInfoTest_1242, OperatorEqualsReturnsFalseForEmptyStringWhenNameIsNonEmpty_1242) {
    Exiv2::XmpPropertyInfo info = {"SomeName", "Title", "XmpText", Exiv2::xmpInternal, "Desc"};
    
    std::string emptyStr("");
    EXPECT_FALSE(info == emptyStr);
}

// Test that operator== handles comparison with exact same string content
TEST_F(XmpPropertyInfoTest_1242, OperatorEqualsExactMatch_1242) {
    Exiv2::XmpPropertyInfo info = {"dc", "Dublin Core", "XmpText", Exiv2::xmpInternal, "Dublin Core namespace"};
    
    std::string name("dc");
    EXPECT_TRUE(info == name);
}

// Test that operator== is case-sensitive
TEST_F(XmpPropertyInfoTest_1242, OperatorEqualsCaseSensitive_1242) {
    Exiv2::XmpPropertyInfo info = {"TestName", "Title", "XmpText", Exiv2::xmpInternal, "Desc"};
    
    std::string upperCaseName("TESTNAME");
    EXPECT_FALSE(info == upperCaseName);
    
    std::string lowerCaseName("testname");
    EXPECT_FALSE(info == lowerCaseName);
    
    std::string mixedCaseName("testName");
    EXPECT_FALSE(info == mixedCaseName);
}

// Test that operator== works with a longer string that starts with the name
TEST_F(XmpPropertyInfoTest_1242, OperatorEqualsReturnsFalseForPartialMatch_1242) {
    Exiv2::XmpPropertyInfo info = {"Test", "Title", "XmpText", Exiv2::xmpInternal, "Desc"};
    
    std::string longerName("TestName");
    EXPECT_FALSE(info == longerName);
}

// Test that operator== works with a substring of the name
TEST_F(XmpPropertyInfoTest_1242, OperatorEqualsReturnsFalseForSubstring_1242) {
    Exiv2::XmpPropertyInfo info = {"TestName", "Title", "XmpText", Exiv2::xmpInternal, "Desc"};
    
    std::string substring("Test");
    EXPECT_FALSE(info == substring);
}

// Test with a name containing special characters
TEST_F(XmpPropertyInfoTest_1242, OperatorEqualsWithSpecialCharacters_1242) {
    Exiv2::XmpPropertyInfo info = {"name-with-dashes", "Title", "XmpText", Exiv2::xmpInternal, "Desc"};
    
    std::string name("name-with-dashes");
    EXPECT_TRUE(info == name);
    
    std::string wrongName("name_with_dashes");
    EXPECT_FALSE(info == wrongName);
}

// Test with a name containing spaces
TEST_F(XmpPropertyInfoTest_1242, OperatorEqualsWithSpaces_1242) {
    Exiv2::XmpPropertyInfo info = {"name with spaces", "Title", "XmpText", Exiv2::xmpInternal, "Desc"};
    
    std::string name("name with spaces");
    EXPECT_TRUE(info == name);
}

// Test with a single character name
TEST_F(XmpPropertyInfoTest_1242, OperatorEqualsWithSingleCharName_1242) {
    Exiv2::XmpPropertyInfo info = {"x", "Title", "XmpText", Exiv2::xmpInternal, "Desc"};
    
    std::string name("x");
    EXPECT_TRUE(info == name);
    
    std::string wrongName("y");
    EXPECT_FALSE(info == wrongName);
}

}  // namespace
