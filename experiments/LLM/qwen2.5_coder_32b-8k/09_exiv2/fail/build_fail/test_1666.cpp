#include <gtest/gtest.h>

#include "tiffvisitor_int.hpp"



using namespace Exiv2::Internal;



class TiffEncoderTest : public ::testing::Test {

protected:

    // Mock objects or setup if needed

    TiffEncoder encoder{{}, {}, nullptr, false, PrimaryGroups(), nullptr, nullptr};

};



TEST_F(TiffEncoderTest_1666, SetDirtyFlagTrue_1666) {

    encoder.setDirty(true);

    EXPECT_EQ(encoder.dirty(), true);

}



TEST_F(TiffEncoderTest_1666, SetDirtyFlagFalse_1666) {

    encoder.setDirty(false);

    EXPECT_EQ(encoder.dirty(), false);

}



TEST_F(TiffEncoderTest_1666, SetDirtyTrueThenFalse_1666) {

    encoder.setDirty(true);

    encoder.setDirty(false);

    EXPECT_EQ(encoder.dirty(), false);

}



TEST_F(TiffEncoderTest_1666, SetDirtyFalseThenTrue_1666) {

    encoder.setDirty(false);

    encoder.setDirty(true);

    EXPECT_EQ(encoder.dirty(), true);

}
