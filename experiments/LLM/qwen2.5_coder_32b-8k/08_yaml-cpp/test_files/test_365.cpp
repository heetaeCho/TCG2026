#include <gtest/gtest.h>

#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"



namespace YAML { namespace jkj { namespace dragonbox { namespace policy { namespace decimal_to_binary_rounding {



using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding;



class nearest_toward_minus_infinity_t_Test_365 : public ::testing::Test {

protected:

    using Policy = nearest_toward_minus_infinity_t;

};



TEST_F(nearest_toward_minus_infinity_t_Test_365, NormalInterval_PositiveSignificandBits_365) {

    struct MockSignedSignificandBits {

        bool is_negative() const noexcept { return false; }

    };



    auto result = Policy::normal_interval(MockSignedSignificandBits{});

    EXPECT_EQ(result.is_negative, false);

}



TEST_F(nearest_toward_minus_infinity_t_Test_365, NormalInterval_NegativeSignificandBits_365) {

    struct MockSignedSignificandBits {

        bool is_negative() const noexcept { return true; }

    };



    auto result = Policy::normal_interval(MockSignedSignificandBits{});

    EXPECT_EQ(result.is_negative, true);

}



TEST_F(nearest_toward_minus_infinity_t_Test_365, ShorterInterval_PositiveSignificandBits_365) {

    struct MockSignedSignificandBits {

        bool is_negative() const noexcept { return false; }

    };



    auto result = Policy::shorter_interval(MockSignedSignificandBits{});

    EXPECT_EQ(result.is_negative, false);

}



TEST_F(nearest_toward_minus_infinity_t_Test_365, ShorterInterval_NegativeSignificandBits_365) {

    struct MockSignedSignificandBits {

        bool is_negative() const noexcept { return true; }

    };



    auto result = Policy::shorter_interval(MockSignedSignificandBits{});

    EXPECT_EQ(result.is_negative, true);

}



}}}}}  // namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding
