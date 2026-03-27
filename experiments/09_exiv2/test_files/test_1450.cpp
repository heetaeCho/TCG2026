#include <gtest/gtest.h>

#include "makernote_int.hpp"



using namespace Exiv2::Internal;



class OMSystemMnHeaderTest : public ::testing::Test {

protected:

    OMSystemMnHeader header;

};



TEST_F(OMSystemMnHeaderTest_BaseOffset_Nominal_1450, BaseOffset_ReturnsPassedValue_1450) {

    size_t mnOffset = 1234;

    EXPECT_EQ(header.baseOffset(mnOffset), mnOffset);

}



TEST_F(OMSystemMnHeaderTest_BaseOffset_Zero_1450, BaseOffset_ReturnsZero_1450) {

    size_t mnOffset = 0;

    EXPECT_EQ(header.baseOffset(mnOffset), mnOffset);

}



TEST_F(OMSystemMnHeaderTest_BaseOffset_MaxValue_1450, BaseOffset_ReturnsMaxValue_1450) {

    size_t mnOffset = std::numeric_limits<size_t>::max();

    EXPECT_EQ(header.baseOffset(mnOffset), mnOffset);

}
