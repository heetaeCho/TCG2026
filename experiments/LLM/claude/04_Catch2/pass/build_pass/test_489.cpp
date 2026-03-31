#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "catch2/internal/catch_source_line_info.hpp"

// Test fixture for SourceLineInfo tests
class SourceLineInfoTest_489 : public ::testing::Test {
protected:
    // Helper to get the string representation of a SourceLineInfo
    std::string toString(const Catch::SourceLineInfo& info) {
        std::ostringstream oss;
        oss << info;
        return oss.str();
    }
};

// ==================== Construction Tests ====================

TEST_F(SourceLineInfoTest_489, ConstructWithFileAndLine_489) {
    Catch::SourceLineInfo info("test.cpp", 42);
    EXPECT_STREQ(info.file, "test.cpp");
    EXPECT_EQ(info.line, 42u);
}

TEST_F(SourceLineInfoTest_489, ConstructWithZeroLine_489) {
    Catch::SourceLineInfo info("file.cpp", 0);
    EXPECT_STREQ(info.file, "file.cpp");
    EXPECT_EQ(info.line, 0u);
}

TEST_F(SourceLineInfoTest_489, ConstructWithLargeLine_489) {
    Catch::SourceLineInfo info("file.cpp", 999999);
    EXPECT_STREQ(info.file, "file.cpp");
    EXPECT_EQ(info.line, 999999u);
}

TEST_F(SourceLineInfoTest_489, ConstructWithEmptyFileName_489) {
    Catch::SourceLineInfo info("", 10);
    EXPECT_STREQ(info.file, "");
    EXPECT_EQ(info.line, 10u);
}

// ==================== Equality Operator Tests ====================

TEST_F(SourceLineInfoTest_489, EqualityOperator_SameFileAndLine_489) {
    Catch::SourceLineInfo a("test.cpp", 42);
    Catch::SourceLineInfo b("test.cpp", 42);
    EXPECT_TRUE(a == b);
}

TEST_F(SourceLineInfoTest_489, EqualityOperator_DifferentFile_489) {
    Catch::SourceLineInfo a("test1.cpp", 42);
    Catch::SourceLineInfo b("test2.cpp", 42);
    EXPECT_FALSE(a == b);
}

TEST_F(SourceLineInfoTest_489, EqualityOperator_DifferentLine_489) {
    Catch::SourceLineInfo a("test.cpp", 42);
    Catch::SourceLineInfo b("test.cpp", 43);
    EXPECT_FALSE(a == b);
}

TEST_F(SourceLineInfoTest_489, EqualityOperator_BothDifferent_489) {
    Catch::SourceLineInfo a("test1.cpp", 10);
    Catch::SourceLineInfo b("test2.cpp", 20);
    EXPECT_FALSE(a == b);
}

TEST_F(SourceLineInfoTest_489, EqualityOperator_SameObject_489) {
    Catch::SourceLineInfo a("test.cpp", 42);
    EXPECT_TRUE(a == a);
}

// ==================== Less-Than Operator Tests ====================

