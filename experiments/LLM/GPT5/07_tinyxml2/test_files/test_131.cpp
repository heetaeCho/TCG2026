#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// Test fixture for XMLHandle tests
class XMLHandleTest_131 : public ::testing::Test {
protected:
    XMLDocument doc;
};

// Test: ToUnknown returns nullptr if handle was initialized with nullptr
TEST_F(XMLHandleTest_131, ToUnknownReturnsNullForNullNode_131) {
    XMLHandle handle(nullptr);
    EXPECT_EQ(handle.ToUnknown(), nullptr);
}

// Test: ToUnknown returns a valid XMLUnknown pointer when the node is actually XMLUnknown
TEST_F(XMLHandleTest_131, ToUnknownReturnsXMLUnknown_131) {
    XMLUnknown* unknownNode = doc.NewUnknown("TestUnknown");
    doc.InsertEndChild(unknownNode);

    XMLHandle handle(unknownNode);
    XMLUnknown* result = handle.ToUnknown();

    // Observable behavior: should return the same pointer
    EXPECT_EQ(result, unknownNode);
}

// Test: ToUnknown returns nullptr if the node is not an XMLUnknown
TEST_F(XMLHandleTest_131, ToUnknownReturnsNullForNonUnknownNode_131) {
    XMLElement* elem = doc.NewElement("TestElement");
    doc.InsertEndChild(elem);

    XMLHandle handle(elem);
    EXPECT_EQ(handle.ToUnknown(), nullptr);
}

// Test: Copy constructor preserves the behavior of ToUnknown
TEST_F(XMLHandleTest_131, CopyConstructorPreservesToUnknown_131) {
    XMLUnknown* unknownNode = doc.NewUnknown("CopyTest");
    doc.InsertEndChild(unknownNode);

    XMLHandle handle(unknownNode);
    XMLHandle copyHandle(handle);

    EXPECT_EQ(copyHandle.ToUnknown(), unknownNode);
}

// Test: Assignment operator preserves the behavior of ToUnknown
TEST_F(XMLHandleTest_131, AssignmentOperatorPreservesToUnknown_131) {
    XMLUnknown* unknownNode = doc.NewUnknown("AssignTest");
    doc.InsertEndChild(unknownNode);

    XMLHandle handle(unknownNode);
    XMLHandle assignedHandle(nullptr);

    assignedHandle = handle;
    EXPECT_EQ(assignedHandle.ToUnknown(), unknownNode);
}
