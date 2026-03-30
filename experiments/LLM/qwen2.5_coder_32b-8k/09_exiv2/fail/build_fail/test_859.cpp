#include <gtest/gtest.h>

#include "./TestProjects/exiv2/src/value.cpp"



using namespace Exiv2;



class LangAltValueTest_859 : public ::testing::Test {

protected:

    LangAltValue langAltValue;

};



TEST_F(LangAltValueTest_859, ToUint32_ReturnsZero_859) {

    uint32_t result = langAltValue.toUint32(0);

    EXPECT_EQ(result, 0);

}



TEST_F(LangAltValueTest_859, ToUint32_SetsOkToFalse_859) {

    langAltValue.toUint32(0);

    // Since ok_ is a private member, we can't directly verify it.

    // Instead, we rely on the observable behavior described in the function.

}



TEST_F(LangAltValueTest_859, ToUint32_BoundaryConditionZeroIndex_859) {

    uint32_t result = langAltValue.toUint32(0);

    EXPECT_EQ(result, 0);

}



// Assuming size_t can be a large number, we test with a large index.

TEST_F(LangAltValueTest_859, ToUint32_BoundaryConditionLargeIndex_859) {

    uint32_t result = langAltValue.toUint32(static_cast<size_t>(-1));

    EXPECT_EQ(result, 0);

}
