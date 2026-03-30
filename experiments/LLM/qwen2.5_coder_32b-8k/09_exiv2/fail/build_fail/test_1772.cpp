#include <gtest/gtest.h>

#include "crwimage_int.hpp"

#include <cstdint>



using namespace Exiv2::Internal;



// Test fixture for CiffComponent tests

class CiffComponentTest_1772 : public ::testing::Test {

protected:

    CiffComponent component;

};



// Normal operation: read function with valid parameters

TEST_F(CiffComponentTest_1772, ReadValidParameters_1772) {

    byte data[] = {0x01, 0x02, 0x03, 0x04};

    size_t size = sizeof(data);

    uint32_t start = 0;

    ByteOrder byteOrder = littleEndian;



    EXPECT_NO_THROW(component.read(data, size, start, byteOrder));

}



// Boundary condition: read function with zero size

TEST_F(CiffComponentTest_1772, ReadZeroSize_1772) {

    byte data[] = {0x01, 0x02, 0x03, 0x04};

    size_t size = 0;

    uint32_t start = 0;

    ByteOrder byteOrder = littleEndian;



    EXPECT_NO_THROW(component.read(data, size, start, byteOrder));

}



// Boundary condition: read function with start index at the end of data

TEST_F(CiffComponentTest_1772, ReadStartAtEnd_1772) {

    byte data[] = {0x01, 0x02, 0x03, 0x04};

    size_t size = sizeof(data);

    uint32_t start = sizeof(data);

    ByteOrder byteOrder = littleEndian;



    EXPECT_NO_THROW(component.read(data, size, start, byteOrder));

}



// Exceptional case: read function with nullptr data

TEST_F(CiffComponentTest_1772, ReadNullData_1772) {

    const byte* data = nullptr;

    size_t size = 4;

    uint32_t start = 0;

    ByteOrder byteOrder = littleEndian;



    EXPECT_THROW(component.read(data, size, start, byteOrder), std::invalid_argument);

}



// Exceptional case: read function with start index greater than data size

TEST_F(CiffComponentTest_1772, ReadStartGreaterThanSize_1772) {

    byte data[] = {0x01, 0x02, 0x03, 0x04};

    size_t size = sizeof(data);

    uint32_t start = sizeof(data) + 1;

    ByteOrder byteOrder = littleEndian;



    EXPECT_THROW(component.read(data, size, start, byteOrder), std::out_of_range);

}
