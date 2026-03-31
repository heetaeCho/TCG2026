#include <gtest/gtest.h>
#include <string>

// Include the header under test
#include "catch2/internal/catch_test_case_tracker.hpp"

using Catch::TestCaseTracking::NameAndLocation;
using Catch::SourceLineInfo;

class NameAndLocationTest_437 : public ::testing::Test {
protected:
    // Helper to create SourceLineInfo
    SourceLineInfo makeSLI(const char* file, std::size_t line) {
        return SourceLineInfo(file, line);
    }
};

// Test that two NameAndLocation objects with the same name and location are equal
TEST_F(NameAndLocationTest_437, EqualObjectsAreEqual_437) {
    SourceLineInfo sli1("file.cpp", 10);
    SourceLineInfo sli2("file.cpp", 10);
    NameAndLocation a(std::string("test_name"), sli1);
    NameAndLocation b(std::string("test_name"), sli2);

    EXPECT_FALSE(a != b);
}

// Test that two NameAndLocation objects with different names are not equal
TEST_F(NameAndLocationTest_437, DifferentNamesAreNotEqual_437) {
    SourceLineInfo sli1("file.cpp", 10);
    SourceLineInfo sli2("file.cpp", 10);
    NameAndLocation a(std::string("name_a"), sli1);
    NameAndLocation b(std::string("name_b"), sli2);

    EXPECT_TRUE(a != b);
}

// Test that two NameAndLocation objects with different file locations are not equal
TEST_F(NameAndLocationTest_437, DifferentFilesAreNotEqual_437) {
    SourceLineInfo sli1("file1.cpp", 10);
    SourceLineInfo sli2("file2.cpp", 10);
    NameAndLocation a(std::string("test_name"), sli1);
    NameAndLocation b(std::string("test_name"), sli2);

    EXPECT_TRUE(a != b);
}

// Test that two NameAndLocation objects with different line numbers are not equal
TEST_F(NameAndLocationTest_437, DifferentLinesAreNotEqual_437) {
    SourceLineInfo sli1("file.cpp", 10);
    SourceLineInfo sli2("file.cpp", 20);
    NameAndLocation a(std::string("test_name"), sli1);
    NameAndLocation b(std::string("test_name"), sli2);

    EXPECT_TRUE(a != b);
}

// Test that two NameAndLocation objects with different names AND different locations are not equal
TEST_F(NameAndLocationTest_437, DifferentNameAndLocationAreNotEqual_437) {
    SourceLineInfo sli1("file1.cpp", 10);
    SourceLineInfo sli2("file2.cpp", 20);
    NameAndLocation a(std::string("name_a"), sli1);
    NameAndLocation b(std::string("name_b"), sli2);

    EXPECT_TRUE(a != b);
}

// Test with empty names - same empty names and same location should be equal
TEST_F(NameAndLocationTest_437, EmptyNamesAreEqual_437) {
    SourceLineInfo sli1("file.cpp", 1);
    SourceLineInfo sli2("file.cpp", 1);
    NameAndLocation a(std::string(""), sli1);
    NameAndLocation b(std::string(""), sli2);

    EXPECT_FALSE(a != b);
}

// Test with empty name vs non-empty name
TEST_F(NameAndLocationTest_437, EmptyVsNonEmptyNameNotEqual_437) {
    SourceLineInfo sli1("file.cpp", 1);
    SourceLineInfo sli2("file.cpp", 1);
    NameAndLocation a(std::string(""), sli1);
    NameAndLocation b(std::string("something"), sli2);

    EXPECT_TRUE(a != b);
}

// Test symmetry of inequality operator
TEST_F(NameAndLocationTest_437, InequalityIsSymmetric_437) {
    SourceLineInfo sli1("file1.cpp", 10);
    SourceLineInfo sli2("file2.cpp", 20);
    NameAndLocation a(std::string("name_a"), sli1);
    NameAndLocation b(std::string("name_b"), sli2);

    EXPECT_EQ((a != b), (b != a));
}

// Test that line 0 boundary works
TEST_F(NameAndLocationTest_437, LineZeroBoundary_437) {
    SourceLineInfo sli1("file.cpp", 0);
    SourceLineInfo sli2("file.cpp", 0);
    NameAndLocation a(std::string("test"), sli1);
    NameAndLocation b(std::string("test"), sli2);

    EXPECT_FALSE(a != b);
}

// Test self-consistency: an object should be equal to itself (not not-equal)
TEST_F(NameAndLocationTest_437, SelfEqualityConsistency_437) {
    SourceLineInfo sli("file.cpp", 42);
    NameAndLocation a(std::string("my_test"), sli);

    EXPECT_FALSE(a != a);
}

// Test that NameAndLocation stores the name correctly
TEST_F(NameAndLocationTest_437, ConstructorStoresName_437) {
    SourceLineInfo sli("file.cpp", 5);
    NameAndLocation a(std::string("hello_world"), sli);

    EXPECT_EQ(a.name, "hello_world");
}

// Test that NameAndLocation stores the location correctly
TEST_F(NameAndLocationTest_437, ConstructorStoresLocation_437) {
    SourceLineInfo sli("myfile.cpp", 99);
    NameAndLocation a(std::string("test"), sli);

    EXPECT_EQ(a.location.line, 99u);
    EXPECT_STREQ(a.location.file, "myfile.cpp");
}
