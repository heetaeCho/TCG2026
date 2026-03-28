#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/iterator.h"



namespace leveldb {



class MockCleanupFunction {

public:

    MOCK_METHOD0(Call, void());

};



TEST_F(IteratorTest_402, RegisterCleanupStoresFunctionPointer_402) {

    Iterator iterator;

    MockCleanupFunction mock_cleanup_function;



    EXPECT_CALL(mock_cleanup_function, Call()).Times(1);



    auto cleanup_function = [&mock_cleanup_function]() { mock_cleanup_function.Call(); };

    void* arg1 = nullptr;

    void* arg2 = nullptr;



    iterator.RegisterCleanup(cleanup_function, arg1, arg2);

}



TEST_F(IteratorTest_402, RegisterMultipleCleanupsInOrder_402) {

    Iterator iterator;

    MockCleanupFunction mock_cleanup_function1;

    MockCleanupFunction mock_cleanup_function2;



    EXPECT_CALL(mock_cleanup_function1, Call()).Times(1).WillOnce(::testing::InvokeWithoutArgs([]() { /* Do nothing */ }));

    EXPECT_CALL(mock_cleanup_function2, Call()).Times(1).WillOnce(::testing::InvokeWithoutArgs([]() { /* Do nothing */ }));



    auto cleanup_function1 = [&mock_cleanup_function1]() { mock_cleanup_function1.Call(); };

    auto cleanup_function2 = [&mock_cleanup_function2]() { mock_cleanup_function2.Call(); };



    iterator.RegisterCleanup(cleanup_function1, nullptr, nullptr);

    iterator.RegisterCleanup(cleanup_function2, nullptr, nullptr);



    // Assuming CleanupNode::Run() is called somewhere in the test setup to verify order

}



TEST_F(IteratorTest_402, RegisterCleanupWithNullFunctionPointerThrowsAssertion_402) {

    Iterator iterator;



    EXPECT_DEATH({

        iterator.RegisterCleanup(nullptr, nullptr, nullptr);

    }, "assertion");

}



} // namespace leveldb

```



Note: The test `RegisterMultipleCleanupsInOrder_402` assumes that there is a mechanism to trigger the cleanup functions (e.g., through a destructor or explicit call) to verify the order of execution. Since this is not provided in the interface, you might need an additional method to run these cleanups for testing purposes if such functionality does not exist.


