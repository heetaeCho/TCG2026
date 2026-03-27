#include <gtest/gtest.h>

#include "re2/prog.h"

#include "absl/strings/string_view.h"



using namespace re2;



class ProgTest_567 : public ::testing::Test {

protected:

    Prog* prog;



    void SetUp() override {

        // Assuming a default constructor exists and initializes the object properly

        prog = new Prog();

    }



    void TearDown() override {

        delete prog;

    }

};



TEST_F(ProgTest_567, SearchOnePass_AnchoredFullMatch_Success_567) {

    absl::string_view text("abc");

    absl::string_view context("abc");

    Anchor anchor = kAnchored;

    MatchKind kind = kFullMatch;

    absl::string_view match[1];

    int nmatch = 1;



    bool result = prog->SearchOnePass(text, context, anchor, kind, match, nmatch);



    EXPECT_TRUE(result);

    EXPECT_EQ(match[0], "abc");

}



TEST_F(ProgTest_567, SearchOnePass_AnchoredFullMatch_Failure_567) {

    absl::string_view text("abc");

    absl::string_view context("abcd");

    Anchor anchor = kAnchored;

    MatchKind kind = kFullMatch;

    absl::string_view match[1];

    int nmatch = 1;



    bool result = prog->SearchOnePass(text, context, anchor, kind, match, nmatch);



    EXPECT_FALSE(result);

}



TEST_F(ProgTest_567, SearchOnePass_UnanchoredMatch_Disallowed_567) {

    absl::string_view text("abc");

    absl::string_view context("abc");

    Anchor anchor = kUnanchored;

    MatchKind kind = kFirstMatch;

    absl::string_view match[1];

    int nmatch = 1;



    bool result = prog->SearchOnePass(text, context, anchor, kind, match, nmatch);



    EXPECT_FALSE(result);

}



TEST_F(ProgTest_567, SearchOnePass_NonFullMatch_Disallowed_567) {

    absl::string_view text("abc");

    absl::string_view context("abc");

    Anchor anchor = kAnchored;

    MatchKind kind = kFirstMatch;

    absl::string_view match[1];

    int nmatch = 1;



    bool result = prog->SearchOnePass(text, context, anchor, kind, match, nmatch);



    EXPECT_FALSE(result);

}



TEST_F(ProgTest_567, SearchOnePass_NegativeNMatch_567) {

    absl::string_view text("abc");

    absl::string_view context("abc");

    Anchor anchor = kAnchored;

    MatchKind kind = kFullMatch;

    absl::string_view match[1];

    int nmatch = -1;



    bool result = prog->SearchOnePass(text, context, anchor, kind, match, nmatch);



    EXPECT_FALSE(result);

}



TEST_F(ProgTest_567, SearchOnePass_ZeroNMatch_Success_567) {

    absl::string_view text("abc");

    absl::string_view context("abc");

    Anchor anchor = kAnchored;

    MatchKind kind = kFullMatch;

    absl::string_view match[1];

    int nmatch = 0;



    bool result = prog->SearchOnePass(text, context, anchor, kind, match, nmatch);



    EXPECT_TRUE(result);

}
