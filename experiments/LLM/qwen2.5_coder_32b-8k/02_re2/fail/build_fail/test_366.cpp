#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/regexp.h"



using namespace re2;

using ::testing::NotNull;



class RegexpTest_366 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed, but this class is mostly a black box

    }



    void TearDown() override {

        // Teardown code if needed, but this class is mostly a black box

    }

};



TEST_F(RegexpTest_366, CaptureNames_ReturnsNonNullMap_366) {

    Regexp* regexp = Regexp::Parse("(.*)", 0, nullptr);

    std::map<int, std::string>* capture_names = regexp->CaptureNames();

    EXPECT_THAT(capture_names, NotNull());

    delete capture_names;

    regexp->Decref();

}



TEST_F(RegexpTest_366, CaptureNames_HandlesNoCaptures_366) {

    Regexp* regexp = Regexp::Parse("a", 0, nullptr);

    std::map<int, std::string>* capture_names = regexp->CaptureNames();

    EXPECT_TRUE(capture_names->empty());

    delete capture_names;

    regexp->Decref();

}



TEST_F(RegexpTest_366, CaptureNames_HandlesSingleCapture_366) {

    Regexp* regexp = Regexp::Parse("(a)", 0, nullptr);

    std::map<int, std::string>* capture_names = regexp->CaptureNames();

    EXPECT_EQ(capture_names->size(), 1);

    EXPECT_EQ(capture_names->at(1), "");

    delete capture_names;

    regexp->Decref();

}



TEST_F(RegexpTest_366, CaptureNames_HandlesMultipleCaptures_366) {

    Regexp* regexp = Regexp::Parse("(a)(b)(c)", 0, nullptr);

    std::map<int, std::string>* capture_names = regexp->CaptureNames();

    EXPECT_EQ(capture_names->size(), 3);

    EXPECT_EQ(capture_names->at(1), "");

    EXPECT_EQ(capture_names->at(2), "");

    EXPECT_EQ(capture_names->at(3), "");

    delete capture_names;

    regexp->Decref();

}



TEST_F(RegexpTest_366, CaptureNames_HandlesNamedCaptures_366) {

    Regexp* regexp = Regexp::Parse("(?<name1>a)(?<name2>b)", 0, nullptr);

    std::map<int, std::string>* capture_names = regexp->CaptureNames();

    EXPECT_EQ(capture_names->size(), 2);

    EXPECT_EQ(capture_names->at(1), "name1");

    EXPECT_EQ(capture_names->at(2), "name2");

    delete capture_names;

    regexp->Decref();

}



TEST_F(RegexpTest_366, CaptureNames_HandlesNestedCaptures_366) {

    Regexp* regexp = Regexp::Parse("(a(b)c)", 0, nullptr);

    std::map<int, std::string>* capture_names = regexp->CaptureNames();

    EXPECT_EQ(capture_names->size(), 2);

    EXPECT_EQ(capture_names->at(1), "");

    EXPECT_EQ(capture_names->at(2), "");

    delete capture_names;

    regexp->Decref();

}



TEST_F(RegexpTest_366, CaptureNames_HandlesAlternations_366) {

    Regexp* regexp = Regexp::Parse("(a|b)|(c|d)", 0, nullptr);

    std::map<int, std::string>* capture_names = regexp->CaptureNames();

    EXPECT_EQ(capture_names->size(), 4);

    delete capture_names;

    regexp->Decref();

}



TEST_F(RegexpTest_366, CaptureNames_HandlesConcatenations_366) {

    Regexp* regexp = Regexp::Parse("abc", 0, nullptr);

    std::map<int, std::string>* capture_names = regexp->CaptureNames();

    EXPECT_TRUE(capture_names->empty());

    delete capture_names;

    regexp->Decref();

}



TEST_F(RegexpTest_366, CaptureNames_HandlesQuantifiers_366) {

    Regexp* regexp = Regexp::Parse("(a*)*(b+)(c?)", 0, nullptr);

    std::map<int, std::string>* capture_names = regexp->CaptureNames();

    EXPECT_EQ(capture_names->size(), 4);

    delete capture_names;

    regexp->Decref();

}



TEST_F(RegexpTest_366, CaptureNames_HandlesComplexPattern_366) {

    Regexp* regexp = Regexp::Parse("((a(b)c)|(d(e)f))", 0, nullptr);

    std::map<int, std::string>* capture_names = regexp->CaptureNames();

    EXPECT_EQ(capture_names->size(), 5);

    delete capture_names;

    regexp->Decref();

}



TEST_F(RegexpTest_366, CaptureNames_HandlesEmptyPattern_366) {

    Regexp* regexp = Regexp::Parse("", 0, nullptr);

    std::map<int, std::string>* capture_names = regexp->CaptureNames();

    EXPECT_TRUE(capture_names->empty());

    delete capture_names;

    regexp->Decref();

}



TEST_F(RegexpTest_366, CaptureNames_HandlesInvalidPattern_366) {

    Regexp* regexp = Regexp::Parse("(*", 0, nullptr);

    std::map<int, std::string>* capture_names = regexp->CaptureNames();

    EXPECT_TRUE(capture_names->empty());

    delete capture_names;

    if (regexp) {

        regexp->Decref();

    }

}
