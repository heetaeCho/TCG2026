#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming the necessary headers for YAML and dragonbox are included



namespace YAML { namespace jkj { namespace dragonbox { namespace policy { namespace decimal_to_binary_rounding {



class NearestTowardMinusInfinityTest : public ::testing::Test {

protected:

    using Policy = nearest_toward_minus_infinity_t;



    template <typename Func, typename... Args>

    auto delegate(Func f, Args... args) -> decltype(f(Policy{}, args...)) {

        return Policy::delegate(0, f, args...);

    }

};



TEST_F(NearestTowardMinusInfinityTest_364, DelegateCallsFunctionWithPolicy_364) {

    struct MockFunc {

        MOCK_METHOD1(operator(), void(Policy));

    };



    MockFunc mockFunc;

    EXPECT_CALL(mockFunc, operator()(Policy{}));



    delegate(mockFunc);

}



TEST_F(NearestTowardMinusInfinityTest_364, DelegatePassesAdditionalArguments_364) {

    struct MockFunc {

        MOCK_METHOD2(operator(), void(Policy, int));

    };



    MockFunc mockFunc;

    EXPECT_CALL(mockFunc, operator()(Policy{}, 42));



    delegate(mockFunc, 42);

}



TEST_F(NearestTowardMinusInfinityTest_364, DelegateHandlesMultipleArguments_364) {

    struct MockFunc {

        MOCK_METHOD3(operator(), void(Policy, int, double));

    };



    MockFunc mockFunc;

    EXPECT_CALL(mockFunc, operator()(Policy{}, 42, 3.14));



    delegate(mockFunc, 42, 3.14);

}



TEST_F(NearestTowardMinusInfinityTest_364, DelegateReturnsFunctionResult_364) {

    struct MockFunc {

        MOCK_METHOD1(operator(), int(Policy));

    };



    MockFunc mockFunc;

    EXPECT_CALL(mockFunc, operator()(Policy{})).WillOnce(::testing::Return(42));



    auto result = delegate(mockFunc);

    EXPECT_EQ(result, 42);

}



} } } } }
