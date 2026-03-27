// OutputRedirect_tests_490.cpp
#include <gtest/gtest.h>
#include "catch2/internal/catch_output_redirect.hpp"

using Catch::OutputRedirect;

class OutputRedirectTest_490 : public ::testing::Test {
protected:
    OutputRedirect redir;
};

// [Normal] A default-constructed redirect is not active
TEST_F(OutputRedirectTest_490, InitialStateIsInactive_490) {
    EXPECT_FALSE(redir.isActive());
}

// [Normal] After activate(), isActive() reports true
TEST_F(OutputRedirectTest_490, ActivateSetsActive_490) {
    redir.activate();
    EXPECT_TRUE(redir.isActive());
}

// [Normal] activate() followed by deactivate() returns to inactive
TEST_F(OutputRedirectTest_490, DeactivateAfterActivateSetsInactive_490) {
    redir.activate();
    ASSERT_TRUE(redir.isActive()); // sanity check observable state

    redir.deactivate();
    EXPECT_FALSE(redir.isActive());
}

// [Boundary] Deactivating when already inactive keeps it inactive (and should not crash)
TEST_F(OutputRedirectTest_490, RedundantDeactivateKeepsInactive_490) {
    ASSERT_FALSE(redir.isActive()); // start inactive

    redir.deactivate();             // call again while inactive
    EXPECT_FALSE(redir.isActive()); // still inactive
}

// [Boundary] Multiple activates keep it active (idempotent from caller’s view)
TEST_F(OutputRedirectTest_490, MultipleActivateKeepsActive_490) {
    redir.activate();
    ASSERT_TRUE(redir.isActive());

    redir.activate();               // activate again
    EXPECT_TRUE(redir.isActive());  // still active
}

// [Boundary] Activate twice, then deactivate once -> inactive only after explicit deactivate
TEST_F(OutputRedirectTest_490, MultipleActivateThenSingleDeactivateLeadsInactive_490) {
    redir.activate();
    redir.activate();
    ASSERT_TRUE(redir.isActive());

    redir.deactivate();
    EXPECT_FALSE(redir.isActive());
}
