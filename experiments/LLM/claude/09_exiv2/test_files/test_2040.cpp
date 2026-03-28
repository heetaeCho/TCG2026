#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers for XMP SDK
#define TXMP_STRING_TYPE std::string
#include "XMP.incl_cpp"
#include "XMP.hpp"
#include "WXMPMeta.hpp"
#include "XMPMeta.hpp"

#include <string>
#include <cstring>

class WXMPMetaUnlockObjectTest_2040 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize the XMP toolkit
        SXMPMeta::Initialize();
    }

    void TearDown() override {
        SXMPMeta::Terminate();
    }
};

// Test that UnlockObject can be called with zero options on a valid XMPMeta object
TEST_F(WXMPMetaUnlockObjectTest_2040, UnlockObjectWithZeroOptions_2040) {
    XMPMeta meta;
    XMPMetaRef xmpRef = WXMPMeta_GetXMPMetaRef(&meta);
    
    // Should not throw or crash when called with 0 options
    EXPECT_NO_THROW(WXMPMeta_UnlockObject_1(xmpRef, 0));
}

// Test that UnlockObject can be called with non-zero options
TEST_F(WXMPMetaUnlockObjectTest_2040, UnlockObjectWithNonZeroOptions_2040) {
    XMPMeta meta;
    XMPMetaRef xmpRef = WXMPMeta_GetXMPMetaRef(&meta);
    
    // Should not throw or crash with arbitrary option bits
    EXPECT_NO_THROW(WXMPMeta_UnlockObject_1(xmpRef, 0x0001));
}

// Test that UnlockObject can be called multiple times without issues
TEST_F(WXMPMetaUnlockObjectTest_2040, UnlockObjectCalledMultipleTimes_2040) {
    XMPMeta meta;
    XMPMetaRef xmpRef = WXMPMeta_GetXMPMetaRef(&meta);
    
    EXPECT_NO_THROW(WXMPMeta_UnlockObject_1(xmpRef, 0));
    EXPECT_NO_THROW(WXMPMeta_UnlockObject_1(xmpRef, 0));
    EXPECT_NO_THROW(WXMPMeta_UnlockObject_1(xmpRef, 0));
}

// Test that UnlockObject works on a meta object that has properties set
TEST_F(WXMPMetaUnlockObjectTest_2040, UnlockObjectOnMetaWithProperties_2040) {
    XMPMeta meta;
    
    // Set some property to make the meta object non-empty
    meta.SetProperty("http://ns.adobe.com/xap/1.0/", "CreatorTool", "TestTool", 0);
    
    XMPMetaRef xmpRef = WXMPMeta_GetXMPMetaRef(&meta);
    
    EXPECT_NO_THROW(WXMPMeta_UnlockObject_1(xmpRef, 0));
    
    // Verify the object is still functional after unlock
    XMP_StringPtr value = nullptr;
    XMP_StringLen valueLen = 0;
    XMP_OptionBits opts = 0;
    bool found = meta.GetProperty("http://ns.adobe.com/xap/1.0/", "CreatorTool", &value, &valueLen, &opts);
    EXPECT_TRUE(found);
}

// Test that UnlockObject with various option bit patterns does not crash
TEST_F(WXMPMetaUnlockObjectTest_2040, UnlockObjectWithVariousOptionBits_2040) {
    XMPMeta meta;
    XMPMetaRef xmpRef = WXMPMeta_GetXMPMetaRef(&meta);
    
    EXPECT_NO_THROW(WXMPMeta_UnlockObject_1(xmpRef, 0x00000000));
    EXPECT_NO_THROW(WXMPMeta_UnlockObject_1(xmpRef, 0x00000001));
    EXPECT_NO_THROW(WXMPMeta_UnlockObject_1(xmpRef, 0x0000FFFF));
    EXPECT_NO_THROW(WXMPMeta_UnlockObject_1(xmpRef, 0xFFFFFFFF));
}

// Test UnlockObject on a freshly created empty meta object
TEST_F(WXMPMetaUnlockObjectTest_2040, UnlockObjectOnEmptyMeta_2040) {
    XMPMeta meta;
    XMPMetaRef xmpRef = WXMPMeta_GetXMPMetaRef(&meta);
    
    // An empty meta object should still allow UnlockObject
    EXPECT_NO_THROW(WXMPMeta_UnlockObject_1(xmpRef, 0));
}

// Test UnlockObject preserves const-correctness (the function is const on XMPMeta)
TEST_F(WXMPMetaUnlockObjectTest_2040, UnlockObjectIsConstOperation_2040) {
    XMPMeta meta;
    meta.SetProperty("http://ns.adobe.com/xap/1.0/", "Rating", "5", 0);
    
    XMPMetaRef xmpRef = WXMPMeta_GetXMPMetaRef(&meta);
    
    // Call unlock
    WXMPMeta_UnlockObject_1(xmpRef, 0);
    
    // Verify state is unchanged after unlock (const operation should not modify)
    XMP_StringPtr value = nullptr;
    XMP_StringLen valueLen = 0;
    XMP_OptionBits opts = 0;
    bool found = meta.GetProperty("http://ns.adobe.com/xap/1.0/", "Rating", &value, &valueLen, &opts);
    EXPECT_TRUE(found);
    EXPECT_STREQ(value, "5");
}

// Test that UnlockObject on a parsed XMP meta object works correctly
TEST_F(WXMPMetaUnlockObjectTest_2040, UnlockObjectOnParsedMeta_2040) {
    XMPMeta meta;
    
    const char* xmpPacket = 
        "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
        "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
        "<rdf:Description rdf:about=\"\" "
        "xmlns:dc=\"http://purl.org/dc/elements/1.1/\">"
        "<dc:title><rdf:Alt><rdf:li xml:lang=\"x-default\">Test</rdf:li></rdf:Alt></dc:title>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>";
    
    meta.ParseFromBuffer(xmpPacket, static_cast<XMP_StringLen>(strlen(xmpPacket)), 0);
    
    XMPMetaRef xmpRef = WXMPMeta_GetXMPMetaRef(&meta);
    EXPECT_NO_THROW(WXMPMeta_UnlockObject_1(xmpRef, 0));
}
