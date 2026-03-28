// TEST_ID: 48
#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

namespace {

class TestXMLNode_48 : public tinyxml2::XMLNode {
public:
    explicit TestXMLNode_48(tinyxml2::XMLDocument* doc) : tinyxml2::XMLNode(doc) {}
    ~TestXMLNode_48() override = default;
    // Inherit default behavior of XMLNode::ToUnknown()
};

class OverrideToUnknownNode_48 : public TestXMLNode_48 {
public:
    explicit OverrideToUnknownNode_48(tinyxml2::XMLDocument* doc) : TestXMLNode_48(doc) {}
    ~OverrideToUnknownNode_48() override = default;

    tinyxml2::XMLUnknown* ToUnknown() override {
        // We only test virtual dispatch and returned pointer identity; we never dereference it.
        return reinterpret_cast<tinyxml2::XMLUnknown*>(static_cast<uintptr_t>(0xDEADBEEF));
    }
};

}  // namespace

TEST(ToUnknownTest_48, DefaultImplementationReturnsNull_48) {
    tinyxml2::XMLDocument doc;
    TestXMLNode_48 node(&doc);

    EXPECT_EQ(nullptr, node.ToUnknown());
}

TEST(ToUnknownTest_48, DefaultImplementationReturnsNullViaBasePointer_48) {
    tinyxml2::XMLDocument doc;
    TestXMLNode_48 node(&doc);

    tinyxml2::XMLNode* basePtr = &node;
    EXPECT_EQ(nullptr, basePtr->ToUnknown());
}

TEST(ToUnknownTest_48, DefaultImplementationIsStableAcrossRepeatedCalls_48) {
    tinyxml2::XMLDocument doc;
    TestXMLNode_48 node(&doc);

    EXPECT_EQ(nullptr, node.ToUnknown());
    EXPECT_EQ(nullptr, node.ToUnknown());
    EXPECT_EQ(nullptr, node.ToUnknown());
}

TEST(ToUnknownTest_48, VirtualDispatchUsesOverrideWhenProvided_48) {
    tinyxml2::XMLDocument doc;
    OverrideToUnknownNode_48 node(&doc);

    tinyxml2::XMLNode* basePtr = &node;
    auto* expected = reinterpret_cast<tinyxml2::XMLUnknown*>(static_cast<uintptr_t>(0xDEADBEEF));

    EXPECT_EQ(expected, basePtr->ToUnknown());
    EXPECT_EQ(expected, node.ToUnknown());
}
