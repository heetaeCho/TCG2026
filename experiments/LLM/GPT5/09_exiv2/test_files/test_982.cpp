// TEST_ID 982
// Unit tests for Exiv2::MrwImage::writeMetadata()
// File under test: ./TestProjects/exiv2/src/mrwimage.cpp

#include <gtest/gtest.h>

#include <string>

#include "exiv2/error.hpp"
#include "exiv2/mrwimage.hpp"

namespace {

class MrwImageTest_982 : public ::testing::Test {};

TEST_F(MrwImageTest_982, WriteMetadataThrowsError_982) {
  // Construct MrwImage via its public constructor. We avoid assuming any
  // BasicIo concrete type is required by using a null unique_ptr; the function
  // under test (writeMetadata) is expected to throw independent of IO state.
  Exiv2::MrwImage image(Exiv2::BasicIo::UniquePtr{}, /*create=*/false);

  // Observable behavior from the provided implementation: always throws Exiv2::Error.
  EXPECT_THROW(image.writeMetadata(), Exiv2::Error);
}

TEST_F(MrwImageTest_982, WriteMetadataThrowsWithUnsupportedFormatCode_982) {
  Exiv2::MrwImage image(Exiv2::BasicIo::UniquePtr{}, /*create=*/false);

  try {
    image.writeMetadata();
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Exiv2::Error& e) {
    // Verify observable error code (part of the public Error interface in Exiv2).
    EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerWritingImageFormatUnsupported);
  } catch (...) {
    FAIL() << "Expected Exiv2::Error, but caught a different exception type";
  }
}

TEST_F(MrwImageTest_982, WriteMetadataThrowsAndMentionsMRW_982) {
  Exiv2::MrwImage image(Exiv2::BasicIo::UniquePtr{}, /*create=*/false);

  try {
    image.writeMetadata();
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Exiv2::Error& e) {
    // The implementation passes "MRW" as the message argument; verify the message
    // contains it via the public what() string (observable).
    const std::string msg = e.what();
    EXPECT_NE(msg.find("MRW"), std::string::npos);
  } catch (...) {
    FAIL() << "Expected Exiv2::Error, but caught a different exception type";
  }
}

TEST_F(MrwImageTest_982, WriteMetadataThrowsConsistentlyOnRepeatedCalls_982) {
  Exiv2::MrwImage image(Exiv2::BasicIo::UniquePtr{}, /*create=*/false);

  EXPECT_THROW(image.writeMetadata(), Exiv2::Error);
  EXPECT_THROW(image.writeMetadata(), Exiv2::Error);
}

TEST_F(MrwImageTest_982, WriteMetadataThrowsRegardlessOfCreateFlag_982) {
  Exiv2::MrwImage image_create_true(Exiv2::BasicIo::UniquePtr{}, /*create=*/true);
  Exiv2::MrwImage image_create_false(Exiv2::BasicIo::UniquePtr{}, /*create=*/false);

  EXPECT_THROW(image_create_true.writeMetadata(), Exiv2::Error);
  EXPECT_THROW(image_create_false.writeMetadata(), Exiv2::Error);
}

}  // namespace