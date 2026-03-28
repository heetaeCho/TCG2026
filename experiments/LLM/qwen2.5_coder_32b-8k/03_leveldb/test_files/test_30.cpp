#include <gtest/gtest.h>

#include "leveldb/iterator.h"



namespace leveldb {



class IteratorTest_30 : public ::testing::Test {

protected:

    CleanupNode cleanup_node;



    static void MockCleanupFunction(void* arg1, void* arg2) {

        // Mock function implementation for testing

    }

};



TEST_F(IteratorTest_30, IsEmpty_ReturnsTrueWhenNoFunctionSet_30) {

    EXPECT_TRUE(cleanup_node.IsEmpty());

}



TEST_F(IteratorTest_30, IsEmpty_ReturnsFalseWhenFunctionSet_30) {

    cleanup_node.function = &MockCleanupFunction;

    EXPECT_FALSE(cleanup_node.IsEmpty());

}



TEST_F(IteratorTest_30, Run_CallsFunctionWithArguments_30) {

    bool function_called = false;



    void MockCleanupFunction(void* arg1, void* arg2) {

        function_called = true;

        EXPECT_EQ(arg1, reinterpret_cast<void*>(42));

        EXPECT_EQ(arg2, reinterpret_cast<void*>(84));

    }



    cleanup_node.function = &MockCleanupFunction;

    cleanup_node.arg1 = reinterpret_cast<void*>(42);

    cleanup_node.arg2 = reinterpret_cast<void*>(84);



    cleanup_node.Run();

    EXPECT_TRUE(function_called);

}



TEST_F(IteratorTest_30, Run_DoesNotCrashWhenNoFunctionSet_30) {

    // This test ensures that calling Run() when no function is set does not cause a crash

    EXPECT_NO_THROW(cleanup_node.Run());

}



}  // namespace leveldb
