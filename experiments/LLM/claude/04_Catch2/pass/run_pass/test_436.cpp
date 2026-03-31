#include <gtest/gtest.h>
#include <string>

// Include the headers under test
#include "catch2/internal/catch_test_case_tracker.hpp"
#include "catch2/internal/catch_source_line_info.hpp"

using Catch::SourceLineInfo;
using Catch::TestCaseTracking::NameAndLocation;

// Test fixture
class NameAndLocationTest_436 : public ::testing::Test {
protected:
    // Helper to create SourceLineInfo
    static SourceLineInfo makeSLI(const char* file, std::size_t line) {
        return SourceLineInfo(file, line);
    }
};

// ==================== Construction Tests ====================

TEST_F(NameAndLocationTest_436, ConstructWithNameAndLocation_436) {
    SourceLineInfo loc("test_file.cpp", 42);
    NameAndLocation nal(std::string("TestName"), loc);
    
    EXPECT_EQ(nal.location.line, 42u);
    EXPECT_STREQ(nal.location.file, "test_file.cpp");
}

TEST_F(NameAndLocationTest_436, ConstructWithEmptyName_436) {
    SourceLineInfo loc("file.cpp", 1);
    NameAndLocation nal(std::string(""), loc);
    
    EXPECT_EQ(nal.location.line, 1u);
}

// ==================== Equality Tests ====================

TEST_F(NameAndLocationTest_436, EqualityWithSameNameAndLocation_436) {
    SourceLineInfo loc1("file.cpp", 10);
    SourceLineInfo loc2("file.cpp", 10);
    NameAndLocation nal1(std::string("Test"), loc1);
    NameAndLocation nal2(std::string("Test"), loc2);
    
    EXPECT_TRUE(nal1 == nal2);
}

TEST_F(NameAndLocationTest_436, InequalityWithDifferentLines_436) {
    SourceLineInfo loc1("file.cpp", 10);
    SourceLineInfo loc2("file.cpp", 20);
    NameAndLocation nal1(std::string("Test"), loc1);
    NameAndLocation nal2(std::string("Test"), loc2);
    
    EXPECT_FALSE(nal1 == nal2);
}

TEST_F(NameAndLocationTest_436, InequalityWithDifferentNames_436) {
    SourceLineInfo loc1("file.cpp", 10);
    SourceLineInfo loc2("file.cpp", 10);
    NameAndLocation nal1(std::string("TestA"), loc1);
    NameAndLocation nal2(std::string("TestB"), loc2);
    
    EXPECT_FALSE(nal1 == nal2);
}

TEST_F(NameAndLocationTest_436, InequalityWithDifferentFiles_436) {
    SourceLineInfo loc1("file1.cpp", 10);
    SourceLineInfo loc2("file2.cpp", 10);
    NameAndLocation nal1(std::string("Test"), loc1);
    NameAndLocation nal2(std::string("Test"), loc2);
    
    EXPECT_FALSE(nal1 == nal2);
}

TEST_F(NameAndLocationTest_436, InequalityWithDifferentNamesAndLines_436) {
    SourceLineInfo loc1("file.cpp", 10);
    SourceLineInfo loc2("file.cpp", 20);
    NameAndLocation nal1(std::string("TestA"), loc1);
    NameAndLocation nal2(std::string("TestB"), loc2);
    
    EXPECT_FALSE(nal1 == nal2);
}

TEST_F(NameAndLocationTest_436, EqualityWithEmptyNames_436) {
    SourceLineInfo loc1("file.cpp", 5);
    SourceLineInfo loc2("file.cpp", 5);
    NameAndLocation nal1(std::string(""), loc1);
    NameAndLocation nal2(std::string(""), loc2);
    
    EXPECT_TRUE(nal1 == nal2);
}

TEST_F(NameAndLocationTest_436, InequalityEmptyVsNonEmptyName_436) {
    SourceLineInfo loc1("file.cpp", 5);
    SourceLineInfo loc2("file.cpp", 5);
    NameAndLocation nal1(std::string(""), loc1);
    NameAndLocation nal2(std::string("NonEmpty"), loc2);
    
    EXPECT_FALSE(nal1 == nal2);
}

TEST_F(NameAndLocationTest_436, EqualityWithLineZero_436) {
    SourceLineInfo loc1("file.cpp", 0);
    SourceLineInfo loc2("file.cpp", 0);
    NameAndLocation nal1(std::string("Test"), loc1);
    NameAndLocation nal2(std::string("Test"), loc2);
    
    EXPECT_TRUE(nal1 == nal2);
}

TEST_F(NameAndLocationTest_436, EqualityWithLargeLineNumber_436) {
    SourceLineInfo loc1("file.cpp", 999999);
    SourceLineInfo loc2("file.cpp", 999999);
    NameAndLocation nal1(std::string("Test"), loc1);
    NameAndLocation nal2(std::string("Test"), loc2);
    
    EXPECT_TRUE(nal1 == nal2);
}

TEST_F(NameAndLocationTest_436, EqualitySameObject_436) {
    SourceLineInfo loc("file.cpp", 42);
    NameAndLocation nal(std::string("Test"), loc);
    
    EXPECT_TRUE(nal == nal);
}

TEST_F(NameAndLocationTest_436, InequalityDifferentFilesSameLine_436) {
    SourceLineInfo loc1("a.cpp", 1);
    SourceLineInfo loc2("b.cpp", 1);
    NameAndLocation nal1(std::string("Same"), loc1);
    NameAndLocation nal2(std::string("Same"), loc2);
    
    // Same name and line, but different file - should be unequal
    // because SourceLineInfo::operator== checks file as well
    EXPECT_FALSE(nal1 == nal2);
}

TEST_F(NameAndLocationTest_436, EqualityWithLongName_436) {
    std::string longName(1000, 'x');
    SourceLineInfo loc1("file.cpp", 10);
    SourceLineInfo loc2("file.cpp", 10);
    NameAndLocation nal1(std::string(longName), loc1);
    NameAndLocation nal2(std::string(longName), loc2);
    
    EXPECT_TRUE(nal1 == nal2);
}

// Test that the line check short-circuits: different lines returns false early
TEST_F(NameAndLocationTest_436, DifferentLineShortCircuit_436) {
    SourceLineInfo loc1("file.cpp", 1);
    SourceLineInfo loc2("file.cpp", 2);
    NameAndLocation nal1(std::string("A"), loc1);
    NameAndLocation nal2(std::string("A"), loc2);
    
    EXPECT_FALSE(nal1 == nal2);
}

TEST_F(NameAndLocationTest_436, SameLineDifferentFileDifferentName_436) {
    SourceLineInfo loc1("file1.cpp", 10);
    SourceLineInfo loc2("file2.cpp", 10);
    NameAndLocation nal1(std::string("NameA"), loc1);
    NameAndLocation nal2(std::string("NameB"), loc2);
    
    EXPECT_FALSE(nal1 == nal2);
}
