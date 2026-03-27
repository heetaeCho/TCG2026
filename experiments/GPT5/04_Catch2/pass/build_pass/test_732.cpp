// File: tests/config_rngSeed_tests_732.cpp

#include <gtest/gtest.h>
#include <limits>
#include "catch2/catch_config.hpp"  // Adjust include path if needed

using namespace Catch;

class ConfigRngSeedTest_732 : public ::testing::Test {};

// Normal operation: returns the explicitly provided seed
TEST_F(ConfigRngSeedTest_732, ReturnsExplicitSeed_732) {
    ConfigData data;
    data.rngSeed = static_cast<uint32_t>(123456789u);

    Config cfg{data};
    EXPECT_EQ(cfg.rngSeed(), static_cast<uint32_t>(123456789u));
}

// Boundary condition: zero seed is preserved and returned
TEST_F(ConfigRngSeedTest_732, ReturnsZeroSeed_732) {
    ConfigData data;
    data.rngSeed = static_cast<uint32_t>(0u);

    Config cfg{data};
    EXPECT_EQ(cfg.rngSeed(), static_cast<uint32_t>(0u));
}

// Boundary condition: max uint32_t seed is preserved and returned
TEST_F(ConfigRngSeedTest_732, ReturnsMaxUint32Seed_732) {
    ConfigData data;
    data.rngSeed = std::numeric_limits<uint32_t>::max();

    Config cfg{data};
    EXPECT_EQ(cfg.rngSeed(), std::numeric_limits<uint32_t>::max());
}

// Observable behavior: value is stable across multiple calls
TEST_F(ConfigRngSeedTest_732, ConsistentAcrossCalls_732) {
    ConfigData data;
    data.rngSeed = static_cast<uint32_t>(42u);

    Config cfg{data};
    const auto first = cfg.rngSeed();
    const auto second = cfg.rngSeed();
    EXPECT_EQ(first, second);
}
