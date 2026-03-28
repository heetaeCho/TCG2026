#include <gtest/gtest.h>

#include "StructElement.h"



// Mocking external dependencies if needed (not required in this case as there are no collaborators)



TEST(nameToOwnerTest_1781, UnknownNameReturnsUnknownOwner_1781) {

    EXPECT_EQ(Attribute::UnknownOwner, nameToOwner("unknown"));

}



TEST(nameToOwnerTest_1781, UserPropertiesNameReturnsUserProperties_1781) {

    EXPECT_EQ(Attribute::UserProperties, nameToOwner("UserProperties"));

}



TEST(nameToOwnerTest_1781, LayoutNameReturnsLayout_1781) {

    EXPECT_EQ(Attribute::Layout, nameToOwner("Layout"));

}



TEST(nameToOwnerTest_1781, ListNameReturnsList_1781) {

    EXPECT_EQ(Attribute::List, nameToOwner("List"));

}



TEST(nameToOwnerTest_1781, PrintFieldNameReturnsPrintField_1781) {

    EXPECT_EQ(Attribute::PrintField, nameToOwner("PrintField"));

}



TEST(nameToOwnerTest_1781, TableNameReturnsTable_1781) {

    EXPECT_EQ(Attribute::Table, nameToOwner("Table"));

}



TEST(nameToOwnerTest_1781, XMLNameReturnsXML_1781) {

    EXPECT_EQ(Attribute::XML_1_00, nameToOwner("XML_1_00"));

}



TEST(nameToOwnerTest_1781, HTML320NameReturnsHTML320_1781) {

    EXPECT_EQ(Attribute::HTML_3_20, nameToOwner("HTML_3_20"));

}



TEST(nameToOwnerTest_1781, HTML401NameReturnsHTML401_1781) {

    EXPECT_EQ(Attribute::HTML_4_01, nameToOwner("HTML_4_01"));

}



TEST(nameToOwnerTest_1781, OEBNameReturnsOEB_1781) {

    EXPECT_EQ(Attribute::OEB_1_00, nameToOwner("OEB_1_00"));

}



TEST(nameToOwnerTest_1781, RTFNameReturnsRTF_1781) {

    EXPECT_EQ(Attribute::RTF_1_05, nameToOwner("RTF_1_05"));

}



TEST(nameToOwnerTest_1781, CSS100NameReturnsCSS100_1781) {

    EXPECT_EQ(Attribute::CSS_1_00, nameToOwner("CSS_1_00"));

}



TEST(nameToOwnerTest_1781, CSS200NameReturnsCSS200_1781) {

    EXPECT_EQ(Attribute::CSS_2_00, nameToOwner("CSS_2_00"));

}
