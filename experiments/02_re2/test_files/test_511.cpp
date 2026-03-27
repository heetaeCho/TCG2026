#include <gtest/gtest.h>

#include "regexp.h"

#include "parse.cc"



using namespace re2;



class ParseStateTest_511 : public ::testing::Test {

protected:

    ParseStateTest_511() 

        : status_(new RegexpStatus()),

          parse_state_(ParseFlags::kNone, absl::string_view(""), status_) {}



    ~ParseStateTest_511() {

        delete status_;

    }



    void SetUp() override {

        // Initialize any necessary state before tests

    }



    void TearDown() override {

        // Clean up after tests

    }



    RegexpStatus* status_;

    ParseState parse_state_;

};



TEST_F(ParseStateTest_511, DoAlternation_NormalOperation_511) {

    // Arrange

    Regexp* r1 = Regexp::LiteralString(nullptr, 0, ParseFlags::kNone);

    parse_state_.stacktop_ = r1;



    // Act

    parse_state_.DoAlternation();



    // Assert

    EXPECT_EQ(parse_state_.stacktop_->op(), kRegexpAlternate);

    r1->Decref();

}



TEST_F(ParseStateTest_511, DoAlternation_BoundaryConditions_511) {

    // Arrange: Empty stacktop

    parse_state_.stacktop_ = nullptr;



    // Act & Assert

    EXPECT_DEATH(parse_state_.DoAlternation(), "stacktop_ should not be null");

}



TEST_F(ParseStateTest_511, DoAlternation_ExceptionalCases_511) {

    // Arrange: Simulate an exceptional case (e.g., memory allocation failure)

    Regexp* r1 = Regexp::LiteralString(nullptr, 0, ParseFlags::kNone);

    parse_state_.stacktop_ = r1;



    // Act & Assert

    EXPECT_NO_THROW(parse_state_.DoAlternation());

    r1->Decref();

}



TEST_F(ParseStateTest_511, DoAlternation_VerifyExternalInteractions_511) {

    // Arrange

    Regexp* r1 = Regexp::LiteralString(nullptr, 0, ParseFlags::kNone);

    parse_state_.stacktop_ = r1;



    // Act

    parse_state_.DoAlternation();



    // Assert

    EXPECT_EQ(r1->ref(), 0);  // Ensure Decref was called on r1

}
