#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "WXMPMeta.hpp"

// Mocking the external dependencies if needed
class MockWXMPMeta : public XMPMeta {
public:
    MOCK_METHOD(void, DecrementRefCount, (XMPMetaRef xmpRef), (override));
};

// Test suite for WXMPMeta_DecrementRefCount_1
TEST_F(WXMPMetaDecrementRefCountTest_1992, TestDecrementRefCount_Normal_1992) {
    // Create a mock object of WXMPMeta
    MockWXMPMeta mockXMPMeta;
    XMPMetaRef xmpRef = reinterpret_cast<XMPMetaRef>(&mockXMPMeta);

    // Set an initial reference count
    mockXMPMeta.clientRefs = 1;

    // Set expectations (if any)
    EXPECT_CALL(mockXMPMeta, DecrementRefCount(xmpRef)).Times(1);

    // Call the function under test
    WXMPMeta_DecrementRefCount_1(xmpRef);

    // Validate the results (assert the side-effects as needed)
    EXPECT_EQ(mockXMPMeta.clientRefs, 0); // Ensuring that the reference count is decremented
}

TEST_F(WXMPMetaDecrementRefCountTest_1992, TestDecrementRefCount_Boundary_1992) {
    // Test for boundary conditions

    // Create a mock object of WXMPMeta
    MockWXMPMeta mockXMPMeta;
    XMPMetaRef xmpRef = reinterpret_cast<XMPMetaRef>(&mockXMPMeta);

    // Test when clientRefs is 1
    mockXMPMeta.clientRefs = 1;
    EXPECT_CALL(mockXMPMeta, DecrementRefCount(xmpRef)).Times(1);

    // Call the function under test
    WXMPMeta_DecrementRefCount_1(xmpRef);

    // Validate the results (assert the side-effects as needed)
    EXPECT_EQ(mockXMPMeta.clientRefs, 0);

    // Test when clientRefs is 0, should not decrement further (boundary check)
    mockXMPMeta.clientRefs = 0;
    EXPECT_CALL(mockXMPMeta, DecrementRefCount(xmpRef)).Times(0); // Should not call DecrementRefCount again

    // Call the function under test again with 0 refs
    WXMPMeta_DecrementRefCount_1(xmpRef);

    // Assert that the clientRefs remains 0
    EXPECT_EQ(mockXMPMeta.clientRefs, 0);
}

TEST_F(WXMPMetaDecrementRefCountTest_1992, TestDecrementRefCount_ExceptionalCase_1992) {
    // Exceptional or error case handling

    // Create a mock object of WXMPMeta
    MockWXMPMeta mockXMPMeta;
    XMPMetaRef xmpRef = reinterpret_cast<XMPMetaRef>(&mockXMPMeta);

    // Simulate an invalid scenario where clientRefs is already 0, and test the behavior
    mockXMPMeta.clientRefs = 0;

    // Expect the function to handle the exceptional case without decrementing further
    EXPECT_CALL(mockXMPMeta, DecrementRefCount(xmpRef)).Times(0);

    // Call the function under test
    WXMPMeta_DecrementRefCount_1(xmpRef);

    // Validate that clientRefs remains at 0, as no decrement should happen
    EXPECT_EQ(mockXMPMeta.clientRefs, 0);
}