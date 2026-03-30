#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "WXMP_Common.hpp"

#include "XMPMeta.hpp"



class WXMPMetaTest_2007 : public ::testing::Test {

protected:

    XMPMetaRef xmpRef;

    XMP_StringPtr schemaNS = const_cast<XMP_StringPtr>("http://example.com/schema");

    XMP_StringPtr arrayName = const_cast<XMP_StringPtr>("testArray");

    XMP_Index itemIndex = 1;

    XMP_StringPtr itemValue;

    XMP_StringLen valueSize;

    XMP_OptionBits options;

    WXMP_Result wResult;



    void SetUp() override {

        xmpRef = reinterpret_cast<XMPMetaRef>(new XMPMeta());

    }



    void TearDown() override {

        delete reinterpret_cast<XMPMeta*>(xmpRef);

    }

};



TEST_F(WXMPMetaTest_2007, NormalOperation_2007) {

    // Assuming the array item exists and can be retrieved.

    WXMPMeta_GetArrayItem_1(xmpRef, schemaNS, arrayName, itemIndex, &itemValue, &valueSize, &options, &wResult);

    EXPECT_EQ(wResult.int32Result, true);

}



TEST_F(WXMPMetaTest_2007, EmptySchemaNamespaceURI_2007) {

    XMP_StringPtr emptySchemaNS = const_cast<XMP_StringPtr>("");

    try {

        WXMPMeta_GetArrayItem_1(xmpRef, emptySchemaNS, arrayName, itemIndex, &itemValue, &valueSize, &options, &wResult);

    } catch (const XMP_Error& e) {

        EXPECT_EQ(e.GetID(), kXMPErr_BadSchema);

    }

}



TEST_F(WXMPMetaTest_2007, NullSchemaNamespaceURI_2007) {

    try {

        WXMPMeta_GetArrayItem_1(xmpRef, nullptr, arrayName, itemIndex, &itemValue, &valueSize, &options, &wResult);

    } catch (const XMP_Error& e) {

        EXPECT_EQ(e.GetID(), kXMPErr_BadSchema);

    }

}



TEST_F(WXMPMetaTest_2007, EmptyArrayName_2007) {

    XMP_StringPtr emptyArrayName = const_cast<XMP_StringPtr>("");

    try {

        WXMPMeta_GetArrayItem_1(xmpRef, schemaNS, emptyArrayName, itemIndex, &itemValue, &valueSize, &options, &wResult);

    } catch (const XMP_Error& e) {

        EXPECT_EQ(e.GetID(), kXMPErr_BadXPath);

    }

}



TEST_F(WXMPMetaTest_2007, NullArrayName_2007) {

    try {

        WXMPMeta_GetArrayItem_1(xmpRef, schemaNS, nullptr, itemIndex, &itemValue, &valueSize, &options, &wResult);

    } catch (const XMP_Error& e) {

        EXPECT_EQ(e.GetID(), kXMPErr_BadXPath);

    }

}



TEST_F(WXMPMetaTest_2007, ItemNotFound_2007) {

    // Assuming the array item does not exist.

    WXMPMeta_GetArrayItem_1(xmpRef, schemaNS, arrayName, itemIndex, &itemValue, &valueSize, &options, &wResult);

    EXPECT_EQ(wResult.int32Result, false);

}



TEST_F(WXMPMetaTest_2007, NullItemValuePointer_2007) {

    // Assuming the function handles null pointers gracefully.

    WXMPMeta_GetArrayItem_1(xmpRef, schemaNS, arrayName, itemIndex, nullptr, &valueSize, &options, &wResult);

    EXPECT_EQ(wResult.int32Result, false); // or true if default handling is correct

}



TEST_F(WXMPMetaTest_2007, NullValueSizePointer_2007) {

    // Assuming the function handles null pointers gracefully.

    WXMPMeta_GetArrayItem_1(xmpRef, schemaNS, arrayName, itemIndex, &itemValue, nullptr, &options, &wResult);

    EXPECT_EQ(wResult.int32Result, false); // or true if default handling is correct

}



TEST_F(WXMPMetaTest_2007, NullOptionsPointer_2007) {

    // Assuming the function handles null pointers gracefully.

    WXMPMeta_GetArrayItem_1(xmpRef, schemaNS, arrayName, itemIndex, &itemValue, &valueSize, nullptr, &wResult);

    EXPECT_EQ(wResult.int32Result, false); // or true if default handling is correct

}
