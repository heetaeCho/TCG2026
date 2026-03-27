// Decrypt_rc4DecryptByte_test_1599.cc
#include <gtest/gtest.h>

#include <array>
#include <algorithm>
#include <cstdint>

// NOTE:
// rc4DecryptByte is declared static in Decrypt.cc (internal linkage).
// To test it directly as a black box, we include the implementation file so the
// symbol is in this translation unit.
#include "Decrypt.cc" // ./TestProjects/poppler/poppler/Decrypt.cc

namespace {

using State256 = std::array<unsigned char, 256>;

State256 MakeIdentityState() {
  State256 s{};
  for (int i = 0; i < 256; ++i) s[i] = static_cast<unsigned char>(i);
  return s;
}

// A deterministic permutation of 0..255 (since 73 is coprime with 256).
State256 MakeAffinePermutationState() {
  State256 s{};
  for (int i = 0; i < 256; ++i) {
    s[i] = static_cast<unsigned char>((i * 73 + 41) & 0xFF);
  }
  return s;
}

}  // namespace

TEST(Rc4DecryptByteTest_1599, DeterministicForSameInputs_1599) {
  State256 s1 = MakeAffinePermutationState();
  State256 s2 = s1;

  unsigned char x1 = 17, y1 = 201;
  unsigned char x2 = x1, y2 = y1;

  const unsigned char c = 0x5A;

  const unsigned char out1 = rc4DecryptByte(s1.data(), &x1, &y1, c);
  const unsigned char out2 = rc4DecryptByte(s2.data(), &x2, &y2, c);

  EXPECT_EQ(out1, out2);
  EXPECT_EQ(x1, x2);
  EXPECT_EQ(y1, y2);
  EXPECT_TRUE(std::equal(s1.begin(), s1.end(), s2.begin()));
}

TEST(Rc4DecryptByteTest_1599, StateEvolutionIndependentOfInputByte_1599) {
  // Observable behavior we can validate without knowing internals:
  // For the same initial (state,x,y), changing 'c' should not change the
  // post-call (state,x,y) if 'c' is only used to produce the return byte.
  State256 sA = MakeAffinePermutationState();
  State256 sB = sA;

  unsigned char xA = 33, yA = 44;
  unsigned char xB = xA, yB = yA;

  const unsigned char c1 = 0x00;
  const unsigned char c2 = 0xFF;

  const unsigned char out1 = rc4DecryptByte(sA.data(), &xA, &yA, c1);
  const unsigned char out2 = rc4DecryptByte(sB.data(), &xB, &yB, c2);

  EXPECT_EQ(xA, xB);
  EXPECT_EQ(yA, yB);
  EXPECT_TRUE(std::equal(sA.begin(), sA.end(), sB.begin()));

  // Metamorphic relation (observable): out1 ^ out2 should match c1 ^ c2
  // when starting from identical initial conditions.
  EXPECT_EQ(static_cast<unsigned char>(out1 ^ out2),
            static_cast<unsigned char>(c1 ^ c2));
}

TEST(Rc4DecryptByteTest_1599, XorSymmetryDecryptsWhatWasEncrypted_1599) {
  // Using the same initial (state,x,y), applying the function to a plaintext
  // yields a ciphertext, and applying again (from the same initial state) to
  // that ciphertext should yield the original plaintext.
  const unsigned char plaintext = 0xC3;

  State256 sEnc = MakeAffinePermutationState();
  State256 sDec = sEnc;

  unsigned char xEnc = 7, yEnc = 9;
  unsigned char xDec = xEnc, yDec = yEnc;

  const unsigned char ciphertext = rc4DecryptByte(sEnc.data(), &xEnc, &yEnc, plaintext);
  const unsigned char recovered  = rc4DecryptByte(sDec.data(), &xDec, &yDec, ciphertext);

  EXPECT_EQ(recovered, plaintext);

  // Post-call evolution should match between the two runs (same starting state).
  EXPECT_EQ(xEnc, xDec);
  EXPECT_EQ(yEnc, yDec);
  EXPECT_TRUE(std::equal(sEnc.begin(), sEnc.end(), sDec.begin()));
}

TEST(Rc4DecryptByteTest_1599, BoundaryWrapWhenXIs255_1599) {
  // Boundary condition: x starts at 255 (max unsigned char).
  // Observable: x must remain a byte value; we specifically validate wrap to 0
  // since the function exposes x as an in/out parameter.
  State256 s = MakeIdentityState();

  unsigned char x = 255;
  unsigned char y = 0;

  (void)rc4DecryptByte(s.data(), &x, &y, 0x12);

  EXPECT_EQ(x, static_cast<unsigned char>(0));  // wrap-around boundary check
  // y must remain a byte; check it's within [0,255] by type and a sanity compare.
  EXPECT_LE(y, static_cast<unsigned char>(255));
}

TEST(Rc4DecryptByteTest_1599, CanMutateStateWithNonTrivialInputs_1599) {
  // We don't assume *how* the state mutates, only that mutation is possible
  // and observable through the caller-provided state buffer.
  State256 s = MakeIdentityState();
  const State256 before = s;

  unsigned char x = 1;   // choose values that are unlikely to be a no-op on identity
  unsigned char y = 1;
  (void)rc4DecryptByte(s.data(), &x, &y, 0x00);

  // Either the state changes or (x,y) changes (or both). We assert at least one
  // visible change occurred.
  const bool state_changed = !std::equal(s.begin(), s.end(), before.begin());
  const bool xy_changed = (x != static_cast<unsigned char>(1)) || (y != static_cast<unsigned char>(1));

  EXPECT_TRUE(state_changed || xy_changed);
}