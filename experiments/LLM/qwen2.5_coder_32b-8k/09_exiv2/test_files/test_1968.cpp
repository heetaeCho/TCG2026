#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mocking external collaborators if needed (not required in this case)



using namespace ::testing;



class XMPNodeTest : public ::testing::Test {

protected:

    XMP_Node* schemaNode;

    XMP_Node* arrayNode;



    void SetUp() override {

        schemaNode = new XMP_Node(nullptr, "schemaNS", 0);

        arrayNode = new XMP_Node(schemaNode, "arrayName", kXMP_PropValueIsArray);

        schemaNode->children.push_back(arrayNode);

    }



    void TearDown() override {

        delete schemaNode;

    }

};



TEST_F(XMPNodeTest_1968, RepairAltText_NoSchemaNodeExists_1968) {

    XMP_Node tree(nullptr, "root", 0);

    RepairAltText(tree, "nonExistentSchemaNS", "arrayName");

    EXPECT_TRUE(tree.children.empty());

}



TEST_F(XMPNodeTest_1968, RepairAltText_ArrayNodeNotArray_1968) {

    arrayNode->options = kXMP_PropValueIsStruct;

    RepairAltText(*schemaNode, schemaNode->name.c_str(), arrayNode->name.c_str());

    EXPECT_FALSE(arrayNode->options & kXMP_PropArrayIsAltText);

}



TEST_F(XMPNodeTest_1968, RepairAltText_ArrayAlreadyAltText_1968) {

    arrayNode->options |= kXMP_PropArrayIsAltText;

    RepairAltText(*schemaNode, schemaNode->name.c_str(), arrayNode->name.c_str());

    EXPECT_TRUE(arrayNode->options & kXMP_PropArrayIsAltText);

}



TEST_F(XMPNodeTest_1968, RepairAltText_ArrayChildrenNonSimpleRemoved_1968) {

    XMP_Node* nonSimpleChild = new XMP_Node(arrayNode, "nonSimple", kXMP_PropValueIsStruct);

    arrayNode->children.push_back(nonSimpleChild);



    RepairAltText(*schemaNode, schemaNode->name.c_str(), arrayNode->name.c_str());

    EXPECT_TRUE(arrayNode->children.empty());

}



TEST_F(XMPNodeTest_1968, RepairAltText_ArrayChildrenWithoutLangButValueAddedQualifier_1968) {

    XMP_Node* child = new XMP_Node(arrayNode, "child", "value");

    arrayNode->children.push_back(child);



    RepairAltText(*schemaNode, schemaNode->name.c_str(), arrayNode->name.c_str());

    EXPECT_EQ(child->qualifiers.size(), 1);

    EXPECT_STREQ(child->qualifiers[0]->name.c_str(), "xml:lang");

    EXPECT_STREQ(child->qualifiers[0]->value.c_str(), "x-repair");

}



TEST_F(XMPNodeTest_1968, RepairAltText_ArrayChildrenWithoutLangAndEmptyValueRemoved_1968) {

    XMP_Node* child = new XMP_Node(arrayNode, "child", "");

    arrayNode->children.push_back(child);



    RepairAltText(*schemaNode, schemaNode->name.c_str(), arrayNode->name.c_str());

    EXPECT_TRUE(arrayNode->children.empty());

}



TEST_F(XMPNodeTest_1968, RepairAltText_ArrayChildrenWithLangLeftUntouched_1968) {

    XMP_Node* child = new XMP_Node(arrayNode, "child", "value");

    arrayNode->children.push_back(child);

    child->options |= kXMP_PropHasLang;



    RepairAltText(*schemaNode, schemaNode->name.c_str(), arrayNode->name.c_str());

    EXPECT_TRUE(child->qualifiers.empty());

}



TEST_F(XMPNodeTest_1968, RepairAltText_ArrayChildrenMultipleScenarios_1968) {

    XMP_Node* simpleChild = new XMP_Node(arrayNode, "simple", "value");

    XMP_Node* nonSimpleChild = new XMP_Node(arrayNode, "nonSimple", kXMP_PropValueIsStruct);

    XMP_Node* emptyChild = new XMP_Node(arrayNode, "empty", "");

    XMP_Node* langChild = new XMP_Node(arrayNode, "lang", "value");

    langChild->options |= kXMP_PropHasLang;



    arrayNode->children.push_back(simpleChild);

    arrayNode->children.push_back(nonSimpleChild);

    arrayNode->children.push_back(emptyChild);

    arrayNode->children.push_back(langChild);



    RepairAltText(*schemaNode, schemaNode->name.c_str(), arrayNode->name.c_str());



    EXPECT_EQ(arrayNode->children.size(), 2);

    EXPECT_STREQ(arrayNode->children[0]->name.c_str(), "simple");

    EXPECT_EQ(arrayNode->children[0]->qualifiers.size(), 1);

    EXPECT_STREQ(arrayNode->children[0]->qualifiers[0]->name.c_str(), "xml:lang");

    EXPECT_STREQ(arrayNode->children[0]->qualifiers[0]->value.c_str(), "x-repair");



    EXPECT_STREQ(arrayNode->children[1]->name.c_str(), "lang");

}
