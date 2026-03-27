// File: tests/section_tracker_addInitialFilters_1040_tests.cpp

#include <gtest/gtest.h>
#include <vector>
#include <string>

// If your project exposes SectionTracker via the unified amalgamated include,
// prefer that (it already defines StringRef, SectionTracker, etc.).
// Otherwise, include the regular header.
#include "Catch2/extras/catch_amalgamated.hpp"
// Or, if you don’t use the amalgamated header in tests, use:
// #include "Catch2/src/catch2/internal/catch_test_case_tracker.hpp"

using Catch::StringRef;
using Catch::TestCaseTracking::SectionTracker;

class SectionTracker_AddInitialFilters_Test_1040 : public ::testing::Test {
protected:
    // We treat SectionTracker as a black box and only use its public API.
    // The Known Dependencies declare getFilters(), which we use as the
    // observable surface to verify addInitialFilters effects.
    SectionTracker sut_{/* default-constructible in amalgamated header */};
};

// Normal operation: non-empty input inserts 2 leading placeholders
// (root + test case) followed by the provided filters.
TEST_F(SectionTracker_AddInitialFilters_Test_1040,
       AddsPlaceholdersAndCopiesInput_1040) {
    std::vector<std::string> input{"alpha", "beta"};

    sut_.addInitialFilters(input);

    const auto& filters = sut_.getFilters();
    ASSERT_EQ(filters.size(), 2u + input.size());

    // The first two entries are placeholders (empty StringRefs)
    EXPECT_TRUE(filters[0].empty());
    EXPECT_TRUE(filters[1].empty());

    // Then the provided filters (content equality only — observable behavior)
    EXPECT_TRUE(filters[2] == "alpha");
    EXPECT_TRUE(filters[3] == "beta");
}

// Boundary condition: empty input should be a no-op (no filters added).
TEST_F(SectionTracker_AddInitialFilters_Test_1040,
       EmptyInputDoesNothing_1040) {
    std::vector<std::string> empty;

    sut_.addInitialFilters(empty);

    const auto& filters = sut_.getFilters();
    EXPECT_TRUE(filters.empty());
}

// Boundary-ish / sequence behavior (still observable):
// Calling with non-empty input multiple times appends two placeholders
// and then the new filters each time.
TEST_F(SectionTracker_AddInitialFilters_Test_1040,
       MultipleCallsAppendPlaceholdersAndInputs_1040) {
    std::vector<std::string> first{"one"};
    std::vector<std::string> second{"two", "three"};

    sut_.addInitialFilters(first);
    sut_.addInitialFilters(second);

    const auto& filters = sut_.getFilters();

    // After first call: [ "", "", "one" ]  -> size 3
    // After second call appended: [ "", "", "one", "", "", "two", "three" ] -> size 7
    ASSERT_EQ(filters.size(), 7u);

    // First call’s placeholders and item
    EXPECT_TRUE(filters[0].empty());
    EXPECT_TRUE(filters[1].empty());
    EXPECT_TRUE(filters[2] == "one");

    // Second call’s placeholders and items
    EXPECT_TRUE(filters[3].empty());
    EXPECT_TRUE(filters[4].empty());
    EXPECT_TRUE(filters[5] == "two");
    EXPECT_TRUE(filters[6] == "three");
}

// Input robustness: handles strings requiring no special treatment (ASCII).
// This is still observable purely via the returned filter contents.
TEST_F(SectionTracker_AddInitialFilters_Test_1040,
       PreservesExactFilterText_1040) {
    std::vector<std::string> input{
        "top/level",
        "nested::section",
        "[tagged]"
    };

    sut_.addInitialFilters(input);

    const auto& filters = sut_.getFilters();
    ASSERT_EQ(filters.size(), 2u + input.size());

    EXPECT_TRUE(filters[2] == "top/level");
    EXPECT_TRUE(filters[3] == "nested::section");
    EXPECT_TRUE(filters[4] == "[tagged]");
}
