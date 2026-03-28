#include <gtest/gtest.h>
#include <cstring>

// Include necessary XMP SDK headers
#define TXMP_STRING_TYPE std::string
#include "XMP.incl_cpp"
#include "XMP.hpp"
#include "client-glue/WXMP_Common.hpp"

// Declaration of the function under test
extern void WXMPMeta_GetQualifier_1(
    XMPMetaRef xmpRef,
    XMP_StringPtr schemaNS,
    XMP_StringPtr propName,
    XMP_StringPtr qualNS,
    XMP_StringPtr qualName,
    XMP_StringPtr * qualValue,
    XMP_StringLen * valueSize,
    XMP_OptionBits * options,
    WXMP_Result * wResult
);

class WXMPMetaGetQualifierTest_2009 : public ::testing::Test {
protected:
    void SetUp() override {
        SXMPMeta::Initialize();
        meta = new XMPMeta();
        xmpRef = (XMPMetaRef)meta;
    }

    void TearDown() override {
        delete meta;
        SXMPMeta::Terminate();
    }

    XMPMeta* meta;
    XMPMetaRef xmpRef;
};

// Test: Empty schema namespace URI (null pointer)
TEST_F(WXMPMetaGetQualifierTest_2009, EmptySchemaNS_Null_2009) {
    WXMP_Result wResult;
    XMP_StringPtr qualValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetQualifier_1(xmpRef, nullptr, "propName", "http://qualNS/", "qualName",
                             &qualValue, &valueSize, &options, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty schema namespace URI (empty string)
TEST_F(WXMPMetaGetQualifierTest_2009, EmptySchemaNS_EmptyString_2009) {
    WXMP_Result wResult;
    XMP_StringPtr qualValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetQualifier_1(xmpRef, "", "propName", "http://qualNS/", "qualName",
                             &qualValue, &valueSize, &options, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty property name (null pointer)
TEST_F(WXMPMetaGetQualifierTest_2009, EmptyPropName_Null_2009) {
    WXMP_Result wResult;
    XMP_StringPtr qualValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetQualifier_1(xmpRef, "http://ns.adobe.com/xap/1.0/", nullptr,
                             "http://qualNS/", "qualName",
                             &qualValue, &valueSize, &options, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty property name (empty string)
TEST_F(WXMPMetaGetQualifierTest_2009, EmptyPropName_EmptyString_2009) {
    WXMP_Result wResult;
    XMP_StringPtr qualValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetQualifier_1(xmpRef, "http://ns.adobe.com/xap/1.0/", "",
                             "http://qualNS/", "qualName",
                             &qualValue, &valueSize, &options, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty qualifier namespace URI (null pointer)
TEST_F(WXMPMetaGetQualifierTest_2009, EmptyQualNS_Null_2009) {
    WXMP_Result wResult;
    XMP_StringPtr qualValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetQualifier_1(xmpRef, "http://ns.adobe.com/xap/1.0/", "propName",
                             nullptr, "qualName",
                             &qualValue, &valueSize, &options, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty qualifier namespace URI (empty string)
TEST_F(WXMPMetaGetQualifierTest_2009, EmptyQualNS_EmptyString_2009) {
    WXMP_Result wResult;
    XMP_StringPtr qualValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetQualifier_1(xmpRef, "http://ns.adobe.com/xap/1.0/", "propName",
                             "", "qualName",
                             &qualValue, &valueSize, &options, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty qualifier name (null pointer)
TEST_F(WXMPMetaGetQualifierTest_2009, EmptyQualName_Null_2009) {
    WXMP_Result wResult;
    XMP_StringPtr qualValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetQualifier_1(xmpRef, "http://ns.adobe.com/xap/1.0/", "propName",
                             "http://qualNS/", nullptr,
                             &qualValue, &valueSize, &options, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Empty qualifier name (empty string)
TEST_F(WXMPMetaGetQualifierTest_2009, EmptyQualName_EmptyString_2009) {
    WXMP_Result wResult;
    XMP_StringPtr qualValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetQualifier_1(xmpRef, "http://ns.adobe.com/xap/1.0/", "propName",
                             "http://qualNS/", "",
                             &qualValue, &valueSize, &options, &wResult);

    EXPECT_NE(wResult.errMessage, nullptr);
}

// Test: Qualifier not found returns false (int32Result == 0)
TEST_F(WXMPMetaGetQualifierTest_2009, QualifierNotFound_2009) {
    WXMP_Result wResult;
    XMP_StringPtr qualValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    // Set a property but no qualifier
    meta->SetProperty("http://ns.adobe.com/xap/1.0/", "Creator", "TestValue", 0);

    WXMPMeta_GetQualifier_1(xmpRef, "http://ns.adobe.com/xap/1.0/", "Creator",
                             "http://ns.adobe.com/xap/1.0/", "NonExistentQual",
                             &qualValue, &valueSize, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, 0u);
}

// Test: Qualifier found returns true (int32Result != 0)
TEST_F(WXMPMetaGetQualifierTest_2009, QualifierFound_2009) {
    WXMP_Result wResult;
    XMP_StringPtr qualValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    const char* qualNS = "http://ns.adobe.com/xap/1.0/";

    meta->SetProperty(schemaNS, "Creator", "TestValue", 0);
    meta->SetQualifier(schemaNS, "Creator", qualNS, "myQual", "qualVal", 0);

    WXMPMeta_GetQualifier_1(xmpRef, schemaNS, "Creator",
                             qualNS, "myQual",
                             &qualValue, &valueSize, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, 0u);
    EXPECT_NE(qualValue, nullptr);
    EXPECT_STREQ(qualValue, "qualVal");
    EXPECT_EQ(valueSize, static_cast<XMP_StringLen>(strlen("qualVal")));
}

// Test: Null qualValue pointer is handled (uses voidStringPtr internally)
TEST_F(WXMPMetaGetQualifierTest_2009, NullQualValuePtr_2009) {
    WXMP_Result wResult;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    meta->SetProperty(schemaNS, "Creator", "TestValue", 0);

    WXMPMeta_GetQualifier_1(xmpRef, schemaNS, "Creator",
                             "http://ns.adobe.com/xap/1.0/", "NonExistent",
                             nullptr, &valueSize, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, 0u);
}

// Test: Null valueSize pointer is handled
TEST_F(WXMPMetaGetQualifierTest_2009, NullValueSizePtr_2009) {
    WXMP_Result wResult;
    XMP_StringPtr qualValue = nullptr;
    XMP_OptionBits options = 0;

    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    meta->SetProperty(schemaNS, "Creator", "TestValue", 0);

    WXMPMeta_GetQualifier_1(xmpRef, schemaNS, "Creator",
                             "http://ns.adobe.com/xap/1.0/", "NonExistent",
                             &qualValue, nullptr, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, 0u);
}

// Test: Null options pointer is handled
TEST_F(WXMPMetaGetQualifierTest_2009, NullOptionsPtr_2009) {
    WXMP_Result wResult;
    XMP_StringPtr qualValue = nullptr;
    XMP_StringLen valueSize = 0;

    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    meta->SetProperty(schemaNS, "Creator", "TestValue", 0);

    WXMPMeta_GetQualifier_1(xmpRef, schemaNS, "Creator",
                             "http://ns.adobe.com/xap/1.0/", "NonExistent",
                             &qualValue, &valueSize, nullptr, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, 0u);
}

// Test: All optional output pointers null
TEST_F(WXMPMetaGetQualifierTest_2009, AllOptionalOutputsNull_2009) {
    WXMP_Result wResult;

    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    const char* qualNS = "http://ns.adobe.com/xap/1.0/";

    meta->SetProperty(schemaNS, "Creator", "TestValue", 0);
    meta->SetQualifier(schemaNS, "Creator", qualNS, "myQual", "qualVal", 0);

    WXMPMeta_GetQualifier_1(xmpRef, schemaNS, "Creator",
                             qualNS, "myQual",
                             nullptr, nullptr, nullptr, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, 0u);
}

// Test: Property does not exist, qualifier query returns not found
TEST_F(WXMPMetaGetQualifierTest_2009, PropertyDoesNotExist_2009) {
    WXMP_Result wResult;
    XMP_StringPtr qualValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    WXMPMeta_GetQualifier_1(xmpRef, "http://ns.adobe.com/xap/1.0/", "NonExistentProp",
                             "http://ns.adobe.com/xap/1.0/", "qualName",
                             &qualValue, &valueSize, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.int32Result, 0u);
}

// Test: Verify qualifier value with specific content
TEST_F(WXMPMetaGetQualifierTest_2009, QualifierValueContent_2009) {
    WXMP_Result wResult;
    XMP_StringPtr qualValue = nullptr;
    XMP_StringLen valueSize = 0;
    XMP_OptionBits options = 0;

    const char* schemaNS = "http://ns.adobe.com/xap/1.0/";
    const char* qualNS = "http://ns.adobe.com/xap/1.0/";
    const char* expectedQualValue = "MyQualifierValue123";

    meta->SetProperty(schemaNS, "TestProp", "SomeValue", 0);
    meta->SetQualifier(schemaNS, "TestProp", qualNS, "testQual", expectedQualValue, 0);

    WXMPMeta_GetQualifier_1(xmpRef, schemaNS, "TestProp",
                             qualNS, "testQual",
                             &qualValue, &valueSize, &options, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.int32Result, 0u);
    EXPECT_STREQ(qualValue, expectedQualValue);
    EXPECT_EQ(valueSize, static_cast<XMP_StringLen>(strlen(expectedQualValue)));
}
