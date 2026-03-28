#include <gtest/gtest.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_string_manip.cpp"

#include "./TestProjects/Catch2/src/catch2/internal/catch_stringref.hpp"



class StringRefManipulationTest_593 : public ::testing::Test {

protected:

    using namespace Catch;

};



TEST_F(StringRefManipulationTest_593, TrimEmptyString_593) {

    StringRef ref("");

    EXPECT_EQ(trim(ref), "");

}



TEST_F(StringRefManipulationTest_593, TrimNoWhitespace_593) {

    StringRef ref("HelloWorld");

    EXPECT_EQ(trim(ref), "HelloWorld");

}



TEST_F(StringRefManipulationTest_593, TrimLeadingSpaces_593) {

    StringRef ref("   HelloWorld");

    EXPECT_EQ(trim(ref), "HelloWorld");

}



TEST_F(StringRefManipulationTest_593, TrimTrailingSpaces_593) {

    StringRef ref("HelloWorld   ");

    EXPECT_EQ(trim(ref), "HelloWorld");

}



TEST_F(StringRefManipulationTest_593, TrimBothEnds_593) {

    StringRef ref("   HelloWorld   ");

    EXPECT_EQ(trim(ref), "HelloWorld");

}



TEST_F(StringRefManipulationTest_593, TrimMixedWhitespace_593) {

    StringRef ref("\t\n  HelloWorld \r\t");

    EXPECT_EQ(trim(ref), "HelloWorld");

}



TEST_F(StringRefManipulationTest_593, TrimAllSpaces_593) {

    StringRef ref("   ");

    EXPECT_EQ(trim(ref), "");

}



TEST_F(StringRefManipulationTest_593, TrimSingleCharNoWhitespace_593) {

    StringRef ref("A");

    EXPECT_EQ(trim(ref), "A");

}



TEST_F(StringRefManipulationTest_593, TrimSingleCharWithWhitespace_593) {

    StringRef ref(" A ");

    EXPECT_EQ(trim(ref), "A");

}
