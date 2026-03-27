#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"



using namespace Catch::Benchmark::Detail;



// Mock function to verify invocation and parameters

template <typename Result>

class MockFunction {

public:

    MOCK_METHOD(Result, Call, (), (const));

};



TEST(CompleteInvokerTest_898, InvokeWithVoidReturn_898) {

    MockFunction<void> mockFun;

    EXPECT_CALL(mockFun, Call()).Times(1);



    CompleteInvoker<void>::invoke([&mockFun]() { mockFun.Call(); });

}



TEST(CompleteInvokerTest_898, InvokeWithNonVoidReturn_898) {

    MockFunction<int> mockFun;

    EXPECT_CALL(mockFun, Call()).WillOnce(testing::Return(42));



    int result = CompleteInvoker<int>::invoke([&mockFun]() { return mockFun.Call(); });

    EXPECT_EQ(result, 42);

}



TEST(CompleteInvokerTest_898, InvokeWithMultipleArgs_898) {

    MockFunction<int> mockFun;

    EXPECT_CALL(mockFun, Call()).WillOnce(testing::Return(42));



    int result = CompleteInvoker<int>::invoke([&mockFun](int a, double b, std::string c) { return mockFun.Call(); }, 1, 3.14, "test");

    EXPECT_EQ(result, 42);

}



TEST(CompleteInvokerTest_898, InvokeWithNoArgsAndNonVoidReturn_898) {

    MockFunction<int> mockFun;

    EXPECT_CALL(mockFun, Call()).WillOnce(testing::Return(42));



    int result = CompleteInvoker<int>::invoke([&mockFun]() { return mockFun.Call(); });

    EXPECT_EQ(result, 42);

}
