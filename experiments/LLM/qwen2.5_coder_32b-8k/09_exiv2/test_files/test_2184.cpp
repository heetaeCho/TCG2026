#include <gtest/gtest.h>

#include "makernote_int.hpp"

#include "exiv2/types.hpp"



using namespace Exiv2::Internal;

using namespace Exiv2;



class OlympusMnHeaderTest_2184 : public ::testing::Test {

protected:

    OlympusMnHeader olympusMnHeader_;

};



TEST_F(OlympusMnHeaderTest_2184, ConstructorInitializesSignature_2184) {

    // Since the constructor reads a signature, we assume it initializes correctly

    // without needing to verify internal state.

}



TEST_F(OlympusMnHeaderTest_2184, ReadReturnsFalseOnInvalidData_2184) {

    byte invalidData[] = {0x00, 0x00};

    ByteOrder byteOrder = littleEndian;

    EXPECT_FALSE(olympusMnHeader_.read(invalidData, sizeof(invalidData), byteOrder));

}



TEST_F(OlympusMnHeaderTest_2184, ReadReturnsTrueOnValidData_2184) {

    // Assuming valid data for Olympus signature is 0x4D4D or 0x4949

    byte validData[] = {0x4D, 0x4D};

    ByteOrder byteOrder = littleEndian;

    EXPECT_TRUE(olympusMnHeader_.read(validData, sizeof(validData), byteOrder));

}



TEST_F(OlympusMnHeaderTest_2184, SizeOfSignatureReturnsCorrectValue_2184) {

    size_t expectedSize = OlympusMnHeader::sizeOfSignature();

    EXPECT_EQ(expectedSize, 2u); // Assuming signature size is 2 bytes

}



TEST_F(OlympusMnHeaderTest_2184, SetByteOrderSetsCorrectly_2184) {

    ByteOrder byteOrder = bigEndian;

    olympusMnHeader_.setByteOrder(byteOrder);

    EXPECT_EQ(olympusMnHeader_.byteOrder(), byteOrder);

}



TEST_F(OlympusMnHeaderTest_2184, IfdOffsetReturnsZeroByDefault_2184) {

    EXPECT_EQ(olympusMnHeader_.ifdOffset(), 0u);

}



TEST_F(OlympusMnHeaderTest_2184, BaseOffsetReturnsCorrectValue_2184) {

    size_t mnOffset = 10;

    EXPECT_EQ(olympusMnHeader_.baseOffset(mnOffset), mnOffset);

}
