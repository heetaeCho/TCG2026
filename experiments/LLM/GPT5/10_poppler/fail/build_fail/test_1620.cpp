// Decrypt_md5Round3_test_1620.cc
#include <gtest/gtest.h>

#include <cstdint>
#include <limits>

// NOTE:
// md5Round3 is a TU-local (static inline) helper in Decrypt.cc.
// To test it via its provided interface, we include the implementation file here.
// This pattern assumes Decrypt.cc is NOT separately compiled/linked into the same test binary.
#include "./TestProjects/poppler/poppler/Decrypt.cc"

namespace {

static inline uint32_t U32(unsigned long v) {
  return static_cast<uint32_t>(v & 0xFFFFFFFFul);
}

TEST(md5Round3Test_1620, ProducesExpectedValue_KnownVector1_1620) {
  const unsigned long a  = 0x67452301ul;
  const unsigned long b  = 0xEFCDAB89ul;
  const unsigned long c  = 0x98BADCFEul;
  const unsigned long d  = 0x10325476ul;
  const unsigned long Xk = 0x00000000ul;
  const unsigned long s  = 4ul;
  const unsigned long Ti = 0xD76AA478ul;

  const unsigned long out = md5Round3(a, b, c, d, Xk, s, Ti);
  EXPECT_EQ(U32(out), 0x4F1C5333u);
}

TEST(md5Round3Test_1620, ProducesExpectedValue_KnownVector2_1620) {
  const unsigned long a  = 0x01234567ul;
  const unsigned long b  = 0x89ABCDEFul;
  const unsigned long c  = 0xFEDCBA98ul;
  const unsigned long d  = 0x76543210ul;
  const unsigned long Xk = 0x0F1E2D3Cul;
  const unsigned long s  = 11ul;
  const unsigned long Ti = 0xA4BEEA44ul;

  const unsigned long out = md5Round3(a, b, c, d, Xk, s, Ti);
  EXPECT_EQ(U32(out), 0xA6BE43A0u);
}

TEST(md5Round3Test_1620, ProducesExpectedValue_KnownVector3_1620) {
  const unsigned long a  = 0xFFFFFFFFul;
  const unsigned long b  = 0x00000000ul;
  const unsigned long c  = 0x00000000ul;
  const unsigned long d  = 0x00000000ul;
  const unsigned long Xk = 0xFFFFFFFFul;
  const unsigned long s  = 16ul;
  const unsigned long Ti = 0x4BDECFA9ul;

  const unsigned long out = md5Round3(a, b, c, d, Xk, s, Ti);
  EXPECT_EQ(U32(out), 0xCFA74BDEu);
}

TEST(md5Round3Test_1620, ProducesExpectedValue_KnownVector4_1620) {
  const unsigned long a  = 0x00000000ul;
  const unsigned long b  = 0xFFFFFFFFul;
  const unsigned long c  = 0x12345678ul;
  const unsigned long d  = 0x9ABCDEF0ul;
  const unsigned long Xk = 0x13579BDFul;
  const unsigned long s  = 23ul;
  const unsigned long Ti = 0xF6BB4B60ul;

  const unsigned long out = md5Round3(a, b, c, d, Xk, s, Ti);
  EXPECT_EQ(U32(out), 0x5B40C52Eu);
}

TEST(md5Round3Test_1620, DeterministicForSameInputs_1620) {
  const unsigned long a  = 0xDEADBEEFul;
  const unsigned long b  = 0xFEEDFACEul;
  const unsigned long c  = 0x01234567ul;
  const unsigned long d  = 0x89ABCDEFul;
  const unsigned long Xk = 0x00000001ul;
  const unsigned long s  = 1ul;
  const unsigned long Ti = 0x00000000ul;

  const unsigned long out1 = md5Round3(a, b, c, d, Xk, s, Ti);
  const unsigned long out2 = md5Round3(a, b, c, d, Xk, s, Ti);

  EXPECT_EQ(U32(out1), U32(out2));
  EXPECT_EQ(U32(out1), 0xA9145D3Au);
}

TEST(md5Round3Test_1620, Boundary_Shift31_HandlesHighBitRotation_1620) {
  const unsigned long a  = 0x80000000ul;
  const unsigned long b  = 0x7FFFFFFFul;
  const unsigned long c  = 0xAAAAAAAAul;
  const unsigned long d  = 0x55555555ul;
  const unsigned long Xk = 0xFFFFFFFFul;
  const unsigned long s  = 31ul;
  const unsigned long Ti = 0xFFFFFFFFul;

  const unsigned long out = md5Round3(a, b, c, d, Xk, s, Ti);
  EXPECT_EQ(U32(out), 0xFFFFFFFEu);
}

TEST(md5Round3Test_1620, Boundary_AllZeros_ReturnsSomeValue_AndIsStable_1620) {
  const unsigned long out1 = md5Round3(0ul, 0ul, 0ul, 0ul, 0ul, 0ul, 0ul);
  const unsigned long out2 = md5Round3(0ul, 0ul, 0ul, 0ul, 0ul, 0ul, 0ul);

  EXPECT_EQ(U32(out1), U32(out2));
  // No specific constant asserted here; this is a black-box boundary stability check.
}

TEST(md5Round3Test_1620, Boundary_MaxValues_NoCrashAndDeterministic_1620) {
  const unsigned long m = std::numeric_limits<unsigned long>::max();

  const unsigned long out1 = md5Round3(m, m, m, m, m, 7ul, m);
  const unsigned long out2 = md5Round3(m, m, m, m, m, 7ul, m);

  EXPECT_EQ(U32(out1), U32(out2));
}

}  // namespace