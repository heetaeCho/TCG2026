#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers
#include "XMPIterator.hpp"
#include "XMPMeta.hpp"
#include "WXMP_Common.hpp"

// Forward declarations for the C-linkage wrapper functions
extern "C" {
void WXMPIterator_DecrementRefCount_1(XMPIteratorRef iterRef);
}

// We need access to XMPCore_Impl for void_wResult
#include "XMPCore_Impl.hpp"

class WXMPIteratorDecrementRefCountTest_1910 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize XMP toolkit if needed
        XMPIterator::Initialize();
    }

    void TearDown() override {
        XMPIterator::Terminate();
    }
};

// Test that decrementing ref count on an iterator with clientRefs > 1 does not delete it
TEST_F(WXMPIteratorDecrementRefCountTest_1910, DecrementRefCountDoesNotDeleteWhenRefsRemain_1910) {
    // Create an XMPMeta object to use with the iterator
    XMPMeta meta;
    
    // Create an iterator - this should set clientRefs to some initial value
    XMPIterator* iter = new XMPIterator(meta, "", "", 0);
    
    // Manually increment clientRefs to simulate multiple references
    // We need at least 2 refs so decrementing once doesn't delete
    iter->clientRefs = 2;
    
    XMPIteratorRef iterRef = (XMPIteratorRef)iter;
    
    // Decrement - should go from 2 to 1, not deleted
    WXMPIterator_DecrementRefCount_1(iterRef);
    
    // The object should still be alive with clientRefs == 1
    EXPECT_EQ(iter->clientRefs, 1);
    
    // Clean up - decrement again to delete
    WXMPIterator_DecrementRefCount_1(iterRef);
}

// Test that decrementing ref count to 0 deletes the iterator (no crash)
TEST_F(WXMPIteratorDecrementRefCountTest_1910, DecrementRefCountDeletesWhenRefsReachZero_1910) {
    XMPMeta meta;
    XMPIterator* iter = new XMPIterator(meta, "", "", 0);
    
    // Set clientRefs to 1 so decrementing deletes it
    iter->clientRefs = 1;
    
    XMPIteratorRef iterRef = (XMPIteratorRef)iter;
    
    // This should decrement to 0 and delete - should not crash
    WXMPIterator_DecrementRefCount_1(iterRef);
    
    // No assertion on the deleted object - just verify no crash
    SUCCEED();
}

// Test multiple decrements from a higher ref count
TEST_F(WXMPIteratorDecrementRefCountTest_1910, MultipleDecrementsFromHighRefCount_1910) {
    XMPMeta meta;
    XMPIterator* iter = new XMPIterator(meta, "", "", 0);
    
    iter->clientRefs = 5;
    
    XMPIteratorRef iterRef = (XMPIteratorRef)iter;
    
    WXMPIterator_DecrementRefCount_1(iterRef);
    EXPECT_EQ(iter->clientRefs, 4);
    
    WXMPIterator_DecrementRefCount_1(iterRef);
    EXPECT_EQ(iter->clientRefs, 3);
    
    WXMPIterator_DecrementRefCount_1(iterRef);
    EXPECT_EQ(iter->clientRefs, 2);
    
    WXMPIterator_DecrementRefCount_1(iterRef);
    EXPECT_EQ(iter->clientRefs, 1);
    
    // Last decrement should delete
    WXMPIterator_DecrementRefCount_1(iterRef);
    SUCCEED();
}

// Test with clientRefs exactly at boundary value of 1
TEST_F(WXMPIteratorDecrementRefCountTest_1910, BoundaryRefCountOne_1910) {
    XMPMeta meta;
    XMPIterator* iter = new XMPIterator(meta, "", "", 0);
    
    iter->clientRefs = 1;
    
    XMPIteratorRef iterRef = (XMPIteratorRef)iter;
    
    // Should delete the object (clientRefs goes to 0 which is <= 0)
    WXMPIterator_DecrementRefCount_1(iterRef);
    
    // If we get here without crash, the test passes
    SUCCEED();
}

// Test with clientRefs at 2 - boundary where object survives
TEST_F(WXMPIteratorDecrementRefCountTest_1910, BoundaryRefCountTwo_1910) {
    XMPMeta meta;
    XMPIterator* iter = new XMPIterator(meta, "", "", 0);
    
    iter->clientRefs = 2;
    
    XMPIteratorRef iterRef = (XMPIteratorRef)iter;
    
    WXMPIterator_DecrementRefCount_1(iterRef);
    
    // Object should survive with clientRefs == 1
    EXPECT_EQ(iter->clientRefs, 1);
    
    // Clean up
    WXMPIterator_DecrementRefCount_1(iterRef);
}

// Test using the global schema iterator constructor
TEST_F(WXMPIteratorDecrementRefCountTest_1910, DecrementRefCountWithGlobalIterator_1910) {
    XMPIterator* iter = new XMPIterator("", "", 0);
    
    iter->clientRefs = 1;
    
    XMPIteratorRef iterRef = (XMPIteratorRef)iter;
    
    // Should cleanly delete
    WXMPIterator_DecrementRefCount_1(iterRef);
    
    SUCCEED();
}
