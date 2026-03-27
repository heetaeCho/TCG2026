#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <cstdio>

// Mocks for external collaborators
class MockErrorCallback {
public:
    MOCK_METHOD(void, operator(), (ErrorCategory category, Goffset pos, const char* msg), ());
};

// Include the headers for the function and dependencies
#include "./TestProjects/poppler/poppler/Error.cc"
#include "./TestProjects/poppler/goo/GooString.h"
#include "./TestProjects/poppler/poppler/GlobalParams.h"

// Test fixture for Error function
class ErrorTest_1895 : public ::testing::Test {
protected:
    MockErrorCallback mockErrorCbk;

    void SetUp() override {
        // Set up the global params to mimic the real environment (if needed)
        globalParams = std::make_unique<GlobalParams>("testDir");
    }

    void TearDown() override {
        // Reset global variables or mocks if needed
        globalParams.reset();
    }
};

// Test normal operation of error function
TEST_F(ErrorTest_1895, ErrorReportsCorrectly_1895) {
    // Setup: Inject mock callback
    errorCbk = &mockErrorCbk;

    // Expect the error callback to be called with expected parameters
    EXPECT_CALL(mockErrorCbk, operator()(ErrorCategory::SyntaxError, 100, testing::StrEq("Syntax error occurred")));

    // Call the error function
    error(ErrorCategory::SyntaxError, 100, "Syntax error occurred");

    // Verify callback is invoked correctly
    testing::Mock::VerifyAndClearExpectations(&mockErrorCbk);
}

// Test boundary conditions (testing empty and large messages)
TEST_F(ErrorTest_1895, ErrorHandlesEmptyMessage_1895) {
    // Setup: Inject mock callback
    errorCbk = &mockErrorCbk;

    // Expect the error callback to be called with an empty message
    EXPECT_CALL(mockErrorCbk, operator()(ErrorCategory::CommandLineError, 0, testing::StrEq("")));

    // Call the error function with empty message
    error(ErrorCategory::CommandLineError, 0, "");

    // Verify callback is invoked correctly
    testing::Mock::VerifyAndClearExpectations(&mockErrorCbk);
}

TEST_F(ErrorTest_1895, ErrorHandlesSpecialCharactersInMessage_1895) {
    // Setup: Inject mock callback
    errorCbk = &mockErrorCbk;

    // Expect the error callback to handle special characters properly
    EXPECT_CALL(mockErrorCbk, operator()(ErrorCategory::IOError, 200, testing::StrEq("<20>Test message with special chars <ff>")));

    // Call the error function with special characters
    error(ErrorCategory::IOError, 200, "Test message with special chars \x20\xFF");

    // Verify callback is invoked correctly
    testing::Mock::VerifyAndClearExpectations(&mockErrorCbk);
}

// Test exceptional/error cases (checking behavior when errorCbk is null)
TEST_F(ErrorTest_1895, ErrorHandlesNullErrorCallback_1895) {
    // Setup: Ensure errorCbk is null
    errorCbk = nullptr;

    // Expect no callback to be invoked, but stderr should still print the error
    EXPECT_CALL(mockErrorCbk, operator()(testing::_ , testing::_ , testing::_)).Times(0);

    // Capture stderr output
    testing::internal::CaptureStderr();

    // Call the error function with null callback
    error(ErrorCategory::PermissionError, -1, "Permission denied");

    // Verify stderr contains the correct message
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_NE(output.find("Permission Error: Permission denied"), std::string::npos);
}

// Test boundary conditions with large input (checking size limits of error message)
TEST_F(ErrorTest_1895, ErrorHandlesLargeMessage_1895) {
    // Setup: Inject mock callback
    errorCbk = &mockErrorCbk;

    // Prepare a very large message
    std::string largeMessage(10000, 'A');  // 10,000 'A' characters

    // Expect the error callback to be called with the large message
    EXPECT_CALL(mockErrorCbk, operator()(ErrorCategory::InternalError, 999, testing::StrEq(largeMessage.c_str())));

    // Call the error function with the large message
    error(ErrorCategory::InternalError, 999, largeMessage.c_str());

    // Verify callback is invoked correctly
    testing::Mock::VerifyAndClearExpectations(&mockErrorCbk);
}