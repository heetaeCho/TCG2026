#include <gtest/gtest.h>

// Reproduce the types and helper functions as they appear in the codebase
// We need these to test IsPropertyElementName

typedef unsigned char XMP_Uns8;
typedef XMP_Uns8 RDFTermKind;

// RDF term constants based on the XMP SDK ParseRDF.cpp
// These are the standard RDF term kinds used in the XMP SDK
enum {
    kRDFTerm_Other = 0,
    
    // Core syntax terms
    kRDFTerm_RDF = 1,
    kRDFTerm_ID = 2,
    kRDFTerm_about = 3,
    kRDFTerm_parseType = 4,
    kRDFTerm_resource = 5,
    kRDFTerm_nodeID = 6,
    kRDFTerm_datatype = 7,
    
    kRDFTerm_Description = 8,
    
    // Old terms
    kRDFTerm_aboutEach = 10,
    kRDFTerm_aboutEachPrefix = 11,
    kRDFTerm_bagID = 12,
    
    // Other RDF terms that are property element names
    kRDFTerm_li = 9,
    kRDFTerm_value = 13,
    kRDFTerm_first = 14,
    kRDFTerm_rest = 15,
    kRDFTerm_subject = 16,
    kRDFTerm_predicate = 17,
    kRDFTerm_object = 18,
    kRDFTerm_type = 19,
    kRDFTerm_Bag = 20,
    kRDFTerm_Seq = 21,
    kRDFTerm_Alt = 22,
    kRDFTerm_Statement = 23,
    kRDFTerm_Property = 24,
    kRDFTerm_List = 25,
    kRDFTerm_XMLList = 26,
};

// Helper functions matching the XMP SDK
static bool IsCoreSyntaxTerm(RDFTermKind term) {
    // Core syntax terms: kRDFTerm_RDF(1) through kRDFTerm_datatype(7)
    return (term >= kRDFTerm_RDF && term <= kRDFTerm_datatype);
}

static bool IsOldTerm(RDFTermKind term) {
    // Old terms: kRDFTerm_aboutEach(10), kRDFTerm_aboutEachPrefix(11), kRDFTerm_bagID(12)
    return (term == kRDFTerm_aboutEach || term == kRDFTerm_aboutEachPrefix || term == kRDFTerm_bagID);
}

// The function under test - copied from the provided code
static bool IsPropertyElementName(RDFTermKind term) {
    if ((term == kRDFTerm_Description) || IsOldTerm(term)) return false;
    return (!IsCoreSyntaxTerm(term));
}

// Test fixture
class IsPropertyElementNameTest_2119 : public ::testing::Test {
protected:
};

// Test that kRDFTerm_Description returns false
TEST_F(IsPropertyElementNameTest_2119, DescriptionReturnsFalse_2119) {
    EXPECT_FALSE(IsPropertyElementName(kRDFTerm_Description));
}

// Test that old terms return false
TEST_F(IsPropertyElementNameTest_2119, OldTermAboutEachReturnsFalse_2119) {
    EXPECT_FALSE(IsPropertyElementName(kRDFTerm_aboutEach));
}

TEST_F(IsPropertyElementNameTest_2119, OldTermAboutEachPrefixReturnsFalse_2119) {
    EXPECT_FALSE(IsPropertyElementName(kRDFTerm_aboutEachPrefix));
}

TEST_F(IsPropertyElementNameTest_2119, OldTermBagIDReturnsFalse_2119) {
    EXPECT_FALSE(IsPropertyElementName(kRDFTerm_bagID));
}

// Test that core syntax terms return false
TEST_F(IsPropertyElementNameTest_2119, CoreSyntaxTermRDFReturnsFalse_2119) {
    EXPECT_FALSE(IsPropertyElementName(kRDFTerm_RDF));
}

TEST_F(IsPropertyElementNameTest_2119, CoreSyntaxTermIDReturnsFalse_2119) {
    EXPECT_FALSE(IsPropertyElementName(kRDFTerm_ID));
}

TEST_F(IsPropertyElementNameTest_2119, CoreSyntaxTermAboutReturnsFalse_2119) {
    EXPECT_FALSE(IsPropertyElementName(kRDFTerm_about));
}

TEST_F(IsPropertyElementNameTest_2119, CoreSyntaxTermParseTypeReturnsFalse_2119) {
    EXPECT_FALSE(IsPropertyElementName(kRDFTerm_parseType));
}

TEST_F(IsPropertyElementNameTest_2119, CoreSyntaxTermResourceReturnsFalse_2119) {
    EXPECT_FALSE(IsPropertyElementName(kRDFTerm_resource));
}

