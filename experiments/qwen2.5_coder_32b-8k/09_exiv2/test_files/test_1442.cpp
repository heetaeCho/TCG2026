#include <gtest/gtest.h>

#include "makernote_int.hpp"

#include "types.hpp"



namespace Exiv2 {

namespace Internal {



class Olympus2MnHeaderTest_1442 : public ::testing::Test {

protected:

    Olympus2MnHeader header_;

};



TEST_F(Olympus2MnHeaderTest_1442, SizeIsInitiallyZero_1442) {

    EXPECT_EQ(header_.size(), 0u);

}



TEST_F(Olympus2MnHeaderTest_1442, ReadReturnsFalseWithNullData_1442) {

    EXPECT_FALSE(header_.read(nullptr, 10, littleEndian));

}



TEST_F(Olympus2MnHeaderTest_1442, ReadReturnsFalseWithZeroSize_1442) {

    byte data[10];

    EXPECT_FALSE(header_.read(data, 0, littleEndian));

}



TEST_F(Olympus2MnHeaderTest_1442, WriteReturnsZeroWithNullIoWrapper_1442) {

    IoWrapper* ioWrapper = nullptr;

    EXPECT_EQ(header_.write(*ioWrapper, littleEndian), 0u);

}



TEST_F(Olympus2MnHeaderTest_1442, IfdOffsetIsInitiallyZero_1442) {

    EXPECT_EQ(header_.ifdOffset(), 0u);

}



TEST_F(Olympus2MnHeaderTest_1442, BaseOffsetWithZeroMnOffsetReturnsInitialBaseOffset_1442) {

    size_t mnOffset = 0;

    EXPECT_EQ(header_.baseOffset(mnOffset), header_.size());

}



TEST_F(Olympus2MnHeaderTest_1442, SizeOfSignatureIsPositive_1442) {

    EXPECT_GT(Olympus2MnHeader::sizeOfSignature(), 0u);

}



} // namespace Internal

} // namespace Exiv2
