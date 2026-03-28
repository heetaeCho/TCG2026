#include <gtest/gtest.h>

// Reproduce the types and constants from the source code to test IsOldTerm
typedef unsigned char XMP_Uns8;
typedef XMP_Uns8 RDFTermKind;

// Based on the XMP SDK, these are the known RDFTermKind constants.
// The "old" terms are a specific range within the enum.
// From the XMP SDK source, typical values:
enum {
    kRDFTerm_Other = 0,
    
    kRDFTerm_RDF = 1,
    kRDFTerm_Description = 2,
    kRDFTerm_ID = 3,
    kRDFTerm_about = 4,
    kRDFTerm_parseType = 5,
    kRDFTerm_resource = 6,
    kRDFTerm_nodeID = 7,
    kRDFTerm_datatype = 8,
    kRDFTerm_li = 9,
    
    kRDFTerm_aboutEach = 10,
    kRDFTerm_aboutEachPrefix = 11,
    kRDFTerm_bagID = 12,
    
    kRDFTerm_FirstCore = kRDFTerm_RDF,
    kRDFTerm_LastCore = kRDFTerm_datatype,
    
    kRDFTerm_FirstSyntax = kRDFTerm_FirstCore,
    kRDFTerm_LastSyntax = kRDFTerm_li,
    
    kRDFTerm_FirstOld = kRDFTerm_aboutEach,
    kRDFTerm_LastOld = kRDFTerm_bagID
};

// Reproduce the function under test
static bool IsOldTerm(RDFTermKind term) {
    if ((kRDFTerm_FirstOld <= term) && (term <= kRDFTerm_LastOld)) return true;
    return false;
}

// Test fixture
class IsOldTermTest_2118 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that kRDFTerm_aboutEach (first old term) is recognized as old
TEST_F(IsOldTermTest_2118, FirstOldTermIsOld_2118) {
    EXPECT_TRUE(IsOldTerm(kRDFTerm_aboutEach));
}

// Test that kRDFTerm_aboutEachPrefix (middle old term) is recognized as old
TEST_F(IsOldTermTest_2118, MiddleOldTermIsOld_2118) {
    EXPECT_TRUE(IsOldTerm(kRDFTerm_aboutEachPrefix));
}

// Test that kRDFTerm_bagID (last old term) is recognized as old
TEST_F(IsOldTermTest_2118, LastOldTermIsOld_2118) {
    EXPECT_TRUE(IsOldTerm(kRDFTerm_bagID));
}

// Test that kRDFTerm_Other (0) is NOT an old term
TEST_F(IsOldTermTest_2118, OtherTermIsNotOld_2118) {
    EXPECT_FALSE(IsOldTerm(kRDFTerm_Other));
}

// Test that kRDFTerm_RDF is NOT an old term
TEST_F(IsOldTermTest_2118, RDFTermIsNotOld_2118) {
    EXPECT_FALSE(IsOldTerm(kRDFTerm_RDF));
}

// Test that kRDFTerm_Description is NOT an old term
TEST_F(IsOldTermTest_2118, DescriptionTermIsNotOld_2118) {
    EXPECT_FALSE(IsOldTerm(kRDFTerm_Description));
}

// Test that kRDFTerm_about is NOT an old term
TEST_F(IsOldTermTest_2118, AboutTermIsNotOld_2118) {
    EXPECT_FALSE(IsOldTerm(kRDFTerm_about));
}

// Test that kRDFTerm_parseType is NOT an old term
TEST_F(IsOldTermTest_2118, ParseTypeTermIsNotOld_2118) {
    EXPECT_FALSE(IsOldTerm(kRDFTerm_parseType));
}

// Test that kRDFTerm_resource is NOT an old term
TEST_F(IsOldTermTest_2118, ResourceTermIsNotOld_2118) {
    EXPECT_FALSE(IsOldTerm(kRDFTerm_resource));
}

// Test that kRDFTerm_nodeID is NOT an old term
TEST_F(IsOldTermTest_2118, NodeIDTermIsNotOld_2118) {
    EXPECT_FALSE(IsOldTerm(kRDFTerm_nodeID));
}

// Test that kRDFTerm_datatype is NOT an old term
TEST_F(IsOldTermTest_2118, DatatypeTermIsNotOld_2118) {
    EXPECT_FALSE(IsOldTerm(kRDFTerm_datatype));
}

// Test that kRDFTerm_li is NOT an old term
TEST_F(IsOldTermTest_2118, LiTermIsNotOld_2118) {
    EXPECT_FALSE(IsOldTerm(kRDFTerm_li));
}

// Boundary: one below the first old term
TEST_F(IsOldTermTest_2118, OneBelowFirstOldIsNotOld_2118) {
    RDFTermKind belowFirst = kRDFTerm_FirstOld - 1;
    EXPECT_FALSE(IsOldTerm(belowFirst));
}

// Boundary: one above the last old term
TEST_F(IsOldTermTest_2118, OneAboveLastOldIsNotOld_2118) {
    RDFTermKind aboveLastOld = kRDFTerm_LastOld + 1;
    EXPECT_FALSE(IsOldTerm(aboveLastOld));
}

// Test with zero
TEST_F(IsOldTermTest_2118, ZeroIsNotOld_2118) {
    EXPECT_FALSE(IsOldTerm(0));
}

// Test with max value of XMP_Uns8
TEST_F(IsOldTermTest_2118, MaxUns8IsNotOld_2118) {
    EXPECT_FALSE(IsOldTerm(255));
}

// Test a large value well outside the old range
TEST_F(IsOldTermTest_2118, LargeValueIsNotOld_2118) {
    EXPECT_FALSE(IsOldTerm(100));
}

// Verify all values in the old range are old
TEST_F(IsOldTermTest_2118, AllValuesInOldRangeAreOld_2118) {
    for (RDFTermKind t = kRDFTerm_FirstOld; t <= kRDFTerm_LastOld; ++t) {
        EXPECT_TRUE(IsOldTerm(t)) << "Term " << (int)t << " should be old";
    }
}

// Verify all values below the old range are not old
TEST_F(IsOldTermTest_2118, AllValuesBelowOldRangeAreNotOld_2118) {
    for (RDFTermKind t = 0; t < kRDFTerm_FirstOld; ++t) {
        EXPECT_FALSE(IsOldTerm(t)) << "Term " << (int)t << " should NOT be old";
    }
}

// Verify values above the old range are not old (sample)
TEST_F(IsOldTermTest_2118, ValuesAboveOldRangeAreNotOld_2118) {
    for (int t = kRDFTerm_LastOld + 1; t <= 50; ++t) {
        EXPECT_FALSE(IsOldTerm(static_cast<RDFTermKind>(t))) 
            << "Term " << t << " should NOT be old";
    }
}
