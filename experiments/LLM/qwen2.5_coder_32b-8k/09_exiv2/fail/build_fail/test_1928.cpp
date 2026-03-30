#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mocking XMP_Node for testing AppendLangItem function.

class MockXMP_Node : public XMP_Node {

public:

    MockXMP_Node(XMP_Node* _parent, XMP_StringPtr _name, XMP_OptionBits _options)

        : XMP_Node(_parent, _name, _options) {}



    MOCK_METHOD(void, RemoveChildren, (), (override));

    MOCK_METHOD(void, RemoveQualifiers, (), (override));

    MOCK_METHOD(void, ClearNode, (), (override));

};



TEST(AppendLangItemTest_1928, NormalOperationWithNonDefaultLanguage_1928) {

    XMP_Node arrayNode(nullptr, "array", kXMP_PropValueIsArray);

    AppendLangItem(&arrayNode, "en-US", "Hello");



    EXPECT_EQ(arrayNode.children.size(), 1);

    XMP_Node* newItem = arrayNode.children.front();

    EXPECT_EQ(newItem->name, kXMP_ArrayItemName);

    EXPECT_EQ(newItem->value, "Hello");

    EXPECT_EQ(newItem->options & kXMP_PropHasQualifiers, kXMP_PropHasQualifiers);

    EXPECT_EQ(newItem->options & kXMP_PropHasLang, kXMP_PropHasLang);



    EXPECT_EQ(newItem->qualifiers.size(), 1);

    XMP_Node* langQual = newItem->qualifiers.front();

    EXPECT_EQ(langQual->name, "xml:lang");

    EXPECT_EQ(langQual->value, "en-US");

    EXPECT_EQ(langQual->options & kXMP_PropIsQualifier, kXMP_PropIsQualifier);



    EXPECT_EQ(newItem->parent, &arrayNode);

}



TEST(AppendLangItemTest_1928, NormalOperationWithDefaultLanguage_1928) {

    XMP_Node arrayNode(nullptr, "array", kXMP_PropValueIsArray);

    AppendLangItem(&arrayNode, "x-default", "Hello");



    EXPECT_EQ(arrayNode.children.size(), 1);

    XMP_Node* newItem = arrayNode.children.front();

    EXPECT_EQ(newItem->name, kXMP_ArrayItemName);

    EXPECT_EQ(newItem->value, "Hello");

    EXPECT_EQ(newItem->options & kXMP_PropHasQualifiers, kXMP_PropHasQualifiers);

    EXPECT_EQ(newItem->options & kXMP_PropHasLang, kXMP_PropHasLang);



    EXPECT_EQ(newItem->qualifiers.size(), 1);

    XMP_Node* langQual = newItem->qualifiers.front();

    EXPECT_EQ(langQual->name, "xml:lang");

    EXPECT_EQ(langQual->value, "x-default");

    EXPECT_EQ(langQual->options & kXMP_PropIsQualifier, kXMP_PropIsQualifier);



    EXPECT_EQ(newItem->parent, &arrayNode);

}



TEST(AppendLangItemTest_1928, BoundaryConditionEmptyChildrenList_1928) {

    XMP_Node arrayNode(nullptr, "array", kXMP_PropValueIsArray);

    AppendLangItem(&arrayNode, "x-default", "Hello");



    EXPECT_EQ(arrayNode.children.size(), 1);

    XMP_Node* newItem = arrayNode.children.front();

    EXPECT_EQ(newItem->name, kXMP_ArrayItemName);

    EXPECT_EQ(newItem->value, "Hello");

    EXPECT_EQ(newItem->options & kXMP_PropHasQualifiers, kXMP_PropHasQualifiers);

    EXPECT_EQ(newItem->options & kXMP_PropHasLang, kXMP_PropHasLang);



    EXPECT_EQ(newItem->qualifiers.size(), 1);

    XMP_Node* langQual = newItem->qualifiers.front();

    EXPECT_EQ(langQual->name, "xml:lang");

    EXPECT_EQ(langQual->value, "x-default");

    EXPECT_EQ(langQual->options & kXMP_PropIsQualifier, kXMP_PropIsQualifier);



    EXPECT_EQ(newItem->parent, &arrayNode);

}



TEST(AppendLangItemTest_1928, ExceptionalCaseNullParent_1928) {

    XMP_Node* arrayNode = nullptr;

    EXPECT_NO_THROW(AppendLangItem(arrayNode, "en-US", "Hello"));

}



TEST(AppendLangItemTest_1928, VerificationOfChildInsertionOrderWithDefaultLanguage_1928) {

    XMP_Node arrayNode(nullptr, "array", kXMP_PropValueIsArray);

    AppendLangItem(&arrayNode, "x-default", "Hello");

    AppendLangItem(&arrayNode, "en-US", "World");



    EXPECT_EQ(arrayNode.children.size(), 2);

    XMP_Node* newItem1 = arrayNode.children.front();

    XMP_Node* newItem2 = arrayNode.children.back();



    EXPECT_EQ(newItem1->qualifiers.front()->value, "x-default");

    EXPECT_EQ(newItem2->qualifiers.front()->value, "en-US");



    EXPECT_EQ(newItem1->parent, &arrayNode);

    EXPECT_EQ(newItem2->parent, &arrayNode);

}



TEST(AppendLangItemTest_1928, VerificationOfChildInsertionOrderWithNonDefaultLanguages_1928) {

    XMP_Node arrayNode(nullptr, "array", kXMP_PropValueIsArray);

    AppendLangItem(&arrayNode, "en-US", "Hello");

    AppendLangItem(&arrayNode, "fr-FR", "World");



    EXPECT_EQ(arrayNode.children.size(), 2);

    XMP_Node* newItem1 = arrayNode.children.front();

    XMP_Node* newItem2 = arrayNode.children.back();



    EXPECT_EQ(newItem1->qualifiers.front()->value, "en-US");

    EXPECT_EQ(newItem2->qualifiers.front()->value, "fr-FR");



    EXPECT_EQ(newItem1->parent, &arrayNode);

    EXPECT_EQ(newItem2->parent, &arrayNode);

}
