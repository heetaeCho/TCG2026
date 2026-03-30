#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/tgaimage.hpp"

#include "exiv2/basicio.hpp"



using namespace Exiv2;

using ::testing::Return;

using ::testing::Throw;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));

    MOCK_METHOD(const std::string&, path, (), (const override));

    MOCK_METHOD(int, error, (), (const override));

    MOCK_METHOD(bool, eof, (), (const override));

};



class TgaImageTest : public ::testing::Test {

protected:

    void SetUp() override {

        io = std::make_unique<MockBasicIo>();

        image = std::make_unique<TgaImage>(std::move(io));

    }



    std::unique_ptr<MockBasicIo> io;

    std::unique_ptr<TgaImage> image;

};



TEST_F(TgaImageTest_1231, ReadMetadata_SuccessfulRead_1231) {

    byte header[18] = {0}; // Initialize a valid TGA header

    EXPECT_CALL(*io, open()).WillOnce(Return(0));

    EXPECT_CALL(*io, read(header, 18)).WillOnce(Return(18));

    EXPECT_NO_THROW(image->readMetadata());

}



TEST_F(TgaImageTest_1231, ReadMetadata_FileOpenFailure_1231) {

    EXPECT_CALL(*io, open()).WillOnce(Return(-1));

    EXPECT_CALL(*io, path()).WillOnce(Return("test.tga"));

    EXPECT_THROW(image->readMetadata(), Error);

}



TEST_F(TgaImageTest_1231, ReadMetadata_NotTgaFile_1231) {

    byte header[18] = {0}; // Invalid TGA header

    EXPECT_CALL(*io, open()).WillOnce(Return(0));

    EXPECT_CALL(*io, read(header, 18)).WillOnce(Return(18));

    EXPECT_THROW(image->readMetadata(), Error);

}



TEST_F(TgaImageTest_1231, ReadMetadata_ReadFailure_1231) {

    byte header[18] = {0}; // Initialize a valid TGA header

    EXPECT_CALL(*io, open()).WillOnce(Return(0));

    EXPECT_CALL(*io, read(header, 18)).WillOnce(Return(0)); // Simulate partial read failure

    EXPECT_THROW(image->readMetadata(), Error);

}



TEST_F(TgaImageTest_1231, ReadMetadata_EndOfFilePrematurely_1231) {

    byte header[18] = {0}; // Initialize a valid TGA header

    EXPECT_CALL(*io, open()).WillOnce(Return(0));

    EXPECT_CALL(*io, read(header, 18)).WillOnce(Return(9)); // Simulate partial read failure

    EXPECT_THROW(image->readMetadata(), Error);

}



TEST_F(TgaImageTest_1231, ReadMetadata_MetadataClearedOnSuccess_1231) {

    byte header[18] = {0}; // Initialize a valid TGA header

    EXPECT_CALL(*io, open()).WillOnce(Return(0));

    EXPECT_CALL(*io, read(header, 18)).WillOnce(Return(18));

    EXPECT_NO_THROW(image->readMetadata());

}



TEST_F(TgaImageTest_1231, ReadMetadata_MetadataNotClearedOnFailure_1231) {

    byte header[18] = {0}; // Invalid TGA header

    EXPECT_CALL(*io, open()).WillOnce(Return(0));

    EXPECT_CALL(*io, read(header, 18)).WillOnce(Return(18));

    EXPECT_THROW(image->readMetadata(), Error);

}



TEST_F(TgaImageTest_1231, ReadMetadata_ErrorSetOnFailure_1231) {

    byte header[18] = {0}; // Invalid TGA header

    EXPECT_CALL(*io, open()).WillOnce(Return(0));

    EXPECT_CALL(*io, read(header, 18)).WillOnce(Return(18));

    try {

        image->readMetadata();

    } catch (const Error& e) {

        EXPECT_EQ(e.code(), ErrorCode::kerNotAnImage);

    }

}
