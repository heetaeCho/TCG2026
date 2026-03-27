// Decrypt_md5Round4_unittest_1621.cc
#include <gtest/gtest.h>

#include <cstdint>
#include <limits>

// NOTE:
// md5Round4 is a static inline function in Decrypt.cc (internal linkage).
// To test it via its real implementation without re-implementing it here,
// we include the translation unit so the function is visible in this TU.
#include "poppler/Decrypt.cc"

namespace {

constexpr uint32_t kMask32 = 0xffffffffu;

static uint32_t Low32(unsigned long v) {
  return static_cast<uint32_t>(v & static_cast<unsigned long>(kMask32));
}

class Md5Round4Test_1621 : public ::testing::Test {};

TEST_F(Md5Round4Test_1621, ProducesExpectedLow32ForAllZerosWithShift1_1621) {
  const unsigned long a = 0ul;
  const unsigned long b = 0ul;
  const unsigned long c = 0ul;
  const unsigned long d = 0ul;
  const unsigned long Xk = 0ul;
  const unsigned long s = 1ul;
  const unsigned long Ti = 0ul;

  const unsigned long out = md5Round4(a, b, c, d, Xk, s, Ti);

  // Golden value (low 32-bit) for the given inputs.
  EXPECT_EQ(Low32(out), 0xffffffffu);
}

TEST_F(Md5Round4Test_1621, ProducesExpectedLow32ForSmallIncreasingInputs_1621) {
  const unsigned long out = md5Round4(
      /*a=*/0ul, /*b=*/1ul, /*c=*/2ul, /*d=*/3ul,
      /*Xk=*/4ul, /*s=*/5ul, /*Ti=*/6ul);

  EXPECT_EQ(Low32(out), 0x00000121u);
}

TEST_F(Md5Round4Test_1621, ProducesExpectedLow32ForRfcStyleStateExample1_1621) {
  // Common MD5 IV-like values + round-4 constant used in many references.
  const unsigned long out = md5Round4(
      /*a=*/0x67452301ul,
      /*b=*/0xefcdab89ul,
      /*c=*/0x98badcfeul,
      /*d=*/0x10325476ul,
      /*Xk=*/0ul,
      /*s=*/6ul,
      /*Ti=*/0xf4292244ul);

  EXPECT_EQ(Low32(out), 0xa93cdabdu);
}

TEST_F(Md5Round4Test_1621, ProducesExpectedLow32ForRfcStyleStateExample2_1621) {
  const unsigned long out = md5Round4(
      /*a=*/0x10325476ul,
      /*b=*/0x67452301ul,
      /*c=*/0xefcdab89ul,
      /*d=*/0x98badcfeul,
      /*Xk=*/0ul,
      /*s=*/10ul,
      /*Ti=*/0x432aff97ul);

  EXPECT_EQ(Low32(out), 0xfeb77a70u);
}

TEST_F(Md5Round4Test_1621, BoundaryAllOnesInputsProducesExpectedLow32_1621) {
  const unsigned long out = md5Round4(
      /*a=*/std::numeric_limits<unsigned long>::max(),
      /*b=*/std::numeric_limits<unsigned long>::max(),
      /*c=*/std::numeric_limits<unsigned long>::max(),
      /*d=*/std::numeric_limits<unsigned long>::max(),
      /*Xk=*/std::numeric_limits<unsigned long>::max(),
      /*s=*/21ul,
      /*Ti=*/0xfc93a039ul);

  EXPECT_EQ(Low32(out), 0x06ff9273u);
}

TEST_F(Md5Round4Test_1621, BoundaryShift31ProducesExpectedLow32_1621) {
  const unsigned long out = md5Round4(
      /*a=*/0x80000000ul,
      /*b=*/0x7ffffffful,
      /*c=*/0x00000000ul,
      /*d=*/0xfffffffful,
      /*Xk=*/0ul,
      /*s=*/31ul,
      /*Ti=*/0x12345678ul);

  EXPECT_EQ(Low32(out), 0x091a2b3au);
}

TEST_F(Md5Round4Test_1621, DeterministicForSameInputs_1621) {
  const unsigned long a = 0x01234567ul;
  const unsigned long b = 0x89abcdeful;
  const unsigned long c = 0xfedcba98ul;
  const unsigned long d = 0x76543210ul;
  const unsigned long Xk = 0x0f0e0d0cul;
  const unsigned long s = 15ul;
  const unsigned long Ti = 0xab9423a7ul;

  const unsigned long out1 = md5Round4(a, b, c, d, Xk, s, Ti);
  const unsigned long out2 = md5Round4(a, b, c, d, Xk, s, Ti);

  EXPECT_EQ(out1, out2);
  EXPECT_EQ(Low32(out1), 0x0074678du);
}

}  // namespace