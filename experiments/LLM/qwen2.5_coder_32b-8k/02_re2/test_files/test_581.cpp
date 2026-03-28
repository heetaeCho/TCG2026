#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/prog.h"



using namespace re2;

using ::testing::_;

using ::testing::Return;



class ProgTest_581 : public ::testing::Test {

protected:

    Prog prog;

};



TEST_F(ProgTest_581, SearchBitState_NormalOperation_KFirstMatch_581) {

    absl::string_view text = "hello";

    absl::string_view context = "";

    Anchor anchor = kUnanchored;

    MatchKind kind = kFirstMatch;

    absl::string_view match[1];

    int nmatch = 1;



    EXPECT_TRUE(prog.SearchBitState(text, context, anchor, kind, match, nmatch));

}



TEST_F(ProgTest_581, SearchBitState_NormalOperation_KLongestMatch_581) {

    absl::string_view text = "hello";

    absl::string_view context = "";

    Anchor anchor = kUnanchored;

    MatchKind kind = kLongestMatch;

    absl::string_view match[1];

    int nmatch = 1;



    EXPECT_TRUE(prog.SearchBitState(text, context, anchor, kind, match, nmatch));

}



TEST_F(ProgTest_581, SearchBitState_NormalOperation_KFullMatch_581) {

    absl::string_view text = "hello";

    absl::string_view context = "";

    Anchor anchor = kUnanchored;

    MatchKind kind = kFullMatch;

    absl::string_view match[1];

    int nmatch = 1;



    EXPECT_FALSE(prog.SearchBitState(text, context, anchor, kind, match, nmatch));

}



TEST_F(ProgTest_581, SearchBitState_BoundaryConditions_EmptyText_581) {

    absl::string_view text = "";

    absl::string_view context = "";

    Anchor anchor = kUnanchored;

    MatchKind kind = kFirstMatch;

    absl::string_view match[1];

    int nmatch = 1;



    EXPECT_TRUE(prog.SearchBitState(text, context, anchor, kind, match, nmatch));

}



TEST_F(ProgTest_581, SearchBitState_BoundaryConditions_ZeroNMatch_581) {

    absl::string_view text = "hello";

    absl::string_view context = "";

    Anchor anchor = kUnanchored;

    MatchKind kind = kFirstMatch;

    absl::string_view match[1];

    int nmatch = 0;



    EXPECT_TRUE(prog.SearchBitState(text, context, anchor, kind, match, nmatch));

}



TEST_F(ProgTest_581, SearchBitState_ErrorCase_InvalidText_581) {

    absl::string_view text = "\xFF";

    absl::string_view context = "";

    Anchor anchor = kUnanchored;

    MatchKind kind = kFirstMatch;

    absl::string_view match[1];

    int nmatch = 1;



    EXPECT_FALSE(prog.SearchBitState(text, context, anchor, kind, match, nmatch));

}



TEST_F(ProgTest_581, SearchBitState_ErrorCase_UnanchoredFullMatch_581) {

    absl::string_view text = "hello";

    absl::string_view context = "";

    Anchor anchor = kUnanchored;

    MatchKind kind = kFullMatch;

    absl::string_view match[1];

    int nmatch = 1;



    EXPECT_FALSE(prog.SearchBitState(text, context, anchor, kind, match, nmatch));

}



TEST_F(ProgTest_581, SearchBitState_ErrorCase_AnchoredMismatch_581) {

    absl::string_view text = "hello";

    absl::string_view context = "";

    Anchor anchor = kAnchored;

    MatchKind kind = kFullMatch;

    absl::string_view match[1];

    int nmatch = 1;



    EXPECT_FALSE(prog.SearchBitState(text, context, anchor, kind, match, nmatch));

}
