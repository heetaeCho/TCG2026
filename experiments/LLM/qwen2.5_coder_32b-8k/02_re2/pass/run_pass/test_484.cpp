#include <gtest/gtest.h>

#include "re2/unicode_casefold.h"

#include "re2/parse.cc"



namespace re2 {



class LookupCaseFoldTest_484 : public ::testing::Test {

protected:

    CaseFold caseFolds[5] = {

        {1}, {2}, {3}, {4}, {5}

    };

};



TEST_F(LookupCaseFoldTest_484, NormalOperationWithinBounds_484) {

    const CaseFold* result = LookupCaseFold(caseFolds, 5, 3);

    EXPECT_EQ(result, &caseFolds[2]);

}



TEST_F(LookupCaseFoldTest_484, NormalOperationLowerBound_484) {

    const CaseFold* result = LookupCaseFold(caseFolds, 5, 1);

    EXPECT_EQ(result, &caseFolds[0]);

}



TEST_F(LookupCaseFoldTest_484, NormalOperationUpperBound_484) {

    const CaseFold* result = LookupCaseFold(caseFolds, 5, 5);

    EXPECT_EQ(result, &caseFolds[4]);

}



TEST_F(LookupCaseFoldTest_484, BoundaryConditionBelowRange_484) {

    const CaseFold* result = LookupCaseFold(caseFolds, 5, 0);

    EXPECT_EQ(result, &caseFolds[0]);

}



TEST_F(LookupCaseFoldTest_484, BoundaryConditionAboveRange_484) {

    const CaseFold* result = LookupCaseFold(caseFolds, 5, 6);

    EXPECT_EQ(result, nullptr);

}



TEST_F(LookupCaseFoldTest_484, EmptyArray_484) {

    const CaseFold* result = LookupCaseFold(caseFolds, 0, 3);

    EXPECT_EQ(result, nullptr);

}



} // namespace re2
