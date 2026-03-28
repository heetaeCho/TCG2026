#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

// Test fixture for DeepCopy tests
class XMLDocumentDeepCopyTest_271 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test DeepCopy with an empty document
TEST_F(XMLDocumentDeepCopyTest_271, DeepCopyEmptyDocument_271) {
    XMLDocument source;
    XMLDocument target;
    
    source.DeepCopy(&target);
    
    EXPECT_TRUE(target.NoChildren());
    EXPECT_FALSE(target.Error());
}

// Test DeepCopy with a simple XML document
TEST_F(XMLDocumentDeepCopyTest_271, DeepCopySimpleDocument_271) {
    XMLDocument source;
    source.Parse("<root><child>text</child></root>");
    ASSERT_FALSE(source.Error());
    
    XMLDocument target;
    source.DeepCopy(&target);
    
    ASSERT_FALSE(target.Error());
    ASSERT_FALSE(target.NoChildren());
    
    XMLElement* rootElem = target.RootElement();
    ASSERT_NE(rootElem, nullptr);
    EXPECT_STREQ(rootElem->Name(), "root");
    
    XMLElement* childElem = rootElem->FirstChildElement("child");
    ASSERT_NE(childElem, nullptr);
    EXPECT_STREQ(childElem->GetText(), "text");
}

// Test DeepCopy to self (no-op)
TEST_F(XMLDocumentDeepCopyTest_271, DeepCopyToSelf_271) {
    XMLDocument doc;
    doc.Parse("<root>hello</root>");
    ASSERT_FALSE(doc.Error());
    
    doc.DeepCopy(&doc);
    
    // Should be a no-op, document should remain intact
    ASSERT_FALSE(doc.Error());
    XMLElement* rootElem = doc.RootElement();
    ASSERT_NE(rootElem, nullptr);
    EXPECT_STREQ(rootElem->Name(), "root");
    EXPECT_STREQ(rootElem->GetText(), "hello");
}

// Test DeepCopy clears target before copying
TEST_F(XMLDocumentDeepCopyTest_271, DeepCopyClearsTarget_271) {
    XMLDocument source;
    source.Parse("<source>data</source>");
    ASSERT_FALSE(source.Error());
    
    XMLDocument target;
    target.Parse("<existing><old>content</old></existing>");
    ASSERT_FALSE(target.Error());
    
    source.DeepCopy(&target);
    
    XMLElement* rootElem = target.RootElement();
    ASSERT_NE(rootElem, nullptr);
    EXPECT_STREQ(rootElem->Name(), "source");
    EXPECT_STREQ(rootElem->GetText(), "data");
    
    // Ensure old content is gone
    XMLElement* oldElem = target.FirstChildElement("existing");
    EXPECT_EQ(oldElem, nullptr);
}

// Test DeepCopy with multiple children at root level
TEST_F(XMLDocumentDeepCopyTest_271, DeepCopyMultipleRootChildren_271) {
    XMLDocument source;
    source.Parse("<?xml version=\"1.0\"?><root><a/><b/><c/></root>");
    ASSERT_FALSE(source.Error());
    
    XMLDocument target;
    source.DeepCopy(&target);
    
    ASSERT_FALSE(target.Error());
    
    // Check declaration exists
    const XMLNode* firstChild = target.FirstChild();
    ASSERT_NE(firstChild, nullptr);
    
    XMLElement* rootElem = target.RootElement();
    ASSERT_NE(rootElem, nullptr);
    EXPECT_STREQ(rootElem->Name(), "root");
    
    int count = rootElem->ChildElementCount();
    EXPECT_EQ(count, 3);
}

// Test DeepCopy with deeply nested structure
TEST_F(XMLDocumentDeepCopyTest_271, DeepCopyNestedStructure_271) {
    XMLDocument source;
    source.Parse("<a><b><c><d>deep</d></c></b></a>");
    ASSERT_FALSE(source.Error());
    
    XMLDocument target;
    source.DeepCopy(&target);
    
    XMLElement* a = target.RootElement();
    ASSERT_NE(a, nullptr);
    EXPECT_STREQ(a->Name(), "a");
    
    XMLElement* b = a->FirstChildElement("b");
    ASSERT_NE(b, nullptr);
    
    XMLElement* c = b->FirstChildElement("c");
    ASSERT_NE(c, nullptr);
    
    XMLElement* d = c->FirstChildElement("d");
    ASSERT_NE(d, nullptr);
    EXPECT_STREQ(d->GetText(), "deep");
}

// Test DeepCopy with attributes
TEST_F(XMLDocumentDeepCopyTest_271, DeepCopyWithAttributes_271) {
    XMLDocument source;
    source.Parse("<root attr1=\"value1\" attr2=\"value2\"><child name=\"test\"/></root>");
    ASSERT_FALSE(source.Error());
    
    XMLDocument target;
    source.DeepCopy(&target);
    
    XMLElement* rootElem = target.RootElement();
    ASSERT_NE(rootElem, nullptr);
    
    EXPECT_STREQ(rootElem->Attribute("attr1"), "value1");
    EXPECT_STREQ(rootElem->Attribute("attr2"), "value2");
    
    XMLElement* childElem = rootElem->FirstChildElement("child");
    ASSERT_NE(childElem, nullptr);
    EXPECT_STREQ(childElem->Attribute("name"), "test");
}

