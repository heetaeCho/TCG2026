#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/re2.h"



using namespace re2;



class LazyRE2Test : public ::testing::Test {

protected:

    LazyRE2 lazy_re2;

};



TEST_F(LazyRE2Test, DereferenceOperatorReturnsReferenceToRE2_46) {

    RE2& re2_ref = *lazy_re2;

    EXPECT_TRUE(&re2_ref != nullptr);

}



TEST_F(LazyRE2Test, ArrowOperatorReturnsPointerToRE2_46) {

    RE2* re2_ptr = lazy_re2.operator->();

    EXPECT_TRUE(re2_ptr != nullptr);

}



TEST_F(LazyRE2Test, GetMethodReturnsPointerToRE2_46) {

    RE2* re2_ptr = lazy_re2.get();

    EXPECT_TRUE(re2_ptr != nullptr);

}



// Boundary Conditions

TEST_F(LazyRE2Test, MultipleDereferencesReturnSameReference_46) {

    RE2& ref1 = *lazy_re2;

    RE2& ref2 = *lazy_re2;

    EXPECT_EQ(&ref1, &ref2);

}



TEST_F(LazyRE2Test, MultipleArrowOperatorsReturnSamePointer_46) {

    RE2* ptr1 = lazy_re2.operator->();

    RE2* ptr2 = lazy_re2.operator->();

    EXPECT_EQ(ptr1, ptr2);

}



TEST_F(LazyRE2Test, MultipleGetCallsReturnSamePointer_46) {

    RE2* ptr1 = lazy_re2.get();

    RE2* ptr2 = lazy_re2.get();

    EXPECT_EQ(ptr1, ptr2);

}
