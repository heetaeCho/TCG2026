// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_rw2image_writeMetadata_1580.cpp

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/image.hpp>
#include <exiv2/rw2image.hpp>

#include <cstdint>
#include <memory>
#include <string>

namespace {

// Helper: construct a minimal Rw2Image using an in-memory BasicIo.
static std::unique_ptr<Exiv2::Rw2Image> MakeRw2Image() {
  auto io = std::make_unique<Exiv2::MemIo>();
  return std::make_unique<Exiv2::Rw2Image>(std::move(io));
}

}  // namespace

TEST(Rw2ImageTest_1580, WriteMetadataThrowsExiv2Error_1580) {
  auto img = MakeRw2Image();

  EXPECT_THROW(img->writeMetadata(), Exiv2::Error);
}

TEST(Rw2ImageTest_1580, WriteMetadataErrorCodeIsWritingFormatUnsupported_1580) {
  auto img = MakeRw2Image();

  try {
    img->writeMetadata();
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Exiv2::Error& e) {
    // Verify observable error code (no assumptions beyond public interface).
    // If code() returns an integral type in your build, this still compiles due to comparison rules.
    EXPECT_EQ(Exiv2::ErrorCode::kerWritingImageFormatUnsupported, e.code());
  } catch (...) {
    FAIL() << "Expected Exiv2::Error, but caught a different exception type";
  }
}

TEST(Rw2ImageTest_1580, WriteMetadataErrorMessageMentionsRW2_1580) {
  auto img = MakeRw2Image();

  try {
    img->writeMetadata();
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Exiv2::Error& e) {
    const std::string what = e.what() ? std::string(e.what()) : std::string();
    EXPECT_NE(std::string::npos, what.find("RW2"));
  } catch (...) {
    FAIL() << "Expected Exiv2::Error, but caught a different exception type";
  }
}

TEST(Rw2ImageTest_1580, WriteMetadataThrowsThroughBaseClassVirtualDispatch_1580) {
  auto img = MakeRw2Image();
  Exiv2::Image* base = img.get();

  EXPECT_THROW(base->writeMetadata(), Exiv2::Error);
}

TEST(Rw2ImageTest_1580, WriteMetadataRepeatedCallsConsistentlyThrow_1580) {
  auto img = MakeRw2Image();

  for (int i = 0; i < 3; ++i) {
    try {
      img->writeMetadata();
      FAIL() << "Iteration " << i << ": expected Exiv2::Error to be thrown";
    } catch (const Exiv2::Error& e) {
      EXPECT_EQ(Exiv2::ErrorCode::kerWritingImageFormatUnsupported, e.code())
          << "Iteration " << i << ": unexpected error code";
    } catch (...) {
      FAIL() << "Iteration " << i << ": expected Exiv2::Error, got different exception type";
    }
  }
}