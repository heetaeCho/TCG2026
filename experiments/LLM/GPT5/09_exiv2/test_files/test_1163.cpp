// File: test_tiffmapping_finddecoder_1163.cpp
// TEST_ID: 1163

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <string>
#include <string_view>
#include <vector>

// Exiv2 internals under test
#include "tiffimage_int.hpp"

namespace {

// Helper to build a "very unlikely to exist" make string.
static std::string UnlikelyMake() {
  return "UnitTest_DefinitelyNotARealCameraMake_1163__"
         "X1b9c1c9c_6c4b_4e1b_9a6f_3b6c6e2c2a3a";
}

class TiffMappingTest_1163 : public ::testing::Test {
 protected:
  Exiv2::Internal::TiffMapping mapping_;
};

TEST_F(TiffMappingTest_1163, ReturnsNonNullDecoderForUnknownInputs_1163) {
  const std::string make = UnlikelyMake();
  const auto group = static_cast<Exiv2::IfdId>(0);

  const Exiv2::Internal::DecoderFct f =
      mapping_.findDecoder(std::string_view(make), 0xDEADBEEFu, group);

  ASSERT_NE(f, nullptr);
}

TEST_F(TiffMappingTest_1163, ReturnsDefaultDecoderForHighlyUnlikelyMake_1163) {
  const std::string make = UnlikelyMake();
  const auto group = static_cast<Exiv2::IfdId>(0);

  const Exiv2::Internal::DecoderFct f =
      mapping_.findDecoder(std::string_view(make),
                           std::numeric_limits<uint32_t>::max(), group);

  ASSERT_NE(f, nullptr);

  // Observable behavior from implementation snippet: default is decodeStdTiffEntry.
  // We purposely choose an extremely unlikely (make, tag, group) combination to
  // avoid relying on internal mapping contents.
  EXPECT_EQ(f, &Exiv2::Internal::TiffDecoder::decodeStdTiffEntry);
}

TEST_F(TiffMappingTest_1163, EmptyMakeDoesNotCrashAndReturnsNonNull_1163) {
  const std::string_view make = std::string_view{};
  const auto group = static_cast<Exiv2::IfdId>(0);

  const Exiv2::Internal::DecoderFct f = mapping_.findDecoder(make, 0u, group);

  EXPECT_NE(f, nullptr);
}

TEST_F(TiffMappingTest_1163, BoundaryExtendedTagsReturnNonNull_1163) {
  const std::string make = UnlikelyMake();
  const auto group = static_cast<Exiv2::IfdId>(0);

  const std::vector<uint32_t> tags = {
      0u,
      1u,
      0xFFFFu,
      0x10000u,
      0x7FFFFFFFu,
      std::numeric_limits<uint32_t>::max(),
  };

  for (const uint32_t tag : tags) {
    const Exiv2::Internal::DecoderFct f =
        mapping_.findDecoder(std::string_view(make), tag, group);
    EXPECT_NE(f, nullptr) << "tag=" << tag;
  }
}

TEST_F(TiffMappingTest_1163, VeryLongMakeStringViewReturnsNonNull_1163) {
  std::string longMake(10'000, 'A');
  longMake.replace(0, 16, "UnitTest_1163__");

  const auto group = static_cast<Exiv2::IfdId>(0);

  const Exiv2::Internal::DecoderFct f =
      mapping_.findDecoder(std::string_view(longMake), 0x12345678u, group);

  EXPECT_NE(f, nullptr);
}

TEST_F(TiffMappingTest_1163, SameInputIsDeterministicForUnknownMake_1163) {
  const std::string make = UnlikelyMake();
  const auto group = static_cast<Exiv2::IfdId>(0);
  const uint32_t tag = 0xCAFEBABEu;

  const Exiv2::Internal::DecoderFct f1 =
      mapping_.findDecoder(std::string_view(make), tag, group);
  const Exiv2::Internal::DecoderFct f2 =
      mapping_.findDecoder(std::string_view(make), tag, group);

  ASSERT_NE(f1, nullptr);
  ASSERT_NE(f2, nullptr);
  EXPECT_EQ(f1, f2);
}

}  // namespace