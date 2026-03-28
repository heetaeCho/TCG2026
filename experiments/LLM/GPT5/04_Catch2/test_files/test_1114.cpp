// File: tests/section_tracker_ctor_1114_tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/internal/catch_test_case_tracker.hpp"

using ::testing::ElementsAre;
using Catch::TestCaseTracking::SectionTracker;
using Catch::TestCaseTracking::TrackerBase;
using Catch::TestCaseTracking::TrackerContext;
using Catch::TestCaseTracking::ITracker;
using Catch::TestCaseTracking::NameAndLocation;
using Catch::SourceLineInfo;
using Catch::StringRef;

namespace {

// Minimal non-section tracker collaborator that lets us set a parent.
struct FakeNonSectionTracker : ITracker {
    FakeNonSectionTracker(NameAndLocation&& nal, ITracker* parent)
        : ITracker(std::move(nal), parent) {}

    // Keep default behaviours for everything else; only assert it's not a section/generator.
    bool isSectionTracker() const override { return false; }
    bool isGeneratorTracker() const override { return false; }
    // Provide harmless overridables (no-ops) to satisfy virtuals if needed.
    bool isComplete() const override { return true; }
    void close() override {}
    void fail() override {}
};

inline NameAndLocation makeNAL(std::string name = "sec",
                               const SourceLineInfo& loc = SourceLineInfo{"file.cpp", 42}) {
    return NameAndLocation(std::move(name), loc);
}

} // namespace

// ----------------------------------------------------------------------------
// TESTS
// ----------------------------------------------------------------------------

class SectionTrackerTest_1114 : public ::testing::Test {
protected:
    TrackerContext ctx_;
    SourceLineInfo loc_{"test_file.cpp", 10};
};

// Normal operation: constructor trims the section name.
TEST_F(SectionTrackerTest_1114, CtorTrimsName_1114) {
    // Leading/trailing whitespace, tabs, and newline
    SectionTracker st{makeNAL(" \t My Section \n "), ctx_, /*parent*/ nullptr};

    EXPECT_TRUE(st.trimmedName() == StringRef("My Section"));
}

// Boundary: empty parent -> no filters inherited, filters stay empty.
TEST_F(SectionTrackerTest_1114, NoParent_YieldsEmptyFilters_1114) {
    SectionTracker st{makeNAL("child", loc_), ctx_, nullptr};

    ASSERT_TRUE(st.getFilters().empty());
}

// Normal operation: child inherits filters from immediate section parent.
TEST_F(SectionTrackerTest_1114, InheritsFiltersFromDirectSectionParent_1114) {
    SectionTracker parent{makeNAL("parent", loc_), ctx_, nullptr};
    parent.addInitialFilters(std::vector<std::string>{"[foo]", "[bar]"});

    SectionTracker child{makeNAL("child", loc_), ctx_, &parent};

    auto const& f = child.getFilters();
    ASSERT_EQ(f.size(), 2u);
    EXPECT_TRUE(f[0] == StringRef("[foo]"));
    EXPECT_TRUE(f[1] == StringRef("[bar]"));
}

// Normal operation + external interaction path: when the immediate parent is NOT
// a section tracker, the ctor climbs to the nearest ancestor that IS a section tracker
// and inherits that ancestor's filters.
TEST_F(SectionTrackerTest_1114, SkipsNonSectionImmediateParent_AndInheritsFromNearestSectionAncestor_1114) {
    // Create a real section ancestor with filters
    SectionTracker ancestor{makeNAL("ancestor", loc_), ctx_, nullptr};
    ancestor.addInitialFilters(std::vector<std::string>{"[alpha]", "[beta]"});

    // Non-section immediate parent that points to the section ancestor
    FakeNonSectionTracker nonSectionParent{makeNAL("not_a_section", loc_), &ancestor};

    // Now create the child with non-section immediate parent. The ctor should walk up.
    SectionTracker child{makeNAL("child", loc_), ctx_, &nonSectionParent};

    auto const& f = child.getFilters();
    ASSERT_EQ(f.size(), 2u);
    EXPECT_TRUE(f[0] == StringRef("[alpha]"));
    EXPECT_TRUE(f[1] == StringRef("[beta]"));
}

// Boundary: parent section has empty filter set -> child inherits the same (still empty).
TEST_F(SectionTrackerTest_1114, InheritsEmptyFiltersFromParent_1114) {
    SectionTracker parent{makeNAL("parent", loc_), ctx_, nullptr};
    parent.addInitialFilters(std::vector<std::string>{}); // explicitly empty

    SectionTracker child{makeNAL("child", loc_), ctx_, &parent};
    EXPECT_TRUE(child.getFilters().empty());
}

// Boundary: name consists only of whitespace -> trimmedName becomes empty.
TEST_F(SectionTrackerTest_1114, TrimsAllWhitespaceName_ToEmpty_1114) {
    SectionTracker st{makeNAL(" \t \n "), ctx_, nullptr};
    EXPECT_TRUE(st.trimmedName().empty());
}
