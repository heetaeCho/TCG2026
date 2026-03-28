#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLTextShallowCloneTest_194 : public ::testing::Test {
protected:
    void SetUp() override {
        doc = new XMLDocument();
    }

    void TearDown() override {
        delete doc;
        if (otherDoc) {
            delete otherDoc;
        }
    }

    XMLDocument* doc = nullptr;
    XMLDocument* otherDoc = nullptr;
};

// Test: ShallowClone creates a copy of a normal text node in the same document
TEST_F(XMLTextShallowCloneTest_194, ShallowCloneNormalText_SameDocument_194) {
    const char* xml = "<root>Hello World</root>";
    doc->Parse(xml);

    XMLElement* root = doc->RootElement();
    ASSERT_NE(root, nullptr);

    XMLText* originalText = root->FirstChild()->ToText();
    ASSERT_NE(originalText, nullptr);

    XMLNode* cloned = originalText->ShallowClone(doc);
    ASSERT_NE(cloned, nullptr);

    XMLText* clonedText = cloned->ToText();
    ASSERT_NE(clonedText, nullptr);

    EXPECT_STREQ(clonedText->Value(), "Hello World");
    EXPECT_FALSE(clonedText->CData());

    doc->DeleteNode(cloned);
}

// Test: ShallowClone creates a copy of a CDATA text node
TEST_F(XMLTextShallowCloneTest_194, ShallowCloneCDataText_194) {
    const char* xml = "<root><![CDATA[Some CDATA content]]></root>";
    doc->Parse(xml);

    XMLElement* root = doc->RootElement();
    ASSERT_NE(root, nullptr);

    XMLText* originalText = root->FirstChild()->ToText();
    ASSERT_NE(originalText, nullptr);
    EXPECT_TRUE(originalText->CData());

    XMLNode* cloned = originalText->ShallowClone(doc);
    ASSERT_NE(cloned, nullptr);

    XMLText* clonedText = cloned->ToText();
    ASSERT_NE(clonedText, nullptr);

    EXPECT_STREQ(clonedText->Value(), "Some CDATA content");
    EXPECT_TRUE(clonedText->CData());

    doc->DeleteNode(cloned);
}

// Test: ShallowClone with a different target document
TEST_F(XMLTextShallowCloneTest_194, ShallowCloneToDifferentDocument_194) {
    const char* xml = "<root>Test text</root>";
    doc->Parse(xml);

    XMLElement* root = doc->RootElement();
    ASSERT_NE(root, nullptr);

    XMLText* originalText = root->FirstChild()->ToText();
    ASSERT_NE(originalText, nullptr);

    otherDoc = new XMLDocument();
    XMLNode* cloned = originalText->ShallowClone(otherDoc);
    ASSERT_NE(cloned, nullptr);

    XMLText* clonedText = cloned->ToText();
    ASSERT_NE(clonedText, nullptr);

    EXPECT_STREQ(clonedText->Value(), "Test text");
    EXPECT_EQ(clonedText->GetDocument(), otherDoc);

    otherDoc->DeleteNode(cloned);
}

// Test: ShallowClone with null document parameter uses the original document
TEST_F(XMLTextShallowCloneTest_194, ShallowCloneWithNullDoc_194) {
    const char* xml = "<root>Null doc test</root>";
    doc->Parse(xml);

    XMLElement* root = doc->RootElement();
    ASSERT_NE(root, nullptr);

    XMLText* originalText = root->FirstChild()->ToText();
    ASSERT_NE(originalText, nullptr);

    XMLNode* cloned = originalText->ShallowClone(nullptr);
    ASSERT_NE(cloned, nullptr);

    XMLText* clonedText = cloned->ToText();
    ASSERT_NE(clonedText, nullptr);

    EXPECT_STREQ(clonedText->Value(), "Null doc test");
    EXPECT_EQ(clonedText->GetDocument(), doc);

    doc->DeleteNode(cloned);
}

// Test: ShallowClone preserves CData=false when original is not CData
TEST_F(XMLTextShallowCloneTest_194, ShallowClonePreservesNonCData_194) {
    XMLText* text = doc->NewText("plain text");
    ASSERT_NE(text, nullptr);
    EXPECT_FALSE(text->CData());

    XMLNode* cloned = text->ShallowClone(doc);
    ASSERT_NE(cloned, nullptr);

    XMLText* clonedText = cloned->ToText();
    ASSERT_NE(clonedText, nullptr);

    EXPECT_STREQ(clonedText->Value(), "plain text");
    EXPECT_FALSE(clonedText->CData());

    doc->DeleteNode(text);
    doc->DeleteNode(cloned);
}

// Test: ShallowClone preserves CData=true when SetCData is explicitly called
TEST_F(XMLTextShallowCloneTest_194, ShallowClonePreservesCDataSetExplicitly_194) {
    XMLText* text = doc->NewText("cdata text");
    ASSERT_NE(text, nullptr);
    text->SetCData(true);
    EXPECT_TRUE(text->CData());

    XMLNode* cloned = text->ShallowClone(doc);
    ASSERT_NE(cloned, nullptr);

    XMLText* clonedText = cloned->ToText();
    ASSERT_NE(clonedText, nullptr);

    EXPECT_STREQ(clonedText->Value(), "cdata text");
    EXPECT_TRUE(clonedText->CData());

    doc->DeleteNode(text);
    doc->DeleteNode(cloned);
}

