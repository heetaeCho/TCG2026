#include <gtest/gtest.h>
#include "CIDFontsWidthsBuilder.h"

// Helper to access SegmentBuilder - we need to figure out how to instantiate it
// Based on the interface, SegmentBuilder is a nested class of CIDFontsWidthsBuilder

using SegmentBuilder = CIDFontsWidthsBuilder::SegmentBuilder;

// Test: First call to accept should always succeed
TEST(SegmentBuilderTest_1509, FirstAcceptAlwaysSucceeds_1509) {
    SegmentBuilder sb;
    EXPECT_TRUE(sb.accept(0, 100));
}

// Test: Sequential indices should be accepted
TEST(SegmentBuilderTest_1509, SequentialIndicesAccepted_1509) {
    SegmentBuilder sb;
    EXPECT_TRUE(sb.accept(0, 100));
    EXPECT_TRUE(sb.accept(1, 200));
    EXPECT_TRUE(sb.accept(2, 300));
}

// Test: Non-sequential indices should be rejected
TEST(SegmentBuilderTest_1509, NonSequentialIndexRejected_1509) {
    SegmentBuilder sb;
    EXPECT_TRUE(sb.accept(0, 100));
    EXPECT_FALSE(sb.accept(5, 200));
}

// Test: Gap in indices should be rejected
TEST(SegmentBuilderTest_1509, GapInIndicesRejected_1509) {
    SegmentBuilder sb;
    EXPECT_TRUE(sb.accept(10, 100));
    EXPECT_TRUE(sb.accept(11, 200));
    EXPECT_FALSE(sb.accept(13, 300));
}

// Test: First four values with same value (no differentValues)
TEST(SegmentBuilderTest_1509, FirstFourSameValues_1509) {
    SegmentBuilder sb;
    EXPECT_TRUE(sb.accept(0, 500));
    EXPECT_TRUE(sb.accept(1, 500));
    EXPECT_TRUE(sb.accept(2, 500));
    EXPECT_TRUE(sb.accept(3, 500));
}

// Test: After four same values, same value continues to be accepted
TEST(SegmentBuilderTest_1509, SameValuesContinueAfterFour_1509) {
    SegmentBuilder sb;
    EXPECT_TRUE(sb.accept(0, 500));
    EXPECT_TRUE(sb.accept(1, 500));
    EXPECT_TRUE(sb.accept(2, 500));
    EXPECT_TRUE(sb.accept(3, 500));
    EXPECT_TRUE(sb.accept(4, 500));
    EXPECT_TRUE(sb.accept(5, 500));
}

// Test: After four same values, different value is rejected
TEST(SegmentBuilderTest_1509, DifferentValueRejectedAfterFourSame_1509) {
    SegmentBuilder sb;
    EXPECT_TRUE(sb.accept(0, 500));
    EXPECT_TRUE(sb.accept(1, 500));
    EXPECT_TRUE(sb.accept(2, 500));
    EXPECT_TRUE(sb.accept(3, 500));
    EXPECT_FALSE(sb.accept(4, 600));
}

// Test: First four values with different values (differentValues = true)
TEST(SegmentBuilderTest_1509, FirstFourDifferentValues_1509) {
    SegmentBuilder sb;
    EXPECT_TRUE(sb.accept(0, 100));
    EXPECT_TRUE(sb.accept(1, 200));
    EXPECT_TRUE(sb.accept(2, 300));
    EXPECT_TRUE(sb.accept(3, 400));
}

// Test: With different values, values are accepted until 3 unique from end
TEST(SegmentBuilderTest_1509, DifferentValuesAcceptedUntilThreeUniqueFromEnd_1509) {
    SegmentBuilder sb;
    EXPECT_TRUE(sb.accept(0, 100));
    EXPECT_TRUE(sb.accept(1, 200));
    EXPECT_TRUE(sb.accept(2, 100));
    EXPECT_TRUE(sb.accept(3, 200));
    // After 4 values with differentValues=true, adding more values
    EXPECT_TRUE(sb.accept(4, 100));
}

