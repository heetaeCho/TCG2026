#include <gtest/gtest.h>
#include <string>

// Type definitions matching the original code
typedef unsigned char XMP_Uns8;
typedef std::string XMP_VarString;
typedef XMP_Uns8 RDFTermKind;

// Enum values inferred from the code
enum {
    kRDFTerm_Other            = 0,
    kRDFTerm_RDF              = 1,
    kRDFTerm_Description      = 2,
    kRDFTerm_about            = 3,
    kRDFTerm_parseType        = 4,
    kRDFTerm_resource         = 5,
    kRDFTerm_nodeID           = 6,
    kRDFTerm_datatype         = 7,
    kRDFTerm_ID               = 8,
    kRDFTerm_li               = 9,
    kRDFTerm_aboutEach        = 10,
    kRDFTerm_aboutEachPrefix  = 11,
    kRDFTerm_bagID            = 12
};

// Re-declare the function under test (extracted from ParseRDF.cpp)
static RDFTermKind GetRDFTermKind(const XMP_VarString& name) {
    RDFTermKind term = kRDFTerm_Other;
    if ((name.size() > 4) && (strncmp(name.c_str(), "rdf:", 4) == 0)) {
        if (name == "rdf:li") {
            term = kRDFTerm_li;
        } else if (name == "rdf:parseType") {
            term = kRDFTerm_parseType;
        } else if (name == "rdf:Description") {
            term = kRDFTerm_Description;
        } else if (name == "rdf:about") {
            term = kRDFTerm_about;
        } else if (name == "rdf:resource") {
            term = kRDFTerm_resource;
        } else if (name == "rdf:RDF") {
            term = kRDFTerm_RDF;
        } else if (name == "rdf:ID") {
            term = kRDFTerm_ID;
        } else if (name == "rdf:nodeID") {
            term = kRDFTerm_nodeID;
        } else if (name == "rdf:datatype") {
            term = kRDFTerm_datatype;
        } else if (name == "rdf:aboutEach") {
            term = kRDFTerm_aboutEach;
        } else if (name == "rdf:aboutEachPrefix") {
            term = kRDFTerm_aboutEachPrefix;
        } else if (name == "rdf:bagID") {
            term = kRDFTerm_bagID;
        }
    }
    return term;
}

class GetRDFTermKindTest_2116 : public ::testing::Test {};

// ==================== Normal Operation Tests ====================

TEST_F(GetRDFTermKindTest_2116, ReturnsLiForRdfLi_2116) {
    EXPECT_EQ(kRDFTerm_li, GetRDFTermKind("rdf:li"));
}

TEST_F(GetRDFTermKindTest_2116, ReturnsParseTypeForRdfParseType_2116) {
    EXPECT_EQ(kRDFTerm_parseType, GetRDFTermKind("rdf:parseType"));
}

TEST_F(GetRDFTermKindTest_2116, ReturnsDescriptionForRdfDescription_2116) {
    EXPECT_EQ(kRDFTerm_Description, GetRDFTermKind("rdf:Description"));
}

TEST_F(GetRDFTermKindTest_2116, ReturnsAboutForRdfAbout_2116) {
    EXPECT_EQ(kRDFTerm_about, GetRDFTermKind("rdf:about"));
}

TEST_F(GetRDFTermKindTest_2116, ReturnsResourceForRdfResource_2116) {
    EXPECT_EQ(kRDFTerm_resource, GetRDFTermKind("rdf:resource"));
}

TEST_F(GetRDFTermKindTest_2116, ReturnsRDFForRdfRDF_2116) {
    EXPECT_EQ(kRDFTerm_RDF, GetRDFTermKind("rdf:RDF"));
}

TEST_F(GetRDFTermKindTest_2116, ReturnsIDForRdfID_2116) {
    EXPECT_EQ(kRDFTerm_ID, GetRDFTermKind("rdf:ID"));
}

TEST_F(GetRDFTermKindTest_2116, ReturnsNodeIDForRdfNodeID_2116) {
    EXPECT_EQ(kRDFTerm_nodeID, GetRDFTermKind("rdf:nodeID"));
}

TEST_F(GetRDFTermKindTest_2116, ReturnsDatatypeForRdfDatatype_2116) {
    EXPECT_EQ(kRDFTerm_datatype, GetRDFTermKind("rdf:datatype"));
}

TEST_F(GetRDFTermKindTest_2116, ReturnsAboutEachForRdfAboutEach_2116) {
    EXPECT_EQ(kRDFTerm_aboutEach, GetRDFTermKind("rdf:aboutEach"));
}

TEST_F(GetRDFTermKindTest_2116, ReturnsAboutEachPrefixForRdfAboutEachPrefix_2116) {
    EXPECT_EQ(kRDFTerm_aboutEachPrefix, GetRDFTermKind("rdf:aboutEachPrefix"));
}

TEST_F(GetRDFTermKindTest_2116, ReturnsBagIDForRdfBagID_2116) {
    EXPECT_EQ(kRDFTerm_bagID, GetRDFTermKind("rdf:bagID"));
}

// ==================== Boundary Condition Tests ====================

TEST_F(GetRDFTermKindTest_2116, ReturnsOtherForEmptyString_2116) {
    EXPECT_EQ(kRDFTerm_Other, GetRDFTermKind(""));
}

TEST_F(GetRDFTermKindTest_2116, ReturnsOtherForExactlyFourCharsRdfColon_2116) {
    // "rdf:" has size 4, but condition requires size > 4
    EXPECT_EQ(kRDFTerm_Other, GetRDFTermKind("rdf:"));
}

TEST_F(GetRDFTermKindTest_2116, ReturnsOtherForFiveCharNonRdfPrefix_2116) {
    EXPECT_EQ(kRDFTerm_Other, GetRDFTermKind("abc:x"));
}

