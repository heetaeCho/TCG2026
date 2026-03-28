#include <gtest/gtest.h>
#include <cstring>

// Include necessary XMP SDK headers
#include "XMP_Const.h"
#include "XMP_Environment.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPMeta.hpp"

// Declaration of the function under test
extern "C" void WXMPMeta_DoesPropertyExist_1(
    XMPMetaRef xmpRef,
    XMP_StringPtr schemaNS,
    XMP_StringPtr propName,
    WXMP_Result * wResult);

// Helper to convert XMPMeta* to XMPMetaRef
static XMPMetaRef MetaToRef(XMPMeta* meta) {
    return reinterpret_cast<XMPMetaRef>(meta);
}

class WXMPMetaDoesPropertyExistTest_2019 : public ::testing::Test {
protected:
    void SetUp() override {
        XMPMeta::Initialize();
        meta = new XMPMeta();
    }

    void TearDown() override {
        delete meta;
        XMPMeta::Terminate();
    }

    XMPMeta* meta;
};

// Test: Null schemaNS should produce an error
TEST_F(WXMPMetaDoesPropertyExistTest_2019, NullSchemaNSReturnsError_2019) {
    WXMP_Result result;
    WXMPMeta_DoesPropertyExist_1(MetaToRef(meta), nullptr, "propName", &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Empty schemaNS string should produce an error
TEST_F(WXMPMetaDoesPropertyExistTest_2019, EmptySchemaNSReturnsError_2019) {
    WXMP_Result result;
    WXMPMeta_DoesPropertyExist_1(MetaToRef(meta), "", "propName", &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Null propName should produce an error
TEST_F(WXMPMetaDoesPropertyExistTest_2019, NullPropNameReturnsError_2019) {
    WXMP_Result result;
    WXMPMeta_DoesPropertyExist_1(MetaToRef(meta), "http://ns.example.com/", nullptr, &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Empty propName string should produce an error
TEST_F(WXMPMetaDoesPropertyExistTest_2019, EmptyPropNameReturnsError_2019) {
    WXMP_Result result;
    WXMPMeta_DoesPropertyExist_1(MetaToRef(meta), "http://ns.example.com/", "", &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Property that does not exist should return false (0)
TEST_F(WXMPMetaDoesPropertyExistTest_2019, NonExistentPropertyReturnsFalse_2019) {
    WXMP_Result result;
    // Register namespace first
    XMPMeta::RegisterNamespace("http://ns.example.com/test/", "test");
    WXMPMeta_DoesPropertyExist_1(MetaToRef(meta), "http://ns.example.com/test/", "NonExistent", &result);
    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_EQ(result.int32Result, static_cast<XMP_Uns32>(0));
}

// Test: Property that exists should return true (non-zero)
TEST_F(WXMPMetaDoesPropertyExistTest_2019, ExistingPropertyReturnsTrue_2019) {
    WXMP_Result result;
    const char* ns = "http://ns.example.com/test2/";
    XMPMeta::RegisterNamespace(ns, "test2");
    meta->SetProperty(ns, "MyProp", "SomeValue", 0);
    WXMPMeta_DoesPropertyExist_1(MetaToRef(meta), ns, "MyProp", &result);
    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_NE(result.int32Result, static_cast<XMP_Uns32>(0));
}

// Test: Both schemaNS and propName are null
TEST_F(WXMPMetaDoesPropertyExistTest_2019, BothNullReturnsError_2019) {
    WXMP_Result result;
    WXMPMeta_DoesPropertyExist_1(MetaToRef(meta), nullptr, nullptr, &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: Both schemaNS and propName are empty strings
TEST_F(WXMPMetaDoesPropertyExistTest_2019, BothEmptyReturnsError_2019) {
    WXMP_Result result;
    WXMPMeta_DoesPropertyExist_1(MetaToRef(meta), "", "", &result);
    EXPECT_NE(result.errMessage, nullptr);
}

// Test: After setting and deleting a property, it should not exist
TEST_F(WXMPMetaDoesPropertyExistTest_2019, DeletedPropertyReturnsFalse_2019) {
    WXMP_Result result;
    const char* ns = "http://ns.example.com/test3/";
    XMPMeta::RegisterNamespace(ns, "test3");
    meta->SetProperty(ns, "TempProp", "TempValue", 0);
    meta->DeleteProperty(ns, "TempProp");
    WXMPMeta_DoesPropertyExist_1(MetaToRef(meta), ns, "TempProp", &result);
    EXPECT_EQ(result.errMessage, nullptr);
    EXPECT_EQ(result.int32Result, static_cast<XMP_Uns32>(0));
}

// Test: WXMP_Result is properly initialized (no error) on success
TEST_F(WXMPMetaDoesPropertyExistTest_2019, ResultHasNoErrorOnSuccess_2019) {
    WXMP_Result result;
    const char* ns = "http://ns.example.com/test4/";
    XMPMeta::RegisterNamespace(ns, "test4");
    WXMPMeta_DoesPropertyExist_1(MetaToRef(meta), ns, "SomeProp", &result);
    EXPECT_EQ(result.errMessage, nullptr);
}

// Test: Error message contains meaningful text for empty schema
TEST_F(WXMPMetaDoesPropertyExistTest_2019, EmptySchemaErrorMessageContainsSchema_2019) {
    WXMP_Result result;
    WXMPMeta_DoesPropertyExist_1(MetaToRef(meta), "", "propName", &result);
    ASSERT_NE(result.errMessage, nullptr);
    // The error message should mention schema
    EXPECT_TRUE(std::strstr(result.errMessage, "schema") != nullptr ||
                std::strstr(result.errMessage, "Schema") != nullptr ||
                std::strlen(result.errMessage) > 0);
}

// Test: Error message contains meaningful text for empty property name
TEST_F(WXMPMetaDoesPropertyExistTest_2019, EmptyPropNameErrorMessageContainsProp_2019) {
    WXMP_Result result;
    WXMPMeta_DoesPropertyExist_1(MetaToRef(meta), "http://ns.example.com/", "", &result);
    ASSERT_NE(result.errMessage, nullptr);
    EXPECT_TRUE(std::strstr(result.errMessage, "property") != nullptr ||
                std::strstr(result.errMessage, "Property") != nullptr ||
                std::strlen(result.errMessage) > 0);
}

// Test: Multiple properties - check one exists and another doesn't
TEST_F(WXMPMetaDoesPropertyExistTest_2019, MultiplePropertiesCheckIndependence_2019) {
    const char* ns = "http://ns.example.com/test5/";
    XMPMeta::RegisterNamespace(ns, "test5");
    meta->SetProperty(ns, "PropA", "ValueA", 0);
    meta->SetProperty(ns, "PropB", "ValueB", 0);

    WXMP_Result resultA;
    WXMPMeta_DoesPropertyExist_1(MetaToRef(meta), ns, "PropA", &resultA);
    EXPECT_EQ(resultA.errMessage, nullptr);
    EXPECT_NE(resultA.int32Result, static_cast<XMP_Uns32>(0));

    WXMP_Result resultB;
    WXMPMeta_DoesPropertyExist_1(MetaToRef(meta), ns, "PropB", &resultB);
    EXPECT_EQ(resultB.errMessage, nullptr);
    EXPECT_NE(resultB.int32Result, static_cast<XMP_Uns32>(0));

    WXMP_Result resultC;
    WXMPMeta_DoesPropertyExist_1(MetaToRef(meta), ns, "PropC", &resultC);
    EXPECT_EQ(resultC.errMessage, nullptr);
    EXPECT_EQ(resultC.int32Result, static_cast<XMP_Uns32>(0));
}
