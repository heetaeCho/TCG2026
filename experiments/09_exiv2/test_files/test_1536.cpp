#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "makernote_int.cpp"  // Assuming this is how we include the file



using namespace Exiv2::Internal;



class NikonSelectorTest_1536 : public ::testing::Test {

protected:

    uint16_t tag;

    byte pData[8];

    size_t size;

    TiffComponent* pRoot = nullptr;  // Assuming TiffComponent is a pointer and we can initialize it to nullptr for this test

};



TEST_F(NikonSelectorTest_1536, NormalOperation_1536) {

    tag = 0x0001;

    pData[0] = 'N'; pData[1] = 'I'; pData[2] = 'K'; pData[3] = 'O';

    size = 4;

    EXPECT_EQ(nikonSelector(tag, pData, size, pRoot), 0);  // Assuming the idx_ for this key is 0

}



TEST_F(NikonSelectorTest_1536, BoundaryCondition_SizeLessThanFour_1536) {

    tag = 0x0001;

    pData[0] = 'N'; pData[1] = 'I';

    size = 2;

    EXPECT_EQ(nikonSelector(tag, pData, size, pRoot), -1);

}



TEST_F(NikonSelectorTest_1536, BoundaryCondition_SizeExactlyFour_1536) {

    tag = 0x0001;

    pData[0] = 'N'; pData[1] = 'I'; pData[2] = 'K'; pData[3] = 'O';

    size = 4;

    EXPECT_EQ(nikonSelector(tag, pData, size, pRoot), 0);  // Assuming the idx_ for this key is 0

}



TEST_F(NikonSelectorTest_1536, KeyNotFound_1536) {

    tag = 0xFFFF;

    pData[0] = 'U'; pData[1] = 'N'; pData[2] = 'K'; pData[3] = 'N';

    size = 4;

    EXPECT_EQ(nikonSelector(tag, pData, size, pRoot), -1);

}
