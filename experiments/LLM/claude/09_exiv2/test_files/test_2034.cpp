#include <gtest/gtest.h>
#include <cstring>

// Include necessary headers for XMP SDK
#include "XMP_Const.h"
#include "XMPMeta.hpp"
#include "client-glue/WXMP_Common.hpp"

// Declaration of the function under test
extern "C" void WXMPMeta_SetProperty_Date_1(
    XMPMetaRef xmpRef,
    XMP_StringPtr schemaNS,
    XMP_StringPtr propName,
    const XMP_DateTime & propValue,
    XMP_OptionBits options,
    WXMP_Result * wResult);

class WXMPMetaSetPropertyDateTest_2034 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize XMP toolkit
        XMPMeta::Initialize();
        meta = new XMPMeta();
        xmpRef = reinterpret_cast<XMPMetaRef>(meta);

        // Set up a valid date
        memset(&validDate, 0, sizeof(validDate));
        validDate.year = 2023;
        validDate.month = 6;
        validDate.day = 15;
        validDate.hour = 10;
        validDate.minute = 30;
        validDate.second = 45;
        validDate.tzSign = 1;
        validDate.tzHour = 5;
        validDate.tzMinute = 0;
        validDate.nanoSecond = 0;
    }

    void TearDown() override {
        delete meta;
        XMPMeta::Terminate();
    }

    XMPMeta * meta;
    XMPMetaRef xmpRef;
    XMP_DateTime validDate;
};

