#include <gtest/gtest.h>

// Include necessary Catch2 headers
#include "catch2/catch_registry_hub.hpp"
#include "catch2/interfaces/catch_interfaces_registry_hub.hpp"

namespace {

// Test that getRegistryHub returns a valid reference (doesn't crash/throw)
TEST(CatchRegistryHubTest_286, GetRegistryHubReturnsValidReference_286) {
    EXPECT_NO_THROW({
        const Catch::IRegistryHub& hub = Catch::getRegistryHub();
        // Simply verifying we can obtain a reference without error
        (void)hub;
    });
}

// Test that getRegistryHub returns the same instance on multiple calls (singleton behavior)
TEST(CatchRegistryHubTest_286, GetRegistryHubReturnsSameInstance_286) {
    const Catch::IRegistryHub& hub1 = Catch::getRegistryHub();
    const Catch::IRegistryHub& hub2 = Catch::getRegistryHub();
    EXPECT_EQ(&hub1, &hub2);
}

// Test that the returned hub provides access to reporter registry
TEST(CatchRegistryHubTest_286, GetRegistryHubProvidesReporterRegistry_286) {
    const Catch::IRegistryHub& hub = Catch::getRegistryHub();
    EXPECT_NO_THROW({
        const auto& reporterRegistry = hub.getReporterRegistry();
        (void)reporterRegistry;
    });
}

// Test that the returned hub provides access to test case registry
TEST(CatchRegistryHubTest_286, GetRegistryHubProvidesTestCaseRegistry_286) {
    const Catch::IRegistryHub& hub = Catch::getRegistryHub();
    EXPECT_NO_THROW({
        const auto& testCaseRegistry = hub.getTestCaseRegistry();
        (void)testCaseRegistry;
    });
}

// Test that the returned hub provides access to exception translator registry
TEST(CatchRegistryHubTest_286, GetRegistryHubProvidesExceptionTranslatorRegistry_286) {
    const Catch::IRegistryHub& hub = Catch::getRegistryHub();
    EXPECT_NO_THROW({
        const auto& exceptionTranslatorRegistry = hub.getExceptionTranslatorRegistry();
        (void)exceptionTranslatorRegistry;
    });
}

// Test that multiple sequential calls remain consistent
TEST(CatchRegistryHubTest_286, GetRegistryHubIsConsistentAcrossMultipleCalls_286) {
    for (int i = 0; i < 10; ++i) {
        EXPECT_NO_THROW({
            const Catch::IRegistryHub& hub = Catch::getRegistryHub();
            (void)hub;
        });
    }
    // All calls should return the same address
    const Catch::IRegistryHub* first = &Catch::getRegistryHub();
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(first, &Catch::getRegistryHub());
    }
}

} // namespace
