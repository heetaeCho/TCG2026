// File: name_and_location_eq_tests_438.cpp
#include <gtest/gtest.h>

#include "catch2/internal/catch_stringref.hpp"
#include "catch2/internal/catch_source_line_info.hpp"
#include "catch2/internal/catch_test_case_tracker.hpp"

using Catch::StringRef;
using Catch::SourceLineInfo;
using Catch::TestCaseTracking::NameAndLocation;
using Catch::TestCaseTracking::NameAndLocationRef;

class NameAndLocationEqTest_438 : public ::testing::Test {};

// Normal operation: identical name + identical location -> equal
TEST_F(NameAndLocationEqTest_438, Equal_SameNameSameFileSameLine_438) {
    SourceLineInfo loc{"file_a.cpp", 123};
    NameAndLocation lhs{std::string("MyTest"), loc};
    NameAndLocationRef rhs{StringRef("MyTest"), loc};

    EXPECT_TRUE(lhs == rhs);
}

// Boundary: empty names with identical location -> equal
TEST_F(NameAndLocationEqTest_438, Equal_EmptyNameSameLocation_438) {
    SourceLineInfo loc{"empty.cpp", 1};
    NameAndLocation lhs{std::string(""), loc};
    NameAndLocationRef rhs{StringRef("", 0), loc};

    EXPECT_TRUE(lhs == rhs);
}

// Error/negative case: same name, different line -> not equal
TEST_F(NameAndLocationEqTest_438, NotEqual_SameFileDifferentLine_438) {
    SourceLineInfo loc1{"file_b.cpp", 10};
    SourceLineInfo loc2{"file_b.cpp", 11};
    NameAndLocation lhs{std::string("LineSensitiveTest"), loc1};
    NameAndLocationRef rhs{StringRef("LineSensitiveTest"), loc2};

    EXPECT_FALSE(lhs == rhs);
}

// Error/negative case: same name, different file -> not equal
TEST_F(NameAndLocationEqTest_438, NotEqual_DifferentFileSameLine_438) {
    SourceLineInfo loc1{"file_c.cpp", 42};
    SourceLineInfo loc2{"file_d.cpp", 42};
    NameAndLocation lhs{std::string("FileSensitiveTest"), loc1};
    NameAndLocationRef rhs{StringRef("FileSensitiveTest"), loc2};

    EXPECT_FALSE(lhs == rhs);
}

// Error/negative case: different name, identical location -> not equal
TEST_F(NameAndLocationEqTest_438, NotEqual_DifferentNameSameLocation_438) {
    SourceLineInfo loc{"same_loc.cpp", 7};
    NameAndLocation lhs{std::string("Alpha"), loc};
    NameAndLocationRef rhs{StringRef("Beta"), loc};

    EXPECT_FALSE(lhs == rhs);
}

// Boundary: name is prefix of other (non-equal) with identical location -> not equal
TEST_F(NameAndLocationEqTest_438, NotEqual_NameIsPrefixOfOther_438) {
    SourceLineInfo loc{"prefix.cpp", 77};
    NameAndLocation lhs{std::string("Test"), loc};
    NameAndLocationRef rhs{StringRef("TestCase"), loc};

    EXPECT_FALSE(lhs == rhs);
}
