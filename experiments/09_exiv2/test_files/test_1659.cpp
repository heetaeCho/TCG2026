#include <gtest/gtest.h>

#include <gmock/gmock.h>



using namespace Exiv2;

using namespace Exiv2::Internal;



class MockTiffEntryBase : public TiffEntryBase {

public:

    MOCK_CONST_METHOD0(pData, const byte*());

    MOCK_CONST_METHOD0(storage, std::shared_ptr<DataBuf>());

};



class TiffDecoderTest_1659 : public ::testing::Test {

protected:

    IptcData iptcData_;

    XmpData xmpData_;

    MockTiffEntryBase mockObject_;

    TiffDecoder decoder_{ExifData{}, iptcData_, xmpData_, nullptr, nullptr};

};



TEST_F(TiffDecoderTest_1659, DecodeIptc_NoData_1659) {

    EXPECT_CALL(mockObject_, pData()).WillOnce(testing::Return(nullptr));



    decoder_.decodeIptc(&mockObject_);



    EXPECT_EQ(iptcData_.count(), 0u);

}



TEST_F(TiffDecoderTest_1659, DecodeIptc_ValidIptcBlock_1659) {

    const byte iptcData[] = { /* valid IPTC data */ };

    size_t size = sizeof(iptcData);



    EXPECT_CALL(mockObject_, pData()).WillOnce(testing::Return(iptcData));

    EXPECT_CALL(mockObject_, storage())

        .WillOnce(testing::Invoke([&]() {

            return std::make_shared<DataBuf>(iptcData, size);

        }));

    EXPECT_CALL(*Mockito::mock(&IptcParser), decode(testing::Ref(iptcData_), iptcData, size))

        .WillOnce(testing::Return(0));



    decoder_.decodeIptc(&mockObject_);



    EXPECT_EQ(iptcData_.count(), 1u); // Assuming valid IPTC data adds one entry

}



TEST_F(TiffDecoderTest_1659, DecodeIptc_InvalidIptcBlock_1659) {

    const byte iptcData[] = { /* invalid IPTC data */ };

    size_t size = sizeof(iptcData);



    EXPECT_CALL(mockObject_, pData()).WillOnce(testing::Return(iptcData));

    EXPECT_CALL(mockObject_, storage())

        .WillOnce(testing::Invoke([&]() {

            return std::make_shared<DataBuf>(iptcData, size);

        }));

    EXPECT_CALL(*Mockito::mock(&IptcParser), decode(testing::Ref(iptcData_), iptcData, size))

        .WillOnce(testing::Return(-1));



    decoder_.decodeIptc(&mockObject_);



    EXPECT_EQ(iptcData_.count(), 0u);

}



TEST_F(TiffDecoderTest_1659, DecodeIptc_ValidPhotoshopBlock_1659) {

    const byte photoshopData[] = { /* valid Photoshop data with IPTC block */ };

    size_t size = sizeof(photoshopData);



    EXPECT_CALL(mockObject_, pData()).WillOnce(testing::Return(photoshopData));

    EXPECT_CALL(mockObject_, storage())

        .WillOnce(testing::Invoke([&]() {

            return std::make_shared<DataBuf>(photoshopData, size);

        }));

    EXPECT_CALL(*Mockito::mock(&Photoshop), locateIptcIrb(photoshopData, size, testing::NotNull(), testing::NotNull(), testing::NotNull()))

        .WillOnce(testing::DoAll(

            testing::SetArgReferee<3>(photoshopData),

            testing::SetArgReferee<4>(0u),

            testing::SetArgReferee<5>(size),

            testing::Return(0)

        ));

    EXPECT_CALL(*Mockito::mock(&IptcParser), decode(testing::Ref(iptcData_), photoshopData, size))

        .WillOnce(testing::Return(0));



    decoder_.decodeIptc(&mockObject_);



    EXPECT_EQ(iptcData_.count(), 1u); // Assuming valid IPTC data adds one entry

}



