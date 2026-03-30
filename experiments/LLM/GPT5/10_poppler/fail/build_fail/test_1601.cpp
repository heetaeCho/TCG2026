// TEST_ID: 1601
#include <gtest/gtest.h>

#include <cstdint>

// subWord is defined as static inline in Decrypt.cc, so it is not link-visible.
// To test it without re-implementing it, we include the translation unit.
#include "poppler/Decrypt.cc"

class SubWordTest_1601 : public ::testing::Test {};

TEST_F(SubWordTest_1601, SubstitutesAllZeroWord_1601)
{
  const unsigned int in = 0x00000000U;
  // AES S-box[0x00] == 0x63, applied to each byte.
  EXPECT_EQ(subWord(in), 0x63636363U);
}

TEST_F(SubWordTest_1601, SubstitutesAllOnesWord_1601)
{
  const unsigned int in = 0xFFFFFFFFU;
  // AES S-box[0xFF] == 0x16, applied to each byte.
  EXPECT_EQ(subWord(in), 0x16161616U);
}

TEST_F(SubWordTest_1601, SubstitutesIncreasingBytes_1601)
{
  const unsigned int in = 0x01020304U;
  // Expected: [S(01)=7c][S(02)=77][S(03)=7b][S(04)=f2]
  EXPECT_EQ(subWord(in), 0x7C777BF2U);
}

TEST_F(SubWordTest_1601, SubstitutesMixedBytesWord_1601)
{
  const unsigned int in = 0x00112233U;
  // Expected: [S(00)=63][S(11)=82][S(22)=93][S(33)=c3]
  EXPECT_EQ(subWord(in), 0x638293C3U);
}

TEST_F(SubWordTest_1601, SubstitutesArbitraryWordVector_1601)
{
  const unsigned int in = 0xDEADBEEFU;
  // Expected: [S(DE)=1d][S(AD)=95][S(BE)=ae][S(EF)=df]
  EXPECT_EQ(subWord(in), 0x1D95AEDFU);
}

TEST_F(SubWordTest_1601, IsDeterministicAcrossCalls_1601)
{
  const unsigned int in = 0x536F6D65U;
  const unsigned int expected = 0xEDA83C4DU;

  EXPECT_EQ(subWord(in), expected);
  EXPECT_EQ(subWord(in), expected);
  EXPECT_EQ(subWord(in), expected);
}

TEST_F(SubWordTest_1601, BytePositionMatters_1601)
{
  // Same bytes but placed differently should produce different outputs
  // because subWord substitutes each byte in its position.
  const unsigned int in1 = 0x00010203U;
  const unsigned int in2 = 0x01020300U;

  EXPECT_EQ(subWord(in1), 0x637C777BU);
  EXPECT_EQ(subWord(in2), 0x7C777B63U);
  EXPECT_NE(subWord(in1), subWord(in2));
}

TEST_F(SubWordTest_1601, DistinguishesDifferentHighByte_1601)
{
  const unsigned int base = 0x00ABCDEFU;
  const unsigned int changedHigh = 0xFFABCDEFU;

  EXPECT_EQ(subWord(base), 0x6362BDD FU);   // 0x63 (S(00)), then S(AB)=62, S(CD)=bd, S(EF)=df
  EXPECT_EQ(subWord(changedHigh), 0x1662BDD FU); // 0x16 (S(FF)), then same tail
  EXPECT_NE(subWord(base), subWord(changedHigh));
}