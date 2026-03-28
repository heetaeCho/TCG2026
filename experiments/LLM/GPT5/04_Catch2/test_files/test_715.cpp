// File: tests/config_listeners_715_tests.cpp

#include <gtest/gtest.h>

// Prefer including the real header if available in your project layout.
// Adjust include path as needed.
#include "catch2/catch_config.hpp"

using namespace Catch;

// --- Tests ---

// Verifies: Default (unset) state returns false
TEST(Config_ListListenersTest_715, ReturnsFalseWhenUnset_715) {
    ConfigData data;              // listListeners defaults to false per interface defaults
    data.listListeners = false;   // explicit for clarity
    Config cfg{ data };

    EXPECT_FALSE(cfg.listListeners());
}

// Verifies: Explicitly setting listListeners to true is reflected by the accessor
TEST(Config_ListListenersTest_715, ReturnsTrueWhenSet_715) {
    ConfigData data;
    data.listListeners = true;
    Config cfg{ data };

    EXPECT_TRUE(cfg.listListeners());
}

// Verifies: Method is callable on const instances (const-correctness of the interface)
TEST(Config_ListListenersTest_715, ConstCorrectness_715) {
    ConfigData data;
    data.listListeners = true;
    const Config cfg{ data };

    // Should compile and return the observable value on a const object
    EXPECT_TRUE(cfg.listListeners());
}

// Verifies: Value observed is independent of subsequent external mutations
// (i.e., constructing Config from ConfigData captures the needed state)
TEST(Config_ListListenersTest_715, IndependenceFromSourceAfterConstruction_715) {
    ConfigData source;
    source.listListeners = true;

    Config cfg{ source };
    // Mutate the original after construction; observable behavior of cfg should not change
    source.listListeners = false;

    EXPECT_TRUE(cfg.listListeners());
}

// Verifies: Unrelated flags do not affect listListeners observable result
TEST(Config_ListListenersTest_715, UnrelatedFlagsDoNotAffectResult_715) {
    ConfigData data;
    // Flip a bunch of other flags; keep listListeners false
    data.listTests = true;
    data.listTags = true;
    data.listReporters = true;
    data.showHelp = true;
    data.showInvisibles = true;
    data.allowZeroTests = true;
    data.listListeners = false; // the flag under test

    Config cfg{ data };
    EXPECT_FALSE(cfg.listListeners());
}
