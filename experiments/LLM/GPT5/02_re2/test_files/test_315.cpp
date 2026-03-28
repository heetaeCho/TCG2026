// File: re2_add_80_10ffff_test.cc
#include "gtest/gtest.h"

// If your project exposes the Compiler header differently, adjust this include.
#include "re2/compile.h"

namespace re2 {

class Add_80_10ffff_Test_315 : public ::testing::Test {
protected:
  Compiler c_; // default-constructed; we treat reversed_ as whatever default is
               // (we don't inspect or modify private state).
};

// Verifies that calling Add_80_10ffff registers/caches the three UTF-8
// lead-byte ranges (with their continuation suffix chains) that cover
// U+0080..U+10FFFF in the *default* (non-reversed) flow.
// We only assert through IsCachedRuneByteSuffix on publicly obtained ids.
TEST_F(Add_80_10ffff_Test_315, NonReversed_CachesExpectedTopChains_315) {
  // Build the exact public ids that Add_80_10ffff is expected to AddSuffix() for
  // in the non-reversed flow (using only public methods).
  int cont1 = c_.UncachedRuneByteSuffix(0x80, 0xBF, /*foldcase=*/false, /*next=*/0);
  int id1   = c_.UncachedRuneByteSuffix(0xC2, 0xDF, /*foldcase=*/false, /*next=*/cont1);

  int cont2 = c_.UncachedRuneByteSuffix(0x80, 0xBF, /*foldcase=*/false, /*next=*/cont1);
  int id2   = c_.UncachedRuneByteSuffix(0xE0, 0xEF, /*foldcase=*/false, /*next=*/cont2);

  int cont3 = c_.UncachedRuneByteSuffix(0x80, 0xBF, /*foldcase=*/false, /*next=*/cont2);
  int id3   = c_.UncachedRuneByteSuffix(0xF0, 0xF4, /*foldcase=*/false, /*next=*/cont3);

  // Before calling Add_80_10ffff, these shouldn't be marked cached yet.
  // (We don't assume *which* ids the implementation caches implicitly;
  // we only check the exact ids that Add_80_10ffff documents via its interface.)
  EXPECT_FALSE(c_.IsCachedRuneByteSuffix(id1));
  EXPECT_FALSE(c_.IsCachedRuneByteSuffix(id2));
  EXPECT_FALSE(c_.IsCachedRuneByteSuffix(id3));

  // Call the method under test.
  c_.Add_80_10ffff();

  // Afterward, those exact ids should be cached/registered.
  EXPECT_TRUE(c_.IsCachedRuneByteSuffix(id1));
  EXPECT_TRUE(c_.IsCachedRuneByteSuffix(id2));
  EXPECT_TRUE(c_.IsCachedRuneByteSuffix(id3));

  // Sanity: unrelated ASCII single-byte range should not become cached by this call.
  // (This serves as a negative control using only public API.)
  int ascii_id = c_.UncachedRuneByteSuffix(0x00, 0x7F, /*foldcase=*/false, /*next=*/0);
  EXPECT_FALSE(c_.IsCachedRuneByteSuffix(ascii_id));
}

// Calling Add_80_10ffff() multiple times should be safe and keep the same ids cached.
// We don't assert internal counts; only that the observable "cached" state persists.
TEST_F(Add_80_10ffff_Test_315, NonReversed_IdempotentCaching_315) {
  // Build ids (publicly).
  int cont1 = c_.UncachedRuneByteSuffix(0x80, 0xBF, false, 0);
  int id1   = c_.UncachedRuneByteSuffix(0xC2, 0xDF, false, cont1);

  int cont2 = c_.UncachedRuneByteSuffix(0x80, 0xBF, false, cont1);
  int id2   = c_.UncachedRuneByteSuffix(0xE0, 0xEF, false, cont2);

  int cont3 = c_.UncachedRuneByteSuffix(0x80, 0xBF, false, cont2);
  int id3   = c_.UncachedRuneByteSuffix(0xF0, 0xF4, false, cont3);

  // First call: establishes caching.
  c_.Add_80_10ffff();
  EXPECT_TRUE(c_.IsCachedRuneByteSuffix(id1));
  EXPECT_TRUE(c_.IsCachedRuneByteSuffix(id2));
  EXPECT_TRUE(c_.IsCachedRuneByteSuffix(id3));

  // Second call: should not break or un-cache anything.
  c_.Add_80_10ffff();
  EXPECT_TRUE(c_.IsCachedRuneByteSuffix(id1));
  EXPECT_TRUE(c_.IsCachedRuneByteSuffix(id2));
  EXPECT_TRUE(c_.IsCachedRuneByteSuffix(id3));
}

// Basic boundary-style sanity: the public ids we construct for the three chains
// should be valid (non-negative) and remain valid after Add_80_10ffff().
TEST_F(Add_80_10ffff_Test_315, NonReversed_PublicIdsRemainValid_315) {
  int cont1 = c_.UncachedRuneByteSuffix(0x80, 0xBF, false, 0);
  int id1   = c_.UncachedRuneByteSuffix(0xC2, 0xDF, false, cont1);
  int cont2 = c_.UncachedRuneByteSuffix(0x80, 0xBF, false, cont1);
  int id2   = c_.UncachedRuneByteSuffix(0xE0, 0xEF, false, cont2);
  int cont3 = c_.UncachedRuneByteSuffix(0x80, 0xBF, false, cont2);
  int id3   = c_.UncachedRuneByteSuffix(0xF0, 0xF4, false, cont3);

  EXPECT_GE(cont1, 0);
  EXPECT_GE(cont2, 0);
  EXPECT_GE(cont3, 0);
  EXPECT_GE(id1, 0);
  EXPECT_GE(id2, 0);
  EXPECT_GE(id3, 0);

  c_.Add_80_10ffff(); // should not invalidate ids

  // Re-check cached state as an observable postcondition.
  EXPECT_TRUE(c_.IsCachedRuneByteSuffix(id1));
  EXPECT_TRUE(c_.IsCachedRuneByteSuffix(id2));
  EXPECT_TRUE(c_.IsCachedRuneByteSuffix(id3));
}

// Smoke test: Method should be safe to call even after other unrelated tree nodes exist.
// This exercises a slightly different public graph shape before calling the method.
TEST_F(Add_80_10ffff_Test_315, NonReversed_SmokeWithUnrelatedNodes_315) {
  // Create some unrelated suffix chain via the public API.
  int x1 = c_.UncachedRuneByteSuffix(0x90, 0x9F, false, 0);
  int x2 = c_.UncachedRuneByteSuffix(0xA0, 0xAF, false, x1);
  EXPECT_GE(x1, 0);
  EXPECT_GE(x2, 0);
  EXPECT_FALSE(c_.IsCachedRuneByteSuffix(x2));

  // Now call the method under test; it should not interfere with unrelated ids.
  c_.Add_80_10ffff();

  // The known three chains should be cached.
  int cont1 = c_.UncachedRuneByteSuffix(0x80, 0xBF, false, 0);
  int id1   = c_.UncachedRuneByteSuffix(0xC2, 0xDF, false, cont1);
  int cont2 = c_.UncachedRuneByteSuffix(0x80, 0xBF, false, cont1);
  int id2   = c_.UncachedRuneByteSuffix(0xE0, 0xEF, false, cont2);
  int cont3 = c_.UncachedRuneByteSuffix(0x80, 0xBF, false, cont2);
  int id3   = c_.UncachedRuneByteSuffix(0xF0, 0xF4, false, cont3);

  EXPECT_TRUE(c_.IsCachedRuneByteSuffix(id1));
  EXPECT_TRUE(c_.IsCachedRuneByteSuffix(id2));
  EXPECT_TRUE(c_.IsCachedRuneByteSuffix(id3));

  // The unrelated chain should still be uncached (no assumptions about internal caching policy
  // beyond what Add_80_10ffff promises to cache). If your implementation *does* end up caching
  // intermediate nodes, relax this assertion accordingly.
  EXPECT_FALSE(c_.IsCachedRuneByteSuffix(x2));
}

}  // namespace re2
