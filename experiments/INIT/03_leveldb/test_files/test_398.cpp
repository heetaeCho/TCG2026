// File: footer_encode_to_test_398.cc
#include <gtest/gtest.h>
#include <string>
#include <cstdint>
#include <cstring>

// Include the headers under test
#include "table/format.h"   // Declares leveldb::Footer and kTableMagicNumber

namespace {

// Helper: read a little-endian uint32_t from a char buffer.
static uint32_t ReadLE32(const char* p) {
  // Interpret as unsigned bytes; portable for tests.
  return (static_cast<uint32_t>(static_cast<unsigned char>(p[0]))      ) |
         (static_cast<uint32_t>(static_cast<unsigned char>(p[1])) <<  8) |
         (static_cast<uint32_t>(static_cast<unsigned char>(p[2])) << 16) |
         (static_cast<uint32_t>(static_cast<unsigned char>(p[3])) << 24);
}

// Helper: interpret the last 8 bytes of s as two fixed32 little-endian words
// and combine them into a uint64_t: low32 first, then high32.
static uint64_t ReadTrailingFixed64AsTwoFixed32LE(const std::string& s) {
  ASSERT_GE(s.size(), size_t{8}) << "Output must be at least 8 bytes to read magic";
  const char* p = s.data() + (s.size() - 8);
  uint32_t low  = ReadLE32(p);
  uint32_t high = ReadLE32(p + 4);
  return (static_cast<uint64_t>(high) << 32) | static_cast<uint64_t>(low);
}

}  // namespace

using leveldb::Footer;
using leveldb::kTableMagicNumber;

class FooterEncodeToTest_398 : public ::testing::Test {};

// Verifies that EncodeTo appends (i.e., results end with) the table magic number.
// We only assert on the observable bytes written by the API.
TEST_F(FooterEncodeToTest_398, AppendsMagicNumberAtEnd_398) {
  Footer footer;
  std::string out;
  footer.EncodeTo(&out);

  ASSERT_GE(out.size(), size_t{8}) << "EncodeTo should write at least the magic";
  uint64_t magic_at_end = ReadTrailingFixed64AsTwoFixed32LE(out);
  EXPECT_EQ(magic_at_end, kTableMagicNumber);
}

// Verifies that EncodeTo appends to an existing prefix without removing it.
// This checks the black-box behavior that the function does not erase prior data.
TEST_F(FooterEncodeToTest_398, PreservesExistingPrefix_398) {
  Footer footer;
  std::string out = "prefix-data";
  const std::string original = out;

  footer.EncodeTo(&out);

  ASSERT_GE(out.size(), original.size() + size_t{8});
  // Existing prefix must remain unchanged at the front.
  EXPECT_EQ(out.substr(0, original.size()), original);

  // The encoded footer should still end with the magic.
  uint64_t magic_at_end = ReadTrailingFixed64AsTwoFixed32LE(out);
  EXPECT_EQ(magic_at_end, kTableMagicNumber);
}

// Calling EncodeTo multiple times should keep appending new footer encodings.
// We verify size growth and that the *final* 8 bytes still represent the magic.
TEST_F(FooterEncodeToTest_398, MultipleEncodesGrowAndEndWithMagic_398) {
  Footer footer;
  std::string out;

  footer.EncodeTo(&out);
  const size_t after_first = out.size();
  ASSERT_GE(after_first, size_t{8});

  footer.EncodeTo(&out);
  const size_t after_second = out.size();

  // Size must increase on subsequent encodes (black-box observable effect).
  EXPECT_GT(after_second, after_first);

  // Final 8 bytes should still be the magic number.
  uint64_t magic_at_end = ReadTrailingFixed64AsTwoFixed32LE(out);
  EXPECT_EQ(magic_at_end, kTableMagicNumber);
}

// Minimal robustness check: EncodeTo should not shrink the buffer and
// should increase it by at least 8 bytes (the two fixed32 words).
TEST_F(FooterEncodeToTest_398, SizeGrowsByAtLeastMagicBytes_398) {
  Footer footer;
  std::string out;
  const size_t before = out.size();

  footer.EncodeTo(&out);

  EXPECT_GE(out.size(), before + size_t{8});
  // And verify the trailing magic again to ensure correct termination.
  uint64_t magic_at_end = ReadTrailingFixed64AsTwoFixed32LE(out);
  EXPECT_EQ(magic_at_end, kTableMagicNumber);
}
