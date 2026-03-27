#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/image.hpp"

#include "exiv2/futils.hpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;



class ImageFactoryTest : public ::testing::Test {

protected:

    ImageFactory imageFactory;

};



TEST_F(ImageFactoryTest, CreateIo_FileProtocol_1105) {

    std::string path = "file://example.jpg";

    BasicIo::UniquePtr io = imageFactory.createIo(path, false);

    ASSERT_NE(io, nullptr);

}



#ifdef EXV_USE_CURL

TEST_F(ImageFactoryTest, CreateIo_HttpProtocolWithCurlEnabled_1105) {

    std::string path = "http://example.com/image.jpg";

    BasicIo::UniquePtr io = imageFactory.createIo(path, true);

    ASSERT_NE(io, nullptr);

}



TEST_F(ImageFactoryTest, CreateIo_HttpsProtocolWithCurlEnabled_1105) {

    std::string path = "https://example.com/image.jpg";

    BasicIo::UniquePtr io = imageFactory.createIo(path, true);

    ASSERT_NE(io, nullptr);

}



TEST_F(ImageFactoryTest, CreateIo_FtpProtocolWithCurlEnabled_1105) {

    std::string path = "ftp://example.com/image.jpg";

    BasicIo::UniquePtr io = imageFactory.createIo(path, true);

    ASSERT_NE(io, nullptr);

}

#endif



#ifdef EXV_ENABLE_WEBREADY

TEST_F(ImageFactoryTest, CreateIo_HttpProtocolWithWebReadyEnabled_1105) {

    std::string path = "http://example.com/image.jpg";

    BasicIo::UniquePtr io = imageFactory.createIo(path, false);

    ASSERT_NE(io, nullptr);

}

#endif



#ifdef EXV_ENABLE_FILESYSTEM

TEST_F(ImageFactoryTest, CreateIo_FileUriProtocol_1105) {

    std::string path = "file://example.jpg";

    BasicIo::UniquePtr io = imageFactory.createIo(path, false);

    ASSERT_NE(io, nullptr);

}



TEST_F(ImageFactoryTest, CreateIo_DataUriProtocol_1105) {

    std::string path = "data:image/jpeg;base64,/9j/4AAQSkZJRgABAQAAAQABAAD/";

    BasicIo::UniquePtr io = imageFactory.createIo(path, false);

    ASSERT_NE(io, nullptr);

}



TEST_F(ImageFactoryTest, CreateIo_StdinProtocol_1105) {

    std::string path = "-";

    BasicIo::UniquePtr io = imageFactory.createIo(path, false);

    ASSERT_NE(io, nullptr);

}

#endif



#ifndef EXV_ENABLE_FILESYSTEM

TEST_F(ImageFactoryTest, CreateIo_FileAccessDisabled_1105) {

    std::string path = "file://example.jpg";

    EXPECT_THROW(imageFactory.createIo(path, false), Error);

}

#endif



TEST_F(ImageFactoryTest, CreateIo_EmptyPath_1105) {

    std::string path = "";

    EXPECT_THROW(imageFactory.createIo(path, false), Error);

}



TEST_F(ImageFactoryTest, CreateIo_UnsupportedProtocol_1105) {

    std::string path = "sftp://example.com/image.jpg";

    EXPECT_THROW(imageFactory.createIo(path, false), Error);

}