TEST_F(SourceLineInfoTest_489, LessThanOperator_SameFileSmallerLine_489) {
    Catch::SourceLineInfo a("test.cpp", 10);
    Catch::SourceLineInfo b("test.cpp", 20);
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST_F(SourceLineInfoTest_489, LessThanOperator_SameFileAndLine_489) {
    Catch::SourceLineInfo a("test.cpp", 42);
    Catch::SourceLineInfo b("test.cpp", 42);
    EXPECT_FALSE(a < b);
    EXPECT_FALSE(b < a);
}

TEST_F(SourceLineInfoTest_489, LessThanOperator_DifferentFile_489) {
    Catch::SourceLineInfo a("aaa.cpp", 100);
    Catch::SourceLineInfo b("bbb.cpp", 1);
    // file comparison should come first (lexicographic)
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST_F(SourceLineInfoTest_489, LessThanOperator_SameFileLargerLine_489) {
    Catch::SourceLineInfo a("test.cpp", 50);
    Catch::SourceLineInfo b("test.cpp", 10);
    EXPECT_FALSE(a < b);
    EXPECT_TRUE(b < a);
}

TEST_F(SourceLineInfoTest_489, LessThanOperator_SelfComparison_489) {
    Catch::SourceLineInfo a("test.cpp", 42);
    EXPECT_FALSE(a < a);
}

// ==================== Stream Output Operator Tests ====================

TEST_F(SourceLineInfoTest_489, StreamOutput_NormalFileAndLine_489) {
    Catch::SourceLineInfo info("test.cpp", 42);
    std::string result = toString(info);
#ifndef __GNUG__
    EXPECT_EQ(result, "test.cpp(42)");
#else
    EXPECT_EQ(result, "test.cpp:42");
#endif
}

TEST_F(SourceLineInfoTest_489, StreamOutput_ZeroLine_489) {
    Catch::SourceLineInfo info("file.cpp", 0);
    std::string result = toString(info);
#ifndef __GNUG__
    EXPECT_EQ(result, "file.cpp(0)");
#else
    EXPECT_EQ(result, "file.cpp:0");
#endif
}

TEST_F(SourceLineInfoTest_489, StreamOutput_LargeLine_489) {
    Catch::SourceLineInfo info("main.cpp", 123456);
    std::string result = toString(info);
#ifndef __GNUG__
    EXPECT_EQ(result, "main.cpp(123456)");
#else
    EXPECT_EQ(result, "main.cpp:123456");
#endif
}

TEST_F(SourceLineInfoTest_489, StreamOutput_EmptyFileName_489) {
    Catch::SourceLineInfo info("", 5);
    std::string result = toString(info);
#ifndef __GNUG__
    EXPECT_EQ(result, "(5)");
#else
    EXPECT_EQ(result, ":5");
#endif
}

TEST_F(SourceLineInfoTest_489, StreamOutput_PathInFileName_489) {
    Catch::SourceLineInfo info("/home/user/project/src/test.cpp", 99);
    std::string result = toString(info);
#ifndef __GNUG__
    EXPECT_EQ(result, "/home/user/project/src/test.cpp(99)");
#else
    EXPECT_EQ(result, "/home/user/project/src/test.cpp:99");
#endif
}

TEST_F(SourceLineInfoTest_489, StreamOutput_ReturnsStreamReference_489) {
    Catch::SourceLineInfo info("test.cpp", 1);
    std::ostringstream oss;
    std::ostream& ref = (oss << info);
    EXPECT_EQ(&ref, &oss);
}

TEST_F(SourceLineInfoTest_489, StreamOutput_Chaining_489) {
    Catch::SourceLineInfo info1("a.cpp", 1);
    Catch::SourceLineInfo info2("b.cpp", 2);
    std::ostringstream oss;
    oss << info1 << " - " << info2;
    std::string result = oss.str();
#ifndef __GNUG__
    EXPECT_EQ(result, "a.cpp(1) - b.cpp(2)");
#else
    EXPECT_EQ(result, "a.cpp:1 - b.cpp:2");
#endif
}

// ==================== Boundary Tests ====================

TEST_F(SourceLineInfoTest_489, BoundaryMaxSizeT_489) {
    std::size_t maxLine = std::numeric_limits<std::size_t>::max();
    Catch::SourceLineInfo info("test.cpp", maxLine);
    EXPECT_EQ(info.line, maxLine);
    // Just verify it doesn't crash when streaming
    std::ostringstream oss;
    oss << info;
    EXPECT_FALSE(oss.str().empty());
}

TEST_F(SourceLineInfoTest_489, ConstructWithLineOne_489) {
    Catch::SourceLineInfo info("test.cpp", 1);
    EXPECT_EQ(info.line, 1u);
    std::string result = toString(info);
#ifndef __GNUG__
    EXPECT_EQ(result, "test.cpp(1)");
#else
    EXPECT_EQ(result, "test.cpp:1");
#endif
}

// ==================== Consistency Tests ====================

TEST_F(SourceLineInfoTest_489, EqualObjectsAreNotLessThan_489) {
    Catch::SourceLineInfo a("test.cpp", 42);
    Catch::SourceLineInfo b("test.cpp", 42);
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a < b);
    EXPECT_FALSE(b < a);
}

TEST_F(SourceLineInfoTest_489, LessThanImpliesNotEqual_489) {
    Catch::SourceLineInfo a("test.cpp", 10);
    Catch::SourceLineInfo b("test.cpp", 20);
    if (a < b || b < a) {
        EXPECT_FALSE(a == b);
    }
}

TEST_F(SourceLineInfoTest_489, Transitivity_489) {
    Catch::SourceLineInfo a("a.cpp", 1);
    Catch::SourceLineInfo b("b.cpp", 1);
    Catch::SourceLineInfo c("c.cpp", 1);
    if (a < b && b < c) {
        EXPECT_TRUE(a < c);
    }
}
