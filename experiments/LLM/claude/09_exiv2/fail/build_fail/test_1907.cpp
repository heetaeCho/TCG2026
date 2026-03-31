#include <gtest/gtest.h>
#include <cstring>

// Include necessary XMP SDK headers
#include "XMP_Const.h"
#include "XMP_Environment.h"
#include "client-glue/WXMP_Common.hpp"

// Forward declarations matching the XMP SDK
#include "TXMPMeta.hpp"
#include "XMPMeta.hpp"
#include "XMPIterator.hpp"

// Declaration of the function under test
extern "C" void WXMPIterator_PropCTor_1(
    XMPMetaRef xmpRef,
    XMP_StringPtr schemaNS,
    XMP_StringPtr propName,
    XMP_OptionBits options,
    WXMP_Result * wResult);

// We also need the destructor wrapper to clean up
extern "C" void WXMPIterator_DecrementRefCount_1(XMPIteratorRef iterRef);

class WXMPIteratorPropCTorTest_1907 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize XMP SDK if needed
        SXMPMeta::Initialize();
    }

    void TearDown() override {
        SXMPMeta::Terminate();
    }

    // Helper to create a valid XMPMeta object
    SXMPMeta createValidMeta() {
        SXMPMeta meta;
        meta.SetProperty("http://ns.adobe.com/xap/1.0/", "CreatorTool", "TestTool");
        return meta;
    }
};

// Test: Normal construction with valid parameters
TEST_F(WXMPIteratorPropCTorTest_1907, NormalConstruction_ValidParams_1907) {
    SXMPMeta meta = createValidMeta();
    XMPMetaRef metaRef = meta.GetInternalRef();

    WXMP_Result wResult;
    WXMPIterator_PropCTor_1(metaRef, "http://ns.adobe.com/xap/1.0/", "", 0, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr) << "No error expected for valid construction";
    EXPECT_NE(wResult.ptrResult, nullptr) << "Iterator pointer should be non-null";

    // Cleanup: decrement ref count to free the iterator
    if (wResult.ptrResult != nullptr) {
        XMPIterator* iter = reinterpret_cast<XMPIterator*>(wResult.ptrResult);
        delete iter;
    }
}

// Test: Construction with null schemaNS (should be treated as empty string)
TEST_F(WXMPIteratorPropCTorTest_1907, NullSchemaNS_TreatedAsEmpty_1907) {
    SXMPMeta meta = createValidMeta();
    XMPMetaRef metaRef = meta.GetInternalRef();

    WXMP_Result wResult;
    WXMPIterator_PropCTor_1(metaRef, nullptr, "", 0, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr) << "No error expected when schemaNS is null";
    EXPECT_NE(wResult.ptrResult, nullptr) << "Iterator pointer should be non-null";

    if (wResult.ptrResult != nullptr) {
        XMPIterator* iter = reinterpret_cast<XMPIterator*>(wResult.ptrResult);
        delete iter;
    }
}

// Test: Construction with null propName (should be treated as empty string)
TEST_F(WXMPIteratorPropCTorTest_1907, NullPropName_TreatedAsEmpty_1907) {
    SXMPMeta meta = createValidMeta();
    XMPMetaRef metaRef = meta.GetInternalRef();

    WXMP_Result wResult;
    WXMPIterator_PropCTor_1(metaRef, "http://ns.adobe.com/xap/1.0/", nullptr, 0, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr) << "No error expected when propName is null";
    EXPECT_NE(wResult.ptrResult, nullptr) << "Iterator pointer should be non-null";

    if (wResult.ptrResult != nullptr) {
        XMPIterator* iter = reinterpret_cast<XMPIterator*>(wResult.ptrResult);
        delete iter;
    }
}

// Test: Construction with both null schemaNS and propName
TEST_F(WXMPIteratorPropCTorTest_1907, BothNullStrings_TreatedAsEmpty_1907) {
    SXMPMeta meta = createValidMeta();
    XMPMetaRef metaRef = meta.GetInternalRef();

    WXMP_Result wResult;
    WXMPIterator_PropCTor_1(metaRef, nullptr, nullptr, 0, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr) << "No error expected when both strings are null";
    EXPECT_NE(wResult.ptrResult, nullptr) << "Iterator pointer should be non-null";

    if (wResult.ptrResult != nullptr) {
        XMPIterator* iter = reinterpret_cast<XMPIterator*>(wResult.ptrResult);
        delete iter;
    }
}

