#include <gtest/gtest.h>

#include "re2/parse.cc"

#include "re2/regexp.h"



using namespace re2;



class ParseStateTest_491 : public ::testing::Test {

protected:

    ParseState* parse_state;



    void SetUp() override {

        RegexpStatus status;

        parse_state = new ParseState(ParseFlags(), absl::string_view(""), &status);

    }



    void TearDown() override {

        delete parse_state;

    }

};



TEST_F(ParseStateTest_491, PushWordBoundary_WordTrue_ReturnsTrue_491) {

    EXPECT_TRUE(parse_state->PushWordBoundary(true));

}



TEST_F(ParseStateTest_491, PushWordBoundary_WordFalse_ReturnsTrue_491) {

    EXPECT_TRUE(parse_state->PushWordBoundary(false));

}



// Boundary conditions

TEST_F(ParseStateTest_491, PushWordBoundary_BoundaryTrue_ReturnsTrue_491) {

    EXPECT_TRUE(parse_state->PushWordBoundary(true));

}



TEST_F(ParseStateTest_491, PushWordBoundary_BoundaryFalse_ReturnsTrue_491) {

    EXPECT_TRUE(parse_state->PushWordBoundary(false));

}



// Exceptional or error cases

// There are no observable exceptional or error cases based on the provided interface.



// Verification of external interactions

// No external collaborators are involved in this function, so no Google Mock is needed.
