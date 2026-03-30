// File: tests/name_and_location_eq_tests_436.cpp

#include <gtest/gtest.h>
#include <string>

// Headers under test (paths follow the prompt)
#include "Catch2/src/catch2/internal/catch_source_line_info.hpp"
#include "Catch2/src/catch2/internal/catch_test_case_tracker.hpp"

using Catch::SourceLineInfo;
using Catch::TestCaseTracking::NameAndLocation;

namespace {

// Helper to make a NameAndLocation via its public ctor
static NameAndLocation MakeNAL(std::string name, const char* file, std::size_t line) {
    return NameAndLocation(std::move(name), SourceLineInfo(file, line));
}

} // namespace

// --- Normal operation ---

TEST(NameAndLocationEqTest_436, EqualWhenNameAndLocationMatch_436) {
    auto a = MakeNAL("CaseA", "file.cpp", 42);
    auto b = MakeNAL("CaseA", "file.cpp", 42);

    EXPECT_TRUE(a == b);
    EXPECT_TRUE(b == a); // symmetry
    EXPECT_TRUE(a == a); // reflexivity
}

TEST(NameAndLocationEqTest_436, UnequalWhenNamesDiffer_436) {
    auto a = MakeNAL("CaseA", "file.cpp", 42);
    auto b = MakeNAL("CaseB", "file.cpp", 42);

    EXPECT_FALSE(a == b);
    EXPECT_FALSE(b == a);
}

TEST(NameAndLocationEqTest_436, UnequalWhenFilesDiffer_436) {
    auto a = MakeNAL("CaseA", "a.cpp", 10);
    auto b = MakeNAL("CaseA", "b.cpp", 10);

    EXPECT_FALSE(a == b);
    EXPECT_FALSE(b == a);
}

TEST(NameAndLocationEqTest_436, UnequalWhenLinesDiffer_436) {
    auto a = MakeNAL("CaseA", "file.cpp", 10);
    auto b = MakeNAL("CaseA", "file.cpp", 11);

    EXPECT_FALSE(a == b);
    EXPECT_FALSE(b == a);
}

// --- Boundary conditions ---

TEST(NameAndLocationEqTest_436, EqualWithEmptyNameIfLocationMatches_436) {
    auto a = MakeNAL("", "file.cpp", 1);
    auto b = MakeNAL("", "file.cpp", 1);

    EXPECT_TRUE(a == b);
}

TEST(NameAndLocationEqTest_436, UnequalWithEmptyVsNonEmptyName_436) {
    auto a = MakeNAL("", "file.cpp", 1);
    auto b = MakeNAL("nonempty", "file.cpp", 1);

    EXPECT_FALSE(a == b);
}

// --- Additional observable properties ---

TEST(NameAndLocationEqTest_436, TransitivityHoldsForEquality_436) {
    auto a = MakeNAL("X", "file.cpp", 7);
    auto b = MakeNAL("X", "file.cpp", 7);
    auto c = MakeNAL("X", "file.cpp", 7);

    ASSERT_TRUE(a == b);
    ASSERT_TRUE(b == c);
    EXPECT_TRUE(a == c);
}

