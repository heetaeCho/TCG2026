#include <gtest/gtest.h>
#include <cstring>
#include <sstream>

// Include the header for SourceLineInfo
#include "catch2/internal/catch_source_line_info.hpp"

namespace {

// Test fixture for SourceLineInfo tests
class SourceLineInfoTest_487 : public ::testing::Test {
protected:
    // Helper to create SourceLineInfo instances
};

// ==================== Equality Operator Tests ====================

TEST_F(SourceLineInfoTest_487, EqualityWithSameFilePointerAndSameLine_487) {
    const char* file = "test.cpp";
    Catch::SourceLineInfo a(file, 42);
    Catch::SourceLineInfo b(file, 42);
    EXPECT_TRUE(a == b);
}

TEST_F(SourceLineInfoTest_487, EqualityWithDifferentFilePointersSameContent_487) {
    char file1[] = "test.cpp";
    char file2[] = "test.cpp";
    // Ensure they are different pointers
    ASSERT_NE(static_cast<const char*>(file1), static_cast<const char*>(file2));
    Catch::SourceLineInfo a(file1, 42);
    Catch::SourceLineInfo b(file2, 42);
    EXPECT_TRUE(a == b);
}

TEST_F(SourceLineInfoTest_487, InequalityWithDifferentLines_487) {
    const char* file = "test.cpp";
    Catch::SourceLineInfo a(file, 42);
    Catch::SourceLineInfo b(file, 43);
    EXPECT_FALSE(a == b);
}

TEST_F(SourceLineInfoTest_487, InequalityWithDifferentFiles_487) {
    Catch::SourceLineInfo a("file1.cpp", 42);
    Catch::SourceLineInfo b("file2.cpp", 42);
    EXPECT_FALSE(a == b);
}

TEST_F(SourceLineInfoTest_487, InequalityWithDifferentFilesAndLines_487) {
    Catch::SourceLineInfo a("file1.cpp", 10);
    Catch::SourceLineInfo b("file2.cpp", 20);
    EXPECT_FALSE(a == b);
}

TEST_F(SourceLineInfoTest_487, EqualityWithEmptyFileStrings_487) {
    char file1[] = "";
    char file2[] = "";
    Catch::SourceLineInfo a(file1, 0);
    Catch::SourceLineInfo b(file2, 0);
    EXPECT_TRUE(a == b);
}

TEST_F(SourceLineInfoTest_487, EqualityWithLineZero_487) {
    Catch::SourceLineInfo a("test.cpp", 0);
    Catch::SourceLineInfo b("test.cpp", 0);
    EXPECT_TRUE(a == b);
}

TEST_F(SourceLineInfoTest_487, EqualityWithMaxLine_487) {
    Catch::SourceLineInfo a("test.cpp", std::numeric_limits<std::size_t>::max());
    Catch::SourceLineInfo b("test.cpp", std::numeric_limits<std::size_t>::max());
    EXPECT_TRUE(a == b);
}

TEST_F(SourceLineInfoTest_487, EqualityReflexive_487) {
    Catch::SourceLineInfo a("test.cpp", 100);
    EXPECT_TRUE(a == a);
}

TEST_F(SourceLineInfoTest_487, EqualitySymmetric_487) {
    char file1[] = "test.cpp";
    char file2[] = "test.cpp";
    Catch::SourceLineInfo a(file1, 100);
    Catch::SourceLineInfo b(file2, 100);
    EXPECT_TRUE(a == b);
    EXPECT_TRUE(b == a);
}

// ==================== Less-Than Operator Tests ====================

TEST_F(SourceLineInfoTest_487, LessThanByLine_487) {
    const char* file = "test.cpp";
    Catch::SourceLineInfo a(file, 10);
    Catch::SourceLineInfo b(file, 20);
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST_F(SourceLineInfoTest_487, LessThanByFile_487) {
    Catch::SourceLineInfo a("aaa.cpp", 10);
    Catch::SourceLineInfo b("bbb.cpp", 10);
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST_F(SourceLineInfoTest_487, NotLessThanWhenEqual_487) {
    Catch::SourceLineInfo a("test.cpp", 10);
    Catch::SourceLineInfo b("test.cpp", 10);
    EXPECT_FALSE(a < b);
    EXPECT_FALSE(b < a);
}

TEST_F(SourceLineInfoTest_487, LessThanFileTakesPrecedenceOverLine_487) {
    // If file comparison determines order, line should not matter
    Catch::SourceLineInfo a("aaa.cpp", 100);
    Catch::SourceLineInfo b("bbb.cpp", 1);
    EXPECT_TRUE(a < b);
}

TEST_F(SourceLineInfoTest_487, LessThanSameFileDifferentLines_487) {
    Catch::SourceLineInfo a("test.cpp", 5);
    Catch::SourceLineInfo b("test.cpp", 10);
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

// ==================== Constructor / Member Access Tests ====================

TEST_F(SourceLineInfoTest_487, ConstructorSetsFileAndLine_487) {
    const char* filename = "myfile.cpp";
    Catch::SourceLineInfo info(filename, 99);
    EXPECT_EQ(info.file, filename);
    EXPECT_EQ(info.line, 99u);
}

TEST_F(SourceLineInfoTest_487, ConstructorWithZeroLine_487) {
    Catch::SourceLineInfo info("file.cpp", 0);
    EXPECT_STREQ(info.file, "file.cpp");
    EXPECT_EQ(info.line, 0u);
}

// ==================== Stream Operator Tests ====================

TEST_F(SourceLineInfoTest_487, StreamOperatorOutputsFileAndLine_487) {
    Catch::SourceLineInfo info("test.cpp", 42);
    std::ostringstream oss;
    oss << info;
    std::string result = oss.str();
    // Should contain the filename
    EXPECT_NE(result.find("test.cpp"), std::string::npos);
    // Should contain the line number
    EXPECT_NE(result.find("42"), std::string::npos);
}

TEST_F(SourceLineInfoTest_487, StreamOperatorWithLineZero_487) {
    Catch::SourceLineInfo info("file.cpp", 0);
    std::ostringstream oss;
    oss << info;
    std::string result = oss.str();
    EXPECT_NE(result.find("file.cpp"), std::string::npos);
}

// ==================== Edge Case Tests ====================

TEST_F(SourceLineInfoTest_487, EqualityWithLongFileName_487) {
    std::string longName(1000, 'a');
    longName += ".cpp";
    char* file1 = new char[longName.size() + 1];
    char* file2 = new char[longName.size() + 1];
    std::strcpy(file1, longName.c_str());
    std::strcpy(file2, longName.c_str());

    Catch::SourceLineInfo a(file1, 1);
    Catch::SourceLineInfo b(file2, 1);
    EXPECT_TRUE(a == b);

    delete[] file1;
    delete[] file2;
}

TEST_F(SourceLineInfoTest_487, InequalityWhenFilesDifferByOneChar_487) {
    Catch::SourceLineInfo a("test.cpx", 10);
    Catch::SourceLineInfo b("test.cpp", 10);
    EXPECT_FALSE(a == b);
}

TEST_F(SourceLineInfoTest_487, EqualitySamePointerOptimization_487) {
    // When file pointers are identical, strcmp should not be needed
    // but the result should still be correct
    const char* file = "same_pointer.cpp";
    Catch::SourceLineInfo a(file, 55);
    Catch::SourceLineInfo b(file, 55);
    EXPECT_TRUE(a == b);
}

TEST_F(SourceLineInfoTest_487, LessThanIrreflexive_487) {
    Catch::SourceLineInfo a("test.cpp", 10);
    EXPECT_FALSE(a < a);
}

TEST_F(SourceLineInfoTest_487, LessThanTransitive_487) {
    Catch::SourceLineInfo a("aaa.cpp", 1);
    Catch::SourceLineInfo b("bbb.cpp", 1);
    Catch::SourceLineInfo c("ccc.cpp", 1);
    if ((a < b) && (b < c)) {
        EXPECT_TRUE(a < c);
    }
}

} // anonymous namespace
