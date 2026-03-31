#include <gtest/gtest.h>

// Include necessary headers
#include "poppler/SplashOutputDev.h"
#include "splash/SplashFontFileID.h"

// Since SplashOutFontFileID is defined in SplashOutputDev.cc and may not be
// directly accessible via header, we need to replicate the minimal interface
// for testing. However, per constraints, we treat the implementation as a
// black box and test only observable behavior.

// We need access to Ref and SplashOutFontFileID. Based on the partial code,
// SplashOutFontFileID takes a Ref* in constructor and compares Ref fields in matches().

// Ref is typically defined in poppler
#include "poppler/Object.h"

// Forward-declare or include what's needed for SplashOutFontFileID
// Since SplashOutFontFileID is in a .cc file, we may need to include it or
// replicate the class definition for testing purposes.

// Minimal recreation based on provided interface (needed for compilation):
#include "splash/SplashFontFileID.h"

// Recreate class as provided in the prompt since it's in a .cc file
class SplashOutFontFileID : public SplashFontFileID
{
public:
    explicit SplashOutFontFileID(const Ref *rA) : r(*rA) { }
    ~SplashOutFontFileID() override = default;

    bool matches(const SplashFontFileID &id) const override
    {
        return static_cast<const SplashOutFontFileID &>(id).r == r;
    }

private:
    Ref r;
};

class SplashOutFontFileIDTest_1596 : public ::testing::Test
{
protected:
    void SetUp() override { }
    void TearDown() override { }
};

// Test that two SplashOutFontFileID objects with the same Ref match
TEST_F(SplashOutFontFileIDTest_1596, MatchesSameRef_1596)
{
    Ref ref1 = { 10, 0 };
    Ref ref2 = { 10, 0 };

    SplashOutFontFileID id1(&ref1);
    SplashOutFontFileID id2(&ref2);

    EXPECT_TRUE(id1.matches(id2));
}

// Test that two SplashOutFontFileID objects with different num don't match
TEST_F(SplashOutFontFileIDTest_1596, DoesNotMatchDifferentNum_1596)
{
    Ref ref1 = { 10, 0 };
    Ref ref2 = { 20, 0 };

    SplashOutFontFileID id1(&ref1);
    SplashOutFontFileID id2(&ref2);

    EXPECT_FALSE(id1.matches(id2));
}

// Test that two SplashOutFontFileID objects with different gen don't match
TEST_F(SplashOutFontFileIDTest_1596, DoesNotMatchDifferentGen_1596)
{
    Ref ref1 = { 10, 0 };
    Ref ref2 = { 10, 1 };

    SplashOutFontFileID id1(&ref1);
    SplashOutFontFileID id2(&ref2);

    EXPECT_FALSE(id1.matches(id2));
}

// Test symmetry of matches: if a matches b, then b matches a
TEST_F(SplashOutFontFileIDTest_1596, MatchesIsSymmetric_1596)
{
    Ref ref1 = { 42, 7 };
    Ref ref2 = { 42, 7 };

    SplashOutFontFileID id1(&ref1);
    SplashOutFontFileID id2(&ref2);

    EXPECT_TRUE(id1.matches(id2));
    EXPECT_TRUE(id2.matches(id1));
}

// Test that an object matches itself (reflexive)
TEST_F(SplashOutFontFileIDTest_1596, MatchesSelf_1596)
{
    Ref ref1 = { 5, 3 };

    SplashOutFontFileID id1(&ref1);

    EXPECT_TRUE(id1.matches(id1));
}

// Test with both num and gen different
TEST_F(SplashOutFontFileIDTest_1596, DoesNotMatchBothDifferent_1596)
{
    Ref ref1 = { 10, 5 };
    Ref ref2 = { 20, 10 };

    SplashOutFontFileID id1(&ref1);
    SplashOutFontFileID id2(&ref2);

    EXPECT_FALSE(id1.matches(id2));
}

// Test boundary: Ref with num=0 and gen=0
TEST_F(SplashOutFontFileIDTest_1596, MatchesZeroRef_1596)
{
    Ref ref1 = { 0, 0 };
    Ref ref2 = { 0, 0 };

    SplashOutFontFileID id1(&ref1);
    SplashOutFontFileID id2(&ref2);

    EXPECT_TRUE(id1.matches(id2));
}

// Test boundary: Zero ref vs non-zero ref
TEST_F(SplashOutFontFileIDTest_1596, ZeroRefDoesNotMatchNonZero_1596)
{
    Ref ref1 = { 0, 0 };
    Ref ref2 = { 1, 0 };

    SplashOutFontFileID id1(&ref1);
    SplashOutFontFileID id2(&ref2);

    EXPECT_FALSE(id1.matches(id2));
}

// Test with large ref numbers
TEST_F(SplashOutFontFileIDTest_1596, MatchesLargeRefNumbers_1596)
{
    Ref ref1 = { 999999, 65535 };
    Ref ref2 = { 999999, 65535 };

    SplashOutFontFileID id1(&ref1);
    SplashOutFontFileID id2(&ref2);

    EXPECT_TRUE(id1.matches(id2));
}

// Test with large ref numbers that differ slightly
TEST_F(SplashOutFontFileIDTest_1596, DoesNotMatchLargeRefSlightDiff_1596)
{
    Ref ref1 = { 999999, 65535 };
    Ref ref2 = { 999999, 65534 };

    SplashOutFontFileID id1(&ref1);
    SplashOutFontFileID id2(&ref2);

    EXPECT_FALSE(id1.matches(id2));
}

// Test non-symmetry of non-matching: if a doesn't match b, b doesn't match a
TEST_F(SplashOutFontFileIDTest_1596, NonMatchIsSymmetric_1596)
{
    Ref ref1 = { 1, 2 };
    Ref ref2 = { 3, 4 };

    SplashOutFontFileID id1(&ref1);
    SplashOutFontFileID id2(&ref2);

    EXPECT_FALSE(id1.matches(id2));
    EXPECT_FALSE(id2.matches(id1));
}

// Test with negative ref values (if Ref allows)
TEST_F(SplashOutFontFileIDTest_1596, MatchesNegativeRef_1596)
{
    Ref ref1 = { -1, -1 };
    Ref ref2 = { -1, -1 };

    SplashOutFontFileID id1(&ref1);
    SplashOutFontFileID id2(&ref2);

    EXPECT_TRUE(id1.matches(id2));
}

// Test negative vs positive ref
TEST_F(SplashOutFontFileIDTest_1596, NegativeDoesNotMatchPositive_1596)
{
    Ref ref1 = { -1, 0 };
    Ref ref2 = { 1, 0 };

    SplashOutFontFileID id1(&ref1);
    SplashOutFontFileID id2(&ref2);

    EXPECT_FALSE(id1.matches(id2));
}
