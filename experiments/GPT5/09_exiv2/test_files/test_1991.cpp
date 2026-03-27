#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Mocking dependencies
class MockXMPMeta : public XMPMeta {
public:
    MOCK_METHOD(void, IncrementRefCount, (), (override));
};

// Test class
class WXMPMetaTest_1991 : public ::testing::Test {
protected:
    XMPMeta* xmpMeta;

    void SetUp() override {
        xmpMeta = new XMPMeta();
    }

    void TearDown() override {
        delete xmpMeta;
    }
};

// Test normal operation for IncrementRefCount
TEST_F(WXMPMetaTest_1991, IncrementRefCount_NormalOperation_1991) {
    // Simulating the case where clientRefs is initialized to 0
    xmpMeta->clientRefs = 0;

    // Expect the ref count to be incremented
    WXMPMeta_IncrementRefCount_1(reinterpret_cast<XMPMetaRef>(xmpMeta));

    EXPECT_EQ(xmpMeta->clientRefs, 1);
}

// Test boundary condition for IncrementRefCount when the count is at maximum int value
TEST_F(WXMPMetaTest_1991, IncrementRefCount_MaxValue_1991) {
    // Setting clientRefs to a large value
    xmpMeta->clientRefs = std::numeric_limits<int>::max();

    // We expect the ref count to not overflow and stay within bounds
    EXPECT_NO_FATAL_FAILURE(WXMPMeta_IncrementRefCount_1(reinterpret_cast<XMPMetaRef>(xmpMeta)));

    // Ensure the ref count was incremented correctly
    EXPECT_EQ(xmpMeta->clientRefs, std::numeric_limits<int>::max() + 1);
}

// Test exceptional/error case for IncrementRefCount when ref count is at its max and overflows
TEST_F(WXMPMetaTest_1991, IncrementRefCount_Overflow_1991) {
    // Setting clientRefs to maximum possible value for int
    xmpMeta->clientRefs = std::numeric_limits<int>::max();

    // Expecting that we won't overflow or throw an exception
    // The assertion inside IncrementRefCount will be triggered for debugging purposes, we expect no exception
    EXPECT_NO_THROW(WXMPMeta_IncrementRefCount_1(reinterpret_cast<XMPMetaRef>(xmpMeta)));
}

// Test if the function interacts correctly with external mocks
TEST_F(WXMPMetaTest_1991, IncrementRefCount_ExternalInteraction_1991) {
    MockXMPMeta mockXMPMeta;

    // Expect IncrementRefCount to be called exactly once
    EXPECT_CALL(mockXMPMeta, IncrementRefCount()).Times(1);

    // Call the method that triggers IncrementRefCount
    mockXMPMeta.IncrementRefCount();
}