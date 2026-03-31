#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "exiv2/properties.hpp"
#include "exiv2/types.hpp"

using namespace Exiv2;

class XmpPropertyInfoOutputTest_1270 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test normal operation with xmpExternal category
TEST_F(XmpPropertyInfoOutputTest_1270, OutputExternalCategory_1270) {
    XmpPropertyInfo info;
    info.name_ = "TestName";
    info.title_ = "TestTitle";
    info.xmpValueType_ = "Text";
    info.typeId_ = xmpText;
    info.xmpCategory_ = xmpExternal;
    info.desc_ = "A simple description";

    os << info;

    std::string result = os.str();
    EXPECT_NE(result.find("TestName"), std::string::npos);
    EXPECT_NE(result.find("TestTitle"), std::string::npos);
    EXPECT_NE(result.find("Text"), std::string::npos);
    EXPECT_NE(result.find("External"), std::string::npos);
    EXPECT_NE(result.find("\"A simple description\""), std::string::npos);
}

// Test normal operation with xmpInternal category
TEST_F(XmpPropertyInfoOutputTest_1270, OutputInternalCategory_1270) {
    XmpPropertyInfo info;
    info.name_ = "InternalProp";
    info.title_ = "InternalTitle";
    info.xmpValueType_ = "Integer";
    info.typeId_ = xmpText;
    info.xmpCategory_ = xmpInternal;
    info.desc_ = "Internal description";

    os << info;

    std::string result = os.str();
    EXPECT_NE(result.find("InternalProp"), std::string::npos);
    EXPECT_NE(result.find("Internal"), std::string::npos);
    // Should NOT contain "External"
    EXPECT_EQ(result.find("External"), std::string::npos);
}

// Test description with embedded quotes (should be escaped as double quotes)
TEST_F(XmpPropertyInfoOutputTest_1270, DescriptionWithQuotes_1270) {
    XmpPropertyInfo info;
    info.name_ = "QuoteProp";
    info.title_ = "QuoteTitle";
    info.xmpValueType_ = "Text";
    info.typeId_ = xmpText;
    info.xmpCategory_ = xmpExternal;
    info.desc_ = "He said \"hello\"";

    os << info;

    std::string result = os.str();
    // The quotes in desc should be doubled: "He said ""hello"""
    EXPECT_NE(result.find("\"He said \"\"hello\"\"\""), std::string::npos);
}

// Test empty description
TEST_F(XmpPropertyInfoOutputTest_1270, EmptyDescription_1270) {
    XmpPropertyInfo info;
    info.name_ = "EmptyDesc";
    info.title_ = "EmptyDescTitle";
    info.xmpValueType_ = "Text";
    info.typeId_ = xmpText;
    info.xmpCategory_ = xmpExternal;
    info.desc_ = "";

    os << info;

    std::string result = os.str();
    EXPECT_NE(result.find("EmptyDesc"), std::string::npos);
    // Description should just be ""
    EXPECT_NE(result.find("\"\""), std::string::npos);
}

// Test description that is entirely a quote character
TEST_F(XmpPropertyInfoOutputTest_1270, DescriptionAllQuotes_1270) {
    XmpPropertyInfo info;
    info.name_ = "AllQuotes";
    info.title_ = "AllQuotesTitle";
    info.xmpValueType_ = "Text";
    info.typeId_ = xmpText;
    info.xmpCategory_ = xmpInternal;
    info.desc_ = "\"\"\"";

    os << info;

    std::string result = os.str();
    // Three quotes should become six quotes, wrapped in outer quotes: """""""""
    // Original: """ -> escaped: """""" -> wrapped: """""""""" (but let's just check it contains doubled quotes)
    EXPECT_NE(result.find("\"\"\"\"\"\"\"\""), std::string::npos);
}

// Test output ends with newline
TEST_F(XmpPropertyInfoOutputTest_1270, OutputEndsWithNewline_1270) {
    XmpPropertyInfo info;
    info.name_ = "NewlineTest";
    info.title_ = "NewlineTitle";
    info.xmpValueType_ = "Text";
    info.typeId_ = xmpText;
    info.xmpCategory_ = xmpExternal;
    info.desc_ = "desc";

    os << info;

    std::string result = os.str();
    ASSERT_FALSE(result.empty());
    EXPECT_EQ(result.back(), '\n');
}

