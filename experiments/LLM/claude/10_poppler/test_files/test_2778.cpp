#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers
// Based on the provided code, we need to work with Ref and SplashOutFontFileID

// Forward declarations and minimal includes based on the provided interface
#include "poppler/Object.h"
#include "splash/SplashFontFileID.h"

// Since SplashOutFontFileID is defined in SplashOutputDev.cc (not a header),
// we need to include the header that exposes it, or recreate the test-visible interface.
// In practice, the class may be accessible through SplashOutputDev.h
#include "poppler/SplashOutputDev.h"

// If SplashOutFontFileID is not exposed through a header (it's in .cc file),
// we may need to include the .cc or have a test-specific exposure.
// For testing purposes, we assume access to the class.

class SplashOutFontFileIDTest_2778 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Construction with a valid Ref
TEST_F(SplashOutFontFileIDTest_2778, ConstructWithValidRef_2778) {
    Ref r;
    r.num = 10;
    r.gen = 0;
    SplashOutFontFileID id(&r);
    // Object should be constructible without throwing
    SUCCEED();
}

// Test: matches returns true for same Ref values
TEST_F(SplashOutFontFileIDTest_2778, MatchesReturnsTrueForSameRef_2778) {
    Ref r1;
    r1.num = 42;
    r1.gen = 3;

    SplashOutFontFileID id1(&r1);
    SplashOutFontFileID id2(&r1);

    EXPECT_TRUE(id1.matches(id2));
}

// Test: matches returns true symmetrically
TEST_F(SplashOutFontFileIDTest_2778, MatchesIsSymmetric_2778) {
    Ref r;
    r.num = 100;
    r.gen = 5;

    SplashOutFontFileID id1(&r);
    SplashOutFontFileID id2(&r);

    EXPECT_TRUE(id1.matches(id2));
    EXPECT_TRUE(id2.matches(id1));
}

// Test: matches returns false for different num
TEST_F(SplashOutFontFileIDTest_2778, MatchesReturnsFalseForDifferentNum_2778) {
    Ref r1;
    r1.num = 10;
    r1.gen = 0;

    Ref r2;
    r2.num = 20;
    r2.gen = 0;

    SplashOutFontFileID id1(&r1);
    SplashOutFontFileID id2(&r2);

    EXPECT_FALSE(id1.matches(id2));
}

// Test: matches returns false for different gen
TEST_F(SplashOutFontFileIDTest_2778, MatchesReturnsFalseForDifferentGen_2778) {
    Ref r1;
    r1.num = 10;
    r1.gen = 0;

    Ref r2;
    r2.num = 10;
    r2.gen = 1;

    SplashOutFontFileID id1(&r1);
    SplashOutFontFileID id2(&r2);

    EXPECT_FALSE(id1.matches(id2));
}

// Test: matches returns false for completely different Refs
TEST_F(SplashOutFontFileIDTest_2778, MatchesReturnsFalseForCompletelyDifferentRefs_2778) {
    Ref r1;
    r1.num = 1;
    r1.gen = 2;

    Ref r2;
    r2.num = 3;
    r2.gen = 4;

    SplashOutFontFileID id1(&r1);
    SplashOutFontFileID id2(&r2);

    EXPECT_FALSE(id1.matches(id2));
}

// Test: Construction with zero Ref values
TEST_F(SplashOutFontFileIDTest_2778, ConstructWithZeroRef_2778) {
    Ref r;
    r.num = 0;
    r.gen = 0;

    SplashOutFontFileID id(&r);
    
    // Two IDs with zero refs should match
    SplashOutFontFileID id2(&r);
    EXPECT_TRUE(id.matches(id2));
}

// Test: Construction with negative Ref values (boundary)
TEST_F(SplashOutFontFileIDTest_2778, ConstructWithNegativeRef_2778) {
    Ref r;
    r.num = -1;
    r.gen = -1;

    SplashOutFontFileID id1(&r);
    SplashOutFontFileID id2(&r);

    EXPECT_TRUE(id1.matches(id2));
}

// Test: Negative num doesn't match positive num
TEST_F(SplashOutFontFileIDTest_2778, NegativeNumDoesNotMatchPositiveNum_2778) {
    Ref r1;
    r1.num = -1;
    r1.gen = 0;

    Ref r2;
    r2.num = 1;
    r2.gen = 0;

    SplashOutFontFileID id1(&r1);
    SplashOutFontFileID id2(&r2);

    EXPECT_FALSE(id1.matches(id2));
}

// Test: Large Ref values
TEST_F(SplashOutFontFileIDTest_2778, LargeRefValues_2778) {
    Ref r;
    r.num = 999999;
    r.gen = 999999;

    SplashOutFontFileID id1(&r);
    SplashOutFontFileID id2(&r);

    EXPECT_TRUE(id1.matches(id2));
}

// Test: matches with self
TEST_F(SplashOutFontFileIDTest_2778, MatchesWithSelf_2778) {
    Ref r;
    r.num = 7;
    r.gen = 2;

    SplashOutFontFileID id(&r);

    EXPECT_TRUE(id.matches(id));
}

// Test: Copies Ref by value (modifying original Ref after construction doesn't affect the ID)
TEST_F(SplashOutFontFileIDTest_2778, CopiesRefByValue_2778) {
    Ref r1;
    r1.num = 5;
    r1.gen = 3;

    SplashOutFontFileID id1(&r1);

    // Create a second ID with the same ref values
    Ref r2;
    r2.num = 5;
    r2.gen = 3;
    SplashOutFontFileID id2(&r2);

    // Modify original ref
    r1.num = 999;
    r1.gen = 999;

    // id1 should still match id2 since Ref was copied
    EXPECT_TRUE(id1.matches(id2));
}

// Test: Destruction doesn't cause issues (basic lifecycle)
TEST_F(SplashOutFontFileIDTest_2778, DestructorDoesNotCrash_2778) {
    Ref r;
    r.num = 1;
    r.gen = 0;

    {
        SplashOutFontFileID id(&r);
        // id goes out of scope and destructor is called
    }
    SUCCEED();
}

// Test: Multiple IDs with different Refs are all distinguishable
TEST_F(SplashOutFontFileIDTest_2778, MultipleDistinctIDs_2778) {
    Ref refs[3];
    refs[0].num = 1; refs[0].gen = 0;
    refs[1].num = 2; refs[1].gen = 0;
    refs[2].num = 3; refs[2].gen = 0;

    SplashOutFontFileID id0(&refs[0]);
    SplashOutFontFileID id1(&refs[1]);
    SplashOutFontFileID id2(&refs[2]);

    EXPECT_FALSE(id0.matches(id1));
    EXPECT_FALSE(id0.matches(id2));
    EXPECT_FALSE(id1.matches(id2));

    EXPECT_TRUE(id0.matches(id0));
    EXPECT_TRUE(id1.matches(id1));
    EXPECT_TRUE(id2.matches(id2));
}
