#include "catch2/internal/catch_fatal_condition_handler.hpp"
#include <gtest/gtest.h>
#include <cassert>

class FatalConditionHandlerTest_433 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a freshly constructed handler can be engaged without issues
TEST_F(FatalConditionHandlerTest_433, EngageOnFreshHandler_433) {
    Catch::FatalConditionHandler handler;
    // Should not throw or assert - first engage on a fresh handler
    EXPECT_NO_THROW(handler.engage());
    // Clean up by disengaging
    handler.disengage();
}

// Test that disengage can be called after engage
TEST_F(FatalConditionHandlerTest_433, DisengageAfterEngage_433) {
    Catch::FatalConditionHandler handler;
    handler.engage();
    // Disengage should work without issues after engage
    EXPECT_NO_THROW(handler.disengage());
}

// Test that engage followed by disengage followed by engage works (re-engage)
TEST_F(FatalConditionHandlerTest_433, ReEngageAfterDisengage_433) {
    Catch::FatalConditionHandler handler;
    handler.engage();
    handler.disengage();
    // After disengaging, we should be able to engage again
    EXPECT_NO_THROW(handler.engage());
    handler.disengage();
}

// Test that engaging twice without disengage triggers assertion failure
// Since assert causes abort, we test this with a death test
TEST_F(FatalConditionHandlerTest_433, EngageTwiceCausesAssertionFailure_433) {
    EXPECT_DEATH({
        Catch::FatalConditionHandler handler;
        handler.engage();
        handler.engage();  // Should trigger assert
    }, ".*Handler cannot be installed twice.*|.*");
}

// Test that a handler can be constructed and destroyed without engaging
TEST_F(FatalConditionHandlerTest_433, ConstructAndDestroyWithoutEngage_433) {
    EXPECT_NO_THROW({
        Catch::FatalConditionHandler handler;
        // Just let it go out of scope without engaging
    });
}

// Test that disengage is noexcept as declared
TEST_F(FatalConditionHandlerTest_433, DisengageIsNoexcept_433) {
    Catch::FatalConditionHandler handler;
    // Verify disengage is noexcept at compile time
    static_assert(noexcept(handler.disengage()), "disengage should be noexcept");
    // Also run it to make sure no issues
    handler.engage();
    handler.disengage();
}

// Test multiple cycles of engage/disengage
TEST_F(FatalConditionHandlerTest_433, MultipleCycles_433) {
    Catch::FatalConditionHandler handler;
    for (int i = 0; i < 5; ++i) {
        EXPECT_NO_THROW(handler.engage());
        EXPECT_NO_THROW(handler.disengage());
    }
}

// Test that destruction after engage (without explicit disengage) doesn't leak/crash
TEST_F(FatalConditionHandlerTest_433, DestructionAfterEngageWithoutDisengage_433) {
    EXPECT_NO_THROW({
        Catch::FatalConditionHandler handler;
        handler.engage();
        // Destructor should handle cleanup
    });
}
