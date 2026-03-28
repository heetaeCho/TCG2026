#include "catch2/internal/catch_test_case_tracker.hpp"
#include "catch2/internal/catch_source_line_info.hpp"
#include "catch2/internal/catch_string_ref.hpp"

#include <gtest/gtest.h>
#include <string>

using namespace Catch;
using namespace Catch::TestCaseTracking;

class NameAndLocationEqualityTest_439 : public ::testing::Test {
protected:
    SourceLineInfo loc1{ "file1.cpp", 10 };
    SourceLineInfo loc2{ "file2.cpp", 20 };
    SourceLineInfo loc3{ "file1.cpp", 10 };
};

// Test that NameAndLocation equals NameAndLocationRef with same name and location
TEST_F(NameAndLocationEqualityTest_439, SameNameAndLocation_ReturnsTrue_439) {
    NameAndLocation nal(std::string("TestName"), loc1);
    NameAndLocationRef nalRef(StringRef("TestName"), loc1);
    
    EXPECT_TRUE(nal == nalRef);
}

// Test that NameAndLocationRef equals NameAndLocation with same name and location (friend operator)
TEST_F(NameAndLocationEqualityTest_439, RefEqualsNal_SameNameAndLocation_ReturnsTrue_439) {
    NameAndLocation nal(std::string("TestName"), loc1);
    NameAndLocationRef nalRef(StringRef("TestName"), loc1);
    
    EXPECT_TRUE(nalRef == nal);
}

// Test that different names return false
TEST_F(NameAndLocationEqualityTest_439, DifferentName_ReturnsFalse_439) {
    NameAndLocation nal(std::string("TestName1"), loc1);
    NameAndLocationRef nalRef(StringRef("TestName2"), loc1);
    
    EXPECT_FALSE(nal == nalRef);
}

// Test that different names return false (ref == nal direction)
TEST_F(NameAndLocationEqualityTest_439, RefEqualsNal_DifferentName_ReturnsFalse_439) {
    NameAndLocation nal(std::string("TestName1"), loc1);
    NameAndLocationRef nalRef(StringRef("TestName2"), loc1);
    
    EXPECT_FALSE(nalRef == nal);
}

// Test that different locations return false
TEST_F(NameAndLocationEqualityTest_439, DifferentLocation_ReturnsFalse_439) {
    NameAndLocation nal(std::string("TestName"), loc1);
    NameAndLocationRef nalRef(StringRef("TestName"), loc2);
    
    EXPECT_FALSE(nal == nalRef);
}

// Test that different locations return false (ref == nal direction)
TEST_F(NameAndLocationEqualityTest_439, RefEqualsNal_DifferentLocation_ReturnsFalse_439) {
    NameAndLocation nal(std::string("TestName"), loc1);
    NameAndLocationRef nalRef(StringRef("TestName"), loc2);
    
    EXPECT_FALSE(nalRef == nal);
}

// Test that different name and location return false
TEST_F(NameAndLocationEqualityTest_439, DifferentNameAndLocation_ReturnsFalse_439) {
    NameAndLocation nal(std::string("TestName1"), loc1);
    NameAndLocationRef nalRef(StringRef("TestName2"), loc2);
    
    EXPECT_FALSE(nal == nalRef);
}

// Test that different name and location return false (ref == nal direction)
TEST_F(NameAndLocationEqualityTest_439, RefEqualsNal_DifferentNameAndLocation_ReturnsFalse_439) {
    NameAndLocation nal(std::string("TestName1"), loc1);
    NameAndLocationRef nalRef(StringRef("TestName2"), loc2);
    
    EXPECT_FALSE(nalRef == nal);
}

// Test with empty name - both empty
TEST_F(NameAndLocationEqualityTest_439, EmptyNames_SameLocation_ReturnsTrue_439) {
    NameAndLocation nal(std::string(""), loc1);
    NameAndLocationRef nalRef(StringRef(""), loc1);
    
    EXPECT_TRUE(nal == nalRef);
}

// Test with empty name on one side
TEST_F(NameAndLocationEqualityTest_439, OneEmptyName_ReturnsFalse_439) {
    NameAndLocation nal(std::string(""), loc1);
    NameAndLocationRef nalRef(StringRef("NonEmpty"), loc1);
    
    EXPECT_FALSE(nal == nalRef);
}

// Test symmetry: nal == ref should give same result as ref == nal
TEST_F(NameAndLocationEqualityTest_439, SymmetryWhenEqual_439) {
    NameAndLocation nal(std::string("SymTest"), loc1);
    NameAndLocationRef nalRef(StringRef("SymTest"), loc1);
    
    bool forward = (nal == nalRef);
    bool reverse = (nalRef == nal);
    EXPECT_EQ(forward, reverse);
}

// Test symmetry when not equal
TEST_F(NameAndLocationEqualityTest_439, SymmetryWhenNotEqual_439) {
    NameAndLocation nal(std::string("Name1"), loc1);
    NameAndLocationRef nalRef(StringRef("Name2"), loc2);
    
    bool forward = (nal == nalRef);
    bool reverse = (nalRef == nal);
    EXPECT_EQ(forward, reverse);
}

// Test same file but different line
TEST_F(NameAndLocationEqualityTest_439, SameFileDifferentLine_ReturnsFalse_439) {
    SourceLineInfo locA{ "same_file.cpp", 1 };
    SourceLineInfo locB{ "same_file.cpp", 2 };
    
    NameAndLocation nal(std::string("TestName"), locA);
    NameAndLocationRef nalRef(StringRef("TestName"), locB);
    
    EXPECT_FALSE(nal == nalRef);
}

// Test that equivalent locations constructed separately still match
TEST_F(NameAndLocationEqualityTest_439, EquivalentLocations_ReturnsTrue_439) {
    SourceLineInfo locA{ "file.cpp", 42 };
    SourceLineInfo locB{ "file.cpp", 42 };
    
    NameAndLocation nal(std::string("Test"), locA);
    NameAndLocationRef nalRef(StringRef("Test"), locB);
    
    EXPECT_TRUE(nal == nalRef);
}

// Test with a long name
TEST_F(NameAndLocationEqualityTest_439, LongName_ReturnsTrue_439) {
    std::string longName(1000, 'a');
    NameAndLocation nal(std::string(longName), loc1);
    NameAndLocationRef nalRef(StringRef(longName), loc1);
    
    EXPECT_TRUE(nal == nalRef);
}

// Test NameAndLocation construction preserves location
TEST_F(NameAndLocationEqualityTest_439, ConstructionPreservesLocation_439) {
    SourceLineInfo loc{ "test.cpp", 99 };
    NameAndLocation nal(std::string("MyTest"), loc);
    
    EXPECT_EQ(nal.location.line, 99u);
}
