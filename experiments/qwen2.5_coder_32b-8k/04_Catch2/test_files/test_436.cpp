#include <gtest/gtest.h>

#include "catch2/internal/catch_test_case_tracker.hpp"

#include <string>



using namespace Catch;

using namespace TestCaseTracking;



TEST_F(NameAndLocationTest_436, ConstructorSetsCorrectNameAndLocation_436) {

    SourceLineInfo location("test_file.cpp", 10);

    NameAndLocation nameAndLocation(std::string("TestName"), location);

    

    EXPECT_EQ(nameAndLocation.name, "TestName");

    EXPECT_EQ(nameAndLocation.location.file, "test_file.cpp");

    EXPECT_EQ(nameAndLocation.location.line, 10);

}



TEST_F(NameAndLocationTest_436, OperatorEquality_ReturnsTrueForSameValues_436) {

    SourceLineInfo location1("test_file.cpp", 10);

    NameAndLocation nameAndLocation1(std::string("TestName"), location1);



    SourceLineInfo location2("test_file.cpp", 10);

    NameAndLocation nameAndLocation2(std::string("TestName"), location2);



    EXPECT_TRUE(nameAndLocation1 == nameAndLocation2);

}



TEST_F(NameAndLocationTest_436, OperatorEquality_ReturnsFalseForDifferentNames_436) {

    SourceLineInfo location1("test_file.cpp", 10);

    NameAndLocation nameAndLocation1(std::string("TestName1"), location1);



    SourceLineInfo location2("test_file.cpp", 10);

    NameAndLocation nameAndLocation2(std::string("TestName2"), location2);



    EXPECT_FALSE(nameAndLocation1 == nameAndLocation2);

}



TEST_F(NameAndLocationTest_436, OperatorEquality_ReturnsFalseForDifferentFiles_436) {

    SourceLineInfo location1("test_file1.cpp", 10);

    NameAndLocation nameAndLocation1(std::string("TestName"), location1);



    SourceLineInfo location2("test_file2.cpp", 10);

    NameAndLocation nameAndLocation2(std::string("TestName"), location2);



    EXPECT_FALSE(nameAndLocation1 == nameAndLocation2);

}



TEST_F(NameAndLocationTest_436, OperatorEquality_ReturnsFalseForDifferentLines_436) {

    SourceLineInfo location1("test_file.cpp", 10);

    NameAndLocation nameAndLocation1(std::string("TestName"), location1);



    SourceLineInfo location2("test_file.cpp", 20);

    NameAndLocation nameAndLocation2(std::string("TestName"), location2);



    EXPECT_FALSE(nameAndLocation1 == nameAndLocation2);

}
