#include <gtest/gtest.h>

#include "WXMPMeta.cpp"

#include "XMP_Const.h"

#include "WXMP_Common.hpp"



class WXMPMetaTest_2029 : public ::testing::Test {

protected:

    XMPMetaRef xmpRef;

    XMP_DateTime propValue;

    XMP_OptionBits options;

    WXMP_Result wResult;



    void SetUp() override {

        xmpRef = reinterpret_cast<XMPMetaRef>(new XMPMeta());

        memset(&propValue, 0, sizeof(XMP_DateTime));

        memset(&options, 0, sizeof(XMP_OptionBits));

        memset(&wResult, 0, sizeof(WXMP_Result));

    }



    void TearDown() override {

        delete reinterpret_cast<XMPMeta*>(xmpRef);

        xmpRef = nullptr;

    }

};



TEST_F(WXMPMetaTest_2029, ValidInput_ReturnsFound_2029) {

    const char* schemaNS = "http://example.com/schema";

    const char* propName = "dateProperty";

    WXMPMeta_GetProperty_Date_1(xmpRef, schemaNS, propName, &propValue, &options, &wResult);

    EXPECT_EQ(wResult.int32Result, 0); // Assuming GetProperty_Date returns false if not found

}



TEST_F(WXMPMetaTest_2029, EmptySchemaNamespaceURI_ThrowsException_2029) {

    const char* schemaNS = "";

    const char* propName = "dateProperty";

    EXPECT_THROW(WXMPMeta_GetProperty_Date_1(xmpRef, schemaNS, propName, &propValue, &options, &wResult), XMP_Error);

}



TEST_F(WXMPMetaTest_2029, NullSchemaNamespaceURI_ThrowsException_2029) {

    const char* schemaNS = nullptr;

    const char* propName = "dateProperty";

    EXPECT_THROW(WXMPMeta_GetProperty_Date_1(xmpRef, schemaNS, propName, &propValue, &options, &wResult), XMP_Error);

}



TEST_F(WXMPMetaTest_2029, EmptyPropertyName_ThrowsException_2029) {

    const char* schemaNS = "http://example.com/schema";

    const char* propName = "";

    EXPECT_THROW(WXMPMeta_GetProperty_Date_1(xmpRef, schemaNS, propName, &propValue, &options, &wResult), XMP_Error);

}



TEST_F(WXMPMetaTest_2029, NullPropertyName_ThrowsException_2029) {

    const char* schemaNS = "http://example.com/schema";

    const char* propName = nullptr;

    EXPECT_THROW(WXMPMeta_GetProperty_Date_1(xmpRef, schemaNS, propName, &propValue, &options, &wResult), XMP_Error);

}



TEST_F(WXMPMetaTest_2029, NullPropValue_DoesNotThrowException_2029) {

    const char* schemaNS = "http://example.com/schema";

    const char* propName = "dateProperty";

    EXPECT_NO_THROW(WXMPMeta_GetProperty_Date_1(xmpRef, schemaNS, propName, nullptr, &options, &wResult));

}



TEST_F(WXMPMetaTest_2029, NullOptions_DoesNotThrowException_2029) {

    const char* schemaNS = "http://example.com/schema";

    const char* propName = "dateProperty";

    EXPECT_NO_THROW(WXMPMeta_GetProperty_Date_1(xmpRef, schemaNS, propName, &propValue, nullptr, &wResult));

}