TEST_F(TiffDecoderTest_1659, DecodeIptc_InvalidPhotoshopBlock_1659) {

    const byte photoshopData[] = { /* invalid Photoshop data */ };

    size_t size = sizeof(photoshopData);



    EXPECT_CALL(mockObject_, pData()).WillOnce(testing::Return(photoshopData));

    EXPECT_CALL(mockObject_, storage())

        .WillOnce(testing::Invoke([&]() {

            return std::make_shared<DataBuf>(photoshopData, size);

        }));

    EXPECT_CALL(*Mockito::mock(&Photoshop), locateIptcIrb(photoshopData, size, testing::NotNull(), testing::NotNull(), testing::NotNull()))

        .WillOnce(testing::Return(-1));



    decoder_.decodeIptc(&mockObject_);



    EXPECT_EQ(iptcData_.count(), 0u);

}



TEST_F(TiffDecoderTest_1659, DecodeIptc_DecodedAlready_1659) {

    const byte iptcData[] = { /* valid IPTC data */ };

    size_t size = sizeof(iptcData);



    EXPECT_CALL(mockObject_, pData()).WillOnce(testing::Return(iptcData));

    EXPECT_CALL(mockObject_, storage())

        .WillOnce(testing::Invoke([&]() {

            return std::make_shared<DataBuf>(iptcData, size);

        }));

    EXPECT_CALL(*Mockito::mock(&IptcParser), decode(testing::Ref(iptcData_), iptcData, size))

        .WillOnce(testing::Return(0));



    decoder_.decodeIptc(&mockObject_); // First call to decode

    decoder_.decodeIptc(&mockObject_); // Second call should not decode again



    EXPECT_EQ(iptcData_.count(), 1u);

}



TEST_F(TiffDecoderTest_1659, DecodeIptc_MultipleTags_1659) {

    const byte iptcDataTag83bb[] = { /* valid IPTC data for tag 0x83bb */ };

    size_t size83bb = sizeof(iptcDataTag83bb);

    const byte photoshopDataTag8649[] = { /* valid Photoshop data with IPTC block for tag 0x8649 */ };

    size_t size8649 = sizeof(photoshopDataTag8649);



    EXPECT_CALL(mockObject_, pData())

        .WillOnce(testing::Return(iptcDataTag83bb))

        .WillOnce(testing::Return(photoshopDataTag8649));

    EXPECT_CALL(mockObject_, storage())

        .WillOnce(testing::Invoke([&]() {

            return std::make_shared<DataBuf>(iptcDataTag83bb, size83bb);

        }))

        .WillOnce(testing::Invoke([&]() {

            return std::make_shared<DataBuf>(photoshopDataTag8649, size8649);

        }));

    EXPECT_CALL(*Mockito::mock(&IptcParser), decode(testing::Ref(iptcData_), iptcDataTag83bb, size83bb))

        .WillOnce(testing::Return(0));

    EXPECT_CALL(*Mockito::mock(&Photoshop), locateIptcIrb(photoshopDataTag8649, size8649, testing::NotNull(), testing::NotNull(), testing::NotNull()))

        .WillOnce(testing::DoAll(

            testing::SetArgReferee<3>(photoshopDataTag8649),

            testing::SetArgReferee<4>(0u),

            testing::SetArgReferee<5>(size8649),

            testing::Return(0)

        ));

    EXPECT_CALL(*Mockito::mock(&IptcParser), decode(testing::Ref(iptcData_), photoshopDataTag8649, size8649))

        .WillOnce(testing::Return(0));



    decoder_.decodeIptc(&mockObject_); // First call to decode tag 0x83bb

    decoder_.decodeIptc(&mockObject_); // Second call to decode tag 0x8649



    EXPECT_EQ(iptcData_.count(), 2u); // Assuming valid IPTC data adds one entry per tag

}
