#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/re2/re2/prog.h"



using namespace re2;

using ::testing::_;

using ::testing::Return;



class ProgTest_130 : public ::testing::Test {

protected:

    Prog prog;

};



TEST_F(ProgTest_130, CanPrefixAccel_ReturnsFalseWhenPrefixSizeIsZero_130) {

    // Assuming default constructor initializes prefix_size_ to 0

    EXPECT_FALSE(prog.can_prefix_accel());

}



TEST_F(ProgTest_130, CanPrefixAccel_ReturnsTrueWhenPrefixSizeIsNonZero_130) {

    prog.ConfigurePrefixAccel("prefix", false);

    EXPECT_TRUE(prog.can_prefix_accel());

}



// Since the provided interface does not specify any external collaborators or callbacks,

// Google Mock is not used in these tests. If there were, we would mock those components.



TEST_F(ProgTest_130, ConfigurePrefixAccel_SetsPrefixSizeNonZero_130) {

    prog.ConfigurePrefixAccel("prefix", false);

    EXPECT_TRUE(prog.can_prefix_accel());

}



TEST_F(ProgTest_130, PrefixAccel_ShiftDFA_ReturnsNullptrWhenNoPrefixAcceleration_130) {

    const char* data = "test";

    size_t size = 4;

    EXPECT_EQ(nullptr, prog.PrefixAccel_ShiftDFA(data, size));

}



TEST_F(ProgTest_130, PrefixAccel_FrontAndBack_ReturnsNullptrWhenNoPrefixAcceleration_130) {

    const char* data = "test";

    size_t size = 4;

    EXPECT_EQ(nullptr, prog.PrefixAccel_FrontAndBack(data, size));

}



TEST_F(ProgTest_130, SearchNFA_ReturnsFalseForEmptyString_130) {

    absl::string_view text = "";

    absl::string_view context = "";

    Anchor anchor = UNANCHORED;

    MatchKind kind = MATCH_NFA_LONGEST;

    absl::string_view match[1];

    EXPECT_FALSE(prog.SearchNFA(text, context, anchor, kind, match, 1));

}



TEST_F(ProgTest_130, SearchDFA_ReturnsFalseForEmptyString_130) {

    absl::string_view text = "";

    absl::string_view context = "";

    Anchor anchor = UNANCHORED;

    MatchKind kind = MATCH_DFA_LONGEST;

    absl::string_view match[1];

    bool failed = false;

    SparseSet matches;

    EXPECT_FALSE(prog.SearchDFA(text, context, anchor, kind, match, &failed, &matches));

}



TEST_F(ProgTest_130, PossibleMatchRange_ReturnsFalseForMaxlenZero_130) {

    std::string min;

    std::string max;

    int maxlen = 0;

    EXPECT_FALSE(prog.PossibleMatchRange(&min, &max, maxlen));

}
