#include <gtest/gtest.h>
#include <cstring>

// Include necessary headers for the XMP SDK
#include "XMP_Const.h"
#include "XMP_Environment.h"
#include "client-glue/WXMP_Common.hpp"

// Forward declarations for the wrapper function under test
extern "C" {
void WXMPUtils_AppendProperties_1(XMPMetaRef wSource, XMPMetaRef wDest, XMP_OptionBits options, WXMP_Result* wResult);
}

// We need TXMPMeta to create XMP objects
#define TXMP_STRING_TYPE std::string
#include "TXMPMeta.hpp"
#include "TXMPUtils.hpp"
#include "XMP.incl_cpp"

typedef TXMPMeta<std::string> SXMPMeta;
typedef TXMPUtils<std::string> SXMPUtils;

class WXMPUtilsAppendPropertiesTest_1957 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!SXMPMeta::Initialize()) {
            FAIL() << "Failed to initialize XMP toolkit";
        }
    }

    static void TearDownTestSuite() {
        SXMPMeta::Terminate();
    }

    void SetUp() override {
        memset(&result, 0, sizeof(result));
        result.errMessage = nullptr;
    }

    WXMP_Result result;
};

// Test: Null destination pointer should produce an error
TEST_F(WXMPUtilsAppendPropertiesTest_1957, NullDestThrowsError_1957) {
    SXMPMeta source;
    XMPMetaRef sourceRef = source.GetInternalRef();

    WXMPUtils_AppendProperties_1(sourceRef, 0, 0, &result);

    // Should report an error because dest is null
    EXPECT_NE(result.errMessage, nullptr);
    if (result.errMessage != nullptr) {
        EXPECT_NE(std::string(result.errMessage).find("null"), std::string::npos);
    }
}

// Test: Both source and dest are valid empty XMP objects, no error
TEST_F(WXMPUtilsAppendPropertiesTest_1957, EmptySourceAndDestNoError_1957) {
    SXMPMeta source;
    SXMPMeta dest;
    XMPMetaRef sourceRef = source.GetInternalRef();
    XMPMetaRef destRef = dest.GetInternalRef();

    WXMPUtils_AppendProperties_1(sourceRef, destRef, 0, &result);

    EXPECT_EQ(result.errMessage, nullptr);
}

// Test: Append properties from source with a property to empty dest
TEST_F(WXMPUtilsAppendPropertiesTest_1957, AppendFromSourceWithProperty_1957) {
    SXMPMeta source;
    SXMPMeta dest;

    const char* kNS = "http://ns.example.com/test/";
    source.SetProperty(kNS, "TestProp", "TestValue");

    XMPMetaRef sourceRef = source.GetInternalRef();
    XMPMetaRef destRef = dest.GetInternalRef();

    WXMPUtils_AppendProperties_1(sourceRef, destRef, 0, &result);

    EXPECT_EQ(result.errMessage, nullptr);

    // Verify the property was appended to dest
    std::string value;
    bool found = dest.GetProperty(kNS, "TestProp", &value, nullptr);
    EXPECT_TRUE(found);
    EXPECT_EQ(value, "TestValue");
}

// Test: Append does not overwrite existing property in dest by default
TEST_F(WXMPUtilsAppendPropertiesTest_1957, DoesNotOverwriteExistingByDefault_1957) {
    SXMPMeta source;
    SXMPMeta dest;

    const char* kNS = "http://ns.example.com/test/";
    source.SetProperty(kNS, "TestProp", "SourceValue");
    dest.SetProperty(kNS, "TestProp", "DestValue");

    XMPMetaRef sourceRef = source.GetInternalRef();
    XMPMetaRef destRef = dest.GetInternalRef();

    WXMPUtils_AppendProperties_1(sourceRef, destRef, 0, &result);

    EXPECT_EQ(result.errMessage, nullptr);

    // By default, existing properties should not be replaced
    std::string value;
    bool found = dest.GetProperty(kNS, "TestProp", &value, nullptr);
    EXPECT_TRUE(found);
    EXPECT_EQ(value, "DestValue");
}

