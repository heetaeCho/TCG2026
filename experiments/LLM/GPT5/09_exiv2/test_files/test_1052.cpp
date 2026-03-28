// File: test_image_is2ByteType_1052.cpp
// TEST_ID: 1052

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <vector>

#include "exiv2/image.hpp"

namespace {

class ImageIs2ByteTypeTest_1052 : public ::testing::Test {};

TEST_F(ImageIs2ByteTypeTest_1052, MatchesIsShortTypeForCommonSamples_1052) {
  const std::vector<uint16_t> samples = {
      static_cast<uint16_t>(0u),
      static_cast<uint16_t>(1u),
      static_cast<uint16_t>(2u),
      static_cast<uint16_t>(3u),
      static_cast<uint16_t>(4u),
      static_cast<uint16_t>(5u),
      static_cast<uint16_t>(6u),
      static_cast<uint16_t>(7u),
      static_cast<uint16_t>(8u),
      static_cast<uint16_t>(9u),
      static_cast<uint16_t>(10u),
      static_cast<uint16_t>(16u),
      static_cast<uint16_t>(255u),
      static_cast<uint16_t>(256u),
      static_cast<uint16_t>(1024u),
      static_cast<uint16_t>(4095u),
      static_cast<uint16_t>(32767u),
      static_cast<uint16_t>(32768u),
      static_cast<uint16_t>(65534u),
      static_cast<uint16_t>(65535u),
  };

  for (const auto type : samples) {
    const bool expected = Exiv2::Image::isShortType(type);
    const bool actual = Exiv2::Image::is2ByteType(type);
    EXPECT_EQ(actual, expected) << "type=" << type;
  }
}

TEST_F(ImageIs2ByteTypeTest_1052, MatchesIsShortTypeForAllPossibleValues_1052) {
  // Exhaustive boundary-style verification over the whole uint16_t domain.
  // This does NOT re-implement logic: it checks that is2ByteType is consistent
  // with the observable public API contract implied by the implementation.
  for (uint32_t v = 0; v <= std::numeric_limits<uint16_t>::max(); ++v) {
    const uint16_t type = static_cast<uint16_t>(v);
    EXPECT_EQ(Exiv2::Image::is2ByteType(type), Exiv2::Image::isShortType(type))
        << "type=" << type;
  }
}

TEST_F(ImageIs2ByteTypeTest_1052, IsDeterministicAcrossRepeatedCalls_1052) {
  const std::vector<uint16_t> samples = {
      static_cast<uint16_t>(0u),
      static_cast<uint16_t>(3u),
      static_cast<uint16_t>(42u),
      static_cast<uint16_t>(256u),
      static_cast<uint16_t>(1024u),
      std::numeric_limits<uint16_t>::max(),
  };

  for (const auto type : samples) {
    const bool first = Exiv2::Image::is2ByteType(type);
    for (int i = 0; i < 10; ++i) {
      EXPECT_EQ(Exiv2::Image::is2ByteType(type), first) << "type=" << type;
    }
  }
}

TEST_F(ImageIs2ByteTypeTest_1052, DoesNotThrowForBoundaryValues_1052) {
  EXPECT_NO_THROW((void)Exiv2::Image::is2ByteType(static_cast<uint16_t>(0u)));
  EXPECT_NO_THROW(
      (void)Exiv2::Image::is2ByteType(std::numeric_limits<uint16_t>::max()));
}

}  // namespace