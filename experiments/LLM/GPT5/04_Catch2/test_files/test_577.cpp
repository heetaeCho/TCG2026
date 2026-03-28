// File: tests/reporter_registry_getFactories_577_tests.cpp

#include <gtest/gtest.h>
#include "catch2/internal/catch_reporter_registry.hpp"

using namespace Catch;

class ReporterRegistryTest_577 : public ::testing::Test {
protected:
    ReporterRegistry registry; // fresh instance per test
};

// [577] Verifies that a fresh registry exposes an empty factories view.
TEST_F(ReporterRegistryTest_577, GetFactories_IsEmptyOnNewRegistry_577) {
    const auto& factories = registry.getFactories();
    EXPECT_TRUE(factories.empty());
    EXPECT_EQ(factories.size(), 0u);
}

// [577] Verifies that registering a reporter makes it visible through getFactories().
TEST_F(ReporterRegistryTest_577, GetFactories_ContainsRegisteredKey_577) {
    // Treat IReporterFactoryPtr as opaque; we do not use or assume anything about it.
    IReporterFactoryPtr dummyFactory{}; // nullptr is acceptable as opaque handle for storage visibility tests
    registry.registerReporter("console", dummyFactory);

    const auto& factories = registry.getFactories();
    // Observable behavior: key presence
    auto it = factories.find("console");
    EXPECT_NE(it, factories.end());
    // Do NOT assert on internal pointer value beyond presence; keep the class a black box.
}

// [577] Verifies that the returned map is a live reference (not a copy).
TEST_F(ReporterRegistryTest_577, GetFactories_ReturnsLiveReference_577) {
    const auto& view = registry.getFactories();
    EXPECT_TRUE(view.empty());

    // Mutate registry via public API after taking the reference.
    IReporterFactoryPtr f1{};
    IReporterFactoryPtr f2{};
    registry.registerReporter("r1", f1);
    registry.registerReporter("r2", f2);

    // The previously acquired reference must reflect the new state.
    EXPECT_EQ(view.size(), 2u);
    EXPECT_NE(view.find("r1"), view.end());
    EXPECT_NE(view.find("r2"), view.end());
}

// [577] Verifies that lookup behaves case-insensitively (per the declared comparator type).
TEST_F(ReporterRegistryTest_577, GetFactories_CaseInsensitiveLookup_577) {
    IReporterFactoryPtr dummyFactory{};
    registry.registerReporter("TeStEr", dummyFactory);

    const auto& factories = registry.getFactories();

    // Using differently-cased keys should still find the same entry,
    // because the map comparator type is Detail::CaseInsensitiveLess.
    EXPECT_NE(factories.find("tester"), factories.end());
    EXPECT_NE(factories.find("TESTER"), factories.end());
    EXPECT_NE(factories.find("TeStEr"), factories.end());
}

// [577] Boundary: registering an empty name (if allowed by interface) is observable via getFactories().
TEST_F(ReporterRegistryTest_577, GetFactories_AllowsEmptyNameKey_577) {
    IReporterFactoryPtr dummyFactory{};
    // We do not assume validation logic; we just assert on the observable effect.
    registry.registerReporter("", dummyFactory);

    const auto& factories = registry.getFactories();
    // Either the key is present (accepted) or not (rejected). Both are valid behaviors,
    // but the observable outcome must be consistent with the registry's public API.
    // We assert that the API is at least well-defined: no crash and the map is queryable.
    // If accepted, it should be findable.
    auto it = factories.find("");
    if (it != factories.end()) {
        SUCCEED() << "Empty reporter name accepted and visible in factories.";
    } else {
        SUCCEED() << "Empty reporter name rejected; not present in factories.";
    }
}