TEST_F(IsPropertyElementNameTest_2119, CoreSyntaxTermNodeIDReturnsFalse_2119) {
    EXPECT_FALSE(IsPropertyElementName(kRDFTerm_nodeID));
}

TEST_F(IsPropertyElementNameTest_2119, CoreSyntaxTermDatatypeReturnsFalse_2119) {
    EXPECT_FALSE(IsPropertyElementName(kRDFTerm_datatype));
}

// Test that kRDFTerm_Other (0) returns true - it's not Description, not old, not core syntax
TEST_F(IsPropertyElementNameTest_2119, OtherTermReturnsTrue_2119) {
    EXPECT_TRUE(IsPropertyElementName(kRDFTerm_Other));
}

// Test that kRDFTerm_li returns true (it's a valid property element name)
TEST_F(IsPropertyElementNameTest_2119, LiTermReturnsTrue_2119) {
    EXPECT_TRUE(IsPropertyElementName(kRDFTerm_li));
}

// Test that kRDFTerm_value returns true
TEST_F(IsPropertyElementNameTest_2119, ValueTermReturnsTrue_2119) {
    EXPECT_TRUE(IsPropertyElementName(kRDFTerm_value));
}

// Test that kRDFTerm_first returns true
TEST_F(IsPropertyElementNameTest_2119, FirstTermReturnsTrue_2119) {
    EXPECT_TRUE(IsPropertyElementName(kRDFTerm_first));
}

// Test that kRDFTerm_rest returns true
TEST_F(IsPropertyElementNameTest_2119, RestTermReturnsTrue_2119) {
    EXPECT_TRUE(IsPropertyElementName(kRDFTerm_rest));
}

// Test that kRDFTerm_subject returns true
TEST_F(IsPropertyElementNameTest_2119, SubjectTermReturnsTrue_2119) {
    EXPECT_TRUE(IsPropertyElementName(kRDFTerm_subject));
}

// Test that kRDFTerm_predicate returns true
TEST_F(IsPropertyElementNameTest_2119, PredicateTermReturnsTrue_2119) {
    EXPECT_TRUE(IsPropertyElementName(kRDFTerm_predicate));
}

// Test that kRDFTerm_object returns true
TEST_F(IsPropertyElementNameTest_2119, ObjectTermReturnsTrue_2119) {
    EXPECT_TRUE(IsPropertyElementName(kRDFTerm_object));
}

// Test that kRDFTerm_type returns true
TEST_F(IsPropertyElementNameTest_2119, TypeTermReturnsTrue_2119) {
    EXPECT_TRUE(IsPropertyElementName(kRDFTerm_type));
}

// Test container terms (Bag, Seq, Alt) return true
TEST_F(IsPropertyElementNameTest_2119, BagTermReturnsTrue_2119) {
    EXPECT_TRUE(IsPropertyElementName(kRDFTerm_Bag));
}

TEST_F(IsPropertyElementNameTest_2119, SeqTermReturnsTrue_2119) {
    EXPECT_TRUE(IsPropertyElementName(kRDFTerm_Seq));
}

TEST_F(IsPropertyElementNameTest_2119, AltTermReturnsTrue_2119) {
    EXPECT_TRUE(IsPropertyElementName(kRDFTerm_Alt));
}

// Boundary: test with max XMP_Uns8 value (255) - should be property element name
// since it's not Description, not old term, not core syntax
TEST_F(IsPropertyElementNameTest_2119, MaxUns8ValueReturnsTrue_2119) {
    EXPECT_TRUE(IsPropertyElementName(static_cast<RDFTermKind>(255)));
}

// Boundary: test with a high arbitrary value that is not any known term
TEST_F(IsPropertyElementNameTest_2119, ArbitraryHighValueReturnsTrue_2119) {
    EXPECT_TRUE(IsPropertyElementName(static_cast<RDFTermKind>(100)));
}

// Test that Statement term returns true
TEST_F(IsPropertyElementNameTest_2119, StatementTermReturnsTrue_2119) {
    EXPECT_TRUE(IsPropertyElementName(kRDFTerm_Statement));
}

// Test that Property term returns true
TEST_F(IsPropertyElementNameTest_2119, PropertyTermReturnsTrue_2119) {
    EXPECT_TRUE(IsPropertyElementName(kRDFTerm_Property));
}

// Test that List term returns true
TEST_F(IsPropertyElementNameTest_2119, ListTermReturnsTrue_2119) {
    EXPECT_TRUE(IsPropertyElementName(kRDFTerm_List));
}