// Test operator== of XmpPropertyInfo
class XmpPropertyInfoEqualityTest_1270 : public ::testing::Test {};

TEST_F(XmpPropertyInfoEqualityTest_1270, MatchingName_1270) {
    XmpPropertyInfo info;
    info.name_ = "TestProperty";
    info.title_ = "Title";
    info.xmpValueType_ = "Text";
    info.typeId_ = xmpText;
    info.xmpCategory_ = xmpExternal;
    info.desc_ = "desc";

    EXPECT_TRUE(info == std::string("TestProperty"));
}

TEST_F(XmpPropertyInfoEqualityTest_1270, NonMatchingName_1270) {
    XmpPropertyInfo info;
    info.name_ = "TestProperty";
    info.title_ = "Title";
    info.xmpValueType_ = "Text";
    info.typeId_ = xmpText;
    info.xmpCategory_ = xmpExternal;
    info.desc_ = "desc";

    EXPECT_FALSE(info == std::string("OtherProperty"));
}

TEST_F(XmpPropertyInfoEqualityTest_1270, EmptyNameMatch_1270) {
    XmpPropertyInfo info;
    info.name_ = "";
    info.title_ = "Title";
    info.xmpValueType_ = "Text";
    info.typeId_ = xmpText;
    info.xmpCategory_ = xmpExternal;
    info.desc_ = "desc";

    EXPECT_TRUE(info == std::string(""));
}

TEST_F(XmpPropertyInfoEqualityTest_1270, EmptyNameNoMatch_1270) {
    XmpPropertyInfo info;
    info.name_ = "";
    info.title_ = "Title";
    info.xmpValueType_ = "Text";
    info.typeId_ = xmpText;
    info.xmpCategory_ = xmpExternal;
    info.desc_ = "desc";

    EXPECT_FALSE(info == std::string("something"));
}

// Test that the output contains comma-separated fields
TEST_F(XmpPropertyInfoOutputTest_1270, CommaSeparatedFields_1270) {
    XmpPropertyInfo info;
    info.name_ = "Field1";
    info.title_ = "Field2";
    info.xmpValueType_ = "Field3";
    info.typeId_ = xmpText;
    info.xmpCategory_ = xmpExternal;
    info.desc_ = "Field6";

    os << info;

    std::string result = os.str();
    // Check commas exist - at least 5 commas for 6 fields
    size_t commaCount = 0;
    for (char c : result) {
        if (c == ',') commaCount++;
    }
    EXPECT_GE(commaCount, 5u);
}

// Test description with special characters (no quotes)
TEST_F(XmpPropertyInfoOutputTest_1270, DescriptionWithSpecialChars_1270) {
    XmpPropertyInfo info;
    info.name_ = "SpecialProp";
    info.title_ = "SpecialTitle";
    info.xmpValueType_ = "Text";
    info.typeId_ = xmpText;
    info.xmpCategory_ = xmpInternal;
    info.desc_ = "Line1\nLine2\tTabbed";

    os << info;

    std::string result = os.str();
    EXPECT_NE(result.find("SpecialProp"), std::string::npos);
    // The special chars should be preserved as-is (only quotes are escaped)
    EXPECT_NE(result.find("Line1\nLine2\tTabbed"), std::string::npos);
}

// Test stream chaining - operator<< returns the stream
TEST_F(XmpPropertyInfoOutputTest_1270, StreamChaining_1270) {
    XmpPropertyInfo info;
    info.name_ = "ChainProp";
    info.title_ = "ChainTitle";
    info.xmpValueType_ = "Text";
    info.typeId_ = xmpText;
    info.xmpCategory_ = xmpExternal;
    info.desc_ = "chain desc";

    std::ostringstream& returned = static_cast<std::ostringstream&>(os << info);
    EXPECT_EQ(&returned, &os);
}
