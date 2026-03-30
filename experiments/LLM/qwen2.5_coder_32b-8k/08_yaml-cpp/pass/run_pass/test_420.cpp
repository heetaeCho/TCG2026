#include <gtest/gtest.h>

#include "dragonbox.h"



namespace YAML { namespace jkj { namespace dragonbox { namespace detail {



// Mock Policy class for testing

struct MockPolicy {

    using decimal_to_binary_rounding_policy = void;

};



class IsDecimalToBinaryRoundingPolicyTest_420 : public ::testing::Test {};



TEST_F(IsDecimalToBinaryRoundingPolicyTest_420, NormalOperation_420) {

    is_decimal_to_binary_rounding_policy checker;

    EXPECT_TRUE(checker(dummy<MockPolicy>{}));

}



// Since the function template is constexpr and only checks for the presence of a type alias,

// there are no boundary conditions or exceptional/error cases to test directly through this interface.



TEST_F(IsDecimalToBinaryRoundingPolicyTest_420, MissingTypeAlias_420) {

    struct InvalidPolicy {};



    is_decimal_to_binary_rounding_policy checker;

    EXPECT_FALSE(checker(dummy<InvalidPolicy>{}));

}



}}}}


