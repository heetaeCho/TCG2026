#include <gtest/gtest.h>

#include "re2/re2.h"



using namespace re2;



class LazyRE2Test_47 : public ::testing::Test {

protected:

    LazyRE2 lazy_re2;

};



TEST_F(LazyRE2Test_47, OperatorArrowReturnsNonNullPointer_47) {

    EXPECT_NE(lazy_re2.operator->(), nullptr);

}



TEST_F(LazyRE2Test_47, OperatorStarDereferencesPointerCorrectly_47) {

    RE2* ptr = lazy_re2.get();

    EXPECT_EQ(&lazy_re2.operator*(), ptr);

}



// Assuming get() should also return a non-null pointer after the first call

TEST_F(LazyRE2Test_47, GetReturnsNonNullPointerOnFirstCall_47) {

    EXPECT_NE(lazy_re2.get(), nullptr);

}



// Assuming subsequent calls to get() return the same pointer

TEST_F(LazyRE2Test_47, SubsequentGetCallsReturnSamePointer_47) {

    RE2* first_call = lazy_re2.get();

    RE2* second_call = lazy_re2.get();

    EXPECT_EQ(first_call, second_call);

}
