// ReporterRegistry_registerReporter_tests_575.cpp
#include <gtest/gtest.h>
#include "catch2/internal/catch_reporter_registry.hpp"

using namespace Catch;

class ReporterRegistryTest_575 : public ::testing::Test {
protected:
    ReporterRegistry registry;
};

// Normal operation: inserting a single, valid reporter name succeeds
TEST_F(ReporterRegistryTest_575, RegisterValidNameInserts_575) {
    EXPECT_EQ(registry.getFactories().size(), 0u);

    // Pass a null factory pointer; the API accepts the pointer type, and we only
    // verify observable effects via getFactories().
    registry.registerReporter("reportA", IReporterFactoryPtr{});

    const auto& factories = registry.getFactories();
    EXPECT_EQ(factories.size(), 1u);
    EXPECT_NE(factories.find("reportA"), factories.end());
}

// Error case: name containing "::" should be rejected
TEST_F(ReporterRegistryTest_575, RejectsNameWithScopeOperator_575) {
    EXPECT_ANY_THROW({
        registry.registerReporter("foo::bar", IReporterFactoryPtr{});
    });
    // No insertion happened
    EXPECT_EQ(registry.getFactories().size(), 0u);
}

// Error case: duplicate exact name should be rejected and leave state unchanged
TEST_F(ReporterRegistryTest_575, RejectsDuplicateExactName_575) {
    registry.registerReporter("dup", IReporterFactoryPtr{});
    EXPECT_EQ(registry.getFactories().size(), 1u);

    EXPECT_ANY_THROW({
        registry.registerReporter("dup", IReporterFactoryPtr{});
    });

    // Still only one entry
    const auto& factories = registry.getFactories();
    EXPECT_EQ(factories.size(), 1u);
    EXPECT_NE(factories.find("dup"), factories.end());
}

// Boundary/behavioral case: case-insensitive duplicate should also be rejected
// because the registry uses a case-insensitive comparator for keys.
TEST_F(ReporterRegistryTest_575, RejectsCaseInsensitiveDuplicateName_575) {
    registry.registerReporter("json", IReporterFactoryPtr{});
    EXPECT_EQ(registry.getFactories().size(), 1u);

    EXPECT_ANY_THROW({
        registry.registerReporter("JSON", IReporterFactoryPtr{});
    });

    // Map remains with a single entry; find should work with either casing
    const auto& factories = registry.getFactories();
    EXPECT_EQ(factories.size(), 1u);
    EXPECT_NE(factories.find("json"), factories.end());
    EXPECT_NE(factories.find("JSON"), factories.end()); // should locate the same key per comparator
}

// Normal operation: multiple distinct names register fine
TEST_F(ReporterRegistryTest_575, RegistersMultipleDistinctNames_575) {
    registry.registerReporter("a", IReporterFactoryPtr{});
    registry.registerReporter("b", IReporterFactoryPtr{});

    const auto& factories = registry.getFactories();
    EXPECT_EQ(factories.size(), 2u);
    EXPECT_NE(factories.find("a"), factories.end());
    EXPECT_NE(factories.find("b"), factories.end());
}
