#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/xmpsidecar.hpp"

#include "exiv2/basicio.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2;

using ::testing::Return;

using ::testing::Throw;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));

    MOCK_METHOD(void, transfer, (BasicIo& src), (override));

    MOCK_METHOD(const std::string&, path, (), (const override));

    MOCK_METHOD(int, error, (), (const override));

};



class XmpSidecarTest : public ::testing::Test {

protected:

    void SetUp() override {

        ioMock = std::make_unique<MockBasicIo>();

        xmpSidecar = std::make_unique<XmpSidecar>(std::move(ioMock), false);

    }



    std::unique_ptr<MockBasicIo> ioMock;

    std::unique_ptr<XmpSidecar> xmpSidecar;

};



TEST_F(XmpSidecarTest_1718, WriteMetadata_SuccessfulWrite_1718) {

    EXPECT_CALL(*ioMock, open()).WillOnce(Return(0));

    EXPECT_CALL(*ioMock, write(::testing::_, ::testing::_)).WillOnce(Return(1024));

    EXPECT_CALL(*ioMock, error()).WillOnce(Return(0));



    xmpSidecar->writeMetadata();

}



TEST_F(XmpSidecarTest_1718, WriteMetadata_OpenFailed_1718) {

    EXPECT_CALL(*ioMock, open()).WillOnce(Return(-1));

    EXPECT_THROW(xmpSidecar->writeMetadata(), Error);

}



TEST_F(XmpSidecarTest_1718, WriteMetadata_WriteFailed_1718) {

    EXPECT_CALL(*ioMock, open()).WillOnce(Return(0));

    EXPECT_CALL(*ioMock, write(::testing::_, ::testing::_)).WillOnce(Return(512));

    EXPECT_THROW(xmpSidecar->writeMetadata(), Error);

}



TEST_F(XmpSidecarTest_1718, WriteMetadata_TransferFailed_1718) {

    EXPECT_CALL(*ioMock, open()).WillOnce(Return(0));

    EXPECT_CALL(*ioMock, write(::testing::_, ::testing::_)).WillOnce(Return(1024));

    EXPECT_CALL(*ioMock, error()).WillOnce(Return(-1));



    EXPECT_THROW(xmpSidecar->writeMetadata(), Error);

}



TEST_F(XmpSidecarTest_1718, WriteMetadata_EmptyXmpPacket_NoWriteToIo_1718) {

    EXPECT_CALL(*ioMock, open()).WillOnce(Return(0));

    EXPECT_CALL(*ioMock, write(::testing::_, ::testing::_)).Times(0);

    xmpSidecar->xmpData_.setPacket("");



    xmpSidecar->writeMetadata();

}



TEST_F(XmpSidecarTest_1718, WriteMetadata_XmpPacketMissingXmlHeader_PrependsAndAppends_1718) {

    EXPECT_CALL(*ioMock, open()).WillOnce(Return(0));

    EXPECT_CALL(*ioMock, write(::testing::_, ::testing::_)).WillOnce(Return(2048));

    xmpSidecar->xmpData_.setPacket("Some XMP data");



    xmpSidecar->writeMetadata();

}
