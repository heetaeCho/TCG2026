#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"



using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding;



// Mock function to test delegate method

template<typename T, typename... Args>

struct MockFunc {

    MOCK_CONST_METHOD1(operator(), T(nearest_to_odd_t, Args...));

};



class NearestToOddTest_358 : public ::testing::Test {};



TEST_F(NearestToOddTest_358, DelegateCallsFunctionWithCorrectArguments_358) {

    MockFunc<int, int> mock_func;

    EXPECT_CALL(mock_func, operator()(nearest_to_odd_t{}, 42))

        .WillOnce(::testing::Return(10));



    auto result = nearest_to_odd_t::delegate(0, mock_func, 42);

    EXPECT_EQ(result, 10);

}



TEST_F(NearestToOddTest_358, DelegateHandlesZeroSignificandBits_358) {

    MockFunc<int, int> mock_func;

    EXPECT_CALL(mock_func, operator()(nearest_to_odd_t{}, 0))

        .WillOnce(::testing::Return(20));



    auto result = nearest_to_odd_t::delegate(0, mock_func, 0);

    EXPECT_EQ(result, 20);

}



TEST_F(NearestToOddTest_358, DelegateHandlesNegativeSignificandBits_358) {

    MockFunc<int, int> mock_func;

    EXPECT_CALL(mock_func, operator()(nearest_to_odd_t{}, -1))

        .WillOnce(::testing::Return(30));



    auto result = nearest_to_odd_t::delegate(-1, mock_func, -1);

    EXPECT_EQ(result, 30);

}



TEST_F(NearestToOddTest_358, DelegateHandlesMultipleArguments_358) {

    MockFunc<int, int, int> mock_func;

    EXPECT_CALL(mock_func, operator()(nearest_to_odd_t{}, 42, 84))

        .WillOnce(::testing::Return(40));



    auto result = nearest_to_odd_t::delegate(0, mock_func, 42, 84);

    EXPECT_EQ(result, 40);

}
