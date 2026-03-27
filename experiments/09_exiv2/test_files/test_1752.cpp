#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/epsimage.hpp"

#include <memory>



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(void, read, (char*, size_t), (override));

    MOCK_METHOD(void, write, (const char*, size_t), (override));

    MOCK_METHOD(size_t, tellg, (), (const, override));

    MOCK_METHOD(void, seekg, (size_t pos), (override));

};



class EpsImageTest_1752 : public ::testing::Test {

protected:

    std::unique_ptr<MockBasicIo> mock_io;

    std::unique_ptr<EpsImage> eps_image;



    void SetUp() override {

        mock_io = std::make_unique<MockBasicIo>();

        eps_image = std::make_unique<EpsImage>(std::move(mock_io), false);

    }

};



TEST_F(EpsImageTest_1752, MimeType_ReturnsCorrectType_1752) {

    EXPECT_EQ(eps_image->mimeType(), "application/postscript");

}



TEST_F(EpsImageTest_1752, SetComment_DoesNotThrow_1752) {

    EXPECT_NO_THROW(eps_image->setComment("Sample Comment"));

}



TEST_F(EpsImageTest_1752, ReadMetadata_DoesNotThrow_1752) {

    EXPECT_NO_THROW(eps_image->readMetadata());

}



TEST_F(EpsImageTest_1752, WriteMetadata_DoesNotThrow_1752) {

    EXPECT_NO_THROW(eps_image->writeMetadata());

}
