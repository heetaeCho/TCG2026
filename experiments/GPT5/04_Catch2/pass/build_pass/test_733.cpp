// File: tests/config_shardCount_733_tests.cpp

#include <gtest/gtest.h>
#include <limits>
#include "catch2/catch_config.hpp"  // Adjust include path if needed

using namespace Catch;

class ConfigShardCountTest_733 : public ::testing::Test {
protected:
    static Config makeWithShardCount(unsigned int count) {
        ConfigData data;
        data.shardCount = count;
        return Config{data};
    }
};

// [Normal] Default-constructed ConfigData should yield the documented default (1)
TEST_F(ConfigShardCountTest_733, DefaultIsOne_733) {
    ConfigData data;               // uses default member initializers
    Config cfg{data};
    EXPECT_EQ(cfg.shardCount(), 1u);
}

// [Normal] Returns the value provided at construction
TEST_F(ConfigShardCountTest_733, ReturnsValueProvidedInCtor_733) {
    Config cfg = makeWithShardCount(8u);
    EXPECT_EQ(cfg.shardCount(), 8u);
}

// [Boundary] Zero — if configured to 0, the getter should return 0 (purely observable)
TEST_F(ConfigShardCountTest_733, ReturnsZeroIfConfiguredZero_733) {
    Config cfg = makeWithShardCount(0u);
    EXPECT_EQ(cfg.shardCount(), 0u);
}

// [Boundary] Max unsigned int
TEST_F(ConfigShardCountTest_733, ReturnsMaxUnsignedInt_733) {
    const unsigned int maxu = std::numeric_limits<unsigned int>::max();
    Config cfg = makeWithShardCount(maxu);
    EXPECT_EQ(cfg.shardCount(), maxu);
}

// [Behavior] Independence from original ConfigData after construction
TEST_F(ConfigShardCountTest_733, IndependenceFromOriginalConfigData_733) {
    ConfigData data;
    data.shardCount = 3u;
    Config cfg{data};

    // Mutate the original data after constructing Config — should not affect cfg
    data.shardCount = 42u;

    EXPECT_EQ(cfg.shardCount(), 3u);
}
