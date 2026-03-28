// =================================================================================================
// TEST_ID: 1105
// Unit tests for Exiv2::ImageFactory::createIo (black-box, interface-driven)
// File: ./TestProjects/exiv2/src/image.cpp (partial implementation provided)
// =================================================================================================

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/image.hpp>

#include <memory>
#include <string>

namespace {

class ImageFactoryCreateIoTest_1105 : public ::testing::Test {
 protected:
  static Exiv2::BasicIo::UniquePtr Create(const std::string& path, bool useCurl) {
    // Works whether createIo is static or non-static (calling static via instance is OK in C++).
    Exiv2::ImageFactory factory;
    return factory.createIo(path, useCurl);
  }

  template <typename T>
  static bool IsType(const Exiv2::BasicIo::UniquePtr& io) {
    return dynamic_cast<T*>(io.get()) != nullptr;
  }
};

TEST_F(ImageFactoryCreateIoTest_1105, FilePathReturnsNonNullIo_1105) {
#ifdef EXV_ENABLE_FILESYSTEM
  auto io = Create("test.jpg", /*useCurl=*/false);
  ASSERT_NE(io.get(), nullptr);
  EXPECT_TRUE(IsType<Exiv2::FileIo>(io));
#else
  EXPECT_THROW((void)Create("test.jpg", /*useCurl=*/false), Exiv2::Error);
#endif
}

TEST_F(ImageFactoryCreateIoTest_1105, EmptyPathBehavesLikeFilePath_1105) {
#ifdef EXV_ENABLE_FILESYSTEM
  auto io = Create("", /*useCurl=*/false);
  ASSERT_NE(io.get(), nullptr);
  // The implementation falls back to FileIo(path) when filesystem is enabled.
  EXPECT_TRUE(IsType<Exiv2::FileIo>(io));
#else
  EXPECT_THROW((void)Create("", /*useCurl=*/false), Exiv2::Error);
#endif
}

TEST_F(ImageFactoryCreateIoTest_1105, FileUriReturnsFileIoWhenFilesystemEnabled_1105) {
#ifdef EXV_ENABLE_FILESYSTEM
  // "file://" should be recognized as pFileUri by Exiv2::fileProtocol.
  auto io = Create("file:///tmp/test.jpg", /*useCurl=*/false);
  ASSERT_NE(io.get(), nullptr);
  EXPECT_TRUE(IsType<Exiv2::FileIo>(io));
#else
  EXPECT_THROW((void)Create("file:///tmp/test.jpg", /*useCurl=*/false), Exiv2::Error);
#endif
}

TEST_F(ImageFactoryCreateIoTest_1105, DataUriReturnsXPathIoWhenFilesystemEnabled_1105) {
#ifdef EXV_ENABLE_FILESYSTEM
  // "data:" should be recognized as pDataUri by Exiv2::fileProtocol.
  auto io = Create("data:image/jpeg;base64,AA==", /*useCurl=*/false);
  ASSERT_NE(io.get(), nullptr);
  EXPECT_TRUE(IsType<Exiv2::XPathIo>(io));
#else
  EXPECT_THROW((void)Create("data:image/jpeg;base64,AA==", /*useCurl=*/false), Exiv2::Error);
#endif
}

TEST_F(ImageFactoryCreateIoTest_1105, StdinReturnsXPathIoWhenFilesystemEnabled_1105) {
#ifdef EXV_ENABLE_FILESYSTEM
  // Common Exiv2 convention is "-" for stdin (fileProtocol may map it to pStdin).
  auto io = Create("-", /*useCurl=*/false);
  ASSERT_NE(io.get(), nullptr);
  EXPECT_TRUE(IsType<Exiv2::XPathIo>(io));
#else
  EXPECT_THROW((void)Create("-", /*useCurl=*/false), Exiv2::Error);
#endif
}

TEST_F(ImageFactoryCreateIoTest_1105, FilesystemDisabledThrowsKerFileAccessDisabled_1105) {
#ifndef EXV_ENABLE_FILESYSTEM
  try {
    (void)Create("test.jpg", /*useCurl=*/false);
    FAIL() << "Expected Exiv2::Error to be thrown when EXV_ENABLE_FILESYSTEM is not defined.";
  } catch (const Exiv2::Error& e) {
    // Observable error case explicitly present in the implementation.
    EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerFileAccessDisabled);
  }
#else
  GTEST_SKIP() << "EXV_ENABLE_FILESYSTEM is enabled in this build.";
#endif
}

