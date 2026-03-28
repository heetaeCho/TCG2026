#include <gtest/gtest.h>

#include "TestProjects/re2/re2/sparse_set.h"



using namespace re2;



class SparseSetTest_89 : public ::testing::Test {

protected:

    SparseSet set;

};



TEST_F(SparseSetTest_89, DefaultConstructorInitializesEmptySet_89) {

    EXPECT_TRUE(set.empty());

}



TEST_F(SparseSetTest_89, ConstructorWithMaxSizeInitializesCorrectly_89) {

    SparseSet specificSet(10);

    EXPECT_EQ(specificSet.max_size(), 10);

    EXPECT_TRUE(specificSet.empty());

}



TEST_F(SparseSetTest_89, ResizeChangesMaxSize_89) {

    set.resize(20);

    EXPECT_EQ(set.max_size(), 20);

}



TEST_F(SparseSetTest_89, InsertIncreasesSizeAndContainsReturnsTrue_89) {

    set.insert(5);

    EXPECT_FALSE(set.empty());

    EXPECT_TRUE(set.contains(5));

}



TEST_F(SparseSetTest_89, InsertNewWithExistingElementDoesNotIncreaseSize_89) {

    set.insert_new(10);

    int initialSize = set.size();

    set.insert_new(10);

    EXPECT_EQ(set.size(), initialSize);

}



TEST_F(SparseSetTest_89, ClearEmptiesTheSet_89) {

    set.insert(5);

    set.clear();

    EXPECT_TRUE(set.empty());

}



TEST_F(SparseSetTest_89, BeginAndEndIterateOverInsertedElements_89) {

    set.insert(1);

    set.insert(2);

    int count = 0;

    for (SparseSet::iterator it = set.begin(); it != set.end(); ++it) {

        ++count;

    }

    EXPECT_EQ(count, set.size());

}



TEST_F(SparseSetTest_89, ContainsReturnsFalseForNonInsertedElement_89) {

    EXPECT_FALSE(set.contains(15));

}



TEST_F(SparseSetTest_89, InsertNewIncreasesSizeAndContainsReturnsTrue_89) {

    set.insert_new(7);

    EXPECT_FALSE(set.empty());

    EXPECT_TRUE(set.contains(7));

}



TEST_F(SparseSetTest_89, ResizeSmallerThanCurrentSizeDoesNotLoseElements_89) {

    for (int i = 0; i < 5; ++i) {

        set.insert(i);

    }

    int initialSize = set.size();

    set.resize(3);

    EXPECT_EQ(set.size(), initialSize); // resizing smaller should not affect existing elements

}



TEST_F(SparseSetTest_89, ResizeToZeroEmptiesTheSet_89) {

    for (int i = 0; i < 5; ++i) {

        set.insert(i);

    }

    set.resize(0);

    EXPECT_TRUE(set.empty());

}
