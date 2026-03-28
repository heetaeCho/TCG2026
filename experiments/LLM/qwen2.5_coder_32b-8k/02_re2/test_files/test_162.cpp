#include <gtest/gtest.h>

#include "re2/regexp.h"



using namespace re2;



class RegexpTest_162 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(RegexpTest_162, HaveMatch_Creates_RegexpWithCorrectOp_162) {

    ParseFlags flags = 0;

    Regexp* regexp = Regexp::HaveMatch(1, flags);

    EXPECT_EQ(regexp->op(), kRegexpHaveMatch);

    regexp->Decref();

}



TEST_F(RegexpTest_162, HaveMatch_Creates_RegexpWithCorrectMatchId_162) {

    ParseFlags flags = 0;

    int match_id = 5;

    Regexp* regexp = Regexp::HaveMatch(match_id, flags);

    EXPECT_EQ(regexp->match_id(), match_id);

    regexp->Decref();

}



TEST_F(RegexpTest_162, HaveMatch_Returns_Incref_Regexp_162) {

    ParseFlags flags = 0;

    int initial_ref_count = 1;

    Regexp* regexp = Regexp::HaveMatch(1, flags);

    EXPECT_EQ(regexp->Ref(), initial_ref_count + 1); // incremented by HaveMatch and once more here

    regexp->Decref(); // Decrement to original ref count

    regexp->Decref(); // Proper cleanup

}



TEST_F(RegexpTest_162, HaveMatch_Throws_NoExceptionForValidInput_162) {

    ParseFlags flags = 0;

    EXPECT_NO_THROW({

        Regexp* regexp = Regexp::HaveMatch(1, flags);

        regexp->Decref();

    });

}



TEST_F(RegexpTest_162, match_id_Returns_CorrectId_WhenCalledOnValidObject_162) {

    ParseFlags flags = 0;

    int expected_match_id = 42;

    Regexp* regexp = Regexp::HaveMatch(expected_match_id, flags);

    EXPECT_EQ(regexp->match_id(), expected_match_id);

    regexp->Decref();

}



TEST_F(RegexpTest_162, op_Returns_CorrectOp_WhenCalledOnValidObject_162) {

    ParseFlags flags = 0;

    Regexp* regexp = Regexp::HaveMatch(1, flags);

    EXPECT_EQ(regexp->op(), kRegexpHaveMatch);

    regexp->Decref();

}



TEST_F(RegexpTest_162, Ref_Returns_PositiveRefCount_WhenCalledOnValidObject_162) {

    ParseFlags flags = 0;

    Regexp* regexp = Regexp::HaveMatch(1, flags);

    EXPECT_GT(regexp->Ref(), 0);

    regexp->Decref();

}
