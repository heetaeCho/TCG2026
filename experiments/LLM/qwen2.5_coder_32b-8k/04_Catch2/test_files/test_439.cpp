#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_test_case_tracker.hpp"



using namespace Catch::TestCaseTracking;



TEST(NameAndLocation_439, ConstructorInitialization_439) {

    SourceLineInfo location("file.cpp", 10);

    NameAndLocation nameAndLocation(std::string("TestName"), location);



    EXPECT_EQ(nameAndLocation.location.file, "file.cpp");

    EXPECT_EQ(nameAndLocation.location.line, 10);

}



TEST(NameAndLocationRef_439, ConstructorInitialization_439) {

    SourceLineInfo location("file.cpp", 10);

    NameAndLocationRef nameAndLocationRef("TestName", location);



    EXPECT_STREQ(nameAndLocationRef.name.data(), "TestName");

    EXPECT_EQ(nameAndLocationRef.location.file, "file.cpp");

    EXPECT_EQ(nameAndLocationRef.location.line, 10);

}



TEST(NameAndLocation_439, MoveConstructorInitialization_439) {

    SourceLineInfo location("file.cpp", 10);

    NameAndLocation originalNameAndLocation(std::string("TestName"), location);



    NameAndLocation movedNameAndLocation = std::move(originalNameAndLocation);



    EXPECT_EQ(movedNameAndLocation.location.file, "file.cpp");

    EXPECT_EQ(movedNameAndLocation.location.line, 10);

}



TEST(NameAndLocationRef_439, EqualityOperatorWithSameValues_439) {

    SourceLineInfo location("file.cpp", 10);

    NameAndLocation nameAndLocation(std::string("TestName"), location);

    NameAndLocationRef nameAndLocationRef("TestName", location);



    EXPECT_TRUE(nameAndLocation == nameAndLocationRef);

}



TEST(NameAndLocationRef_439, EqualityOperatorWithDifferentNames_439) {

    SourceLineInfo location("file.cpp", 10);

    NameAndLocation nameAndLocation(std::string("TestName"), location);

    NameAndLocationRef nameAndLocationRef("OtherName", location);



    EXPECT_FALSE(nameAndLocation == nameAndLocationRef);

}



TEST(NameAndLocationRef_439, EqualityOperatorWithDifferentLocations_439) {

    SourceLineInfo location1("file.cpp", 10);

    SourceLineInfo location2("other_file.cpp", 15);

    NameAndLocation nameAndLocation(std::string("TestName"), location1);

    NameAndLocationRef nameAndLocationRef("TestName", location2);



    EXPECT_FALSE(nameAndLocation == nameAndLocationRef);

}
