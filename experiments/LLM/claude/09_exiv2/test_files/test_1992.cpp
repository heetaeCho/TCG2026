#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers for the XMP SDK
#define TXMP_STRING_TYPE std::string
#include "XMP.hpp"
#include "XMPMeta.hpp"

// We need access to the WXMPMeta functions
extern "C" {
void WXMPMeta_DecrementRefCount_1(XMPMetaRef xmpRef);
}

class WXMPMetaDecrementRefCountTest_1992 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize XMP SDK if needed
        SXMPMeta::Initialize();
    }

    void TearDown() override {
        SXMPMeta::Terminate();
    }
};

// Test that decrementing ref count on an object with clientRefs > 1 does not delete it
TEST_F(WXMPMetaDecrementRefCountTest_1992, DecrementRefCountDoesNotDeleteWhenRefsAboveOne_1992) {
    XMPMeta* meta = new XMPMeta();
    // Set clientRefs to 2 so that after decrement it becomes 1 (not deleted)
    meta->clientRefs = 2;
    
    WXMPMeta_DecrementRefCount_1((XMPMetaRef)meta);
    
    // After decrement, clientRefs should be 1, object should still be alive
    EXPECT_EQ(meta->clientRefs, 1);
    
    // Clean up - manually delete since it wasn't auto-deleted
    delete meta;
}

// Test that decrementing ref count from 1 deletes the object (no crash)
TEST_F(WXMPMetaDecrementRefCountTest_1992, DecrementRefCountDeletesWhenRefsReachZero_1992) {
    XMPMeta* meta = new XMPMeta();
    meta->clientRefs = 1;
    
    // This should decrement to 0 and delete the object
    // We just verify it doesn't crash
    WXMPMeta_DecrementRefCount_1((XMPMetaRef)meta);
    
    // Object is deleted, we cannot access it anymore - just verify no crash
    SUCCEED();
}

// Test decrementing from a higher ref count
TEST_F(WXMPMetaDecrementRefCountTest_1992, DecrementRefCountFromHighValue_1992) {
    XMPMeta* meta = new XMPMeta();
    meta->clientRefs = 100;
    
    WXMPMeta_DecrementRefCount_1((XMPMetaRef)meta);
    
    EXPECT_EQ(meta->clientRefs, 99);
    
    delete meta;
}

// Test multiple decrements until deletion
TEST_F(WXMPMetaDecrementRefCountTest_1992, MultipleDecrementsUntilDeletion_1992) {
    XMPMeta* meta = new XMPMeta();
    meta->clientRefs = 3;
    
    WXMPMeta_DecrementRefCount_1((XMPMetaRef)meta);
    EXPECT_EQ(meta->clientRefs, 2);
    
    WXMPMeta_DecrementRefCount_1((XMPMetaRef)meta);
    EXPECT_EQ(meta->clientRefs, 1);
    
    // This final decrement should delete the object
    WXMPMeta_DecrementRefCount_1((XMPMetaRef)meta);
    // Object is now deleted, no further access
    SUCCEED();
}

// Test decrement from exactly 2 leaves object alive with refcount 1
TEST_F(WXMPMetaDecrementRefCountTest_1992, DecrementFromTwoLeavesRefCountAtOne_1992) {
    XMPMeta* meta = new XMPMeta();
    meta->clientRefs = 2;
    
    WXMPMeta_DecrementRefCount_1((XMPMetaRef)meta);
    
    EXPECT_EQ(meta->clientRefs, 1);
    
    // Object should still be usable
    // Try to get object name to verify it's alive
    XMP_StringPtr namePtr = nullptr;
    XMP_StringLen nameLen = 0;
    meta->GetObjectName(&namePtr, &nameLen);
    
    delete meta;
}

// Test that a freshly created XMPMeta with default clientRefs can be decremented
TEST_F(WXMPMetaDecrementRefCountTest_1992, DecrementFreshlyCreatedMeta_1992) {
    XMPMeta* meta = new XMPMeta();
    // Default clientRefs should be 0 based on constructor, need to set it to at least 1
    // to satisfy the assertion in the function
    meta->clientRefs = 1;
    
    // Should delete the object
    WXMPMeta_DecrementRefCount_1((XMPMetaRef)meta);
    SUCCEED();
}

// Test decrementing with a large ref count value
TEST_F(WXMPMetaDecrementRefCountTest_1992, DecrementLargeRefCount_1992) {
    XMPMeta* meta = new XMPMeta();
    meta->clientRefs = 10000;
    
    WXMPMeta_DecrementRefCount_1((XMPMetaRef)meta);
    
    EXPECT_EQ(meta->clientRefs, 9999);
    
    delete meta;
}
