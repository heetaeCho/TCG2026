#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include "catch2/internal/catch_test_case_tracker.hpp"



using namespace Catch;

using namespace TestCaseTracking;



TEST_F(NameAndLocationTests_438, ConstructorWithNameAndLocation_438) {

    SourceLineInfo location("test_file.cpp", 10);

    NameAndLocation nameAndLocation(std::string("TestName"), location);



    EXPECT_EQ(nameAndLocation.name, "TestName");

    EXPECT_EQ(nameAndLocation.location.file, "test_file.cpp");

    EXPECT_EQ(nameAndLocation.location.line, 10);

}



TEST_F(NameAndLocationRefTests_438, ConstructorWithNameRefAndLocation_438) {

    SourceLineInfo location("test_file.cpp", 20);

    StringRef name("TestName");

    NameAndLocationRef nameAndLocationRef(name, location);



    EXPECT_EQ(nameAndLocationRef.name, "TestName");

    EXPECT_EQ(nameAndLocationRef.location.file, "test_file.cpp");

    EXPECT_EQ(nameAndLocationRef.location.line, 20);

}



TEST_F(NameAndLocationEqualityTests_438, EqualWithSameNameAndLocation_438) {

    SourceLineInfo location("test_file.cpp", 10);

    NameAndLocation nameAndLocation1(std::string("TestName"), location);

    NameAndLocationRef nameAndLocationRef(nameAndLocation1.name, nameAndLocation1.location);



    EXPECT_TRUE(operator==(nameAndLocation1, nameAndLocationRef));

}



TEST_F(NameAndLocationEqualityTests_438, NotEqualWithDifferentName_438) {

    SourceLineInfo location("test_file.cpp", 10);

    NameAndLocation nameAndLocation1(std::string("TestName"), location);

    NameAndLocationRef nameAndLocationRef(StringRef("DifferentName"), nameAndLocation1.location);



    EXPECT_FALSE(operator==(nameAndLocation1, nameAndLocationRef));

}



TEST_F(NameAndLocationEqualityTests_438, NotEqualWithDifferentLine_438) {

    SourceLineInfo location1("test_file.cpp", 10);

    SourceLineInfo location2("test_file.cpp", 20);

    NameAndLocation nameAndLocation1(std::string("TestName"), location1);

    NameAndLocationRef nameAndLocationRef(nameAndLocation1.name, location2);



    EXPECT_FALSE(operator==(nameAndLocation1, nameAndLocationRef));

}



TEST_F(NameAndLocationEqualityTests_438, NotEqualWithDifferentFile_438) {

    SourceLineInfo location1("test_file.cpp", 10);

    SourceLineInfo location2("different_file.cpp", 10);

    NameAndLocation nameAndLocation1(std::string("TestName"), location1);

    NameAndLocationRef nameAndLocationRef(nameAndLocation1.name, location2);



    EXPECT_FALSE(operator==(nameAndLocation1, nameAndLocationRef));

}
