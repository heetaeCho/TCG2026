// TEST_ID: 217
// File: ASCII85Encoder_test.cpp
//
// Unit tests for:
//   class ASCII85Encoder
// Interface under test:
//   std::optional<std::string> getPSFilter(int psLevel, const char* indent)
//
// Constraints honored:
// - Treat implementation as a black box
// - Test only observable behavior (return value)
// - No private/internal access
// - No mocking needed (no external collaborators exposed)

#include <gtest/gtest.h>

#include <optional>
#include <string>

// Include the production header.
#include "Stream.h"

namespace {

class ASCII85EncoderTest_217 : public ::testing::Test {
protected:
  ASCII85Encoder encoder;
};

TEST_F(ASCII85EncoderTest_217, GetPSFilterReturnsEmptyOptional_217) {
  // Normal operation: call with typical parameters.
  std::optional<std::string> result = encoder.getPSFilter(2, "  ");
  EXPECT_FALSE(result.has_value());
}

TEST_F(ASCII85EncoderTest_217, GetPSFilterReturnsEmptyOptionalForVariousLevels_217) {
  // Boundary-ish coverage: different psLevel values (including negative/zero/large).
  EXPECT_FALSE(encoder.getPSFilter(-1, " ").has_value());
  EXPECT_FALSE(encoder.getPSFilter(0, "").has_value());
  EXPECT_FALSE(encoder.getPSFilter(1, "\t").has_value());
  EXPECT_FALSE(encoder.getPSFilter(999999, "    ").has_value());
}

TEST_F(ASCII85EncoderTest_217, GetPSFilterHandlesNullIndentPointer_217) {
  // Error-ish / robustness case: null indent pointer.
  // Observable requirement: should not throw; should return empty optional.
  EXPECT_NO_THROW({
    std::optional<std::string> result = encoder.getPSFilter(1, nullptr);
    EXPECT_FALSE(result.has_value());
  });
}

TEST_F(ASCII85EncoderTest_217, GetPSFilterIsDeterministicAcrossRepeatedCalls_217) {
  // Repeated calls should be consistent in observable behavior.
  auto r1 = encoder.getPSFilter(3, ">>");
  auto r2 = encoder.getPSFilter(3, ">>");
  auto r3 = encoder.getPSFilter(3, ">>");

  EXPECT_FALSE(r1.has_value());
  EXPECT_FALSE(r2.has_value());
  EXPECT_FALSE(r3.has_value());
}

TEST_F(ASCII85EncoderTest_217, GetPSFilterIgnoresIndentContentObservableResultStillEmpty_217) {
  // Vary indent content; observable result remains empty.
  EXPECT_FALSE(encoder.getPSFilter(2, " ").has_value());
  EXPECT_FALSE(encoder.getPSFilter(2, "        ").has_value());
  EXPECT_FALSE(encoder.getPSFilter(2, "\n").has_value());
  EXPECT_FALSE(encoder.getPSFilter(2, "indent-with-specials: !@#$%^&*()").has_value());
}

}  // namespace