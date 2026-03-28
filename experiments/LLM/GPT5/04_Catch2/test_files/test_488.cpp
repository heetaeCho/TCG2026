// File: source_line_info_compare_test_488.cpp
#include <gtest/gtest.h>

#include "catch2/internal/catch_source_line_info.hpp"  // adjust include path if needed

using Catch::SourceLineInfo;

class SourceLineInfoTest_488 : public ::testing::Test {};

// Normal: different line numbers — smaller line is less
TEST_F(SourceLineInfoTest_488, LessWhenLineIsSmaller_488) {
    SourceLineInfo a{"a.cpp", 10};
    SourceLineInfo b{"b.cpp", 20};

    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

// Normal: greater line is not less
TEST_F(SourceLineInfoTest_488, NotLessWhenLineIsGreater_488) {
    SourceLineInfo a{"a.cpp", 30};
    SourceLineInfo b{"b.cpp", 20};

    EXPECT_FALSE(a < b);
    EXPECT_TRUE(b < a);
}

// Tie-breaker: same line — lexicographic order of file names decides
TEST_F(SourceLineInfoTest_488, CompareFilesWhenLinesEqual_Lexicographic_488) {
    const std::size_t line = 42;
    SourceLineInfo a{"alpha.cpp", line};
    SourceLineInfo b{"beta.cpp",  line};

    EXPECT_TRUE(a < b);   // "alpha.cpp" < "beta.cpp"
    EXPECT_FALSE(b < a);
}

// Tie case: same line and same file POINTER — not less either way
TEST_F(SourceLineInfoTest_488, NotLessWhenFilesSamePointerAndLineEqual_488) {
    const char* samePtr = "same.cpp"; // same pointer used for both
    SourceLineInfo a{samePtr, 100};
    SourceLineInfo b{samePtr, 100};

    EXPECT_FALSE(a < b);
    EXPECT_FALSE(b < a);
}

// Tie case: same line and same file CONTENT but different storage — not less either way
TEST_F(SourceLineInfoTest_488, EquivalentWhenLinesEqualAndFileNamesIdenticalButDifferentStorage_488) {
    // Distinct arrays ensure distinct pointers with identical contents.
    static const char file1[] = "same-content.cpp";
    static const char file2[] = "same-content.cpp";

    ASSERT_NE(file1, file2); // sanity: different pointers

    SourceLineInfo a{file1, 77};
    SourceLineInfo b{file2, 77};

    // Ordering equivalence (neither is less than the other)
    EXPECT_FALSE(a < b);
    EXPECT_FALSE(b < a);
}

// Transitivity: a < b and b < c implies a < c
TEST_F(SourceLineInfoTest_488, OrderingTransitivity_488) {
    SourceLineInfo a{"alpha.cpp", 10};
    SourceLineInfo b{"beta.cpp",  10};  // same line, file decides
    SourceLineInfo c{"gamma.cpp", 20};  // higher line

    EXPECT_TRUE(a < b);
    EXPECT_TRUE(b < c);
    EXPECT_TRUE(a < c);
}

// Boundary: line number comparison dominates regardless of file names
TEST_F(SourceLineInfoTest_488, BoundaryLines_UsesLineFirst_488) {
    SourceLineInfo low{"zzz.cpp", 0};
    SourceLineInfo high{"aaa.cpp", static_cast<std::size_t>(~std::size_t{0})}; // SIZE_MAX

    EXPECT_TRUE(low < high);
    EXPECT_FALSE(high < low);
}

// Antisymmetry sanity: if a < b then !(b < a)
TEST_F(SourceLineInfoTest_488, Antisymmetry_488) {
    SourceLineInfo a{"a.cpp", 5};
    SourceLineInfo b{"b.cpp", 5};

    ASSERT_TRUE(a < b);  // precondition for this check
    EXPECT_FALSE(b < a);
}
