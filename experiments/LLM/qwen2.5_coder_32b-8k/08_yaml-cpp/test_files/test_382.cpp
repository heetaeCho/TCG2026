#include <gmock/gmock.h>

#include <gtest/gtest.h>



namespace YAML { namespace jkj { namespace dragonbox { namespace policy { namespace decimal_to_binary_rounding {



struct MockFunc {

    MOCK_CONST_METHOD1(operator(), int(detail::left_closed_directed_t));

    MOCK_CONST_METHOD1(operator(), int(detail::right_closed_directed_t));

};



template <class SignedSignificandBits>

struct MockSignedSignificandBits {

    bool is_negative() const { return negative; }

    void set_negative(bool n) { negative = n; }



private:

    bool negative = false;

};



TEST_F(DragonboxPolicyTest_382, PositiveSignificandCallsLeftClosedDirected_382) {

    MockSignedSignificandBits<int> significand;

    significand.set_negative(false);



    MockFunc mock_func;

    EXPECT_CALL(mock_func, operator()(detail::left_closed_directed_t{})).WillOnce(::testing::Return(42));



    auto result = toward_minus_infinity_t::delegate(significand, mock_func);

    EXPECT_EQ(result, 42);

}



TEST_F(DragonboxPolicyTest_382, NegativeSignificandCallsRightClosedDirected_382) {

    MockSignedSignificandBits<int> significand;

    significand.set_negative(true);



    MockFunc mock_func;

    EXPECT_CALL(mock_func, operator()(detail::right_closed_directed_t{})).WillOnce(::testing::Return(42));



    auto result = toward_minus_infinity_t::delegate(significand, mock_func);

    EXPECT_EQ(result, 42);

}



TEST_F(DragonboxPolicyTest_382, PositiveBoundaryCondition_382) {

    MockSignedSignificandBits<int> significand;

    significand.set_negative(false);



    MockFunc mock_func;

    EXPECT_CALL(mock_func, operator()(detail::left_closed_directed_t{})).WillOnce(::testing::Return(0));



    auto result = toward_minus_infinity_t::delegate(significand, mock_func);

    EXPECT_EQ(result, 0);

}



TEST_F(DragonboxPolicyTest_382, NegativeBoundaryCondition_382) {

    MockSignedSignificandBits<int> significand;

    significand.set_negative(true);



    MockFunc mock_func;

    EXPECT_CALL(mock_func, operator()(detail::right_closed_directed_t{})).WillOnce(::testing::Return(0));



    auto result = toward_minus_infinity_t::delegate(significand, mock_func);

    EXPECT_EQ(result, 0);

}



} } } } }
