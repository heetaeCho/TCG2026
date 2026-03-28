// ***************************************************************** -*- C++ -*-
// Unit tests for Exiv2::OrfImage (orfimage.cpp)
// TEST_ID: 1547
// *****************************************************************

#include <gtest/gtest.h>

#include <exiv2/orfimage.hpp>
#include <exiv2/basicio.hpp>

#include <memory>
#include <string>

namespace {

class OrfImageTest_1547 : public ::testing::Test {
 protected:
  static std::unique_ptr<Exiv2::OrfImage> makeOrfImage() {
    // Construct with an in-memory IO. This is an external dependency provided by Exiv2.
    Exiv2::BasicIo::UniquePtr io(new Exiv2::MemIo);
    return std::make_unique<Exiv2::OrfImage>(std::move(io), /*create=*/false);
  }
};

TEST_F(OrfImageTest_1547, MimeType_ReturnsOlympusOrf_1547) {
  auto img = makeOrfImage();

  const std::string mt = img->mimeType();
  EXPECT_EQ("image/x-olympus-orf", mt);
  EXPECT_FALSE(mt.empty());
}

TEST_F(OrfImageTest_1547, MimeType_ConstAndNonConstAgree_1547) {
  auto img = makeOrfImage();

  const std::string mt_nonconst = img->mimeType();

  const Exiv2::OrfImage& cref = *img;
  const std::string mt_const = cref.mimeType();

  EXPECT_EQ(mt_nonconst, mt_const);
  EXPECT_EQ("image/x-olympus-orf", mt_const);
}

TEST_F(OrfImageTest_1547, MimeType_IsStableAcrossRepeatedCalls_1547) {
  auto img = makeOrfImage();

  const std::string first = img->mimeType();
  const std::string second = img->mimeType();
  const std::string third = img->mimeType();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
  EXPECT_EQ("image/x-olympus-orf", first);
}

}  // namespace