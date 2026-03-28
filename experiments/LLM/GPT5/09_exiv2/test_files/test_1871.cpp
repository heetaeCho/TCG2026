#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/exiv2/xmpsdk/src/XMPCore_Impl.hpp"

// Mocking dependencies (if any)
class MockXMPNode : public XMP_Node {
public:
    MOCK_METHOD(void, RemoveChildren, (), (override));
    MOCK_METHOD(void, RemoveQualifiers, (), (override));
};

// Test fixture
class XMPNodeTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up code if needed
    }

    void TearDown() override {
        // Cleanup code if needed
    }
};

// Normal operation tests
TEST_F(XMPNodeTest, ConstructorWithName_1871) {
    XMP_Node node(nullptr, "Name", 0);
    EXPECT_EQ(node.name, "Name");
    EXPECT_EQ(node.parent, nullptr);
}

TEST_F(XMPNodeTest, ConstructorWithNameAndValue_1872) {
    XMP_Node node(nullptr, "Name", "Value", 0);
    EXPECT_EQ(node.name, "Name");
    EXPECT_EQ(node.value, "Value");
    EXPECT_EQ(node.parent, nullptr);
}

// Boundary tests
TEST_F(XMPNodeTest, ConstructorEmptyName_1873) {
    XMP_Node node(nullptr, "", 0);
    EXPECT_EQ(node.name, "");
    EXPECT_EQ(node.parent, nullptr);
}

TEST_F(XMPNodeTest, ConstructorEmptyValue_1874) {
    XMP_Node node(nullptr, "Name", "", 0);
    EXPECT_EQ(node.name, "Name");
    EXPECT_EQ(node.value, "");
    EXPECT_EQ(node.parent, nullptr);
}

// Exceptional or error cases
TEST_F(XMPNodeTest, RemoveChildren_1875) {
    MockXMPNode mockNode(nullptr, "Name", 0);
    EXPECT_CALL(mockNode, RemoveChildren()).Times(1);
    mockNode.RemoveChildren();
}

TEST_F(XMPNodeTest, RemoveQualifiers_1876) {
    MockXMPNode mockNode(nullptr, "Name", 0);
    EXPECT_CALL(mockNode, RemoveQualifiers()).Times(1);
    mockNode.RemoveQualifiers();
}

// Verification of external interactions (mocked RemoveChildren and RemoveQualifiers)
TEST_F(XMPNodeTest, DestructorCallsRemoveChildren_1877) {
    MockXMPNode mockNode(nullptr, "Name", 0);
    EXPECT_CALL(mockNode, RemoveChildren()).Times(1);
    EXPECT_CALL(mockNode, RemoveQualifiers()).Times(1);
    mockNode.~MockXMPNode();
}