// Test: ShallowClone with empty text
TEST_F(XMLTextShallowCloneTest_194, ShallowCloneEmptyText_194) {
    XMLText* text = doc->NewText("");
    ASSERT_NE(text, nullptr);

    XMLNode* cloned = text->ShallowClone(doc);
    ASSERT_NE(cloned, nullptr);

    XMLText* clonedText = cloned->ToText();
    ASSERT_NE(clonedText, nullptr);

    EXPECT_STREQ(clonedText->Value(), "");

    doc->DeleteNode(text);
    doc->DeleteNode(cloned);
}

// Test: ShallowClone produces an independent node (modifying clone doesn't affect original)
TEST_F(XMLTextShallowCloneTest_194, ShallowCloneIsIndependent_194) {
    XMLText* text = doc->NewText("original");
    ASSERT_NE(text, nullptr);
    text->SetCData(false);

    XMLNode* cloned = text->ShallowClone(doc);
    ASSERT_NE(cloned, nullptr);

    XMLText* clonedText = cloned->ToText();
    ASSERT_NE(clonedText, nullptr);

    // Modify clone's CData
    clonedText->SetCData(true);

    // Original should remain unchanged
    EXPECT_FALSE(text->CData());
    EXPECT_TRUE(clonedText->CData());

    doc->DeleteNode(text);
    doc->DeleteNode(cloned);
}

// Test: ShallowClone of text with special characters
TEST_F(XMLTextShallowCloneTest_194, ShallowCloneSpecialCharacters_194) {
    const char* xml = "<root>Text with &amp; and &lt; entities</root>";
    doc->Parse(xml);

    XMLElement* root = doc->RootElement();
    ASSERT_NE(root, nullptr);

    XMLText* originalText = root->FirstChild()->ToText();
    ASSERT_NE(originalText, nullptr);

    XMLNode* cloned = originalText->ShallowClone(doc);
    ASSERT_NE(cloned, nullptr);

    XMLText* clonedText = cloned->ToText();
    ASSERT_NE(clonedText, nullptr);

    EXPECT_STREQ(clonedText->Value(), originalText->Value());

    doc->DeleteNode(cloned);
}

// Test: ShallowClone CDATA to different document preserves CData flag
TEST_F(XMLTextShallowCloneTest_194, ShallowCloneCDataToDifferentDocument_194) {
    const char* xml = "<root><![CDATA[cross doc cdata]]></root>";
    doc->Parse(xml);

    XMLElement* root = doc->RootElement();
    ASSERT_NE(root, nullptr);

    XMLText* originalText = root->FirstChild()->ToText();
    ASSERT_NE(originalText, nullptr);
    EXPECT_TRUE(originalText->CData());

    otherDoc = new XMLDocument();
    XMLNode* cloned = originalText->ShallowClone(otherDoc);
    ASSERT_NE(cloned, nullptr);

    XMLText* clonedText = cloned->ToText();
    ASSERT_NE(clonedText, nullptr);

    EXPECT_STREQ(clonedText->Value(), "cross doc cdata");
    EXPECT_TRUE(clonedText->CData());
    EXPECT_EQ(clonedText->GetDocument(), otherDoc);

    otherDoc->DeleteNode(cloned);
}

// Test: ShallowClone result is not attached to any parent
TEST_F(XMLTextShallowCloneTest_194, ShallowCloneHasNoParent_194) {
    const char* xml = "<root>Parented text</root>";
    doc->Parse(xml);

    XMLElement* root = doc->RootElement();
    ASSERT_NE(root, nullptr);

    XMLText* originalText = root->FirstChild()->ToText();
    ASSERT_NE(originalText, nullptr);
    EXPECT_NE(originalText->Parent(), nullptr);

    XMLNode* cloned = originalText->ShallowClone(doc);
    ASSERT_NE(cloned, nullptr);

    // The cloned node should not have a parent since it's unlinked
    EXPECT_EQ(cloned->Parent(), nullptr);

    doc->DeleteNode(cloned);
}

// Test: ShallowEqual between original and clone returns true
TEST_F(XMLTextShallowCloneTest_194, ShallowCloneIsShallowEqual_194) {
    XMLText* text = doc->NewText("equality test");
    ASSERT_NE(text, nullptr);

    XMLNode* cloned = text->ShallowClone(doc);
    ASSERT_NE(cloned, nullptr);

    EXPECT_TRUE(text->ShallowEqual(cloned));
    EXPECT_TRUE(cloned->ShallowEqual(text));

    doc->DeleteNode(text);
    doc->DeleteNode(cloned);
}

// Test: ShallowClone of text with long content
TEST_F(XMLTextShallowCloneTest_194, ShallowCloneLongText_194) {
    std::string longStr(10000, 'A');
    XMLText* text = doc->NewText(longStr.c_str());
    ASSERT_NE(text, nullptr);

    XMLNode* cloned = text->ShallowClone(doc);
    ASSERT_NE(cloned, nullptr);

    XMLText* clonedText = cloned->ToText();
    ASSERT_NE(clonedText, nullptr);

    EXPECT_STREQ(clonedText->Value(), longStr.c_str());

    doc->DeleteNode(text);
    doc->DeleteNode(cloned);
}
