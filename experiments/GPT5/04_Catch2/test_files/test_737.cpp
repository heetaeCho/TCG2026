// File: tests/config_abortAfter_737_tests.cpp

#include <gtest/gtest.h>
#include <climits>

// Include the provided headers
// Adjust the include paths below if your project layout differs.
#include "Catch2/src/catch2/catch_config.hpp"

using namespace Catch;

class ConfigAbortAfterTest_737 : public ::testing::Test {};

// Default-constructed Config should reflect ConfigData's default (-1)
TEST_F(ConfigAbortAfterTest_737, DefaultCtor_ReturnsDefaultNegOne_737) {
    Config cfg; // default-constructed
    EXPECT_EQ(cfg.abortAfter(), -1);
}

// Constructed with abortAfter = 0 should return 0
TEST_F(ConfigAbortAfterTest_737, ConstructedWithZero_ReturnsZero_737) {
    ConfigData d;
    d.abortAfter = 0;
    Config cfg(d);
    EXPECT_EQ(cfg.abortAfter(), 0);
}

// Constructed with a small positive value should return that value
TEST_F(ConfigAbortAfterTest_737, ConstructedWithPositive_ReturnsSame_737) {
    ConfigData d;
    d.abortAfter = 3;
    Config cfg(d);
    EXPECT_EQ(cfg.abortAfter(), 3);
}

// Constructed with a negative (non-default) value should return that value
TEST_F(ConfigAbortAfterTest_737, ConstructedWithNegative_ReturnsSame_737) {
    ConfigData d;
    d.abortAfter = -5;
    Config cfg(d);
    EXPECT_EQ(cfg.abortAfter(), -5);
}

// Boundary: INT_MAX should be returned unchanged
TEST_F(ConfigAbortAfterTest_737, ConstructedWithIntMax_ReturnsIntMax_737) {
    ConfigData d;
    d.abortAfter = INT_MAX;
    Config cfg(d);
    EXPECT_EQ(cfg.abortAfter(), INT_MAX);
}

// Boundary: INT_MIN should be returned unchanged
TEST_F(ConfigAbortAfterTest_737, ConstructedWithIntMin_ReturnsIntMin_737) {
    ConfigData d;
    d.abortAfter = INT_MIN;
    Config cfg(d);
    EXPECT_EQ(cfg.abortAfter(), INT_MIN);
}