// Test: Append with kXMPUtil_DoAllProperties option
TEST_F(WXMPUtilsAppendPropertiesTest_1957, AppendWithDoAllPropertiesOption_1957) {
    SXMPMeta source;
    SXMPMeta dest;

    // Use dc:format which is an "internal" property
    const char* kDCNS = "http://purl.org/dc/elements/1.1/";
    source.SetProperty(kDCNS, "format", "image/jpeg");

    XMPMetaRef sourceRef = source.GetInternalRef();
    XMPMetaRef destRef = dest.GetInternalRef();

    // kXMPUtil_DoAllProperties = 0x0001
    WXMPUtils_AppendProperties_1(sourceRef, destRef, 0x0001UL, &result);

    EXPECT_EQ(result.errMessage, nullptr);

    std::string value;
    bool found = dest.GetProperty(kDCNS, "format", &value, nullptr);
    EXPECT_TRUE(found);
    EXPECT_EQ(value, "image/jpeg");
}

// Test: Append with kXMPUtil_ReplaceOldValues option overwrites existing
TEST_F(WXMPUtilsAppendPropertiesTest_1957, AppendWithReplaceOldValuesOverwrites_1957) {
    SXMPMeta source;
    SXMPMeta dest;

    const char* kNS = "http://ns.example.com/test/";
    source.SetProperty(kNS, "TestProp", "SourceValue");
    dest.SetProperty(kNS, "TestProp", "DestValue");

    XMPMetaRef sourceRef = source.GetInternalRef();
    XMPMetaRef destRef = dest.GetInternalRef();

    // kXMPUtil_ReplaceOldValues = 0x0002
    WXMPUtils_AppendProperties_1(sourceRef, destRef, 0x0002UL, &result);

    EXPECT_EQ(result.errMessage, nullptr);

    std::string value;
    bool found = dest.GetProperty(kNS, "TestProp", &value, nullptr);
    EXPECT_TRUE(found);
    EXPECT_EQ(value, "SourceValue");
}

// Test: Append with zero options from empty source to dest with properties - dest unchanged
TEST_F(WXMPUtilsAppendPropertiesTest_1957, EmptySourceLeavesDestUnchanged_1957) {
    SXMPMeta source;
    SXMPMeta dest;

    const char* kNS = "http://ns.example.com/test/";
    dest.SetProperty(kNS, "ExistingProp", "ExistingValue");

    XMPMetaRef sourceRef = source.GetInternalRef();
    XMPMetaRef destRef = dest.GetInternalRef();

    WXMPUtils_AppendProperties_1(sourceRef, destRef, 0, &result);

    EXPECT_EQ(result.errMessage, nullptr);

    std::string value;
    bool found = dest.GetProperty(kNS, "ExistingProp", &value, nullptr);
    EXPECT_TRUE(found);
    EXPECT_EQ(value, "ExistingValue");
}

// Test: Append multiple properties from source
TEST_F(WXMPUtilsAppendPropertiesTest_1957, AppendMultipleProperties_1957) {
    SXMPMeta source;
    SXMPMeta dest;

    const char* kNS = "http://ns.example.com/test/";
    source.SetProperty(kNS, "Prop1", "Value1");
    source.SetProperty(kNS, "Prop2", "Value2");
    source.SetProperty(kNS, "Prop3", "Value3");

    XMPMetaRef sourceRef = source.GetInternalRef();
    XMPMetaRef destRef = dest.GetInternalRef();

    WXMPUtils_AppendProperties_1(sourceRef, destRef, 0, &result);

    EXPECT_EQ(result.errMessage, nullptr);

    std::string value;
    EXPECT_TRUE(dest.GetProperty(kNS, "Prop1", &value, nullptr));
    EXPECT_EQ(value, "Value1");
    EXPECT_TRUE(dest.GetProperty(kNS, "Prop2", &value, nullptr));
    EXPECT_EQ(value, "Value2");
    EXPECT_TRUE(dest.GetProperty(kNS, "Prop3", &value, nullptr));
    EXPECT_EQ(value, "Value3");
}

