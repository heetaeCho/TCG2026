#include <gtest/gtest.h>

#include "TestProjects/re2/re2/sparse_set.h"



namespace re2 {

    class SparseSetTTest : public ::testing::Test {

    protected:

        SparseSet set;



        SparseSetTTest() : set(10) {}



        void SetUp() override {

            set.clear();

        }

    };



    TEST_F(SparseSetTTest_93, InsertNew_AddsElement_93) {

        int value = 5;

        auto it = set.insert_new(value);

        EXPECT_EQ(*it, value);

        EXPECT_TRUE(set.contains(value));

    }



    TEST_F(SparseSetTTest_93, InsertNew_ReturnsIteratorToEnd_93) {

        int value = 7;

        auto it = set.insert_new(value);

        EXPECT_EQ(it, set.end() - 1);

    }



    TEST_F(SparseSetTTest_93, InsertNew_IncreasesSize_93) {

        int initial_size = set.size();

        set.insert_new(3);

        EXPECT_EQ(set.size(), initial_size + 1);

    }



    TEST_F(SparseSetTTest_93, InsertNew_DoesNotInsertDuplicate_93) {

        int value = 5;

        set.insert_new(value);

        auto it = set.insert_new(value);

        EXPECT_EQ(it, set.end());

        EXPECT_EQ(set.size(), 1);

    }



    TEST_F(SparseSetTTest_93, InsertNew_BoundaryCondition_MaxSize_93) {

        SparseSet max_size_set(2);

        max_size_set.insert_new(0);

        max_size_set.insert_new(1);

        auto it = max_size_set.insert_new(2);

        EXPECT_EQ(it, max_size_set.end());

    }



    TEST_F(SparseSetTTest_93, InsertNew_ExceptionalCase_EmptySet_93) {

        SparseSet empty_set(0);

        auto it = empty_set.insert_new(5);

        EXPECT_EQ(it, empty_set.end());

    }

}
