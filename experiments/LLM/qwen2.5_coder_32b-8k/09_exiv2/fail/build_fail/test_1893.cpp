#include <gtest/gtest.h>

#include "XMPCore_Impl.hpp"

#include "XMP_Const.h"



class ExpandXPathTest_1893 : public ::testing::Test {

protected:

    XMP_StringPtr schemaNS = "http://ns.example.com/";

    XMP_ExpandedXPath expandedXPath;

};



TEST_F(ExpandXPathTest_1893, NormalOperation_1893) {

    XMP_StringPtr propPath = "Root/Field[1]/SubField";

    EXPECT_NO_THROW(ExpandXPath(schemaNS, propPath, &expandedXPath));

    EXPECT_EQ(expandedXPath.size(), 4);

}



TEST_F(ExpandXPathTest_1893, BoundaryConditions_EmptySchemaNS_1893) {

    XMP_StringPtr propPath = "Root/Field";

    EXPECT_THROW(ExpandXPath("", propPath, &expandedXPath), XMP_Error);

}



TEST_F(ExpandXPathTest_1893, BoundaryConditions_EmptyPropPath_1893) {

    XMP_StringPtr propPath = "";

    EXPECT_THROW(ExpandXPath(schemaNS, propPath, &expandedXPath), XMP_Error);

}



TEST_F(ExpandXPathTest_1893, BoundaryConditions_NullSchemaNS_1893) {

    XMP_StringPtr propPath = "Root/Field";

    EXPECT_THROW(ExpandXPath(nullptr, propPath, &expandedXPath), XMP_Error);

}



TEST_F(ExpandXPathTest_1893, BoundaryConditions_NullPropPath_1893) {

    XMP_StringPtr propPath = nullptr;

    EXPECT_THROW(ExpandXPath(schemaNS, propPath, &expandedXPath), XMP_Error);

}



TEST_F(ExpandXPathTest_1893, ExceptionalCase_MissingClosingBracketForIndex_1893) {

    XMP_StringPtr propPath = "Root/Field[";

    EXPECT_THROW(ExpandXPath(schemaNS, propPath, &expandedXPath), XMP_Error);

}



TEST_F(ExpandXPathTest_1893, ExceptionalCase_EmptyInitialStep_1893) {

    XMP_StringPtr propPath = "//Field[1]";

    EXPECT_THROW(ExpandXPath(schemaNS, propPath, &expandedXPath), XMP_Error);

}



TEST_F(ExpandXPathTest_1893, ExceptionalCase_MissingQuoteInArraySelector_1893) {

    XMP_StringPtr propPath = "Root/Field['value";

    EXPECT_THROW(ExpandXPath(schemaNS, propPath, &expandedXPath), XMP_Error);

}



TEST_F(ExpandXPathTest_1893, ExceptionalCase_InvalidNonNumericArrayIndex_1893) {

    XMP_StringPtr propPath = "Root/Field[a]";

    EXPECT_THROW(ExpandXPath(schemaNS, propPath, &expandedXPath), XMP_Error);

}



TEST_F(ExpandXPathTest_1893, ExceptionalCase_MissingEqualsInArraySelector_1893) {

    XMP_StringPtr propPath = "Root/Field['value'";

    EXPECT_THROW(ExpandXPath(schemaNS, propPath, &expandedXPath), XMP_Error);

}



TEST_F(ExpandXPathTest_1893, VerifyQualName_AttributeUsage_1893) {

    XMP_StringPtr propPath = "Root/@xml:lang";

    EXPECT_NO_THROW(ExpandXPath(schemaNS, propPath, &expandedXPath));

    EXPECT_EQ(expandedXPath.size(), 2);

}



TEST_F(ExpandXPathTest_1893, VerifyQualName_AttributeUsageWithQuestionMark_1893) {

    XMP_StringPtr propPath = "Root/?xml:lang";

    EXPECT_NO_THROW(ExpandXPath(schemaNS, propPath, &expandedXPath));

    EXPECT_EQ(expandedXPath.size(), 2);

}



TEST_F(ExpandXPathTest_1893, VerifyQualName_AttributeUsageInvalid_1893) {

    XMP_StringPtr propPath = "Root/@invalid";

    EXPECT_THROW(ExpandXPath(schemaNS, propPath, &expandedXPath), XMP_Error);

}
