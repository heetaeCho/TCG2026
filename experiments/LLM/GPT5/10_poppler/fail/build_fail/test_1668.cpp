// DeviceNRecoder_getPSFilter_test_1668.cc
#include <gtest/gtest.h>

#include <optional>
#include <string>
#include <type_traits>
#include <utility>

// NOTE:
// DeviceNRecoder is defined in PSOutputDev.cc in the provided snippet.
// To test this implementation as a black box via its public interface, we include the .cc.
// This is a common approach for unit-testing internal/translation-unit-only helpers.
#include "PSOutputDev.cc"

namespace {

class DeviceNRecoderTest_1668 : public ::testing::Test {};

// Helper to call getPSFilter safely (covers nullptr indent too).
static std::optional<std::string> CallGetPSFilter_1668(DeviceNRecoder &rec, int psLevel,
                                                       const char *indent) {
  return rec.getPSFilter(psLevel, indent);
}

TEST_F(DeviceNRecoderTest_1668, IsDefaultConstructible_1668) {
  EXPECT_TRUE((std::is_default_constructible_v<DeviceNRecoder>));
}

TEST_F(DeviceNRecoderTest_1668, GetPSFilterReturnsEmptyOptionalOnTypicalInput_1668) {
  DeviceNRecoder rec;

  auto out = CallGetPSFilter_1668(rec, /*psLevel=*/2, /*indent=*/"  ");
  EXPECT_FALSE(out.has_value());
}

TEST_F(DeviceNRecoderTest_1668, GetPSFilterReturnsEmptyOptionalOnZeroLevel_1668) {
  DeviceNRecoder rec;

  auto out = CallGetPSFilter_1668(rec, /*psLevel=*/0, /*indent=*/"");
  EXPECT_FALSE(out.has_value());
}

TEST_F(DeviceNRecoderTest_1668, GetPSFilterReturnsEmptyOptionalOnNegativeLevel_1668) {
  DeviceNRecoder rec;

  auto out = CallGetPSFilter_1668(rec, /*psLevel=*/-1, /*indent=*/"  ");
  EXPECT_FALSE(out.has_value());
}

TEST_F(DeviceNRecoderTest_1668, GetPSFilterReturnsEmptyOptionalOnLargeLevel_1668) {
  DeviceNRecoder rec;

  auto out = CallGetPSFilter_1668(rec, /*psLevel=*/1000000, /*indent=*/"  ");
  EXPECT_FALSE(out.has_value());
}

TEST_F(DeviceNRecoderTest_1668, GetPSFilterHandlesNullIndent_1668) {
  DeviceNRecoder rec;

  EXPECT_NO_THROW({
    auto out = CallGetPSFilter_1668(rec, /*psLevel=*/2, /*indent=*/nullptr);
    EXPECT_FALSE(out.has_value());
  });
}

TEST_F(DeviceNRecoderTest_1668, GetPSFilterHandlesLongIndentString_1668) {
  DeviceNRecoder rec;

  std::string longIndent(4096, ' ');
  auto out = CallGetPSFilter_1668(rec, /*psLevel=*/3, /*indent=*/longIndent.c_str());
  EXPECT_FALSE(out.has_value());
}

TEST_F(DeviceNRecoderTest_1668, GetPSFilterIsDeterministicAcrossMultipleCalls_1668) {
  DeviceNRecoder rec;

  auto out1 = CallGetPSFilter_1668(rec, /*psLevel=*/1, /*indent=*/" ");
  auto out2 = CallGetPSFilter_1668(rec, /*psLevel=*/1, /*indent=*/" ");
  auto out3 = CallGetPSFilter_1668(rec, /*psLevel=*/1, /*indent=*/" ");

  EXPECT_FALSE(out1.has_value());
  EXPECT_FALSE(out2.has_value());
  EXPECT_FALSE(out3.has_value());
}

}  // namespace