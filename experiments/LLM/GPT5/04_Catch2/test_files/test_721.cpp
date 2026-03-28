// File: tests/config_has_test_filters_721_tests.cpp

#include <gtest/gtest.h>

// Include only the public interface
#include "catch2/catch_config.hpp"

using namespace Catch;

// Test fixture kept minimal: we only exercise observable behavior via the API.
class ConfigHasTestFiltersTest_721 : public ::testing::Test {
protected:
    // Helper to provide a const reference view, ensuring const-correctness
    static bool CallOnConstRef(const Config& cfg) {
        return cfg.hasTestFilters();
    }
};

// [Normal operation] Default-constructed Config should have no test filters.
// Rationale: With no configuration provided via the public interface, there are
// no observable user-specified test filters, so the API should report "false".
TEST_F(ConfigHasTestFiltersTest_721, DefaultIsFalse_721) {
    Config cfg; // default construction via public ctor
    EXPECT_FALSE(cfg.hasTestFilters());
}

// [Idempotence / No side-effects] Calling hasTestFilters() should be a pure
// query with no observable side-effects. Calling it repeatedly should not
// change the returned value or any observable state.
TEST_F(ConfigHasTestFiltersTest_721, RepeatedCallsAreStable_721) {
    Config cfg;

    bool first  = cfg.hasTestFilters();
    bool second = cfg.hasTestFilters();
    bool third  = cfg.hasTestFilters();

    EXPECT_EQ(first, second);
    EXPECT_EQ(second, third);
    EXPECT_FALSE(third);
}

// [Const-correctness] hasTestFilters() must be callable on a const reference
// and return the same observable result.
TEST_F(ConfigHasTestFiltersTest_721, CallableOnConst_721) {
    Config cfg;               // non-const object
    const Config& cref = cfg; // const view

    EXPECT_EQ(cfg.hasTestFilters(), CallOnConstRef(cref));
    EXPECT_FALSE(CallOnConstRef(cref));
}

// [Isolation] Multiple default-constructed instances should not affect each
// other’s observable state.
TEST_F(ConfigHasTestFiltersTest_721, InstancesAreIndependent_721) {
    Config a;
    Config b;

    EXPECT_FALSE(a.hasTestFilters());
    EXPECT_FALSE(b.hasTestFilters());

    // Call on one instance should not affect the other.
    (void)a.hasTestFilters();
    EXPECT_FALSE(b.hasTestFilters());
}
