// test_fatal_condition_handler_434.cpp
#include <gtest/gtest.h>
#include "catch2/internal/catch_fatal_condition_handler.hpp"

using Catch::FatalConditionHandler;

// noexcept is part of the public signature; verify at compile time.
static_assert(noexcept(std::declval<FatalConditionHandler&>().disengage()),
              "disengage() must be noexcept per interface");

// Note: Death tests require assertions to be enabled (no NDEBUG).
// We gracefully skip those tests when NDEBUG is defined.

#ifndef NDEBUG
TEST(FatalConditionHandlerTest_434, DisengageWithoutEngage_TriggersAssert_434) {
    FatalConditionHandler h;
    // Expect an assertion failure when disengaging before engage().
    // We match a distinctive part of the message to avoid toolchain differences.
    EXPECT_DEATH({ h.disengage(); },
                 "Handler cannot be uninstalled without being installed first");
}
#else
TEST(FatalConditionHandlerTest_434, DisengageWithoutEngage_TriggersAssert_434) {
    GTEST_SKIP() << "Assertions disabled (NDEBUG); death test skipped.";
}
#endif

TEST(FatalConditionHandlerTest_434, EngageThenDisengage_Succeeds_434) {
    FatalConditionHandler h;
    // Normal operation: engage followed by disengage should not crash or throw.
    // (No other observable side effects are available via the public interface.)
    EXPECT_NO_THROW({
        h.engage();
        h.disengage();
    });
    SUCCEED();
}

#ifndef NDEBUG
TEST(FatalConditionHandlerTest_434, DoubleDisengage_SecondCallAsserts_434) {
    FatalConditionHandler h;
    h.engage();
    // First disengage is valid
    EXPECT_NO_THROW(h.disengage());
    // Second disengage without a new engage should assert
    EXPECT_DEATH({ h.disengage(); },
                 "Handler cannot be uninstalled without being installed first");
}
#else
TEST(FatalConditionHandlerTest_434, DoubleDisengage_SecondCallAsserts_434) {
    GTEST_SKIP() << "Assertions disabled (NDEBUG); death test skipped.";
}
#endif
