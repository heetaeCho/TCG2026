#include <gtest/gtest.h>

#include "./TestProjects/re2/util/pcre.h"



using namespace re2;



class PCRE_OptionsTest_180 : public ::testing::Test {

protected:

    PCRE_Options options;

};



TEST_F(PCRE_OptionsTest_180, DefaultConstructorInitializesValues_180) {

    EXPECT_EQ(options.stack_limit(), 0);

}



TEST_F(PCRE_OptionsTest_180, SetStackLimitChangesValue_180) {

    int new_stack_limit = 4096;

    options.set_stack_limit(new_stack_limit);

    EXPECT_EQ(options.stack_limit(), new_stack_limit);

}



TEST_F(PCRE_OptionsTest_180, StackLimitBoundaryConditionZero_180) {

    options.set_stack_limit(0);

    EXPECT_EQ(options.stack_limit(), 0);

}



TEST_F(PCRE_OptionsTest_180, StackLimitBoundaryConditionPositive_180) {

    int max_int = std::numeric_limits<int>::max();

    options.set_stack_limit(max_int);

    EXPECT_EQ(options.stack_limit(), max_int);

}
