#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"



using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding;



// Mock function to verify the behavior of delegate

template <class SignedSignificandBits, class... Args>

struct MockFunc {

    MOCK_CONSTEXPR_FUNCTION(decltype(auto) operator()(nearest_toward_plus_infinity_t, Args... args) const);

};



TEST_F(DragonboxDelegateTest_361, NormalOperation_361) {

    MockFunc<int> mock_func;

    EXPECT_CALL(mock_func, operator()(testing::_, testing::_))

        .WillOnce(testing::Return(42));



    auto result = nearest_toward_plus_infinity_t::delegate(0, mock_func(), 5);

    ASSERT_EQ(result, 42);

}



TEST_F(DragonboxDelegateTest_361, BoundaryConditions_ZeroSignificandBits_361) {

    MockFunc<int> mock_func;

    EXPECT_CALL(mock_func, operator()(testing::_, testing::_))

        .WillOnce(testing::Return(0));



    auto result = nearest_toward_plus_infinity_t::delegate(0, mock_func(), 5);

    ASSERT_EQ(result, 0);

}



TEST_F(DragonboxDelegateTest_361, BoundaryConditions_NegativeSignificandBits_361) {

    MockFunc<int> mock_func;

    EXPECT_CALL(mock_func, operator()(testing::_, testing::_))

        .WillOnce(testing::Return(-1));



    auto result = nearest_toward_plus_infinity_t::delegate(-5, mock_func(), 5);

    ASSERT_EQ(result, -1);

}



TEST_F(DragonboxDelegateTest_361, VerificationOfExternalInteractions_361) {

    MockFunc<int> mock_func;

    EXPECT_CALL(mock_func, operator()(nearest_toward_plus_infinity_t{}, 5))

        .WillOnce(testing::Return(42));



    auto result = nearest_toward_plus_infinity_t::delegate(0, mock_func(), 5);

    ASSERT_EQ(result, 42);

}
