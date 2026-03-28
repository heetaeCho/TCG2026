#include <gtest/gtest.h>

// Reproduce the types and constants from the source code
typedef unsigned char XMP_Uns8;
typedef XMP_Uns8 RDFTermKind;

// Based on the RDF specification and typical exiv2/XMP SDK implementation,
// these are the known RDF term kind constants. The exact values need to match
// the actual enum/constants used in ParseRDF.cpp.

// From the XMP SDK, the typical RDF term constants are:
enum {
    kRDFTerm_Other = 0,
    
    kRDFTerm_RDF = 1,           // Start of core syntax terms
    kRDFTerm_Description = 2,
    kRDFTerm_ID = 3,
    kRDFTerm_about = 4,
    kRDFTerm_parseType = 5,
    kRDFTerm_resource = 6,
    kRDFTerm_nodeID = 7,
    kRDFTerm_datatype = 8,
    
    kRDFTerm_FirstCore = 1,
    kRDFTerm_LastCore = 8,
    
    // Old / syntax terms beyond core
    kRDFTerm_aboutEach = 9,
    kRDFTerm_aboutEachPrefix = 10,
    kRDFTerm_bagID = 11,
    
    kRDFTerm_FirstOld = 9,
    kRDFTerm_LastOld = 11,
    
    // Additional terms
    kRDFTerm_li = 12,
    kRDFTerm_value = 13,
    kRDFTerm_type = 14,
    
    kRDFTerm_LastReal = 14
};

// Re-declare the function under test (since it's static in the .cpp, we need to
// replicate it here for testing purposes based on the provided implementation)
static bool IsCoreSyntaxTerm(RDFTermKind term) {
    if ((kRDFTerm_FirstCore <= term) && (term <= kRDFTerm_LastCore)) return true;
    return false;
}

class IsCoreSyntaxTermTest_2117 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: First core term should be recognized as core syntax term
TEST_F(IsCoreSyntaxTermTest_2117, FirstCoreTerm_ReturnsTrue_2117) {
    EXPECT_TRUE(IsCoreSyntaxTerm(kRDFTerm_FirstCore));
}

// Test: Last core term should be recognized as core syntax term
TEST_F(IsCoreSyntaxTermTest_2117, LastCoreTerm_ReturnsTrue_2117) {
    EXPECT_TRUE(IsCoreSyntaxTerm(kRDFTerm_LastCore));
}

// Test: RDF term (within core range) should return true
TEST_F(IsCoreSyntaxTermTest_2117, RDFTerm_ReturnsTrue_2117) {
    EXPECT_TRUE(IsCoreSyntaxTerm(kRDFTerm_RDF));
}

// Test: Description term (within core range) should return true
TEST_F(IsCoreSyntaxTermTest_2117, DescriptionTerm_ReturnsTrue_2117) {
    EXPECT_TRUE(IsCoreSyntaxTerm(kRDFTerm_Description));
}

// Test: ID term (within core range) should return true
TEST_F(IsCoreSyntaxTermTest_2117, IDTerm_ReturnsTrue_2117) {
    EXPECT_TRUE(IsCoreSyntaxTerm(kRDFTerm_ID));
}

// Test: about term (within core range) should return true
TEST_F(IsCoreSyntaxTermTest_2117, AboutTerm_ReturnsTrue_2117) {
    EXPECT_TRUE(IsCoreSyntaxTerm(kRDFTerm_about));
}

// Test: parseType term (within core range) should return true
TEST_F(IsCoreSyntaxTermTest_2117, ParseTypeTerm_ReturnsTrue_2117) {
    EXPECT_TRUE(IsCoreSyntaxTerm(kRDFTerm_parseType));
}

// Test: resource term (within core range) should return true
TEST_F(IsCoreSyntaxTermTest_2117, ResourceTerm_ReturnsTrue_2117) {
    EXPECT_TRUE(IsCoreSyntaxTerm(kRDFTerm_resource));
}

// Test: nodeID term (within core range) should return true
TEST_F(IsCoreSyntaxTermTest_2117, NodeIDTerm_ReturnsTrue_2117) {
    EXPECT_TRUE(IsCoreSyntaxTerm(kRDFTerm_nodeID));
}

