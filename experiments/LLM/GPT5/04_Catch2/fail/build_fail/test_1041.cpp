// File: tests/section_tracker_addNextFilters_1041_tests.cpp

#include <gtest/gtest.h>
#include <vector>
#include <string>

// Include the real SectionTracker interface.
// Adjust the path if your project uses the amalgamated header instead.
#include "catch2/internal/catch_test_case_tracker.hpp"

using Catch::StringRef;
using Catch::TestCaseTracking::SectionTracker;

class SectionTrackerTest_1041 : public ::testing::Test {
protected:
    // If your SectionTracker requires special construction (e.g., NameAndLocation/TrackerContext),
    // replace this with whatever factory/helper you already use in your test suite to obtain a
    // usable SectionTracker instance. The tests only rely on the public API (addNextFilters/getFilters).
    SectionTracker tracker_;
};

// [Normal] Adds all elements except the first when size > 1
TEST_F(SectionTrackerTest_1041, AddsAllButFirst_WhenInputHasMultiple_1041) {
    std::vector<StringRef> input{ StringRef("one"), StringRef("two"), StringRef("three") };

    tracker_.addNextFilters(input);

    const auto& out = tracker_.getFilters();
    ASSERT_EQ(out.size(), 2u);                // only the tail should be appended
    EXPECT_EQ(std::string(out[0]), "two");
    EXPECT_EQ(std::string(out[1]), "three");
}

// [Boundary] No-op when given an empty vector
TEST_F(SectionTrackerTest_1041, NoChange_WhenInputIsEmpty_1041) {
    std::vector<StringRef> input{};

    tracker_.addNextFilters(input);

    const auto& out = tracker_.getFilters();
    EXPECT_TRUE(out.empty());
}

// [Boundary] No-op when given a single element
TEST_F(SectionTrackerTest_1041, NoChange_WhenInputHasSingleElement_1041) {
    std::vector<StringRef> input{ StringRef("only") };

    tracker_.addNextFilters(input);

    const auto& out = tracker_.getFilters();
    EXPECT_TRUE(out.empty());
}

// [Sequencing] Multiple calls append in order, always skipping the first of each call
TEST_F(SectionTrackerTest_1041, AppendsTailAcrossMultipleCalls_InOrder_1041) {
    std::vector<StringRef> first { StringRef("a"), StringRef("b") };                  // tail: b
    std::vector<StringRef> second{ StringRef("x"), StringRef("y"), StringRef("z") };  // tail: y, z

    tracker_.addNextFilters(first);
    tracker_.addNextFilters(second);

    const auto& out = tracker_.getFilters();
    ASSERT_EQ(out.size(), 3u);
    EXPECT_EQ(std::string(out[0]), "b");
    EXPECT_EQ(std::string(out[1]), "y");
    EXPECT_EQ(std::string(out[2]), "z");
}

// [Robustness] Passing temporaries works (lifetime independent of caller)
// Verifies observable result is identical when using rvalues.
TEST_F(SectionTrackerTest_1041, AcceptsRvalueVector_AndStoresTails_1041) {
    tracker_.addNextFilters(std::vector<StringRef>{ StringRef("head"), StringRef("tail1"), StringRef("tail2") });

    const auto& out = tracker_.getFilters();
    ASSERT_EQ(out.size(), 2u);
    EXPECT_EQ(std::string(out[0]), "tail1");
    EXPECT_EQ(std::string(out[1]), "tail2");
}
