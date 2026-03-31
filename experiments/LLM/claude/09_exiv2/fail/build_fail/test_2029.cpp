#include <gtest/gtest.h>
#include <cstring>

// Include necessary headers
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPMeta.hpp"
#include "XMPCore_Impl.hpp"

// Forward declaration of the function under test
extern "C" void WXMPMeta_GetProperty_Date_1(
    XMPMetaRef xmpRef,
    XMP_StringPtr schemaNS,
    XMP_StringPtr propName,
    XMP_DateTime * propValue,
    XMP_OptionBits * options,
    WXMP_Result * wResult);

class WXMPMetaGetPropertyDateTest_2029 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize XMP toolkit
        XMPMeta::Initialize();
        meta = new XMPMeta();
    }

    void TearDown() override {
        delete meta;
        XMPMeta::Terminate();
    }

    XMPMeta* meta;

    XMPMetaRef GetRef() {
        return (XMPMetaRef)meta;
    }
};

// Test: Null schema namespace should set error message in result
TEST_F(WXMPMetaGetPropertyDateTest_2029, NullSchemaNS_SetsError_2029) {
    WXMP_Result wResult;
    XMP_DateTime propValue;
    XMP_OptionBits options;

    WXMPMeta_GetProperty_Date_1(GetRef(), nullptr, "propName", &propValue, &options, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty schema namespace string should set error message in result
TEST_F(WXMPMetaGetPropertyDateTest_2029, EmptySchemaNS_SetsError_2029) {
    WXMP_Result wResult;
    XMP_DateTime propValue;
    XMP_OptionBits options;

    WXMPMeta_GetProperty_Date_1(GetRef(), "", "propName", &propValue, &options, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Null property name should set error message in result
TEST_F(WXMPMetaGetPropertyDateTest_2029, NullPropName_SetsError_2029) {
    WXMP_Result wResult;
    XMP_DateTime propValue;
    XMP_OptionBits options;

    WXMPMeta_GetProperty_Date_1(GetRef(), "http://ns.adobe.com/xap/1.0/", nullptr, &propValue, &options, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty property name string should set error message in result
TEST_F(WXMPMetaGetPropertyDateTest_2029, EmptyPropName_SetsError_2029) {
    WXMP_Result wResult;
    XMP_DateTime propValue;
    XMP_OptionBits options;

    WXMPMeta_GetProperty_Date_1(GetRef(), "http://ns.adobe.com/xap/1.0/", "", &propValue, &options, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Non-existent property should return false (int32Result == 0) and no error
TEST_F(WXMPMetaGetPropertyDateTest_2029, NonExistentProperty_ReturnsFalse_2029) {
    WXMP_Result wResult;
    XMP_DateTime propValue;
    XMP_OptionBits options;

    memset(&propValue, 0, sizeof(propValue));
    options = 0;

    WXMPMeta_GetProperty_Date_1(GetRef(), "http://ns.adobe.com/xap/1.0/", "NonExistent", &propValue, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, 0u);
}

// Test: Setting a date property and then getting it should return true
TEST_F(WXMPMetaGetPropertyDateTest_2029, ExistingDateProperty_ReturnsTrue_2029) {
    XMP_DateTime dateValue;
    memset(&dateValue, 0, sizeof(dateValue));
    dateValue.year = 2023;
    dateValue.month = 6;
    dateValue.day = 15;
    dateValue.hour = 10;
    dateValue.minute = 30;
    dateValue.second = 45;
    dateValue.tzSign = 1;
    dateValue.tzHour = 5;
    dateValue.tzMinute = 30;
    dateValue.nanoSecond = 0;

    meta->SetProperty_Date("http://ns.adobe.com/xap/1.0/", "CreateDate", dateValue, 0);

    WXMP_Result wResult;
    XMP_DateTime retrievedValue;
    XMP_OptionBits options = 0;
    memset(&retrievedValue, 0, sizeof(retrievedValue));

    WXMPMeta_GetProperty_Date_1(GetRef(), "http://ns.adobe.com/xap/1.0/", "CreateDate", &retrievedValue, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, 0u);
    EXPECT_EQ(retrievedValue.year, 2023);
    EXPECT_EQ(retrievedValue.month, 6);
    EXPECT_EQ(retrievedValue.day, 15);
}

// Test: Null propValue pointer should not crash (uses voidDateTime internally)
TEST_F(WXMPMetaGetPropertyDateTest_2029, NullPropValue_DoesNotCrash_2029) {
    WXMP_Result wResult;
    XMP_OptionBits options = 0;

    WXMPMeta_GetProperty_Date_1(GetRef(), "http://ns.adobe.com/xap/1.0/", "CreateDate", nullptr, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Null options pointer should not crash (uses voidOptionBits internally)
TEST_F(WXMPMetaGetPropertyDateTest_2029, NullOptions_DoesNotCrash_2029) {
    WXMP_Result wResult;
    XMP_DateTime propValue;
    memset(&propValue, 0, sizeof(propValue));

    WXMPMeta_GetProperty_Date_1(GetRef(), "http://ns.adobe.com/xap/1.0/", "CreateDate", &propValue, nullptr, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Both null propValue and null options should not crash
TEST_F(WXMPMetaGetPropertyDateTest_2029, NullPropValueAndOptions_DoesNotCrash_2029) {
    WXMP_Result wResult;

    WXMPMeta_GetProperty_Date_1(GetRef(), "http://ns.adobe.com/xap/1.0/", "CreateDate", nullptr, nullptr, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
}

// Test: Retrieve date with all fields populated
TEST_F(WXMPMetaGetPropertyDateTest_2029, FullDateRetrieval_AllFieldsCorrect_2029) {
    XMP_DateTime dateValue;
    memset(&dateValue, 0, sizeof(dateValue));
    dateValue.year = 2000;
    dateValue.month = 1;
    dateValue.day = 1;
    dateValue.hour = 0;
    dateValue.minute = 0;
    dateValue.second = 0;
    dateValue.tzSign = -1;
    dateValue.tzHour = 8;
    dateValue.tzMinute = 0;
    dateValue.nanoSecond = 123456789;

    meta->SetProperty_Date("http://ns.adobe.com/xap/1.0/", "ModifyDate", dateValue, 0);

    WXMP_Result wResult;
    XMP_DateTime retrievedValue;
    XMP_OptionBits options = 0;
    memset(&retrievedValue, 0, sizeof(retrievedValue));

    WXMPMeta_GetProperty_Date_1(GetRef(), "http://ns.adobe.com/xap/1.0/", "ModifyDate", &retrievedValue, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, 0u);
    EXPECT_EQ(retrievedValue.year, 2000);
    EXPECT_EQ(retrievedValue.month, 1);
    EXPECT_EQ(retrievedValue.day, 1);
    EXPECT_EQ(retrievedValue.hour, 0);
    EXPECT_EQ(retrievedValue.minute, 0);
    EXPECT_EQ(retrievedValue.second, 0);
}

// Test: Different schema namespace with non-existent property returns false
TEST_F(WXMPMetaGetPropertyDateTest_2029, DifferentSchema_NonExistent_ReturnsFalse_2029) {
    WXMP_Result wResult;
    XMP_DateTime propValue;
    XMP_OptionBits options = 0;
    memset(&propValue, 0, sizeof(propValue));

    WXMPMeta_GetProperty_Date_1(GetRef(), "http://purl.org/dc/elements/1.1/", "date", &propValue, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, 0u);
}

// Test: WXMP_Result is properly initialized when no error occurs
TEST_F(WXMPMetaGetPropertyDateTest_2029, ResultProperlyInitialized_NoError_2029) {
    WXMP_Result wResult;

    XMP_DateTime dateValue;
    memset(&dateValue, 0, sizeof(dateValue));
    dateValue.year = 2023;
    dateValue.month = 12;
    dateValue.day = 25;

    meta->SetProperty_Date("http://ns.adobe.com/xap/1.0/", "TestDate", dateValue, 0);

    XMP_DateTime retrievedValue;
    XMP_OptionBits options = 0;
    memset(&retrievedValue, 0, sizeof(retrievedValue));

    WXMPMeta_GetProperty_Date_1(GetRef(), "http://ns.adobe.com/xap/1.0/", "TestDate", &retrievedValue, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, 0u);
    EXPECT_EQ(retrievedValue.year, 2023);
    EXPECT_EQ(retrievedValue.month, 12);
    EXPECT_EQ(retrievedValue.day, 25);
}
