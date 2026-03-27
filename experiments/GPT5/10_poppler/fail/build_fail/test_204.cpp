// File: BufStream_test.cpp
// TEST_ID: 204
//
// Unit tests for the provided partial interface in:
//   ./TestProjects/poppler/poppler/Stream.h
//
// Notes:
// - Treat implementation as a black box.
// - Only test observable behavior from the public interface.
// - No private/internal state access.
// - Google Mock is not needed here because there are no observable external interactions.

#include <gtest/gtest.h>

#include <optional>
#include <string>

// Include the header under test.
#include "Stream.h"

namespace {

class BufStreamTest_204 : public ::testing::Test {
 protected:
  BufStream stream_;
};

TEST_F(BufStreamTest_204, GetPSFilterReturnsEmptyOptional_204) {
  // Normal operation: the interface returns an std::optional<std::string>.
  // Observable behavior from the provided code: it returns {}.
  const std::optional<std::string> out = stream_.getPSFilter(/*psLevel=*/0, /*indent=*/"");
  EXPECT_FALSE(out.has_value());
}

TEST_F(BufStreamTest_204, GetPSFilterIgnoresPsLevelAndIndent_ReturnsEmpty_204) {
  // Boundary-ish coverage: try various psLevel values and indent strings (including nullptr).
  // We only assert the observable contract from the provided implementation: always empty.
  EXPECT_FALSE(stream_.getPSFilter(-1, "  ").has_value());
  EXPECT_FALSE(stream_.getPSFilter(0, "\t").has_value());
  EXPECT_FALSE(stream_.getPSFilter(1, "").has_value());
  EXPECT_FALSE(stream_.getPSFilter(999999, "indent").has_value());
  EXPECT_FALSE(stream_.getPSFilter(42, nullptr).has_value());
}

TEST_F(BufStreamTest_204, GetPSFilterRepeatedCallsRemainEmpty_204) {
  // Normal operation: repeated calls should be stable/consistent from the outside.
  for (int i = 0; i < 10; ++i) {
    const std::optional<std::string> out = stream_.getPSFilter(i, "x");
    EXPECT_FALSE(out.has_value());
  }
}

TEST_F(BufStreamTest_204, GetPSFilterDoesNotThrow_204) {
  // Exceptional/error cases: none are observable via the interface; still verify it doesn't throw.
  EXPECT_NO_THROW({
    (void)stream_.getPSFilter(0, "");
    (void)stream_.getPSFilter(0, nullptr);
    (void)stream_.getPSFilter(-123, "indent");
  });
}

}  // namespace