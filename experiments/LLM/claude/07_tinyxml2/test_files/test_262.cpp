#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementInsertNewDeclarationTest_262 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* root;

    void SetUp() override {
        root = doc.NewElement("root");
        doc.InsertEndChild(root);
    }
};

// Test that InsertNewDeclaration returns a non-null pointer with valid text
TEST_F(XMLElementInsertNewDeclarationTest_262, ReturnsNonNullWithValidText_262) {
    XMLDeclaration* decl = root->InsertNewDeclaration("xml version=\"1.0\"");
    ASSERT_NE(decl, nullptr);
}

// Test that the declaration is added as a child of the element
TEST_F(XMLElementInsertNewDeclarationTest_262, DeclarationIsChildOfElement_262) {
    XMLDeclaration* decl = root->InsertNewDeclaration("xml version=\"1.0\"");
    ASSERT_NE(decl, nullptr);
    
    const XMLNode* child = root->FirstChild();
    ASSERT_NE(child, nullptr);
    EXPECT_NE(child->ToDeclaration(), nullptr);
}

// Test that the declaration contains the correct text/value
TEST_F(XMLElementInsertNewDeclarationTest_262, DeclarationHasCorrectValue_262) {
    const char* text = "xml version=\"1.0\" encoding=\"UTF-8\"";
    XMLDeclaration* decl = root->InsertNewDeclaration(text);
    ASSERT_NE(decl, nullptr);
    EXPECT_STREQ(decl->Value(), text);
}

// Test inserting declaration with empty string
TEST_F(XMLElementInsertNewDeclarationTest_262, EmptyStringDeclaration_262) {
    XMLDeclaration* decl = root->InsertNewDeclaration("");
    ASSERT_NE(decl, nullptr);
    EXPECT_STREQ(decl->Value(), "");
}

// Test inserting declaration with null text (default behavior)
TEST_F(XMLElementInsertNewDeclarationTest_262, NullTextDeclaration_262) {
    XMLDeclaration* decl = root->InsertNewDeclaration(nullptr);
    ASSERT_NE(decl, nullptr);
}

// Test that the declaration is appended at the end (InsertEndChild)
TEST_F(XMLElementInsertNewDeclarationTest_262, DeclarationAppendedAtEnd_262) {
    root->InsertNewChildElement("child1");
    XMLDeclaration* decl = root->InsertNewDeclaration("xml version=\"1.0\"");
    ASSERT_NE(decl, nullptr);

    const XMLNode* lastChild = root->LastChild();
    ASSERT_NE(lastChild, nullptr);
    EXPECT_NE(lastChild->ToDeclaration(), nullptr);
    EXPECT_STREQ(lastChild->Value(), "xml version=\"1.0\"");
}

// Test inserting multiple declarations
TEST_F(XMLElementInsertNewDeclarationTest_262, MultipleDeclarations_262) {
    XMLDeclaration* decl1 = root->InsertNewDeclaration("xml version=\"1.0\"");
    XMLDeclaration* decl2 = root->InsertNewDeclaration("xml version=\"2.0\"");
    
    ASSERT_NE(decl1, nullptr);
    ASSERT_NE(decl2, nullptr);
    EXPECT_NE(decl1, decl2);
    
    // First child should be the first declaration
    const XMLNode* firstChild = root->FirstChild();
    ASSERT_NE(firstChild, nullptr);
    EXPECT_STREQ(firstChild->Value(), "xml version=\"1.0\"");
    
    // Last child should be the second declaration
    const XMLNode* lastChild = root->LastChild();
    ASSERT_NE(lastChild, nullptr);
    EXPECT_STREQ(lastChild->Value(), "xml version=\"2.0\"");
}

// Test that the declaration's parent is the element
TEST_F(XMLElementInsertNewDeclarationTest_262, DeclarationParentIsElement_262) {
    XMLDeclaration* decl = root->InsertNewDeclaration("xml version=\"1.0\"");
    ASSERT_NE(decl, nullptr);
    
    const XMLNode* parent = decl->Parent();
    ASSERT_NE(parent, nullptr);
    EXPECT_EQ(parent, root);
}

// Test that the returned pointer can be cast to XMLDeclaration
TEST_F(XMLElementInsertNewDeclarationTest_262, ReturnedPointerIsDeclaration_262) {
    XMLDeclaration* decl = root->InsertNewDeclaration("xml version=\"1.0\"");
    ASSERT_NE(decl, nullptr);
    EXPECT_NE(decl->ToDeclaration(), nullptr);
}

// Test that element's child count increases after inserting declaration
TEST_F(XMLElementInsertNewDeclarationTest_262, ChildCountIncreases_262) {
    EXPECT_TRUE(root->NoChildren());
    
    root->InsertNewDeclaration("xml version=\"1.0\"");
    EXPECT_FALSE(root->NoChildren());
}

// Test declaration with special characters in text
TEST_F(XMLElementInsertNewDeclarationTest_262, DeclarationWithSpecialChars_262) {
    const char* text = "xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"";
    XMLDeclaration* decl = root->InsertNewDeclaration(text);
    ASSERT_NE(decl, nullptr);
    EXPECT_STREQ(decl->Value(), text);
}

// Test that the document is the same for the declaration
TEST_F(XMLElementInsertNewDeclarationTest_262, DeclarationBelongsToSameDocument_262) {
    XMLDeclaration* decl = root->InsertNewDeclaration("xml version=\"1.0\"");
    ASSERT_NE(decl, nullptr);
    EXPECT_EQ(decl->GetDocument(), root->GetDocument());
}

// Test declaration interleaved with other child types
TEST_F(XMLElementInsertNewDeclarationTest_262, DeclarationInterleavedWithOtherChildren_262) {
    root->InsertNewChildElement("child1");
    XMLDeclaration* decl = root->InsertNewDeclaration("xml version=\"1.0\"");
    root->InsertNewComment("a comment");
    root->InsertNewText("some text");
    
    ASSERT_NE(decl, nullptr);
    
    // The element should now have 4 children
    int count = 0;
    for (const XMLNode* child = root->FirstChild(); child; child = child->NextSibling()) {
        count++;
    }
    EXPECT_EQ(count, 4);
}

// Test that document serialization includes the declaration inside the element
TEST_F(XMLElementInsertNewDeclarationTest_262, SerializationIncludesDeclaration_262) {
    root->InsertNewDeclaration("xml version=\"1.0\"");
    
    XMLPrinter printer;
    doc.Print(&printer);
    
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    // The output should contain the declaration
    EXPECT_NE(std::string(result).find("xml version=\"1.0\""), std::string::npos);
}
