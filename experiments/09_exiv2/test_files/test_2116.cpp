#include <gtest/gtest.h>

#include "XMPCommon/XMPCommonFwdDeclarations.h"

#include "XMPCommon/Interfaces/IError_I.h"



// Assuming XMP_VarString and RDFTermKind are defined in some header included by ParseRDF.cpp



TEST(GetRDFTermKindTest_2116, NormalOperation_RdfLi_2116) {

    XMP_VarString name("rdf:li");

    EXPECT_EQ(kRDFTerm_li, GetRDFTermKind(name));

}



TEST(GetRDFTermKindTest_2116, NormalOperation_RdfParseType_2116) {

    XMP_VarString name("rdf:parseType");

    EXPECT_EQ(kRDFTerm_parseType, GetRDFTermKind(name));

}



TEST(GetRDFTermKindTest_2116, NormalOperation_RdfDescription_2116) {

    XMP_VarString name("rdf:Description");

    EXPECT_EQ(kRDFTerm_Description, GetRDFTermKind(name));

}



TEST(GetRDFTermKindTest_2116, NormalOperation_RdfAbout_2116) {

    XMP_VarString name("rdf:about");

    EXPECT_EQ(kRDFTerm_about, GetRDFTermKind(name));

}



TEST(GetRDFTermKindTest_2116, NormalOperation_RdfResource_2116) {

    XMP_VarString name("rdf:resource");

    EXPECT_EQ(kRDFTerm_resource, GetRDFTermKind(name));

}



TEST(GetRDFTermKindTest_2116, NormalOperation_RdfRDF_2116) {

    XMP_VarString name("rdf:RDF");

    EXPECT_EQ(kRDFTerm_RDF, GetRDFTermKind(name));

}



TEST(GetRDFTermKindTest_2116, NormalOperation_RdfID_2116) {

    XMP_VarString name("rdf:ID");

    EXPECT_EQ(kRDFTerm_ID, GetRDFTermKind(name));

}



TEST(GetRDFTermKindTest_2116, NormalOperation_RdfNodeID_2116) {

    XMP_VarString name("rdf:nodeID");

    EXPECT_EQ(kRDFTerm_nodeID, GetRDFTermKind(name));

}



TEST(GetRDFTermKindTest_2116, NormalOperation_RdfDatatype_2116) {

    XMP_VarString name("rdf:datatype");

    EXPECT_EQ(kRDFTerm_datatype, GetRDFTermKind(name));

}



TEST(GetRDFTermKindTest_2116, NormalOperation_RdfAboutEach_2116) {

    XMP_VarString name("rdf:aboutEach");

    EXPECT_EQ(kRDFTerm_aboutEach, GetRDFTermKind(name));

}



TEST(GetRDFTermKindTest_2116, NormalOperation_RdfAboutEachPrefix_2116) {

    XMP_VarString name("rdf:aboutEachPrefix");

    EXPECT_EQ(kRDFTerm_aboutEachPrefix, GetRDFTermKind(name));

}



TEST(GetRDFTermKindTest_2116, NormalOperation_RdfBagID_2116) {

    XMP_VarString name("rdf:bagID");

    EXPECT_EQ(kRDFTerm_bagID, GetRDFTermKind(name));

}



TEST(GetRDFTermKindTest_2116, BoundaryCondition_EmptyString_2116) {

    XMP_VarString name("");

    EXPECT_EQ(kRDFTerm_Other, GetRDFTermKind(name));

}



TEST(GetRDFTermKindTest_2116, BoundaryCondition_ShortPrefix_2116) {

    XMP_VarString name("rdf");

    EXPECT_EQ(kRDFTerm_Other, GetRDFTermKind(name));

}



TEST(GetRDFTermKindTest_2116, ExceptionalCase_UpperCaseRDF_2116) {

    XMP_VarString name("RDF:li");

    EXPECT_EQ(kRDFTerm_Other, GetRDFTermKind(name));

}



TEST(GetRDFTermKindTest_2116, ExceptionalCase_MissingPrefix_2116) {

    XMP_VarString name("li");

    EXPECT_EQ(kRDFTerm_Other, GetRDFTermKind(name));

}



TEST(GetRDFTermKindTest_2116, ExceptionalCase_AdditionalCharacters_2116) {

    XMP_VarString name("rdf:lix");

    EXPECT_EQ(kRDFTerm_Other, GetRDFTermKind(name));

}
