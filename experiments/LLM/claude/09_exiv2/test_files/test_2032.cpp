#include <gtest/gtest.h>
#include <cstring>

// Include necessary headers for the XMP SDK
#include "XMP_Const.h"
#include "XMP_Environment.h"
#include "client-glue/WXMP_Common.hpp"

// Forward declaration of the function under test
extern "C" void WXMPMeta_SetProperty_Int64_1(
    XMPMetaRef xmpRef,
    XMP_StringPtr schemaNS,
    XMP_StringPtr propName,
    XMP_Int64 propValue,
    XMP_OptionBits options,
    WXMP_Result * wResult);

// We need access to XMPMeta creation
#include "XMPMeta.hpp"
#include "TXMPMeta.hpp"

class WXMPMetaSetPropertyInt64Test_2032 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize XMP SDK
        SXMPMeta::Initialize();
        // Register a namespace for testing
        SXMPMeta::RegisterNamespace("http://ns.test.com/", "test", &registeredPrefix_);
    }

    void TearDown() override {
        SXMPMeta::Terminate();
    }

    XMPMetaRef CreateXMPMeta() {
        XMPMeta* meta = new XMPMeta();
        return WXMPMeta_Ref(meta);
    }

    void DestroyXMPMeta(XMPMetaRef ref) {
        XMPMeta* meta = WtoXMPMeta_Ptr(ref);
        delete meta;
    }

    std::string registeredPrefix_;
};

// Test: Null schema namespace should produce an error
TEST_F(WXMPMetaSetPropertyInt64Test_2032, NullSchemaNS_ReturnsError_2032) {
    XMPMetaRef metaRef = CreateXMPMeta();
    WXMP_Result result;

    WXMPMeta_SetProperty_Int64_1(metaRef, nullptr, "propName", 42, 0, &result);

    EXPECT_NE(result.errMessage, nullptr);
    if (result.errMessage != nullptr) {
        EXPECT_TRUE(std::strstr(result.errMessage, "Empty schema namespace URI") != nullptr ||
                    std::strlen(result.errMessage) > 0);
    }

    DestroyXMPMeta(metaRef);
}

// Test: Empty schema namespace should produce an error
TEST_F(WXMPMetaSetPropertyInt64Test_2032, EmptySchemaNS_ReturnsError_2032) {
    XMPMetaRef metaRef = CreateXMPMeta();
    WXMP_Result result;

    WXMPMeta_SetProperty_Int64_1(metaRef, "", "propName", 42, 0, &result);

    EXPECT_NE(result.errMessage, nullptr);

    DestroyXMPMeta(metaRef);
}

// Test: Null property name should produce an error
TEST_F(WXMPMetaSetPropertyInt64Test_2032, NullPropName_ReturnsError_2032) {
    XMPMetaRef metaRef = CreateXMPMeta();
    WXMP_Result result;

    WXMPMeta_SetProperty_Int64_1(metaRef, "http://ns.test.com/", nullptr, 42, 0, &result);

    EXPECT_NE(result.errMessage, nullptr);

    DestroyXMPMeta(metaRef);
}

// Test: Empty property name should produce an error
TEST_F(WXMPMetaSetPropertyInt64Test_2032, EmptyPropName_ReturnsError_2032) {
    XMPMetaRef metaRef = CreateXMPMeta();
    WXMP_Result result;

    WXMPMeta_SetProperty_Int64_1(metaRef, "http://ns.test.com/", "", 42, 0, &result);

    EXPECT_NE(result.errMessage, nullptr);

    DestroyXMPMeta(metaRef);
}

// Test: Valid parameters should succeed (no error)
TEST_F(WXMPMetaSetPropertyInt64Test_2032, ValidParams_NoError_2032) {
    XMPMetaRef metaRef = CreateXMPMeta();
    WXMP_Result result;

    WXMPMeta_SetProperty_Int64_1(metaRef, "http://ns.test.com/", "testProp", 42, 0, &result);

    EXPECT_EQ(result.errMessage, nullptr);

    DestroyXMPMeta(metaRef);
}

