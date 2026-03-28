#include <gtest/gtest.h>

#include "catch2/internal/catch_source_line_info.hpp"



using namespace Catch;



class SourceLineInfoTest_487 : public ::testing::Test {

protected:

    SourceLineInfo info1;

    SourceLineInfo info2;

    SourceLineInfo info3;



    SourceLineInfoTest_487()

        : info1("file1.cpp", 10),

          info2("file2.cpp", 20),

          info3("file1.cpp", 10) {}

};



TEST_F(SourceLineInfoTest_487, EqualityOperatorSameFileAndLine_487) {

    EXPECT_TRUE(info1 == info3);

}



TEST_F(SourceLineInfoTest_487, EqualityOperatorDifferentFile_487) {

    EXPECT_FALSE(info1 == info2);

}



TEST_F(SourceLineInfoTest_487, EqualityOperatorDifferentLine_487) {

    SourceLineInfo differentLine("file1.cpp", 15);

    EXPECT_FALSE(info1 == differentLine);

}



TEST_F(SourceLineInfoTest_487, LessThanOperatorSameFileDifferentLine_487) {

    SourceLineInfo smallerLine("file1.cpp", 5);

    EXPECT_TRUE(smallerLine < info1);

}



TEST_F(SourceLineInfoTest_487, LessThanOperatorDifferentFile_487) {

    // Assuming alphabetical order for file names

    EXPECT_FALSE(info2 < info1);

}



TEST_F(SourceLineInfoTest_487, LessThanOperatorSameLineDifferentFile_487) {

    SourceLineInfo anotherFile("file0.cpp", 10);

    EXPECT_TRUE(anotherFile < info1);

}