// Test: With different values, rejection when 3 unique elements from end
TEST(SegmentBuilderTest_1509, DifferentValuesRejectedThreeUniqueFromEnd_1509) {
    SegmentBuilder sb;
    EXPECT_TRUE(sb.accept(0, 100));
    EXPECT_TRUE(sb.accept(1, 200));
    EXPECT_TRUE(sb.accept(2, 300));
    EXPECT_TRUE(sb.accept(3, 300));
    // Now values end in [... 300, 300]. Adding 300 => uniqueElementsFromEnd(300) should be checked
    // The sequence is 100, 200, 300, 300. Adding 300 would make last 3: 300, 300, 300 -> 1 unique
    EXPECT_TRUE(sb.accept(4, 300));
}

// Test: differentValues set with two distinct values in first four
TEST(SegmentBuilderTest_1509, TwoDistinctInFirstFour_1509) {
    SegmentBuilder sb;
    EXPECT_TRUE(sb.accept(0, 100));
    EXPECT_TRUE(sb.accept(1, 200));
    EXPECT_TRUE(sb.accept(2, 100));
    EXPECT_TRUE(sb.accept(3, 100));
}

// Test: Starting with arbitrary index
TEST(SegmentBuilderTest_1509, ArbitraryStartIndex_1509) {
    SegmentBuilder sb;
    EXPECT_TRUE(sb.accept(100, 500));
    EXPECT_TRUE(sb.accept(101, 500));
    EXPECT_TRUE(sb.accept(102, 500));
}

// Test: Starting with negative index
TEST(SegmentBuilderTest_1509, NegativeStartIndex_1509) {
    SegmentBuilder sb;
    EXPECT_TRUE(sb.accept(-5, 100));
    EXPECT_TRUE(sb.accept(-4, 200));
}

// Test: Single value accepted
TEST(SegmentBuilderTest_1509, SingleValueAccepted_1509) {
    SegmentBuilder sb;
    EXPECT_TRUE(sb.accept(0, 42));
}

// Test: Two values, second with wrong index
TEST(SegmentBuilderTest_1509, SecondValueWrongIndex_1509) {
    SegmentBuilder sb;
    EXPECT_TRUE(sb.accept(0, 42));
    EXPECT_FALSE(sb.accept(0, 42)); // same index, not index+1
}

// Test: Boundary - exactly 4 different values, then 5th triggers uniqueElementsFromEnd check
TEST(SegmentBuilderTest_1509, FifthValueAfterFourDifferent_1509) {
    SegmentBuilder sb;
    EXPECT_TRUE(sb.accept(0, 100));
    EXPECT_TRUE(sb.accept(1, 200));
    EXPECT_TRUE(sb.accept(2, 300));
    EXPECT_TRUE(sb.accept(3, 400));
    // Now differentValues=true, size>=4
    // uniqueElementsFromEnd(500) checks unique elements from end
    // Values: 100, 200, 300, 400. From end: 400, 300, 200 -> 3 unique already
    // Adding 500 would make uniqueElementsFromEnd(500) >= 3 -> rejected
    EXPECT_FALSE(sb.accept(4, 500));
}

// Test: After four different, same as last is accepted
TEST(SegmentBuilderTest_1509, AfterFourDifferentSameAsLastAccepted_1509) {
    SegmentBuilder sb;
    EXPECT_TRUE(sb.accept(0, 100));
    EXPECT_TRUE(sb.accept(1, 200));
    EXPECT_TRUE(sb.accept(2, 300));
    EXPECT_TRUE(sb.accept(3, 300));
    // uniqueElementsFromEnd(300): from end 300, 300 -> 1 unique, < 3
    EXPECT_TRUE(sb.accept(4, 300));
}

// Test: Many same values extended
TEST(SegmentBuilderTest_1509, ManySameValues_1509) {
    SegmentBuilder sb;
    for (int i = 0; i < 100; i++) {
        EXPECT_TRUE(sb.accept(i, 999));
    }
}

// Test: differentValues with repeating pattern that avoids 3 unique from end
TEST(SegmentBuilderTest_1509, RepeatingPatternAvoidingThreeUnique_1509) {
    SegmentBuilder sb;
    EXPECT_TRUE(sb.accept(0, 100));
    EXPECT_TRUE(sb.accept(1, 200));
    EXPECT_TRUE(sb.accept(2, 100));
    EXPECT_TRUE(sb.accept(3, 200));
    // differentValues=true. Values: 100,200,100,200
    // uniqueElementsFromEnd(100): from end: 200,100 -> with new 100 => 100,200,100 -> 2 unique < 3
    EXPECT_TRUE(sb.accept(4, 100));
    // Values: 100,200,100,200,100
    // uniqueElementsFromEnd(200): from end: 100,200,100 -> with new 200 => 200,100,200,100 -> 2 unique
    EXPECT_TRUE(sb.accept(5, 200));
}

