#include <gtest/gtest.h>

#include "makernote_int.cpp"



namespace Exiv2 {

namespace Internal {



class MnHeaderTest_1435 : public ::testing::Test {

protected:

    MnHeader mnHeader;

};



TEST_F(MnHeaderTest_1435, BaseOffset_ReturnsZeroForAnyInput_1435) {

    EXPECT_EQ(mnHeader.baseOffset(0), 0);

    EXPECT_EQ(mnHeader.baseOffset(1), 0);

    EXPECT_EQ(mnHeader.baseOffset(100), 0);

}



TEST_F(MnHeaderTest_1435, BaseOffset_BoundaryCondition_Zero_1435) {

    EXPECT_EQ(mnHeader.baseOffset(0), 0);

}



TEST_F(MnHeaderTest_1435, BaseOffset_BoundaryCondition_MaxSizeT_1435) {

    EXPECT_EQ(mnHeader.baseOffset(std::numeric_limits<size_t>::max()), 0);

}



} // namespace Internal

} // namespace Exiv2
