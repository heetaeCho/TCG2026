// tests/output_redirect_deactivate_tests_492.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include the header under test
#include "catch2/internal/catch_output_redirect.hpp"

using ::testing::Expectation;
using ::testing::InSequence;
using ::testing::StrictMock;

namespace {

// Test double: override ONLY the virtual hooks to observe external interactions.
// We are not simulating internal state; we just verify that the hooks are invoked.
class MockOutputRedirect : public Catch::OutputRedirect {
public:
    MOCK_METHOD(void, activateImpl, (), (override));
    MOCK_METHOD(void, deactivateImpl, (), (override));

    // Expose pass-throughs to public API of the SUT
    using Catch::OutputRedirect::activate;
    using Catch::OutputRedirect::deactivate;
    using Catch::OutputRedirect::isActive;
};

} // namespace

// Normal operation: When active, deactivate() calls deactivateImpl and ends inactive.
TEST(OutputRedirectDeactivateTest_492, DeactivateCallsImplAndEndsInactive_492) {
    StrictMock<MockOutputRedirect> redirect;

    {
        // Becoming active should invoke activateImpl via the public API.
        EXPECT_CALL(redirect, activateImpl()).Times(1);
        redirect.activate();
    }

    EXPECT_TRUE(redirect.isActive()) << "Precondition: redirect should be active after activate()";

    {
        // Deactivation should call the virtual hook and end inactive.
        EXPECT_CALL(redirect, deactivateImpl()).Times(1);
        redirect.deactivate();
    }

    EXPECT_FALSE(redirect.isActive()) << "Postcondition: redirect should be inactive after deactivate()";
}

// Boundary: Calling deactivate() twice — first succeeds, second should assert (death test).
TEST(OutputRedirectDeactivateTest_492, DeactivateTwiceSecondDeath_492) {
    StrictMock<MockOutputRedirect> redirect;

    EXPECT_CALL(redirect, activateImpl()).Times(1);
    redirect.activate();
    ASSERT_TRUE(redirect.isActive());

    EXPECT_CALL(redirect, deactivateImpl()).Times(1);
    redirect.deactivate();
    ASSERT_FALSE(redirect.isActive());

#if GTEST_HAS_DEATH_TEST
    // The implementation asserts with message "redirect is not active"
    // when deactivate() is called while not active.
    ASSERT_DEATH({ redirect.deactivate(); }, "redirect is not active");
#else
    GTEST_SKIP() << "Death tests not supported on this platform/toolchain.";
#endif
}

// Error case: Deactivating while inactive should assert (death test).
TEST(OutputRedirectDeactivateTest_492, DeactivateWhileInactiveDeath_492) {
    StrictMock<MockOutputRedirect> redirect;

    ASSERT_FALSE(redirect.isActive()) << "Precondition: starts inactive";

#if GTEST_HAS_DEATH_TEST
    ASSERT_DEATH({ redirect.deactivate(); }, "redirect is not active");
#else
    GTEST_SKIP() << "Death tests not supported on this platform/toolchain.";
#endif
}
