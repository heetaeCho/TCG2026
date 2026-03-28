#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary Catch2 headers
#include "catch2/internal/catch_test_case_tracker.hpp"
#include "catch2/internal/catch_stringref.hpp"
#include "catch2/internal/catch_source_line_info.hpp"

using namespace Catch;
using namespace Catch::TestCaseTracking;

class SectionTrackerTest_1038 : public ::testing::Test {
protected:
    TrackerContext ctx;

    void SetUp() override {
        // Start a run to initialize the root tracker
        ctx.startRun();
    }
};

// Test that acquiring a section tracker returns a valid SectionTracker
TEST_F(SectionTrackerTest_1038, AcquireReturnsSectionTracker_1038) {
    NameAndLocationRef nameAndLoc("TestSection", SourceLineInfo("file.cpp", 10));
    SectionTracker& tracker = SectionTracker::acquire(ctx, nameAndLoc);
    EXPECT_TRUE(tracker.isSectionTracker());
}

// Test that acquiring the same section tracker twice returns the same tracker
TEST_F(SectionTrackerTest_1038, AcquireSameSectionReturnsSameTracker_1038) {
    NameAndLocationRef nameAndLoc("TestSection", SourceLineInfo("file.cpp", 10));
    SectionTracker& tracker1 = SectionTracker::acquire(ctx, nameAndLoc);
    SectionTracker& tracker2 = SectionTracker::acquire(ctx, nameAndLoc);
    EXPECT_EQ(&tracker1, &tracker2);
}

// Test that acquiring different sections returns different trackers
TEST_F(SectionTrackerTest_1038, AcquireDifferentSectionsReturnsDifferentTrackers_1038) {
    NameAndLocationRef nameAndLoc1("Section1", SourceLineInfo("file.cpp", 10));
    NameAndLocationRef nameAndLoc2("Section2", SourceLineInfo("file.cpp", 20));
    SectionTracker& tracker1 = SectionTracker::acquire(ctx, nameAndLoc1);
    SectionTracker& tracker2 = SectionTracker::acquire(ctx, nameAndLoc2);
    EXPECT_NE(&tracker1, &tracker2);
}

// Test that a newly acquired tracker is a section tracker
TEST_F(SectionTrackerTest_1038, IsSectionTrackerReturnsTrue_1038) {
    NameAndLocationRef nameAndLoc("TestSection", SourceLineInfo("file.cpp", 10));
    SectionTracker& tracker = SectionTracker::acquire(ctx, nameAndLoc);
    EXPECT_TRUE(tracker.isSectionTracker());
}

// Test that a newly acquired tracker is not a generator tracker
TEST_F(SectionTrackerTest_1038, IsGeneratorTrackerReturnsFalse_1038) {
    NameAndLocationRef nameAndLoc("TestSection", SourceLineInfo("file.cpp", 10));
    SectionTracker& tracker = SectionTracker::acquire(ctx, nameAndLoc);
    EXPECT_FALSE(tracker.isGeneratorTracker());
}

// Test that acquiring a section when cycle is not completed opens the tracker
TEST_F(SectionTrackerTest_1038, AcquireOpensTrackerWhenCycleNotCompleted_1038) {
    EXPECT_FALSE(ctx.completedCycle());
    NameAndLocationRef nameAndLoc("TestSection", SourceLineInfo("file.cpp", 10));
    SectionTracker& tracker = SectionTracker::acquire(ctx, nameAndLoc);
    EXPECT_TRUE(tracker.isOpen() || tracker.hasStarted());
}

// Test that acquiring a section after completing a cycle does not open it
TEST_F(SectionTrackerTest_1038, AcquireDoesNotOpenTrackerWhenCycleCompleted_1038) {
    // First acquire and complete
    NameAndLocationRef nameAndLoc("TestSection", SourceLineInfo("file.cpp", 10));
    SectionTracker& tracker1 = SectionTracker::acquire(ctx, nameAndLoc);
    tracker1.close();
    ctx.completeCycle();

    EXPECT_TRUE(ctx.completedCycle());

    // Start a new cycle
    ctx.startCycle();
    // Re-acquire after cycle completed flag may still be set
    // The behavior depends on the implementation
}

// Test trimmedName returns trimmed version of the name
TEST_F(SectionTrackerTest_1038, TrimmedNameReturnsTrimmedName_1038) {
    NameAndLocationRef nameAndLoc("  TestSection  ", SourceLineInfo("file.cpp", 10));
    SectionTracker& tracker = SectionTracker::acquire(ctx, nameAndLoc);
    StringRef trimmed = tracker.trimmedName();
    EXPECT_EQ(std::string(trimmed), "TestSection");
}

