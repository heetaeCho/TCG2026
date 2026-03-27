#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/image.hpp"

#include "exiv2/asfvideo.hpp"

#include "exiv2/xmp_exiv2.hpp"



using namespace Exiv2;



class AsfVideoTest_1570 : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> ioMock;

    AsfVideo* asfVideo;



    void SetUp() override {

        ioMock = BasicIo::createMemIo();

        asfVideo = new AsfVideo(std::move(ioMock));

    }



    void TearDown() override {

        delete asfVideo;

    }

};



TEST_F(AsfVideoTest_1570, ExtendedContentDescription_NoDescriptors_1570) {

    asfVideo->extendedContentDescription();

    EXPECT_EQ(asfVideo->xmpData()["Xmp.video.ExtendedContentDescription"].toString(), "");

}



TEST_F(AsfVideoTest_1570, ExtendedContentDescription_SingleUnicodeDescriptor_1570) {

    ioMock->write("\x00\x01", 2); // content_descriptor_count = 1

    ioMock->write("\x00\x08", 2); // descriptor_name_length = 8 (4 characters)

    ioMock->write("Name\0\0", 6); // "Name" in wide chars

    ioMock->write("\x00\x00", 2); // descriptor_value_data_type = 0 (Unicode string)

    ioMock->write("\x00\x08", 2); // descriptor_value_length = 8 (4 characters)

    ioMock->write("Value\0\0", 6); // "Value" in wide chars



    asfVideo->extendedContentDescription();

    EXPECT_EQ(asfVideo->xmpData()["Xmp.video.ExtendedContentDescription"].toString(), "Name: Value, ");

}



TEST_F(AsfVideoTest_1570, ExtendedContentDescription_MultipleDescriptors_1570) {

    ioMock->write("\x00\x02", 2); // content_descriptor_count = 2



    // First descriptor

    ioMock->write("\x00\x08", 2); // descriptor_name_length = 8 (4 characters)

    ioMock->write("Name1\0\0", 6); // "Name1" in wide chars

    ioMock->write("\x00\x00", 2); // descriptor_value_data_type = 0 (Unicode string)

    ioMock->write("\x00\x08", 2); // descriptor_value_length = 8 (4 characters)

    ioMock->write("Value1\0\0", 6); // "Value1" in wide chars



    // Second descriptor

    ioMock->write("\x00\x08", 2); // descriptor_name_length = 8 (4 characters)

    ioMock->write("Name2\0\0", 6); // "Name2" in wide chars

    ioMock->write("\x00\x01", 2); // descriptor_value_data_type = 1 (BYTE array)

    ioMock->write("\x00\x03", 2); // descriptor_value_length = 3

    ioMock->write("ABC", 3); // "ABC" as byte array



    asfVideo->extendedContentDescription();

    EXPECT_EQ(asfVideo->xmpData()["Xmp.video.ExtendedContentDescription"].toString(), "Name1: Value1, Name2: ABC, ");

}



TEST_F(AsfVideoTest_1570, ExtendedContentDescription_DescriptorTypes_1570) {

    ioMock->write("\x00\x04", 2); // content_descriptor_count = 4



    // Unicode string

    ioMock->write("\x00\x08", 2);

    ioMock->write("Name1\0\0", 6);

    ioMock->write("\x00\x00", 2);

    ioMock->write("\x00\x08", 2);

    ioMock->write("Value1\0\0", 6);



    // BYTE array

    ioMock->write("\x00\x08", 2);

    ioMock->write("Name2\0\0", 6);

    ioMock->write("\x00\x01", 2);

    ioMock->write("\x00\x03", 2);

    ioMock->write("ABC", 3);



    // BOOL

    ioMock->write("\x00\x08", 2);

    ioMock->write("Name3\0\0", 6);

    ioMock->write("\x00\x02", 2);

    ioMock->write("\x00\x00", 2);



    // DWORD

    ioMock->write("\x00\x08", 2);

    ioMock->write("Name4\0\0", 6);

    ioMock->write("\x00\x03", 2);

    ioMock->write("\x01\x00\x00\x00", 4);



    asfVideo->extendedContentDescription();

    EXPECT_EQ(asfVideo->xmpData()["Xmp.video.ExtendedContentDescription"].toString(), "Name1: Value1, Name2: ABC, Name3: 0, Name4: 1, ");

}



TEST_F(AsfVideoTest_1570, ExtendedContentDescription_EmptyDescriptorNames_1570) {

    ioMock->write("\x00\x02", 2); // content_descriptor_count = 2



    // First descriptor

    ioMock->write("\x00\x00", 2); // descriptor_name_length = 0

    ioMock->write("\x00\x00", 2); // descriptor_value_data_type = 0 (Unicode string)

    ioMock->write("\x00\x08", 2); // descriptor_value_length = 8 (4 characters)

    ioMock->write("Value1\0\0", 6); // "Value1" in wide chars



    // Second descriptor

    ioMock->write("\x00\x00", 2); // descriptor_name_length = 0

    ioMock->write("\x00\x01", 2); // descriptor_value_data_type = 1 (BYTE array)

    ioMock->write("\x00\x03", 2); // descriptor_value_length = 3

    ioMock->write("ABC", 3); // "ABC" as byte array



    asfVideo->extendedContentDescription();

    EXPECT_EQ(asfVideo->xmpData()["Xmp.video.ExtendedContentDescription"].toString(), ": Value1, : ABC, ");

}



TEST_F(AsfVideoTest_1570, ExtendedContentDescription_EmptyDescriptorValues_1570) {

    ioMock->write("\x00\x02", 2); // content_descriptor_count = 2



    // First descriptor

    ioMock->write("\x00\x08", 2);

    ioMock->write("Name1\0\0", 6);

    ioMock->write("\x00\x00", 2);

    ioMock->write("\x00\x00", 2);



    // Second descriptor

    ioMock->write("\x00\x08", 2);

    ioMock->write("Name2\0\0", 6);

    ioMock->write("\x00\x01", 2);

    ioMock->write("\x00\x00", 2);



    asfVideo->extendedContentDescription();

    EXPECT_EQ(asfVideo->xmpData()["Xmp.video.ExtendedContentDescription"].toString(), "Name1: , Name2: , ");

}



TEST_F(AsfVideoTest_1570, ExtendedContentDescription_UnsupportedDescriptorTypes_1570) {

    ioMock->write("\x00\x03", 2); // content_descriptor_count = 3



    // Supported type (Unicode string)

    ioMock->write("\x00\x08", 2);

    ioMock->write("Name1\0\0", 6);

    ioMock->write("\x00\x00", 2);

    ioMock->write("\x00\x08", 2);

    ioMock->write("Value1\0\0", 6);



    // Unsupported type

    ioMock->write("\x00\x08", 2);

    ioMock->write("Name2\0\0", 6);

    ioMock->write("\x00\xFF", 2); // Unknown data type



    // Supported type (DWORD)

    ioMock->write("\x00\x08", 2);

    ioMock->write("Name3\0\0", 6);

    ioMock->write("\x00\x03", 2);

    ioMock->write("\x01\x00\x00\x00", 4);



    asfVideo->extendedContentDescription();

    EXPECT_EQ(asfVideo->xmpData()["Xmp.video.ExtendedContentDescription"].toString(), "Name1: Value1, Name3: 1, ");

}
