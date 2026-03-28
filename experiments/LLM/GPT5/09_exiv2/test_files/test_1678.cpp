// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID 1678
//
// File: test_tiffencoder_visitbinaryelement_1678.cpp
//
// Unit tests for: Exiv2::Internal::TiffEncoder::visitBinaryElement(TiffBinaryElement*)
// Interface under test (black-box): ensures byteOrder() is restored after visitBinaryElement,
// and that invalid element byte order does not alter encoder byte order.

#include <gtest/gtest.h>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"

#include "exiv2/exif.hpp"
#include "exiv2/iptc.hpp"
#include "exiv2/xmp.hpp"
#include "exiv2/types.hpp"

#include <cstdint>
#include <functional>
#include <memory>
#include <utility>

namespace {

using Exiv2::bigEndian;
using Exiv2::ByteOrder;
using Exiv2::invalidByteOrder;
using Exiv2::littleEndian;

using Exiv2::ExifData;
using Exiv2::IptcData;
using Exiv2::XmpData;

using Exiv2::Internal::FindEncoderFct;
using Exiv2::Internal::PrimaryGroups;
using Exiv2::Internal::TiffBinaryElement;
using Exiv2::Internal::TiffComponent;
using Exiv2::Internal::TiffEncoder;
using Exiv2::Internal::TiffHeaderBase;

// NOTE: We only provide a minimal concrete header for constructing TiffEncoder in tests.
// If your Exiv2 tree already provides a concrete TiffHeaderBase implementation you prefer,
// replace this with that.
class TestTiffHeader final : public TiffHeaderBase {
public:
  explicit TestTiffHeader(ByteOrder bo) : bo_(bo) {}
  ByteOrder byteOrder() const { return bo_; }

private:
  ByteOrder bo_;
};

// Provide a "do-nothing" encoder-finder function object if required by the constructor.
// The exact signature of FindEncoderFct is defined by Exiv2; we only need something
// that can be constructed and passed.
static FindEncoderFct MakeNoopFindEncoderFct() {
  // Many Exiv2 builds define FindEncoderFct as a std::function returning a pointer/functor.
  // If this does not match your tree, adjust this helper accordingly.
  return FindEncoderFct{};
}

static std::unique_ptr<TiffEncoder> MakeEncoder(ByteOrder headerBo) {
  static const IptcData kEmptyIptc;
  static const XmpData kEmptyXmp;

  ExifData exif; // empty
  auto header = std::make_unique<TestTiffHeader>(headerBo);

  // Root pointer can be nullptr for these tests; we don't rely on encoding side-effects.
  TiffComponent* root = nullptr;
  const bool isNewImage = false;

  PrimaryGroups primaryGroups{};
  const TiffHeaderBase* headerPtr = header.get();
  auto findEncoderFct = MakeNoopFindEncoderFct();

  // TiffEncoder stores pHeader_ pointer; ensure header outlives encoder.
  // We keep header alive by capturing it in a custom deleter holder.
  struct Holder {
    std::unique_ptr<TestTiffHeader> header;
    std::unique_ptr<TiffEncoder> encoder;
  };

  auto holder = std::make_shared<Holder>();
  holder->header = std::move(header);
  holder->encoder = std::make_unique<TiffEncoder>(
      std::move(exif), kEmptyIptc, kEmptyXmp, root, isNewImage, std::move(primaryGroups), headerPtr,
      std::move(findEncoderFct));

  // Return encoder while keeping header alive via aliasing shared_ptr.
  return std::unique_ptr<TiffEncoder>(holder, holder->encoder.get());
}

class TiffEncoderVisitBinaryElementTest_1678 : public ::testing::Test {};

} // namespace

TEST_F(TiffEncoderVisitBinaryElementTest_1678, RestoresByteOrderWhenElementOverrides_1678) {
  auto encoder = MakeEncoder(bigEndian);
  ASSERT_NE(encoder, nullptr);
  EXPECT_EQ(encoder->byteOrder(), bigEndian);

  TiffBinaryElement element;
  element.setElByteOrder(littleEndian);

  // Observable behavior: regardless of any internal encoding work, visitBinaryElement must restore
  // the encoder's original byte order after the call.
  ASSERT_NO_THROW(encoder->visitBinaryElement(&element));
  EXPECT_EQ(encoder->byteOrder(), bigEndian);
}

TEST_F(TiffEncoderVisitBinaryElementTest_1678, KeepsByteOrderWhenElementByteOrderIsInvalid_1678) {
  auto encoder = MakeEncoder(littleEndian);
  ASSERT_NE(encoder, nullptr);
  EXPECT_EQ(encoder->byteOrder(), littleEndian);

  TiffBinaryElement element;
  element.setElByteOrder(invalidByteOrder);

  // Observable behavior: byte order should remain unchanged after visiting an element whose
  // elByteOrder() is invalid.
  ASSERT_NO_THROW(encoder->visitBinaryElement(&element));
  EXPECT_EQ(encoder->byteOrder(), littleEndian);
}

TEST_F(TiffEncoderVisitBinaryElementTest_1678, MultipleVisitsAlwaysRestoreOriginalByteOrder_1678) {
  auto encoder = MakeEncoder(bigEndian);
  ASSERT_NE(encoder, nullptr);
  EXPECT_EQ(encoder->byteOrder(), bigEndian);

  TiffBinaryElement elementLE;
  elementLE.setElByteOrder(littleEndian);

  TiffBinaryElement elementInvalid;
  elementInvalid.setElByteOrder(invalidByteOrder);

  ASSERT_NO_THROW(encoder->visitBinaryElement(&elementLE));
  EXPECT_EQ(encoder->byteOrder(), bigEndian);

  ASSERT_NO_THROW(encoder->visitBinaryElement(&elementInvalid));
  EXPECT_EQ(encoder->byteOrder(), bigEndian);

  // Visit again to ensure no state “leaks” between calls.
  ASSERT_NO_THROW(encoder->visitBinaryElement(&elementLE));
  EXPECT_EQ(encoder->byteOrder(), bigEndian);
}