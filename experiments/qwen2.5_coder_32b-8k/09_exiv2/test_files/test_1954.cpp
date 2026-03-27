#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming the necessary headers for XMPMeta and WXMP_Result are included



extern "C" {

    void WXMPUtils_CatenateArrayItems_1(XMPMetaRef wxmpObj, XMP_StringPtr schemaNS, XMP_StringPtr arrayName, XMP_StringPtr separator, XMP_StringPtr quotes, XMP_OptionBits options, XMP_StringPtr * catedStr, XMP_StringLen * catedLen, WXMP_Result * wResult);

}



class WXMPUtilsTest_1954 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize necessary setup if needed

        wxmpObj = reinterpret_cast<XMPMetaRef>(new XMPMeta());

        result.errMessage = nullptr;

        result.ptrResult = nullptr;

        result.floatResult = 0.0;

        result.int64Result = 0;

        result.int32Result = 0;

    }



    void TearDown() override {

        // Cleanup if needed

        delete reinterpret_cast<XMPMeta*>(wxmpObj);

    }



    XMPMetaRef wxmpObj;

    WXMP_Result result;

};



TEST_F(WXMPUtilsTest_1954, NormalOperation_1954) {

    const char* schemaNS = "http://example.com/schema";

    const char* arrayName = "testArray";

    const char* separator = ", ";

    const char* quotes = "\"";

    XMP_OptionBits options = 0;

    XMP_StringPtr catedStr = nullptr;

    XMP_StringLen catedLen = 0;



    WXMPUtils_CatenateArrayItems_1(wxmpObj, schemaNS, arrayName, separator, quotes, options, &catedStr, &catedLen, &result);



    EXPECT_EQ(result.errMessage, nullptr);

    // Additional checks can be done based on expected output if possible

}



TEST_F(WXMPUtilsTest_1954, EmptySchemaNamespaceURI_1954) {

    const char* schemaNS = "";

    const char* arrayName = "testArray";

    XMP_OptionBits options = 0;

    XMP_StringPtr catedStr = nullptr;

    XMP_StringLen catedLen = 0;



    WXMPUtils_CatenateArrayItems_1(wxmpObj, schemaNS, arrayName, nullptr, nullptr, options, &catedStr, &catedLen, &result);



    EXPECT_NE(result.errMessage, nullptr);

    EXPECT_STREQ(result.errMessage, "Empty schema namespace URI");

}



TEST_F(WXMPUtilsTest_1954, NullSchemaNamespaceURI_1954) {

    const char* schemaNS = nullptr;

    const char* arrayName = "testArray";

    XMP_OptionBits options = 0;

    XMP_StringPtr catedStr = nullptr;

    XMP_StringLen catedLen = 0;



    WXMPUtils_CatenateArrayItems_1(wxmpObj, schemaNS, arrayName, nullptr, nullptr, options, &catedStr, &catedLen, &result);



    EXPECT_NE(result.errMessage, nullptr);

    EXPECT_STREQ(result.errMessage, "Empty schema namespace URI");

}



TEST_F(WXMPUtilsTest_1954, EmptyArrayName_1954) {

    const char* schemaNS = "http://example.com/schema";

    const char* arrayName = "";

    XMP_OptionBits options = 0;

    XMP_StringPtr catedStr = nullptr;

    XMP_StringLen catedLen = 0;



    WXMPUtils_CatenateArrayItems_1(wxmpObj, schemaNS, arrayName, nullptr, nullptr, options, &catedStr, &catedLen, &result);



    EXPECT_NE(result.errMessage, nullptr);

    EXPECT_STREQ(result.errMessage, "Empty array name");

}



TEST_F(WXMPUtilsTest_1954, NullArrayName_1954) {

    const char* schemaNS = "http://example.com/schema";

    const char* arrayName = nullptr;

    XMP_OptionBits options = 0;

    XMP_StringPtr catedStr = nullptr;

    XMP_StringLen catedLen = 0;



    WXMPUtils_CatenateArrayItems_1(wxmpObj, schemaNS, arrayName, nullptr, nullptr, options, &catedStr, &catedLen, &result);



    EXPECT_NE(result.errMessage, nullptr);

    EXPECT_STREQ(result.errMessage, "Empty array name");

}



TEST_F(WXMPUtilsTest_1954, DefaultSeparatorAndQuotes_1954) {

    const char* schemaNS = "http://example.com/schema";

    const char* arrayName = "testArray";

    XMP_OptionBits options = 0;

    XMP_StringPtr catedStr = nullptr;

    XMP_StringLen catedLen = 0;



    WXMPUtils_CatenateArrayItems_1(wxmpObj, schemaNS, arrayName, nullptr, nullptr, options, &catedStr, &catedLen, &result);



    EXPECT_EQ(result.errMessage, nullptr);

    // Additional checks can be done based on expected output if possible

}



TEST_F(WXMPUtilsTest_1954, NullCatedStrAndCatedLen_1954) {

    const char* schemaNS = "http://example.com/schema";

    const char* arrayName = "testArray";

    XMP_OptionBits options = 0;

    XMP_StringPtr catedStr = nullptr;

    XMP_StringLen catedLen = 0;



    WXMPUtils_CatenateArrayItems_1(wxmpObj, schemaNS, arrayName, ", ", "\"", options, &catedStr, &catedLen, &result);



    EXPECT_EQ(result.errMessage, nullptr);

    // Additional checks can be done based on expected output if possible

}
