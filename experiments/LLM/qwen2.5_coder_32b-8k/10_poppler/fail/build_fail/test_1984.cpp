#include <gtest/gtest.h>

#include "TestProjects/poppler/goo/GooString.h"

#include "TestProjects/poppler/poppler/GlobalParamsWin.cc"



TEST(replaceSuffixTest_1984, ReplaceSuffix_NormalOperation_1984) {

    GooString path("example.txt");

    replaceSuffix(&path, ".txt", ".pdf");

    EXPECT_EQ(path.toStr(), "example.pdf");

}



TEST(replaceSuffixTest_1984, ReplaceSuffix_SuffixNotPresent_1984) {

    GooString path("example.doc");

    replaceSuffix(&path, ".txt", ".pdf");

    EXPECT_EQ(path.toStr(), "example.doc");

}



TEST(replaceSuffixTest_1984, ReplaceSuffix_EmptyPath_1984) {

    GooString path("");

    replaceSuffix(&path, ".txt", ".pdf");

    EXPECT_EQ(path.toStr(), "");

}



TEST(replaceSuffixTest_1984, ReplaceSuffix_EmptySuffixA_1984) {

    GooString path("example.txt");

    replaceSuffix(&path, "", ".pdf");

    EXPECT_EQ(path.toStr(), "example.txt");

}



TEST(replaceSuffixTest_1984, ReplaceSuffix_EmptySuffixB_1984) {

    GooString path("example.txt");

    replaceSuffix(&path, ".txt", "");

    EXPECT_EQ(path.toStr(), "example");

}



TEST(replaceSuffixTest_1984, ReplaceSuffix_SameSuffixAAndB_1984) {

    GooString path("example.txt");

    replaceSuffix(&path, ".txt", ".txt");

    EXPECT_EQ(path.toStr(), "example.txt");

}



TEST(replaceSuffixTest_1984, ReplaceSuffix_CaseInsensitive_1984) {

    GooString path("example.TXT");

    replaceSuffix(&path, ".txt", ".pdf");

    EXPECT_EQ(path.toStr(), "example.pdf");

}
