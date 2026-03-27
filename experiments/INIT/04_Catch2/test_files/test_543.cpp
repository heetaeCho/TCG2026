// File: output_redirect_raii_tests_543.cpp

#include <gtest/gtest.h>
#include "catch2/internal/catch_output_redirect.hpp"  // OutputRedirect, scopedActivate

using namespace Catch;

// Test 1: Basic RAII behavior — guard activates on construction and deactivates on destruction.
TEST(OutputRedirectRAII_543, ScopedActivate_ActivatesDuringLifetime_543) {
    OutputRedirect redirect;

    // Before: not active
    EXPECT_FALSE(redirect.isActive());

    {
        // Creating the guard via the provided factory should activate redirection
        auto guard = scopedActivate(redirect);
        EXPECT_TRUE(redirect.isActive()) << "Redirection should be active while the guard lives";
    }

    // After guard is destroyed: not active
    EXPECT_FALSE(redirect.isActive()) << "Redirection should be deactivated after guard destruction";
}

// Test 2: Nested guards — still active while any guard exists; finally deactivates after the last guard ends.
TEST(OutputRedirectRAII_543, ScopedActivate_NestedGuards_LifetimeSemantics_543) {
    OutputRedirect redirect;
    EXPECT_FALSE(redirect.isActive());

    {
        auto outer = scopedActivate(redirect);
        EXPECT_TRUE(redirect.isActive()) << "Active with outer guard";

        {
            auto inner = scopedActivate(redirect);
            EXPECT_TRUE(redirect.isActive()) << "Still active with inner guard";
        }

        // After inner guard ends, should remain active while outer is still alive
        EXPECT_TRUE(redirect.isActive()) << "Still active after inner guard destruction while outer remains";
    }

    // After outer guard ends, no guards remain — should be inactive
    EXPECT_FALSE(redirect.isActive()) << "Inactive after all guards are destroyed";
}

// Test 3: Move semantics — moving the guard should transfer lifetime control without early deactivation.
TEST(OutputRedirectRAII_543, ScopedActivate_MoveTransfersLifetime_543) {
    OutputRedirect redirect;
    EXPECT_FALSE(redirect.isActive());

    std::optional<decltype(scopedActivate(redirect))> movedTo; // use type-deduced optional to hold moved guard

    {
        auto guard = scopedActivate(redirect);
        EXPECT_TRUE(redirect.isActive()) << "Active with original guard";

        // Move the guard; redirection should remain active after the move
        movedTo.emplace(std::move(guard));
        EXPECT_TRUE(redirect.isActive()) << "Still active after moving guard";
    } // original (moved-from) guard goes out of scope here

    // Should still be active because the moved-to guard is alive
    EXPECT_TRUE(redirect.isActive()) << "Active while moved-to guard is alive";

    // Now destroy the moved-to guard
    movedTo.reset();

    EXPECT_FALSE(redirect.isActive()) << "Inactive after moved-to guard destruction";
}