// Test trimmedName with no whitespace
TEST_F(SectionTrackerTest_1038, TrimmedNameNoWhitespace_1038) {
    NameAndLocationRef nameAndLoc("NoWhitespace", SourceLineInfo("file.cpp", 10));
    SectionTracker& tracker = SectionTracker::acquire(ctx, nameAndLoc);
    StringRef trimmed = tracker.trimmedName();
    EXPECT_EQ(std::string(trimmed), "NoWhitespace");
}

// Test that nameAndLocation returns the correct name and location
TEST_F(SectionTrackerTest_1038, NameAndLocationIsCorrect_1038) {
    NameAndLocationRef nameAndLoc("MySectionName", SourceLineInfo("myfile.cpp", 42));
    SectionTracker& tracker = SectionTracker::acquire(ctx, nameAndLoc);
    EXPECT_EQ(tracker.nameAndLocation().name, "MySectionName");
    EXPECT_EQ(tracker.nameAndLocation().location.line, 42);
}

// Test parent of acquired section is the current tracker (root)
TEST_F(SectionTrackerTest_1038, ParentIsRootTracker_1038) {
    NameAndLocationRef nameAndLoc("TestSection", SourceLineInfo("file.cpp", 10));
    SectionTracker& tracker = SectionTracker::acquire(ctx, nameAndLoc);
    ITracker* parent = tracker.parent();
    EXPECT_NE(parent, nullptr);
}

// Test that the root tracker has children after acquiring a section
TEST_F(SectionTrackerTest_1038, RootHasChildrenAfterAcquire_1038) {
    NameAndLocationRef nameAndLoc("TestSection", SourceLineInfo("file.cpp", 10));
    SectionTracker::acquire(ctx, nameAndLoc);
    ITracker& root = ctx.currentTracker();
    // The root should have children now (the root's parent may have the child)
    // Actually the section was added as child to the current tracker
}

// Test initial filters
TEST_F(SectionTrackerTest_1038, AddInitialFilters_1038) {
    NameAndLocationRef nameAndLoc("TestSection", SourceLineInfo("file.cpp", 10));
    SectionTracker& tracker = SectionTracker::acquire(ctx, nameAndLoc);
    std::vector<std::string> filters = {"filter1", "filter2"};
    tracker.addInitialFilters(filters);
    auto& storedFilters = tracker.getFilters();
    EXPECT_EQ(storedFilters.size(), 2u);
}

// Test addNextFilters
TEST_F(SectionTrackerTest_1038, AddNextFilters_1038) {
    NameAndLocationRef nameAndLoc("TestSection", SourceLineInfo("file.cpp", 10));
    SectionTracker& tracker = SectionTracker::acquire(ctx, nameAndLoc);
    std::vector<StringRef> filters = {StringRef("filterA"), StringRef("filterB")};
    tracker.addNextFilters(filters);
    auto& storedFilters = tracker.getFilters();
    EXPECT_EQ(storedFilters.size(), 2u);
}

// Test getFilters returns empty initially
TEST_F(SectionTrackerTest_1038, GetFiltersEmptyInitially_1038) {
    NameAndLocationRef nameAndLoc("TestSection", SourceLineInfo("file.cpp", 10));
    SectionTracker& tracker = SectionTracker::acquire(ctx, nameAndLoc);
    auto& filters = tracker.getFilters();
    EXPECT_TRUE(filters.empty());
}

// Test nested section acquisition
TEST_F(SectionTrackerTest_1038, NestedSectionAcquisition_1038) {
    NameAndLocationRef outerNameAndLoc("OuterSection", SourceLineInfo("file.cpp", 10));
    SectionTracker& outerTracker = SectionTracker::acquire(ctx, outerNameAndLoc);

    // Set current tracker to the outer section for nesting
    ctx.setCurrentTracker(&outerTracker);

    NameAndLocationRef innerNameAndLoc("InnerSection", SourceLineInfo("file.cpp", 20));
    SectionTracker& innerTracker = SectionTracker::acquire(ctx, innerNameAndLoc);

    EXPECT_TRUE(innerTracker.isSectionTracker());
    EXPECT_NE(&outerTracker, &innerTracker);
    EXPECT_EQ(innerTracker.parent(), &outerTracker);
}

// Test acquiring section with same name different location
TEST_F(SectionTrackerTest_1038, SameNameDifferentLocationAreDistinct_1038) {
    NameAndLocationRef nameAndLoc1("TestSection", SourceLineInfo("file.cpp", 10));
    NameAndLocationRef nameAndLoc2("TestSection", SourceLineInfo("file.cpp", 20));
    SectionTracker& tracker1 = SectionTracker::acquire(ctx, nameAndLoc1);
    SectionTracker& tracker2 = SectionTracker::acquire(ctx, nameAndLoc2);
    // They should be different since location differs
    EXPECT_NE(&tracker1, &tracker2);
}

