#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/image.hpp"

#include "exiv2/basicio.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2;



class MockFileIo : public FileIo {

public:

    MOCK_METHOD(int, open, (const std::string& mode), (override));

    MOCK_METHOD(int, close, (), (override));

};



class ImageFactoryTest_1109 : public ::testing::Test {

protected:

    NiceMock<MockFileIo> mockFileIo;

    std::string testPath = "test_file_path";

    ImageType testImageType = ImageType::jpeg;

};



TEST_F(ImageFactoryTest_1109, CreateValidImage_1109) {

    EXPECT_CALL(mockFileIo, open("w+b")).WillOnce(::testing::Return(0));

    EXPECT_CALL(mockFileIo, close()).WillOnce(::testing::Return(0));



    ImageFactory factory;

    auto image = factory.create(testImageType, testPath);

    ASSERT_NE(image, nullptr);

}



TEST_F(ImageFactoryTest_1109, CreateFailsOnFileOpenFailure_1109) {

    EXPECT_CALL(mockFileIo, open("w+b")).WillOnce(::testing::Return(-1));



    ImageFactory factory;

    EXPECT_THROW(factory.create(testImageType, testPath), Error);

}



TEST_F(ImageFactoryTest_1109, CreateFailsOnUnsupportedImageType_1109) {

    EXPECT_CALL(mockFileIo, open("w+b")).WillOnce(::testing::Return(0));

    EXPECT_CALL(mockFileIo, close()).WillOnce(::testing::Return(0));



    ImageFactory factory;

    EXPECT_THROW(factory.create(static_cast<ImageType>(-1), testPath), Error);

}



TEST_F(ImageFactoryTest_1109, CreateFailsOnOpenCloseFailure_1109) {

    EXPECT_CALL(mockFileIo, open("w+b")).WillOnce(::testing::Return(0));

    EXPECT_CALL(mockFileIo, close()).WillOnce(::testing::Throw(std::runtime_error("close failed")));



    ImageFactory factory;

    EXPECT_THROW(factory.create(testImageType, testPath), std::runtime_error);

}



TEST_F(ImageFactoryTest_1109, CreateFailsOnEmptyFilePath_1109) {

    EXPECT_CALL(mockFileIo, open("w+b")).WillOnce(::testing::Return(0));

    EXPECT_CALL(mockFileIo, close()).WillOnce(::testing::Return(0));



    ImageFactory factory;

    EXPECT_THROW(factory.create(testImageType, ""), Error);

}
