// TEST_ID 2200
// File: test_tiffdecoder_ctor_2200.cpp

#include <gtest/gtest.h>

#include "tiffvisitor_int.hpp"     // Exiv2::Internal::TiffDecoder, TiffFinder, TiffVisitor
#include "tiffcomposite_int.hpp"   // Exiv2::Internal::TiffComponent
#include "exiv2/exif.hpp"          // Exiv2::ExifData
#include "exiv2/iptc.hpp"          // Exiv2::IptcData
#include "exiv2/xmp_exiv2.hpp"     // Exiv2::XmpData
#include "exiv2/tags.hpp"          // Exiv2::IfdId

namespace {

// A test double for TiffComponent that lets us observe whether accept() ends up
// calling the virtual doAccept(visitor) (i.e., whether the constructor triggers
// traversal of the TIFF component tree).
class SpyRootComponent : public Exiv2::Internal::TiffComponent {
 public:
  SpyRootComponent()
      : Exiv2::Internal::TiffComponent(/*tag=*/0, Exiv2::IfdId::ifd0Id) {}

  int accept_calls() const { return accept_calls_; }
  bool saw_tiff_finder() const { return saw_tiff_finder_; }

 protected:
  void doAccept(Exiv2::Internal::TiffVisitor& visitor) override {
    ++accept_calls_;
    if (dynamic_cast<Exiv2::Internal::TiffFinder*>(&visitor) != nullptr) {
      saw_tiff_finder_ = true;
    }
    // Intentionally do not attempt to simulate internal traversal or selection.
  }

 private:
  int accept_calls_{0};
  bool saw_tiff_finder_{false};
};

class TiffDecoderCtorTest_2200 : public ::testing::Test {
 protected:
  Exiv2::ExifData exif_;
  Exiv2::IptcData iptc_;
  Exiv2::XmpData xmp_;
};

}  // namespace

TEST_F(TiffDecoderCtorTest_2200, UsesExifMakeWhenPresent_DoesNotTraverseRoot_2200) {
  SpyRootComponent root;

  // Make key present: constructor should read it from ExifData and not use the TIFF tree.
  exif_["Exif.Image.Make"] = std::string("Nikon");

  Exiv2::Internal::TiffDecoder decoder(exif_, iptc_, xmp_, &root,
                                      /*findDecoderFct=*/nullptr);

  EXPECT_EQ(root.accept_calls(), 0);
  EXPECT_FALSE(root.saw_tiff_finder());
}

TEST_F(TiffDecoderCtorTest_2200, WhenExifMakeMissing_TraverseRootWithTiffFinder_2200) {
  SpyRootComponent root;

  // ExifData is empty => constructor should fall back to traversing the TIFF tree.
  Exiv2::Internal::TiffDecoder decoder(exif_, iptc_, xmp_, &root,
                                      /*findDecoderFct=*/nullptr);

  EXPECT_EQ(root.accept_calls(), 1);
  EXPECT_TRUE(root.saw_tiff_finder());
}

TEST_F(TiffDecoderCtorTest_2200, ExifMakePresentButEmptyString_StillDoesNotTraverseRoot_2200) {
  SpyRootComponent root;

  // Boundary case: key exists but value is empty. Observable behavior: still "present",
  // so the traversal fallback should not be used.
  exif_["Exif.Image.Make"] = std::string("");

  Exiv2::Internal::TiffDecoder decoder(exif_, iptc_, xmp_, &root,
                                      /*findDecoderFct=*/nullptr);

  EXPECT_EQ(root.accept_calls(), 0);
  EXPECT_FALSE(root.saw_tiff_finder());
}