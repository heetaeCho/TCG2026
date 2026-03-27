#include <gtest/gtest.h>

#include "XMPMeta-GetSet.cpp"

#include "XMPCore_Impl.hpp"

#include "XMP_Const.h"



// Mocking XMP_Node for testing purposes

class MockXMPNode : public XMP_Node {

public:

    MOCK_CONST_METHOD0(children, const XMP_NodeOffspring&());

    MOCK_CONST_METHOD0(qualifiers, const XMP_NodeOffspring&());

    MOCK_CONST_METHOD0(options, XMP_OptionBits());

};



// Helper function to create a node with qualifiers

XMP_Node* CreateNodeWithQualifier(XMP_StringPtr name, XMP_StringPtr value, XMP_StringPtr qualifierName, XMP_StringPtr qualifierValue) {

    auto* node = new MockXMPNode();

    auto* qualifierNode = new XMP_Node(nullptr, qualifierName, qualifierValue, kXMP_PropIsQualifier);

    node->qualifiers.push_back(qualifierNode);

    return node;

}



class ChooseLocalizedTextTest_1927 : public ::testing::Test {

protected:

    void SetUp() override {

        arrayNode = new MockXMPNode();

        itemNode = nullptr;

    }



    void TearDown() override {

        delete arrayNode;

        delete itemNode;

    }



    MockXMPNode* arrayNode;

    const XMP_Node** itemNode;

};



TEST_F(ChooseLocalizedTextTest_1927, NonAltTextArray_ThrowsError_1927) {

    EXPECT_CALL(*arrayNode, options()).WillRepeatedly(testing::Return(kXMP_PropValueIsURI));

    EXPECT_THROW(ChooseLocalizedText(arrayNode, "en", "en-US", itemNode), XMP_Error);

}



TEST_F(ChooseLocalizedTextTest_1927, EmptyArray_ReturnsNoValues_1927) {

    EXPECT_CALL(*arrayNode, options()).WillRepeatedly(testing::Return(kXMP_PropArrayIsAltText));

    EXPECT_CALL(*arrayNode, children()).WillOnce(testing::ReturnRef(emptyChildren));

    XMP_CLTMatch result = ChooseLocalizedText(arrayNode, "en", "en-US", itemNode);

    EXPECT_EQ(result, kXMP_CLT_NoValues);

}



TEST_F(ChooseLocalizedTextTest_1927, CompositeItem_ThrowsError_1927) {

    auto* compositeNode = new MockXMPNode();

    EXPECT_CALL(*compositeNode, options()).WillRepeatedly(testing::Return(kXMP_PropCompositeMask));

    arrayNode->children.push_back(compositeNode);

    EXPECT_THROW(ChooseLocalizedText(arrayNode, "en", "en-US", itemNode), XMP_Error);

}



TEST_F(ChooseLocalizedTextTest_1927, ItemWithoutLangQualifier_ThrowsError_1927) {

    auto* nodeWithoutLang = new MockXMPNode();

    arrayNode->children.push_back(nodeWithoutLang);

    EXPECT_THROW(ChooseLocalizedText(arrayNode, "en", "en-US", itemNode), XMP_Error);

}



TEST_F(ChooseLocalizedTextTest_1927, SpecificLanguageMatch_ReturnsSpecificMatch_1927) {

    auto* nodeEnUS = CreateNodeWithQualifier("node", "value", "xml:lang", "en-US");

    arrayNode->children.push_back(nodeEnUS);

    XMP_CLTMatch result = ChooseLocalizedText(arrayNode, "en", "en-US", itemNode);

    EXPECT_EQ(result, kXMP_CLT_SpecificMatch);

}



TEST_F(ChooseLocalizedTextTest_1927, GenericLanguageMatch_ReturnsSingleGeneric_1927) {

    auto* nodeEn = CreateNodeWithQualifier("node", "value", "xml:lang", "en");

    arrayNode->children.push_back(nodeEn);

    XMP_CLTMatch result = ChooseLocalizedText(arrayNode, "en", "fr-FR", itemNode);

    EXPECT_EQ(result, kXMP_CLT_SingleGeneric);

}



TEST_F(ChooseLocalizedTextTest_1927, MultipleGenericLanguageMatches_ReturnsMultipleGeneric_1927) {

    auto* nodeEn = CreateNodeWithQualifier("node", "value", "xml:lang", "en");

    arrayNode->children.push_back(nodeEn);

    auto* nodeEnUS = CreateNodeWithQualifier("node", "value", "xml:lang", "en-US");

    arrayNode->children.push_back(nodeEnUS);

    XMP_CLTMatch result = ChooseLocalizedText(arrayNode, "en", "fr-FR", itemNode);

    EXPECT_EQ(result, kXMP_CLT_MultipleGeneric);

}



TEST_F(ChooseLocalizedTextTest_1927, XDefaultLanguage_ReturnsXDefault_1927) {

    auto* nodeXDefault = CreateNodeWithQualifier("node", "value", "xml:lang", "x-default");

    arrayNode->children.push_back(nodeXDefault);

    XMP_CLTMatch result = ChooseLocalizedText(arrayNode, "en", "fr-FR", itemNode);

    EXPECT_EQ(result, kXMP_CLT_XDefault);

}



TEST_F(ChooseLocalizedTextTest_1927, NoMatchingLanguage_ReturnsFirstItem_1927) {

    auto* nodeFrFR = CreateNodeWithQualifier("node", "value", "xml:lang", "fr-FR");

    arrayNode->children.push_back(nodeFrFR);

    XMP_CLTMatch result = ChooseLocalizedText(arrayNode, "en", "en-US", itemNode);

    EXPECT_EQ(result, kXMP_CLT_FirstItem);

}



XMP_NodeOffspring emptyChildren;
