#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

// Include the header for the class under test
#include "catch2/internal/catch_output_redirect.hpp"

namespace {

// A mock/concrete implementation of OutputRedirect for testing purposes
class MockOutputRedirect : public Catch::OutputRedirect {
public:
    MOCK_METHOD(void, activateImpl, (), (override));
    MOCK_METHOD(void, deactivateImpl, (), (override));
    MOCK_METHOD(std::string, getStdout, (), (override));
    MOCK_METHOD(std::string, getStderr, (), (override));
    MOCK_METHOD(void, clearBuffers, (), (override));
};

// Test fixture
class OutputRedirectTest_544 : public ::testing::Test {
protected:
    MockOutputRedirect mockRedirect;
};

// Test that scopedDeactivate returns a RedirectGuard
TEST_F(OutputRedirectTest_544, ScopedDeactivateReturnsRedirectGuard_544) {
    // scopedDeactivate should create a RedirectGuard with false (deactivation)
    // When the redirect is active, scopedDeactivate should deactivate it
    EXPECT_CALL(mockRedirect, deactivateImpl()).Times(::testing::AnyNumber());
    EXPECT_CALL(mockRedirect, activateImpl()).Times(::testing::AnyNumber());

    // First activate the redirect
    mockRedirect.activate();

    {
        auto guard = Catch::scopedDeactivate(mockRedirect);
        // During the scope, the redirect should be deactivated
    }
    // After the guard goes out of scope, the redirect should be reactivated
}

// Test isActive returns false initially
TEST_F(OutputRedirectTest_544, InitiallyInactive_544) {
    EXPECT_FALSE(mockRedirect.isActive());
}

// Test activate makes isActive return true
TEST_F(OutputRedirectTest_544, ActivateMakesActive_544) {
    EXPECT_CALL(mockRedirect, activateImpl()).Times(1);
    mockRedirect.activate();
    EXPECT_TRUE(mockRedirect.isActive());
}

// Test deactivate makes isActive return false
TEST_F(OutputRedirectTest_544, DeactivateMakesInactive_544) {
    EXPECT_CALL(mockRedirect, activateImpl()).Times(1);
    EXPECT_CALL(mockRedirect, deactivateImpl()).Times(1);

    mockRedirect.activate();
    EXPECT_TRUE(mockRedirect.isActive());

    mockRedirect.deactivate();
    EXPECT_FALSE(mockRedirect.isActive());
}

// Test multiple activate/deactivate cycles
TEST_F(OutputRedirectTest_544, MultipleActivateDeactivateCycles_544) {
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

// Test deactivate when already inactive
TEST_F(OutputRedirectTest_544, DeactivateWhenAlreadyInactive_544) {
    // Should not call deactivateImpl if already inactive
    EXPECT_CALL(mockRedirect, deactivateImpl()).Times(0);
    mockRedirect.deactivate();
    EXPECT_FALSE(mockRedirect.isActive());
}

// Test activate when already active
TEST_F(OutputRedirectTest_544, ActivateWhenAlreadyActive_544) {
    EXPECT_CALL(mockRedirect, activateImpl()).Times(::testing::AtLeast(1));
    EXPECT_CALL(mockRedirect, deactivateImpl()).Times(::testing::AnyNumber());

    mockRedirect.activate();
    EXPECT_TRUE(mockRedirect.isActive());
    // Calling activate again - behavior depends on implementation
    // but isActive should still be true
    mockRedirect.activate();
    EXPECT_TRUE(mockRedirect.isActive());
}

// Test getStdout returns expected value
TEST_F(OutputRedirectTest_544, GetStdoutReturnsValue_544) {
    EXPECT_CALL(mockRedirect, getStdout()).WillOnce(::testing::Return("hello stdout"));
    std::string result = mockRedirect.getStdout();
    EXPECT_EQ(result, "hello stdout");
}

// Test getStderr returns expected value
TEST_F(OutputRedirectTest_544, GetStderrReturnsValue_544) {
    EXPECT_CALL(mockRedirect, getStderr()).WillOnce(::testing::Return("hello stderr"));
    std::string result = mockRedirect.getStderr();
    EXPECT_EQ(result, "hello stderr");
}

// Test clearBuffers can be called
TEST_F(OutputRedirectTest_544, ClearBuffersCanBeCalled_544) {
    EXPECT_CALL(mockRedirect, clearBuffers()).Times(1);
    mockRedirect.clearBuffers();
}

// Test getStdout returns empty when no output
TEST_F(OutputRedirectTest_544, GetStdoutReturnsEmptyWhenNoOutput_544) {
    EXPECT_CALL(mockRedirect, getStdout()).WillOnce(::testing::Return(""));
    std::string result = mockRedirect.getStdout();
    EXPECT_TRUE(result.empty());
}

// Test getStderr returns empty when no output
TEST_F(OutputRedirectTest_544, GetStderrReturnsEmptyWhenNoOutput_544) {
    EXPECT_CALL(mockRedirect, getStderr()).WillOnce(::testing::Return(""));
    std::string result = mockRedirect.getStderr();
    EXPECT_TRUE(result.empty());
}

// Test scopedDeactivate with inactive redirect
TEST_F(OutputRedirectTest_544, ScopedDeactivateWithInactiveRedirect_544) {
    EXPECT_CALL(mockRedirect, deactivateImpl()).Times(::testing::AnyNumber());
    EXPECT_CALL(mockRedirect, activateImpl()).Times(::testing::AnyNumber());

    EXPECT_FALSE(mockRedirect.isActive());
    {
        auto guard = Catch::scopedDeactivate(mockRedirect);
        // Guard created on inactive redirect
    }
}

// Test that scopedDeactivate properly restores state when redirect was active
TEST_F(OutputRedirectTest_544, ScopedDeactivateRestoresActiveState_544) {
    EXPECT_CALL(mockRedirect, activateImpl()).Times(::testing::AtLeast(1));
    EXPECT_CALL(mockRedirect, deactivateImpl()).Times(::testing::AtLeast(1));

    mockRedirect.activate();
    EXPECT_TRUE(mockRedirect.isActive());

    {
        auto guard = Catch::scopedDeactivate(mockRedirect);
        // During scope, redirect should be deactivated
        EXPECT_FALSE(mockRedirect.isActive());
    }
    // After scope, redirect should be reactivated
    EXPECT_TRUE(mockRedirect.isActive());

    // Clean up
    mockRedirect.deactivate();
}

// Test clearBuffers followed by getStdout
TEST_F(OutputRedirectTest_544, ClearBuffersThenGetStdout_544) {
    EXPECT_CALL(mockRedirect, clearBuffers()).Times(1);
    EXPECT_CALL(mockRedirect, getStdout()).WillOnce(::testing::Return(""));

    mockRedirect.clearBuffers();
    std::string result = mockRedirect.getStdout();
    EXPECT_TRUE(result.empty());
}

// Test virtual destructor doesn't crash
TEST_F(OutputRedirectTest_544, DestructorDoesNotCrash_544) {
    auto* redirect = new MockOutputRedirect();
    EXPECT_CALL(*redirect, activateImpl()).Times(0);
    EXPECT_CALL(*redirect, deactivateImpl()).Times(0);
    delete redirect;
}

} // namespace
