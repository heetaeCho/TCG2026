#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/makernote_int.hpp"

#include "exiv2/types.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class PanasonicMnHeaderTest : public ::testing::Test {

protected:

    PanasonicMnHeader header;

};



TEST_F(PanasonicMnHeaderTest_2190, ConstructorInitializesCorrectly_2190) {

    // The constructor reads a signature with invalidByteOrder. Ensure no exceptions are thrown.

}



TEST_F(PanasonicMnHeaderTest_2190, ReadFunctionReturnsFalseForInvalidData_2190) {

    const byte data[] = { 0x00, 0x00 };

    EXPECT_FALSE(header.read(data, sizeof(data), invalidByteOrder));

}



TEST_F(PanasonicMnHeaderTest_2190, ReadFunctionHandlesLittleEndianCorrectly_2190) {

    const byte data[] = { 0x4D, 0x4D, 0x00, 0x2A }; // Example valid header in little-endian

    EXPECT_TRUE(header.read(data, sizeof(data), littleEndian));

}



TEST_F(PanasonicMnHeaderTest_2190, ReadFunctionHandlesBigEndianCorrectly_2190) {

    const byte data[] = { 0x4D, 0x4D, 0x00, 0x2A }; // Example valid header in big-endian

    EXPECT_TRUE(header.read(data, sizeof(data), bigEndian));

}



TEST_F(PanasonicMnHeaderTest_2190, SizeFunctionReturnsExpectedValue_2190) {

    const size_t expectedSize = PanasonicMnHeader::sizeOfSignature();

    EXPECT_EQ(expectedSize, header.size());

}



TEST_F(PanasonicMnHeaderTest_2190, SetByteOrderUpdatesInternalState_2190) {

    header.setByteOrder(littleEndian);

    EXPECT_EQ(littleEndian, header.byteOrder());



    header.setByteOrder(bigEndian);

    EXPECT_EQ(bigEndian, header.byteOrder());

}



TEST_F(PanasonicMnHeaderTest_2190, WriteFunctionReturnsExpectedSize_2190) {

    IoWrapper ioWrapper; // Mock or create a suitable IoWrapper for testing

    size_t writtenSize = header.write(ioWrapper, littleEndian);

    EXPECT_EQ(header.size(), writtenSize);

}



TEST_F(PanasonicMnHeaderTest_2190, IfdOffsetFunctionReturnsExpectedValue_2190) {

    const size_t expectedIfdOffset = 0; // Assuming ifdOffset returns 0 as per normal behavior

    EXPECT_EQ(expectedIfdOffset, header.ifdOffset());

}



TEST_F(PanasonicMnHeaderTest_2190, BaseOffsetFunctionReturnsExpectedValue_2190) {

    const size_t mnOffset = 10;

    const size_t expectedBaseOffset = mnOffset; // Assuming baseOffset returns the same as mnOffset

    EXPECT_EQ(expectedBaseOffset, header.baseOffset(mnOffset));

}
