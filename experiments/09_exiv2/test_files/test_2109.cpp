#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mocking the XMP_VarString type as a string for testing purposes

using XMP_VarString = std::string;



// Declaring the function to be tested

extern bool IsRDFAttrQualifier(XMP_VarString qualName);



class IsRDFAttrQualifierTest_2109 : public ::testing::Test {

protected:

    // Setup and teardown can be added here if needed

};



TEST_F(IsRDFAttrQualifierTest_2109, ValidAttribute_ReturnsTrue_2109) {

    EXPECT_TRUE(IsRDFAttrQualifier("xml:lang"));

    EXPECT_TRUE(IsRDFAttrQualifier("rdf:resource"));

    EXPECT_TRUE(IsRDFAttrQualifier("rdf:ID"));

    EXPECT_TRUE(IsRDFAttrQualifier("rdf:bagID"));

    EXPECT_TRUE(IsRDFAttrQualifier("rdf:nodeID"));

}



TEST_F(IsRDFAttrQualifierTest_2109, InvalidAttribute_ReturnsFalse_2109) {

    EXPECT_FALSE(IsRDFAttrQualifier("unknown"));

    EXPECT_FALSE(IsRDFAttrQualifier(""));

    EXPECT_FALSE(IsRDFAttrQualifier("xml:langg"));

}



TEST_F(IsRDFAttrQualifierTest_2109, BoundaryCase_EmptyString_ReturnsFalse_2109) {

    EXPECT_FALSE(IsRDFAttrQualifier(""));

}



TEST_F(IsRDFAttrQualifierTest_2109, CaseSensitivity_ReturnsCorrectly_2109) {

    EXPECT_TRUE(IsRDFAttrQualifier("xml:lang"));

    EXPECT_FALSE(IsRDFAttrQualifier("XML:LANG")); // Case sensitivity check

}
