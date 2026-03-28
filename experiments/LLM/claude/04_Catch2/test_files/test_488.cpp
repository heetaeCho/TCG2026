#include <gtest/gtest.h>
#include <sstream>
#include <cstring>

// Include the header for SourceLineInfo
#include "catch2/internal/catch_source_line_info.hpp"

namespace {

// Test fixture
class SourceLineInfoTest_488 : public ::testing::Test {
protected:
};

// ==================== Constructor Tests ====================

TEST_F(SourceLineInfoTest_488, ConstructorSetsFileAndLine_488) {
    Catch::SourceLineInfo info("test.cpp", 42);
    EXPECT_STREQ(info.file, "test.cpp");
    EXPECT_EQ(info.line, 42u);
}

TEST_F(SourceLineInfoTest_488, ConstructorWithZeroLine_488) {
    Catch::SourceLineInfo info("file.cpp", 0);
    EXPECT_STREQ(info.file, "file.cpp");
    EXPECT_EQ(info.line, 0u);
}

TEST_F(SourceLineInfoTest_488, ConstructorWithLargeLine_488) {
    Catch::SourceLineInfo info("file.cpp", 999999);
    EXPECT_STREQ(info.file, "file.cpp");
    EXPECT_EQ(info.line, 999999u);
}

TEST_F(SourceLineInfoTest_488, ConstructorWithEmptyFileName_488) {
    Catch::SourceLineInfo info("", 10);
    EXPECT_STREQ(info.file, "");
    EXPECT_EQ(info.line, 10u);
}

// ==================== operator== Tests ====================

TEST_F(SourceLineInfoTest_488, EqualityWithSameFileAndLine_488) {
    Catch::SourceLineInfo a("file.cpp", 10);
    Catch::SourceLineInfo b("file.cpp", 10);
    EXPECT_TRUE(a == b);
}

TEST_F(SourceLineInfoTest_488, EqualitySamePointerSameLine_488) {
    const char* file = "file.cpp";
    Catch::SourceLineInfo a(file, 10);
    Catch::SourceLineInfo b(file, 10);
    EXPECT_TRUE(a == b);
}

TEST_F(SourceLineInfoTest_488, InequalityDifferentLine_488) {
    Catch::SourceLineInfo a("file.cpp", 10);
    Catch::SourceLineInfo b("file.cpp", 20);
    EXPECT_FALSE(a == b);
}

TEST_F(SourceLineInfoTest_488, InequalityDifferentFile_488) {
    Catch::SourceLineInfo a("file1.cpp", 10);
    Catch::SourceLineInfo b("file2.cpp", 10);
    EXPECT_FALSE(a == b);
}

TEST_F(SourceLineInfoTest_488, InequalityDifferentFileAndLine_488) {
    Catch::SourceLineInfo a("file1.cpp", 10);
    Catch::SourceLineInfo b("file2.cpp", 20);
    EXPECT_FALSE(a == b);
}

TEST_F(SourceLineInfoTest_488, EqualityReflexive_488) {
    Catch::SourceLineInfo a("file.cpp", 10);
    EXPECT_TRUE(a == a);
}

// ==================== operator< Tests ====================

TEST_F(SourceLineInfoTest_488, LessThanSmallerLine_488) {
    Catch::SourceLineInfo a("file.cpp", 5);
    Catch::SourceLineInfo b("file.cpp", 10);
    EXPECT_TRUE(a < b);
}

TEST_F(SourceLineInfoTest_488, LessThanLargerLine_488) {
    Catch::SourceLineInfo a("file.cpp", 10);
    Catch::SourceLineInfo b("file.cpp", 5);
    EXPECT_FALSE(a < b);
}

TEST_F(SourceLineInfoTest_488, LessThanSameLineSameFile_488) {
    const char* file = "file.cpp";
    Catch::SourceLineInfo a(file, 10);
    Catch::SourceLineInfo b(file, 10);
    EXPECT_FALSE(a < b);
}

TEST_F(SourceLineInfoTest_488, LessThanSameLineDifferentFileLexicographic_488) {
    // "aaa.cpp" < "bbb.cpp" lexicographically
    Catch::SourceLineInfo a("aaa.cpp", 10);
    Catch::SourceLineInfo b("bbb.cpp", 10);
    EXPECT_TRUE(a < b);
}

TEST_F(SourceLineInfoTest_488, LessThanSameLineDifferentFileReverse_488) {
    // "bbb.cpp" > "aaa.cpp" lexicographically
    Catch::SourceLineInfo a("bbb.cpp", 10);
    Catch::SourceLineInfo b("aaa.cpp", 10);
    EXPECT_FALSE(a < b);
}

TEST_F(SourceLineInfoTest_488, LessThanSameLineSameFileContent_488) {
    // Same content but different pointers — strcmp should return 0, so file != other.file but strcmp == 0
    // This tests the condition: line == other.line && file != other.file && strcmp(file, other.file) < 0
    char file1[] = "file.cpp";
    char file2[] = "file.cpp";
    // Ensure different pointers
    ASSERT_NE(static_cast<const char*>(file1), static_cast<const char*>(file2));
    Catch::SourceLineInfo a(file1, 10);
    Catch::SourceLineInfo b(file2, 10);
    // strcmp returns 0, so the overall condition is false
    EXPECT_FALSE(a < b);
    EXPECT_FALSE(b < a);
}

TEST_F(SourceLineInfoTest_488, LessThanNotReflexive_488) {
    Catch::SourceLineInfo a("file.cpp", 10);
    EXPECT_FALSE(a < a);
}

TEST_F(SourceLineInfoTest_488, LessThanZeroLine_488) {
    Catch::SourceLineInfo a("file.cpp", 0);
    Catch::SourceLineInfo b("file.cpp", 1);
    EXPECT_TRUE(a < b);
}

TEST_F(SourceLineInfoTest_488, LessThanLineDominatesOverFile_488) {
    // Even if file "zzz.cpp" > "aaa.cpp", smaller line should win
    Catch::SourceLineInfo a("zzz.cpp", 1);
    Catch::SourceLineInfo b("aaa.cpp", 2);
    EXPECT_TRUE(a < b);
}

TEST_F(SourceLineInfoTest_488, LessThanLineDominatesOverFileReverse_488) {
    Catch::SourceLineInfo a("aaa.cpp", 2);
    Catch::SourceLineInfo b("zzz.cpp", 1);
    EXPECT_FALSE(a < b);
}

TEST_F(SourceLineInfoTest_488, LessThanTransitivity_488) {
    Catch::SourceLineInfo a("file.cpp", 1);
    Catch::SourceLineInfo b("file.cpp", 5);
    Catch::SourceLineInfo c("file.cpp", 10);
    EXPECT_TRUE(a < b);
    EXPECT_TRUE(b < c);
    EXPECT_TRUE(a < c);
}

TEST_F(SourceLineInfoTest_488, LessThanSameLineDifferentFilePointersSameContent_488) {
    // Same file pointer means file != other.file is false -> result is false
    const char* file = "file.cpp";
    Catch::SourceLineInfo a(file, 10);
    Catch::SourceLineInfo b(file, 10);
    EXPECT_FALSE(a < b);
}

// ==================== operator<< Tests ====================

TEST_F(SourceLineInfoTest_488, StreamOutputContainsFileName_488) {
    Catch::SourceLineInfo info("myfile.cpp", 42);
    std::ostringstream oss;
    oss << info;
    std::string result = oss.str();
    EXPECT_NE(result.find("myfile.cpp"), std::string::npos);
}

TEST_F(SourceLineInfoTest_488, StreamOutputContainsLineNumber_488) {
    Catch::SourceLineInfo info("myfile.cpp", 42);
    std::ostringstream oss;
    oss << info;
    std::string result = oss.str();
    EXPECT_NE(result.find("42"), std::string::npos);
}

TEST_F(SourceLineInfoTest_488, StreamOutputWithZeroLine_488) {
    Catch::SourceLineInfo info("file.cpp", 0);
    std::ostringstream oss;
    oss << info;
    std::string result = oss.str();
    EXPECT_NE(result.find("file.cpp"), std::string::npos);
    EXPECT_NE(result.find("0"), std::string::npos);
}

// ==================== Boundary / Edge Cases ====================

TEST_F(SourceLineInfoTest_488, LessThanMaxSizeT_488) {
    Catch::SourceLineInfo a("file.cpp", std::numeric_limits<std::size_t>::max() - 1);
    Catch::SourceLineInfo b("file.cpp", std::numeric_limits<std::size_t>::max());
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST_F(SourceLineInfoTest_488, EqualityWithEmptyFileNames_488) {
    const char* empty = "";
    Catch::SourceLineInfo a(empty, 5);
    Catch::SourceLineInfo b(empty, 5);
    EXPECT_TRUE(a == b);
}

TEST_F(SourceLineInfoTest_488, LessThanEmptyVsNonEmptyFile_488) {
    Catch::SourceLineInfo a("", 10);
    Catch::SourceLineInfo b("file.cpp", 10);
    // "" < "file.cpp" lexicographically, and different pointers
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

// ==================== Antisymmetry of operator< ====================

TEST_F(SourceLineInfoTest_488, LessThanAntisymmetricSameLine_488) {
    Catch::SourceLineInfo a("alpha.cpp", 10);
    Catch::SourceLineInfo b("beta.cpp", 10);
    // If a < b, then !(b < a)
    if (a < b) {
        EXPECT_FALSE(b < a);
    } else if (b < a) {
        EXPECT_FALSE(a < b);
    }
}

TEST_F(SourceLineInfoTest_488, LessThanAntisymmetricDifferentLine_488) {
    Catch::SourceLineInfo a("beta.cpp", 5);
    Catch::SourceLineInfo b("alpha.cpp", 10);
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

} // namespace
