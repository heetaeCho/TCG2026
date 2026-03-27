#include <gtest/gtest.h>

#include "makernote_int.hpp"

#include <gmock/gmock.h>



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::Return;



class Casio2MnHeaderTest : public ::testing::Test {

protected:

    Casio2MnHeader header;

};



TEST_F(Casio2MnHeaderTest_1506, ByteOrder_ReturnsCorrectValue_1506) {

    EXPECT_EQ(header.byteOrder(), littleEndian); // Assuming default byte order is littleEndian

}



// Mock IoWrapper for testing write method

class MockIoWrapper : public IoWrapper {

public:

    MOCK_METHOD(size_t, write, (const byte* data, size_t length), (override));

};



TEST_F(Casio2MnHeaderTest_1506, Write_ReturnsCorrectSize_1506) {

    MockIoWrapper mockIoWrapper;

    EXPECT_CALL(mockIoWrapper, write(_, _)).WillOnce(Return(4)); // Assuming write returns 4 bytes written

    size_t result = header.write(mockIoWrapper, littleEndian);

    EXPECT_EQ(result, 4);

}



TEST_F(Casio2MnHeaderTest_1506, Read_ReturnsTrueForValidData_1506) {

    byte data[] = { 0x01, 0x02, 0x03, 0x04 };

    bool result = header.read(data, sizeof(data), littleEndian);

    EXPECT_TRUE(result); // Assuming valid data returns true

}



TEST_F(Casio2MnHeaderTest_1506, Read_ReturnsFalseForInvalidData_1506) {

    byte invalidData[] = { 0xFF, 0xFE }; // Invalid data example

    bool result = header.read(invalidData, sizeof(invalidData), littleEndian);

    EXPECT_FALSE(result); // Assuming invalid data returns false

}



TEST_F(Casio2MnHeaderTest_1506, Size_ReturnsCorrectValue_1506) {

    size_t result = header.size();

    EXPECT_EQ(result, 8); // Assuming default size is 8 bytes

}



TEST_F(Casio2MnHeaderTest_1506, IfdOffset_ReturnsCorrectValue_1506) {

    size_t result = header.ifdOffset();

    EXPECT_EQ(result, 0); // Assuming default IFD offset is 0

}



TEST_F(Casio2MnHeaderTest_1506, SizeOfSignature_ReturnsCorrectValue_1506) {

    size_t result = Casio2MnHeader::sizeOfSignature();

    EXPECT_EQ(result, 4); // Assuming signature size is 4 bytes

}
