// =================================================================================================
// asfvideo_extendedcontentdescription_test_1570.cpp
// Unit tests for Exiv2::AsfVideo::extendedContentDescription()
// TEST_ID: 1570
// =================================================================================================

#include <gtest/gtest.h>

#include <exiv2/asfvideo.hpp>
#include <exiv2/basicio.hpp>

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace {

using ByteVec = std::vector<Exiv2::byte>;

static ByteVec U16LE(uint16_t v) {
  // ASF is typically little-endian; this helper writes little-endian words.
  return ByteVec{static_cast<Exiv2::byte>(v & 0xFF), static_cast<Exiv2::byte>((v >> 8) & 0xFF)};
}

static void Append(ByteVec& dst, const ByteVec& src) { dst.insert(dst.end(), src.begin(), src.end()); }

static Exiv2::BasicIo::UniquePtr MakeMemIo(const ByteVec& bytes) {
  // MemIo is part of Exiv2's public BasicIo family.
  return std::make_unique<Exiv2::MemIo>(bytes.data(), static_cast<long>(bytes.size()));
}

class AsfVideoTestable_1570 : public Exiv2::AsfVideo {
 public:
  explicit AsfVideoTestable_1570(Exiv2::BasicIo::UniquePtr io) : Exiv2::AsfVideo(std::move(io)) {}
  void CallExtendedContentDescription() { extendedContentDescription(); }
};

class AsfVideoExtendedContentDescriptionTest_1570 : public ::testing::Test {};

TEST_F(AsfVideoExtendedContentDescriptionTest_1570, ZeroDescriptorCount_SetsKeyToEmpty_1570) {
  ByteVec bytes;
  Append(bytes, U16LE(0));  // content_descriptor_count = 0

  AsfVideoTestable_1570 v(MakeMemIo(bytes));
  ASSERT_NO_THROW(v.CallExtendedContentDescription());

  // Observable effect: the XMP key is assigned (even if empty).
  EXPECT_EQ(v.xmpData()["Xmp.video.ExtendedContentDescription"].toString(), std::string());
}

TEST_F(AsfVideoExtendedContentDescriptionTest_1570, OneDescriptor_ZeroNameAndZeroValue_EndsWithCommaSpace_1570) {
  ByteVec bytes;
  Append(bytes, U16LE(1));  // content_descriptor_count = 1

  Append(bytes, U16LE(0));  // descriptor_name_length = 0 (no name bytes follow)

  Append(bytes, U16LE(0));  // descriptor_value_data_type = 0 (Unicode string) - not used since value_length=0
  Append(bytes, U16LE(0));  // descriptor_value_length = 0 (no value bytes follow)

  AsfVideoTestable_1570 v(MakeMemIo(bytes));
  ASSERT_NO_THROW(v.CallExtendedContentDescription());

  // With one descriptor and no name/value content, the implementation still appends ", ".
  EXPECT_EQ(v.xmpData()["Xmp.video.ExtendedContentDescription"].toString(), std::string(", "));
}

TEST_F(AsfVideoExtendedContentDescriptionTest_1570, ExistingXmpValue_IsOverwritten_1570) {
  ByteVec bytes;
  Append(bytes, U16LE(0));  // content_descriptor_count = 0 -> value becomes empty

  AsfVideoTestable_1570 v(MakeMemIo(bytes));

  // Pre-set a value and ensure the call overwrites it.
  v.xmpData()["Xmp.video.ExtendedContentDescription"] = std::string("old");
  ASSERT_NO_THROW(v.CallExtendedContentDescription());

  EXPECT_EQ(v.xmpData()["Xmp.video.ExtendedContentDescription"].toString(), std::string());
}

TEST_F(AsfVideoExtendedContentDescriptionTest_1570, EmptyInput_Throws_1570) {
  // No bytes at all: the first readWORDTag(io_) should fail in some observable way (exception).
  ByteVec bytes;

  AsfVideoTestable_1570 v(MakeMemIo(bytes));
  EXPECT_ANY_THROW(v.CallExtendedContentDescription());
}

}  // namespace