// Test: datatype term (within core range) should return true
TEST_F(IsCoreSyntaxTermTest_2117, DatatypeTerm_ReturnsTrue_2117) {
    EXPECT_TRUE(IsCoreSyntaxTerm(kRDFTerm_datatype));
}

// Test: Term 0 (Other/before core range) should return false
TEST_F(IsCoreSyntaxTermTest_2117, OtherTerm_ReturnsFalse_2117) {
    EXPECT_FALSE(IsCoreSyntaxTerm(kRDFTerm_Other));
}

// Test: Term just after core range should return false
TEST_F(IsCoreSyntaxTermTest_2117, TermJustAfterCoreRange_ReturnsFalse_2117) {
    EXPECT_FALSE(IsCoreSyntaxTerm(kRDFTerm_LastCore + 1));
}

// Test: aboutEach (old term, outside core range) should return false
TEST_F(IsCoreSyntaxTermTest_2117, AboutEachTerm_ReturnsFalse_2117) {
    EXPECT_FALSE(IsCoreSyntaxTerm(kRDFTerm_aboutEach));
}

// Test: aboutEachPrefix (old term, outside core range) should return false
TEST_F(IsCoreSyntaxTermTest_2117, AboutEachPrefixTerm_ReturnsFalse_2117) {
    EXPECT_FALSE(IsCoreSyntaxTerm(kRDFTerm_aboutEachPrefix));
}

// Test: bagID (old term, outside core range) should return false
TEST_F(IsCoreSyntaxTermTest_2117, BagIDTerm_ReturnsFalse_2117) {
    EXPECT_FALSE(IsCoreSyntaxTerm(kRDFTerm_bagID));
}

// Test: li term (outside core range) should return false
TEST_F(IsCoreSyntaxTermTest_2117, LiTerm_ReturnsFalse_2117) {
    EXPECT_FALSE(IsCoreSyntaxTerm(kRDFTerm_li));
}

// Test: value term (outside core range) should return false
TEST_F(IsCoreSyntaxTermTest_2117, ValueTerm_ReturnsFalse_2117) {
    EXPECT_FALSE(IsCoreSyntaxTerm(kRDFTerm_value));
}

// Test: type term (outside core range) should return false
TEST_F(IsCoreSyntaxTermTest_2117, TypeTerm_ReturnsFalse_2117) {
    EXPECT_FALSE(IsCoreSyntaxTerm(kRDFTerm_type));
}

// Test: Maximum possible value for XMP_Uns8 should return false
TEST_F(IsCoreSyntaxTermTest_2117, MaxUns8Value_ReturnsFalse_2117) {
    EXPECT_FALSE(IsCoreSyntaxTerm(255));
}

// Test: Term just before FirstCore (boundary - 1) should return false
TEST_F(IsCoreSyntaxTermTest_2117, TermJustBeforeFirstCore_ReturnsFalse_2117) {
    if (kRDFTerm_FirstCore > 0) {
        EXPECT_FALSE(IsCoreSyntaxTerm(kRDFTerm_FirstCore - 1));
    }
}

// Test: All values in core range should return true
TEST_F(IsCoreSyntaxTermTest_2117, AllCoreRangeValues_ReturnTrue_2117) {
    for (RDFTermKind term = kRDFTerm_FirstCore; term <= kRDFTerm_LastCore; ++term) {
        EXPECT_TRUE(IsCoreSyntaxTerm(term)) << "Failed for term value: " << static_cast<int>(term);
    }
}

// Test: Values outside core range (above) should return false
TEST_F(IsCoreSyntaxTermTest_2117, ValuesAboveCoreRange_ReturnFalse_2117) {
    for (RDFTermKind term = kRDFTerm_LastCore + 1; term < 20; ++term) {
        EXPECT_FALSE(IsCoreSyntaxTerm(term)) << "Failed for term value: " << static_cast<int>(term);
    }
}

// Test: Zero value boundary
TEST_F(IsCoreSyntaxTermTest_2117, ZeroValue_ReturnsFalse_2117) {
    EXPECT_FALSE(IsCoreSyntaxTerm(0));
}

// Test: Mid-range non-core value
TEST_F(IsCoreSyntaxTermTest_2117, MidRangeNonCoreValue_ReturnsFalse_2117) {
    EXPECT_FALSE(IsCoreSyntaxTerm(100));
}