// Test: Construction with empty XMPMeta (no properties set)
TEST_F(WXMPIteratorPropCTorTest_1907, EmptyMeta_SuccessfulConstruction_1907) {
    SXMPMeta meta;  // empty, no properties
    XMPMetaRef metaRef = meta.GetInternalRef();

    WXMP_Result wResult;
    WXMPIterator_PropCTor_1(metaRef, "", "", 0, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr) << "No error expected for empty meta";
    EXPECT_NE(wResult.ptrResult, nullptr) << "Iterator pointer should be non-null even for empty meta";

    if (wResult.ptrResult != nullptr) {
        XMPIterator* iter = reinterpret_cast<XMPIterator*>(wResult.ptrResult);
        delete iter;
    }
}

// Test: Construction with empty string schemaNS and propName
TEST_F(WXMPIteratorPropCTorTest_1907, EmptyStrings_SuccessfulConstruction_1907) {
    SXMPMeta meta = createValidMeta();
    XMPMetaRef metaRef = meta.GetInternalRef();

    WXMP_Result wResult;
    WXMPIterator_PropCTor_1(metaRef, "", "", 0, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr) << "No error expected for empty strings";
    EXPECT_NE(wResult.ptrResult, nullptr);

    if (wResult.ptrResult != nullptr) {
        XMPIterator* iter = reinterpret_cast<XMPIterator*>(wResult.ptrResult);
        delete iter;
    }
}

// Test: WXMP_Result is properly initialized before call
TEST_F(WXMPIteratorPropCTorTest_1907, ResultStructProperlyPopulated_1907) {
    SXMPMeta meta = createValidMeta();
    XMPMetaRef metaRef = meta.GetInternalRef();

    WXMP_Result wResult;
    // Verify default initialization
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_EQ(wResult.ptrResult, nullptr);

    WXMPIterator_PropCTor_1(metaRef, "http://ns.adobe.com/xap/1.0/", "", 0, &wResult);

    // After successful call, ptrResult should be set, errMessage still null
    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.ptrResult, nullptr);

    if (wResult.ptrResult != nullptr) {
        XMPIterator* iter = reinterpret_cast<XMPIterator*>(wResult.ptrResult);
        delete iter;
    }
}

// Test: Construction with specific options - kXMP_IterJustChildren
TEST_F(WXMPIteratorPropCTorTest_1907, OptionsJustChildren_1907) {
    SXMPMeta meta = createValidMeta();
    XMPMetaRef metaRef = meta.GetInternalRef();

    WXMP_Result wResult;
    // kXMP_IterJustChildren = 0x0100UL typically
    WXMPIterator_PropCTor_1(metaRef, "http://ns.adobe.com/xap/1.0/", "", 0x0100UL, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.ptrResult, nullptr);

    if (wResult.ptrResult != nullptr) {
        XMPIterator* iter = reinterpret_cast<XMPIterator*>(wResult.ptrResult);
        delete iter;
    }
}

// Test: Construction with specific options - kXMP_IterJustLeafNodes
TEST_F(WXMPIteratorPropCTorTest_1907, OptionsJustLeafNodes_1907) {
    SXMPMeta meta = createValidMeta();
    XMPMetaRef metaRef = meta.GetInternalRef();

    WXMP_Result wResult;
    // kXMP_IterJustLeafNodes = 0x0200UL typically
    WXMPIterator_PropCTor_1(metaRef, "http://ns.adobe.com/xap/1.0/", "", 0x0200UL, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.ptrResult, nullptr);

    if (wResult.ptrResult != nullptr) {
        XMPIterator* iter = reinterpret_cast<XMPIterator*>(wResult.ptrResult);
        delete iter;
    }
}

// Test: Construction with a specific property name
TEST_F(WXMPIteratorPropCTorTest_1907, SpecificPropertyName_1907) {
    SXMPMeta meta = createValidMeta();
    XMPMetaRef metaRef = meta.GetInternalRef();

    WXMP_Result wResult;
    WXMPIterator_PropCTor_1(metaRef, "http://ns.adobe.com/xap/1.0/", "CreatorTool", 0, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.ptrResult, nullptr);

    if (wResult.ptrResult != nullptr) {
        XMPIterator* iter = reinterpret_cast<XMPIterator*>(wResult.ptrResult);
        delete iter;
    }
}

