// File: tests/config_get_reporter_specs_718.cpp

#include <gtest/gtest.h>
#include <type_traits>

// Include the public headers that declare Config and ConfigData
// (adjust include paths to your project layout if needed)
#include "catch2/catch_config.hpp"

using namespace Catch;

class ConfigGetReporterSpecsTest_718 : public ::testing::Test {};

// [718] Empty vector: getter returns an empty vector reference, and the reference
// is stable across multiple calls.
TEST_F(ConfigGetReporterSpecsTest_718, ReturnsEmptyVectorAndStableReference_718) {
    ConfigData data;                // by default: reporterSpecifications is empty
    Config cfg{data};

    auto const& first = cfg.getReporterSpecs();
    auto const& second = cfg.getReporterSpecs();

    EXPECT_TRUE(first.empty());
    EXPECT_EQ(&first, &second) << "getReporterSpecs() should return the same reference across calls";
}

// [718] Non-empty vector: size is preserved and accessible via the getter.
// We do not rely on ReporterSpec internals; we only check observable size.
TEST_F(ConfigGetReporterSpecsTest_718, ReturnsNonEmptyVectorWithCorrectSize_718) {
    ConfigData data;

    // We avoid asserting anything about ReporterSpec internals — only that
    // entries exist and count matches. If ReporterSpec is default-constructible,
    // this will compile; otherwise, replace with valid construction per your codebase.
    data.reporterSpecifications.emplace_back();
    data.reporterSpecifications.emplace_back();

    Config cfg{data};

    auto const& specs = cfg.getReporterSpecs();
    EXPECT_EQ(specs.size(), 2u);
}

// [718] Independence from constructor input after construction:
// Mutating the original ConfigData after constructing Config must not affect
// the already-constructed Config (observable via size).
TEST_F(ConfigGetReporterSpecsTest_718, DoesNotTrackExternalMutationsAfterConstruction_718) {
    ConfigData data;
    data.reporterSpecifications.emplace_back(); // start with 1

    Config cfg{data};

    // Mutate original data AFTER cfg was constructed
    data.reporterSpecifications.emplace_back();
    data.reporterSpecifications.emplace_back();

    auto const& specs = cfg.getReporterSpecs();
    EXPECT_EQ(specs.size(), 1u) << "Config should hold its own state, not track later external mutations";
}

// [718] Compile-time check: getter type is a const reference (no mutation via API).
TEST_F(ConfigGetReporterSpecsTest_718, GetterReturnsConstReferenceType_718) {
    using GetterType = decltype(std::declval<const Config>().getReporterSpecs());
    static_assert(std::is_reference<GetterType>::value, "Getter should return a reference");
    static_assert(std::is_const<std::remove_reference_t<GetterType>>::value,
                  "Getter should return a reference to const");
    SUCCEED();
}