// Test DeepCopy produces independent copy (modifying target doesn't affect source)
TEST_F(XMLDocumentDeepCopyTest_271, DeepCopyProducesIndependentCopy_271) {
    XMLDocument source;
    source.Parse("<root><child>original</child></root>");
    ASSERT_FALSE(source.Error());
    
    XMLDocument target;
    source.DeepCopy(&target);
    
    // Modify target
    XMLElement* targetChild = target.RootElement()->FirstChildElement("child");
    ASSERT_NE(targetChild, nullptr);
    targetChild->SetText("modified");
    
    // Source should remain unchanged
    XMLElement* sourceChild = source.RootElement()->FirstChildElement("child");
    ASSERT_NE(sourceChild, nullptr);
    EXPECT_STREQ(sourceChild->GetText(), "original");
}

// Test DeepCopy with XML declaration
TEST_F(XMLDocumentDeepCopyTest_271, DeepCopyWithDeclaration_271) {
    XMLDocument source;
    source.Parse("<?xml version=\"1.0\" encoding=\"UTF-8\"?><root/>");
    ASSERT_FALSE(source.Error());
    
    XMLDocument target;
    source.DeepCopy(&target);
    
    ASSERT_FALSE(target.Error());
    
    const XMLNode* first = target.FirstChild();
    ASSERT_NE(first, nullptr);
    
    const XMLDeclaration* decl = first->ToDeclaration();
    EXPECT_NE(decl, nullptr);
    
    XMLElement* rootElem = target.RootElement();
    ASSERT_NE(rootElem, nullptr);
    EXPECT_STREQ(rootElem->Name(), "root");
}

// Test DeepCopy with comments
TEST_F(XMLDocumentDeepCopyTest_271, DeepCopyWithComments_271) {
    XMLDocument source;
    source.Parse("<!-- This is a comment --><root/>");
    ASSERT_FALSE(source.Error());
    
    XMLDocument target;
    source.DeepCopy(&target);
    
    const XMLNode* first = target.FirstChild();
    ASSERT_NE(first, nullptr);
    
    const XMLComment* comment = first->ToComment();
    EXPECT_NE(comment, nullptr);
    
    XMLElement* rootElem = target.RootElement();
    ASSERT_NE(rootElem, nullptr);
    EXPECT_STREQ(rootElem->Name(), "root");
}

// Test DeepCopy with text content including whitespace
TEST_F(XMLDocumentDeepCopyTest_271, DeepCopyWithTextContent_271) {
    XMLDocument source;
    source.Parse("<root>Hello World</root>");
    ASSERT_FALSE(source.Error());
    
    XMLDocument target;
    source.DeepCopy(&target);
    
    XMLElement* rootElem = target.RootElement();
    ASSERT_NE(rootElem, nullptr);
    EXPECT_STREQ(rootElem->GetText(), "Hello World");
}

// Test DeepCopy with mixed content (elements and text)
TEST_F(XMLDocumentDeepCopyTest_271, DeepCopyMixedContent_271) {
    XMLDocument source;
    source.Parse("<root><a>1</a><b>2</b><c>3</c></root>");
    ASSERT_FALSE(source.Error());
    
    XMLDocument target;
    source.DeepCopy(&target);
    
    XMLElement* rootElem = target.RootElement();
    ASSERT_NE(rootElem, nullptr);
    
    XMLElement* a = rootElem->FirstChildElement("a");
    ASSERT_NE(a, nullptr);
    EXPECT_STREQ(a->GetText(), "1");
    
    XMLElement* b = rootElem->FirstChildElement("b");
    ASSERT_NE(b, nullptr);
    EXPECT_STREQ(b->GetText(), "2");
    
    XMLElement* c = rootElem->FirstChildElement("c");
    ASSERT_NE(c, nullptr);
    EXPECT_STREQ(c->GetText(), "3");
}

// Test DeepCopy from empty document to non-empty document clears target
TEST_F(XMLDocumentDeepCopyTest_271, DeepCopyEmptySourceClearsTarget_271) {
    XMLDocument source;
    // source is empty
    
    XMLDocument target;
    target.Parse("<existing>data</existing>");
    ASSERT_FALSE(target.Error());
    ASSERT_NE(target.RootElement(), nullptr);
    
    source.DeepCopy(&target);
    
    EXPECT_TRUE(target.NoChildren());
    EXPECT_EQ(target.RootElement(), nullptr);
}

// Test DeepCopy multiple times to same target
TEST_F(XMLDocumentDeepCopyTest_271, DeepCopyMultipleTimes_271) {
    XMLDocument source1;
    source1.Parse("<first/>");
    ASSERT_FALSE(source1.Error());
    
    XMLDocument source2;
    source2.Parse("<second/>");
    ASSERT_FALSE(source2.Error());
    
    XMLDocument target;
    
    source1.DeepCopy(&target);
    ASSERT_NE(target.RootElement(), nullptr);
    EXPECT_STREQ(target.RootElement()->Name(), "first");
    
    source2.DeepCopy(&target);
    ASSERT_NE(target.RootElement(), nullptr);
    EXPECT_STREQ(target.RootElement()->Name(), "second");
    
    // Ensure "first" is gone
    EXPECT_EQ(target.FirstChildElement("first"), nullptr);
}

