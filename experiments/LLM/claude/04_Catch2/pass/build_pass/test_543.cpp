#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

// Include the header under test
#include "catch2/internal/catch_output_redirect.hpp"

namespace {

// Concrete mock implementation of OutputRedirect for testing
class MockOutputRedirect : public Catch::OutputRedirect {
public:
    MOCK_METHOD(void, activateImpl, (), (override));
    MOCK_METHOD(void, deactivateImpl, (), (override));
    MOCK_METHOD(std::string, getStdout, (), (override));
    MOCK_METHOD(std::string, getStderr, (), (override));
    MOCK_METHOD(void, clearBuffers, (), (override));
};

// Test fixture
class OutputRedirectTest_543 : public ::testing::Test {
protected:
    MockOutputRedirect mockRedirect;
};

// Test that a newly created OutputRedirect is not active
TEST_F(OutputRedirectTest_543, InitiallyNotActive_543) {
    EXPECT_FALSE(mockRedirect.isActive());
}

// Test that activate makes isActive return true
TEST_F(OutputRedirectTest_543, ActivateMakesActive_543) {
    EXPECT_CALL(mockRedirect, activateImpl()).Times(1);
    mockRedirect.activate();
    EXPECT_TRUE(mockRedirect.isActive());
}

// Test that deactivate makes isActive return false after activation
TEST_F(OutputRedirectTest_543, DeactivateMakesInactive_543) {
    EXPECT_CALL(mockRedirect, activateImpl()).Times(1);
    EXPECT_CALL(mockRedirect, deactivateImpl()).Times(1);
    mockRedirect.activate();
    EXPECT_TRUE(mockRedirect.isActive());
    mockRedirect.deactivate();
    EXPECT_FALSE(mockRedirect.isActive());
}

// Test that activate followed by deactivate cycle works multiple times
TEST_F(OutputRedirectTest_543, MultipleActivateDeactivateCycles_543) {
    EXPECT_CALL(mockRedirect, activateImpl()).Times(2);
    EXPECT_CALL(mockRedirect, deactivateImpl()).Times(2);

    mockRedirect.activate();
    EXPECT_TRUE(mockRedirect.isActive());
    mockRedirect.deactivate();
    EXPECT_FALSE(mockRedirect.isActive());

    mockRedirect.activate();
    EXPECT_TRUE(mockRedirect.isActive());
    mockRedirect.deactivate();
    EXPECT_FALSE(mockRedirect.isActive());
}

// Test that deactivate on an already inactive redirect is safe
TEST_F(OutputRedirectTest_543, DeactivateWhenNotActive_543) {
    // Should not call deactivateImpl if not active
    EXPECT_CALL(mockRedirect, deactivateImpl()).Times(0);
    EXPECT_FALSE(mockRedirect.isActive());
    mockRedirect.deactivate();
    EXPECT_FALSE(mockRedirect.isActive());
}

// Test getStdout returns expected string
TEST_F(OutputRedirectTest_543, GetStdoutReturnsOutput_543) {
    EXPECT_CALL(mockRedirect, getStdout()).WillOnce(::testing::Return("hello stdout"));
    std::string result = mockRedirect.getStdout();
    EXPECT_EQ(result, "hello stdout");
}

// Test getStderr returns expected string
TEST_F(OutputRedirectTest_543, GetStderrReturnsOutput_543) {
    EXPECT_CALL(mockRedirect, getStderr()).WillOnce(::testing::Return("hello stderr"));
    std::string result = mockRedirect.getStderr();
    EXPECT_EQ(result, "hello stderr");
}

// Test getStdout returns empty when nothing captured
TEST_F(OutputRedirectTest_543, GetStdoutReturnsEmptyByDefault_543) {
    EXPECT_CALL(mockRedirect, getStdout()).WillOnce(::testing::Return(""));
    std::string result = mockRedirect.getStdout();
    EXPECT_TRUE(result.empty());
}

// Test getStderr returns empty when nothing captured
TEST_F(OutputRedirectTest_543, GetStderrReturnsEmptyByDefault_543) {
    EXPECT_CALL(mockRedirect, getStderr()).WillOnce(::testing::Return(""));
    std::string result = mockRedirect.getStderr();
    EXPECT_TRUE(result.empty());
}

// Test clearBuffers can be called
TEST_F(OutputRedirectTest_543, ClearBuffersCallable_543) {
    EXPECT_CALL(mockRedirect, clearBuffers()).Times(1);
    mockRedirect.clearBuffers();
}

// Test clearBuffers clears previously captured output
TEST_F(OutputRedirectTest_543, ClearBuffersClearsOutput_543) {
    ::testing::InSequence seq;
    EXPECT_CALL(mockRedirect, getStdout()).WillOnce(::testing::Return("some output"));
    EXPECT_CALL(mockRedirect, clearBuffers()).Times(1);
    EXPECT_CALL(mockRedirect, getStdout()).WillOnce(::testing::Return(""));

    std::string before = mockRedirect.getStdout();
    EXPECT_EQ(before, "some output");

    mockRedirect.clearBuffers();

    std::string after = mockRedirect.getStdout();
    EXPECT_TRUE(after.empty());
}

// Test scopedActivate creates a guard that activates the redirect
TEST_F(OutputRedirectTest_543, ScopedActivateActivatesRedirect_543) {
    EXPECT_CALL(mockRedirect, activateImpl()).Times(1);
    EXPECT_CALL(mockRedirect, deactivateImpl()).Times(1);

    {
        auto guard = Catch::scopedActivate(mockRedirect);
        EXPECT_TRUE(mockRedirect.isActive());
    }
    // After guard goes out of scope, redirect should be deactivated
    EXPECT_FALSE(mockRedirect.isActive());
}

// Test that scopedActivate guard deactivates on destruction
TEST_F(OutputRedirectTest_543, RedirectGuardDeactivatesOnDestruction_543) {
    EXPECT_CALL(mockRedirect, activateImpl()).Times(1);
    EXPECT_CALL(mockRedirect, deactivateImpl()).Times(1);

    {
        auto guard = Catch::scopedActivate(mockRedirect);
        EXPECT_TRUE(mockRedirect.isActive());
    }
    EXPECT_FALSE(mockRedirect.isActive());
}

// Test activateImpl is called exactly once per activate call
TEST_F(OutputRedirectTest_543, ActivateImplCalledOnActivate_543) {
    EXPECT_CALL(mockRedirect, activateImpl()).Times(1);
    mockRedirect.activate();
}

// Test deactivateImpl is called exactly once per deactivate call when active
TEST_F(OutputRedirectTest_543, DeactivateImplCalledOnDeactivate_543) {
    EXPECT_CALL(mockRedirect, activateImpl()).Times(1);
    EXPECT_CALL(mockRedirect, deactivateImpl()).Times(1);
    mockRedirect.activate();
    mockRedirect.deactivate();
}

} // anonymous namespace
