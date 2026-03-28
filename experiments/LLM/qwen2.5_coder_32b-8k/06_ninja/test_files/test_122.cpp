#include <gtest/gtest.h>

#include "./TestProjects/ninja/src/msvc_helper-win32.cc"  // Adjust path as necessary



TEST(EscapeForDepfileTest_122, NormalOperationWithSpaces_122) {

    EXPECT_EQ(EscapeForDepfile("path with spaces"), "path\\ with\\ spaces");

}



TEST(EscapeForDepfileTest_122, NoSpacesInPath_122) {

    EXPECT_EQ(EscapeForDepfile("pathwithnospaces"), "pathwithnospaces");

}



TEST(EscapeForDepfileTest_122, SingleSpaceAtStart_122) {

    EXPECT_EQ(EscapeForDepfile(" path"), "\\ path");

}



TEST(EscapeForDepfileTest_122, SingleSpaceAtEnd_122) {

    EXPECT_EQ(EscapeForDepfile("path "), "path\\ ");

}



TEST(EscapeForDepfileTest_122, MultipleSpacesInPath_122) {

    EXPECT_EQ(EscapeForDepfile("multiple   spaces"), "multiple\\ \\ \\ spaces");

}



TEST(EscapeForDepfileTest_122, EmptyString_122) {

    EXPECT_EQ(EscapeForDepfile(""), "");

}
