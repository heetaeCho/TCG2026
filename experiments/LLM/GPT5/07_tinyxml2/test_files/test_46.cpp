// TEST_ID: 46
// Unit tests for tinyxml2::XMLNode::ToDocument (partial interface provided)
//
// Constraints honored:
// - Treat implementation as a black box.
// - Only test observable behavior from the provided interface.
// - No access to private/protected state.
// - No re-implementation/inference of internal logic.

#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

namespace tinyxml2 {

class XMLNodeToDocumentTest_46 : public ::testing::Test {};

// The partial code shows the base implementation:
//   virtual XMLDocument* ToDocument() { return 0; }
// So we can assert it returns nullptr on a base XMLNode instance.
// (If XMLNode is abstract in your build, this test will fail to compile;
//  in that case, remove this test and keep the override/virtual-dispatch tests below.)
TEST_F(XMLNodeToDocumentTest_46, BaseImplementationReturnsNullptr_46) {
    XMLNode node;
    EXPECT_EQ(nullptr, node.ToDocument());
}

// Verify virtual dispatch: overriding ToDocument should be observable via base pointer/reference.
class FakeDocNode_46 : public XMLNode {
public:
    explicit FakeDocNode_46(XMLDocument* docToReturn) : XMLNode(nullptr), doc_(docToReturn) {}
    XMLDocument* ToDocument() override { return doc_; }

private:
    XMLDocument* doc_;
};

TEST_F(XMLNodeToDocumentTest_46, VirtualDispatchReturnsOverrideValue_46) {
    XMLDocument* expected = reinterpret_cast<XMLDocument*>(0x1); // opaque sentinel pointer
    FakeDocNode_46 derived(expected);

    XMLNode* asBase = &derived;
    EXPECT_EQ(expected, asBase->ToDocument());
}

// Boundary: override returns nullptr; base pointer should observe nullptr as well.
class FakeNullDocNode_46 : public XMLNode {
public:
    FakeNullDocNode_46() : XMLNode(nullptr) {}
    XMLDocument* ToDocument() override { return nullptr; }
};

TEST_F(XMLNodeToDocumentTest_46, OverrideCanReturnNullptr_46) {
    FakeNullDocNode_46 derived;
    XMLNode* asBase = &derived;
    EXPECT_EQ(nullptr, asBase->ToDocument());
}

// Const-correctness note:
// The provided partial interface is non-const: XMLDocument* ToDocument().
// So we also validate it can be called repeatedly and yields consistent observable results.
TEST_F(XMLNodeToDocumentTest_46, MultipleCallsAreObservableAndConsistent_46) {
    XMLDocument* expected = reinterpret_cast<XMLDocument*>(0x2);
    FakeDocNode_46 derived(expected);

    XMLNode* asBase = &derived;
    EXPECT_EQ(expected, asBase->ToDocument());
    EXPECT_EQ(expected, asBase->ToDocument());
}

}  // namespace tinyxml2