// Test: Append with kXMPUtil_DeleteEmptyValues option
TEST_F(WXMPUtilsAppendPropertiesTest_1957, AppendWithDeleteEmptyValues_1957) {
    SXMPMeta source;
    SXMPMeta dest;

    const char* kNS = "http://ns.example.com/test/";
    // Set empty value in source, existing value in dest
    source.SetProperty(kNS, "TestProp", "");
    dest.SetProperty(kNS, "TestProp", "DestValue");

    XMPMetaRef sourceRef = source.GetInternalRef();
    XMPMetaRef destRef = dest.GetInternalRef();

    // kXMPUtil_DeleteEmptyValues = 0x0004, combined with kXMPUtil_ReplaceOldValues = 0x0002
    WXMPUtils_AppendProperties_1(sourceRef, destRef, 0x0004UL | 0x0002UL, &result);

    EXPECT_EQ(result.errMessage, nullptr);

    // The empty value from source should cause the property to be deleted from dest
    std::string value;
    bool found = dest.GetProperty(kNS, "TestProp", &value, nullptr);
    EXPECT_FALSE(found);
}

// Test: WXMP_Result is properly initialized and no error on valid operation
TEST_F(WXMPUtilsAppendPropertiesTest_1957, ResultStructProperlySet_1957) {
    SXMPMeta source;
    SXMPMeta dest;

    XMPMetaRef sourceRef = source.GetInternalRef();
    XMPMetaRef destRef = dest.GetInternalRef();

    WXMP_Result localResult;
    localResult.errMessage = nullptr;
    localResult.int32Result = 0;

    WXMPUtils_AppendProperties_1(sourceRef, destRef, 0, &localResult);

    EXPECT_EQ(localResult.errMessage, nullptr);
}

// Test: Source and dest are the same object (self-append)
TEST_F(WXMPUtilsAppendPropertiesTest_1957, SelfAppendNoError_1957) {
    SXMPMeta meta;

    const char* kNS = "http://ns.example.com/test/";
    meta.SetProperty(kNS, "TestProp", "TestValue");

    XMPMetaRef metaRef = meta.GetInternalRef();

    WXMPUtils_AppendProperties_1(metaRef, metaRef, 0, &result);

    // Should not crash; error behavior is implementation-dependent
    // but the property should still exist
    std::string value;
    bool found = meta.GetProperty(kNS, "TestProp", &value, nullptr);
    EXPECT_TRUE(found);
    EXPECT_EQ(value, "TestValue");
}

// Test: Append properties across different namespaces
TEST_F(WXMPUtilsAppendPropertiesTest_1957, AppendAcrossNamespaces_1957) {
    SXMPMeta source;
    SXMPMeta dest;

    const char* kNS1 = "http://ns.example.com/ns1/";
    const char* kNS2 = "http://ns.example.com/ns2/";
    source.SetProperty(kNS1, "Prop1", "Value1");
    source.SetProperty(kNS2, "Prop2", "Value2");

    XMPMetaRef sourceRef = source.GetInternalRef();
    XMPMetaRef destRef = dest.GetInternalRef();

    WXMPUtils_AppendProperties_1(sourceRef, destRef, 0, &result);

    EXPECT_EQ(result.errMessage, nullptr);

    std::string value;
    EXPECT_TRUE(dest.GetProperty(kNS1, "Prop1", &value, nullptr));
    EXPECT_EQ(value, "Value1");
    EXPECT_TRUE(dest.GetProperty(kNS2, "Prop2", &value, nullptr));
    EXPECT_EQ(value, "Value2");
}