// Test: Null schema namespace should produce an error
TEST_F(WXMPMetaSetPropertyDateTest_2034, NullSchemaNS_ProducesError_2034) {
    WXMP_Result wResult;
    WXMPMeta_SetProperty_Date_1(xmpRef, nullptr, "propName", validDate, 0, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty schema namespace should produce an error
TEST_F(WXMPMetaSetPropertyDateTest_2034, EmptySchemaNS_ProducesError_2034) {
    WXMP_Result wResult;
    WXMPMeta_SetProperty_Date_1(xmpRef, "", "propName", validDate, 0, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Null property name should produce an error
TEST_F(WXMPMetaSetPropertyDateTest_2034, NullPropName_ProducesError_2034) {
    WXMP_Result wResult;
    WXMPMeta_SetProperty_Date_1(xmpRef, "http://ns.adobe.com/xap/1.0/", nullptr, validDate, 0, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty property name should produce an error
TEST_F(WXMPMetaSetPropertyDateTest_2034, EmptyPropName_ProducesError_2034) {
    WXMP_Result wResult;
    WXMPMeta_SetProperty_Date_1(xmpRef, "http://ns.adobe.com/xap/1.0/", "", validDate, 0, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Both null schema and null prop name should produce error (schema checked first)
TEST_F(WXMPMetaSetPropertyDateTest_2034, BothNullSchemaAndPropName_ProducesSchemaError_2034) {
    WXMP_Result wResult;
    WXMPMeta_SetProperty_Date_1(xmpRef, nullptr, nullptr, validDate, 0, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Both empty schema and empty prop name should produce error (schema checked first)
TEST_F(WXMPMetaSetPropertyDateTest_2034, BothEmptySchemaAndPropName_ProducesSchemaError_2034) {
    WXMP_Result wResult;
    WXMPMeta_SetProperty_Date_1(xmpRef, "", "", validDate, 0, &wResult);
    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Valid inputs should succeed with no error
TEST_F(WXMPMetaSetPropertyDateTest_2034, ValidInputs_NoError_2034) {
    WXMP_Result wResult;
    // Register the namespace first
    XMPMeta::RegisterNamespace("http://ns.adobe.com/xap/1.0/", "xmp");
    WXMPMeta_SetProperty_Date_1(xmpRef, "http://ns.adobe.com/xap/1.0/", "CreateDate", validDate, 0, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Valid set then verify property exists
TEST_F(WXMPMetaSetPropertyDateTest_2034, ValidSetProperty_PropertyExists_2034) {
    WXMP_Result wResult;
    XMPMeta::RegisterNamespace("http://ns.adobe.com/xap/1.0/", "xmp");
    WXMPMeta_SetProperty_Date_1(xmpRef, "http://ns.adobe.com/xap/1.0/", "CreateDate", validDate, 0, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
    
    bool exists = meta->DoesPropertyExist("http://ns.adobe.com/xap/1.0/", "CreateDate");
    EXPECT_TRUE(exists);
}

// Test: Valid set then retrieve date value
TEST_F(WXMPMetaSetPropertyDateTest_2034, ValidSetProperty_RetrieveDate_2034) {
    WXMP_Result wResult;
    XMPMeta::RegisterNamespace("http://ns.adobe.com/xap/1.0/", "xmp");
    WXMPMeta_SetProperty_Date_1(xmpRef, "http://ns.adobe.com/xap/1.0/", "CreateDate", validDate, 0, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);

    XMP_DateTime retrievedDate;
    memset(&retrievedDate, 0, sizeof(retrievedDate));
    XMP_OptionBits opts = 0;
    bool found = meta->GetProperty_Date("http://ns.adobe.com/xap/1.0/", "CreateDate", &retrievedDate, &opts);
    EXPECT_TRUE(found);
    EXPECT_EQ(retrievedDate.year, 2023);
    EXPECT_EQ(retrievedDate.month, 6);
    EXPECT_EQ(retrievedDate.day, 15);
}

// Test: Set property with zero date values
TEST_F(WXMPMetaSetPropertyDateTest_2034, ZeroDateValues_NoError_2034) {
    WXMP_Result wResult;
    XMP_DateTime zeroDate;
    memset(&zeroDate, 0, sizeof(zeroDate));
    
    XMPMeta::RegisterNamespace("http://ns.adobe.com/xap/1.0/", "xmp");
    WXMPMeta_SetProperty_Date_1(xmpRef, "http://ns.adobe.com/xap/1.0/", "CreateDate", zeroDate, 0, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Set property with options parameter
TEST_F(WXMPMetaSetPropertyDateTest_2034, WithOptions_NoError_2034) {
    WXMP_Result wResult;
    XMPMeta::RegisterNamespace("http://ns.adobe.com/xap/1.0/", "xmp");
    WXMPMeta_SetProperty_Date_1(xmpRef, "http://ns.adobe.com/xap/1.0/", "ModifyDate", validDate, 0, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Overwrite an existing date property
TEST_F(WXMPMetaSetPropertyDateTest_2034, OverwriteExistingProperty_2034) {
    WXMP_Result wResult;
    XMPMeta::RegisterNamespace("http://ns.adobe.com/xap/1.0/", "xmp");
    
    WXMPMeta_SetProperty_Date_1(xmpRef, "http://ns.adobe.com/xap/1.0/", "CreateDate", validDate, 0, &wResult);
    EXPECT_EQ(wResult.errMessage, nullptr);

    XMP_DateTime newDate;
    memset(&newDate, 0, sizeof(newDate));
    newDate.year = 2024;
    newDate.month = 1;
    newDate.day = 1;
    
    WXMP_Result wResult2;
    WXMPMeta_SetProperty_Date_1(xmpRef, "http://ns.adobe.com/xap/1.0/", "CreateDate", newDate, 0, &wResult2);
    EXPECT_EQ(wResult2.errMessage, nullptr);

    XMP_DateTime retrievedDate;
    memset(&retrievedDate, 0, sizeof(retrievedDate));
    XMP_OptionBits opts = 0;
    bool found = meta->GetProperty_Date("http://ns.adobe.com/xap/1.0/", "CreateDate", &retrievedDate, &opts);
    EXPECT_TRUE(found);
    EXPECT_EQ(retrievedDate.year, 2024);
    EXPECT_EQ(retrievedDate.month, 1);
    EXPECT_EQ(retrievedDate.day, 1);
}

// Test: WXMP_Result is properly initialized before use
TEST_F(WXMPMetaSetPropertyDateTest_2034, ResultInitializedCorrectly_2034) {
    WXMP_Result wResult;
    // Verify default construction sets errMessage to 0
    EXPECT_EQ(wResult.errMessage, nullptr);
}
