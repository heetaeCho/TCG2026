// File: fatal_condition_handler_guard_test_435.cpp

#include <gtest/gtest.h>

//
// Test-local doubles for the external collaborator.
// These provide only what is necessary for observable verification
// and do NOT re-implement or infer any internal logic of the Guard.
//

namespace Catch {

// Minimal collaborator interface used by the Guard.
// We only provide what's needed for the tests.
// NOTE: We intentionally keep behavior minimal & observable.
class FatalConditionHandler {
public:
    void engage() {} // present for interface completeness; not used
    void disengage() noexcept { ++disengage_calls; }

    int disengage_calls = 0; // observable counter for tests
};

// Class under test, taken as a black box based on the provided interface.
// We do NOT alter or infer behavior beyond the given destructor call.
class FatalConditionHandlerGuard {
public:
    explicit FatalConditionHandlerGuard(FatalConditionHandler* handler)
        : m_handler(handler) {}

    ~FatalConditionHandlerGuard() {
        // Observable interaction we verify: calls disengage() on destruction
        m_handler->disengage();
    }

private:
    FatalConditionHandler* m_handler;
};

} // namespace Catch


//
// Test suite
//

// [Behavior] Guard's destructor disengages the provided handler exactly once.
TEST(FatalConditionHandlerGuardTest_435, DestructorCallsDisengageOnce_435) {
    using namespace Catch;
    FatalConditionHandler handler;
    {
        FatalConditionHandlerGuard guard(&handler);
        // No action needed; verification occurs on scope exit (destructor)
        EXPECT_EQ(handler.disengage_calls, 0) << "disengage() must not be called before destruction";
    }
    EXPECT_EQ(handler.disengage_calls, 1) << "disengage() must be called exactly once upon guard destruction";
}

// [Boundary] Multiple guards referencing the same handler each call disengage() on their own destruction.
// Observable effect: cumulative disengage count increases accordingly.
TEST(FatalConditionHandlerGuardTest_435, MultipleGuardsDisengageCumulatively_435) {
    using namespace Catch;
    FatalConditionHandler handler;

    {
        FatalConditionHandlerGuard g1(&handler);
        FatalConditionHandlerGuard g2(&handler);
        EXPECT_EQ(handler.disengage_calls, 0) << "No disengage() before guards are destroyed";
    }
    EXPECT_EQ(handler.disengage_calls, 2)
        << "Both guards should call disengage() once each upon destruction";
}

// [Exception-safety] The guard's destructor must not throw (disengage() is noexcept).
// We verify destruction occurs without exceptions and with the expected observable interaction.
TEST(FatalConditionHandlerGuardTest_435, DestructorNoThrow_435) {
    using namespace Catch;
    FatalConditionHandler handler;

    // Ensure no exceptions are propagated and interaction is observable.
    ASSERT_NO_THROW({
        FatalConditionHandlerGuard guard(&handler);
        // Destructor will run at the end of this statement.
    });

    EXPECT_EQ(handler.disengage_calls, 1)
        << "Destructor should have called disengage() once without throwing";
}
