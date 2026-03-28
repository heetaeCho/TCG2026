#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

// We need to include the actual headers
#include "catch2/internal/catch_output_redirect.hpp"

// Mock implementation of OutputRedirect for testing
class MockOutputRedirect : public Catch::OutputRedirect {
public:
    MOCK_METHOD(void, activateImpl, (), (override));
    MOCK_METHOD(void, deactivateImpl, (), (override));
    MOCK_METHOD(std::string, getStdout, (), (override));
    MOCK_METHOD(std::string, getStderr, (), (override));
    MOCK_METHOD(void, clearBuffers, (), (override));

    // Expose activate/deactivate tracking through the base class public interface
    // We need to track calls to activate() and deactivate() which call the Impl versions
};

class RedirectGuardTest_545 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: When RedirectGuard is constructed with activate=true and redirect is not active,
// it should activate the redirect on construction and deactivate on destruction.
TEST_F(RedirectGuardTest_545, ActivateTrueWhenInactive_DeactivatesOnDestruction_545) {
    MockOutputRedirect redirect;
    // activate() calls activateImpl(), deactivate() calls deactivateImpl()
    EXPECT_CALL(redirect, activateImpl()).Times(::testing::AtLeast(1));
    EXPECT_CALL(redirect, deactivateImpl()).Times(::testing::AtLeast(1));

    // redirect starts inactive (m_redirectActive = false by default)
    ASSERT_FALSE(redirect.isActive());

    {
        Catch::RedirectGuard guard(true, redirect);
        // After construction with activate=true, the redirect should be activated
        EXPECT_TRUE(redirect.isActive());
    }
    // After destruction, it should be deactivated back
    EXPECT_FALSE(redirect.isActive());
}

// Test: When RedirectGuard is constructed with activate=false and redirect is active,
// it should deactivate the redirect on construction and reactivate on destruction.
TEST_F(RedirectGuardTest_545, ActivateFalseWhenActive_ReactivatesOnDestruction_545) {
    MockOutputRedirect redirect;
    EXPECT_CALL(redirect, activateImpl()).Times(::testing::AtLeast(2));
    EXPECT_CALL(redirect, deactivateImpl()).Times(::testing::AtLeast(1));

    // First activate the redirect
    redirect.activate();
    ASSERT_TRUE(redirect.isActive());

    {
        Catch::RedirectGuard guard(false, redirect);
        // After construction with activate=false, the redirect should be deactivated
        EXPECT_FALSE(redirect.isActive());
    }
    // After destruction, it should be reactivated back
    EXPECT_TRUE(redirect.isActive());

    // Clean up
    redirect.deactivate();
}

// Test: When RedirectGuard is constructed with activate=true and redirect is already active,
// no state change should occur (previouslyActive == activate), so destructor does nothing extra.
TEST_F(RedirectGuardTest_545, ActivateTrueWhenAlreadyActive_NoChangeOnDestruction_545) {
    MockOutputRedirect redirect;
    EXPECT_CALL(redirect, activateImpl()).Times(::testing::AtLeast(1));
    // deactivateImpl should not be called since state doesn't change
    EXPECT_CALL(redirect, deactivateImpl()).Times(0);

    redirect.activate();
    ASSERT_TRUE(redirect.isActive());

    {
        Catch::RedirectGuard guard(true, redirect);
        EXPECT_TRUE(redirect.isActive());
    }
    // Should still be active - no change since previouslyActive == activate
    EXPECT_TRUE(redirect.isActive());

    // Clean up
    redirect.deactivate();
}

// Test: When RedirectGuard is constructed with activate=false and redirect is already inactive,
// no state change should occur, destructor does nothing.
TEST_F(RedirectGuardTest_545, ActivateFalseWhenAlreadyInactive_NoChangeOnDestruction_545) {
    MockOutputRedirect redirect;
    EXPECT_CALL(redirect, activateImpl()).Times(0);
    EXPECT_CALL(redirect, deactivateImpl()).Times(0);

    ASSERT_FALSE(redirect.isActive());

    {
        Catch::RedirectGuard guard(false, redirect);
        EXPECT_FALSE(redirect.isActive());
    }
    EXPECT_FALSE(redirect.isActive());
}

// Test: Move constructor transfers ownership, original guard should not trigger destruction logic.
TEST_F(RedirectGuardTest_545, MoveConstructorTransfersOwnership_545) {
    MockOutputRedirect redirect;
    EXPECT_CALL(redirect, activateImpl()).Times(::testing::AtLeast(1));
    EXPECT_CALL(redirect, deactivateImpl()).Times(::testing::AtLeast(1));

    ASSERT_FALSE(redirect.isActive());

    {
        Catch::RedirectGuard guard1(true, redirect);
        EXPECT_TRUE(redirect.isActive());

        Catch::RedirectGuard guard2(std::move(guard1));
        // After move, guard1 is "moved from" and should not deactivate
        EXPECT_TRUE(redirect.isActive());
    }
    // Only guard2's destructor should trigger deactivation
    EXPECT_FALSE(redirect.isActive());
}

// Test: Move assignment transfers ownership.
TEST_F(RedirectGuardTest_545, MoveAssignmentTransfersOwnership_545) {
    MockOutputRedirect redirect;
    EXPECT_CALL(redirect, activateImpl()).Times(::testing::AtLeast(1));
    EXPECT_CALL(redirect, deactivateImpl()).Times(::testing::AtLeast(1));

    ASSERT_FALSE(redirect.isActive());

    {
        Catch::RedirectGuard guard1(true, redirect);
        EXPECT_TRUE(redirect.isActive());

        // Create another guard that won't change state
        Catch::RedirectGuard guard2(true, redirect);

        guard2 = std::move(guard1);
        // guard1 is moved from, guard2 now holds guard1's state
    }
    EXPECT_FALSE(redirect.isActive());
}

// Test: OutputRedirect isActive returns correct state
TEST_F(RedirectGuardTest_545, OutputRedirectIsActiveReflectsState_545) {
    MockOutputRedirect redirect;
    EXPECT_CALL(redirect, activateImpl()).Times(1);
    EXPECT_CALL(redirect, deactivateImpl()).Times(1);

    EXPECT_FALSE(redirect.isActive());
    redirect.activate();
    EXPECT_TRUE(redirect.isActive());
    redirect.deactivate();
    EXPECT_FALSE(redirect.isActive());
}

// Test: Multiple activate calls are handled
TEST_F(RedirectGuardTest_545, MultipleActivateCallsHandled_545) {
    MockOutputRedirect redirect;
    EXPECT_CALL(redirect, activateImpl()).Times(::testing::AtLeast(1));

    redirect.activate();
    EXPECT_TRUE(redirect.isActive());
    // Second activate - behavior depends on implementation but should not crash
    redirect.activate();
    EXPECT_TRUE(redirect.isActive());

    EXPECT_CALL(redirect, deactivateImpl()).Times(::testing::AtLeast(1));
    redirect.deactivate();
}

// Test: RedirectGuard with activate=true properly interacts with OutputRedirect
TEST_F(RedirectGuardTest_545, GuardActivatesThenDeactivates_545) {
    MockOutputRedirect redirect;
    EXPECT_CALL(redirect, activateImpl()).Times(1);
    EXPECT_CALL(redirect, deactivateImpl()).Times(1);

    ASSERT_FALSE(redirect.isActive());

    {
        Catch::RedirectGuard guard(true, redirect);
        // Verify redirect is now active
        EXPECT_TRUE(redirect.isActive());
    }
    // Verify redirect is deactivated after guard destruction
    EXPECT_FALSE(redirect.isActive());
}
