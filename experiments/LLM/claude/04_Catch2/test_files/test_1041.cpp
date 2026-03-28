#include <gtest/gtest.h>
#include <vector>
#include <string>

// Include necessary Catch2 headers
#include "catch2/internal/catch_test_case_tracker.hpp"
#include "catch2/internal/catch_string_ref.hpp"

using namespace Catch;
using namespace Catch::TestCaseTracking;

class SectionTrackerTest_1041 : public ::testing::Test {
protected:
    TrackerContext ctx;
    
    SectionTracker& createTracker(const std::string& name = "test_section") {
        // Acquire a root tracker first, then a section tracker
        auto& rootTracker = ctx.startRun();
        // Use acquire to get a SectionTracker
        NameAndLocationRef nameAndLoc(name, SourceLineInfo("test_file.cpp", 1));
        return SectionTracker::acquire(ctx, nameAndLoc);
    }
};

// Test that addNextFilters with empty vector does not add any filters
TEST_F(SectionTrackerTest_1041, AddNextFiltersEmptyVector_1041) {
    auto& tracker = createTracker();
    std::vector<StringRef> emptyFilters;
    
    tracker.addNextFilters(emptyFilters);
    
    EXPECT_TRUE(tracker.getFilters().empty());
}

// Test that addNextFilters with single element does not add any filters (size <= 1)
TEST_F(SectionTrackerTest_1041, AddNextFiltersSingleElement_1041) {
    auto& tracker = createTracker();
    std::vector<StringRef> singleFilter = { StringRef("filter1") };
    
    tracker.addNextFilters(singleFilter);
    
    EXPECT_TRUE(tracker.getFilters().empty());
}

// Test that addNextFilters with two elements adds only the second element
TEST_F(SectionTrackerTest_1041, AddNextFiltersTwoElements_1041) {
    auto& tracker = createTracker();
    std::vector<StringRef> filters = { StringRef("filter0"), StringRef("filter1") };
    
    tracker.addNextFilters(filters);
    
    auto const& result = tracker.getFilters();
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], StringRef("filter1"));
}

// Test that addNextFilters with multiple elements adds all except the first
TEST_F(SectionTrackerTest_1041, AddNextFiltersMultipleElements_1041) {
    auto& tracker = createTracker();
    std::vector<StringRef> filters = { StringRef("skip"), StringRef("a"), StringRef("b"), StringRef("c") };
    
    tracker.addNextFilters(filters);
    
    auto const& result = tracker.getFilters();
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], StringRef("a"));
    EXPECT_EQ(result[1], StringRef("b"));
    EXPECT_EQ(result[2], StringRef("c"));
}

// Test that calling addNextFilters multiple times accumulates filters
TEST_F(SectionTrackerTest_1041, AddNextFiltersAccumulates_1041) {
    auto& tracker = createTracker();
    std::vector<StringRef> filters1 = { StringRef("skip1"), StringRef("x") };
    std::vector<StringRef> filters2 = { StringRef("skip2"), StringRef("y"), StringRef("z") };
    
    tracker.addNextFilters(filters1);
    tracker.addNextFilters(filters2);
    
    auto const& result = tracker.getFilters();
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], StringRef("x"));
    EXPECT_EQ(result[1], StringRef("y"));
    EXPECT_EQ(result[2], StringRef("z"));
}

// Test that addNextFilters with exactly size 1 boundary does nothing
TEST_F(SectionTrackerTest_1041, AddNextFiltersBoundarySizeOne_1041) {
    auto& tracker = createTracker();
    std::vector<StringRef> filters = { StringRef("only_one") };
    
    tracker.addNextFilters(filters);
    tracker.addNextFilters(filters);
    tracker.addNextFilters(filters);
    
    EXPECT_TRUE(tracker.getFilters().empty());
}

// Test isSectionTracker returns true
TEST_F(SectionTrackerTest_1041, IsSectionTrackerReturnsTrue_1041) {
    auto& tracker = createTracker();
    EXPECT_TRUE(tracker.isSectionTracker());
}

// Test trimmedName returns the trimmed section name
TEST_F(SectionTrackerTest_1041, TrimmedNameReturnsName_1041) {
    auto& tracker = createTracker("test_section");
    StringRef trimmed = tracker.trimmedName();
    EXPECT_EQ(trimmed, StringRef("test_section"));
}

// Test trimmedName trims whitespace
TEST_F(SectionTrackerTest_1041, TrimmedNameTrimsWhitespace_1041) {
    auto& tracker = createTracker("  spaced_name  ");
    StringRef trimmed = tracker.trimmedName();
    EXPECT_EQ(trimmed, StringRef("spaced_name"));
}