TEST_F(ImageFactoryCreateIoTest_1105, HttpReturnsHttpIoWhenWebReadyEnabledAndNotUsingCurl_1105) {
#if defined(EXV_ENABLE_FILESYSTEM) && defined(EXV_ENABLE_WEBREADY)
  auto io = Create("http://example.com/test.jpg", /*useCurl=*/false);
  ASSERT_NE(io.get(), nullptr);
  EXPECT_TRUE(IsType<Exiv2::HttpIo>(io));
#else
  GTEST_SKIP() << "Requires EXV_ENABLE_FILESYSTEM and EXV_ENABLE_WEBREADY.";
#endif
}

TEST_F(ImageFactoryCreateIoTest_1105, HttpReturnsCurlIoWhenCurlEnabledAndUseCurlTrue_1105) {
#if defined(EXV_ENABLE_FILESYSTEM) && defined(EXV_USE_CURL)
  auto io = Create("http://example.com/test.jpg", /*useCurl=*/true);
  ASSERT_NE(io.get(), nullptr);
  EXPECT_TRUE(IsType<Exiv2::CurlIo>(io));
#else
  GTEST_SKIP() << "Requires EXV_ENABLE_FILESYSTEM and EXV_USE_CURL.";
#endif
}

TEST_F(ImageFactoryCreateIoTest_1105, HttpsReturnsCurlIoWhenCurlEnabledAndUseCurlTrue_1105) {
#if defined(EXV_ENABLE_FILESYSTEM) && defined(EXV_USE_CURL)
  auto io = Create("https://example.com/test.jpg", /*useCurl=*/true);
  ASSERT_NE(io.get(), nullptr);
  EXPECT_TRUE(IsType<Exiv2::CurlIo>(io));
#else
  GTEST_SKIP() << "Requires EXV_ENABLE_FILESYSTEM and EXV_USE_CURL.";
#endif
}

TEST_F(ImageFactoryCreateIoTest_1105, FtpReturnsCurlIoWhenCurlEnabledAndUseCurlTrue_1105) {
#if defined(EXV_ENABLE_FILESYSTEM) && defined(EXV_USE_CURL)
  auto io = Create("ftp://example.com/test.jpg", /*useCurl=*/true);
  ASSERT_NE(io.get(), nullptr);
  EXPECT_TRUE(IsType<Exiv2::CurlIo>(io));
#else
  GTEST_SKIP() << "Requires EXV_ENABLE_FILESYSTEM and EXV_USE_CURL.";
#endif
}

TEST_F(ImageFactoryCreateIoTest_1105, HttpsFallsBackToFileIoWhenNotUsingCurl_1105) {
#ifdef EXV_ENABLE_FILESYSTEM
  // Based on the provided implementation: only pHttp is handled by HttpIo (webready),
  // while pHttps is only routed to CurlIo when EXV_USE_CURL && useCurl==true.
  // Otherwise it falls through to FileIo(path).
  auto io = Create("https://example.com/test.jpg", /*useCurl=*/false);
  ASSERT_NE(io.get(), nullptr);
  EXPECT_TRUE(IsType<Exiv2::FileIo>(io));
#else
  EXPECT_THROW((void)Create("https://example.com/test.jpg", /*useCurl=*/false), Exiv2::Error);
#endif
}

TEST_F(ImageFactoryCreateIoTest_1105, FtpFallsBackToFileIoWhenNotUsingCurl_1105) {
#ifdef EXV_ENABLE_FILESYSTEM
  auto io = Create("ftp://example.com/test.jpg", /*useCurl=*/false);
  ASSERT_NE(io.get(), nullptr);
  EXPECT_TRUE(IsType<Exiv2::FileIo>(io));
#else
  EXPECT_THROW((void)Create("ftp://example.com/test.jpg", /*useCurl=*/false), Exiv2::Error);
#endif
}

}  // namespace