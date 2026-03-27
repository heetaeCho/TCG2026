// =================================================================================================
// TEST_ID: 1162
// Unit tests for Exiv2::Internal::FindExifdatum (tiffimage_int.*)
// =================================================================================================

#include <gtest/gtest.h>

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include "tiffimage_int.hpp"

#include <exiv2/exif.hpp>
#include <exiv2/exifkey.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

namespace {

class FindExifdatumTest_1162 : public ::testing::Test {
 protected:
  static Exiv2::Exifdatum MakeExifdatum(const std::string& exifKeyString) {
    Exiv2::ExifKey key(exifKeyString);

    // Provide a real Value instance (keep it alive until Exifdatum is constructed).
    // We do not assume anything about how FindExifdatum uses the value; this is just
    // to satisfy Exifdatum's constructor contract.
    Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedShort);
    ASSERT_NE(v.get(), nullptr);
    (void)v->read("1");  // If it fails, Exiv2 will handle it internally; test remains black-box.

    return Exiv2::Exifdatum(key, v.get());
  }
};

TEST_F(FindExifdatumTest_1162, ReturnsTrueWhenIfdIdMatches_1162) {
  const Exiv2::Exifdatum md = MakeExifdatum("Exif.Image.Make");  // commonly in IFD0
  const Exiv2::IfdId mdIfd = md.ifdId();

  const Exiv2::Internal::FindExifdatum pred(mdIfd);
  EXPECT_TRUE(pred(md));
}

TEST_F(FindExifdatumTest_1162, ReturnsFalseWhenIfdIdDoesNotMatch_1162) {
  const Exiv2::Exifdatum md = MakeExifdatum("Exif.Image.Make");
  const Exiv2::IfdId mdIfd = md.ifdId();

  // Pick a different IfdId than the one reported by the metadata.
  const Exiv2::IfdId differentIfd =
      (mdIfd == Exiv2::ifd0Id) ? Exiv2::exifIfdId : Exiv2::ifd0Id;

  const Exiv2::Internal::FindExifdatum pred(differentIfd);
  EXPECT_FALSE(pred(md));
}

TEST_F(FindExifdatumTest_1162, CallableOnConstPredicateAndConstExifdatum_1162) {
  const Exiv2::Exifdatum md = MakeExifdatum("Exif.Photo.ExposureTime");  // commonly in Exif IFD
  const Exiv2::IfdId mdIfd = md.ifdId();

  const Exiv2::Internal::FindExifdatum pred(mdIfd);
  const Exiv2::Internal::FindExifdatum& constPred = pred;

  EXPECT_TRUE(constPred(md));
}

TEST_F(FindExifdatumTest_1162, WorksWithStdFindIf_FindsMatchingElement_1162) {
  // Create a small set of Exifdatum objects from different key families.
  std::vector<Exiv2::Exifdatum> items;
  items.push_back(MakeExifdatum("Exif.Image.Make"));
  items.push_back(MakeExifdatum("Exif.Photo.ExposureTime"));
  items.push_back(MakeExifdatum("Exif.GPSInfo.GPSLatitude"));

  // Choose a target IfdId from one element (black-box: use what Exiv2 reports).
  const Exiv2::IfdId targetIfd = items[1].ifdId();
  const Exiv2::Internal::FindExifdatum pred(targetIfd);

  auto it = std::find_if(items.begin(), items.end(), pred);
  ASSERT_NE(it, items.end());
  EXPECT_EQ(it->ifdId(), targetIfd);
}

TEST_F(FindExifdatumTest_1162, WorksWithStdFindIf_EmptyRangeReturnsEnd_1162) {
  std::vector<Exiv2::Exifdatum> items;

  const Exiv2::Internal::FindExifdatum pred(Exiv2::ifd0Id);
  auto it = std::find_if(items.begin(), items.end(), pred);
  EXPECT_EQ(it, items.end());
}

TEST_F(FindExifdatumTest_1162, CopyOfPredicateBehavesConsistently_1162) {
  const Exiv2::Exifdatum md = MakeExifdatum("Exif.GPSInfo.GPSLatitude");
  const Exiv2::IfdId mdIfd = md.ifdId();

  const Exiv2::Internal::FindExifdatum pred(mdIfd);
  const Exiv2::Internal::FindExifdatum predCopy = pred;

  EXPECT_TRUE(pred(md));
  EXPECT_TRUE(predCopy(md));

  const Exiv2::IfdId differentIfd =
      (mdIfd == Exiv2::gpsIfdId) ? Exiv2::ifd0Id : Exiv2::gpsIfdId;
  const Exiv2::Internal::FindExifdatum other(differentIfd);

  EXPECT_NE(pred(md), other(md));
  EXPECT_NE(predCopy(md), other(md));
}

}  // namespace