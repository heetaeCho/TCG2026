#include <gtest/gtest.h>

#include "sparse_set.h"

#include "onepass.cc"



using namespace re2;



class AddQTest_568 : public ::testing::Test {

protected:

    void SetUp() override {

        q = new Instq();

    }



    void TearDown() override {

        delete q;

    }



    SparseSet* q;

};



TEST_F(AddQTest_568, IdZeroAlwaysReturnsTrue_568) {

    EXPECT_TRUE(AddQ(q, 0));

}



TEST_F(AddQTest_568, InsertNewElementReturnsTrue_568) {

    EXPECT_TRUE(AddQ(q, 1));

}



TEST_F(AddQTest_568, InsertExistingElementReturnsFalse_568) {

    AddQ(q, 2);

    EXPECT_FALSE(AddQ(q, 2));

}



TEST_F(AddQTest_568, MultipleDistinctElementsInsertSuccessfully_568) {

    EXPECT_TRUE(AddQ(q, 1));

    EXPECT_TRUE(AddQ(q, 2));

    EXPECT_TRUE(AddQ(q, 3));

}



TEST_F(AddQTest_568, BoundaryConditionMaxSize_568) {

    q->resize(10);

    for (int i = 1; i <= 10; ++i) {

        EXPECT_TRUE(AddQ(q, i));

    }

    EXPECT_FALSE(AddQ(q, 11)); // Assuming max_size is strictly enforced

}



TEST_F(AddQTest_568, BoundaryConditionZeroMaxSize_568) {

    q->resize(0);

    EXPECT_FALSE(AddQ(q, 1));

}
