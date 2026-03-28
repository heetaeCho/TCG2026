// =================================================================================================
//  TEST_ID: 1040
//  File: test_bmpimage_writeMetadata_1040.cpp
//
//  Unit tests for Exiv2::BmpImage::writeMetadata()
//  Constraints honored:
//   - Treat implementation as a black box
//   - Assert only observable behavior (exception type/message/code)
//   - No private/internal state access
// =================================================================================================

#include <gtest/gtest.h>

#include <memory>
#include <string>

// Exiv2 headers
#include "exiv2/bmpimage.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"

namespace {

class BmpImageWriteMetadataTest_1040 : public ::testing::Test {
 protected:
  static std::unique_ptr<Exiv2::BmpImage> makeBmpImageWithMemIo() {
    // Use a memory-backed IO; content should be irrelevant for writeMetadata() error behavior.
    auto io = std::make_unique<Exiv2::MemIo>();
    return std::make_unique<Exiv2::BmpImage>(std::move(io));
  }
};

TEST_F(BmpImageWriteMetadataTest_1040, WriteMetadataThrowsError_1040) {
  auto img = makeBmpImageWithMemIo();
  EXPECT_THROW(img->writeMetadata(), Exiv2::Error);
}

TEST_F(BmpImageWriteMetadataTest_1040, WriteMetadataThrowsUnsupportedFormatErrorCode_1040) {
  auto img = makeBmpImageWithMemIo();

  try {
    img->writeMetadata();
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Exiv2::Error& e) {
    // Observable behavior via the Error interface
    EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerWritingImageFormatUnsupported);
  } catch (...) {
    FAIL() << "Expected Exiv2::Error, but caught a different exception type";
  }
}

TEST_F(BmpImageWriteMetadataTest_1040, WriteMetadataErrorMessageMentionsBmp_1040) {
  auto img = makeBmpImageWithMemIo();

  try {
    img->writeMetadata();
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Exiv2::Error& e) {
    // The partial implementation constructs Error(..., "BMP").
    // We don't assume exact formatting, only that BMP is mentioned.
    const std::string msg = e.what();
    EXPECT_NE(msg.find("BMP"), std::string::npos) << "Error message should mention BMP; got: " << msg;
  }
}

TEST_F(BmpImageWriteMetadataTest_1040, WriteMetadataAlwaysThrowsAcrossMultipleCalls_1040) {
  auto img = makeBmpImageWithMemIo();

  EXPECT_THROW(img->writeMetadata(), Exiv2::Error);
  EXPECT_THROW(img->writeMetadata(), Exiv2::Error);
}

TEST_F(BmpImageWriteMetadataTest_1040, WriteMetadataThrowsEvenWithEmptyIo_1040) {
  // Boundary-ish: empty MemIo buffer (default)
  auto img = makeBmpImageWithMemIo();
  EXPECT_THROW(img->writeMetadata(), Exiv2::Error);
}

}  // namespace