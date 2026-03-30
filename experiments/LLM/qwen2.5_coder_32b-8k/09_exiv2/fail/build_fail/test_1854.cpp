#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/xmp_exiv2.hpp"

#include "exiv2/value.hpp"

#include "./TestProjects/exiv2/src/convert.cpp"



using namespace Exiv2;

using ::testing::NiceMock;

using ::testing::Return;



class MockXmpData : public XmpData {

public:

    MOCK_METHOD(iterator, findKey, (const XmpKey & key), (override));

    MOCK_METHOD(void, setPacket, (std::string xmpPacket), (override));

    MOCK_METHOD(bool, usePacket, (), (const, override));

};



class ConverterTest_1854 : public ::testing::Test {

protected:

    NiceMock<MockXmpData> mock_xmp_data;

    ExifData exif_data;

    Converter converter{exif_data, mock_xmp_data};

};



TEST_F(ConverterTest_1854, SyncExifWithXmp_NativeDigestsMatch_1854) {

    Xmpdatum td(XmpKey("Xmp.tiff.NativeDigest"), nullptr);

    Xmpdatum ed(XmpKey("Xmp.exif.NativeDigest"), nullptr);



    EXPECT_CALL(mock_xmp_data, findKey(XmpKey("Xmp.tiff.NativeDigest"))).WillOnce(Return(&td));

    EXPECT_CALL(mock_xmp_data, findKey(XmpKey("Xmp.exif.NativeDigest"))).WillOnce(Return(&ed));



    td.setValue(new Value(Exiv2::asciiString));

    ed.setValue(new Value(Exiv2::asciiString));

    td.value().setValue("digest1");

    ed.value().setValue("digest1");



    converter.syncExifWithXmp();

}



TEST_F(ConverterTest_1854, SyncExifWithXmp_NativeDigestsDoNotMatch_1854) {

    Xmpdatum td(XmpKey("Xmp.tiff.NativeDigest"), nullptr);

    Xmpdatum ed(XmpKey("Xmp.exif.NativeDigest"), nullptr);



    EXPECT_CALL(mock_xmp_data, findKey(XmpKey("Xmp.tiff.NativeDigest"))).WillOnce(Return(&td));

    EXPECT_CALL(mock_xmp_data, findKey(XmpKey("Xmp.exif.NativeDigest"))).WillOnce(Return(&ed));



    td.setValue(new Value(Exiv2::asciiString));

    ed.setValue(new Value(Exiv2::asciiString));

    td.value().setValue("digest1");

    ed.value().setValue("digest2");



    converter.syncExifWithXmp();

}



TEST_F(ConverterTest_1854, SyncExifWithXmp_NativeDigestsMissing_1854) {

    EXPECT_CALL(mock_xmp_data, findKey(XmpKey("Xmp.tiff.NativeDigest"))).WillOnce(Return(mock_xmp_data.end()));

    EXPECT_CALL(mock_xmp_data, findKey(XmpKey("Xmp.exif.NativeDigest"))).WillOnce(Return(mock_xmp_data.end()));



    converter.syncExifWithXmp();

}



TEST_F(ConverterTest_1854, SyncExifWithXmp_NativeDigestsOneMissing_1854) {

    Xmpdatum td(XmpKey("Xmp.tiff.NativeDigest"), nullptr);



    EXPECT_CALL(mock_xmp_data, findKey(XmpKey("Xmp.tiff.NativeDigest"))).WillOnce(Return(&td));

    EXPECT_CALL(mock_xmp_data, findKey(XmpKey("Xmp.exif.NativeDigest"))).WillOnce(Return(mock_xmp_data.end()));



    converter.syncExifWithXmp();

}
