// File: tests/fatal_condition_handler_guard_test_1069.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include the header under test
// Adjust the include path if your tree differs.
#include "catch2/internal/catch_fatal_condition_handler.hpp"

using ::testing::InSequence;
using ::testing::NiceMock;
using ::testing::StrictMock;
using ::testing::EXPECT_CALL;
using ::testing::Times;

namespace Catch {

// We only mock the external collaborator passed to the guard.
// This relies on FatalConditionHandler having virtual methods for engage()/disengage().
// If your concrete header uses different qualifiers, mirror them here.
class MockFatalConditionHandler : public FatalConditionHandler {
public:
    // Match the interface exactly, including noexcept on disengage if present.
    MOCK_METHOD(void, engage, (), ());
    MOCK_METHOD(void, disengage, (), (noexcept));
    // Ensure a virtual dtor if the base declares one virtual (safe either way).
    virtual ~MockFatalConditionHandler() = default;
};

} // namespace Catch

// Simple alias for shorter names in tests.
using Catch::FatalConditionHandlerGuard;
using Catch::MockFatalConditionHandler;

// ----------------------------- TESTS ---------------------------------

// Verifies that constructing the guard immediately calls handler->engage().
TEST(FatalConditionHandlerGuardTest_1069, ConstructorCallsEngage_1069) {
    StrictMock<MockFatalConditionHandler> handler;

    // Only verify the construction behavior here.
    EXPECT_CALL(handler, engage()).Times(1);

    // Guard constructed in an inner scope so we don't impose any expectation
    // about destruction behavior in this test.
    {
        FatalConditionHandlerGuard guard(&handler);
        (void)guard; // silence unused warning in some toolchains
    }
}

// Verifies that destroying the guard calls handler->disengage() exactly once.
TEST(FatalConditionHandlerGuardTest_1069, DestructorCallsDisengage_1069) {
    StrictMock<MockFatalConditionHandler> handler;

    EXPECT_CALL(handler, engage()).Times(1);
    EXPECT_CALL(handler, disengage()).Times(1);

    {
        FatalConditionHandlerGuard guard(&handler);
        (void)guard;
    } // ~FatalConditionHandlerGuard should trigger disengage()
}

// Verifies call order: engage() happens before disengage().
TEST(FatalConditionHandlerGuardTest_1069, EngageThenDisengageOrder_1069) {
    StrictMock<MockFatalConditionHandler> handler;

    InSequence seq; // enforce order across expectations below
    EXPECT_CALL(handler, engage()).Times(1);
    EXPECT_CALL(handler, disengage()).Times(1);

    {
        FatalConditionHandlerGuard guard(&handler);
        (void)guard;
    } // destruction should follow engage and respect the declared order
}

// Sanity: No extra/unexpected calls when creating and destroying exactly once.
TEST(FatalConditionHandlerGuardTest_1069, NoExtraneousCalls_1069) {
    StrictMock<MockFatalConditionHandler> handler;

    // StrictMock + exact counts ensure no other calls occur.
    EXPECT_CALL(handler, engage()).Times(1);
    EXPECT_CALL(handler, disengage()).Times(1);

    {
        FatalConditionHandlerGuard guard(&handler);
        (void)guard;
    }
}
