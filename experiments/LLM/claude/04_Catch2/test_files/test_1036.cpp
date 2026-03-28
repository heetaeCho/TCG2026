#include <catch2/internal/catch_test_case_tracker.hpp>
#include <catch2/catch_test_macros.hpp>
#include <gtest/gtest.h>
#include <string>
#include <vector>

using namespace Catch;
using namespace Catch::TestCaseTracking;

class SectionTrackerTest_1036 : public ::testing::Test {
protected:
    void SetUp() override {
        ctx_ = std::make_unique<TrackerContext>();
    }

    void TearDown() override {
        ctx_.reset();
    }

    TrackerContext& ctx() { return *ctx_; }

    // Helper to set up root tracker and get a SectionTracker
    SectionTracker& createSectionTracker(const std::string& name) {
        // First we need a root tracker in the context
        ctx().startRun();
        ctx().startCycle();
        auto& root = ctx().currentTracker();
        
        NameAndLocationRef ref(StringRef(name), SourceLineInfo("test_file.cpp", 1));
        return SectionTracker::acquire(ctx(), ref);
    }

    std::unique_ptr<TrackerContext> ctx_;
};

// Test: SectionTracker with no filters should delegate to TrackerBase::isComplete
TEST_F(SectionTrackerTest_1036, IsCompleteNoFilters_1036) {
    auto& section = createSectionTracker("TestSection");
    // With no filters, isComplete should delegate to TrackerBase::isComplete
    // A freshly created section tracker that hasn't been opened should reflect base behavior
    bool result = section.isComplete();
    // We just verify it doesn't crash and returns a bool
    // Fresh tracker should not be complete yet (hasn't been opened/closed)
    EXPECT_FALSE(result);
}

// Test: SectionTracker isSectionTracker returns true
TEST_F(SectionTrackerTest_1036, IsSectionTracker_1036) {
    auto& section = createSectionTracker("TestSection");
    EXPECT_TRUE(section.isSectionTracker());
}

// Test: trimmedName returns the trimmed name
TEST_F(SectionTrackerTest_1036, TrimmedName_1036) {
    auto& section = createSectionTracker("TestSection");
    StringRef trimmed = section.trimmedName();
    EXPECT_EQ(std::string(trimmed), "TestSection");
}

// Test: trimmedName trims whitespace
TEST_F(SectionTrackerTest_1036, TrimmedNameWithWhitespace_1036) {
    auto& section = createSectionTracker("  TestSection  ");
    StringRef trimmed = section.trimmedName();
    EXPECT_EQ(std::string(trimmed), "TestSection");
}

// Test: getFilters returns empty by default
TEST_F(SectionTrackerTest_1036, GetFiltersEmptyByDefault_1036) {
    auto& section = createSectionTracker("TestSection");
    auto const& filters = section.getFilters();
    EXPECT_TRUE(filters.empty());
}

// Test: addInitialFilters populates the filters
TEST_F(SectionTrackerTest_1036, AddInitialFilters_1036) {
    auto& section = createSectionTracker("TestSection");
    std::vector<std::string> filters = {"filter1", "filter2"};
    section.addInitialFilters(filters);
    auto const& storedFilters = section.getFilters();
    EXPECT_EQ(storedFilters.size(), 2u);
}

// Test: isComplete returns true when filters are non-empty and name is NOT in filters
TEST_F(SectionTrackerTest_1036, IsCompleteWithNonMatchingFilters_1036) {
    auto& section = createSectionTracker("TestSection");
    std::vector<std::string> filters = {"OtherSection"};
    section.addInitialFilters(filters);
    // Since trimmed name "TestSection" is not in filters, isComplete should return true
    EXPECT_TRUE(section.isComplete());
}

// Test: isComplete with matching filter delegates to base
TEST_F(SectionTrackerTest_1036, IsCompleteWithMatchingFilter_1036) {
    auto& section = createSectionTracker("TestSection");
    std::vector<std::string> filters = {"TestSection"};
    section.addInitialFilters(filters);
    // trimmed name "TestSection" IS in filters, so it delegates to TrackerBase::isComplete
    // Fresh tracker should not be complete
    EXPECT_FALSE(section.isComplete());
}

// Test: isComplete with empty string filter delegates to base
TEST_F(SectionTrackerTest_1036, IsCompleteWithEmptyStringFilter_1036) {
    auto& section = createSectionTracker("TestSection");
    std::vector<std::string> filters = {""};
    section.addInitialFilters(filters);
    // m_filters[0] is empty → delegates to TrackerBase::isComplete
    EXPECT_FALSE(section.isComplete());
}

// Test: addNextFilters works
TEST_F(SectionTrackerTest_1036, AddNextFilters_1036) {
    auto& section = createSectionTracker("TestSection");
    std::vector<StringRef> filters = {StringRef("next1"), StringRef("next2")};
    section.addNextFilters(filters);
    auto const& storedFilters = section.getFilters();
    EXPECT_EQ(storedFilters.size(), 2u);
}

// Test: acquire returns same tracker for same name and location
TEST_F(SectionTrackerTest_1036, AcquireSameTrackerForSameNameAndLocation_1036) {
    ctx().startRun();
    ctx().startCycle();
    
    NameAndLocationRef ref(StringRef("Section1"), SourceLineInfo("file.cpp", 10));
    auto& section1 = SectionTracker::acquire(ctx(), ref);
    auto& section2 = SectionTracker::acquire(ctx(), ref);
    
    EXPECT_EQ(&section1, &section2);
}

// Test: isComplete with multiple filters, one matching
TEST_F(SectionTrackerTest_1036, IsCompleteWithMultipleFiltersOneMatching_1036) {
    auto& section = createSectionTracker("TestSection");
    std::vector<std::string> filters = {"Other", "TestSection", "Another"};
    section.addInitialFilters(filters);
    // "TestSection" is found in filters → delegates to base → not complete (fresh)
    EXPECT_FALSE(section.isComplete());
}

// Test: isComplete with multiple filters, none matching
TEST_F(SectionTrackerTest_1036, IsCompleteWithMultipleFiltersNoneMatching_1036) {
    auto& section = createSectionTracker("TestSection");
    std::vector<std::string> filters = {"Other", "Another", "YetAnother"};
    section.addInitialFilters(filters);
    // "TestSection" not found → returns true
    EXPECT_TRUE(section.isComplete());
}

// Test: tryOpen on a section tracker
TEST_F(SectionTrackerTest_1036, TryOpen_1036) {
    auto& section = createSectionTracker("TestSection");
    // Should not throw
    EXPECT_NO_THROW(section.tryOpen());
}

// Test: Section opened and closed becomes complete
TEST_F(SectionTrackerTest_1036, OpenAndCloseBecomesComplete_1036) {
    ctx().startRun();
    ctx().startCycle();
    
    NameAndLocationRef ref(StringRef("Section1"), SourceLineInfo("file.cpp", 10));
    auto& section = SectionTracker::acquire(ctx(), ref);
    
    section.tryOpen();
    section.open();
    section.close();
    
    // After open and close, TrackerBase::isComplete() should return true
    // With no filters, isComplete delegates to base
    EXPECT_TRUE(section.isComplete());
}
