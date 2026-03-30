#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/epsimage.hpp"

#include "exiv2/xmp_exiv2.hpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;

using ::testing::Throw;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(void, seek, (long offset, Position from), (override));

    MOCK_METHOD(long, tell, (), (const, override));

    MOCK_METHOD(bool, read, (byte* data, long numBytes), (override));

    MOCK_METHOD(bool, write, (const byte* data, long numBytes), (override));

    MOCK_METHOD(void, close, (), (override));

    MOCK_METHOD(std::string, path, (), (const, override));

};



class MockXmpParser : public XmpParser {

public:

    MOCK_STATIC_METHOD2(decode, int(XmpData& xmpData, const std::string& xmpPacket));

    MOCK_STATIC_METHOD4(encode, int(std::string& xmpPacket, const XmpData& xmpData, uint16_t formatFlags, uint32_t padding));

};



class EpsImageTest : public ::testing::Test {

protected:

    void SetUp() override {

        ioMock = std::make_unique<MockBasicIo>();

        image = new EpsImage(std::move(ioMock), false);

    }



    void TearDown() override {

        delete image;

    }



    EpsImage* image;

    std::unique_ptr<MockBasicIo> ioMock;

};



TEST_F(EpsImageTest_1754, WriteMetadata_SuccessfulEncode_1754) {

    XmpData xmpData;

    std::string xmpPacket = "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\" x:xmptk=\"XMP Core 6.0.0\"></x:xmpmeta>";



    EXPECT_CALL(*ioMock, path()).Times(2);

    EXPECT_CALL(MockXmpParser::encode, (_ , _, _, _)).WillOnce(Return(2));

    EXPECT_CALL(MockXmpParser::encode, (_, xmpData, _, _)).WillOnce(Return(3));



    image->setXmpData(xmpData);

    image->writeMetadata();

}



TEST_F(EpsImageTest_1754, WriteMetadata_EncodeFails_ThrowsError_1754) {

    XmpData xmpData;

    std::string xmpPacket = "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\" x:xmptk=\"XMP Core 6.0.0\"></x:xmpmeta>";



    EXPECT_CALL(*ioMock, path()).Times(2);

    EXPECT_CALL(MockXmpParser::encode, (_ , _, _, _)).WillOnce(Return(0));

    

    image->setXmpData(xmpData);



    EXPECT_THROW(image->writeMetadata(), Error);

}



TEST_F(EpsImageTest_1754, WriteMetadata_WriteXmpFromPacketTrue_1754) {

    XmpData xmpData;

    std::string xmpPacket = "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\" x:xmptk=\"XMP Core 6.0.0\"></x:xmpmeta>";



    EXPECT_CALL(*ioMock, path()).Times(2);

    EXPECT_CALL(MockXmpParser::encode, (_ , _, _, _)).WillOnce(Return(3));

    EXPECT_CALL(MockXmpParser::decode, (_, xmpPacket)).WillOnce(Return(1));



    image->setXmpData(xmpData);

    image->writeXmpFromPacket(true);



    image->writeMetadata();

}
