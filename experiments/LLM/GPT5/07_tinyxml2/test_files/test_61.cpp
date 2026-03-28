#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

namespace tinyxml2 {

// XMLNode has a protected ctor, so expose it for testing via a trivial derived type.
class TestXMLNode_61 : public XMLNode {
public:
    explicit TestXMLNode_61(XMLDocument* doc) : XMLNode(doc) {}
    ~TestXMLNode_61() override = default;
};

class XMLNodeSetUserDataTest_61 : public ::testing::Test {
protected:
    XMLDocument doc_;
};

TEST_F(XMLNodeSetUserDataTest_61, DefaultUserDataIsNull_61) {
    TestXMLNode_61 node(&doc_);
    EXPECT_EQ(node.GetUserData(), nullptr);
}

TEST_F(XMLNodeSetUserDataTest_61, SetUserDataStoresPointer_61) {
    TestXMLNode_61 node(&doc_);

    int payload = 123;
    void* p = &payload;

    node.SetUserData(p);
    EXPECT_EQ(node.GetUserData(), p);
}

TEST_F(XMLNodeSetUserDataTest_61, SetUserDataAllowsNullptr_61) {
    TestXMLNode_61 node(&doc_);

    int payload = 7;
    node.SetUserData(&payload);
    ASSERT_EQ(node.GetUserData(), static_cast<void*>(&payload));

    node.SetUserData(nullptr);
    EXPECT_EQ(node.GetUserData(), nullptr);
}

TEST_F(XMLNodeSetUserDataTest_61, SetUserDataOverwritesPreviousValue_61) {
    TestXMLNode_61 node(&doc_);

    int a = 1;
    int b = 2;

    node.SetUserData(&a);
    ASSERT_EQ(node.GetUserData(), static_cast<void*>(&a));

    node.SetUserData(&b);
    EXPECT_EQ(node.GetUserData(), static_cast<void*>(&b));
}

TEST_F(XMLNodeSetUserDataTest_61, SetUserDataIsPerNodeNotShared_61) {
    TestXMLNode_61 node1(&doc_);
    TestXMLNode_61 node2(&doc_);

    int a = 10;
    int b = 20;

    node1.SetUserData(&a);
    node2.SetUserData(&b);

    EXPECT_EQ(node1.GetUserData(), static_cast<void*>(&a));
    EXPECT_EQ(node2.GetUserData(), static_cast<void*>(&b));
}

}  // namespace tinyxml2
