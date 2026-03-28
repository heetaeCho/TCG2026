#include "catch2/internal/catch_test_case_tracker.hpp"
#include "catch2/internal/catch_stringref.hpp"
#include "catch2/internal/catch_source_line_info.hpp"
#include <gtest/gtest.h>
#include <string>

using Catch::TestCaseTracking::NameAndLocation;
using Catch::TestCaseTracking::NameAndLocationRef;
using Catch::SourceLineInfo;
using Catch::StringRef;

class NameAndLocationEqualityTest_438 : public ::testing::Test {
protected:
    // Helper to create NameAndLocation
    NameAndLocation makeNAL(std::string name, const char* file, std::size_t line) {
        return NameAndLocation(std::move(name), SourceLineInfo(file, line));
    }

    // Helper to create NameAndLocationRef
    NameAndLocationRef makeNALRef(StringRef name, const char* file, std::size_t line) {
        return NameAndLocationRef(name, SourceLineInfo(file, line));
    }
};

// Test that identical name and location are equal
TEST_F(NameAndLocationEqualityTest_438, SameNameAndLocation_ReturnsTrue_438) {
    NameAndLocation lhs(std::string("TestCase"), SourceLineInfo("file.cpp", 42));
    NameAndLocationRef rhs(StringRef("TestCase"), SourceLineInfo("file.cpp", 42));

    EXPECT_TRUE(lhs == rhs);
}

// Test that different names with same location are not equal
TEST_F(NameAndLocationEqualityTest_438, DifferentName_SameLocation_ReturnsFalse_438) {
    NameAndLocation lhs(std::string("TestCaseA"), SourceLineInfo("file.cpp", 42));
    NameAndLocationRef rhs(StringRef("TestCaseB"), SourceLineInfo("file.cpp", 42));

    EXPECT_FALSE(lhs == rhs);
}

// Test that same name with different line numbers are not equal
TEST_F(NameAndLocationEqualityTest_438, SameName_DifferentLine_ReturnsFalse_438) {
    NameAndLocation lhs(std::string("TestCase"), SourceLineInfo("file.cpp", 42));
    NameAndLocationRef rhs(StringRef("TestCase"), SourceLineInfo("file.cpp", 99));

    EXPECT_FALSE(lhs == rhs);
}

// Test that same name with different file names are not equal
TEST_F(NameAndLocationEqualityTest_438, SameName_DifferentFile_ReturnsFalse_438) {
    NameAndLocation lhs(std::string("TestCase"), SourceLineInfo("file1.cpp", 42));
    NameAndLocationRef rhs(StringRef("TestCase"), SourceLineInfo("file2.cpp", 42));

    EXPECT_FALSE(lhs == rhs);
}

// Test that everything different returns false
TEST_F(NameAndLocationEqualityTest_438, EverythingDifferent_ReturnsFalse_438) {
    NameAndLocation lhs(std::string("TestA"), SourceLineInfo("a.cpp", 1));
    NameAndLocationRef rhs(StringRef("TestB"), SourceLineInfo("b.cpp", 2));

    EXPECT_FALSE(lhs == rhs);
}

// Test with empty names and same location
TEST_F(NameAndLocationEqualityTest_438, EmptyNames_SameLocation_ReturnsTrue_438) {
    NameAndLocation lhs(std::string(""), SourceLineInfo("file.cpp", 10));
    NameAndLocationRef rhs(StringRef(""), SourceLineInfo("file.cpp", 10));

    EXPECT_TRUE(lhs == rhs);
}

// Test with empty name on one side
TEST_F(NameAndLocationEqualityTest_438, EmptyNameVsNonEmpty_ReturnsFalse_438) {
    NameAndLocation lhs(std::string(""), SourceLineInfo("file.cpp", 10));
    NameAndLocationRef rhs(StringRef("NonEmpty"), SourceLineInfo("file.cpp", 10));

    EXPECT_FALSE(lhs == rhs);
}

// Test with line number 0 (boundary)
TEST_F(NameAndLocationEqualityTest_438, LineZero_SameNameAndFile_ReturnsTrue_438) {
    NameAndLocation lhs(std::string("Test"), SourceLineInfo("file.cpp", 0));
    NameAndLocationRef rhs(StringRef("Test"), SourceLineInfo("file.cpp", 0));

    EXPECT_TRUE(lhs == rhs);
}

// Test with very large line number
TEST_F(NameAndLocationEqualityTest_438, LargeLineNumber_SameNameAndFile_ReturnsTrue_438) {
    std::size_t largeLine = static_cast<std::size_t>(-1);
    NameAndLocation lhs(std::string("Test"), SourceLineInfo("file.cpp", largeLine));
    NameAndLocationRef rhs(StringRef("Test"), SourceLineInfo("file.cpp", largeLine));

    EXPECT_TRUE(lhs == rhs);
}

// Test with same name, same file, adjacent lines
TEST_F(NameAndLocationEqualityTest_438, AdjacentLines_ReturnsFalse_438) {
    NameAndLocation lhs(std::string("Test"), SourceLineInfo("file.cpp", 42));
    NameAndLocationRef rhs(StringRef("Test"), SourceLineInfo("file.cpp", 43));

    EXPECT_FALSE(lhs == rhs);
}

// Test with long name strings
TEST_F(NameAndLocationEqualityTest_438, LongNames_Equal_ReturnsTrue_438) {
    std::string longName(1000, 'x');
    NameAndLocation lhs(std::string(longName), SourceLineInfo("file.cpp", 1));
    NameAndLocationRef rhs(StringRef(longName.c_str()), SourceLineInfo("file.cpp", 1));

    EXPECT_TRUE(lhs == rhs);
}

// Test with long name strings that differ by one character
TEST_F(NameAndLocationEqualityTest_438, LongNames_DifferByOneChar_ReturnsFalse_438) {
    std::string longName1(1000, 'x');
    std::string longName2(1000, 'x');
    longName2[999] = 'y';
    NameAndLocation lhs(std::string(longName1), SourceLineInfo("file.cpp", 1));
    NameAndLocationRef rhs(StringRef(longName2.c_str()), SourceLineInfo("file.cpp", 1));

    EXPECT_FALSE(lhs == rhs);
}

// Test name is a substring of the other
TEST_F(NameAndLocationEqualityTest_438, NameSubstring_ReturnsFalse_438) {
    NameAndLocation lhs(std::string("Test"), SourceLineInfo("file.cpp", 1));
    NameAndLocationRef rhs(StringRef("TestExtra"), SourceLineInfo("file.cpp", 1));

    EXPECT_FALSE(lhs == rhs);
}

// Test name where rhs is prefix of lhs
TEST_F(NameAndLocationEqualityTest_438, NamePrefix_ReturnsFalse_438) {
    NameAndLocation lhs(std::string("TestExtra"), SourceLineInfo("file.cpp", 1));
    NameAndLocationRef rhs(StringRef("Test"), SourceLineInfo("file.cpp", 1));

    EXPECT_FALSE(lhs == rhs);
}

// Early return optimization: different line should fail fast regardless of name/file
TEST_F(NameAndLocationEqualityTest_438, DifferentLineOnly_ReturnsFalse_438) {
    NameAndLocation lhs(std::string("Same"), SourceLineInfo("same.cpp", 10));
    NameAndLocationRef rhs(StringRef("Same"), SourceLineInfo("same.cpp", 20));

    EXPECT_FALSE(lhs == rhs);
}
