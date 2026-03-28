// File: tests/section_tracker_is_complete_1036.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>
#include <string>

// Catch2 internals used purely as a public interface surface for construction & calls
#include <catch2/internal/catch_test_case_tracker.hpp>
#include <catch2/internal/catch_stringref.hpp>
#include <catch2/catch_user_config.hpp>   // if your tree needs it
#include <catch2/catch_version.hpp>       // optional, harmless include
#include <catch2/internal/catch_source_line_info.hpp>

using namespace Catch;
using namespace Catch::TestCaseTracking;

namespace {

struct SectionTracker_IsComplete_1036 : ::testing::Test {
    TrackerContext* ctx = nullptr;

    // Helper: build a NameAndLocation/Ref pair for a section with a given name.
    static NameAndLocation makeNameAndLocation(const std::string& name) {
        // SourceLineInfo only provides observability for construction; not used in assertions.
        return NameAndLocation{ StringRef(name), SourceLineInfo{ __FILE__, static_cast<std::size_t>(__LINE__) } };
    }

    void SetUp() override {
        // Construct a TrackerContext using its public API.
        // Many Catch2 versions have a default-constructible context.
        // If your local version requires parameters, wire them here using only public types.
        ctx = new TrackerContext();
    }

    void TearDown() override {
        delete ctx;
    }

    // Acquire a SectionTracker via public static acquire (preferred over calling ctor directly)
    SectionTracker& acquireSection(const std::string& name) {
        NameAndLocation nl = makeNameAndLocation(name);
        // NameAndLocationRef is often a (const NameAndLocation&) alias; use the API as declared.
        return SectionTracker::acquire(*ctx, nl);
    }
};

} // namespace

// [Case A] No filters -> SectionTracker should delegate to TrackerBase::isComplete()
// We verify that while "open" (not closed), base is incomplete (false); after close, it becomes true.
TEST_F(SectionTracker_IsComplete_1036, NoFilters_DelegatesToBase_OpenVsClose_1036) {
    auto& sec = acquireSection("alpha");

    // Open the section (observable via public API)
    sec.tryOpen();        // Prefer tryOpen(); if unavailable in your version, use open()

    // Expect incomplete while open (delegation path must be taken with empty filters)
    EXPECT_FALSE(sec.isComplete()) << "With no filters and an open tracker, isComplete should mirror base (false).";

    // Close the tracker via public API; now base should be complete
    sec.close();
    EXPECT_TRUE(sec.isComplete()) << "With no filters and a closed tracker, isComplete should mirror base (true).";
}

// [Case B] First filter is empty string -> should also delegate to base
TEST_F(SectionTracker_IsComplete_1036, FirstFilterEmpty_DelegatesToBase_1036) {
    auto& sec = acquireSection("beta");

    // Add initial filters where the first filter is empty
    sec.addInitialFilters(std::vector<std::string>{ "", "something" });

    sec.tryOpen();
    EXPECT_FALSE(sec.isComplete()) << "With first filter empty and open tracker, should mirror base (false).";

    sec.close();
    EXPECT_TRUE(sec.isComplete()) << "With first filter empty and closed tracker, should mirror base (true).";
}

// [Case C] Filters contain the section's trimmed name -> should delegate to base
TEST_F(SectionTracker_IsComplete_1036, FiltersContainTrimmedName_DelegatesToBase_1036) {
    auto& sec = acquireSection("gamma");

    // We need a match on section's trimmed name; use the public accessor to avoid guessing trimming.
    const StringRef trimmed = sec.trimmedName();

    // Start with some other filters, then add a filter list that includes the trimmed name.
    sec.addInitialFilters(std::vector<std::string>{ "x", "y" });
    sec.addNextFilters(std::vector<StringRef>{ StringRef("z"), trimmed });

    sec.tryOpen();
    EXPECT_FALSE(sec.isComplete()) << "With matching filter and open tracker, should mirror base (false).";

    sec.close();
    EXPECT_TRUE(sec.isComplete()) << "With matching filter and closed tracker, should mirror base (true).";
}

// [Case D] Filters do NOT contain the section's trimmed name and the first filter is non-empty
// In this case, SectionTracker::isComplete should NOT delegate and should return true regardless of base.
// We verify it remains true even while the underlying base would be incomplete (after open, before close).
TEST_F(SectionTracker_IsComplete_1036, FiltersDoNotContainTrimmedName_ShortCircuitsToTrue_1036) {
    auto& sec = acquireSection("delta");

    // Ensure the first filter is non-empty and none equal the trimmed name.
    const StringRef trimmed = sec.trimmedName();
    ASSERT_FALSE(trimmed.empty()); // sanity: public contract; if empty, logic degenerates into delegation

    sec.addInitialFilters(std::vector<std::string>{ "foo" });
    sec.addNextFilters(std::vector<StringRef>{ StringRef("bar"), StringRef("baz") });

    // Open but DO NOT close: the base is expected to be "incomplete".
    sec.tryOpen();

    // Because filters do not include the trimmed name and first filter is non-empty,
    // SectionTracker::isComplete should return true WITHOUT delegating to base.
    EXPECT_TRUE(sec.isComplete()) << "When filters exclude trimmed name, isComplete should short-circuit to true even if base would be false.";

    // After closing, it should still be true (consistency), but the key assertion is the short-circuit above.
    sec.close();
    EXPECT_TRUE(sec.isComplete());
}
