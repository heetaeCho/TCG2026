#include <gtest/gtest.h>

#include "XMPCore_Impl.hpp"



class SerializeCompactRDFAttrPropsTest_2112 : public ::testing::Test {

protected:

    XMP_Node parentNode;

    XMP_VarString outputStr;

    const XMP_StringPtr newline = "\n";

    const XMP_StringPtr indentStr = "  ";

    XMP_Index indent = 1;



    SerializeCompactRDFAttrPropsTest_2112() : parentNode(nullptr, "parentNode", 0) {}



    bool CanBeRDFAttrProp(const XMP_Node* node) {

        // Mock implementation for testing purposes

        return true;

    }



    void AppendNodeValue(XMP_VarString &str, const XMP_StringPtr value, int /*flag*/) {

        str += value;

    }

};



TEST_F(SerializeCompactRDFAttrPropsTest_2112, NoChildren_2112) {

    EXPECT_TRUE(SerializeCompactRDFAttrProps(&parentNode, outputStr, newline, indentStr, indent));

    EXPECT_EQ(outputStr.size(), 0);

}



TEST_F(SerializeCompactRDFAttrPropsTest_2112, OneChild_2112) {

    XMP_Node child(&parentNode, "childName", "childValue", 0);

    parentNode.children.push_back(&child);



    EXPECT_TRUE(SerializeCompactRDFAttrProps(&parentNode, outputStr, newline, indentStr, indent));

    EXPECT_EQ(outputStr, "\n  childName=\"childValue\"");

}



TEST_F(SerializeCompactRDFAttrPropsTest_2112, MultipleChildren_2112) {

    XMP_Node child1(&parentNode, "childName1", "childValue1", 0);

    XMP_Node child2(&parentNode, "childName2", "childValue2", 0);

    parentNode.children.push_back(&child1);

    parentNode.children.push_back(&child2);



    EXPECT_TRUE(SerializeCompactRDFAttrProps(&parentNode, outputStr, newline, indentStr, indent));

    EXPECT_EQ(outputStr, "\n  childName1=\"childValue1\"\n  childName2=\"childValue2\"");

}



TEST_F(SerializeCompactRDFAttrPropsTest_2112, Indentation_2112) {

    XMP_Node child(&parentNode, "childName", "childValue", 0);

    parentNode.children.push_back(&child);



    indent = 2;

    EXPECT_TRUE(SerializeCompactRDFAttrProps(&parentNode, outputStr, newline, indentStr, indent));

    EXPECT_EQ(outputStr, "\n    childName=\"childValue\"");

}



TEST_F(SerializeCompactRDFAttrPropsTest_2112, NonAttributeChild_2112) {

    XMP_Node attrChild(&parentNode, "attrChild", "attrValue", 0);

    XMP_Node nonAttrChild(&parentNode, "nonAttrChild", "nonAttrValue", 0);



    // Mock CanBeRDFAttrProp to return false for the second child

    auto originalCanBeRDFAttrProp = CanBeRDFAttrProp;

    CanBeRDFAttrProp = [&](const XMP_Node* node) {

        return node->name == "attrChild";

    };



    parentNode.children.push_back(&attrChild);

    parentNode.children.push_back(&nonAttrChild);



    EXPECT_FALSE(SerializeCompactRDFAttrProps(&parentNode, outputStr, newline, indentStr, indent));

    EXPECT_EQ(outputStr, "\n  attrChild=\"attrValue\"");

}



TEST_F(SerializeCompactRDFAttrPropsTest_2112, AllChildrenAreAttributes_2112) {

    XMP_Node child1(&parentNode, "childName1", "childValue1", 0);

    XMP_Node child2(&parentNode, "childName2", "childValue2", 0);



    parentNode.children.push_back(&child1);

    parentNode.children.push_back(&child2);



    EXPECT_TRUE(SerializeCompactRDFAttrProps(&parentNode, outputStr, newline, indentStr, indent));

}



TEST_F(SerializeCompactRDFAttrPropsTest_2112, SomeChildrenNotAttributes_2112) {

    XMP_Node attrChild(&parentNode, "attrChild", "attrValue", 0);

    XMP_Node nonAttrChild(&parentNode, "nonAttrChild", "nonAttrValue", 0);



    // Mock CanBeRDFAttrProp to return false for the second child

    auto originalCanBeRDFAttrProp = CanBeRDFAttrProp;

    CanBeRDFAttrProp = [&](const XMP_Node* node) {

        return node->name == "attrChild";

    };



    parentNode.children.push_back(&attrChild);

    parentNode.children.push_back(&nonAttrChild);



    EXPECT_FALSE(SerializeCompactRDFAttrProps(&parentNode, outputStr, newline, indentStr, indent));

}
