#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "XMP_Const.h"
#include "WXMP_Common.hpp"
#include "WXMPUtils.hpp"

using namespace ::testing;

class WXMPUtilsTest_1955 : public ::testing::Test {
protected:
    WXMPUtilsTest_1955() {}

    virtual void SetUp() override {
        // Initialize any required objects before each test
    }

    virtual void TearDown() override {
        // Clean up any resources if needed after each test
    }
};

// Test for normal operation where valid input is provided
TEST_F(WXMPUtilsTest_1955, SeparateArrayItems_ValidInput_1955) {
    XMPMetaRef wxmpObj = nullptr;  // Replace with appropriate initialization
    XMP_StringPtr schemaNS = "http://example.com/schema";
    XMP_StringPtr arrayName = "arrayName";
    XMP_OptionBits options = 0;
    XMP_StringPtr catedStr = "item1,item2,item3";
    WXMP_Result wResult;
    
    // Call the function
    WXMPUtils_SeparateArrayItems_1(wxmpObj, schemaNS, arrayName, options, catedStr, &wResult);

    // Validate the expected outcome
    EXPECT_EQ(wResult.errMessage, nullptr);  // No error message
    EXPECT_TRUE(wResult.ptrResult != nullptr);  // Result pointer should be non-null
}

// Test for null wxmpObj which should throw an exception
TEST_F(WXMPUtilsTest_1955, SeparateArrayItems_NullWXMPObj_1955) {
    XMPMetaRef wxmpObj = nullptr;
    XMP_StringPtr schemaNS = "http://example.com/schema";
    XMP_StringPtr arrayName = "arrayName";
    XMP_OptionBits options = 0;
    XMP_StringPtr catedStr = "item1,item2,item3";
    WXMP_Result wResult;

    // Expect exception to be thrown
    EXPECT_THROW(WXMPUtils_SeparateArrayItems_1(wxmpObj, schemaNS, arrayName, options, catedStr, &wResult),
                 const XMP_Error&);
}

// Test for empty schemaNS, which should throw an exception
TEST_F(WXMPUtilsTest_1955, SeparateArrayItems_EmptySchemaNS_1955) {
    XMPMetaRef wxmpObj = nullptr;  // Replace with appropriate initialization
    XMP_StringPtr schemaNS = "";
    XMP_StringPtr arrayName = "arrayName";
    XMP_OptionBits options = 0;
    XMP_StringPtr catedStr = "item1,item2,item3";
    WXMP_Result wResult;

    // Expect exception to be thrown
    EXPECT_THROW(WXMPUtils_SeparateArrayItems_1(wxmpObj, schemaNS, arrayName, options, catedStr, &wResult),
                 const XMP_Error&);
}

// Test for empty arrayName, which should throw an exception
TEST_F(WXMPUtilsTest_1955, SeparateArrayItems_EmptyArrayName_1955) {
    XMPMetaRef wxmpObj = nullptr;  // Replace with appropriate initialization
    XMP_StringPtr schemaNS = "http://example.com/schema";
    XMP_StringPtr arrayName = "";
    XMP_OptionBits options = 0;
    XMP_StringPtr catedStr = "item1,item2,item3";
    WXMP_Result wResult;

    // Expect exception to be thrown
    EXPECT_THROW(WXMPUtils_SeparateArrayItems_1(wxmpObj, schemaNS, arrayName, options, catedStr, &wResult),
                 const XMP_Error&);
}

// Test for null catedStr, which should default to an empty string
TEST_F(WXMPUtilsTest_1955, SeparateArrayItems_NullCatedStr_1955) {
    XMPMetaRef wxmpObj = nullptr;  // Replace with appropriate initialization
    XMP_StringPtr schemaNS = "http://example.com/schema";
    XMP_StringPtr arrayName = "arrayName";
    XMP_OptionBits options = 0;
    XMP_StringPtr catedStr = nullptr;
    WXMP_Result wResult;

    // Call the function with null catedStr
    WXMPUtils_SeparateArrayItems_1(wxmpObj, schemaNS, arrayName, options, catedStr, &wResult);

    // Validate the expected outcome
    EXPECT_EQ(wResult.errMessage, nullptr);  // No error message
    EXPECT_TRUE(wResult.ptrResult != nullptr);  // Result pointer should be non-null
}

// Test for boundary condition when arrayName is at the maximum length (assuming 255 characters as an example)
TEST_F(WXMPUtilsTest_1955, SeparateArrayItems_MaxLengthArrayName_1955) {
    XMPMetaRef wxmpObj = nullptr;  // Replace with appropriate initialization
    XMP_StringPtr schemaNS = "http://example.com/schema";
    char longArrayName[256] = {};  // Max length arrayName
    std::fill(longArrayName, longArrayName + 255, 'a');  // Fill with 'a's
    XMP_OptionBits options = 0;
    XMP_StringPtr catedStr = "item1,item2,item3";
    WXMP_Result wResult;

    // Call the function
    WXMPUtils_SeparateArrayItems_1(wxmpObj, schemaNS, longArrayName, options, catedStr, &wResult);

    // Validate the expected outcome
    EXPECT_EQ(wResult.errMessage, nullptr);  // No error message
    EXPECT_TRUE(wResult.ptrResult != nullptr);  // Result pointer should be non-null
}

// Test for boundary condition when catedStr is empty
TEST_F(WXMPUtilsTest_1955, SeparateArrayItems_EmptyCatedStr_1955) {
    XMPMetaRef wxmpObj = nullptr;  // Replace with appropriate initialization
    XMP_StringPtr schemaNS = "http://example.com/schema";
    XMP_StringPtr arrayName = "arrayName";
    XMP_OptionBits options = 0;
    XMP_StringPtr catedStr = "";
    WXMP_Result wResult;

    // Call the function with empty catedStr
    WXMPUtils_SeparateArrayItems_1(wxmpObj, schemaNS, arrayName, options, catedStr, &wResult);

    // Validate the expected outcome
    EXPECT_EQ(wResult.errMessage, nullptr);  // No error message
    EXPECT_TRUE(wResult.ptrResult != nullptr);  // Result pointer should be non-null
}