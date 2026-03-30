// File: compiler_cached_rune_byte_suffix_test.cc

#include <cstdint>
#include <gtest/gtest.h>

// Include the project's public header for Compiler.
// Adjust the include path if your build uses a different layout.
#include "re2/compile.h"

using re2::Compiler;

class CompilerCachedRuneByteSuffixTest_306 : public ::testing::Test {
protected:
    Compiler c_;
    // Convenience wrapper to keep call sites short/readable.
    int Call(uint8_t lo, uint8_t hi, bool foldcase, int next) {
        return c_.CachedRuneByteSuffix(lo, hi, foldcase, next);
    }
};

// [Normal] Repeating the exact same arguments should return the same id
// (cache hit on the second call).
TEST_F(CompilerCachedRuneByteSuffixTest_306, SameArgs_ReturnsSameId_306) {
    const uint8_t lo = 0x41;   // 'A'
    const uint8_t hi = 0x5A;   // 'Z'
    const bool fold = false;
    const int next = 123;

    int first = Call(lo, hi, fold, next);
    int second = Call(lo, hi, fold, next);

    EXPECT_EQ(first, second) << "Cached call with identical args must be stable.";
}

// [Boundary] Single-byte boundary (lo == hi) remains stable across calls.
TEST_F(CompilerCachedRuneByteSuffixTest_306, SingleByteRange_IsStable_306) {
    const uint8_t b = 0x00;    // Lowest possible byte
    const bool fold = false;
    const int next = 0;

    int first = Call(b, b, fold, next);
    int second = Call(b, b, fold, next);

    EXPECT_EQ(first, second);
}

// [Boundary] Full Latin-1 span stays stable across repeated calls.
TEST_F(CompilerCachedRuneByteSuffixTest_306, FullLatin1Range_IsStable_306) {
    const uint8_t lo = 0x00;
    const uint8_t hi = 0xFF;
    const bool fold = true;    // exercise the foldcase branch as part of the key
    const int next = -1;       // arbitrary sentinel-ish next

    int first = Call(lo, hi, fold, next);
    int second = Call(lo, hi, fold, next);

    EXPECT_EQ(first, second);
}

// [Normal] Changing the 'next' parameter defines a different lookup key,
// but each key remains internally stable across repeated calls.
// (We do not assert cross-key inequality; we only assert per-key stability.)
TEST_F(CompilerCachedRuneByteSuffixTest_306, DifferentNext_PerKeyStability_306) {
    const uint8_t lo = 0x61;   // 'a'
    const uint8_t hi = 0x7A;   // 'z'
    const bool fold = true;

    int id_next_1_first = Call(lo, hi, fold, /*next=*/1);
    int id_next_2_first = Call(lo, hi, fold, /*next=*/2);

    // Interleave to ensure cache lookups don’t interfere.
    int id_next_1_second = Call(lo, hi, fold, /*next=*/1);
    int id_next_2_second = Call(lo, hi, fold, /*next=*/2);

    EXPECT_EQ(id_next_1_first, id_next_1_second);
    EXPECT_EQ(id_next_2_first, id_next_2_second);
}

// [Normal] Changing foldcase defines a different lookup key,
// but each key remains stable across repeated calls.
TEST_F(CompilerCachedRuneByteSuffixTest_306, DifferentFoldcase_PerKeyStability_306) {
    const uint8_t lo = 0x41;   // 'A'
    const uint8_t hi = 0x5A;   // 'Z'
    const int next = 42;

    int id_fold_false_first = Call(lo, hi, /*foldcase=*/false, next);
    int id_fold_true_first  = Call(lo, hi, /*foldcase=*/true,  next);

    // Interleave and re-check stability per key.
    int id_fold_true_second  = Call(lo, hi, /*foldcase=*/true,  next);
    int id_fold_false_second = Call(lo, hi, /*foldcase=*/false, next);

    EXPECT_EQ(id_fold_false_first, id_fold_false_second);
    EXPECT_EQ(id_fold_true_first,  id_fold_true_second);
}

// [Normal] Using multiple distinct (lo, hi) ranges in an interleaved sequence
// preserves stability for each individual key.
// (Again, we do not assert cross-key inequality.)
TEST_F(CompilerCachedRuneByteSuffixTest_306, MultipleKeys_InterleavedCallsRemainStable_306) {
    struct Key { uint8_t lo, hi; bool fold; int next; };
    const Key keys[] = {
        {0x30, 0x39, false, 10},   // '0'-'9'
        {0x41, 0x46, false, 20},   // 'A'-'F'
        {0x61, 0x66, true,  30},   // 'a'-'f' with foldcase
    };

    int first_ids[3];
    int second_ids[3];

    // First pass: populate cache entries for each key.
    for (int i = 0; i < 3; ++i) {
        first_ids[i] = Call(keys[i].lo, keys[i].hi, keys[i].fold, keys[i].next);
    }

    // Interleave: call them in a different order.
    second_ids[1] = Call(keys[1].lo, keys[1].hi, keys[1].fold, keys[1].next);
    second_ids[0] = Call(keys[0].lo, keys[0].hi, keys[0].fold, keys[0].next);
    second_ids[2] = Call(keys[2].lo, keys[2].hi, keys[2].fold, keys[2].next);

    for (int i = 0; i < 3; ++i) {
        EXPECT_EQ(first_ids[i], second_ids[i]) << "Key index " << i << " must be stable.";
    }
}

// [Edge Handling] hi less than lo: we avoid asserting behavior for invalid ranges.
// We only verify that, whatever the function returns for a given tuple, it is
// stable for identical inputs (still an observable contract of the cache wrapper).
TEST_F(CompilerCachedRuneByteSuffixTest_306, PossiblyInvalidRange_StillStablePerKey_306) {
    const uint8_t lo = 0x10;
    const uint8_t hi = 0x0F; // hi < lo (intentionally)
    const bool fold = false;
    const int next = 7;

    int first = Call(lo, hi, fold, next);
    int second = Call(lo, hi, fold, next);

    EXPECT_EQ(first, second);
}
