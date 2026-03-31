#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers
#include "XMPIterator.hpp"
#include "WXMP_Common.hpp"

// Forward declarations for the C wrapper functions we're testing
extern "C" {
    void WXMPIterator_IncrementRefCount_1(XMPIteratorRef iterRef);
}

// Since we need to test WXMPIterator_IncrementRefCount_1 which operates on XMPIterator objects,
// and the XMPIterator class has complex constructors requiring XMPMeta objects,
// we need to work with what's available through the public interface.

// We'll test the increment ref count function by creating a minimal test fixture.
// Note: XMPIterator has a private default constructor and private copy constructor,
// so we need to use the public constructors which require XMPMeta or string parameters.

#include "XMPMeta.hpp"

// External void_wResult declaration
extern WXMP_Result void_wResult;

class WXMPIteratorTest_1909 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize XMP toolkit if needed
        XMPIterator::Initialize();
    }

    void TearDown() override {
        XMPIterator::Terminate();
    }
};

// Test that IncrementRefCount works on a valid iterator
TEST_F(WXMPIteratorTest_1909, IncrementRefCount_ValidIterator_1909) {
    // Create an XMPMeta object to use with the iterator
    XMPMeta meta;
    
    // Create an iterator - this should set clientRefs to some initial value
    XMPIterator* iter = new XMPIterator(meta, "", "", 0);
    
    // The iterator starts with clientRefs initialized (likely 1 after construction for client use)
    // Incrementing should increase it
    XMPIteratorRef iterRef = (XMPIteratorRef)iter;
    
    // This should not crash or throw - it increments the ref count
    WXMPIterator_IncrementRefCount_1(iterRef);
    
    // We can't directly observe clientRefs, but the function should complete without error
    // Clean up - we need to account for the incremented ref count
    delete iter;
}

// Test that IncrementRefCount can be called multiple times
TEST_F(WXMPIteratorTest_1909, IncrementRefCount_MultipleCalls_1909) {
    XMPMeta meta;
    XMPIterator* iter = new XMPIterator(meta, "", "", 0);
    XMPIteratorRef iterRef = (XMPIteratorRef)iter;
    
    // Call increment multiple times - should not crash
    WXMPIterator_IncrementRefCount_1(iterRef);
    WXMPIterator_IncrementRefCount_1(iterRef);
    WXMPIterator_IncrementRefCount_1(iterRef);
    
    delete iter;
}

// Test with a global/table iterator (second constructor form)
TEST_F(WXMPIteratorTest_1909, IncrementRefCount_GlobalIterator_1909) {
    // Use the constructor that takes string params without XMPMeta
    XMPIterator* iter = new XMPIterator("", "", 0);
    XMPIteratorRef iterRef = (XMPIteratorRef)iter;
    
    WXMPIterator_IncrementRefCount_1(iterRef);
    
    delete iter;
}

// Test that WXMP_Result structure initializes correctly
TEST_F(WXMPIteratorTest_1909, WXMPResult_DefaultConstruction_1909) {
    WXMP_Result result;
    EXPECT_EQ(result.errMessage, nullptr);
}

// Test IncrementRefCount with schema-specific iterator
TEST_F(WXMPIteratorTest_1909, IncrementRefCount_SchemaIterator_1909) {
    XMPMeta meta;
    // Create iterator with specific schema namespace
    XMPIterator* iter = new XMPIterator(meta, "http://ns.adobe.com/xap/1.0/", "", 0);
    XMPIteratorRef iterRef = (XMPIteratorRef)iter;
    
    // Should work without issues
    WXMPIterator_IncrementRefCount_1(iterRef);
    
    delete iter;
}
