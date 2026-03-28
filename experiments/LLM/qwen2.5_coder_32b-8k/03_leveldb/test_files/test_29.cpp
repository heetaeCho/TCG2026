#include <gtest/gtest.h>

#include "leveldb/iterator.h"



using namespace leveldb;



class IteratorTest_29 : public ::testing::Test {

protected:

    CleanupNode cleanup_node;

};



TEST_F(IteratorTest_29, IsEmpty_ReturnsTrueWhenFunctionIsNullptr_29) {

    // Arrange

    cleanup_node.function = nullptr;



    // Act & Assert

    EXPECT_TRUE(cleanup_node.IsEmpty());

}



TEST_F(IteratorTest_29, IsEmpty_ReturnsFalseWhenFunctionIsNotNullptr_29) {

    // Arrange

    void dummy_function(void*, void*) {}

    cleanup_node.function = dummy_function;



    // Act & Assert

    EXPECT_FALSE(cleanup_node.IsEmpty());

}
