// File: test_name_and_location_equality_439.cpp
#include <gtest/gtest.h>

#include "catch2/internal/catch_test_case_tracker.hpp" // For NameAndLocation / NameAndLocationRef
#include "catch2/internal/catch_source_line_info.hpp"  // For SourceLineInfo
#include "catch2/internal/catch_stringref.hpp"         // For StringRef

using Catch::SourceLineInfo;
using Catch::StringRef;
using Catch::TestCaseTracking::NameAndLocation;
using Catch::TestCaseTracking::NameAndLocationRef;

namespace {

// Helper to build matching pairs succinctly
static inline std::pair<NameAndLocation, NameAndLocationRef>
MakePair(const char* name, const char* file, std::size_t line) {
    SourceLineInfo sli{file, static_cast<std::size_t>(line)};
    NameAndLocation obj{std::string{name}, sli};
    NameAndLocationRef ref{StringRef{name}, sli};
    return {std::move(obj), ref};
}

} // namespace

// [439] Equal when both name and location match
TEST(NameAndLocationEq_439, EqualWhenNameAndLocationMatch_439) {
    auto [obj, ref] = MakePair("CaseA", "foo.cpp", 10);

    // Verify cross-type equality in both directions
    EXPECT_TRUE(ref == obj);
    EXPECT_TRUE(obj == ref);
}

// [439] Not equal when names differ (same location)
TEST(NameAndLocationEq_439, NotEqualWhenNameDiffers_439) {
    SourceLineInfo sli{"bar.cpp", 42};
    NameAndLocation obj_same_loc{std::string{"CaseA"}, sli};
    NameAndLocationRef ref_same_loc{StringRef{"CaseB"}, sli};

    EXPECT_FALSE(ref_same_loc == obj_same_loc);
    EXPECT_FALSE(obj_same_loc == ref_same_loc);
}

// [439] Not equal when locations differ (same name)
TEST(NameAndLocationEq_439, NotEqualWhenLocationDiffers_439) {
    NameAndLocation     obj{std::string{"CaseX"}, SourceLineInfo{"alpha.cpp", 7}};
    NameAndLocationRef  ref{StringRef{"CaseX"}, SourceLineInfo{"beta.cpp", 7}}; // different file

    EXPECT_FALSE(ref == obj);
    EXPECT_FALSE(obj == ref);

    // Also check differing line with same file to cover another location variation
    NameAndLocationRef  ref_line{StringRef{"CaseX"}, SourceLineInfo{"alpha.cpp", 8}};
    EXPECT_FALSE(ref_line == obj);
    EXPECT_FALSE(obj == ref_line);
}

// [439] Symmetry sanity: (ref == obj) result equals (obj == ref)
TEST(NameAndLocationEq_439, SymmetricResultsMatch_439) {
    auto [obj1, ref1] = MakePair("Same", "t.cpp", 1);
    auto [obj2, ref2] = MakePair("Different", "t.cpp", 1);

    // Equal pair
    bool a = (ref1 == obj1);
    bool b = (obj1 == ref1);
    EXPECT_EQ(a, b);
    EXPECT_TRUE(a);

    // Non-equal pair
    bool c = (ref2 == obj1);
    bool d = (obj1 == ref2);
    EXPECT_EQ(c, d);
    EXPECT_FALSE(c);
}
