#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <cassert>

// Since we need to test the OutputRedirect class which has virtual methods,
// we create a concrete mock/test subclass to test the base class behavior.

namespace Catch {

class OutputRedirect {
public:
    virtual ~OutputRedirect() = default;

    void activate() {
        assert(!m_redirectActive && "redirect is already active");
        activateImpl();
        m_redirectActive = true;
    }

    void deactivate() {
        assert(m_redirectActive && "redirect is not active");
        deactivateImpl();
        m_redirectActive = false;
    }

    bool isActive() const { return m_redirectActive; }

    virtual std::string getStdout() = 0;
    virtual std::string getStderr() = 0;
    virtual void clearBuffers() = 0;

private:
    bool m_redirectActive = false;
    virtual void activateImpl() = 0;
    virtual void deactivateImpl() = 0;
};

} // namespace Catch

// Mock subclass for testing
class MockOutputRedirect : public Catch::OutputRedirect {
public:
    MOCK_METHOD(void, activateImpl, (), (override));
    MOCK_METHOD(void, deactivateImpl, (), (override));
    MOCK_METHOD(std::string, getStdout, (), (override));
    MOCK_METHOD(std::string, getStderr, (), (override));
    MOCK_METHOD(void, clearBuffers, (), (override));
};

class OutputRedirectTest_491 : public ::testing::Test {
protected:
    MockOutputRedirect redirect;
};

// Test that a newly created OutputRedirect is not active
TEST_F(OutputRedirectTest_491, InitiallyNotActive_491) {
    EXPECT_FALSE(redirect.isActive());
}

// Test that activate() sets the redirect to active state
TEST_F(OutputRedirectTest_491, ActivateSetsActive_491) {
    EXPECT_CALL(redirect, activateImpl()).Times(1);
    redirect.activate();
    EXPECT_TRUE(redirect.isActive());
}

// Test that activate() calls activateImpl()
TEST_F(OutputRedirectTest_491, ActivateCallsActivateImpl_491) {
    EXPECT_CALL(redirect, activateImpl()).Times(1);
    redirect.activate();
}

// Test that deactivate() sets the redirect to inactive state
TEST_F(OutputRedirectTest_491, DeactivateSetsInactive_491) {
    EXPECT_CALL(redirect, activateImpl()).Times(1);
    EXPECT_CALL(redirect, deactivateImpl()).Times(1);
    redirect.activate();
    EXPECT_TRUE(redirect.isActive());
    redirect.deactivate();
    EXPECT_FALSE(redirect.isActive());
}

// Test that deactivate() calls deactivateImpl()
TEST_F(OutputRedirectTest_491, DeactivateCallsDeactivateImpl_491) {
    EXPECT_CALL(redirect, activateImpl()).Times(1);
    EXPECT_CALL(redirect, deactivateImpl()).Times(1);
    redirect.activate();
    redirect.deactivate();
}

// Test that activate then deactivate then activate works correctly
TEST_F(OutputRedirectTest_491, ActivateDeactivateActivateCycle_491) {
    EXPECT_CALL(redirect, activateImpl()).Times(2);
    EXPECT_CALL(redirect, deactivateImpl()).Times(1);

    redirect.activate();
    EXPECT_TRUE(redirect.isActive());

    redirect.deactivate();
    EXPECT_FALSE(redirect.isActive());

    redirect.activate();
    EXPECT_TRUE(redirect.isActive());
}

// Test that activating when already active triggers assertion (death test)
TEST_F(OutputRedirectTest_491, ActivateWhileActiveAssertsFailure_491) {
    EXPECT_CALL(redirect, activateImpl()).Times(1);
    redirect.activate();

    EXPECT_DEATH({
        redirect.activate();
    }, "redirect is already active");
}

// Test that deactivating when not active triggers assertion (death test)
TEST(OutputRedirectDeathTest_491, DeactivateWhileNotActiveAssertsFailure_491) {
    MockOutputRedirect redirect;
    EXPECT_DEATH({
        redirect.deactivate();
    }, "redirect is not active");
}

// Test getStdout returns expected value
TEST_F(OutputRedirectTest_491, GetStdoutReturnsExpectedValue_491) {
    EXPECT_CALL(redirect, getStdout()).WillOnce(::testing::Return("hello stdout"));
    EXPECT_EQ(redirect.getStdout(), "hello stdout");
}

// Test getStderr returns expected value
TEST_F(OutputRedirectTest_491, GetStderrReturnsExpectedValue_491) {
    EXPECT_CALL(redirect, getStderr()).WillOnce(::testing::Return("hello stderr"));
    EXPECT_EQ(redirect.getStderr(), "hello stderr");
}

// Test getStdout returns empty string when nothing captured
TEST_F(OutputRedirectTest_491, GetStdoutReturnsEmptyByDefault_491) {
    EXPECT_CALL(redirect, getStdout()).WillOnce(::testing::Return(""));
    EXPECT_EQ(redirect.getStdout(), "");
}

// Test getStderr returns empty string when nothing captured
TEST_F(OutputRedirectTest_491, GetStderrReturnsEmptyByDefault_491) {
    EXPECT_CALL(redirect, getStderr()).WillOnce(::testing::Return(""));
    EXPECT_EQ(redirect.getStderr(), "");
}

// Test clearBuffers can be called
TEST_F(OutputRedirectTest_491, ClearBuffersCalled_491) {
    EXPECT_CALL(redirect, clearBuffers()).Times(1);
    redirect.clearBuffers();
}

// Test clearBuffers then getStdout returns empty
TEST_F(OutputRedirectTest_491, ClearBuffersThenGetStdoutEmpty_491) {
    ::testing::InSequence seq;
    EXPECT_CALL(redirect, clearBuffers()).Times(1);
    EXPECT_CALL(redirect, getStdout()).WillOnce(::testing::Return(""));

    redirect.clearBuffers();
    EXPECT_EQ(redirect.getStdout(), "");
}

// Test multiple activate/deactivate cycles
TEST_F(OutputRedirectTest_491, MultipleActivateDeactivateCycles_491) {
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

// Test that isActive is const-correct (can be called on const reference)
TEST_F(OutputRedirectTest_491, IsActiveConstCorrectness_491) {
    const Catch::OutputRedirect& constRef = redirect;
    EXPECT_FALSE(constRef.isActive());
}

// Test virtual destructor doesn't crash
TEST(OutputRedirectLifecycle_491, DestructorDoesNotCrash_491) {
    auto* redirect = new MockOutputRedirect();
    EXPECT_FALSE(redirect->isActive());
    delete redirect;
}

// Test destruction while active (should be valid, destructor handles cleanup)
TEST(OutputRedirectLifecycle_491, DestructionWhileActive_491) {
    auto* redirect = new MockOutputRedirect();
    EXPECT_CALL(*redirect, activateImpl()).Times(1);
    redirect->activate();
    EXPECT_TRUE(redirect->isActive());
    delete redirect;
}
