#include <gtest/gtest.h>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"



namespace YAML { namespace jkj { namespace dragonbox { namespace policy { namespace decimal_to_binary_rounding {



using TowardZero = toward_zero;



class DragonboxPolicyTest : public ::testing::Test {

protected:

    // No setup or teardown needed as the class is stateless

};



TEST_F(DragonboxPolicyTest_383, DelegateFunctionCalledWithCorrectArguments_383) {

    struct MockFunc {

        MOCK_CONSTEXPR_FUNCTION(int operator()(detail::left_closed_directed_t, int arg1, double arg2) const);

    };

    

    constexpr MockFunc mockFunc;

    EXPECT_CALL(mockFunc, operator()(detail::left_closed_directed_t{}, 42, 3.14)).WillOnce(testing::Return(7));



    auto result = TowardZero::delegate(0, mockFunc, 42, 3.14);

    static_assert(std::is_same<decltype(result), int>::value, "Unexpected return type");

    EXPECT_EQ(result, 7);

}



TEST_F(DragonboxPolicyTest_383, DelegateHandlesMultipleArgumentTypes_383) {

    struct MockFunc {

        MOCK_CONSTEXPR_FUNCTION(double operator()(detail::left_closed_directed_t, char arg1, int arg2, float arg3) const);

    };

    

    constexpr MockFunc mockFunc;

    EXPECT_CALL(mockFunc, operator()(detail::left_closed_directed_t{}, 'a', 42, 3.14f)).WillOnce(testing::Return(7.0));



    auto result = TowardZero::delegate(0, mockFunc, 'a', 42, 3.14f);

    static_assert(std::is_same<decltype(result), double>::value, "Unexpected return type");

    EXPECT_EQ(result, 7.0);

}



TEST_F(DragonboxPolicyTest_383, DelegateWithNoAdditionalArguments_383) {

    struct MockFunc {

        MOCK_CONSTEXPR_FUNCTION(int operator()(detail::left_closed_directed_t) const);

    };

    

    constexpr MockFunc mockFunc;

    EXPECT_CALL(mockFunc, operator()(detail::left_closed_directed_t{})).WillOnce(testing::Return(7));



    auto result = TowardZero::delegate(0, mockFunc);

    static_assert(std::is_same<decltype(result), int>::value, "Unexpected return type");

    EXPECT_EQ(result, 7);

}



TEST_F(DragonboxPolicyTest_383, DelegateWithMultipleArgumentsOfSameType_383) {

    struct MockFunc {

        MOCK_CONSTEXPR_FUNCTION(int operator()(detail::left_closed_directed_t, int arg1, int arg2) const);

    };

    

    constexpr MockFunc mockFunc;

    EXPECT_CALL(mockFunc, operator()(detail::left_closed_directed_t{}, 42, 84)).WillOnce(testing::Return(7));



    auto result = TowardZero::delegate(0, mockFunc, 42, 84);

    static_assert(std::is_same<decltype(result), int>::value, "Unexpected return type");

    EXPECT_EQ(result, 7);

}



TEST_F(DragonboxPolicyTest_383, DelegateHandlesVoidReturn_383) {

    struct MockFunc {

        MOCK_CONSTEXPR_FUNCTION(void operator()(detail::left_closed_directed_t, int arg1, double arg2) const);

    };

    

    constexpr MockFunc mockFunc;

    EXPECT_CALL(mockFunc, operator()(detail::left_closed_directed_t{}, 42, 3.14));



    TowardZero::delegate(0, mockFunc, 42, 3.14);

}



} } } } }
