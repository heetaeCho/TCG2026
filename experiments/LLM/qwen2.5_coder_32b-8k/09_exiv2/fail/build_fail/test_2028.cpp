#include <gtest/gtest.h>

#include "WXMP_Common.hpp"

#include "XMP_Const.h"



// Assuming XMPMetaRef and related functions are defined in some header

extern "C" void WXMPMeta_GetProperty_Float_1(XMPMetaRef xmpRef, XMP_StringPtr schemaNS, XMP_StringPtr propName, double * propValue, XMP_OptionBits * options, WXMP_Result * wResult);



class WXMPMetaTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any necessary setup for tests

        xmpRef = reinterpret_cast<XMPMetaRef>(new XMPMeta());

    }



    void TearDown() override {

        // Cleanup after tests

        delete reinterpret_cast<XMPMeta*>(xmpRef);

    }



    XMPMetaRef xmpRef;

};



TEST_F(WXMPMetaTest_2028, NormalOperation_2028) {

    WXMP_Result result;

    double propValue = 0.0;

    XMP_OptionBits options = 0;



    // Assuming the property is set in some way before testing

    reinterpret_cast<XMPMeta*>(xmpRef)->SetProperty_Float("http://example.com/schema", "property", 123.45, 0);



    WXMPMeta_GetProperty_Float_1(xmpRef, "http://example.com/schema", "property", &propValue, &options, &result);

    EXPECT_EQ(result.int32Result, 1); // true if found

    EXPECT_DOUBLE_EQ(propValue, 123.45);

}



TEST_F(WXMPMetaTest_2028, PropertyNotFound_2028) {

    WXMP_Result result;

    double propValue = 0.0;

    XMP_OptionBits options = 0;



    WXMPMeta_GetProperty_Float_1(xmpRef, "http://example.com/schema", "nonexistentproperty", &propValue, &options, &result);

    EXPECT_EQ(result.int32Result, 0); // false if not found

}



TEST_F(WXMPMetaTest_2028, EmptySchemaNamespaceURI_2028) {

    WXMP_Result result;

    double propValue = 0.0;

    XMP_OptionBits options = 0;



    EXPECT_THROW({

        WXMPMeta_GetProperty_Float_1(xmpRef, "", "property", &propValue, &options, &result);

    }, std::exception);

}



TEST_F(WXMPMetaTest_2028, NullSchemaNamespaceURI_2028) {

    WXMP_Result result;

    double propValue = 0.0;

    XMP_OptionBits options = 0;



    EXPECT_THROW({

        WXMPMeta_GetProperty_Float_1(xmpRef, nullptr, "property", &propValue, &options, &result);

    }, std::exception);

}



TEST_F(WXMPMetaTest_2028, EmptyPropertyName_2028) {

    WXMP_Result result;

    double propValue = 0.0;

    XMP_OptionBits options = 0;



    EXPECT_THROW({

        WXMPMeta_GetProperty_Float_1(xmpRef, "http://example.com/schema", "", &propValue, &options, &result);

    }, std::exception);

}



TEST_F(WXMPMetaTest_2028, NullPropertyName_2028) {

    WXMP_Result result;

    double propValue = 0.0;

    XMP_OptionBits options = 0;



    EXPECT_THROW({

        WXMPMeta_GetProperty_Float_1(xmpRef, "http://example.com/schema", nullptr, &propValue, &options, &result);

    }, std::exception);

}



TEST_F(WXMPMetaTest_2028, NullPropValuePointer_2028) {

    WXMP_Result result;

    XMP_OptionBits options = 0;



    WXMPMeta_GetProperty_Float_1(xmpRef, "http://example.com/schema", "property", nullptr, &options, &result);

    EXPECT_EQ(result.int32Result, 0); // false if not found

}



TEST_F(WXMPMetaTest_2028, NullOptionsPointer_2028) {

    WXMP_Result result;

    double propValue = 0.0;



    WXMPMeta_GetProperty_Float_1(xmpRef, "http://example.com/schema", "property", &propValue, nullptr, &result);

    EXPECT_EQ(result.int32Result, 0); // false if not found

}



TEST_F(WXMPMetaTest_2028, NullWXMP_ResultPointer_2028) {

    double propValue = 0.0;

    XMP_OptionBits options = 0;



    WXMPMeta_GetProperty_Float_1(xmpRef, "http://example.com/schema", "property", &propValue, &options, nullptr);

    // Assuming this does not throw and just ignores the result

}
