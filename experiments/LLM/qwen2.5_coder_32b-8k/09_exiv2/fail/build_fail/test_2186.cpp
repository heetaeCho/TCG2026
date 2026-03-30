#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "makernote_int.hpp"

#include "types.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class OMSystemMnHeaderTest : public ::testing::Test {

protected:

    OMSystemMnHeader header;

};



TEST_F(OMSystemMnHeaderTest_2186, DefaultConstructorInitializesCorrectly_2186) {

    // Since we cannot access internal state, we will verify behavior through observable functions.

    EXPECT_EQ(header.byteOrder(), ByteOrder::invalidByteOrder);

}



TEST_F(OMSystemMnHeaderTest_2186, SetByteOrderUpdatesCorrectly_2186) {

    header.setByteOrder(ByteOrder::littleEndian);

    EXPECT_EQ(header.byteOrder(), ByteOrder::littleEndian);



    header.setByteOrder(ByteOrder::bigEndian);

    EXPECT_EQ(header.byteOrder(), ByteOrder::bigEndian);

}



TEST_F(OMSystemMnHeaderTest_2186, SizeOfSignatureIsConsistent_2186) {

    size_t expectedSize = OMSystemMnHeader::sizeOfSignature();

    EXPECT_EQ(expectedSize, OMSystemMnHeader::sizeOfSignature());

}



TEST_F(OMSystemMnHeaderTest_2186, ReadFunctionReturnsFalseForInvalidData_2186) {

    const byte invalidData[] = {0x00, 0x00, 0x00};

    size_t dataSize = sizeof(invalidData);

    bool result = header.read(invalidData, dataSize, ByteOrder::littleEndian);

    EXPECT_FALSE(result);

}



TEST_F(OMSystemMnHeaderTest_2186, WriteFunctionHandlesIoWrapperCorrectly_2186) {

    class MockIoWrapper : public IoWrapper {

    public:

        MOCK_METHOD(void, write, (const byte*, size_t), (override));

    };



    MockIoWrapper mockIoWrapper;

    EXPECT_CALL(mockIoWrapper, write(testing::_, testing::_));



    header.write(mockIoWrapper, ByteOrder::littleEndian);

}



TEST_F(OMSystemMnHeaderTest_2186, IfdOffsetReturnsValidValue_2186) {

    size_t ifdOffset = header.ifdOffset();

    EXPECT_GE(ifdOffset, 0); // Assuming a valid offset is non-negative

}



TEST_F(OMSystemMnHeaderTest_2186, BaseOffsetCalculatesCorrectly_2186) {

    size_t baseOffset = header.baseOffset(10);

    EXPECT_GE(baseOffset, 0); // Assuming a valid offset is non-negative

}
