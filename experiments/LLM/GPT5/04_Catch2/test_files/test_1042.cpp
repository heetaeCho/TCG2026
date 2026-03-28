// File: tests/section_tracker_trimmed_name_1042_tests.cpp

#include <gtest/gtest.h>

// Catch2 internals used as public interfaces for construction
#include <catch2/internal/catch_test_case_tracker.hpp>
#include <catch2/internal/catch_stringref.hpp>
#include <catch2/internal/catch_source_line_info.hpp>

using Catch::StringRef;
using Catch::SourceLineInfo;
using Catch::NameAndLocation;
using Catch::NameAndLocationRef;
using Catch::TestCaseTracking::SectionTracker;
using Catch::TestCaseTracking::TrackerContext;
using Catch::TestCaseTracking::ITracker;

namespace {

// Small helper to create NameAndLocation with a stable SourceLineInfo
inline NameAndLocation makeNAL(const std::string& name) {
    return NameAndLocation{name, SourceLineInfo{"section_tracker_trimmed_name_1042_tests.cpp", 42}};
}

} // namespace

// Fixture kept minimal; no private/internal peeks.
class SectionTrackerTrimmedNameTest_1042 : public ::testing::Test {
protected:
    TrackerContext ctx_; // Treat as an opaque collaborator
};

// [Normal] Mixed leading/trailing whitespace should not affect observable trimmedName contract
TEST_F(SectionTrackerTrimmedNameTest_1042, ReturnsTrimmedForLeadingAndTrailingSpaces_1042) {
    auto nal = makeNAL("   Important Section   ");
    // parent can be nullptr for a root section tracker in many Catch2 setups
    SectionTracker tracker(std::move(nal), ctx_, /*parent*/ nullptr);

    StringRef observed = tracker.trimmedName();

    // Observable behavior: returns a StringRef view representing the trimmed section name
    // (based on the provided interface and constructor usage shown in the prompt).
    EXPECT_EQ(observed, StringRef("Important Section"));
}

// [Boundary] No surrounding whitespace -> should be returned unchanged
TEST_F(SectionTrackerTrimmedNameTest_1042, ReturnsExactWhenAlreadyTrimmed_1042) {
    auto nal = makeNAL("Core");
    SectionTracker tracker(std::move(nal), ctx_, nullptr);

    StringRef observed = tracker.trimmedName();
    EXPECT_EQ(observed, StringRef("Core"));
}

// [Boundary] Empty name -> observable result should also be empty
TEST_F(SectionTrackerTrimmedNameTest_1042, EmptyNameYieldsEmptyTrimmedName_1042) {
    auto nal = makeNAL("");
    SectionTracker tracker(std::move(nal), ctx_, nullptr);

    StringRef observed = tracker.trimmedName();
    EXPECT_TRUE(observed.empty());
    EXPECT_EQ(observed.size(), 0u);
}

// [Boundary] Name consisting only of whitespace -> observable trimmed result is empty
TEST_F(SectionTrackerTrimmedNameTest_1042, AllWhitespaceYieldsEmptyTrimmedName_1042) {
    auto nal = makeNAL("\t  \n  ");
    SectionTracker tracker(std::move(nal), ctx_, nullptr);

    StringRef observed = tracker.trimmedName();
    EXPECT_TRUE(observed.empty());
    EXPECT_EQ(observed, StringRef(""));
}

// [Robustness] Multiple calls should be stable and consistent
TEST_F(SectionTrackerTrimmedNameTest_1042, MultipleCallsReturnConsistentResult_1042) {
    auto nal = makeNAL("  Alpha/Beta  ");
    SectionTracker tracker(std::move(nal), ctx_, nullptr);

    StringRef first = tracker.trimmedName();
    StringRef second = tracker.trimmedName();
    EXPECT_EQ(first, StringRef("Alpha/Beta"));
    EXPECT_EQ(second, StringRef("Alpha/Beta"));
    EXPECT_EQ(first, second);  // value equality; does not assume storage identity
}

// [Normal] Use the public static acquire API as an alternative construction path
TEST_F(SectionTrackerTrimmedNameTest_1042, AcquirePathAlsoYieldsTrimmedName_1042) {
    // NameAndLocationRef expects a NameAndLocation lvalue
    NameAndLocation nal = makeNAL("   Acquire Path   ");
    NameAndLocationRef nalRef{nal};
    // Using the public acquire interface from the provided declarations
    SectionTracker& tracker = SectionTracker::acquire(ctx_, nalRef);

    StringRef observed = tracker.trimmedName();
    EXPECT_EQ(observed, StringRef("Acquire Path"));
}
