#include <gtest/gtest.h>

#include "TestProjects/exiv2/src/crwimage_int.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2::Internal;



TEST_F(CiffComponentTest_1773, NormalOperation_ValueData_1773) {

    CiffComponent component;

    byte data[] = {0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00};

    component.doRead(data, sizeof(data), 0, ByteOrder::littleEndian);

    EXPECT_EQ(component.tag(), 1);

    EXPECT_EQ(component.size(), 4);

    EXPECT_EQ(component.offset(), 16);

}



TEST_F(CiffComponentTest_1773, NormalOperation_DirectoryData_1773) {

    CiffComponent component;

    byte data[] = {0x00, 0x02};

    component.doRead(data, sizeof(data), 0, ByteOrder::littleEndian);

    EXPECT_EQ(component.tag(), 2);

    EXPECT_EQ(component.size(), 8);

    EXPECT_EQ(component.offset(), 2);

}



TEST_F(CiffComponentTest_1773, BoundaryCondition_SizeTooSmall_1773) {

    CiffComponent component;

    byte data[] = {0x00, 0x01, 0x00, 0x04};

    EXPECT_THROW(component.doRead(data, sizeof(data), 0, ByteOrder::littleEndian), Exiv2::Error);

}



TEST_F(CiffComponentTest_1773, BoundaryCondition_StartTooLarge_1773) {

    CiffComponent component;

    byte data[] = {0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00};

    EXPECT_THROW(component.doRead(data, sizeof(data), 11, ByteOrder::littleEndian), Exiv2::Error);

}



TEST_F(CiffComponentTest_1773, ExceptionalCase_NotACrwImage_1773) {

    CiffComponent component;

    byte data[] = {0x00, 0x01};

    EXPECT_THROW(component.doRead(data, sizeof(data), 1, ByteOrder::littleEndian), Exiv2::Error);

}



TEST_F(CiffComponentTest_1773, ExceptionalCase_OffsetOutOfRange_1773) {

    CiffComponent component;

    byte data[] = {0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF};

    EXPECT_THROW(component.doRead(data, sizeof(data), 0, ByteOrder::littleEndian), Exiv2::Error);

}



TEST_F(CiffComponentTest_1773, ExceptionalCase_SizeTooLarge_1773) {

    CiffComponent component;

    byte data[] = {0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x10};

    EXPECT_THROW(component.doRead(data, sizeof(data), 0, ByteOrder::littleEndian), Exiv2::Error);

}
