#include <gtest/gtest.h>

#include "GooString.h"

#include "gfile.h"



class AppendToPathTest_37 : public ::testing::Test {

protected:

    void SetUp() override {

        path = std::make_unique<GooString>("/test");

        fileName = "file";

    }



    void TearDown() override {

        path.reset();

    }



    std::unique_ptr<GooString> path;

    const char* fileName;

};



TEST_F(AppendToPathTest_37, NormalOperation_37) {

    GooString* result = appendToPath(path.get(), fileName);

    EXPECT_EQ(result->toStr(), "/test/file");

}



TEST_F(AppendToPathTest_37, PathAlreadyEndsWithSlash_37) {

    path.reset(new GooString("/test/"));

    GooString* result = appendToPath(path.get(), fileName);

    EXPECT_EQ(result->toStr(), "/test/file");

}



TEST_F(AppendToPathTest_37, FileNameStartsWithDot_37) {

    fileName = ".";

    GooString* result = appendToPath(path.get(), fileName);

    EXPECT_EQ(result->toStr(), "/test");

}



TEST_F(AppendToPathTest_37, FileNameIsDoubleDot_37) {

    fileName = "..";

    GooString* result = appendToPath(path.get(), fileName);

    EXPECT_EQ(result->toStr(), "/");

}



TEST_F(AppendToPathTest_37, PathIsEmpty_37) {

    path.reset(new GooString(""));

    GooString* result = appendToPath(path.get(), fileName);

    EXPECT_EQ(result->toStr(), "/file");

}



TEST_F(AppendToPathTest_37, FileNameIsEmpty_37) {

    fileName = "";

    GooString* result = appendToPath(path.get(), fileName);

    EXPECT_EQ(result->toStr(), "/test/");

}



TEST_F(AppendToPathTest_37, PathIsSingleSlash_37) {

    path.reset(new GooString("/"));

    GooString* result = appendToPath(path.get(), fileName);

    EXPECT_EQ(result->toStr(), "/file");

}



TEST_F(AppendToPathTest_37, FileNameContainsSlash_37) {

    fileName = "dir/file";

    GooString* result = appendToPath(path.get(), fileName);

    EXPECT_EQ(result->toStr(), "/test/dir/file");

}
