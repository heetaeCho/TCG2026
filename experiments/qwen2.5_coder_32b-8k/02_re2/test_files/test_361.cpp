#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/regexp.h"



namespace re2 {

namespace {



using ::testing::Return;



class RegexpTest_361 : public ::testing::Test {

protected:

    Regexp* regexp_;

    std::map<std::string, int>* namedCaptures_;



    void SetUp() override {

        // Create a simple regex to test with

        regexp_ = Regexp::Parse("abc(def)ghi", Regexp::NoParseFlags(), nullptr);

    }



    void TearDown() override {

        if (namedCaptures_) {

            delete namedCaptures_;

        }

        regexp_->Decref();

    }

};



TEST_F(RegexpTest_361, NamedCaptures_ReturnsValidMap_361) {

    namedCaptures_ = regexp_->NamedCaptures();

    EXPECT_EQ(namedCaptures_->size(), 1);

    EXPECT_EQ((*namedCaptures_)["def"], 1);

}



TEST_F(RegexpTest_361, NamedCaptures_NoCaptures_ReturnsEmptyMap_361) {

    Regexp* noCaptureRegexp = Regexp::Parse("abcdefg", Regexp::NoParseFlags(), nullptr);

    namedCaptures_ = noCaptureRegexp->NamedCaptures();

    EXPECT_EQ(namedCaptures_->size(), 0);

    noCaptureRegexp->Decref();

}



TEST_F(RegexpTest_361, NamedCaptures_MultipleCaptures_ReturnsCorrectMap_361) {

    Regexp* multipleCaptureRegexp = Regexp::Parse("(abc)(def)(ghi)", Regexp::NoParseFlags(), nullptr);

    namedCaptures_ = multipleCaptureRegexp->NamedCaptures();

    EXPECT_EQ(namedCaptures_->size(), 0); // No named captures, just numbered

    multipleCaptureRegexp->Decref();

}



TEST_F(RegexpTest_361, NamedCaptures_EmptyString_ReturnsEmptyMap_361) {

    Regexp* emptyRegexp = Regexp::Parse("", Regexp::NoParseFlags(), nullptr);

    namedCaptures_ = emptyRegexp->NamedCaptures();

    EXPECT_EQ(namedCaptures_->size(), 0);

    emptyRegexp->Decref();

}



TEST_F(RegexpTest_361, NamedCaptures_ComplexRegex_ReturnsCorrectMap_361) {

    Regexp* complexRegexp = Regexp::Parse("(abc)(?<def>ghi)(jkl)(?<mno>pqr)", Regexp::NoParseFlags(), nullptr);

    namedCaptures_ = complexRegexp->NamedCaptures();

    EXPECT_EQ(namedCaptures_->size(), 2);

    EXPECT_EQ((*namedCaptures_)["def"], 1); // Named capture "def"

    EXPECT_EQ((*namedCaptures_)["mno"], 3); // Named capture "mno"

    complexRegexp->Decref();

}



TEST_F(RegexpTest_361, NamedCaptures_InvalidRegex_ReturnsNullptr_361) {

    Regexp* invalidRegexp = Regexp::Parse("(abc(def)ghi", Regexp::NoParseFlags(), nullptr);

    namedCaptures_ = invalidRegexp->NamedCaptures();

    EXPECT_EQ(namedCaptures_, nullptr); // Invalid regex

    if (invalidRegexp) {

        invalidRegexp->Decref();

    }

}



}  // namespace

}  // namespace re2
