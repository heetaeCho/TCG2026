#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/epsimage.hpp"

#include "exiv2/xmp_exiv2.hpp"

#include "exiv2/image.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2;

using testing::_;

using testing::Return;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(std::string, path, (), (const, override));

};



TEST_F(EpsImageTest_1753, ReadMetadataNormalOperation_1753) {

    auto io = std::make_unique<MockBasicIo>();

    EXPECT_CALL(*io, path()).WillOnce(Return("test.eps"));



    EpsImage image(std::move(io), false);

    image.readMetadata();

}



TEST_F(EpsImageTest_1753, ReadMetadataXmpPacketEmpty_1753) {

    auto io = std::make_unique<MockBasicIo>();

    EXPECT_CALL(*io, path()).WillOnce(Return("test.eps"));



    EpsImage image(std::move(io), false);

    image.xmpPacket_.clear();

    image.readMetadata();

}



TEST_F(EpsImageTest_1753, ReadMetadataXmpDecodeFail_1753) {

    auto io = std::make_unique<MockBasicIo>();

    EXPECT_CALL(*io, path()).WillOnce(Return("test.eps"));



    EpsImage image(std::move(io), false);

    image.xmpPacket_ = "invalid_xmp_packet";

    EXPECT_THROW(image.readMetadata(), Error);

}



TEST_F(EpsImageTest_1753, ReadMetadataXmpDecodeSuccess_1753) {

    auto io = std::make_unique<MockBasicIo>();

    EXPECT_CALL(*io, path()).WillOnce(Return("test.eps"));



    EpsImage image(std::move(io), false);

    image.xmpPacket_ = "valid_xmp_packet";

    EXPECT_CALL(XmpParser::decode(_, _)).WillOnce(Return(1));

    image.readMetadata();

}



TEST_F(EpsImageTest_1753, ReadMetadataExceptionHandling_1753) {

    auto io = std::make_unique<MockBasicIo>();

    EXPECT_CALL(*io, path()).WillOnce(Return("test.eps"));



    EpsImage image(std::move(io), false);

    image.xmpPacket_ = "invalid_xmp_packet";

    EXPECT_THROW(image.readMetadata(), Error);

}



TEST_F(EpsImageTest_1753, SetCommentNormalOperation_1753) {

    auto io = std::make_unique<MockBasicIo>();

    EpsImage image(std::move(io), false);

    image.setComment("test comment");

}



TEST_F(EpsImageTest_1753, MimeTypeNormalOperation_1753) {

    auto io = std::make_unique<MockBasicIo>();

    EpsImage image(std::move(io), false);

    EXPECT_EQ(image.mimeType(), "image/eps");

}
