// File: tests/config_getSectionsToRun_717_tests.cpp

#include <gtest/gtest.h>
#include <string>
#include <vector>

// Include the public interface under test.
#include "catch2/catch_config.hpp"

using Catch::Config;
using Catch::ConfigData;

namespace {

TEST(ConfigGetSectionsToRunTest_717, EmptyWhenDefaultConstructed_717) {
    // Given: default-initialized ConfigData with no sections set
    ConfigData data;
    Config cfg{data};

    // Then: getSectionsToRun should be empty
    const auto& sections = cfg.getSectionsToRun();
    EXPECT_TRUE(sections.empty());
    EXPECT_EQ(sections.size(), 0u);
}

TEST(ConfigGetSectionsToRunTest_717, ReturnsProvidedSectionsPreservingOrderAndDuplicates_717) {
    // Given: sections set (including duplicates and specific order)
    ConfigData data;
    data.sectionsToRun = {"secA", "secB", "secA", "secC"};
    Config cfg{data};

    // Then: returned vector matches exactly (order + duplicates preserved)
    const auto& sections = cfg.getSectionsToRun();
    ASSERT_EQ(sections.size(), 4u);
    EXPECT_EQ(sections[0], "secA");
    EXPECT_EQ(sections[1], "secB");
    EXPECT_EQ(sections[2], "secA");
    EXPECT_EQ(sections[3], "secC");
}

TEST(ConfigGetSectionsToRunTest_717, ReferenceIsStableAcrossCalls_717) {
    // Given: some non-empty sections
    ConfigData data;
    data.sectionsToRun = {"alpha", "beta"};
    Config cfg{data};

    // When: we obtain references from multiple calls
    const auto& ref1 = cfg.getSectionsToRun();
    const auto& ref2 = cfg.getSectionsToRun();

    // Then: both references refer to the same underlying object
    EXPECT_EQ(&ref1, &ref2);

    // And: contents remain intact
    ASSERT_EQ(ref1.size(), 2u);
    EXPECT_EQ(ref1[0], "alpha");
    EXPECT_EQ(ref1[1], "beta");
}

TEST(ConfigGetSectionsToRunTest_717, UnaffectedByExternalMutationAfterConstruction_717) {
    // Given: start with 1 section in the input ConfigData
    ConfigData input;
    input.sectionsToRun = {"initial"};
    Config cfg{input};

    // When: mutate the original ConfigData AFTER constructing Config
    input.sectionsToRun.push_back("added-later");
    input.sectionsToRun[0] = "modified";

    // Then: Config's returned sections reflect the state at construction (observable behavior)
    const auto& sections = cfg.getSectionsToRun();
    ASSERT_EQ(sections.size(), 1u);
    EXPECT_EQ(sections[0], "initial");
}

TEST(ConfigGetSectionsToRunTest_717, HandlesLargeNumberOfSections_717) {
    // Given: a large list of sections (boundary-ish case)
    ConfigData data;
    constexpr std::size_t N = 1000;
    data.sectionsToRun.reserve(N);
    for (std::size_t i = 0; i < N; ++i) {
        data.sectionsToRun.push_back("section_" + std::to_string(i));
    }
    Config cfg{data};

    // Then: size matches and spot-check a few positions for order correctness
    const auto& sections = cfg.getSectionsToRun();
    ASSERT_EQ(sections.size(), N);
    EXPECT_EQ(sections.front(), "section_0");
    EXPECT_EQ(sections[1], "section_1");
    EXPECT_EQ(sections[123], "section_123");
    EXPECT_EQ(sections[998], "section_998");
    EXPECT_EQ(sections.back(), "section_999");
}

} // namespace
