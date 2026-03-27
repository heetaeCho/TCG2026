#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mocking external dependencies if necessary

class XMP_Node_Mock : public XMP_Node {

public:

    MOCK_METHOD(void, RemoveChildren, (), (override));

    MOCK_METHOD(void, RemoveQualifiers, (), (override));

    MOCK_METHOD(void, ClearNode, (), (override));

};



TEST_F(XMPMeta_ParseTest_1965, NormalOperation_NoAliases_1965) {

    XMP_Node tree(nullptr, "root", 0);

    XMP_OptionBits parseOptions = 0;



    MoveExplicitAliases(&tree, parseOptions);



    // No aliases should be present in the root node or its children

    EXPECT_EQ(tree.children.size(), 0);

}



TEST_F(XMPMeta_ParseTest_1965, NormalOperation_SingleAlias_1965) {

    XMP_Node tree(nullptr, "root", kXMP_PropHasAliases);

    XMP_Node schemaNode(&tree, "schema", kXMP_CreateNodes);

    tree.children.push_back(&schemaNode);

    XMP_Node propNode(&schemaNode, "prop", kXMP_PropIsAlias);

    schemaNode.children.push_back(&propNode);



    // Mocking the global map for aliases

    XPathStepInfo step1("root", 0);

    XPathStepInfo step2("prop", 0);

    XMP_ExpandedXPath basePath = {step1, step2};

    (*sRegisteredAliasMap)["prop"] = basePath;



    XMP_OptionBits parseOptions = 0;

    MoveExplicitAliases(&tree, parseOptions);



    // Alias should be removed from the schema node

    EXPECT_EQ(schemaNode.children.size(), 0);

}



TEST_F(XMPMeta_ParseTest_1965, BoundaryConditions_EmptyTree_1965) {

    XMP_Node tree(nullptr, "root", 0);

    XMP_OptionBits parseOptions = kXMP_StrictAliasing;



    MoveExplicitAliases(&tree, parseOptions);



    // Tree should remain empty

    EXPECT_EQ(tree.children.size(), 0);

}



TEST_F(XMPMeta_ParseTest_1965, BoundaryConditions_NoSchemaChildren_1965) {

    XMP_Node tree(nullptr, "root", kXMP_PropHasAliases);

    XMP_OptionBits parseOptions = kXMP_StrictAliasing;



    MoveExplicitAliases(&tree, parseOptions);



    // Tree should remain unchanged

    EXPECT_EQ(tree.children.size(), 0);

}



TEST_F(XMPMeta_ParseTest_1965, ExceptionalCases_MissingAliasInMap_1965) {

    XMP_Node tree(nullptr, "root", kXMP_PropHasAliases);

    XMP_Node schemaNode(&tree, "schema", kXMP_CreateNodes);

    tree.children.push_back(&schemaNode);

    XMP_Node propNode(&schemaNode, "prop", kXMP_PropIsAlias);

    schemaNode.children.push_back(&propNode);



    // Not adding the alias to the global map

    XMP_OptionBits parseOptions = kXMP_StrictAliasing;



    EXPECT_DEATH(MoveExplicitAliases(&tree, parseOptions), ".*Assertion `aliasPos != sRegisteredAliasMap->end().*");

}



TEST_F(XMPMeta_ParseTest_1965, ExternalInteractions_TransplantNamedAlias_1965) {

    // This test requires mocking XMP_Node to verify internal interactions

    // However, we cannot mock internal behavior. Therefore, this test is limited.

    XMP_Node tree(nullptr, "root", kXMP_PropHasAliases);

    XMP_Node schemaNode(&tree, "schema", kXMP_CreateNodes);

    tree.children.push_back(&schemaNode);

    XMP_Node propNode(&schemaNode, "prop", kXMP_PropIsAlias);

    schemaNode.children.push_back(&propNode);



    // Mocking the global map for aliases

    XPathStepInfo step1("root", 0);

    XPathStepInfo step2("prop", 0);

    XMP_ExpandedXPath basePath = {step1, step2};

    (*sRegisteredAliasMap)["prop"] = basePath;



    XMP_OptionBits parseOptions = kXMP_StrictAliasing;

    MoveExplicitAliases(&tree, parseOptions);



    // Alias should be removed from the schema node

    EXPECT_EQ(schemaNode.children.size(), 0);

}



TEST_F(XMPMeta_ParseTest_1965, ExternalInteractions_TransplantArrayItemAlias_1965) {

    // This test requires mocking XMP_Node to verify internal interactions

    // However, we cannot mock internal behavior. Therefore, this test is limited.

    XMP_Node tree(nullptr, "root", kXMP_PropHasAliases);

    XMP_Node schemaNode(&tree, "schema", kXMP_CreateNodes);

    tree.children.push_back(&schemaNode);

    XMP_OptionBits arrayOptions = kXMP_PropArrayIsAltText;

    XMP_Node propNode(&schemaNode, "prop", arrayOptions | kXMP_PropIsAlias);

    schemaNode.children.push_back(&propNode);



    // Mocking the global map for aliases

    XPathStepInfo step1("root", 0);

    XPathStepInfo step2("prop", arrayOptions);

    XMP_ExpandedXPath basePath = {step1, step2};

    (*sRegisteredAliasMap)["prop"] = basePath;



    XMP_OptionBits parseOptions = kXMP_StrictAliasing;

    MoveExplicitAliases(&tree, parseOptions);



    // Alias should be removed from the schema node

    EXPECT_EQ(schemaNode.children.size(), 0);

}



TEST_F(XMPMeta_ParseTest_1965, StrictAliasing_CompareAliasedSubtrees_1965) {

    XMP_Node tree(nullptr, "root", kXMP_PropHasAliases);

    XMP_Node schemaNode(&tree, "schema", kXMP_CreateNodes);

    tree.children.push_back(&schemaNode);



    // Create an alias property

    XMP_OptionBits arrayOptions = 0;

    XMP_Node propNode(&schemaNode, "prop", arrayOptions | kXMP_PropIsAlias);

    schemaNode.children.push_back(&propNode);



    // Mocking the global map for aliases

    XPathStepInfo step1("root", 0);

    XPathStepInfo step2("prop", arrayOptions);

    XMP_ExpandedXPath basePath = {step1, step2};

    (*sRegisteredAliasMap)["prop"] = basePath;



    // Create a base node to compare against

    XMP_Node baseSchemaNode(&tree, "schema", kXMP_CreateNodes);

    tree.children.push_back(&baseSchemaNode);

    XMP_Node basePropNode(&baseSchemaNode, "prop", arrayOptions);

    baseSchemaNode.children.push_back(&basePropNode);



    XMP_OptionBits parseOptions = kXMP_StrictAliasing;

    MoveExplicitAliases(&tree, parseOptions);



    // Alias should be removed from the schema node

    EXPECT_EQ(schemaNode.children.size(), 0);

}
