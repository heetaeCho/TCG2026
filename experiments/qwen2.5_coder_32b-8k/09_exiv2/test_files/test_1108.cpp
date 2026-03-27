#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/image.hpp"

#include "exiv2/basicio.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2;

using ::testing::Return;

using ::testing::_;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(const std::string &, path, (), (const, override));

};



class ImageFactoryTest_1108 : public ::testing::Test {

protected:

    void SetUp() override {

        mockIo = std::make_unique<MockBasicIo>();

    }



    std::unique_ptr<MockBasicIo> mockIo;

};



TEST_F(ImageFactoryTest_1108, OpenSucceedsWhenFileTypeIsRecognized_1108) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, path()).WillRepeatedly(Return("test.jpg"));



    Image::UniquePtr image = ImageFactory().open(std::move(mockIo));



    ASSERT_NE(image, nullptr);

}



TEST_F(ImageFactoryTest_1108, OpenFailsWhenFileTypeIsNotRecognized_1108) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, path()).WillRepeatedly(Return("test.unknown"));



    try {

        Image::UniquePtr image = ImageFactory().open(std::move(mockIo));

        FAIL() << "Expected exception not thrown";

    } catch (const Error& e) {

        EXPECT_EQ(e.code(), ErrorCode::kerFileContainsUnknownImageType);

    }

}



TEST_F(ImageFactoryTest_1108, OpenThrowsExceptionWhenIoOpenFails_1108) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(1));

    EXPECT_CALL(*mockIo, path()).WillRepeatedly(Return("test.jpg"));



    try {

        Image::UniquePtr image = ImageFactory().open(std::move(mockIo));

        FAIL() << "Expected exception not thrown";

    } catch (const Error& e) {

        EXPECT_EQ(e.code(), ErrorCode::kerDataSourceOpenFailed);

    }

}



TEST_F(ImageFactoryTest_1108, OpenReturnsNullptrWhenNoIOProvided_1108) {

    Image::UniquePtr image = ImageFactory().open(nullptr);



    EXPECT_EQ(image, nullptr);

}
