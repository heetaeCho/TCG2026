#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"



namespace YAML { namespace jkj { namespace dragonbox { namespace policy { namespace decimal_to_binary_rounding {



class MockFunc {

public:

    MOCK_METHOD1(call, int(detail::right_closed_directed_t));

};



TEST_F(DragonboxPolicyTest_384, DelegateCallsFunctionWithRightClosedDirectedT_384) {

    MockFunc mock_func;

    EXPECT_CALL(mock_func, call(testing::_)).WillOnce(testing::Return(42));



    auto result = away_from_zero::delegate(0, [&mock_func](detail::right_closed_directed_t t) {

        return mock_func.call(t);

    });



    EXPECT_EQ(result, 42);

}



TEST_F(DragonboxPolicyTest_384, DelegateHandlesZeroSignificandBits_384) {

    MockFunc mock_func;

    EXPECT_CALL(mock_func, call(testing::_)).WillOnce(testing::Return(0));



    auto result = away_from_zero::delegate(0, [&mock_func](detail::right_closed_directed_t t) {

        return mock_func.call(t);

    });



    EXPECT_EQ(result, 0);

}



TEST_F(DragonboxPolicyTest_384, DelegateHandlesNonZeroSignificandBits_384) {

    MockFunc mock_func;

    EXPECT_CALL(mock_func, call(testing::_)).WillOnce(testing::Return(100));



    auto result = away_from_zero::delegate(10, [&mock_func](detail::right_closed_directed_t t) {

        return mock_func.call(t);

    });



    EXPECT_EQ(result, 100);

}



} } } } }
