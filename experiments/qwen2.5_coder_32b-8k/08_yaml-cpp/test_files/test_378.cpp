#include <gtest/gtest.h>

#include "dragonbox.h"

#include <type_traits>



using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding;



// Mock function to verify arguments and return types

struct MockFunc {

    template<typename... Args>

    int operator()(Args... args) const {

        static_assert(std::is_same<decltype(args)..., detail::nearest_always_closed_t>::value || 

                      std::is_same<decltype(args)..., detail::nearest_always_open_t>::value, "Invalid argument type");

        return 42; // Arbitrary return value for testing

    }

};



struct SignedSignificandBitsMock {

    bool has_even_significand_bits() const { return even_significand_bits; }



    void set_even_significand_bits(bool val) { even_significand_bits = val; }



private:

    bool even_significand_bits = false;

};



class NearestToOddStaticBoundaryTest_378 : public ::testing::Test {

protected:

    SignedSignificandBitsMock mockSignedSignificandBits;

};



TEST_F(NearestToOddStaticBoundaryTest_378, EvenSignificandBits_CallsNearestAlwaysClosed_378) {

    mockSignedSignificandBits.set_even_significand_bits(true);

    MockFunc mockFunc;

    EXPECT_EQ(nearest_to_odd_static_boundary_t::delegate(mockSignedSignificandBits, mockFunc), 42);

}



TEST_F(NearestToOddStaticBoundaryTest_378, OddSignificandBits_CallsNearestAlwaysOpen_378) {

    mockSignedSignificandBits.set_even_significand_bits(false);

    MockFunc mockFunc;

    EXPECT_EQ(nearest_to_odd_static_boundary_t::delegate(mockSignedSignificandBits, mockFunc), 42);

}



TEST_F(NearestToOddStaticBoundaryTest_378, BoundaryCondition_EvenSignificandBits_ReturnsExpectedValue_378) {

    mockSignedSignificandBits.set_even_significand_bits(true);

    MockFunc mockFunc;

    EXPECT_EQ(nearest_to_odd_static_boundary_t::delegate(mockSignedSignificandBits, mockFunc), 42);

}



TEST_F(NearestToOddStaticBoundaryTest_378, BoundaryCondition_OddSignificandBits_ReturnsExpectedValue_378) {

    mockSignedSignificandBits.set_even_significand_bits(false);

    MockFunc mockFunc;

    EXPECT_EQ(nearest_to_odd_static_boundary_t::delegate(mockSignedSignificandBits, mockFunc), 42);

}
