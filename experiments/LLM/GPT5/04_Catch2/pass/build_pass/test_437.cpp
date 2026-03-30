// File: name_and_location_not_equal_tests_437.cpp
#include <gtest/gtest.h>

// Include the header that declares NameAndLocation and operator!=
#include "catch2/internal/catch_test_case_tracker.hpp"

// If SourceLineInfo is declared in Catch's root namespace (as in Catch2),
// we will refer to it as Catch::SourceLineInfo.
// NameAndLocation is in Catch::TestCaseTracking.
using Catch::SourceLineInfo;
using Catch::TestCaseTracking::NameAndLocation;

namespace {

// Small helper to construct SourceLineInfo without relying on any internals.
inline SourceLineInfo SLI(const char* file, std::size_t line) {
    return SourceLineInfo(file, line);
}

} // namespace

// The following tests verify only the public, observable behavior:
// - Self comparison: x != x must be false
// - Consistency: (a != b) must equal !(a == b)
// - Symmetry: (a != b) must equal (b != a)
// They do NOT assume what constitutes equality internally (name vs. location, etc.).

TEST(NameAndLocationTest_437, SelfComparison_IsAlwaysFalse_437) {
    NameAndLocation a{"AlphaTest", SLI("alpha.cpp", 10)};
    EXPECT_FALSE(a != a);
}

TEST(NameAndLocationTest_437, IdenticalValues_EqualOppositeNotEqual_437) {
    NameAndLocation a{"SameTest", SLI("same.cpp", 42)};
    NameAndLocation b{"SameTest", SLI("same.cpp", 42)};

    // Check that != is logical negation of == for identical values
    EXPECT_EQ(a != b, !(a == b));

    // Symmetry should hold too
    EXPECT_EQ(a != b, b != a);
}

TEST(NameAndLocationTest_437, DifferentName_ConsistencyBetweenEqAndNeq_437) {
    NameAndLocation a{"TestA", SLI("file.cpp", 123)};
    NameAndLocation b{"TestB", SLI("file.cpp", 123)};

    // We do not assert specific equality semantics; only that != negates ==.
    EXPECT_EQ(a != b, !(a == b));
    EXPECT_EQ(a != b, b != a);
}

TEST(NameAndLocationTest_437, DifferentLocation_ConsistencyBetweenEqAndNeq_437) {
    NameAndLocation a{"LineSensitive", SLI("file.cpp", 1)};
    NameAndLocation b{"LineSensitive", SLI("file.cpp", 2)};

    EXPECT_EQ(a != b, !(a == b));
    EXPECT_EQ(a != b, b != a);
}

TEST(NameAndLocationTest_437, EmptyNameAndExtremeLines_Consistency_437) {
    // Boundary-ish values for line numbers and empty names
    NameAndLocation a{"", SLI("edge.cpp", 0)};
    NameAndLocation b{"", SLI("edge.cpp", static_cast<std::size_t>(-1))}; // very large size_t

    EXPECT_FALSE(a != a);  // self-comparison still false
    EXPECT_EQ(a != b, !(a == b));
    EXPECT_EQ(a != b, b != a);
}