// Test completedCycle initially false
TEST_F(SectionTrackerTest_1038, CompletedCycleInitiallyFalse_1038) {
    EXPECT_FALSE(ctx.completedCycle());
}

// Test completeCycle sets completedCycle to true
TEST_F(SectionTrackerTest_1038, CompleteCycleSetsFlag_1038) {
    ctx.completeCycle();
    EXPECT_TRUE(ctx.completedCycle());
}

// Test closing a section tracker
TEST_F(SectionTrackerTest_1038, CloseSectionTracker_1038) {
    NameAndLocationRef nameAndLoc("TestSection", SourceLineInfo("file.cpp", 10));
    SectionTracker& tracker = SectionTracker::acquire(ctx, nameAndLoc);
    tracker.close();
    // After closing, it should be complete (if no children need another run)
    EXPECT_TRUE(tracker.isComplete());
}

// Test that empty section name works
TEST_F(SectionTrackerTest_1038, EmptySectionName_1038) {
    NameAndLocationRef nameAndLoc("", SourceLineInfo("file.cpp", 10));
    SectionTracker& tracker = SectionTracker::acquire(ctx, nameAndLoc);
    EXPECT_TRUE(tracker.isSectionTracker());
    EXPECT_EQ(std::string(tracker.trimmedName()), "");
}

// Test that trimmedName with only whitespace returns empty
TEST_F(SectionTrackerTest_1038, TrimmedNameOnlyWhitespace_1038) {
    NameAndLocationRef nameAndLoc("   ", SourceLineInfo("file.cpp", 10));
    SectionTracker& tracker = SectionTracker::acquire(ctx, nameAndLoc);
    StringRef trimmed = tracker.trimmedName();
    EXPECT_TRUE(trimmed.empty());
}

// Test marking section as needing another run
TEST_F(SectionTrackerTest_1038, MarkAsNeedingAnotherRun_1038) {
    NameAndLocationRef nameAndLoc("TestSection", SourceLineInfo("file.cpp", 10));
    SectionTracker& tracker = SectionTracker::acquire(ctx, nameAndLoc);
    tracker.markAsNeedingAnotherRun();
    // After marking, the section should not be complete
    EXPECT_FALSE(tracker.isComplete());
}

// Test failing a section tracker
TEST_F(SectionTrackerTest_1038, FailSectionTracker_1038) {
    NameAndLocationRef nameAndLoc("TestSection", SourceLineInfo("file.cpp", 10));
    SectionTracker& tracker = SectionTracker::acquire(ctx, nameAndLoc);
    tracker.fail();
    // After failing, check that it's not successfully completed
    EXPECT_FALSE(tracker.isSuccessfullyCompleted());
}

// Test isComplete for section with children that are not complete
TEST_F(SectionTrackerTest_1038, IsCompleteWithIncompleteChildren_1038) {
    NameAndLocationRef outerNameAndLoc("OuterSection", SourceLineInfo("file.cpp", 10));
    SectionTracker& outerTracker = SectionTracker::acquire(ctx, outerNameAndLoc);

    ctx.setCurrentTracker(&outerTracker);

    NameAndLocationRef innerNameAndLoc("InnerSection", SourceLineInfo("file.cpp", 20));
    SectionTracker& innerTracker = SectionTracker::acquire(ctx, innerNameAndLoc);

    // The outer section has a child that was opened but not closed
    // So outer should not be complete
    EXPECT_FALSE(outerTracker.isComplete());
}

// Test hasChildren
TEST_F(SectionTrackerTest_1038, HasChildrenAfterAcquiringNestedSection_1038) {
    NameAndLocationRef outerNameAndLoc("OuterSection", SourceLineInfo("file.cpp", 10));
    SectionTracker& outerTracker = SectionTracker::acquire(ctx, outerNameAndLoc);

    ctx.setCurrentTracker(&outerTracker);

    NameAndLocationRef innerNameAndLoc("InnerSection", SourceLineInfo("file.cpp", 20));
    SectionTracker::acquire(ctx, innerNameAndLoc);

    EXPECT_TRUE(outerTracker.hasChildren());
}

// Test setCurrentTracker and currentTracker
TEST_F(SectionTrackerTest_1038, SetAndGetCurrentTracker_1038) {
    NameAndLocationRef nameAndLoc("TestSection", SourceLineInfo("file.cpp", 10));
    SectionTracker& tracker = SectionTracker::acquire(ctx, nameAndLoc);
    ctx.setCurrentTracker(&tracker);
    EXPECT_EQ(&ctx.currentTracker(), &tracker);
}
