#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "dragonbox.h"



namespace YAML { namespace jkj { namespace dragonbox { namespace policy { namespace decimal_to_binary_rounding {



class MockFunc {

public:

    MOCK_METHOD2(call, int(nearest_toward_zero_t, int));

};



TEST_F(MockFuncTest_367, Delegate_CallsFuncWithNearestTowardZeroAndArgs_367) {

    MockFunc mockFunc;

    EXPECT_CALL(mockFunc, call(testing::_, 42)).WillOnce(testing::Return(0));



    auto result = nearest_toward_zero_t::delegate<int>(10, &MockFunc::call, &mockFunc, 42);

    EXPECT_EQ(result, 0);

}



TEST_F(MockFuncTest_367, Delegate_ReturnsFuncResult_367) {

    MockFunc mockFunc;

    EXPECT_CALL(mockFunc, call(testing::_, 42)).WillOnce(testing::Return(123));



    auto result = nearest_toward_zero_t::delegate<int>(10, &MockFunc::call, &mockFunc, 42);

    EXPECT_EQ(result, 123);

}



TEST_F(MockFuncTest_367, Delegate_HandlesZeroArgs_367) {

    MockFunc mockFunc;

    EXPECT_CALL(mockFunc, call(testing::_, testing::_)).WillOnce(testing::Return(0));



    auto result = nearest_toward_zero_t::delegate<int>(10, &MockFunc::call, &mockFunc);

    EXPECT_EQ(result, 0);

}



} } } } }
