#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/makernote_int.cpp"



namespace Exiv2 {

namespace Internal {



class PanasonicMnHeaderTest_1476 : public ::testing::Test {

protected:

    PanasonicMnHeader header_;

    const byte validSignature[9] = { 'L', 'U', 'N', 'A', 'P', 'A', 'N', 'A', 'S' };

    const size_t validSize = 10; // Example size greater than signature length

};



TEST_F(PanasonicMnHeaderTest_1476, ReadValidData_1476) {

    byte data[10] = { 'L', 'U', 'N', 'A', 'P', 'A', 'N', 'A', 'S', 0x00 };

    ASSERT_TRUE(header_.read(data, validSize, littleEndian));

}



TEST_F(PanasonicMnHeaderTest_1476, ReadInvalidSignature_1476) {

    byte data[10] = { 'I', 'N', 'V', 'A', 'L', 'I', 'D', 'S', 'I', 0x00 };

    ASSERT_FALSE(header_.read(data, validSize, littleEndian));

}



TEST_F(PanasonicMnHeaderTest_1476, ReadNullData_1476) {

    ASSERT_FALSE(header_.read(nullptr, validSize, littleEndian));

}



TEST_F(PanasonicMnHeaderTest_1476, ReadTooSmallData_1476) {

    byte data[8] = { 'L', 'U', 'N', 'A', 'P', 'A', 'N', 'A' };

    ASSERT_FALSE(header_.read(data, 8, littleEndian));

}



TEST_F(PanasonicMnHeaderTest_1476, ReadExactSizeData_1476) {

    byte data[9] = { 'L', 'U', 'N', 'A', 'P', 'A', 'N', 'A', 'S' };

    ASSERT_TRUE(header_.read(data, 9, littleEndian));

}



} // namespace Internal

} // namespace Exiv2
