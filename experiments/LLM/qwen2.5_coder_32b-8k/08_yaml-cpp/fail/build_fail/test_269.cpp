#include <gtest/gtest.h>

#include "dragonbox.h"



using namespace YAML::jkj::dragonbox;



// Mocking external collaborators or dependencies if needed

// In this case, there are no external collaborators to mock



struct TestFormat {

    using carrier_uint = uint64_t;

    using exponent_int = int32_t;

    static constexpr int significand_bits = 52; // Example value for double precision

    static constexpr int exponent_bits = 11;   // Example value for double precision

};



using TestTraits = ieee754_binary_traits<TestFormat, TestFormat::carrier_uint, TestFormat::exponent_int>;



class DragonboxTest_269 : public ::testing::Test {

protected:

    using CarrierUInt = TestFormat::carrier_uint;

    using ExponentInt = TestFormat::exponent_int;



    static constexpr int kSignificandBits = TestFormat::significand_bits;

    static constexpr int kExponentBits = TestFormat::exponent_bits;

};



TEST_F(DragonboxTest_269, ExtractExponentBits_NormalOperation_269) {

    CarrierUInt input = 0x408F400000000000; // Example value

    ExponentInt expectedExponentBits = 1027; // (input >> significand_bits) & ((1 << exponent_bits) - 1)

    EXPECT_EQ(TestTraits::extract_exponent_bits(input), expectedExponentBits);

}



TEST_F(DragonboxTest_269, ExtractExponentBits_BoundaryCondition_Max_269) {

    CarrierUInt input = 0x7FF0000000000000; // Maximum exponent bits set

    ExponentInt expectedExponentBits = (1 << kExponentBits) - 1;

    EXPECT_EQ(TestTraits::extract_exponent_bits(input), expectedExponentBits);

}



TEST_F(DragonboxTest_269, ExtractExponentBits_BoundaryCondition_Min_269) {

    CarrierUInt input = 0x0000000000000000; // Minimum exponent bits set

    ExponentInt expectedExponentBits = 0;

    EXPECT_EQ(TestTraits::extract_exponent_bits(input), expectedExponentBits);

}



// Assuming no exceptional cases are observable through the interface for this function
