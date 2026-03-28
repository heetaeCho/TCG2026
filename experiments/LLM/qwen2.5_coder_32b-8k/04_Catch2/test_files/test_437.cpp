#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_test_case_tracker.hpp"



using namespace Catch::TestCaseTracking;



// Fixture for NameAndLocation tests

class NameAndLocationTest_437 : public ::testing::Test {

protected:

    SourceLineInfo sourceLineInfo;

    std::string name = "TestName";



    void SetUp() override {

        sourceLineInfo = SourceLineInfo("file.cpp", 123);

    }

};



// Test normal operation

TEST_F(NameAndLocationTest_437, ConstructionWithValidParameters_437) {

    NameAndLocation nameAndLocation(std::move(name), sourceLineInfo);

    EXPECT_EQ(nameAndLocation.location.file, "file.cpp");

    EXPECT_EQ(nameAndLocation.location.line, 123);

}



// Test boundary conditions

TEST_F(NameAndLocationTest_437, ConstructionWithEmptyName_437) {

    std::string emptyName = "";

    NameAndLocation nameAndLocation(std::move(emptyName), sourceLineInfo);

    EXPECT_EQ(nameAndLocation.location.file, "file.cpp");

    EXPECT_EQ(nameAndLocation.location.line, 123);

}



TEST_F(NameAndLocationTest_437, ConstructionWithDefaultSourceLineInfo_437) {

    SourceLineInfo defaultSourceLineInfo;

    NameAndLocation nameAndLocation(std::move(name), defaultSourceLineInfo);

    EXPECT_EQ(nameAndLocation.name, "TestName");

    EXPECT_EQ(nameAndLocation.location.file, "");

    EXPECT_EQ(nameAndLocation.location.line, 0);

}



// Test exceptional or error cases (if observable through the interface)

// In this case, there are no obvious exceptional/error cases as the constructor does not throw



// Verification of external interactions

// There are no external collaborators or callbacks to verify in this class



// Additional tests for comparison operators can be added if needed

TEST_F(NameAndLocationTest_437, EqualityOperatorForDifferentInstances_437) {

    NameAndLocation nameAndLocation1(std::move(name), sourceLineInfo);

    SourceLineInfo anotherSourceLineInfo("another_file.cpp", 456);

    std::string anotherName = "AnotherName";

    NameAndLocation nameAndLocation2(std::move(anotherName), anotherSourceLineInfo);



    EXPECT_NE(nameAndLocation1, nameAndLocation2);

}



TEST_F(NameAndLocationTest_437, EqualityOperatorForSameInstances_437) {

    NameAndLocation nameAndLocation1("SameName", sourceLineInfo);

    NameAndLocation nameAndLocation2("SameName", sourceLineInfo);



    EXPECT_EQ(nameAndLocation1, nameAndLocation2);

}
