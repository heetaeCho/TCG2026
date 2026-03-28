// File: tests/source_line_info_eq_tests_487.cpp
#include <gtest/gtest.h>
#include "catch2/internal/catch_source_line_info.hpp"  // Adjust include path if needed
#include <string>

using Catch::SourceLineInfo;

class SourceLineInfoTest_487 : public ::testing::Test {};

// Normal operation: same file pointer and same line -> equal
TEST_F(SourceLineInfoTest_487, EqualWhenSamePointerAndLine_487) {
    const char* file = "file.cpp";
    SourceLineInfo a{file, 42};
    SourceLineInfo b{file, 42};

    EXPECT_TRUE(a == b);
}

// Normal operation: different pointers, same file content, same line -> equal
// (verifies observable behavior consistent with strcmp-based comparison)
TEST_F(SourceLineInfoTest_487, EqualWhenDifferentPointersButSameContentAndLine_487) {
    std::string s1 = "path/to/file.cpp";
    std::string s2 = "path/to/file.cpp"; // distinct std::string, distinct c_str() pointers
    const char* f1 = s1.c_str();
    const char* f2 = s2.c_str();

    // Sanity: ensure pointers differ (not required for equality, but ensures the scenario)
    ASSERT_NE(f1, f2);

    SourceLineInfo a{f1, 100};
    SourceLineInfo b{f2, 100};

    EXPECT_TRUE(a == b);
}

// Boundary: reflexivity — an object equals itself
TEST_F(SourceLineInfoTest_487, ReflexiveEquality_487) {
    SourceLineInfo a{"self.cpp", 7};
    EXPECT_TRUE(a == a);
}

// Boundary: empty file name but same contents and line -> equal
TEST_F(SourceLineInfoTest_487, EmptyFileNameEqualWhenSameLine_487) {
    const char* empty1 = "";
    std::string emptyStr = "";
    const char* empty2 = emptyStr.c_str();

    ASSERT_NE(empty1, empty2); // ensure distinct pointers where possible

    SourceLineInfo a{empty1, 0};
    SourceLineInfo b{empty2, 0};

    EXPECT_TRUE(a == b);
}

// Exceptional/negative case: same file pointer, different line -> not equal
TEST_F(SourceLineInfoTest_487, NotEqualWhenDifferentLine_487) {
    const char* file = "same.cpp";
    SourceLineInfo a{file, 1};
    SourceLineInfo b{file, 2};

    EXPECT_FALSE(a == b);
}

// Exceptional/negative case: different file content, same line -> not equal
TEST_F(SourceLineInfoTest_487, NotEqualWhenDifferentFileNames_487) {
    SourceLineInfo a{"a.cpp", 77};
    SourceLineInfo b{"b.cpp", 77};

    EXPECT_FALSE(a == b);
}

// Verification: symmetry — if a == b then b == a
TEST_F(SourceLineInfoTest_487, SymmetricEquality_487) {
    std::string s1 = "sym/file.cpp";
    std::string s2 = "sym/file.cpp";
    SourceLineInfo a{s1.c_str(), 55};
    SourceLineInfo b{s2.c_str(), 55};

    EXPECT_TRUE(a == b);
    EXPECT_TRUE(b == a);
}