// Test: Setting a positive Int64 value and verifying via GetProperty_Int64
TEST_F(WXMPMetaSetPropertyInt64Test_2032, SetPositiveInt64_CanBeRetrieved_2032) {
    XMPMeta* meta = new XMPMeta();
    XMPMetaRef metaRef = WXMPMeta_Ref(meta);
    WXMP_Result result;

    XMP_Int64 setValue = 1234567890123LL;
    WXMPMeta_SetProperty_Int64_1(metaRef, "http://ns.test.com/", "int64Prop", setValue, 0, &result);
    EXPECT_EQ(result.errMessage, nullptr);

    // Verify the property was set by reading it back
    XMP_Int64 getValue = 0;
    XMP_OptionBits opts = 0;
    bool found = meta->GetProperty_Int64("http://ns.test.com/", "int64Prop", &getValue, &opts);
    EXPECT_TRUE(found);
    EXPECT_EQ(getValue, setValue);

    delete meta;
}

// Test: Setting a negative Int64 value
TEST_F(WXMPMetaSetPropertyInt64Test_2032, SetNegativeInt64_CanBeRetrieved_2032) {
    XMPMeta* meta = new XMPMeta();
    XMPMetaRef metaRef = WXMPMeta_Ref(meta);
    WXMP_Result result;

    XMP_Int64 setValue = -9876543210LL;
    WXMPMeta_SetProperty_Int64_1(metaRef, "http://ns.test.com/", "negProp", setValue, 0, &result);
    EXPECT_EQ(result.errMessage, nullptr);

    XMP_Int64 getValue = 0;
    XMP_OptionBits opts = 0;
    bool found = meta->GetProperty_Int64("http://ns.test.com/", "negProp", &getValue, &opts);
    EXPECT_TRUE(found);
    EXPECT_EQ(getValue, setValue);

    delete meta;
}

// Test: Setting zero value
TEST_F(WXMPMetaSetPropertyInt64Test_2032, SetZeroInt64_CanBeRetrieved_2032) {
    XMPMeta* meta = new XMPMeta();
    XMPMetaRef metaRef = WXMPMeta_Ref(meta);
    WXMP_Result result;

    WXMPMeta_SetProperty_Int64_1(metaRef, "http://ns.test.com/", "zeroProp", 0, 0, &result);
    EXPECT_EQ(result.errMessage, nullptr);

    XMP_Int64 getValue = -1;
    XMP_OptionBits opts = 0;
    bool found = meta->GetProperty_Int64("http://ns.test.com/", "zeroProp", &getValue, &opts);
    EXPECT_TRUE(found);
    EXPECT_EQ(getValue, 0);

    delete meta;
}

// Test: Setting Int64 max value
TEST_F(WXMPMetaSetPropertyInt64Test_2032, SetMaxInt64_CanBeRetrieved_2032) {
    XMPMeta* meta = new XMPMeta();
    XMPMetaRef metaRef = WXMPMeta_Ref(meta);
    WXMP_Result result;

    XMP_Int64 setValue = 0x7FFFFFFFFFFFFFFFLL; // INT64_MAX
    WXMPMeta_SetProperty_Int64_1(metaRef, "http://ns.test.com/", "maxProp", setValue, 0, &result);
    EXPECT_EQ(result.errMessage, nullptr);

    XMP_Int64 getValue = 0;
    XMP_OptionBits opts = 0;
    bool found = meta->GetProperty_Int64("http://ns.test.com/", "maxProp", &getValue, &opts);
    EXPECT_TRUE(found);
    EXPECT_EQ(getValue, setValue);

    delete meta;
}

// Test: Setting Int64 min value
TEST_F(WXMPMetaSetPropertyInt64Test_2032, SetMinInt64_CanBeRetrieved_2032) {
    XMPMeta* meta = new XMPMeta();
    XMPMetaRef metaRef = WXMPMeta_Ref(meta);
    WXMP_Result result;

    XMP_Int64 setValue = static_cast<XMP_Int64>(0x8000000000000000LL); // INT64_MIN
    WXMPMeta_SetProperty_Int64_1(metaRef, "http://ns.test.com/", "minProp", setValue, 0, &result);
    EXPECT_EQ(result.errMessage, nullptr);

    XMP_Int64 getValue = 0;
    XMP_OptionBits opts = 0;
    bool found = meta->GetProperty_Int64("http://ns.test.com/", "minProp", &getValue, &opts);
    EXPECT_TRUE(found);
    EXPECT_EQ(getValue, setValue);

    delete meta;
}

