#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/exiv2/xmpsdk/src/XMPMeta-GetSet.cpp"

// Mock classes for external dependencies
class XMP_NodeMock : public XMP_Node {
public:
    MOCK_METHOD(void, RemoveChildren, (), (override));
    MOCK_METHOD(void, RemoveQualifiers, (), (override));
    MOCK_METHOD(void, ClearNode, (), (override));
};

// Test fixture for AppendLangItem tests
class XMPMetaTest_1928 : public ::testing::Test {
protected:
    XMP_Node *arrayNode;
    XMP_Node *itemNode;
    XMP_Node *langQualNode;

    void SetUp() override {
        arrayNode = new XMP_Node(nullptr, "ArrayNode", kXMP_PropHasLang);
        itemNode = new XMP_Node(arrayNode, "Item", "ItemValue", kXMP_PropHasLang | kXMP_PropHasQualifiers);
        langQualNode = new XMP_Node(itemNode, "xml:lang", "en", kXMP_PropIsQualifier);
    }

    void TearDown() override {
        delete arrayNode;
        delete itemNode;
        delete langQualNode;
    }
};

// Normal operation test
TEST_F(XMPMetaTest_1928, AppendLangItem_NormalOperation_1928) {
    AppendLangItem(arrayNode, "en", "ItemValue");
    ASSERT_EQ(arrayNode->children.size(), 1);
    ASSERT_EQ(arrayNode->children.front()->value, "ItemValue");
    ASSERT_EQ(arrayNode->children.front()->qualifiers.front()->value, "en");
}

// Test for boundary condition where the arrayNode has no children
TEST_F(XMPMetaTest_1928, AppendLangItem_EmptyNode_1928) {
    XMP_Node *emptyNode = new XMP_Node(nullptr, "EmptyNode", kXMP_PropHasLang);
    AppendLangItem(emptyNode, "fr", "AnotherItem");
    ASSERT_EQ(emptyNode->children.size(), 1);
    ASSERT_EQ(emptyNode->children.front()->value, "AnotherItem");
    delete emptyNode;
}

// Boundary condition for "x-default" lang qualifier
TEST_F(XMPMetaTest_1928, AppendLangItem_XDefaultLang_1928) {
    AppendLangItem(arrayNode, "x-default", "DefaultItem");
    ASSERT_EQ(arrayNode->children.size(), 1);
    ASSERT_EQ(arrayNode->children.front()->value, "DefaultItem");
    ASSERT_EQ(arrayNode->children.front()->qualifiers.front()->value, "x-default");
}

// Exceptional case: Invalid lang value
TEST_F(XMPMetaTest_1928, AppendLangItem_InvalidLang_1928) {
    ASSERT_THROW(AppendLangItem(arrayNode, "", "InvalidLangItem"), std::invalid_argument);
}

// Exceptional case: Null arrayNode passed
TEST_F(XMPMetaTest_1928, AppendLangItem_NullArrayNode_1928) {
    ASSERT_THROW(AppendLangItem(nullptr, "en", "NullArrayNodeItem"), std::invalid_argument);
}