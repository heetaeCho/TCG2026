#include <gtest/gtest.h>

#include "TestProjects/exiv2/src/crwimage_int.hpp"



using namespace Exiv2::Internal;



class CiffComponentTest_1761 : public ::testing::Test {

protected:

    CiffComponent component;

};



TEST_F(CiffComponentTest_1761, OffsetReturnsZeroByDefault_1761) {

    EXPECT_EQ(component.offset(), 0);

}



// Assuming the constructor initializes offset_ properly

TEST_F(CiffComponentTest_1761, ConstructorInitializesOffsetProperly_1761) {

    CiffComponent comp(0x0001, 0x0002);

    EXPECT_EQ(comp.offset(), 0); // Assuming offset is not set by constructor

}



TEST_F(CiffComponentTest_1761, SetOffsetUpdatesOffsetValue_1761) {

    size_t newOffset = 12345;

    component.setOffset(newOffset);

    EXPECT_EQ(component.offset(), newOffset);

}



// Boundary condition test for offset

TEST_F(CiffComponentTest_1761, SetOffsetToMaxSizeT_1761) {

    component.setOffset(std::numeric_limits<size_t>::max());

    EXPECT_EQ(component.offset(), std::numeric_limits<size_t>::max());

}



// Assuming there are error conditions or exceptional cases that can be tested

// For example, invalid parameters in read function

TEST_F(CiffComponentTest_1761, ReadWithNullPointerThrowsException_1761) {

    EXPECT_THROW(component.read(nullptr, 10, 0, Exiv2::littleEndian), std::invalid_argument);

}



// Assuming there are error conditions or exceptional cases that can be tested

// For example, invalid size in read function

TEST_F(CiffComponentTest_1761, ReadWithZeroSizeThrowsException_1761) {

    const byte* data = new byte[10];

    EXPECT_THROW(component.read(data, 0, 0, Exiv2::littleEndian), std::invalid_argument);

    delete[] data;

}



// Assuming there are error conditions or exceptional cases that can be tested

// For example, invalid size in read function

TEST_F(CiffComponentTest_1761, ReadWithNegativeSizeThrowsException_1761) {

    const byte* data = new byte[10];

    EXPECT_THROW(component.read(data, -1, 0, Exiv2::littleEndian), std::invalid_argument);

    delete[] data;

}



// Assuming there are error conditions or exceptional cases that can be tested

// For example, invalid parameters in write function

TEST_F(CiffComponentTest_1761, WriteWithNullPointerThrowsException_1761) {

    Blob blob;

    EXPECT_THROW(component.write(blob, Exiv2::littleEndian, 0), std::invalid_argument);

}



// Assuming there are error conditions or exceptional cases that can be tested

// For example, invalid offset in write function

TEST_F(CiffComponentTest_1761, WriteWithNegativeOffsetThrowsException_1761) {

    Blob blob;

    EXPECT_THROW(component.write(blob, Exiv2::littleEndian, -1), std::invalid_argument);

}
