#include <gtest/gtest.h>

#include "./TestProjects/poppler/fofi/FoFiTrueType.cc"



// Test Fixture for cmpTrueTypeLocaIdxFunctor

class cmpTrueTypeLocaIdxFunctorTest_47 : public ::testing::Test {

protected:

    TrueTypeLoca loca1;

    TrueTypeLoca loca2;

    cmpTrueTypeLocaIdxFunctor comparator;



    void SetUp() override {

        loca1.idx = 0;

        loca1.newOffset = 10;

        loca2.idx = 1;

        loca2.newOffset = 20;

    }

};



// Test normal operation where idx of loca1 is less than idx of loca2

TEST_F(cmpTrueTypeLocaIdxFunctorTest_47, CompareLessThan_47) {

    loca1.idx = 5;

    loca2.idx = 10;

    EXPECT_TRUE(comparator(loca1, loca2));

}



// Test normal operation where idx of loca1 is equal to idx of loca2

TEST_F(cmpTrueTypeLocaIdxFunctorTest_47, CompareEqual_47) {

    loca1.idx = 5;

    loca2.idx = 5;

    EXPECT_FALSE(comparator(loca1, loca2));

}



// Test normal operation where idx of loca1 is greater than idx of loca2

TEST_F(cmpTrueTypeLocaIdxFunctorTest_47, CompareGreaterThan_47) {

    loca1.idx = 15;

    loca2.idx = 10;

    EXPECT_FALSE(comparator(loca1, loca2));

}



// Test boundary condition where idx of loca1 is zero

TEST_F(cmpTrueTypeLocaIdxFunctorTest_47, CompareZeroIdx_47) {

    loca1.idx = 0;

    loca2.idx = 1;

    EXPECT_TRUE(comparator(loca1, loca2));

}



// Test boundary condition where idx of loca2 is zero

TEST_F(cmpTrueTypeLocaIdxFunctorTest_47, CompareAgainstZeroIdx_47) {

    loca1.idx = 1;

    loca2.idx = 0;

    EXPECT_FALSE(comparator(loca1, loca2));

}



// Test boundary condition with maximum int value for idx of loca1

TEST_F(cmpTrueTypeLocaIdxFunctorTest_47, CompareMaxIdx_47) {

    loca1.idx = std::numeric_limits<int>::max();

    loca2.idx = std::numeric_limits<int>::max() - 1;

    EXPECT_FALSE(comparator(loca1, loca2));

}



// Test boundary condition with maximum int value for idx of loca2

TEST_F(cmpTrueTypeLocaIdxFunctorTest_47, CompareAgainstMaxIdx_47) {

    loca1.idx = std::numeric_limits<int>::max() - 1;

    loca2.idx = std::numeric_limits<int>::max();

    EXPECT_TRUE(comparator(loca1, loca2));

}
