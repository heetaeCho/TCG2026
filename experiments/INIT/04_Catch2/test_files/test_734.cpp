// File: tests/config_shardIndex_734_tests.cpp

#include <gtest/gtest.h>
#include <limits>
#include "catch2/catch_config.hpp"

using Catch::Config;
using Catch::ConfigData;

TEST(ConfigShardIndexTest_734, ReturnsDefaultZero_734) {
    // Default-constructed Config should report default shardIndex (0)
    Config cfg{ConfigData{}};
    EXPECT_EQ(cfg.shardIndex(), static_cast<unsigned int>(0));
}

TEST(ConfigShardIndexTest_734, ReturnsProvidedIndex_734) {
    // When shardIndex is explicitly set, the same value should be observable
    ConfigData data;
    data.shardIndex = 5u;
    Config cfg{data};
    EXPECT_EQ(cfg.shardIndex(), 5u);
}

TEST(ConfigShardIndexTest_734, IndependentOfShardCount_734) {
    // shardIndex() should report the index regardless of shardCount value
    ConfigData data;
    data.shardCount = 10u;
    data.shardIndex = 3u;
    Config cfg{data};
    EXPECT_EQ(cfg.shardIndex(), 3u);
}

TEST(ConfigShardIndexTest_734, DoesNotAliasInputAfterConstruction_734) {
    // Modifying the original ConfigData after constructing Config
    // must not change the observed shardIndex() result.
    ConfigData data;
    data.shardIndex = 2u;
    Config cfg{data};

    // Mutate the original source object post-construction
    data.shardIndex = 7u;

    // Observable behavior should remain as initially constructed
    EXPECT_EQ(cfg.shardIndex(), 2u);
}

TEST(ConfigShardIndexTest_734, HandlesMaxUnsignedInt_734) {
    // Boundary: largest representable unsigned int should be preserved
    ConfigData data;
    data.shardIndex = std::numeric_limits<unsigned int>::max();
    Config cfg{data};
    EXPECT_EQ(cfg.shardIndex(), std::numeric_limits<unsigned int>::max());
}
