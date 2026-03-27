#include <gtest/gtest.h>

#include "crwimage_int.hpp"



using namespace Exiv2::Internal;



class CiffComponentTest_1780 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize CiffComponent with sample values

        component = std::make_unique<CiffComponent>(0x1234, 0x5678);

        component->setSize(10);

        component->setOffset(20);

    }



    std::unique_ptr<CiffComponent> component;

};



TEST_F(CiffComponentTest_1780, WriteDirEntry_ValueData_1780) {

    Blob blob;

    ByteOrder byteOrder = littleEndian;



    component->setDataLocation(DataLocId::valueData);

    component->writeDirEntry(blob, byteOrder);



    EXPECT_EQ(blob.size(), 12u); // tag (2 bytes), size (4 bytes), offset (4 bytes)

}



TEST_F(CiffComponentTest_1780, WriteDirEntry_DirectoryData_1780) {

    Blob blob;

    ByteOrder byteOrder = littleEndian;



    component->setDataLocation(DataLocId::directoryData);

    component->writeDirEntry(blob, byteOrder);



    EXPECT_EQ(blob.size(), 8u); // tag (2 bytes), pData (6 bytes padded to 8)

}



TEST_F(CiffComponentTest_1780, WriteDirEntry_SizeBoundary_1780) {

    Blob blob;

    ByteOrder byteOrder = littleEndian;



    component->setSize(4);

    component->setDataLocation(DataLocId::directoryData);

    component->writeDirEntry(blob, byteOrder);



    EXPECT_EQ(blob.size(), 8u); // tag (2 bytes), pData (4 bytes padded to 8)

}



TEST_F(CiffComponentTest_1780, WriteDirEntry_OffsetBoundary_1780) {

    Blob blob;

    ByteOrder byteOrder = littleEndian;



    component->setOffset(0);

    component->setDataLocation(DataLocId::valueData);

    component->writeDirEntry(blob, byteOrder);



    EXPECT_EQ(blob.size(), 12u); // tag (2 bytes), size (4 bytes), offset (4 bytes)

}



TEST_F(CiffComponentTest_1780, WriteDirEntry_DataLocationDefault_1780) {

    Blob blob;

    ByteOrder byteOrder = littleEndian;



    component->setDataLocation(static_cast<DataLocId>(99)); // Invalid DataLocId

    component->writeDirEntry(blob, byteOrder);



    EXPECT_EQ(blob.size(), 0u); // No data written if DataLocId is invalid

}



TEST_F(CiffComponentTest_1780, WriteDirEntry_LittleEndian_1780) {

    Blob blob;

    ByteOrder byteOrder = littleEndian;



    component->setDataLocation(DataLocId::valueData);

    component->writeDirEntry(blob, byteOrder);



    EXPECT_EQ(blob[0], 0x34); // Little endian: tag (0x1234) -> 0x34, 0x12

    EXPECT_EQ(blob[1], 0x12);

}



TEST_F(CiffComponentTest_1780, WriteDirEntry_BigEndian_1780) {

    Blob blob;

    ByteOrder byteOrder = bigEndian;



    component->setDataLocation(DataLocId::valueData);

    component->writeDirEntry(blob, byteOrder);



    EXPECT_EQ(blob[0], 0x12); // Big endian: tag (0x1234) -> 0x12, 0x34

    EXPECT_EQ(blob[1], 0x34);

}
