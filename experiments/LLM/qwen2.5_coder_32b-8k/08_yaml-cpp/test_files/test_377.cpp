#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "dragonbox.h"



namespace YAML { namespace jkj { namespace dragonbox { namespace policy { namespace decimal_to_binary_rounding {



// Mock function to verify interactions

template <typename T, typename... Args>

struct MockFunc {

    MOCK_CONST_METHOD1(call, T(Args...));

};



class SignedSignificandBitsMock {

public:

    MOCK_CONST_METHOD0(has_even_significand_bits, bool());

};



TEST_F(DragonboxTest_377, DelegateCallsFuncWithEvenSignificandBits_377) {

    SignedSignificandBitsMock s;

    MockFunc<int, detail::nearest_always_closed_t> f;



    EXPECT_CALL(s, has_even_significand_bits()).WillOnce(testing::Return(true));

    EXPECT_CALL(f, call(detail::nearest_always_closed_t{})).Times(1);



    nearest_to_even_static_boundary_t::delegate(s, f);

}



TEST_F(DragonboxTest_377, DelegateCallsFuncWithOddSignificandBits_377) {

    SignedSignificandBitsMock s;

    MockFunc<int, detail::nearest_always_open_t> f;



    EXPECT_CALL(s, has_even_significand_bits()).WillOnce(testing::Return(false));

    EXPECT_CALL(f, call(detail::nearest_always_open_t{})).Times(1);



    nearest_to_even_static_boundary_t::delegate(s, f);

}



} } } } }
