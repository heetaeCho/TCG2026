// SPDX-License-Identifier: GPL-2.0-or-later
//
// File: RunLengthEncoder_test_223.cpp
//
// Unit tests for the (partial) RunLengthEncoder interface in Stream.h
// Constraints honored:
// - Treat implementation as a black box.
// - Test only observable behavior through the public interface.
//
// NOTE: The provided snippet shows getPSFilter(...) always returning std::nullopt ({}).
// We only assert what is observable via the interface: return engaged/empty, and that it
// does not throw for a variety of inputs.

#include <gtest/gtest.h>

#include <optional>
#include <string>

// Include the real header from the codebase.
#include "Stream.h"

namespace {

class RunLengthEncoderTest_223 : public ::testing::Test {
protected:
  RunLengthEncoder encoder_;
};

TEST_F(RunLengthEncoderTest_223, GetPSFilter_ReturnsNullopt_ForTypicalInputs_223) {
  const std::optional<std::string> out = encoder_.getPSFilter(2, "  ");
  EXPECT_FALSE(out.has_value());
}

TEST_F(RunLengthEncoderTest_223, GetPSFilter_ReturnsNullopt_ForNullIndent_223) {
  const std::optional<std::string> out = encoder_.getPSFilter(3, nullptr);
  EXPECT_FALSE(out.has_value());
}

TEST_F(RunLengthEncoderTest_223, GetPSFilter_ReturnsNullopt_ForEmptyIndent_223) {
  const std::optional<std::string> out = encoder_.getPSFilter(3, "");
  EXPECT_FALSE(out.has_value());
}

TEST_F(RunLengthEncoderTest_223, GetPSFilter_ReturnsNullopt_ForVariousPSLevels_223) {
  // Boundary-ish values; we only validate it remains well-defined via the interface.
  for (int level : {0, 1, 2, 3, 10, -1, -100, 100}) {
    const std::optional<std::string> out = encoder_.getPSFilter(level, "    ");
    EXPECT_FALSE(out.has_value()) << "psLevel=" << level;
  }
}

TEST_F(RunLengthEncoderTest_223, GetPSFilter_DoesNotThrow_ForVariousIndents_223) {
  const char* indents[] = {" ", "\t", "    ", ">>", "indent", "\n", "\r\n"};
  for (const char* indent : indents) {
    EXPECT_NO_THROW({
      const std::optional<std::string> out = encoder_.getPSFilter(2, indent);
      EXPECT_FALSE(out.has_value());
    }) << "indent=" << (indent ? indent : "(null)");
  }
}

TEST_F(RunLengthEncoderTest_223, GetPSFilter_CanBeCalledRepeatedly_AndStaysNullopt_223) {
  for (int i = 0; i < 50; ++i) {
    const std::optional<std::string> out = encoder_.getPSFilter(i, "  ");
    EXPECT_FALSE(out.has_value()) << "iteration=" << i;
  }
}

}  // namespace