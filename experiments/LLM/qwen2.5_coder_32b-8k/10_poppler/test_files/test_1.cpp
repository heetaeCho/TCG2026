#include <gtest/gtest.h>

#include "gbasename.cc"



class GBaseNameTest_1 : public ::testing::Test {

protected:

    // You can add any necessary setup or teardown here if needed.

};



TEST_F(GBaseNameTest_1, NormalOperationWithExtension_1) {

    EXPECT_EQ(gbasename("path/to/file.txt"), "file.txt");

}



TEST_F(GBaseNameTest_1, NormalOperationWithoutExtension_1) {

    EXPECT_EQ(gbasename("path/to/file"), "file");

}



TEST_F(GBaseNameTest_1, SingleFileInRoot_1) {

    EXPECT_EQ(gbasename("/file.txt"), "file.txt");

}



TEST_F(GBaseNameTest_1, RootDirectory_1) {

    EXPECT_EQ(gbasename("/"), "");

}



TEST_F(GBaseNameTest_1, EmptyPath_1) {

    EXPECT_EQ(gbasename(""), "");

}



TEST_F(GBaseNameTest_1, TrailingSlash_1) {

    EXPECT_EQ(gbasename("path/to/"), "");

}



TEST_F(GBaseNameTest_1, DoubleSlashes_1) {

    EXPECT_EQ(gbasename("path//to//file.txt"), "file.txt");

}



TEST_F(GBaseNameTest_1, DotFileInDirectory_1) {

    EXPECT_EQ(gbasename("path/to/.dotfile"), ".dotfile");

}



TEST_F(GBaseNameTest_1, HiddenFile_1) {

    EXPECT_EQ(gbasename(".hiddenfile"), ".hiddenfile");

}



TEST_F(GBaseNameTest_1, FilenameOnlyWithExtension_1) {

    EXPECT_EQ(gbasename("filename.txt"), "filename.txt");

}



TEST_F(GBaseNameTest_1, FilenameOnlyWithoutExtension_1) {

    EXPECT_EQ(gbasename("filename"), "filename");

}
