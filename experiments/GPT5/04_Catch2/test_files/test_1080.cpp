// File: tests/redirect_guard_move_ctor_1080_tests.cpp

#include <gtest/gtest.h>
#include <type_traits>

// We include the header declaring RedirectGuard's interface.
// If your build already provides OutputRedirect, remove the stub below.
#include "Catch2/src/catch2/internal/catch_output_redirect.hpp"

namespace Catch {

// Minimal stand-in for the external collaborator used by RedirectGuard's ctor.
// It exposes only what RedirectGuard's interface observes: isActive().
struct OutputRedirect {
    explicit OutputRedirect(bool active = false) : active_(active) {}
    bool isActive() const { return active_; }

private:
    bool active_;
};

} // namespace Catch

using Catch::RedirectGuard;
using Catch::OutputRedirect;

// A tiny test fixture to keep naming consistent and future-proof for expansion.
class RedirectGuardTest_1080 : public ::testing::Test {};

// -----------------------------------------------------------------------------
// Type trait & interface conformance tests (observable at compile-time)
// -----------------------------------------------------------------------------

TEST_F(RedirectGuardTest_1080, TypeTraits_MoveOnlyAndNoThrowMove_1080) {
    // Move-constructible & move-assignable
    EXPECT_TRUE((std::is_move_constructible<RedirectGuard>::value));
    EXPECT_TRUE((std::is_move_assignable<RedirectGuard>::value));

    // Not copyable (copy-ctor/assignment deleted in interface)
    EXPECT_FALSE((std::is_copy_constructible<RedirectGuard>::value));
    EXPECT_FALSE((std::is_copy_assignable<RedirectGuard>::value));

    // noexcept guarantees advertised in the interface
    EXPECT_TRUE((std::is_nothrow_move_constructible<RedirectGuard>::value));
    EXPECT_TRUE((std::is_nothrow_move_assignable<RedirectGuard>::value));
}

// -----------------------------------------------------------------------------
// Move construction behavior: source and destination are safely destructible,
// move construction itself is noexcept, and construction uses the dependency
// via the provided interface only.
// -----------------------------------------------------------------------------

TEST_F(RedirectGuardTest_1080, MoveConstructor_NoThrow_SourceAndDestDestructible_1080) {
    OutputRedirect redir_initial(/*active=*/false);

    // Construct a guard (observably consults isActive() via the interface).
    EXPECT_NO_THROW({
        RedirectGuard g1(/*activate=*/true, redir_initial);

        // Move-construct g2 from g1; should be noexcept and leave both
        // objects safely destructible (observable: no exceptions / crashes).
        RedirectGuard g2(std::move(g1));

        // End of scope for g2 first, then g1 (post-move). Both must be safe.
    });
    // If destructor throws (it is declared noexcept(false)), EXPECT_NO_THROW
    // would fail. Here we only assert observable "no-throw during lifetime".
}

// -----------------------------------------------------------------------------
// Move assignment behavior: assigning from another live guard is noexcept and
// leaves both the target and moved-from objects safely destructible.
// -----------------------------------------------------------------------------

TEST_F(RedirectGuardTest_1080, MoveAssignment_NoThrow_BothObjectsRemainValid_1080) {
    OutputRedirect redir_a(/*active=*/true);
    OutputRedirect redir_b(/*active=*/false);

    EXPECT_NO_THROW({
        RedirectGuard g1(/*activate=*/false, redir_a);
        RedirectGuard g2(/*activate=*/true,  redir_b);

        // Move-assign; interface promises noexcept on operator=.
        g1 = std::move(g2);

        // End of scope: g1 (after assignment) and g2 (moved-from) both
        // destruct without throwing as an observable behavior.
    });
}

