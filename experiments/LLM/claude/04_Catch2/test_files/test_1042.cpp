#include "catch2/internal/catch_test_case_tracker.hpp"
#include "catch2/catch_test_macros.hpp"
#include <gtest/gtest.h>
#include <string>
#include <vector>

using namespace Catch;
using namespace Catch::TestCaseTracking;

class SectionTrackerTest_1042 : public ::testing::Test {
protected:
    TrackerContext ctx;
    
    void SetUp() override {
        // TrackerContext needs a root tracker to work with
    }
};

TEST_F(SectionTrackerTest_1042, IsSectionTrackerReturnsTrue_1042) {
    // Acquire creates or retrieves a SectionTracker from context
    // First we need a root section in the context
    auto& rootSection = SectionTracker::acquire(ctx, NameAndLocationRef("root", SourceLineInfo("file", 1)));
    
    EXPECT_TRUE(rootSection.isSectionTracker());
}

TEST_F(SectionTrackerTest_1042, TrimmedNameReturnsTrimmedVersion_1042) {
    auto& tracker = SectionTracker::acquire(ctx, NameAndLocationRef("  hello  ", SourceLineInfo("file", 1)));
    
    StringRef trimmed = tracker.trimmedName();
    EXPECT_EQ(std::string(trimmed.data(), trimmed.size()), "hello");
}

TEST_F(SectionTrackerTest_1042, TrimmedNameNoWhitespace_1042) {
    auto& tracker = SectionTracker::acquire(ctx, NameAndLocationRef("nowhitespace", SourceLineInfo("file", 2)));
    
    StringRef trimmed = tracker.trimmedName();
    EXPECT_EQ(std::string(trimmed.data(), trimmed.size()), "nowhitespace");
}

TEST_F(SectionTrackerTest_1042, TrimmedNameOnlyWhitespace_1042) {
    auto& tracker = SectionTracker::acquire(ctx, NameAndLocationRef("   ", SourceLineInfo("file", 3)));
    
    StringRef trimmed = tracker.trimmedName();
    EXPECT_EQ(std::string(trimmed.data(), trimmed.size()), "");
}

TEST_F(SectionTrackerTest_1042, TrimmedNameEmptyString_1042) {
    auto& tracker = SectionTracker::acquire(ctx, NameAndLocationRef("", SourceLineInfo("file", 4)));
    
    StringRef trimmed = tracker.trimmedName();
    EXPECT_EQ(std::string(trimmed.data(), trimmed.size()), "");
}

TEST_F(SectionTrackerTest_1042, TrimmedNameLeadingWhitespace_1042) {
    auto& tracker = SectionTracker::acquire(ctx, NameAndLocationRef("  leading", SourceLineInfo("file", 5)));
    
    StringRef trimmed = tracker.trimmedName();
    EXPECT_EQ(std::string(trimmed.data(), trimmed.size()), "leading");
}

TEST_F(SectionTrackerTest_1042, TrimmedNameTrailingWhitespace_1042) {
    auto& tracker = SectionTracker::acquire(ctx, NameAndLocationRef("trailing  ", SourceLineInfo("file", 6)));
    
    StringRef trimmed = tracker.trimmedName();
    EXPECT_EQ(std::string(trimmed.data(), trimmed.size()), "trailing");
}

TEST_F(SectionTrackerTest_1042, AcquireSameNameReturnsSameTracker_1042) {
    auto& tracker1 = SectionTracker::acquire(ctx, NameAndLocationRef("same", SourceLineInfo("file", 7)));
    auto& tracker2 = SectionTracker::acquire(ctx, NameAndLocationRef("same", SourceLineInfo("file", 7)));
    
    EXPECT_EQ(&tracker1, &tracker2);
}

TEST_F(SectionTrackerTest_1042, GetFiltersInitiallyEmpty_1042) {
    auto& tracker = SectionTracker::acquire(ctx, NameAndLocationRef("filtertest", SourceLineInfo("file", 8)));
    
    auto const& filters = tracker.getFilters();
    EXPECT_TRUE(filters.empty());
}

TEST_F(SectionTrackerTest_1042, AddInitialFiltersStoresFilters_1042) {
    auto& tracker = SectionTracker::acquire(ctx, NameAndLocationRef("filtertest2", SourceLineInfo("file", 9)));
    
    std::vector<std::string> filters = {"filter1", "filter2"};
    tracker.addInitialFilters(filters);
    
    auto const& storedFilters = tracker.getFilters();
    EXPECT_EQ(storedFilters.size(), 2u);
}

TEST_F(SectionTrackerTest_1042, AddNextFiltersStoresFilters_1042) {
    auto& tracker = SectionTracker::acquire(ctx, NameAndLocationRef("filtertest3", SourceLineInfo("file", 10)));
    
    std::vector<StringRef> filters = {StringRef("f1"), StringRef("f2"), StringRef("f3")};
    tracker.addNextFilters(filters);
    
    auto const& storedFilters = tracker.getFilters();
    EXPECT_EQ(storedFilters.size(), 3u);
}

TEST_F(SectionTrackerTest_1042, IsCompleteInitiallyFalse_1042) {
    auto& tracker = SectionTracker::acquire(ctx, NameAndLocationRef("completetest", SourceLineInfo("file", 11)));
    
    // A freshly acquired tracker should not be complete yet
    // (it hasn't been opened and closed)
    EXPECT_FALSE(tracker.isComplete());
}

TEST_F(SectionTrackerTest_1042, TryOpenDoesNotThrow_1042) {
    auto& tracker = SectionTracker::acquire(ctx, NameAndLocationRef("tryopentest", SourceLineInfo("file", 12)));
    
    EXPECT_NO_THROW(tracker.tryOpen());
}
