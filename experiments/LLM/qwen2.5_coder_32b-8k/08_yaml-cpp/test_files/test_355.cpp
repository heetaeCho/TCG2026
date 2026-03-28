#include <gtest/gtest.h>

#include <gmock/gmock.h>



namespace YAML { namespace jkj { namespace dragonbox { namespace policy { namespace decimal_to_binary_rounding {



// Mock function to use with delegate method

template <typename... Args>

struct MockFunc {

    MOCK_CONST_METHOD1(operator(), decltype(std::declval<Args>()())(Args...));

};



TEST_F(DragonboxNearestToEvenTest_355, DelegateCallsFunctionWithCorrectArguments_355) {

    MockFunc<int> mockFunc;

    EXPECT_CALL(mockFunc, operator()(testing::_)).Times(1);



    nearest_to_even_t::delegate(0, mockFunc{}, 42);

}



TEST_F(DragonboxNearestToEvenTest_355, DelegateReturnsFunctionResult_355) {

    MockFunc<int> mockFunc;

    EXPECT_CALL(mockFunc, operator()(testing::_)).WillOnce(testing::Return(100));



    auto result = nearest_to_even_t::delegate(0, mockFunc{}, 42);

    EXPECT_EQ(result, 100);

}



TEST_F(DragonboxNearestToEvenTest_355, DelegateHandlesZeroSignificandBits_355) {

    MockFunc<int> mockFunc;

    EXPECT_CALL(mockFunc, operator()(testing::_)).WillOnce(testing::Return(200));



    auto result = nearest_to_even_t::delegate(0, mockFunc{}, 42);

    EXPECT_EQ(result, 200);

}



TEST_F(DragonboxNearestToEvenTest_355, DelegateHandlesNegativeSignificandBits_355) {

    MockFunc<int> mockFunc;

    EXPECT_CALL(mockFunc, operator()(testing::_)).WillOnce(testing::Return(300));



    auto result = nearest_to_even_t::delegate(-1, mockFunc{}, 42);

    EXPECT_EQ(result, 300);

}



TEST_F(DragonboxNearestToEvenTest_355, DelegateHandlesPositiveSignificandBits_355) {

    MockFunc<int> mockFunc;

    EXPECT_CALL(mockFunc, operator()(testing::_)).WillOnce(testing::Return(400));



    auto result = nearest_to_even_t::delegate(1, mockFunc{}, 42);

    EXPECT_EQ(result, 400);

}



} } } } }
