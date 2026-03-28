#include <gtest/gtest.h>

#include "XMPCore_Impl.hpp"



using namespace XMP_Lib;



TEST(CompareNodeNamesTest_2142, xmlLangBeforeRdfType_2142) {

    XMP_Node left(nullptr, "xml:lang", 0);

    XMP_Node right(nullptr, "rdf:type", 0);



    EXPECT_TRUE(CompareNodeNames(&left, &right));

}



TEST(CompareNodeNamesTest_2142, rdfTypeAfterXmlLang_2142) {

    XMP_Node left(nullptr, "rdf:type", 0);

    XMP_Node right(nullptr, "xml:lang", 0);



    EXPECT_FALSE(CompareNodeNames(&left, &right));

}



TEST(CompareNodeNamesTest_2142, xmlLangBeforeOtherNodes_2142) {

    XMP_Node left(nullptr, "xml:lang", 0);

    XMP_Node right(nullptr, "otherNode", 0);



    EXPECT_TRUE(CompareNodeNames(&left, &right));

}



TEST(CompareNodeNamesTest_2142, rdfTypeBeforeOtherNodes_2142) {

    XMP_Node left(nullptr, "rdf:type", 0);

    XMP_Node right(nullptr, "otherNode", 0);



    EXPECT_TRUE(CompareNodeNames(&left, &right));

}



TEST(CompareNodeNamesTest_2142, otherNodesAfterXmlLang_2142) {

    XMP_Node left(nullptr, "otherNode", 0);

    XMP_Node right(nullptr, "xml:lang", 0);



    EXPECT_FALSE(CompareNodeNames(&left, &right));

}



TEST(CompareNodeNamesTest_2142, otherNodesAfterRdfType_2142) {

    XMP_Node left(nullptr, "otherNode", 0);

    XMP_Node right(nullptr, "rdf:type", 0);



    EXPECT_FALSE(CompareNodeNames(&left, &right));

}



TEST(CompareNodeNamesTest_2142, normalNodeComparison_2142) {

    XMP_Node left(nullptr, "firstNode", 0);

    XMP_Node right(nullptr, "secondNode", 0);



    EXPECT_TRUE(CompareNodeNames(&left, &right));

}



TEST(CompareNodeNamesTest_2142, identicalNodes_2142) {

    XMP_Node left(nullptr, "sameNode", 0);

    XMP_Node right(nullptr, "sameNode", 0);



    EXPECT_FALSE(CompareNodeNames(&left, &right));

}
