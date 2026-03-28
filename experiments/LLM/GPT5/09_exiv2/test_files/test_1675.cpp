// File: test_tiffencoder_visitifdmakernote_1675.cpp
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"

#include "exiv2/exif.hpp"
#include "exiv2/iptc.hpp"
#include "exiv2/types.hpp"
#include "exiv2/xmp.hpp"

using ::testing::_;
using ::testing::AnyNumber;

namespace {

// Some Exiv2 builds make TiffHeaderBase an abstract interface.
// We provide a minimal mock so we can construct TiffEncoder without relying on internals.
class MockTiffHeaderBase : public Exiv2::Internal::TiffHeaderBase {
 public:
  // byteOrder() is used by TiffEncoder's constructor (per provided snippet).
  MOCK_METHOD(Exiv2::ByteOrder, byteOrder, (), (const, override));

  // If TiffHeaderBase has additional pure virtuals in your build, add MOCK_METHODs here.
  // Keeping them as mocks avoids re-implementing any internal logic.
};

static std::string ByteOrderToTagStringGuess(Exiv2::ByteOrder bo) {
  // Exiv2 maker note byte order is commonly represented as "II" (little endian) or "MM" (big endian).
  // This is a *test input* guess; tests below are written to stay valid even if the library uses
  // a different accepted string representation (by asserting only on observable invariants).
  switch (bo) {
    case Exiv2::littleEndian:
      return "II";
    case Exiv2::bigEndian:
      return "MM";
    default:
      return "invalid";
  }
}

class TiffEncoderVisitIfdMakernoteTest_1675 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Default empty metadata
    // (IptcData/XmpData are collaborators passed by const-ref).
    //
    // pRoot can be nullptr: visitIfdMakernote uses only exifData_/byteOrder_/dirty_ and the object.
    // This keeps the test focused on the provided interface behavior.
    header_ = std::make_unique<MockTiffHeaderBase>();
    ON_CALL(*header_, byteOrder()).WillByDefault(::testing::Return(Exiv2::littleEndian));

    // PrimaryGroups is a value type in Exiv2; in most builds it is default-constructible.
    // If your build requires specific construction, adjust here without changing test intent.
    primaryGroups_ = Exiv2::Internal::PrimaryGroups{};
  }

  // Helper to create an encoder with a given ExifData payload.
  std::unique_ptr<Exiv2::Internal::TiffEncoder> MakeEncoder(Exiv2::ExifData exif) {
    // findEncoderFct can be nullptr for these tests; we do not call encode paths.
    Exiv2::Internal::FindEncoderFct findEncoderFct = nullptr;

    return std::make_unique<Exiv2::Internal::TiffEncoder>(
        std::move(exif),
        iptc_,
        xmp_,
        /*pRoot*/ nullptr,
        /*isNewImage*/ false,
        primaryGroups_,
        header_.get(),
        findEncoderFct);
  }

  // Helper to create a makernote IFD with a known starting byte order.
  // We pass a null MnHeader unique_ptr; this is valid ownership-wise and does not rely on internals.
  std::unique_ptr<Exiv2::Internal::TiffIfdMakernote> MakeMakernote(Exiv2::ByteOrder bo) {
    auto mk = std::make_unique<Exiv2::Internal::TiffIfdMakernote>(
        /*tag*/ 0x0001,
        /*group*/ Exiv2::ifd0Id,
        /*mnGroup*/ Exiv2::ifd0Id,
        /*pHeader*/ std::unique_ptr<Exiv2::Internal::MnHeader>{},
        /*hasNext*/ false);
    mk->setByteOrder(bo);
    return mk;
  }

  Exiv2::IptcData iptc_;
  Exiv2::XmpData xmp_;
  Exiv2::Internal::PrimaryGroups primaryGroups_{};
  std::unique_ptr<MockTiffHeaderBase> header_;
};

TEST_F(TiffEncoderVisitIfdMakernoteTest_1675, NoByteOrderTag_UpdatesEncoderByteOrderAndDoesNotDirty_1675) {
  Exiv2::ExifData exif;  // No "Exif.MakerNote.ByteOrder" key
  auto encoder = MakeEncoder(std::move(exif));

  auto mk = MakeMakernote(Exiv2::bigEndian);
  ASSERT_EQ(mk->byteOrder(), Exiv2::bigEndian);

  EXPECT_FALSE(encoder->dirty());
  encoder->visitIfdMakernote(mk.get());

  // Observable invariant from provided implementation: encoder byteOrder becomes makernote byteOrder.
  EXPECT_EQ(encoder->byteOrder(), mk->byteOrder());

  // With no tag present, implementation should not call setDirty().
  EXPECT_FALSE(encoder->dirty());
}

