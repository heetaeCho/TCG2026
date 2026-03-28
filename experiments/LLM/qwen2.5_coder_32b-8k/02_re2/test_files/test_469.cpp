#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "prefilter.h"

#include "prefilter_tree.h"



using namespace re2;

using ::testing::Eq;



class PrefilterTreeTest_469 : public ::testing::Test {

protected:

    Prefilter* prefilter1;

    Prefilter* prefilter2;



    void SetUp() override {

        prefilter1 = new Prefilter(Prefilter::Op::ATOM);

        prefilter2 = new Prefilter(Prefilter::Op::ATOM);

    }



    void TearDown() override {

        delete prefilter1;

        delete prefilter2;

    }

};



TEST_F(PrefilterTreeTest_469, PrefilterEqualSameObject_469) {

    PrefilterTree::PrefilterEqual comparator;

    EXPECT_TRUE(comparator(prefilter1, prefilter1));

}



TEST_F(PrefilterTreeTest_469, PrefilterEqualDifferentObjectsSameContent_469) {

    prefilter1->set_unique_id(1);

    prefilter2->set_unique_id(1);



    PrefilterTree::PrefilterEqual comparator;

    EXPECT_TRUE(comparator(prefilter1, prefilter2));

}



TEST_F(PrefilterTreeTest_469, PrefilterEqualDifferentObjectsDifferentContent_469) {

    prefilter1->set_unique_id(1);

    prefilter2->set_unique_id(2);



    PrefilterTree::PrefilterEqual comparator;

    EXPECT_FALSE(comparator(prefilter1, prefilter2));

}



TEST_F(PrefilterTreeTest_469, PrefilterEqualNullPointers_469) {

    Prefilter* nullPtr = nullptr;

    PrefilterTree::PrefilterEqual comparator;



    // This will cause a failure as the operator() checks for non-null pointers

    EXPECT_DEATH(comparator(nullPtr, nullPtr), "Check failed: a != NULL");

}



TEST_F(PrefilterTreeTest_469, PrefilterEqualOneNullPointer_469) {

    Prefilter* nullPtr = nullptr;

    PrefilterTree::PrefilterEqual comparator;



    // This will cause a failure as the operator() checks for non-null pointers

    EXPECT_DEATH(comparator(prefilter1, nullPtr), "Check failed: b != NULL");

}



TEST_F(PrefilterTreeTest_469, PrefilterEqualDifferentOps_469) {

    prefilter1->set_unique_id(1);

    prefilter2->set_unique_id(1);

    prefilter2->op() = Prefilter::Op::AND;



    PrefilterTree::PrefilterEqual comparator;

    EXPECT_FALSE(comparator(prefilter1, prefilter2));

}



TEST_F(PrefilterTreeTest_469, PrefilterEqualDifferentAtoms_469) {

    prefilter1->set_unique_id(1);

    prefilter2->set_unique_id(1);

    prefilter1->atom() = "test1";

    prefilter2->atom() = "test2";



    PrefilterTree::PrefilterEqual comparator;

    EXPECT_FALSE(comparator(prefilter1, prefilter2));

}



TEST_F(PrefilterTreeTest_469, PrefilterEqualSameAtoms_469) {

    prefilter1->set_unique_id(1);

    prefilter2->set_unique_id(1);

    prefilter1->atom() = "test";

    prefilter2->atom() = "test";



    PrefilterTree::PrefilterEqual comparator;

    EXPECT_TRUE(comparator(prefilter1, prefilter2));

}