// Test: Three distinct values at end causes rejection
TEST(SegmentBuilderTest_1509, ThreeDistinctValuesAtEndCausesRejection_1509) {
    SegmentBuilder sb;
    EXPECT_TRUE(sb.accept(0, 100));
    EXPECT_TRUE(sb.accept(1, 200));
    EXPECT_TRUE(sb.accept(2, 100));
    EXPECT_TRUE(sb.accept(3, 200));
    // differentValues=true. Adding 300:
    // From end: 200, 100, 200. uniqueElementsFromEnd(300): 300 is new, 200 is different, 100 is different -> 3 unique
    EXPECT_FALSE(sb.accept(4, 300));
}

// Test: Zero values
TEST(SegmentBuilderTest_1509, ZeroValues_1509) {
    SegmentBuilder sb;
    EXPECT_TRUE(sb.accept(0, 0));
    EXPECT_TRUE(sb.accept(1, 0));
    EXPECT_TRUE(sb.accept(2, 0));
    EXPECT_TRUE(sb.accept(3, 0));
    EXPECT_TRUE(sb.accept(4, 0));
}

// Test: Large index values
TEST(SegmentBuilderTest_1509, LargeIndexValues_1509) {
    SegmentBuilder sb;
    EXPECT_TRUE(sb.accept(1000000, 42));
    EXPECT_TRUE(sb.accept(1000001, 42));
}

// Test: Negative values
TEST(SegmentBuilderTest_1509, NegativeValues_1509) {
    SegmentBuilder sb;
    EXPECT_TRUE(sb.accept(0, -100));
    EXPECT_TRUE(sb.accept(1, -200));
    EXPECT_TRUE(sb.accept(2, -100));
    EXPECT_TRUE(sb.accept(3, -200));
}

// Test: Fresh builder rejects non-sequential after first
TEST(SegmentBuilderTest_1509, RejectNonSequentialAfterFirst_1509) {
    SegmentBuilder sb;
    EXPECT_TRUE(sb.accept(5, 100));
    EXPECT_TRUE(sb.accept(6, 100));
    EXPECT_FALSE(sb.accept(8, 100));
}

// Test: Mixed values within first four where first != later
TEST(SegmentBuilderTest_1509, MixedFirstFourFirstDiffers_1509) {
    SegmentBuilder sb;
    EXPECT_TRUE(sb.accept(0, 100));
    EXPECT_TRUE(sb.accept(1, 100));
    EXPECT_TRUE(sb.accept(2, 100));
    EXPECT_TRUE(sb.accept(3, 200)); // differentValues becomes true since front(100) != 200
}

// Test: After differentValues set at position 3, continuing with same value
TEST(SegmentBuilderTest_1509, DifferentSetAtThirdThenContinue_1509) {
    SegmentBuilder sb;
    EXPECT_TRUE(sb.accept(0, 100));
    EXPECT_TRUE(sb.accept(1, 100));
    EXPECT_TRUE(sb.accept(2, 100));
    EXPECT_TRUE(sb.accept(3, 200));
    // differentValues=true now, values: 100,100,100,200
    // Adding 200: from end 200 -> uniqueElementsFromEnd(200) = 1 < 3
    EXPECT_TRUE(sb.accept(4, 200));
}

// Test: Exactly at boundary - two unique from end should still accept
TEST(SegmentBuilderTest_1509, TwoUniqueFromEndAccepts_1509) {
    SegmentBuilder sb;
    EXPECT_TRUE(sb.accept(0, 100));
    EXPECT_TRUE(sb.accept(1, 200));
    EXPECT_TRUE(sb.accept(2, 100));
    EXPECT_TRUE(sb.accept(3, 100));
    // differentValues=true. Values: 100,200,100,100
    // Adding 200: from end: 100,100 -> uniqueElementsFromEnd(200): 200,100 = 2 unique < 3
    EXPECT_TRUE(sb.accept(4, 200));
}
