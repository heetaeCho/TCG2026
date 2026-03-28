// File: section_tracker_getfilters_tests_446.cpp

#include <gtest/gtest.h>

// Public Catch2 internals used by the tested interface
#include "catch2/internal/catch_test_case_tracker.hpp"
#include "catch2/internal/catch_stringref.hpp"
#include "catch2/internal/catch_source_line_info.hpp"
#include "catch2/internal/catch_interfaces_capture.hpp" // for NameAndLocation / NameAndLocationRef in many Catch2 versions
// If your repo exposes NameAndLocation in a different header, include that one instead.

using Catch::StringRef;
using Catch::SourceLineInfo;
using Catch::NameAndLocation;
using Catch::NameAndLocationRef;
using Catch::TestCaseTracking::SectionTracker;
using Catch::TestCaseTracking::TrackerContext;
using Catch::TestCaseTracking::ITracker;

namespace {

// Utility that constructs a NameAndLocation (or ref) in a version-tolerant way.
inline NameAndLocation makeNameAndLocation(const char* name = "SectionName_446",
                                           const char* file = "file_446.cpp",
                                           std::size_t line = 446) {
    return NameAndLocation{ StringRef{name}, SourceLineInfo{ file, static_cast<std::size_t>(line) } };
}

struct SectionTrackerFixture_446 : ::testing::Test {
    TrackerContext ctx{};
    // Parent tracker is not needed for exercising filter-related API
    ITracker* parent = nullptr;

    // Helper that creates a fresh SectionTracker instance in a state suitable
    // for filter manipulation tests. We construct it directly, as allowed by the public ctor.
    SectionTracker makeFresh() {
        NameAndLocation nl = makeNameAndLocation();
        return SectionTracker(CATCH_MOVE(nl), ctx, parent);
    }
};

} // namespace

// --- Tests ---

// Normal operation: freshly constructed tracker has no filters.
TEST_F(SectionTrackerFixture_446, GetFilters_InitiallyEmpty_446) {
    auto tracker = makeFresh();
    const auto& filters = tracker.getFilters();
    EXPECT_TRUE(filters.empty());
    EXPECT_EQ(&filters, &tracker.getFilters()) << "Should return a stable const reference";
}

// Normal operation: addInitialFilters populates filters; getFilters reflects them in order.
TEST_F(SectionTrackerFixture_446, GetFilters_AfterAddInitialFilters_446) {
    auto tracker = makeFresh();

    std::vector<std::string> initial = { "alpha", "beta" };
    tracker.addInitialFilters(initial);

    const auto& filters = tracker.getFilters();
    ASSERT_EQ(filters.size(), 2u);
    EXPECT_EQ(filters[0], StringRef("alpha"));
    EXPECT_EQ(filters[1], StringRef("beta"));
}

// Normal operation: addNextFilters appends to existing filters; order is preserved.
TEST_F(SectionTrackerFixture_446, GetFilters_AddNextAppends_446) {
    auto tracker = makeFresh();

    tracker.addInitialFilters({ "one", "two" });
    std::vector<StringRef> next = { StringRef("three"), StringRef("four") };
    tracker.addNextFilters(next);

    const auto& filters = tracker.getFilters();
    ASSERT_EQ(filters.size(), 4u);
    EXPECT_EQ(filters[0], StringRef("one"));
    EXPECT_EQ(filters[1], StringRef("two"));
    EXPECT_EQ(filters[2], StringRef("three"));
    EXPECT_EQ(filters[3], StringRef("four"));
}

// Boundary: adding empty initial filters keeps the list unchanged (still empty).
TEST_F(SectionTrackerFixture_446, GetFilters_EmptyInitialNoChange_446) {
    auto tracker = makeFresh();

    std::vector<std::string> none{};
    tracker.addInitialFilters(none);

    const auto& filters = tracker.getFilters();
    EXPECT_TRUE(filters.empty());
}

// Boundary: adding empty next filters does not modify existing ones.
TEST_F(SectionTrackerFixture_446, GetFilters_EmptyNextNoChange_446) {
    auto tracker = makeFresh();

    tracker.addInitialFilters({ "solo" });
    const auto& beforeRef = tracker.getFilters();
    ASSERT_EQ(beforeRef.size(), 1u);

    std::vector<StringRef> empty{};
    tracker.addNextFilters(empty);

    const auto& afterRef = tracker.getFilters();
    EXPECT_EQ(&beforeRef, &afterRef) << "Reference identity should remain the same";
    ASSERT_EQ(afterRef.size(), 1u);
    EXPECT_EQ(afterRef[0], StringRef("solo"));
}

// Observable behavior: previously captured const reference reflects subsequent appends.
TEST_F(SectionTrackerFixture_446, GetFilters_ReturnedRefReflectsLaterUpdates_446) {
    auto tracker = makeFresh();

    tracker.addInitialFilters({ "head" });
    const auto& ref = tracker.getFilters();

    std::vector<StringRef> more = { StringRef("tail") };
    tracker.addNextFilters(more);

    ASSERT_EQ(ref.size(), 2u) << "The original const& should observe later changes";
    EXPECT_EQ(ref[0], StringRef("head"));
    EXPECT_EQ(ref[1], StringRef("tail"));
}

// Exceptional/edge (interface-observable): duplicates are allowed and preserved in order.
TEST_F(SectionTrackerFixture_446, GetFilters_AllowsDuplicates_446) {
    auto tracker = makeFresh();

    tracker.addInitialFilters({ "dup", "x" });
    tracker.addNextFilters({ StringRef("dup") });

    const auto& filters = tracker.getFilters();
    ASSERT_EQ(filters.size(), 3u);
    EXPECT_EQ(filters[0], StringRef("dup"));
    EXPECT_EQ(filters[1], StringRef("x"));
    EXPECT_EQ(filters[2], StringRef("dup")) << "Duplicate should be preserved";
}
