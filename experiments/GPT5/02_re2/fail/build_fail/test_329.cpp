// File: compile_dotstar_test.cc
#include <gtest/gtest.h>

// Include headers that declare re2::Compiler and its public API used below.
#include "re2/compile.h"   // adjust include path to where Compiler is declared
// If the project uses forward declarations differently, include the appropriate headers.

using re2::Compiler;

namespace {

class CompilerDotStarTest_329 : public ::testing::Test {
protected:
  // For these tests we only need a default-constructible Compiler.
  // We do not touch internal state and treat the implementation as a black box.
  Compiler c_;
};

// [329] Normal operation: DotStar() returns a Frag that can be composed via Cat with Match().
TEST_F(CompilerDotStarTest_329, DotStar_ComposableWithCatAndMatch_329) {
  // Act
  auto dotstar = c_.DotStar();
  auto match1  = c_.Match(1);
  // Compose: Cat should accept the DotStar() Frag.
  EXPECT_NO_THROW({
    (void)c_.Cat(dotstar, match1);
  });
}

// [329] Normal operation: DotStar() can be wrapped with Plus/Quest (greedy & non-greedy paths).
TEST_F(CompilerDotStarTest_329, DotStar_ComposableWithQuantifiers_329) {
  auto dotstar = c_.DotStar();

  EXPECT_NO_THROW({
    (void)c_.Plus(dotstar, /*nongreedy=*/false);
  });
  EXPECT_NO_THROW({
    (void)c_.Plus(dotstar, /*nongreedy=*/true);
  });

  EXPECT_NO_THROW({
    (void)c_.Quest(dotstar, /*nongreedy=*/false);
  });
  EXPECT_NO_THROW({
    (void)c_.Quest(dotstar, /*nongreedy=*/true);
  });

  EXPECT_NO_THROW({
    (void)c_.Star(dotstar, /*nongreedy=*/false);
  });
  EXPECT_NO_THROW({
    (void)c_.Star(dotstar, /*nongreedy=*/true);
  });
}

// [329] Normal operation: DotStar() may be alternated with Nop()/NoMatch() and still compose.
TEST_F(CompilerDotStarTest_329, DotStar_ComposableWithAltAndNopNoMatch_329) {
  auto dotstar = c_.DotStar();
  auto nop     = c_.Nop();
  auto nomatch = c_.NoMatch();

  EXPECT_NO_THROW({
    (void)c_.Alt(dotstar, nop);
  });
  EXPECT_NO_THROW({
    (void)c_.Alt(nop, dotstar);
  });
  EXPECT_NO_THROW({
    (void)c_.Alt(dotstar, nomatch);
  });
  EXPECT_NO_THROW({
    (void)c_.Alt(nomatch, dotstar);
  });
}

// [329] Boundary: DotStar() captured and concatenated multiple times remains composable.
TEST_F(CompilerDotStarTest_329, DotStar_ComposableWithNestedCaptureAndCat_329) {
  auto dotstar = c_.DotStar();
  // Wrap in a couple of captures and concatenate with another simple fragment.
  EXPECT_NO_THROW({
    auto cap1 = c_.Capture(dotstar, /*n=*/1);
    auto cap2 = c_.Capture(cap1, /*n=*/2);
    auto m    = c_.Match(42);
    (void)c_.Cat(cap2, m);
  });
}

// [329] Boundary: Copy of DotStar() remains composable like the original.
TEST_F(CompilerDotStarTest_329, DotStar_CopyIsComposable_329) {
  auto dotstar = c_.DotStar();
  auto copy    = c_.Copy(dotstar);

  EXPECT_NO_THROW({
    (void)c_.Cat(copy, c_.Match(7));
  });
  EXPECT_NO_THROW({
    (void)c_.Alt(copy, c_.Nop());
  });
  EXPECT_NO_THROW({
    (void)c_.Plus(copy, /*nongreedy=*/true);
  });
}

// [329] Sanity: DotStar() can be compared against an independently built
// ByteRange + Star by *using* both in identical compositions.
// We do not assert internal equality of Frags; we only assert both are valid/composable.
TEST_F(CompilerDotStarTest_329, DotStar_BehavesLikeStarOfFullByteRangeInCompositions_329) {
  auto dotstar = c_.DotStar();

  auto full_range = c_.ByteRange(0x00, 0xff, /*foldcase=*/false);
  auto star_full  = c_.Star(full_range, /*nongreedy=*/true);

  // Both should be acceptable to the same combinators.
  EXPECT_NO_THROW({
    (void)c_.Cat(dotstar, c_.Match(1));
    (void)c_.Cat(star_full, c_.Match(1));
  });
  EXPECT_NO_THROW({
    (void)c_.Alt(c_.Nop(), dotstar);
    (void)c_.Alt(c_.Nop(), star_full);
  });
  EXPECT_NO_THROW({
    (void)c_.Plus(dotstar, /*nongreedy=*/false);
    (void)c_.Plus(star_full, /*nongreedy=*/false);
  });
}

// [329] Stress-ish composition: Chain DotStar() with several operations.
// Purpose: ensure no crashes and that public methods accept the returned Frag repeatedly.
TEST_F(CompilerDotStarTest_329, DotStar_ChainedCompositionsRemainValid_329) {
  auto f = c_.DotStar();
  EXPECT_NO_THROW({
    f = c_.Capture(f, 1);
    f = c_.Plus(f, /*nongreedy=*/false);
    f = c_.Quest(f, /*nongreedy=*/true);
    f = c_.Alt(f, c_.Nop());
    f = c_.Cat(f, c_.Match(99));
    // One more copy to ensure it remains usable.
    f = c_.Copy(f);
    (void)f;
  });
}

} // namespace
