// CairoFontEngine_getRef_test_1673.cpp

#include <gtest/gtest.h>

#include <climits>

// Poppler header under test
#include "CairoFontEngine.h"

namespace {

class CairoFontTest_1673 : public ::testing::Test {
protected:
  // Helper that compares Ref in the least-assumptive way used in Poppler:
  // Ref is expected to expose `.num` and `.gen`.
  static void ExpectRefEq(const Ref &expected, const Ref &actual) {
    EXPECT_EQ(expected.num, actual.num);
    EXPECT_EQ(expected.gen, actual.gen);
  }
};

TEST_F(CairoFontTest_1673, GetRefReturnsConstructorRef_1673) {
  Ref inRef;
  inRef.num = 123;
  inRef.gen = 7;

  int dummyFaceStorage = 0;
  int *dummyFace = &dummyFaceStorage;

  CairoFont font(inRef, dummyFace, 0, /*substituteA=*/false, /*printingA=*/false);

  Ref outRef = font.getRef();
  ExpectRefEq(inRef, outRef);
}

TEST_F(CairoFontTest_1673, GetRefIsStableAcrossMultipleCalls_1673) {
  Ref inRef;
  inRef.num = 42;
  inRef.gen = 1;

  int dummyFaceStorage = 0;
  int *dummyFace = &dummyFaceStorage;

  CairoFont font(inRef, dummyFace, 0, /*substituteA=*/true, /*printingA=*/true);

  Ref r1 = font.getRef();
  Ref r2 = font.getRef();
  Ref r3 = font.getRef();

  ExpectRefEq(inRef, r1);
  ExpectRefEq(inRef, r2);
  ExpectRefEq(inRef, r3);
}

TEST_F(CairoFontTest_1673, GetRefHandlesZeroBoundaryValues_1673) {
  Ref inRef;
  inRef.num = 0;
  inRef.gen = 0;

  int dummyFaceStorage = 0;
  int *dummyFace = &dummyFaceStorage;

  CairoFont font(inRef, dummyFace, 0, /*substituteA=*/false, /*printingA=*/true);

  Ref outRef = font.getRef();
  ExpectRefEq(inRef, outRef);
}

TEST_F(CairoFontTest_1673, GetRefHandlesLargeBoundaryValues_1673) {
  Ref inRef;
  inRef.num = INT_MAX;
  inRef.gen = INT_MAX;

  int dummyFaceStorage = 0;
  int *dummyFace = &dummyFaceStorage;

  CairoFont font(inRef, dummyFace, 0, /*substituteA=*/true, /*printingA=*/false);

  Ref outRef = font.getRef();
  ExpectRefEq(inRef, outRef);
}

TEST_F(CairoFontTest_1673, GetRefNotAffectedBySubsequentLocalRefChanges_1673) {
  Ref inRef;
  inRef.num = 9;
  inRef.gen = 2;

  int dummyFaceStorage = 0;
  int *dummyFace = &dummyFaceStorage;

  CairoFont font(inRef, dummyFace, 0, /*substituteA=*/false, /*printingA=*/false);

  // Change the local variable after construction; observable behavior should
  // remain that getRef() returns the Ref associated with the CairoFont object.
  inRef.num = 9999;
  inRef.gen = 8888;

  Ref outRef = font.getRef();

  Ref expectedOriginal;
  expectedOriginal.num = 9;
  expectedOriginal.gen = 2;

  ExpectRefEq(expectedOriginal, outRef);
}

} // namespace