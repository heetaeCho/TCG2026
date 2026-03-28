// File: tests/reporter_registry_default_1088_tests.cpp

#include <gtest/gtest.h>

#include "catch2/internal/catch_reporter_registry.hpp"

// NOTE:
// - These tests only interact with ReporterRegistry via its public methods
//   (constructor, getFactories(), getListeners()).
// - We do not construct or use ReporterConfig, IReporterFactoryPtr,
//   or EventListenerFactory, and we do not assert on the concrete factory types.

namespace {

using Catch::ReporterRegistry;

TEST(ReporterRegistry_1088, DefaultFactoriesContainBuiltinNames_1088) {
    ReporterRegistry registry;

    const auto& factories = registry.getFactories();

    // Presence checks for all built-ins registered by the constructor.
    // We assert only on keys (reporter names), not on values.
    EXPECT_TRUE(factories.find("Automake")  != factories.end());
    EXPECT_TRUE(factories.find("compact")   != factories.end());
    EXPECT_TRUE(factories.find("console")   != factories.end());
    EXPECT_TRUE(factories.find("JUnit")     != factories.end());
    EXPECT_TRUE(factories.find("SonarQube") != factories.end());
    EXPECT_TRUE(factories.find("TAP")       != factories.end());
    EXPECT_TRUE(factories.find("TeamCity")  != factories.end());
    EXPECT_TRUE(factories.find("XML")       != factories.end());
    EXPECT_TRUE(factories.find("JSON")      != factories.end());

    // Sanity: expect at least these 9 entries. We don't assert exact size
    // to avoid over-constraining future additions.
    EXPECT_GE(static_cast<int>(factories.size()), 9);
}

TEST(ReporterRegistry_1088, ListenersInitiallyEmpty_1088) {
    ReporterRegistry registry;

    const auto& listeners = registry.getListeners();

    // No listeners are registered by default.
    EXPECT_TRUE(listeners.empty());
    EXPECT_EQ(listeners.size(), 0u);
}

TEST(ReporterRegistry_1088, FactoryLookupIsCaseInsensitiveForKnownKeys_1088) {
    ReporterRegistry registry;

    const auto& factories = registry.getFactories();

    // The comparator exposed via the public map type is case-insensitive,
    // so lookups using different casings for the same logical key should succeed.
    // We do NOT assert on the comparator implementation—only on the observable
    // ability to find existing entries with mixed case.
    auto it_lower = factories.find("console");
    auto it_mixed = factories.find("ConSoLe");
    auto it_upper = factories.find("CONSOLE");

    EXPECT_NE(it_lower, factories.end()); // present by default
    EXPECT_NE(it_mixed, factories.end());
    EXPECT_NE(it_upper, factories.end());

    // All successful lookups should refer to the same element.
    // (In std::map, find returns the iterator to the stored node.)
    EXPECT_EQ(it_lower, it_mixed);
    EXPECT_EQ(it_lower, it_upper);

    // Spot-check another built-in with mixed case to avoid overfitting to one key.
    auto it_json_1 = factories.find("JSON");
    auto it_json_2 = factories.find("json");
    EXPECT_NE(it_json_1, factories.end());
    EXPECT_EQ(it_json_1, it_json_2);
}

} // namespace
