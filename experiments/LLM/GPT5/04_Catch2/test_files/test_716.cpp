// File: tests/catch_config_getTestsOrTags_716_tests.cpp

#include <gtest/gtest.h>
#include <vector>
#include <string>

// Public headers under test
#include "catch2/catch_config.hpp"

using Catch::Config;
using Catch::ConfigData;

namespace {

TEST(Config_GetTestsOrTags_716, ReturnsEmptyByDefault_716) {
    // Default-constructed Config should have no tests/tags.
    Config cfg;

    const auto& first = cfg.getTestsOrTags();
    const auto& second = cfg.getTestsOrTags();

    EXPECT_TRUE(first.empty());
    // Same reference across repeated calls (observable property).
    EXPECT_EQ(std::addressof(first), std::addressof(second));
}

TEST(Config_GetTestsOrTags_716, ReturnsProvidedValues_716) {
    ConfigData data;
    data.testsOrTags = { "[fast]", "Math/AddsCorrectly", "Parser/*" };

    const Config cfg{ data };

    const auto& out = cfg.getTestsOrTags();
    ASSERT_EQ(out.size(), 3u);
    EXPECT_EQ(out[0], "[fast]");
    EXPECT_EQ(out[1], "Math/AddsCorrectly");
    EXPECT_EQ(out[2], "Parser/*");
}

TEST(Config_GetTestsOrTags_716, PreservesOrderAndDuplicates_716) {
    ConfigData data;
    data.testsOrTags = { "[db]", "Suite/TestA", "[db]" }; // duplicate tag

    const Config cfg{ data };

    const auto& out = cfg.getTestsOrTags();
    ASSERT_EQ(out.size(), 3u);
    EXPECT_EQ(out[0], "[db]");
    EXPECT_EQ(out[1], "Suite/TestA");
    EXPECT_EQ(out[2], "[db]"); // ensure duplicate preserved and in order
}

TEST(Config_GetTestsOrTags_716, IsIndependentFromOriginalConfigData_716) {
    ConfigData data;
    data.testsOrTags = { "A", "B" };

    const Config cfg{ data };

    // Mutate the original source after constructing Config.
    data.testsOrTags.push_back("C");

    // Observable behavior: contents exposed by Config should not change.
    const auto& out = cfg.getTestsOrTags();
    ASSERT_EQ(out.size(), 2u);
    EXPECT_EQ(out[0], "A");
    EXPECT_EQ(out[1], "B");
}

TEST(Config_GetTestsOrTags_716, CallableOnConstObject_716) {
    ConfigData data;
    data.testsOrTags = { "OnlyOne" };

    const Config cfg{ data };    // const object

    const auto& out = cfg.getTestsOrTags(); // method is const
    ASSERT_EQ(out.size(), 1u);
    EXPECT_EQ(out.front(), "OnlyOne");

    // Reference stability across multiple const calls
    const auto& out2 = cfg.getTestsOrTags();
    EXPECT_EQ(std::addressof(out), std::addressof(out2));
}

} // namespace
