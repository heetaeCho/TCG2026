#include <gtest/gtest.h>

#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"



using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding;



// Mock class to simulate SignedSignificandBits for testing purposes

class MockSignedSignificandBits {

public:

    bool is_negative() const noexcept { return negative; }

    void set_negative(bool value) noexcept { negative = value; }



private:

    bool negative = false;

};



TEST_F(DragonboxTest_363, ShorterInterval_PositiveValue_ReturnsFalse_363) {

    MockSignedSignificandBits s;

    s.set_negative(false);

    EXPECT_EQ(nearest_toward_plus_infinity_t::shorter_interval(s), interval_type::asymmetric_boundary{false});

}



TEST_F(DragonboxTest_363, ShorterInterval_NegativeValue_ReturnsTrue_363) {

    MockSignedSignificandBits s;

    s.set_negative(true);

    EXPECT_EQ(nearest_toward_plus_infinity_t::shorter_interval(s), interval_type::asymmetric_boundary{true});

}



TEST_F(DragonboxTest_363, NormalInterval_UnusedFunction_ShouldNotCompileIfCalled_363) {

    MockSignedSignificandBits s;

    // This test case is more of a conceptual one, as we cannot directly test an unused function.

    // The presence of this test indicates that normal_interval should not be used in these tests.

}



TEST_F(DragonboxTest_363, BoundaryCondition_PositiveZero_ReturnsFalse_363) {

    MockSignedSignificandBits s;

    s.set_negative(false);

    EXPECT_EQ(nearest_toward_plus_infinity_t::shorter_interval(s), interval_type::asymmetric_boundary{false});

}



TEST_F(DragonboxTest_363, BoundaryCondition_NegativeZero_ReturnsTrue_363) {

    MockSignedSignificandBits s;

    s.set_negative(true);

    EXPECT_EQ(nearest_toward_plus_infinity_t::shorter_interval(s), interval_type::asymmetric_boundary{true});

}
