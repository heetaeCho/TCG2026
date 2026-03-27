#include <gtest/gtest.h>

#include "tiffimage_int.hpp"



using namespace Exiv2::Internal;



class TiffHeaderBaseTest_1174 : public ::testing::Test {

protected:

    ByteOrder defaultByteOrder = littleEndian;

    uint32_t defaultSize = 20;

    uint32_t defaultOffset = 50;

    uint16_t defaultTag = 256;



    TiffHeaderBase* header;



    void SetUp() override {

        header = new TiffHeaderBase(defaultTag, defaultSize, defaultByteOrder, defaultOffset);

    }



    void TearDown() override {

        delete header;

    }

};



TEST_F(TiffHeaderBaseTest_1174, OffsetInitialValue_1174) {

    EXPECT_EQ(header->offset(), defaultOffset);

}



TEST_F(TiffHeaderBaseTest_1174, SetOffsetChangesValue_1174) {

    uint32_t newOffset = 100;

    header->setOffset(newOffset);

    EXPECT_EQ(header->offset(), newOffset);

}



TEST_F(TiffHeaderBaseTest_1174, ByteOrderInitialValue_1174) {

    EXPECT_EQ(header->byteOrder(), defaultByteOrder);

}



TEST_F(TiffHeaderBaseTest_1174, SetByteOrderChangesValue_1174) {

    ByteOrder newByteOrder = bigEndian;

    header->setByteOrder(newByteOrder);

    EXPECT_EQ(header->byteOrder(), newByteOrder);

}



TEST_F(TiffHeaderBaseTest_1174, SizeInitialValue_1174) {

    EXPECT_EQ(header->size(), defaultSize);

}



TEST_F(TiffHeaderBaseTest_1174, TagInitialValue_1174) {

    EXPECT_EQ(header->tag(), defaultTag);

}



TEST_F(TiffHeaderBaseTest_1174, IsImageTagReturnsFalseForNonImageTag_1174) {

    uint16_t nonImageTag = 0;

    IfdId groupId = ifd0Id;

    PrimaryGroups primaryGroups; // Assuming PrimaryGroups can be default constructed

    EXPECT_FALSE(header->isImageTag(nonImageTag, groupId, primaryGroups));

}



TEST_F(TiffHeaderBaseTest_1174, VirtualMethodsExistAndCompile_1174) {

    const byte* data = nullptr;

    size_t dataSize = 0;

    std::ostream os(nullptr);

    const char* prefix = "";



    // These calls ensure the virtual methods exist and compile

    header->read(data, dataSize);

    DataBuf buf = header->write();

    header->print(os, prefix);

}