// Test DeepCopy preserves sibling order
TEST_F(XMLDocumentDeepCopyTest_271, DeepCopyPreservesSiblingOrder_271) {
    XMLDocument source;
    source.Parse("<root><alpha/><beta/><gamma/><delta/></root>");
    ASSERT_FALSE(source.Error());
    
    XMLDocument target;
    source.DeepCopy(&target);
    
    XMLElement* root = target.RootElement();
    ASSERT_NE(root, nullptr);
    
    XMLElement* elem = root->FirstChildElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Name(), "alpha");
    
    elem = elem->NextSiblingElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Name(), "beta");
    
    elem = elem->NextSiblingElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Name(), "gamma");
    
    elem = elem->NextSiblingElement();
    ASSERT_NE(elem, nullptr);
    EXPECT_STREQ(elem->Name(), "delta");
    
    elem = elem->NextSiblingElement();
    EXPECT_EQ(elem, nullptr);
}

// Test DeepCopy with complex XML including multiple node types
TEST_F(XMLDocumentDeepCopyTest_271, DeepCopyComplexDocument_271) {
    XMLDocument source;
    const char* xml = 
        "<?xml version=\"1.0\"?>"
        "<!-- A comment -->"
        "<root>"
        "  <item id=\"1\">First</item>"
        "  <item id=\"2\">Second</item>"
        "  <nested>"
        "    <deep attr=\"val\">Content</deep>"
        "  </nested>"
        "</root>";
    source.Parse(xml);
    ASSERT_FALSE(source.Error());
    
    XMLDocument target;
    source.DeepCopy(&target);
    
    ASSERT_FALSE(target.Error());
    
    XMLElement* root = target.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->Name(), "root");
    
    XMLElement* item1 = root->FirstChildElement("item");
    ASSERT_NE(item1, nullptr);
    EXPECT_STREQ(item1->Attribute("id"), "1");
    EXPECT_STREQ(item1->GetText(), "First");
    
    XMLElement* item2 = item1->NextSiblingElement("item");
    ASSERT_NE(item2, nullptr);
    EXPECT_STREQ(item2->Attribute("id"), "2");
    EXPECT_STREQ(item2->GetText(), "Second");
    
    XMLElement* nested = root->FirstChildElement("nested");
    ASSERT_NE(nested, nullptr);
    
    XMLElement* deep = nested->FirstChildElement("deep");
    ASSERT_NE(deep, nullptr);
    EXPECT_STREQ(deep->Attribute("attr"), "val");
    EXPECT_STREQ(deep->GetText(), "Content");
}

// Test that source document is not modified after DeepCopy
TEST_F(XMLDocumentDeepCopyTest_271, SourceUnmodifiedAfterDeepCopy_271) {
    XMLDocument source;
    source.Parse("<root><child key=\"val\">text</child></root>");
    ASSERT_FALSE(source.Error());
    
    XMLDocument target;
    source.DeepCopy(&target);
    
    // Verify source is still intact
    XMLElement* sourceRoot = source.RootElement();
    ASSERT_NE(sourceRoot, nullptr);
    EXPECT_STREQ(sourceRoot->Name(), "root");
    
    XMLElement* sourceChild = sourceRoot->FirstChildElement("child");
    ASSERT_NE(sourceChild, nullptr);
    EXPECT_STREQ(sourceChild->Attribute("key"), "val");
    EXPECT_STREQ(sourceChild->GetText(), "text");
}

// Test DeepCopy with document containing only a declaration
TEST_F(XMLDocumentDeepCopyTest_271, DeepCopyDeclarationOnly_271) {
    XMLDocument source;
    source.Parse("<?xml version=\"1.0\"?>");
    ASSERT_FALSE(source.Error());
    
    XMLDocument target;
    source.DeepCopy(&target);
    
    const XMLNode* first = target.FirstChild();
    ASSERT_NE(first, nullptr);
    EXPECT_NE(first->ToDeclaration(), nullptr);
    
    // No root element
    EXPECT_EQ(target.RootElement(), nullptr);
}

// Test DeepCopy with BOM setting
TEST_F(XMLDocumentDeepCopyTest_271, DeepCopyPreservesContent_271) {
    XMLDocument source;
    source.Parse("<data><value type=\"int\">42</value></data>");
    ASSERT_FALSE(source.Error());
    
    XMLDocument target;
    source.DeepCopy(&target);
    
    XMLElement* data = target.RootElement();
    ASSERT_NE(data, nullptr);
    EXPECT_STREQ(data->Name(), "data");
    
    XMLElement* value = data->FirstChildElement("value");
    ASSERT_NE(value, nullptr);
    EXPECT_STREQ(value->Attribute("type"), "int");
    EXPECT_STREQ(value->GetText(), "42");
}
