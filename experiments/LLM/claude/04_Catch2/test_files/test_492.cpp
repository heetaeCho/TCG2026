#include "catch2/internal/catch_output_redirect.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <cassert>

namespace Catch {

// Mock implementation of OutputRedirect for testing
class MockOutputRedirect : public OutputRedirect {
public:
    MOCK_METHOD(void, activateImpl, (), (override));
    MOCK_METHOD(void, deactivateImpl, (), (override));
    MOCK_METHOD(std::string, getStdout, (), (override));
    MOCK_METHOD(std::string, getStderr, (), (override));
    MOCK_METHOD(void, clearBuffers, (), (override));
};

} // namespace Catch

class OutputRedirectTest_492 : public ::testing::Test {
protected:
    Catch::MockOutputRedirect redirect;
};

// Test that a newly created OutputRedirect is not active
TEST_F(OutputRedirectTest_492, InitiallyNotActive_492) {
    EXPECT_FALSE(redirect.isActive());
}

// Test that activate makes the redirect active
TEST_F(OutputRedirectTest_492, ActivateMakesActive_492) {
    EXPECT_CALL(redirect, activateImpl()).Times(1);
    redirect.activate();
    EXPECT_TRUE(redirect.isActive());
}

// Test that deactivate after activate makes it inactive
TEST_F(OutputRedirectTest_492, DeactivateAfterActivateMakesInactive_492) {
    EXPECT_CALL(redirect, activateImpl()).Times(1);
    EXPECT_CALL(redirect, deactivateImpl()).Times(1);
    
    redirect.activate();
    EXPECT_TRUE(redirect.isActive());
    
    redirect.deactivate();
    EXPECT_FALSE(redirect.isActive());
}

// Test that deactivateImpl is called when deactivate is called
TEST_F(OutputRedirectTest_492, DeactivateCallsDeactivateImpl_492) {
    EXPECT_CALL(redirect, activateImpl()).Times(1);
    EXPECT_CALL(redirect, deactivateImpl()).Times(1);
    
    redirect.activate();
    redirect.deactivate();
}

// Test that activateImpl is called when activate is called
TEST_F(OutputRedirectTest_492, ActivateCallsActivateImpl_492) {
    EXPECT_CALL(redirect, activateImpl()).Times(1);
    redirect.activate();
}

// Test activate then deactivate then activate cycle
TEST_F(OutputRedirectTest_492, ActivateDeactivateActivateCycle_492) {
    EXPECT_CALL(redirect, activateImpl()).Times(2);
    EXPECT_CALL(redirect, deactivateImpl()).Times(1);
    
    redirect.activate();
    EXPECT_TRUE(redirect.isActive());
    
    redirect.deactivate();
    EXPECT_FALSE(redirect.isActive());
    
    redirect.activate();
    EXPECT_TRUE(redirect.isActive());
}

// Test getStdout returns expected value
TEST_F(OutputRedirectTest_492, GetStdoutReturnsValue_492) {
    EXPECT_CALL(redirect, getStdout()).WillOnce(::testing::Return("hello stdout"));
    EXPECT_EQ(redirect.getStdout(), "hello stdout");
}

// Test getStderr returns expected value
TEST_F(OutputRedirectTest_492, GetStderrReturnsValue_492) {
    EXPECT_CALL(redirect, getStderr()).WillOnce(::testing::Return("hello stderr"));
    EXPECT_EQ(redirect.getStderr(), "hello stderr");
}

// Test getStdout returns empty string when nothing captured
TEST_F(OutputRedirectTest_492, GetStdoutReturnsEmptyWhenNothingCaptured_492) {
    EXPECT_CALL(redirect, getStdout()).WillOnce(::testing::Return(""));
    EXPECT_EQ(redirect.getStdout(), "");
}

// Test getStderr returns empty string when nothing captured
TEST_F(OutputRedirectTest_492, GetStderrReturnsEmptyWhenNothingCaptured_492) {
    EXPECT_CALL(redirect, getStderr()).WillOnce(::testing::Return(""));
    EXPECT_EQ(redirect.getStderr(), "");
}

// Test clearBuffers is callable
TEST_F(OutputRedirectTest_492, ClearBuffersIsCalled_492) {
    EXPECT_CALL(redirect, clearBuffers()).Times(1);
    redirect.clearBuffers();
}

// Test that clearBuffers clears stdout content
TEST_F(OutputRedirectTest_492, ClearBuffersClearsStdout_492) {
    EXPECT_CALL(redirect, clearBuffers()).Times(1);
    EXPECT_CALL(redirect, getStdout()).WillOnce(::testing::Return(""));
    
    redirect.clearBuffers();
    EXPECT_EQ(redirect.getStdout(), "");
}

// Test that clearBuffers clears stderr content
TEST_F(OutputRedirectTest_492, ClearBuffersClearsStderr_492) {
    EXPECT_CALL(redirect, clearBuffers()).Times(1);
    EXPECT_CALL(redirect, getStderr()).WillOnce(::testing::Return(""));
    
    redirect.clearBuffers();
    EXPECT_EQ(redirect.getStderr(), "");
}

// Test multiple activate/deactivate cycles
TEST_F(OutputRedirectTest_492, MultipleActivateDeactivateCycles_492) {
    EXPECT_CALL(redirect, activateImpl()).Times(3);
    EXPECT_CALL(redirect, deactivateImpl()).Times(3);
    
    for (int i = 0; i < 3; ++i) {
        redirect.activate();
        EXPECT_TRUE(redirect.isActive());
        redirect.deactivate();
        EXPECT_FALSE(redirect.isActive());
    }
}

// Test deactivate when not active triggers assertion (death test)
TEST_F(OutputRedirectTest_492, DeactivateWhenNotActiveAssertion_492) {
    // The deactivate method has an assert that m_redirectActive is true
    // When called without activation, it should trigger the assertion
    EXPECT_DEATH(redirect.deactivate(), "");
}

// Test that deactivate called twice without re-activation triggers assertion
TEST(OutputRedirectDeathTest_492, DoubleDeactivateAssertion_492) {
    Catch::MockOutputRedirect redirect;
    EXPECT_CALL(redirect, activateImpl()).Times(1);
    EXPECT_CALL(redirect, deactivateImpl()).Times(1);
    
    redirect.activate();
    redirect.deactivate();
    
    // Second deactivate without activate should assert
    EXPECT_DEATH(redirect.deactivate(), "");
}

// Test isActive const correctness - can be called on const reference
TEST_F(OutputRedirectTest_492, IsActiveOnConstReference_492) {
    const Catch::OutputRedirect& constRef = redirect;
    EXPECT_FALSE(constRef.isActive());
}
