#include <gtest/gtest.h>

#include "dragonbox.h"



// Mocking Policy and detector_default_pair_list for testing purposes

struct MockPolicy {};

template<class T> struct dummy {};

template<class... Ts> struct detector_default_pair_list {};



namespace YAML { namespace jkj { namespace dragonbox { namespace detail {



class CheckPolicyValidityTest_411 : public ::testing::Test {

protected:

    using Policy = MockPolicy;

};



TEST_F(CheckPolicyValidityTest_411, ReturnsFalseForEmptyPairList_411) {

    constexpr bool result = check_policy_validity(dummy<Policy>{}, detector_default_pair_list<>());

    EXPECT_FALSE(result);

}



} } } }