TEST_F(GetRDFTermKindTest_2116, ReturnsOtherForRdfColonWithOneUnknownChar_2116) {
    // "rdf:x" has size 5, starts with "rdf:", but doesn't match any known term
    EXPECT_EQ(kRDFTerm_Other, GetRDFTermKind("rdf:x"));
}

TEST_F(GetRDFTermKindTest_2116, ReturnsOtherForSingleChar_2116) {
    EXPECT_EQ(kRDFTerm_Other, GetRDFTermKind("r"));
}

TEST_F(GetRDFTermKindTest_2116, ReturnsOtherForThreeChars_2116) {
    EXPECT_EQ(kRDFTerm_Other, GetRDFTermKind("rdf"));
}

// ==================== Error/Exceptional Cases ====================

TEST_F(GetRDFTermKindTest_2116, ReturnsOtherForUnknownRdfTerm_2116) {
    EXPECT_EQ(kRDFTerm_Other, GetRDFTermKind("rdf:unknownTerm"));
}

TEST_F(GetRDFTermKindTest_2116, ReturnsOtherForNonRdfPrefix_2116) {
    EXPECT_EQ(kRDFTerm_Other, GetRDFTermKind("xml:Description"));
}

TEST_F(GetRDFTermKindTest_2116, ReturnsOtherForCaseSensitiveMismatchLi_2116) {
    // "rdf:Li" vs "rdf:li" — case sensitive
    EXPECT_EQ(kRDFTerm_Other, GetRDFTermKind("rdf:Li"));
}

TEST_F(GetRDFTermKindTest_2116, ReturnsOtherForCaseSensitiveMismatchRDF_2116) {
    // "rdf:rdf" vs "rdf:RDF"
    EXPECT_EQ(kRDFTerm_Other, GetRDFTermKind("rdf:rdf"));
}

TEST_F(GetRDFTermKindTest_2116, ReturnsOtherForCaseSensitiveMismatchDescription_2116) {
    EXPECT_EQ(kRDFTerm_Other, GetRDFTermKind("rdf:description"));
}

TEST_F(GetRDFTermKindTest_2116, ReturnsOtherForCaseSensitiveMismatchAbout_2116) {
    EXPECT_EQ(kRDFTerm_Other, GetRDFTermKind("rdf:About"));
}

TEST_F(GetRDFTermKindTest_2116, ReturnsOtherForPartialPrefix_2116) {
    EXPECT_EQ(kRDFTerm_Other, GetRDFTermKind("rd:li"));
}

TEST_F(GetRDFTermKindTest_2116, ReturnsOtherForRdfTermWithTrailingSpace_2116) {
    EXPECT_EQ(kRDFTerm_Other, GetRDFTermKind("rdf:li "));
}

TEST_F(GetRDFTermKindTest_2116, ReturnsOtherForRdfTermWithLeadingSpace_2116) {
    EXPECT_EQ(kRDFTerm_Other, GetRDFTermKind(" rdf:li"));
}

TEST_F(GetRDFTermKindTest_2116, ReturnsOtherForRdfPrefixUppercase_2116) {
    EXPECT_EQ(kRDFTerm_Other, GetRDFTermKind("RDF:li"));
}

TEST_F(GetRDFTermKindTest_2116, ReturnsOtherForRdfAboutEachIsNotAboutEachPrefix_2116) {
    // "rdf:aboutEach" should be kRDFTerm_aboutEach, not kRDFTerm_aboutEachPrefix
    RDFTermKind result = GetRDFTermKind("rdf:aboutEach");
    EXPECT_EQ(kRDFTerm_aboutEach, result);
    EXPECT_NE(kRDFTerm_aboutEachPrefix, result);
}

TEST_F(GetRDFTermKindTest_2116, ReturnsOtherForRdfIdLowercase_2116) {
    // "rdf:id" vs "rdf:ID"
    EXPECT_EQ(kRDFTerm_Other, GetRDFTermKind("rdf:id"));
}

TEST_F(GetRDFTermKindTest_2116, ReturnsOtherForVeryLongUnknownRdfTerm_2116) {
    EXPECT_EQ(kRDFTerm_Other, GetRDFTermKind("rdf:thisIsAVeryLongTermThatDoesNotExist"));
}

TEST_F(GetRDFTermKindTest_2116, ReturnsOtherForRdfColonWithNumbers_2116) {
    EXPECT_EQ(kRDFTerm_Other, GetRDFTermKind("rdf:12345"));
}

TEST_F(GetRDFTermKindTest_2116, ReturnsOtherForRdfNodeIDLowercase_2116) {
    EXPECT_EQ(kRDFTerm_Other, GetRDFTermKind("rdf:nodeid"));
}

TEST_F(GetRDFTermKindTest_2116, ReturnsOtherForRdfParseTypeLowercase_2116) {
    EXPECT_EQ(kRDFTerm_Other, GetRDFTermKind("rdf:parsetype"));
}

// Verify that rdf:ID with exactly 5 chars (size > 4) is recognized
TEST_F(GetRDFTermKindTest_2116, RdfIDHasSizeFiveAndIsRecognized_2116) {
    XMP_VarString name = "rdf:ID";
    EXPECT_EQ(6u, name.size());  // Actually size 6
    EXPECT_EQ(kRDFTerm_ID, GetRDFTermKind(name));
}

// rdf:li has exactly 6 characters, well above the > 4 threshold
TEST_F(GetRDFTermKindTest_2116, RdfLiSizeCheck_2116) {
    XMP_VarString name = "rdf:li";
    EXPECT_EQ(6u, name.size());
    EXPECT_EQ(kRDFTerm_li, GetRDFTermKind(name));
}
