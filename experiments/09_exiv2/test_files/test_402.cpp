#include <gtest/gtest.h>

#include "tiffcomposite_int.hpp"



namespace Exiv2 {

namespace Internal {



class TiffSubIfdTest : public ::testing::Test {

protected:

    TiffSubIfd tiffSubIfd;



    TiffSubIfdTest() : tiffSubIfd(0, IfdId(), IfdId()) {}

};



TEST_F(TiffSubIfdTest_402, DoSizeData_ReturnsZeroForEmptyIFDs_402) {

    EXPECT_EQ(tiffSubIfd.doSizeData(), 0);

}



TEST_F(TiffSubIfdTest_402, DoSizeData_ReturnsSumOfSizes_402) {

    // Assuming we can modify ifds_ for testing purposes

    // This is a workaround since the actual implementation details are not accessible

    TiffSubIfd::Ifds mockIfds;

    mockIfds.push_back(TiffSubIfd(1, IfdId(), IfdId()));

    mockIfds.push_back(TiffSubIfd(2, IfdId(), IfdId()));



    // Mocking the size of each ifd

    EXPECT_CALL(mockIfds[0], size()).WillOnce(::testing::Return(5));

    EXPECT_CALL(mockIfds[1], size()).WillOnce(::testing::Return(7));



    tiffSubIfd.ifds_ = mockIfds;

    EXPECT_EQ(tiffSubIfd.doSizeData(), 12);

}



}  // namespace Internal

}  // namespace Exiv2
