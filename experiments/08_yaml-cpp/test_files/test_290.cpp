#include <gtest/gtest.h>

#include "dragonbox.h"



using namespace YAML::jkj::dragonbox;



// Test Fixture for float_bits class tests

class FloatBitsTest_290 : public ::testing::Test {

protected:

    using FormatTraits = /* specify appropriate format traits */;

    using ExponentInt = typename FormatTraits::exponent_int;

    using CarrierUInt = typename FormatTraits::carrier_uint;

    using SignedSignificandBits = signed_significand_bits<FormatTraits>;



    FloatBitsTest_290() : fb(0) {} // Initialize with a default bit pattern



    float_bits<FormatTraits> fb;

};



// Test normal operation of remove_exponent_bits

TEST_F(FloatBitsTest_290, RemoveExponentBits_NormalOperation_290) {

    CarrierUInt testPattern = /* specify a valid bit pattern */;

    fb = float_bits<FormatTraits>(testPattern);

    SignedSignificandBits result = fb.remove_exponent_bits();

    // Assuming we have an expected value for comparison

    SignedSignificandBits expected = /* specify expected signed_significand_bits */;

    EXPECT_EQ(result, expected);

}



// Test boundary condition with zero bit pattern

TEST_F(FloatBitsTest_290, RemoveExponentBits_ZeroPattern_290) {

    fb = float_bits<FormatTraits>(0);

    SignedSignificandBits result = fb.remove_exponent_bits();

    // Assuming we have an expected value for comparison

    SignedSignificandBits expected = /* specify expected signed_significand_bits */;

    EXPECT_EQ(result, expected);

}



// Test boundary condition with maximum bit pattern

TEST_F(FloatBitsTest_290, RemoveExponentBits_MaxPattern_290) {

    CarrierUInt testPattern = std::numeric_limits<CarrierUInt>::max();

    fb = float_bits<FormatTraits>(testPattern);

    SignedSignificandBits result = fb.remove_exponent_bits();

    // Assuming we have an expected value for comparison

    SignedSignificandBits expected = /* specify expected signed_significand_bits */;

    EXPECT_EQ(result, expected);

}



// Test exceptional or error case if applicable (not specified in interface)

// If no exceptional cases are observable through the interface, this test can be omitted



// Verification of external interactions is not applicable here as there are no external collaborators

```


