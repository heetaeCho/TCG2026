#include <gtest/gtest.h>

#include "TestProjects/Catch2/tools/misc/coverage-helper.cpp"



// Test Fixture for windowsify_path function

class WindowsifyPathTest_884 : public ::testing::Test {

protected:

    // You can set up any common state here if necessary.

};



TEST_F(WindowsifyPathTest_884, NormalOperation_ReplacesSlashes_884) {

    std::string path = "path/to/file";

    std::string expected = "path\\to\\file";

    EXPECT_EQ(windowsify_path(path), expected);

}



TEST_F(WindowsifyPathTest_884, BoundaryCondition_EmptyString_884) {

    std::string path = "";

    std::string expected = "";

    EXPECT_EQ(windowsify_path(path), expected);

}



TEST_F(WindowsifyPathTest_884, BoundaryCondition_SingleCharacterNoSlash_884) {

    std::string path = "a";

    std::string expected = "a";

    EXPECT_EQ(windowsify_path(path), expected);

}



TEST_F(WindowsifyPathTest_884, BoundaryCondition_SingleCharacterSlash_884) {

    std::string path = "/";

    std::string expected = "\\";

    EXPECT_EQ(windowsify_path(path), expected);

}



TEST_F(WindowsifyPathTest_884, EdgeCase_MultipleConsecutiveSlashes_884) {

    std::string path = "path///to///file";

    std::string expected = "path\\\\\\to\\\\\\file";

    EXPECT_EQ(windowsify_path(path), expected);

}



TEST_F(WindowsifyPathTest_884, EdgeCase_NoSlashes_884) {

    std::string path = "path\\to\\file";

    std::string expected = "path\\to\\file";

    EXPECT_EQ(windowsify_path(path), expected);

}
