#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming the repeater class template is available in some header file.

namespace Catch { namespace Benchmark { namespace Detail {

template <typename Fun> struct repeater {

public:

    void operator()(int k) const;

};

}}}



using namespace Catch::Benchmark::Detail;



class MockFunction {

public:

    MOCK_METHOD0(fun, void());

};



TEST_F(MockFunctionTest_896, NormalOperation_CallsFun_K_Times_896) {

    MockFunction mockFun;

    repeater<MockFunction> rep(mockFun);



    EXPECT_CALL(mockFun, fun()).Times(5);

    rep(5);

}



TEST_F(MockFunctionTest_896, BoundaryCondition_ZeroK_NoCalls_896) {

    MockFunction mockFun;

    repeater<MockFunction> rep(mockFun);



    EXPECT_CALL(mockFun, fun()).Times(0);

    rep(0);

}



TEST_F(MockFunctionTest_896, BoundaryCondition_OneK_OneCall_896) {

    MockFunction mockFun;

    repeater<MockFunction> rep(mockFun);



    EXPECT_CALL(mockFun, fun()).Times(1);

    rep(1);

}



TEST_F(MockFunctionTest_896, ExceptionalCase_NegativeK_NoCalls_896) {

    MockFunction mockFun;

    repeater<MockFunction> rep(mockFun);



    EXPECT_CALL(mockFun, fun()).Times(0);

    rep(-1); // Assuming no exception is thrown and it behaves like 0

}
