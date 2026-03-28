#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// Fixture for XMLHandle tests
class XMLHandleTest_129 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* element = nullptr;
    XMLHandle* handle = nullptr;

    void SetUp() override {
        // Normal setup: create an element
        element = doc.NewElement("root");
        doc.InsertFirstChild(element);
    }

    void TearDown() override {
        delete handle;
    }
};

// Test: ToElement returns the underlying XMLElement when XMLHandle wraps an XMLElement
TEST_F(XMLHandleTest_129, ToElementReturnsXMLElement_129) {
    handle = new XMLHandle(element);
    XMLElement* result = handle->ToElement();
    EXPECT_EQ(result, element);
}

// Test: ToElement returns nullptr when XMLHandle wraps a null XMLNode
TEST_F(XMLHandleTest_129, ToElementReturnsNullForNullNode_129) {
    handle = new XMLHandle(static_cast<XMLNode*>(nullptr));
    XMLElement* result = handle->ToElement();
    EXPECT_EQ(result, nullptr);
}

// Test: Copy-constructed XMLHandle preserves ToElement behavior
TEST_F(XMLHandleTest_129, ToElementCopyConstructorPreservesNode_129) {
    XMLHandle original(element);
    XMLHandle copy(original);
    XMLElement* result = copy.ToElement();
    EXPECT_EQ(result, element);
}

// Test: Assignment operator preserves ToElement behavior
TEST_F(XMLHandleTest_129, ToElementAssignmentOperatorPreservesNode_129) {
    XMLHandle original(element);
    XMLHandle assigned(static_cast<XMLNode*>(nullptr));
    assigned = original;
    XMLElement* result = assigned.ToElement();
    EXPECT_EQ(result, element);
}

// Test: ToElement on handle created from XMLNode pointer of non-element type returns nullptr
TEST_F(XMLHandleTest_129, ToElementReturnsNullForNonElementNode_129) {
    XMLText* textNode = doc.NewText("hello");
    doc.InsertEndChild(textNode);
    handle = new XMLHandle(textNode);
    XMLElement* result = handle->ToElement();
    EXPECT_EQ(result, nullptr);
}