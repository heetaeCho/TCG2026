#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mocking XMP_Throw to verify that it gets called with specific error codes and messages.

class MockXMP {

public:

    MOCK_STATIC(void, XMP_Throw, (const std::string& message, int errorCode));

};



using ::testing::_;



namespace {



TEST(CompareAliasedSubtreesTest_1962, MatchingNodesNoChildrenNoQualifiers_1962) {

    XMP_Node baseNode(nullptr, "name", "value", 0);

    XMP_Node aliasNode(nullptr, "name", "value", 0);



    EXPECT_NO_THROW(CompareAliasedSubtrees(&aliasNode, &baseNode));

}



TEST(CompareAliasedSubtreesTest_1962, MatchingNodesWithChildrenNoQualifiers_1962) {

    XMP_Node baseParent(nullptr, "parentName", "parentValue", 0);

    XMP_Node aliasParent(nullptr, "parentName", "parentValue", 0);



    XMP_Node baseChild(&baseParent, "childName", "childValue", 0);

    XMP_Node aliasChild(&aliasParent, "childName", "childValue", 0);



    baseParent.children.push_back(&baseChild);

    aliasParent.children.push_back(&aliasChild);



    EXPECT_NO_THROW(CompareAliasedSubtrees(&aliasParent, &baseParent));

}



TEST(CompareAliasedSubtreesTest_1962, MatchingNodesNoChildrenWithQualifiers_1962) {

    XMP_Node baseNode(nullptr, "name", "value", 0);

    XMP_Node aliasNode(nullptr, "name", "value", 0);



    XMP_Node baseQualifier(&baseNode, "qualifierName", "qualifierValue", 0);

    XMP_Node aliasQualifier(&aliasNode, "qualifierName", "qualifierValue", 0);



    baseNode.qualifiers.push_back(&baseQualifier);

    aliasNode.qualifiers.push_back(&aliasQualifier);



    EXPECT_NO_THROW(CompareAliasedSubtrees(&aliasNode, &baseNode));

}



TEST(CompareAliasedSubtreesTest_1962, MismatchedValues_1962) {

    XMP_Node baseNode(nullptr, "name", "value", 0);

    XMP_Node aliasNode(nullptr, "name", "differentValue", 0);



    EXPECT_CALL(MockXMP::XMP_Throw, ("Mismatch between alias and base nodes", kXMPErr_BadXMP)).Times(1);



    CompareAliasedSubtrees(&aliasNode, &baseNode);

}



TEST(CompareAliasedSubtreesTest_1962, MismatchedChildrenCount_1962) {

    XMP_Node baseParent(nullptr, "parentName", "parentValue", 0);

    XMP_Node aliasParent(nullptr, "parentName", "parentValue", 0);



    XMP_Node baseChild(&baseParent, "childName", "childValue", 0);

    baseParent.children.push_back(&baseChild);



    EXPECT_CALL(MockXMP::XMP_Throw, ("Mismatch between alias and base nodes", kXMPErr_BadXMP)).Times(1);



    CompareAliasedSubtrees(&aliasParent, &baseParent);

}



TEST(CompareAliasedSubtreesTest_1962, MismatchedQualifiersCount_1962) {

    XMP_Node baseNode(nullptr, "name", "value", 0);

    XMP_Node aliasNode(nullptr, "name", "value", 0);



    XMP_Node baseQualifier(&baseNode, "qualifierName", "qualifierValue", 0);

    baseNode.qualifiers.push_back(&baseQualifier);



    EXPECT_CALL(MockXMP::XMP_Throw, ("Mismatch between alias and base nodes", kXMPErr_BadXMP)).Times(1);



    CompareAliasedSubtrees(&aliasNode, &baseNode);

}



TEST(CompareAliasedSubtreesTest_1962, MismatchedChildNodes_1962) {

    XMP_Node baseParent(nullptr, "parentName", "parentValue", 0);

    XMP_Node aliasParent(nullptr, "parentName", "parentValue", 0);



    XMP_Node baseChild(&baseParent, "childName", "childValue", 0);

    XMP_Node aliasChild(&aliasParent, "differentChildName", "differentChildValue", 0);



    baseParent.children.push_back(&baseChild);

    aliasParent.children.push_back(&aliasChild);



    EXPECT_CALL(MockXMP::XMP_Throw, ("Mismatch between alias and base nodes", kXMPErr_BadXMP)).Times(1);



    CompareAliasedSubtrees(&aliasParent, &baseParent);

}



TEST(CompareAliasedSubtreesTest_1962, MismatchedQualifierNodes_1962) {

    XMP_Node baseNode(nullptr, "name", "value", 0);

    XMP_Node aliasNode(nullptr, "name", "value", 0);



    XMP_Node baseQualifier(&baseNode, "qualifierName", "qualifierValue", 0);

    XMP_Node aliasQualifier(&aliasNode, "differentQualifierName", "differentQualifierValue", 0);



    baseNode.qualifiers.push_back(&baseQualifier);

    aliasNode.qualifiers.push_back(&aliasQualifier);



    EXPECT_CALL(MockXMP::XMP_Throw, ("Mismatch between alias and base nodes", kXMPErr_BadXMP)).Times(1);



    CompareAliasedSubtrees(&aliasNode, &baseNode);

}



TEST(CompareAliasedSubtreesTest_1962, MatchingNestedNodes_1962) {

    XMP_Node baseGrandParent(nullptr, "grandparentName", "grandparentValue", 0);

    XMP_Node aliasGrandParent(nullptr, "grandparentName", "grandparentValue", 0);



    XMP_Node baseParent(&baseGrandParent, "parentName", "parentValue", 0);

    XMP_Node aliasParent(&aliasGrandParent, "parentName", "parentValue", 0);



    XMP_Node baseChild(&baseParent, "childName", "childValue", 0);

    XMP_Node aliasChild(&aliasParent, "childName", "childValue", 0);



    baseParent.children.push_back(&baseChild);

    aliasParent.children.push_back(&aliasChild);



    baseGrandParent.children.push_back(&baseParent);

    aliasGrandParent.children.push_back(&aliasParent);



    EXPECT_NO_THROW(CompareAliasedSubtrees(&aliasGrandParent, &baseGrandParent));

}



TEST(CompareAliasedSubtreesTest_1962, MismatchedNestedNodes_1962) {

    XMP_Node baseGrandParent(nullptr, "grandparentName", "grandparentValue", 0);

    XMP_Node aliasGrandParent(nullptr, "grandparentName", "grandparentValue", 0);



    XMP_Node baseParent(&baseGrandParent, "parentName", "parentValue", 0);

    XMP_Node aliasParent(&aliasGrandParent, "differentParentName", "differentParentValue", 0);



    XMP_Node baseChild(&baseParent, "childName", "childValue", 0);

    XMP_Node aliasChild(&aliasParent, "childName", "childValue", 0);



    baseParent.children.push_back(&baseChild);

    aliasParent.children.push_back(&aliasChild);



    baseGrandParent.children.push_back(&baseParent);

    aliasGrandParent.children.push_back(&aliasParent);



    EXPECT_CALL(MockXMP::XMP_Throw, ("Mismatch between alias and base nodes", kXMPErr_BadXMP)).Times(1);



    CompareAliasedSubtrees(&aliasGrandParent, &baseGrandParent);

}



} // namespace
