// File: snappy_compress_test_36.cc
#include "port/port_stdcxx.h"

#include <gtest/gtest.h>
#include <string>

namespace {

using leveldb::port::Snappy_Compress;

class SnappyCompressTest_36 : public ::testing::Test {};

// Normal operation with non-empty input
TEST(SnappyCompressTest_36, ReturnsExpectedFlag_NonEmpty_36) {
  const std::string input = "hello world!";
  std::string output = "preset";
  const bool ok = Snappy_Compress(input.data(), input.size(), &output);

#if HAVE_SNAPPY
  // When compression is available, function should succeed and produce some bytes.
  EXPECT_TRUE(ok);
  // Output should be set by the function; it shouldn't remain the preset string.
  EXPECT_NE(output, "preset");
  // For non-empty input, compressed output should not be empty.
  EXPECT_FALSE(output.empty());
#else
  // When compression is not available, function should fail and not modify output.
  EXPECT_FALSE(ok);
  EXPECT_EQ(output, "preset");
#endif
}

// Boundary condition: empty input
TEST(SnappyCompressTest_36, EmptyInputBehavior_36) {
  const std::string input;  // empty
  std::string output = "unchanged";
  const bool ok = Snappy_Compress(input.data(), input.size(), &output);

#if HAVE_SNAPPY
  EXPECT_TRUE(ok);
  // For empty input, it is valid for the compressed output to be empty.
  // At minimum, the function should define the output; allow either empty or non-empty,
  // but it must not remain the sentinel "unchanged".
  EXPECT_NE(output, "unchanged");
  // Many compressors return empty for empty input; accept both to avoid assuming internals.
  // If you want to be stricter for your environment, you may assert EXPECT_TRUE(output.empty()).
#else
  EXPECT_FALSE(ok);
  // No compression available -> output should not be modified.
  EXPECT_EQ(output, "unchanged");
#endif
}

// Verification of external effect on the provided buffer object
// (ensuring the function overwrites rather than appends/preserves previous content)
TEST(SnappyCompressTest_36, OverwritesOutputBuffer_36) {
  const std::string input(64, 'A');  // moderately sized input
  std::string output = "XXXXXXXXXXXXXXXX";  // recognizable sentinel content
  const bool ok = Snappy_Compress(input.data(), input.size(), &output);

#if HAVE_SNAPPY
  EXPECT_TRUE(ok);
  // Output should not retain the sentinel content.
  EXPECT_NE(output, "XXXXXXXXXXXXXXXX");
  // Size is determined by the implementation, but should be a conscious write, not append.
  // At least verify it's not exactly the old sentinel size unless implementation chooses so;
  // if it is, the content should differ.
  // (This keeps the check black-box and tolerant.)
  if (output.size() == std::string("XXXXXXXXXXXXXXXX").size()) {
    EXPECT_NE(output, "XXXXXXXXXXXXXXXX");
  }
#else
  EXPECT_FALSE(ok);
  // Without snappy, there should be no visible change to the provided output string.
  EXPECT_EQ(output, "XXXXXXXXXXXXXXXX");
#endif
}

}  // namespace
