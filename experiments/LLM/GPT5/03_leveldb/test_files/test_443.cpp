// File: coding_putvarint64_test.cc
#include "gtest/gtest.h"
#include <cstdint>
#include <string>
#include <vector>

// SUT header (declare the function we test)
namespace leveldb {
  void PutVarint64(std::string* dst, uint64_t v);
}

namespace {

// Small helper to build a std::string from raw bytes
std::string Bytes(std::initializer_list<uint8_t> bs) {
  return std::string(reinterpret_cast<const char*>(bs.begin()), bs.size());
}

// ----- Tests -----

TEST(PutVarint64Test_443, EncodesZero_443) {
  std::string out;
  leveldb::PutVarint64(&out, 0ull);
  EXPECT_EQ(out, Bytes({0x00}));
}

TEST(PutVarint64Test_443, EncodesOneByteBoundary_443) {
  std::string out;
  leveldb::PutVarint64(&out, 127ull);  // 0x7F
  EXPECT_EQ(out, Bytes({0x7F}));
}

TEST(PutVarint64Test_443, EncodesTwoBytesAtBoundaryStart_443) {
  std::string out;
  leveldb::PutVarint64(&out, 128ull);  // 0x80 0x01
  EXPECT_EQ(out, Bytes({0x80, 0x01}));
}

TEST(PutVarint64Test_443, EncodesTypicalTwoByteValue_443) {
  std::string out;
  leveldb::PutVarint64(&out, 255ull);  // 0xFF 0x01
  EXPECT_EQ(out, Bytes({0xFF, 0x01}));
}

TEST(PutVarint64Test_443, EncodesAnotherTwoByteValue_443) {
  std::string out;
  leveldb::PutVarint64(&out, 300ull);  // 0xAC 0x02
  EXPECT_EQ(out, Bytes({0xAC, 0x02}));
}

TEST(PutVarint64Test_443, EncodesThreeBytesAtNextBoundaryStart_443) {
  std::string out;
  leveldb::PutVarint64(&out, 16384ull);  // 1<<14 -> 0x80 0x80 0x01
  EXPECT_EQ(out, Bytes({0x80, 0x80, 0x01}));
}

TEST(PutVarint64Test_443, AppendsToExistingString_443) {
  std::string out = "xyz";
  leveldb::PutVarint64(&out, 0ull);  // append single 0x00
  EXPECT_EQ(out, std::string("xyz") + Bytes({0x00}));
}

TEST(PutVarint64Test_443, MultipleAppendsConcatenateEncodings_443) {
  std::string out;
  leveldb::PutVarint64(&out, 1ull);    // 0x01
  leveldb::PutVarint64(&out, 128ull);  // 0x80 0x01
  leveldb::PutVarint64(&out, 300ull);  // 0xAC 0x02
  EXPECT_EQ(out, Bytes({0x01, 0x80, 0x01, 0xAC, 0x02}));
}

TEST(PutVarint64Test_443, EncodesMaxUint64_443) {
  std::string out;
  leveldb::PutVarint64(&out, std::numeric_limits<uint64_t>::max());
  // For max u64, varint uses 10 bytes: 0xFF repeated 9 times, then 0x01
  EXPECT_EQ(out, Bytes({0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                        0xFF, 0xFF, 0xFF, 0xFF, 0x01}));
}

} // namespace
