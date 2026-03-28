// File: ./TestProjects/tinyxml2/test_xmldocument_identify_179.cpp

#include <gtest/gtest.h>
#include "tinyxml2.h"

#include <string>
#include <vector>

using namespace tinyxml2;

namespace {

class XMLDocumentIdentifyTest_179 : public ::testing::Test {
protected:
    static std::vector<char> MakeBuffer(const std::string& s) {
        std::vector<char> buf(s.begin(), s.end());
        buf.push_back('\0');
        return buf;
    }

    static ptrdiff_t Offset(const char* base, const char* p) {
        return p - base;
    }
};

}  // namespace

TEST_F(XMLDocumentIdentifyTest_179, EmptyAfterWhitespaceReturnsNullNode_179) {
    XMLDocument doc(/*processEntities=*/true, PRESERVE_WHITESPACE);

    auto buf = MakeBuffer(" \n\t  ");
    char* p = buf.data();
    XMLNode* node = reinterpret_cast<XMLNode*>(0x1);  // sentinel

    char* out = doc.Identify(p, &node, /*first=*/true);

    ASSERT_NE(out, nullptr);
    EXPECT_EQ(*out, '\0');
    EXPECT_EQ(node, nullptr);
}

TEST_F(XMLDocumentIdentifyTest_179, IdentifiesXmlDeclarationAndAdvancesPastHeader_179) {
    XMLDocument doc(/*processEntities=*/true, PRESERVE_WHITESPACE);

    auto buf = MakeBuffer("   <?xml version=\"1.0\"?>");
    char* base = buf.data();
    XMLNode* node = nullptr;

    char* out = doc.Identify(base, &node, /*first=*/true);

    ASSERT_NE(node, nullptr);
    EXPECT_NE(node->ToDeclaration(), nullptr);

    // After skipping leading whitespace, Identify should consume the "<?" header.
    // So the returned pointer should point at "xml ..." (i.e., after "<?").
    EXPECT_EQ(std::string(out, 3), "xml");
    EXPECT_GT(Offset(base, out), 0);
}

TEST_F(XMLDocumentIdentifyTest_179, IdentifiesCommentAndAdvancesPastHeader_179) {
    XMLDocument doc(/*processEntities=*/true, PRESERVE_WHITESPACE);

    auto buf = MakeBuffer("<!--hello-->");
    char* base = buf.data();
    XMLNode* node = nullptr;

    char* out = doc.Identify(base, &node, /*first=*/true);

    ASSERT_NE(node, nullptr);
    EXPECT_NE(node->ToComment(), nullptr);

    // After "<!--" the next chars should be the comment content.
    EXPECT_EQ(std::string(out, 5), "hello");
    EXPECT_EQ(Offset(base, out), 4);  // "<!--" length
}

TEST_F(XMLDocumentIdentifyTest_179, IdentifiesCDataAsTextWithCDataFlag_179) {
    XMLDocument doc(/*processEntities=*/true, PRESERVE_WHITESPACE);

    auto buf = MakeBuffer("<![CDATA[some <cdata>]]>");
    char* base = buf.data();
    XMLNode* node = nullptr;

    char* out = doc.Identify(base, &node, /*first=*/true);

    ASSERT_NE(node, nullptr);
    XMLText* text = node->ToText();
    ASSERT_NE(text, nullptr);
    EXPECT_TRUE(text->CData());

    // After "<![CDATA[" the next chars should be the CDATA content.
    EXPECT_EQ(std::string(out, 4), "some");
    EXPECT_EQ(Offset(base, out), 9);  // "<![CDATA[" length
}

TEST_F(XMLDocumentIdentifyTest_179, IdentifiesDtdOrBangAsUnknownAndAdvancesPastBangHeader_179) {
    XMLDocument doc(/*processEntities=*/true, PRESERVE_WHITESPACE);

    auto buf = MakeBuffer("<!DOCTYPE root>");
    char* base = buf.data();
    XMLNode* node = nullptr;

    char* out = doc.Identify(base, &node, /*first=*/true);

    ASSERT_NE(node, nullptr);
    EXPECT_NE(node->ToUnknown(), nullptr);

    // After "<!" the next chars should begin with "DOCTYPE".
    EXPECT_EQ(std::string(out, 7), "DOCTYPE");
    EXPECT_EQ(Offset(base, out), 2);  // "<!" length
}

TEST_F(XMLDocumentIdentifyTest_179, IdentifiesElementAndAdvancesPastLessThan_179) {
    XMLDocument doc(/*processEntities=*/true, PRESERVE_WHITESPACE);

    auto buf = MakeBuffer("   <root/>");
    char* base = buf.data();
    XMLNode* node = nullptr;

    char* out = doc.Identify(base, &node, /*first=*/true);

    ASSERT_NE(node, nullptr);
    EXPECT_NE(node->ToElement(), nullptr);

    // After skipping whitespace and consuming "<", the next chars should be "root".
    EXPECT_EQ(std::string(out, 4), "root");
    EXPECT_GT(Offset(base, out), 0);
}

TEST_F(XMLDocumentIdentifyTest_179, NonMarkupCreatesTextAndReturnsStartPointer_179) {
    XMLDocument doc(/*processEntities=*/true, PRESERVE_WHITESPACE);

    auto buf = MakeBuffer(" \nHello");
    char* base = buf.data();
    XMLNode* node = nullptr;

    char* out = doc.Identify(base, &node, /*first=*/true);

    ASSERT_NE(node, nullptr);
    EXPECT_NE(node->ToText(), nullptr);

    // For non-'<' content, Identify backs up and returns the original start pointer.
    EXPECT_EQ(out, base);
}

TEST_F(XMLDocumentIdentifyTest_179, PedanticWhitespaceFirstClosingTagBecomesTextAndReturnsStart_179) {
    XMLDocument doc(/*processEntities=*/true, PEDANTIC_WHITESPACE);

    auto buf = MakeBuffer(" \n</a>");
    char* base = buf.data();
    XMLNode* node = nullptr;

    char* out = doc.Identify(base, &node, /*first=*/true);

    ASSERT_NE(node, nullptr);
    // In this special case, Identify creates a text node instead of an element.
    EXPECT_NE(node->ToText(), nullptr);
    EXPECT_EQ(node->ToElement(), nullptr);

    // It also backs up to include the whitespace, returning the original start.
    EXPECT_EQ(out, base);
}

TEST_F(XMLDocumentIdentifyTest_179, NonPedanticClosingTagIsTreatedAsElementAndAdvancesPastLessThan_179) {
    XMLDocument doc(/*processEntities=*/true, PRESERVE_WHITESPACE);

    auto buf = MakeBuffer(" \n</a>");
    char* base = buf.data();
    XMLNode* node = nullptr;

    char* out = doc.Identify(base, &node, /*first=*/true);

    ASSERT_NE(node, nullptr);
    EXPECT_NE(node->ToElement(), nullptr);

    // After consuming '<', next char should be '/' for a closing tag.
    ASSERT_NE(out, nullptr);
    EXPECT_EQ(*out, '/');
}