// Test: Overwriting an existing property
TEST_F(WXMPMetaSetPropertyInt64Test_2032, OverwriteExistingProperty_2032) {
    XMPMeta* meta = new XMPMeta();
    XMPMetaRef metaRef = WXMPMeta_Ref(meta);
    WXMP_Result result;

    WXMPMeta_SetProperty_Int64_1(metaRef, "http://ns.test.com/", "overProp", 100, 0, &result);
    EXPECT_EQ(result.errMessage, nullptr);

    WXMPMeta_SetProperty_Int64_1(metaRef, "http://ns.test.com/", "overProp", 200, 0, &result);
    EXPECT_EQ(result.errMessage, nullptr);

    XMP_Int64 getValue = 0;
    XMP_OptionBits opts = 0;
    bool found = meta->GetProperty_Int64("http://ns.test.com/", "overProp", &getValue, &opts);
    EXPECT_TRUE(found);
    EXPECT_EQ(getValue, 200);

    delete meta;
}

// Test: Both schemaNS and propName are null
TEST_F(WXMPMetaSetPropertyInt64Test_2032, BothNullSchemaAndProp_ReturnsError_2032) {
    XMPMetaRef metaRef = CreateXMPMeta();
    WXMP_Result result;

    WXMPMeta_SetProperty_Int64_1(metaRef, nullptr, nullptr, 42, 0, &result);

    // Should fail on the schema check first
    EXPECT_NE(result.errMessage, nullptr);

    DestroyXMPMeta(metaRef);
}

// Test: Both schemaNS and propName are empty strings
TEST_F(WXMPMetaSetPropertyInt64Test_2032, BothEmptySchemaAndProp_ReturnsError_2032) {
    XMPMetaRef metaRef = CreateXMPMeta();
    WXMP_Result result;

    WXMPMeta_SetProperty_Int64_1(metaRef, "", "", 42, 0, &result);

    // Should fail on the schema check first
    EXPECT_NE(result.errMessage, nullptr);

    DestroyXMPMeta(metaRef);
}

// Test: WXMP_Result is properly initialized on success
TEST_F(WXMPMetaSetPropertyInt64Test_2032, ResultInitializedOnSuccess_2032) {
    XMPMetaRef metaRef = CreateXMPMeta();
    WXMP_Result result;
    result.errMessage = reinterpret_cast<XMP_StringPtr>(0xDEADBEEF); // Set to garbage

    WXMPMeta_SetProperty_Int64_1(metaRef, "http://ns.test.com/", "initProp", 55, 0, &result);

    // On success, errMessage should be cleared to nullptr
    EXPECT_EQ(result.errMessage, nullptr);

    DestroyXMPMeta(metaRef);
}

// Test: Setting multiple different properties
TEST_F(WXMPMetaSetPropertyInt64Test_2032, SetMultipleProperties_2032) {
    XMPMeta* meta = new XMPMeta();
    XMPMetaRef metaRef = WXMPMeta_Ref(meta);
    WXMP_Result result;

    WXMPMeta_SetProperty_Int64_1(metaRef, "http://ns.test.com/", "prop1", 111, 0, &result);
    EXPECT_EQ(result.errMessage, nullptr);

    WXMPMeta_SetProperty_Int64_1(metaRef, "http://ns.test.com/", "prop2", 222, 0, &result);
    EXPECT_EQ(result.errMessage, nullptr);

    WXMPMeta_SetProperty_Int64_1(metaRef, "http://ns.test.com/", "prop3", 333, 0, &result);
    EXPECT_EQ(result.errMessage, nullptr);

    XMP_Int64 val = 0;
    XMP_OptionBits opts = 0;

    EXPECT_TRUE(meta->GetProperty_Int64("http://ns.test.com/", "prop1", &val, &opts));
    EXPECT_EQ(val, 111);

    EXPECT_TRUE(meta->GetProperty_Int64("http://ns.test.com/", "prop2", &val, &opts));
    EXPECT_EQ(val, 222);

    EXPECT_TRUE(meta->GetProperty_Int64("http://ns.test.com/", "prop3", &val, &opts));
    EXPECT_EQ(val, 333);

    delete meta;
}
