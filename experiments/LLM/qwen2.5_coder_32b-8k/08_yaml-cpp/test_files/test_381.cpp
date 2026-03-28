#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "dragonbox.h"



using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding;



// Mock function to verify its invocation

class MockFunc {

public:

    MOCK_CONST_METHOD1(mock_method, int(detail::left_closed_directed_t));

    MOCK_CONST_METHOD1(mock_method, int(detail::right_closed_directed_t));

};



TEST_F(TowardPlusInfinityTest_381, PositiveSignificandCallsRightClosedDirected_381) {

    MockFunc mock;

    toward_plus_infinity_t policy;



    EXPECT_CALL(mock, mock_method(detail::right_closed_directed_t{})).Times(1);



    policy.delegate(SignedSignificandBits{1}, [&mock](detail::right_closed_directed_t) { return mock.mock_method(detail::right_closed_directed_t{}); });

}



TEST_F(TowardPlusInfinityTest_381, NegativeSignificandCallsLeftClosedDirected_381) {

    MockFunc mock;

    toward_plus_infinity_t policy;



    EXPECT_CALL(mock, mock_method(detail::left_closed_directed_t{})).Times(1);



    policy.delegate(SignedSignificandBits{-1}, [&mock](detail::left_closed_directed_t) { return mock.mock_method(detail::left_closed_directed_t{}); });

}



TEST_F(TowardPlusInfinityTest_381, ZeroSignificandCallsRightClosedDirected_381) {

    MockFunc mock;

    toward_plus_infinity_t policy;



    EXPECT_CALL(mock, mock_method(detail::right_closed_directed_t{})).Times(1);



    policy.delegate(SignedSignificandBits{0}, [&mock](detail::right_closed_directed_t) { return mock.mock_method(detail::right_closed_directed_t{}); });

}



// Assuming SignedSignificandBits is an integral type, testing boundary conditions

TEST_F(TowardPlusInfinityTest_381, BoundaryConditionMaxValue_381) {

    MockFunc mock;

    toward_plus_infinity_t policy;



    EXPECT_CALL(mock, mock_method(detail::right_closed_directed_t{})).Times(1);



    policy.delegate(SignedSignificandBits{std::numeric_limits<SignedSignificandBits>::max()}, [&mock](detail::right_closed_directed_t) { return mock.mock_method(detail::right_closed_directed_t{}); });

}



TEST_F(TowardPlusInfinityTest_381, BoundaryConditionMinValue_381) {

    MockFunc mock;

    toward_plus_infinity_t policy;



    EXPECT_CALL(mock, mock_method(detail::left_closed_directed_t{})).Times(1);



    policy.delegate(SignedSignificandBits{std::numeric_limits<SignedSignificandBits>::min()}, [&mock](detail::left_closed_directed_t) { return mock.mock_method(detail::left_closed_directed_t{}); });

}

```


