#include <gtest/gtest.h>

#include "catch2/internal/catch_source_line_info.hpp"

#include <sstream>



class SourceLineInfoTest_489 : public ::testing::Test {

protected:

    Catch::SourceLineInfo info1;

    Catch::SourceLineInfo info2;

    Catch::SourceLineInfo info3;



    SourceLineInfoTest_489()

        : info1("file1.cpp", 10),

          info2("file2.cpp", 20),

          info3("file1.cpp", 10) {}

};



TEST_F(SourceLineInfoTest_489, OperatorEquality_SameFileAndLine_489) {

    EXPECT_TRUE(info1 == info3);

}



TEST_F(SourceLineInfoTest_489, OperatorEquality_DifferentFile_489) {

    EXPECT_FALSE(info1 == info2);

}



TEST_F(SourceLineInfoTest_489, OperatorEquality_DifferentLine_489) {

    Catch::SourceLineInfo differentLine("file1.cpp", 15);

    EXPECT_FALSE(info1 == differentLine);

}



TEST_F(SourceLineInfoTest_489, OperatorLess_SameFileDifferentLine_489) {

    Catch::SourceLineInfo differentLine("file1.cpp", 15);

    EXPECT_TRUE(info1 < differentLine);

}



TEST_F(SourceLineInfoTest_489, OperatorLess_DifferentFileAndLine_489) {

    EXPECT_TRUE(info1 < info2);

}



TEST_F(SourceLineInfoTest_489, OperatorLess_SameLineDifferentFile_489) {

    Catch::SourceLineInfo differentFile("afile.cpp", 10);

    EXPECT_TRUE(differentFile < info1);

}



TEST_F(SourceLineInfoTest_489, OutputStreamOperator_GNUStyle_489) {

    std::ostringstream oss;

    oss << info1;

    EXPECT_EQ(oss.str(), "file1.cpp:10");

}



TEST_F(SourceLineInfoTest_489, OutputStreamOperator_NonGNUStyle_489) {

#ifdef __GNUG__

#undef __GNUG__

#endif

    std::ostringstream oss;

    oss << info1;

    EXPECT_EQ(oss.str(), "file1.cpp(10)");

#ifdef __GNUC__

#define __GNUG__ 1

#endif

}
