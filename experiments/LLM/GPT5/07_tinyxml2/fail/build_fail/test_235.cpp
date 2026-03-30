// File: tinyxml2_gettext_test_235.cpp

#include <gtest/gtest.h>
#include "TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLElementGetTextTest_235 : public ::testing::Test {
protected:
    // Parses XML into doc_ and returns the first element with the given name.
    // If rootName is nullptr, returns the document's first element.
    const XMLElement* ParseAndGet(const char* xml, const char* elemName = nullptr) {
        doc_.Clear();
        ASSERT_NE(xml, nullptr);

        const XMLError err = doc_.Parse(xml);
        ASSERT_EQ(err, XML_SUCCESS);

        const XMLElement* root = doc_.FirstChildElement();
        ASSERT_NE(root, nullptr);

        if (!elemName) {
            return root;
        }
        const XMLElement* e = root->FirstChildElement(elemName);
        ASSERT_NE(e, nullptr);
        return e;
    }

    XMLDocument doc_;
};

}  // namespace

TEST_F(XMLElementGetTextTest_235, ReturnsNullWhenNoChildren_235) {
    const XMLElement* e = ParseAndGet("<root><a/></root>", "a");
    ASSERT_NE(e, nullptr);

    EXPECT_EQ(e->GetText(), nullptr);
}

TEST_F(XMLElementGetTextTest_235, ReturnsTextWhenFirstChildIsText_235) {
    const XMLElement* e = ParseAndGet("<root><a>hello</a></root>", "a");
    ASSERT_NE(e, nullptr);

    const char* text = e->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "hello");
}

TEST_F(XMLElementGetTextTest_235, SkipsLeadingCommentAndReturnsFollowingText_235) {
    const XMLElement* e = ParseAndGet("<root><a><!--c-->hello</a></root>", "a");
    ASSERT_NE(e, nullptr);

    const char* text = e->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "hello");
}

TEST_F(XMLElementGetTextTest_235, SkipsMultipleLeadingCommentsAndReturnsFollowingText_235) {
    const XMLElement* e = ParseAndGet("<root><a><!--c1--><!--c2-->hello</a></root>", "a");
    ASSERT_NE(e, nullptr);

    const char* text = e->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "hello");
}

TEST_F(XMLElementGetTextTest_235, ReturnsNullWhenOnlyCommentChildren_235) {
    const XMLElement* e = ParseAndGet("<root><a><!--only--></a></root>", "a");
    ASSERT_NE(e, nullptr);

    EXPECT_EQ(e->GetText(), nullptr);
}

TEST_F(XMLElementGetTextTest_235, ReturnsNullWhenFirstNonCommentChildIsElement_235) {
    // First child is an element, not text; even if text appears later, observable behavior is nullptr.
    const XMLElement* e = ParseAndGet("<root><a><b/>tail</a></root>", "a");
    ASSERT_NE(e, nullptr);

    EXPECT_EQ(e->GetText(), nullptr);
}

TEST_F(XMLElementGetTextTest_235, ReturnsNullWhenCommentThenElementThenText_235) {
    // Leading comment is skipped, but then an element appears; observable behavior is nullptr.
    const XMLElement* e = ParseAndGet("<root><a><!--c--><b/>tail</a></root>", "a");
    ASSERT_NE(e, nullptr);

    EXPECT_EQ(e->GetText(), nullptr);
}

TEST_F(XMLElementGetTextTest_235, WorksThroughConstPointer_235) {
    const XMLElement* e = ParseAndGet("<root><a><!--c-->hello</a></root>", "a");
    ASSERT_NE(e, nullptr);

    // Ensure the const overload behavior is usable (GetText is const in the provided implementation).
    const char* text = e->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "hello");
}
