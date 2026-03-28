// File: ./TestProjects/tinyxml2/tests/test_xmlnode_getdocument_42.cpp

#include <gtest/gtest.h>

#include "tinyxml2.h"

namespace {

class TestXMLNode_42 : public tinyxml2::XMLNode {
public:
    explicit TestXMLNode_42(tinyxml2::XMLDocument* doc) : tinyxml2::XMLNode(doc) {}
    ~TestXMLNode_42() override = default;
};

}  // namespace

TEST(XMLNodeGetDocumentTest_42, ReturnsSamePointerWhenNonNull_42)
{
    tinyxml2::XMLDocument doc;
    TestXMLNode_42 node(&doc);

    const tinyxml2::XMLDocument* returned = node.GetDocument();
    EXPECT_EQ(returned, &doc);
}

TEST(XMLNodeGetDocumentTest_42, WorksOnConstObject_42)
{
    tinyxml2::XMLDocument doc;
    const TestXMLNode_42 node(&doc);

    const tinyxml2::XMLDocument* returned = node.GetDocument();
    EXPECT_EQ(returned, &doc);
}

TEST(XMLNodeGetDocumentTest_42, NullDocumentTriggersAssertionOrReturnsNullInNDebug_42)
{
    TestXMLNode_42 node(nullptr);

#if defined(NDEBUG)
    // If assertions are compiled out, observable behavior is that nullptr is returned.
    EXPECT_EQ(node.GetDocument(), nullptr);
#else
    // If assertions are enabled, GetDocument() should assert on null _document.
    EXPECT_DEATH(
        {
            (void)node.GetDocument();
        },
        ".*");
#endif
}
