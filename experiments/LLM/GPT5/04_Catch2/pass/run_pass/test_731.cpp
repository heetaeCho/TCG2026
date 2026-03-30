// File: tests/config_runOrder_731_tests.cpp

#include <gtest/gtest.h>
#include "catch2/catch_config.hpp"

using namespace Catch;

class ConfigRunOrderTest_731 : public ::testing::Test {};

// [Normal] Default-constructed Config should use the default run order from ConfigData
TEST(ConfigRunOrderTest_731, DefaultIsDeclared_731) {
    const Config cfg; // uses default-initialized ConfigData
    // Observable behavior: runOrder() reflects default in ConfigData
    EXPECT_EQ(cfg.runOrder(), TestRunOrder::Declared);
}

// [Normal] runOrder() should reflect the value provided via constructor-injected ConfigData
TEST(ConfigRunOrderTest_731, CtorPropagatesRunOrder_731) {
    ConfigData data;
    // Choose a distinct (but valid as a value of the enum type) sentinel to
    // ensure we are not accidentally relying on the default.
    const auto sentinel = static_cast<TestRunOrder>(0x7FFFFFFF);

    data.runOrder = sentinel;
    const Config cfg{data};

    EXPECT_EQ(cfg.runOrder(), sentinel);
}

// [Boundary/Const correctness] runOrder() is const and must be callable on const objects
TEST(ConfigRunOrderTest_731, CallableOnConstObject_731) {
    ConfigData data;
    data.runOrder = TestRunOrder::Declared;

    const Config cfg{data}; // const object
    // If this compiles and the value matches, const-correctness is respected
    EXPECT_EQ(cfg.runOrder(), TestRunOrder::Declared);
}
