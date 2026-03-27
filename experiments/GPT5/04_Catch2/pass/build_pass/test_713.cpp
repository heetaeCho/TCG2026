// File: tests/config_listTags_tests_713.cpp

#include <gtest/gtest.h>
#include "catch2/catch_config.hpp"  // Adjust include path if needed

using Catch::Config;
using Catch::ConfigData;

//
// Tests focus solely on the observable behavior of Config::listTags().
//

// Normal operation: default-constructed Config should reflect default settings.
TEST(Config_ListTagsTest_713, DefaultIsFalse_713) {
    // Arrange
    Config cfg;  // Uses default-constructed internal ConfigData

    // Act
    const bool result = cfg.listTags();

    // Assert
    // Based on public defaults in ConfigData, listTags starts as false.
    EXPECT_FALSE(result);
}

// Normal operation: constructed with listTags = true should return true.
TEST(Config_ListTagsTest_713, ReturnsTrueWhenConfiguredTrue_713) {
    // Arrange
    ConfigData data;
    data.listTags = true;

    const Config cfg(data); // construct from data

    // Act
    const bool result = cfg.listTags();

    // Assert
    EXPECT_TRUE(result);
}

// Normal operation: constructed with listTags = false should return false.
TEST(Config_ListTagsTest_713, ReturnsFalseWhenConfiguredFalse_713) {
    // Arrange
    ConfigData data;
    data.listTags = false;

    const Config cfg(data);

    // Act
    const bool result = cfg.listTags();

    // Assert
    EXPECT_FALSE(result);
}

// Boundary/interaction check: unrelated flags should not affect listTags() result.
TEST(Config_ListTagsTest_713, UnrelatedFlagsDoNotAffectListTags_713) {
    // Case A: listTags=false, others true
    {
        ConfigData dataA;
        dataA.listTags = false;
        dataA.listTests = true;
        dataA.listReporters = true;
        dataA.listListeners = true;

        const Config cfgA(dataA);
        EXPECT_FALSE(cfgA.listTags());
    }

    // Case B: listTags=true, others false
    {
        ConfigData dataB;
        dataB.listTags = true;
        dataB.listTests = false;
        dataB.listReporters = false;
        dataB.listListeners = false;

        const Config cfgB(dataB);
        EXPECT_TRUE(cfgB.listTags());
    }
}
