// File: ./TestProjects/tinyxml2/test_XMLNode_SetValue_185.cpp

#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

#include <cstring>
#include <string>

namespace tinyxml2 {

// XMLNode has a protected constructor and protected virtual destructor.
// Create a small derived type to allow construction/destruction in tests.
class TestXMLNode_185 final : public XMLNode {
public:
    explicit TestXMLNode_185(XMLDocument* doc) : XMLNode(doc) {}
    ~TestXMLNode_185() override = default;

    // Expose the method under test (already public in the interface).
    using XMLNode::SetValue;
    using XMLNode::Value;
};

class XMLNodeSetValueTest_185 : public ::testing::Test {
protected:
    XMLDocument doc_;
};

TEST_F(XMLNodeSetValueTest_185, SetValueStaticMemFalse_StoresAndReturnsSameText_185) {
    TestXMLNode_185 node(&doc_);

    node.SetValue("alpha", /*staticMem=*/false);
    ASSERT_NE(node.Value(), nullptr);
    EXPECT_STREQ(node.Value(), "alpha");

    node.SetValue("beta", /*staticMem=*/false);
    ASSERT_NE(node.Value(), nullptr);
    EXPECT_STREQ(node.Value(), "beta");
}

TEST_F(XMLNodeSetValueTest_185, SetValueStaticMemTrue_StoresAndReturnsSameText_185) {
    TestXMLNode_185 node(&doc_);

    node.SetValue("alpha", /*staticMem=*/true);
    ASSERT_NE(node.Value(), nullptr);
    EXPECT_STREQ(node.Value(), "alpha");

    node.SetValue("beta", /*staticMem=*/true);
    ASSERT_NE(node.Value(), nullptr);
    EXPECT_STREQ(node.Value(), "beta");
}

TEST_F(XMLNodeSetValueTest_185, SetValueEmptyString_WorksForBothFlags_185) {
    TestXMLNode_185 node(&doc_);

    node.SetValue("", /*staticMem=*/false);
    ASSERT_NE(node.Value(), nullptr);
    EXPECT_STREQ(node.Value(), "");

    node.SetValue("", /*staticMem=*/true);
    ASSERT_NE(node.Value(), nullptr);
    EXPECT_STREQ(node.Value(), "");
}

TEST_F(XMLNodeSetValueTest_185, SetValueNonStatic_DoesNotReflectLaterSourceBufferMutation_185) {
    TestXMLNode_185 node(&doc_);

    char buf[] = "mutable";
    node.SetValue(buf, /*staticMem=*/false);

    // Mutate the original buffer after SetValue.
    buf[0] = 'M';

    // Observable expectation: Value() should still be what was set at the time of the call.
    // (If it does reflect mutation, this test will catch it.)
    ASSERT_NE(node.Value(), nullptr);
    EXPECT_STREQ(node.Value(), "mutable");
}

TEST_F(XMLNodeSetValueTest_185, SetValueLongString_RoundTrips_185) {
    TestXMLNode_185 node(&doc_);

    std::string longStr(4096, 'x');
    node.SetValue(longStr.c_str(), /*staticMem=*/false);

    ASSERT_NE(node.Value(), nullptr);
    EXPECT_EQ(std::strlen(node.Value()), longStr.size());
    EXPECT_EQ(std::string(node.Value()), longStr);
}

TEST_F(XMLNodeSetValueTest_185, SetValueNullptr_DoesNotCrashAndProducesSafeValue_185) {
    TestXMLNode_185 node(&doc_);

    // We do not assume a specific representation for nullptr input.
    // We only assert it is handled safely and results in either nullptr or an empty string.
    ASSERT_NO_FATAL_FAILURE(node.SetValue(nullptr, /*staticMem=*/false));
    const char* v1 = node.Value();
    EXPECT_TRUE(v1 == nullptr || std::strcmp(v1, "") == 0);

    ASSERT_NO_FATAL_FAILURE(node.SetValue(nullptr, /*staticMem=*/true));
    const char* v2 = node.Value();
    EXPECT_TRUE(v2 == nullptr || std::strcmp(v2, "") == 0);
}

}  // namespace tinyxml2
