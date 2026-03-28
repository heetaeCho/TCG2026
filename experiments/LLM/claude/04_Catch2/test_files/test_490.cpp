#include "catch2/internal/catch_output_redirect.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

// Since OutputRedirect has virtual methods and we cannot instantiate it directly
// (it has pure virtual methods), we create a concrete test subclass.
class TestableOutputRedirect : public Catch::OutputRedirect {
public:
    MOCK_METHOD(void, activateImpl, (), (override));
    MOCK_METHOD(void, deactivateImpl, (), (override));
    MOCK_METHOD(std::string, getStdout, (), (override));
    MOCK_METHOD(std::string, getStderr, (), (override));
    MOCK_METHOD(void, clearBuffers, (), (override));
};

class OutputRedirectTest_490 : public ::testing::Test {
protected:
    TestableOutputRedirect redirect;
};

TEST_F(OutputRedirectTest_490, InitiallyNotActive_490) {
    EXPECT_FALSE(redirect.isActive());
}

TEST_F(OutputRedirectTest_490, ActivateMakesActive_490) {
    EXPECT_CALL(redirect, activateImpl()).Times(1);
    redirect.activate();
    EXPECT_TRUE(redirect.isActive());
}

TEST_F(OutputRedirectTest_490, DeactivateMakesInactive_490) {
    EXPECT_CALL(redirect, activateImpl()).Times(1);
    EXPECT_CALL(redirect, deactivateImpl()).Times(1);
    redirect.activate();
    EXPECT_TRUE(redirect.isActive());
    redirect.deactivate();
    EXPECT_FALSE(redirect.isActive());
}

TEST_F(OutputRedirectTest_490, ActivateDeactivateMultipleCycles_490) {
    EXPECT_CALL(redirect, activateImpl()).Times(3);
    EXPECT_CALL(redirect, deactivateImpl()).Times(3);

    for (int i = 0; i < 3; ++i) {
        EXPECT_FALSE(redirect.isActive());
        redirect.activate();
        EXPECT_TRUE(redirect.isActive());
        redirect.deactivate();
        EXPECT_FALSE(redirect.isActive());
    }
}

TEST_F(OutputRedirectTest_490, IsActiveReturnsFalseInitially_490) {
    // Verify const method works on fresh instance
    const Catch::OutputRedirect& constRef = redirect;
    EXPECT_FALSE(constRef.isActive());
}

TEST_F(OutputRedirectTest_490, IsActiveReturnsTrueAfterActivate_490) {
    EXPECT_CALL(redirect, activateImpl()).Times(1);
    redirect.activate();
    const Catch::OutputRedirect& constRef = redirect;
    EXPECT_TRUE(constRef.isActive());
}

TEST_F(OutputRedirectTest_490, GetStdoutReturnsExpectedString_490) {
    EXPECT_CALL(redirect, getStdout()).WillOnce(::testing::Return("hello stdout"));
    std::string result = redirect.getStdout();
    EXPECT_EQ(result, "hello stdout");
}

TEST_F(OutputRedirectTest_490, GetStderrReturnsExpectedString_490) {
    EXPECT_CALL(redirect, getStderr()).WillOnce(::testing::Return("hello stderr"));
    std::string result = redirect.getStderr();
    EXPECT_EQ(result, "hello stderr");
}

TEST_F(OutputRedirectTest_490, GetStdoutReturnsEmptyByDefault_490) {
    EXPECT_CALL(redirect, getStdout()).WillOnce(::testing::Return(""));
    std::string result = redirect.getStdout();
    EXPECT_TRUE(result.empty());
}

TEST_F(OutputRedirectTest_490, GetStderrReturnsEmptyByDefault_490) {
    EXPECT_CALL(redirect, getStderr()).WillOnce(::testing::Return(""));
    std::string result = redirect.getStderr();
    EXPECT_TRUE(result.empty());
}

TEST_F(OutputRedirectTest_490, ClearBuffersCanBeCalled_490) {
    EXPECT_CALL(redirect, clearBuffers()).Times(1);
    redirect.clearBuffers();
}

TEST_F(OutputRedirectTest_490, ClearBuffersMultipleTimes_490) {
    EXPECT_CALL(redirect, clearBuffers()).Times(3);
    redirect.clearBuffers();
    redirect.clearBuffers();
    redirect.clearBuffers();
}

TEST_F(OutputRedirectTest_490, ActivateCallsActivateImpl_490) {
    EXPECT_CALL(redirect, activateImpl()).Times(1);
    redirect.activate();
}

TEST_F(OutputRedirectTest_490, DeactivateCallsDeactivateImpl_490) {
    EXPECT_CALL(redirect, activateImpl()).Times(1);
    EXPECT_CALL(redirect, deactivateImpl()).Times(1);
    redirect.activate();
    redirect.deactivate();
}

TEST_F(OutputRedirectTest_490, StateConsistencyAfterActivateDeactivate_490) {
    EXPECT_CALL(redirect, activateImpl()).Times(2);
    EXPECT_CALL(redirect, deactivateImpl()).Times(2);

    // First cycle
    redirect.activate();
    EXPECT_TRUE(redirect.isActive());
    redirect.deactivate();
    EXPECT_FALSE(redirect.isActive());

    // Second cycle
    redirect.activate();
    EXPECT_TRUE(redirect.isActive());
    redirect.deactivate();
    EXPECT_FALSE(redirect.isActive());
}
