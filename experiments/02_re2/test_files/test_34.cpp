#include <gtest/gtest.h>

#include "re2/re2.h"



using namespace re2;



class RE2OptionsTest_34 : public ::testing::Test {

protected:

    RE2::Options options_;

};



TEST_F(RE2OptionsTest_34, DefaultConstructorInitializesWordBoundaryFalse_34) {

    EXPECT_FALSE(options_.word_boundary());

}



TEST_F(RE2OptionsTest_34, SetWordBoundaryChangesValueToTrue_34) {

    options_.set_word_boundary(true);

    EXPECT_TRUE(options_.word_boundary());

}



TEST_F(RE2OptionsTest_34, SetWordBoundaryChangesValueToFalse_34) {

    options_.set_word_boundary(false);

    EXPECT_FALSE(options_.word_boundary());

}



TEST_F(RE2OptionsTest_34, CopySetsSameWordBoundaryValue_34) {

    RE2::Options other;

    other.set_word_boundary(true);

    options_.Copy(other);

    EXPECT_TRUE(options_.word_boundary());

}



TEST_F(RE2OptionsTest_34, ParseFlagsDoesNotAffectWordBoundary_34) {

    bool initial_value = options_.word_boundary();

    options_.ParseFlags();

    EXPECT_EQ(initial_value, options_.word_boundary());

}