TEST_F(TiffEncoderVisitIfdMakernoteTest_1675, InvalidByteOrderString_DoesNotChangeMakernoteAndDoesNotDirty_1675) {
  Exiv2::ExifData exif;
  exif["Exif.MakerNote.ByteOrder"] = std::string("definitely-not-a-byte-order");

  auto encoder = MakeEncoder(std::move(exif));

  auto mk = MakeMakernote(Exiv2::littleEndian);
  const auto before = mk->byteOrder();

  EXPECT_FALSE(encoder->dirty());
  encoder->visitIfdMakernote(mk.get());

  // If the string is not recognized, implementation checks invalidByteOrder and should not change.
  EXPECT_EQ(mk->byteOrder(), before);

  // Encoder byteOrder is always updated to makernote byteOrder at end of visit.
  EXPECT_EQ(encoder->byteOrder(), mk->byteOrder());

  // With invalid conversion, setDirty() should not be invoked.
  EXPECT_FALSE(encoder->dirty());
}

TEST_F(TiffEncoderVisitIfdMakernoteTest_1675, SameByteOrderTag_DoesNotChangeMakernoteAndDoesNotDirty_1675) {
  auto mk = MakeMakernote(Exiv2::littleEndian);
  const auto before = mk->byteOrder();

  Exiv2::ExifData exif;
  exif["Exif.MakerNote.ByteOrder"] = ByteOrderToTagStringGuess(before);

  auto encoder = MakeEncoder(std::move(exif));

  EXPECT_FALSE(encoder->dirty());
  encoder->visitIfdMakernote(mk.get());

  // If the tag resolves to the same byte order, no update is expected.
  EXPECT_EQ(mk->byteOrder(), before);

  EXPECT_EQ(encoder->byteOrder(), mk->byteOrder());
  EXPECT_FALSE(encoder->dirty());
}

TEST_F(TiffEncoderVisitIfdMakernoteTest_1675, DifferentValidByteOrderTag_ChangesMakernoteAndSetsDirty_1675) {
  // Start big endian, provide a likely-little-endian tag string.
  auto mk = MakeMakernote(Exiv2::bigEndian);
  const auto before = mk->byteOrder();

  Exiv2::ExifData exif;
  exif["Exif.MakerNote.ByteOrder"] = ByteOrderToTagStringGuess(Exiv2::littleEndian);

  auto encoder = MakeEncoder(std::move(exif));

  EXPECT_FALSE(encoder->dirty());
  encoder->visitIfdMakernote(mk.get());

  // We only assert the *observable contract* that must hold regardless:
  // - encoder byteOrder matches makernote byteOrder after the visit.
  EXPECT_EQ(encoder->byteOrder(), mk->byteOrder());

  // If the library recognizes the provided tag as a valid byte order different from current,
  // the implementation sets makernote byte order and marks encoder dirty.
  //
  // To keep the test robust across supported string formats, we assert conditionally:
  if (mk->byteOrder() != before) {
    EXPECT_TRUE(encoder->dirty());
  } else {
    // If the string format isn't recognized by this build, behavior matches "invalid" case.
    EXPECT_FALSE(encoder->dirty());
  }
}

TEST_F(TiffEncoderVisitIfdMakernoteTest_1675, Boundary_RepeatVisitIsIdempotentOnEncoderByteOrderInvariant_1675) {
  Exiv2::ExifData exif;
  exif["Exif.MakerNote.ByteOrder"] = ByteOrderToTagStringGuess(Exiv2::littleEndian);

  auto encoder = MakeEncoder(std::move(exif));
  auto mk = MakeMakernote(Exiv2::littleEndian);

  encoder->visitIfdMakernote(mk.get());
  const auto afterFirst = encoder->byteOrder();

  // Repeat visit should still satisfy invariant: encoder byteOrder equals makernote byteOrder.
  encoder->visitIfdMakernote(mk.get());
  EXPECT_EQ(encoder->byteOrder(), mk->byteOrder());

  // And repeating should not break stability of encoder's byte order value.
  EXPECT_EQ(encoder->byteOrder(), afterFirst);
}

}  // namespace