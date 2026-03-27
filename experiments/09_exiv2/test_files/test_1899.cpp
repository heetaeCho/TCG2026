#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming necessary headers are included for XMP_Node, XMP_ExpandedXPath, etc.



class XMPCoreTest : public ::testing::Test {

protected:

    // Setup and teardown can be added here if needed

};



TEST_F(XMPCoreTest_1899, FindNode_NormalOperation_1899) {

    // Arrange

    XMP_Node root(nullptr, "Root", 0);

    XMP_ExpandedXPath xpath;

    xpath.push_back(XPathStepInfo("schema", 0));

    xpath.push_back(XPathStepInfo("rootprop", 0));



    // Act

    XMP_Node* result = FindNode(&root, xpath, true);



    // Assert

    EXPECT_NE(result, nullptr);

    EXPECT_EQ(result->name, "rootprop");

}



TEST_F(XMPCoreTest_1899, FindNode_EmptyXPath_ThrowsError_1899) {

    // Arrange

    XMP_Node root(nullptr, "Root", 0);

    XMP_ExpandedXPath xpath;



    // Act & Assert

    EXPECT_THROW(FindNode(&root, xpath, true), XMP_Error);

}



TEST_F(XMPCoreTest_1899, FindNode_CreateNodesFalse_ReturnsNull_1899) {

    // Arrange

    XMP_Node root(nullptr, "Root", 0);

    XMP_ExpandedXPath xpath;

    xpath.push_back(XPathStepInfo("schema", 0));

    xpath.push_back(XPathStepInfo("rootprop", 0));



    // Act

    XMP_Node* result = FindNode(&root, xpath, false);



    // Assert

    EXPECT_EQ(result, nullptr);

}



TEST_F(XMPCoreTest_1899, FindNode_AliasPath_1899) {

    // Arrange

    XMP_Node root(nullptr, "Root", 0);

    XMP_ExpandedXPath aliasPath;

    aliasPath.push_back(XPathStepInfo("aliasprop", kXMP_StepIsAlias));

    aliasPath.push_back(XPathStepInfo("schema", 0));

    aliasPath.push_back(XPathStepInfo("rootprop", 0));



    // Assuming sRegisteredAliasMap is set up properly

    XPathStepInfo schemaStep("schema", 0);

    XPathStepInfo rootPropStep("rootprop", 0);

    XMP_ExpandedXPath resolvedPath = {schemaStep, rootPropStep};

    (*sRegisteredAliasMap)[aliasPath[0].step] = resolvedPath;



    // Act

    XMP_Node* result = FindNode(&root, aliasPath, true);



    // Assert

    EXPECT_NE(result, nullptr);

    EXPECT_EQ(result->name, "rootprop");

}



TEST_F(XMPCoreTest_1899, FindNode_ArrayFormPath_1899) {

    // Arrange

    XMP_Node root(nullptr, "Root", 0);

    XMP_ExpandedXPath arrayPath;

    arrayPath.push_back(XPathStepInfo("arrayprop", kXMP_PropArrayIsOrdered | kXMP_StepIsAlias));

    arrayPath.push_back(XPathStepInfo("schema", 0));

    arrayPath.push_back(XPathStepInfo("rootprop", 0));

    arrayPath.push_back(XPathStepInfo("item1", kXMP_ArrayIndexStep));



    // Assuming sRegisteredAliasMap is set up properly

    XPathStepInfo schemaStep("schema", 0);

    XPathStepInfo rootPropStep("rootprop", 0);

    XMP_ExpandedXPath resolvedPath = {schemaStep, rootPropStep};

    (*sRegisteredAliasMap)[arrayPath[0].step] = resolvedPath;



    // Act

    XMP_Node* result = FindNode(&root, arrayPath, true);



    // Assert

    EXPECT_NE(result, nullptr);

    EXPECT_EQ(result->name, "item1");

}



TEST_F(XMPCoreTest_1899, FindNode_BoundaryCondition_EmptySchemaStep_1899) {

    // Arrange

    XMP_Node root(nullptr, "Root", 0);

    XMP_ExpandedXPath xpath;

    xpath.push_back(XPathStepInfo("", 0));

    xpath.push_back(XPathStepInfo("rootprop", 0));



    // Act & Assert

    EXPECT_THROW(FindNode(&root, xpath, true), XMP_Error);

}



TEST_F(XMPCoreTest_1899, FindNode_BoundaryCondition_EmptyRootPropStep_1899) {

    // Arrange

    XMP_Node root(nullptr, "Root", 0);

    XMP_ExpandedXPath xpath;

    xpath.push_back(XPathStepInfo("schema", 0));

    xpath.push_back(XPathStepInfo("", 0));



    // Act & Assert

    EXPECT_THROW(FindNode(&root, xpath, true), XMP_Error);

}
