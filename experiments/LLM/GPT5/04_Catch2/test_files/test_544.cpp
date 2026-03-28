// File: tests/scoped_deactivate_tests_544.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Headers under test
#include "catch2/internal/catch_output_redirect.hpp"
#include "catch2/internal/catch_output_redirect.cpp" // for Catch::scopedDeactivate declaration

using ::testing::InSequence;
using ::testing::StrictMock;
using ::testing::Exactly;

namespace Catch {

// Create a strict mock for the public collaborator interface.
// We only mock *public* virtuals to observe interactions.
// We do NOT touch any private/internal state or impl details.
class MockOutputRedirect : public OutputRedirect {
public:
    // Only mock what we need to observe:
    MOCK_METHOD(void, activate, (), (override));
    MOCK_METHOD(void, deactivate, (), (override));

    // Provide benign stubs for other public virtuals that might be referenced
    // by the real implementation in some environments. Keeping them non-strict
    // avoids over-constraining behavior we don't need to validate.
    MOCK_METHOD(std::string, getStdout, (), (override));
    MOCK_METHOD(std::string, getStderr, (), (override));
    MOCK_METHOD(void, clearBuffers, (), (override));

    // Ensure virtual dtor is defined
    ~MockOutputRedirect() override = default;
};

} // namespace Catch

// -----------------------------------------------------------------------------
// Single guard: should request deactivation on construction and re-activation
// on destruction (observable via public methods only).
// -----------------------------------------------------------------------------
TEST(ScopedDeactivateTest_544, SingleGuard_DeactivateThenActivate_544) {
    StrictMock<Catch::MockOutputRedirect> redirect;

    {
        InSequence seq; // enforce call order

        // Expect: constructing the guard leads to a call that deactivates output
        EXPECT_CALL(redirect, deactivate()).Times(Exactly(1));

        // And when the guard goes out of scope, it should restore/activate
        EXPECT_CALL(redirect, activate()).Times(Exactly(1));

        auto guard = Catch::scopedDeactivate(redirect);

        // While guard is alive, no further expectations asserted here; order
        // checking ensures activate won't be called before destruction.
        (void)guard; // silence unused warning if needed
    }
    // Exiting scope destroys guard, satisfying the activate() expectation.
}

// -----------------------------------------------------------------------------
// Nested guards: observable interaction should be LIFO.
// Outer construction: deactivate()
// Inner construction: deactivate()
// Inner destruction first: activate()
// Outer destruction last: activate()
// -----------------------------------------------------------------------------
TEST(ScopedDeactivateTest_544, NestedGuards_LIFODeactivateActivate_544) {
    StrictMock<Catch::MockOutputRedirect> redirect;

    InSequence seq; // enforce exact call order across the whole scope

    // Outer construction
    EXPECT_CALL(redirect, deactivate()).Times(Exactly(1));
    {
        auto outer = Catch::scopedDeactivate(redirect);

        // Inner construction
        EXPECT_CALL(redirect, deactivate()).Times(Exactly(1));
        {
            auto inner = Catch::scopedDeactivate(redirect);
            (void)inner;
        } // inner destroyed -> expect activate()
        EXPECT_CALL(redirect, activate()).Times(Exactly(1));

    } // outer destroyed -> expect activate()
    EXPECT_CALL(redirect, activate()).Times(Exactly(1));
}