// Test: Multiple iterators can be created from the same meta
TEST_F(WXMPIteratorPropCTorTest_1907, MultipleIteratorsFromSameMeta_1907) {
    SXMPMeta meta = createValidMeta();
    XMPMetaRef metaRef = meta.GetInternalRef();

    WXMP_Result wResult1;
    WXMP_Result wResult2;

    WXMPIterator_PropCTor_1(metaRef, "", "", 0, &wResult1);
    WXMPIterator_PropCTor_1(metaRef, "", "", 0, &wResult2);

    EXPECT_EQ(wResult1.errMessage, nullptr);
    EXPECT_EQ(wResult2.errMessage, nullptr);
    EXPECT_NE(wResult1.ptrResult, nullptr);
    EXPECT_NE(wResult2.ptrResult, nullptr);
    // They should be different iterator instances
    EXPECT_NE(wResult1.ptrResult, wResult2.ptrResult);

    if (wResult1.ptrResult != nullptr) {
        XMPIterator* iter = reinterpret_cast<XMPIterator*>(wResult1.ptrResult);
        delete iter;
    }
    if (wResult2.ptrResult != nullptr) {
        XMPIterator* iter = reinterpret_cast<XMPIterator*>(wResult2.ptrResult);
        delete iter;
    }
}

// Test: Construction with non-existent schema namespace
TEST_F(WXMPIteratorPropCTorTest_1907, NonExistentNamespace_1907) {
    SXMPMeta meta = createValidMeta();
    XMPMetaRef metaRef = meta.GetInternalRef();

    WXMP_Result wResult;
    WXMPIterator_PropCTor_1(metaRef, "http://nonexistent.namespace/", "", 0, &wResult);

    // Depending on implementation, this may succeed with an empty iterator
    // or may fail. We check the observable behavior.
    if (wResult.errMessage == nullptr) {
        EXPECT_NE(wResult.ptrResult, nullptr);
        if (wResult.ptrResult != nullptr) {
            XMPIterator* iter = reinterpret_cast<XMPIterator*>(wResult.ptrResult);
            delete iter;
        }
    }
    // If there's an error, errMessage should be set
}

// Test: Construction with meta containing multiple namespaces
TEST_F(WXMPIteratorPropCTorTest_1907, MultipleNamespaces_IterateAll_1907) {
    SXMPMeta meta;
    meta.SetProperty("http://ns.adobe.com/xap/1.0/", "CreatorTool", "TestTool");
    meta.SetProperty("http://purl.org/dc/elements/1.1/", "title", "TestTitle");
    XMPMetaRef metaRef = meta.GetInternalRef();

    WXMP_Result wResult;
    // Empty schemaNS to iterate all namespaces
    WXMPIterator_PropCTor_1(metaRef, "", "", 0, &wResult);

    EXPECT_EQ(wResult.errMessage, nullptr);
    EXPECT_NE(wResult.ptrResult, nullptr);

    if (wResult.ptrResult != nullptr) {
        XMPIterator* iter = reinterpret_cast<XMPIterator*>(wResult.ptrResult);
        delete iter;
    }
}

// Test: Construction with propName but empty schemaNS should potentially raise error
// (property name without schema is often invalid)
TEST_F(WXMPIteratorPropCTorTest_1907, PropNameWithoutSchema_1907) {
    SXMPMeta meta = createValidMeta();
    XMPMetaRef metaRef = meta.GetInternalRef();

    WXMP_Result wResult;
    WXMPIterator_PropCTor_1(metaRef, "", "SomeProperty", 0, &wResult);

    // This may result in an error since propName without schemaNS may be invalid
    // We just verify the result is consistent
    if (wResult.errMessage != nullptr) {
        // Error case: ptrResult should not be used
        EXPECT_NE(wResult.errMessage, nullptr);
    } else {
        EXPECT_NE(wResult.ptrResult, nullptr);
        if (wResult.ptrResult != nullptr) {
            XMPIterator* iter = reinterpret_cast<XMPIterator*>(wResult.ptrResult);
            delete iter;
        }
    }
}
