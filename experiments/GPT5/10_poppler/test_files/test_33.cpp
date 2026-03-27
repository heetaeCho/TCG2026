// TEST_ID is 33
#include <gtest/gtest.h>

#include <limits>
#include <type_traits>

#include "goo/TiffWriter.h"

namespace {

class TiffWriterTest_33 : public ::testing::Test {};

TEST_F(TiffWriterTest_33, SupportCMYK_ReturnsTrue_ForFormat0_33) {
  TiffWriter writer(static_cast<Format>(0));
  EXPECT_TRUE(writer.supportCMYK());
}

TEST_F(TiffWriterTest_33, SupportCMYK_ReturnsTrue_ForDifferentFormats_33) {
  TiffWriter writer0(static_cast<Format>(0));
  TiffWriter writer1(static_cast<Format>(1));
  EXPECT_TRUE(writer0.supportCMYK());
  EXPECT_TRUE(writer1.supportCMYK());
}

TEST_F(TiffWriterTest_33, SupportCMYK_ReturnsTrue_ForExtremeFormatValue_33) {
  // Boundary-ish: create with a large integral value cast to Format.
  TiffWriter writerMax(static_cast<Format>(std::numeric_limits<int>::max()));
  EXPECT_TRUE(writerMax.supportCMYK());
}

TEST_F(TiffWriterTest_33, SupportCMYK_IsIdempotent_AcrossMultipleCalls_33) {
  TiffWriter writer(static_cast<Format>(0));
  EXPECT_TRUE(writer.supportCMYK());
  EXPECT_TRUE(writer.supportCMYK());
  EXPECT_TRUE(writer.supportCMYK());
}

// Interface-level (compile-time) checks derived from the provided signatures.
static_assert(!std::is_copy_constructible_v<TiffWriter>,
              "TiffWriter copy-ctor should be deleted per interface");
static_assert(!std::is_copy_assignable_v<TiffWriter>,
              "TiffWriter copy assignment should be deleted per interface");

}  // namespace