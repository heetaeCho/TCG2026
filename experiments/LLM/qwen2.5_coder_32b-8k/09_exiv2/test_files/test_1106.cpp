#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/image.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2;

using testing::_;

using testing::Return;



class ImageFactoryMock : public ImageFactory {

public:

    MOCK_STATIC(std::unique_ptr<BasicIo> createIo(const std::string & path, bool useCurl));

    MOCK_STATIC(Image::UniquePtr open(std::unique_ptr<BasicIo> io));

};



TEST_F(ImageFactoryTest_1106, OpenValidImageFile_ReturnsNonNullPointer_1106) {

    auto mockIo = ImageFactoryMock::createIo("", false);

    EXPECT_CALL(ImageFactoryMock, createIo(_, _)).WillOnce(Return(std::move(mockIo)));

    EXPECT_CALL(ImageFactoryMock, open(_)).WillOnce(Return(Image::UniquePtr(new class Image())));



    Image::UniquePtr image = ImageFactoryMock::open("valid_image.jpg", false);

    EXPECT_NE(image.get(), nullptr);

}



TEST_F(ImageFactoryTest_1106, OpenUnknownImageFile_ThrowsException_1106) {

    auto mockIo = ImageFactoryMock::createIo("", false);

    EXPECT_CALL(ImageFactoryMock, createIo(_, _)).WillOnce(Return(std::move(mockIo)));

    EXPECT_CALL(ImageFactoryMock, open(_)).WillOnce(testing::Throw(Error(ErrorCode::kerFileContainsUnknownImageType, "")));



    EXPECT_THROW({

        Image::UniquePtr image = ImageFactoryMock::open("unknown_image.jpg", false);

    }, Error);

}



TEST_F(ImageFactoryTest_1106, OpenEmptyPathString_ThrowsException_1106) {

    auto mockIo = ImageFactoryMock::createIo("", false);

    EXPECT_CALL(ImageFactoryMock, createIo(_, _)).WillOnce(Return(std::move(mockIo)));

    EXPECT_CALL(ImageFactoryMock, open(_)).WillOnce(testing::Throw(Error(ErrorCode::kerFileContainsUnknownImageType, "")));



    EXPECT_THROW({

        Image::UniquePtr image = ImageFactoryMock::open("", false);

    }, Error);

}



TEST_F(ImageFactoryTest_1106, OpenWithUseCurlTrue_ReturnsNonNullPointer_1106) {

    auto mockIo = ImageFactoryMock::createIo("", true);

    EXPECT_CALL(ImageFactoryMock, createIo(_, _)).WillOnce(Return(std::move(mockIo)));

    EXPECT_CALL(ImageFactoryMock, open(_)).WillOnce(Return(Image::UniquePtr(new class Image())));



    Image::UniquePtr image = ImageFactoryMock::open("valid_image.jpg", true);

    EXPECT_NE(image.get(), nullptr);

}



TEST_F(ImageFactoryTest_1106, OpenNonExistentFile_ReturnsNonNullPointerOrExceptionBasedOnImplementation_1106) {

    auto mockIo = ImageFactoryMock::createIo("", false);

    EXPECT_CALL(ImageFactoryMock, createIo(_, _)).WillOnce(Return(std::move(mockIo)));

    EXPECT_CALL(ImageFactoryMock, open(_)).WillOnce(testing::Throw(Error(ErrorCode::kerFileContainsUnknownImageType, "")));



    try {

        Image::UniquePtr image = ImageFactoryMock::open("non_existent_image.jpg", false);

        EXPECT_NE(image.get(), nullptr);

    } catch (const Error& e) {

        EXPECT_EQ(e.code(), ErrorCode::kerFileContainsUnknownImageType);

    }

}
