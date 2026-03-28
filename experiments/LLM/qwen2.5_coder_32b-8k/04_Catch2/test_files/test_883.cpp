#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/Catch2/tools/misc/coverage-helper.cpp"

#include <stdexcept>



using namespace testing;



TEST(catch_path_883, NormalOperation_883) {

    EXPECT_EQ(catch_path("/home/user/project/catch/include"), "/home/user/project");

    EXPECT_EQ(catch_path("C:\\dev\\catch2\\tests"), "C:");

}



TEST(catch_path_883, CaseInsensitivePath_883) {

    EXPECT_EQ(catch_path("/home/user/CATCH/include"), "/home/user");

    EXPECT_EQ(catch_path("c:\\Catch2\\examples"), "c:");

}



TEST(catch_path_883, BoundaryConditionEmptyString_883) {

    EXPECT_THROW(catch_path(""), std::domain_error);

}



TEST(catch_path_883, BoundaryConditionNoCatchFound_883) {

    EXPECT_THROW(catch_path("/home/user/project/include"), std::domain_error);

}



TEST(catch_path_883, ExceptionalPathSingleCharacter_883) {

    EXPECT_THROW(catch_path("a"), std::domain_error);

}



TEST(catch_path_883, ExceptionalPathNoSeparator_883) {

    EXPECT_EQ(catch_path("/home/user/projectcatchinclude"), "/home/user/project");

}
