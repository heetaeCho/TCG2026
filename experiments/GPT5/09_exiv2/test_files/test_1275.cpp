#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "client-glue/TXMPMeta.incl_cpp"

// Mock class for XMP_TextOutputProc
class MockXMP_TextOutputProc {
public:
    MOCK_METHOD(XMP_Status, operator(), (void* clientRefCon, XMP_StringPtr buffer, XMP_StringLen bufferSize), ());
};

// Test fixture
class TextOutputProcWrapperTest : public ::testing::Test {
protected:
    // Member variables for the mock and the class under test
    MockXMP_TextOutputProc mockClientProc;
    TOPW_Info* info;

    // SetUp method to create TOPW_Info object before each test
    void SetUp() override {
        info = new TOPW_Info(mockClientProc, nullptr); // Initialize with mock and nullptr
    }

    // TearDown method to delete the object after each test
    void TearDown() override {
        delete info;
    }
};

// Test case for normal operation
TEST_F(TextOutputProcWrapperTest, NormalOperation_1275) {
    // Setup: Expecting the mock method to be called once with any arguments
    XMP_StringPtr buffer = "Test buffer";
    XMP_StringLen bufferSize = 12;
    EXPECT_CALL(mockClientProc, operator()(nullptr, buffer, bufferSize)).WillOnce(testing::Return(0)); // Expect success (0)

    // Test: Call the wrapper function
    XMP_Status result = TextOutputProcWrapper(info, buffer, bufferSize);

    // Verify: Ensure that the return value is the expected result (i.e., 0)
    EXPECT_EQ(result, 0);
}

// Test case for handling exceptions in the callback
TEST_F(TextOutputProcWrapperTest, ExceptionInCallback_1276) {
    // Setup: Simulate exception in the callback by making the mock method throw
    XMP_StringPtr buffer = "Test buffer";
    XMP_StringLen bufferSize = 12;
    EXPECT_CALL(mockClientProc, operator()(nullptr, buffer, bufferSize)).WillOnce(testing::Throw(std::runtime_error("Test exception")));

    // Test: Call the wrapper function
    XMP_Status result = TextOutputProcWrapper(info, buffer, bufferSize);

    // Verify: Ensure that the return value indicates an error (i.e., -1)
    EXPECT_EQ(result, -1);
}

// Test case for handling a NULL refCon
TEST_F(TextOutputProcWrapperTest, NullRefCon_1277) {
    // Setup: Use nullptr for refCon in the wrapper
    info->clientRefCon = nullptr;
    XMP_StringPtr buffer = "Test buffer";
    XMP_StringLen bufferSize = 12;
    EXPECT_CALL(mockClientProc, operator()(nullptr, buffer, bufferSize)).WillOnce(testing::Return(0)); // Expect success

    // Test: Call the wrapper function with null refCon
    XMP_Status result = TextOutputProcWrapper(info, buffer, bufferSize);

    // Verify: Ensure that the result is still success
    EXPECT_EQ(result, 0);
}

// Test case for boundary condition with maximum buffer size
TEST_F(TextOutputProcWrapperTest, MaxBufferSize_1278) {
    // Setup: Simulate calling with a large buffer size
    XMP_StringPtr buffer = "A very large buffer for testing boundary condition";
    XMP_StringLen bufferSize = 256; // Assuming 256 is the boundary for this example
    EXPECT_CALL(mockClientProc, operator()(nullptr, buffer, bufferSize)).WillOnce(testing::Return(0)); // Expect success

    // Test: Call the wrapper function with maximum buffer size
    XMP_Status result = TextOutputProcWrapper(info, buffer, bufferSize);

    // Verify: Ensure the result is success
    EXPECT_EQ(result, 0);
}