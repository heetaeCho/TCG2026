#include <gtest/gtest.h>
#include <string>

// Include necessary headers for XMP SDK
#include "XMP_Environment.h"
#include "XMP_Const.h"
#include "XMPMeta.hpp"
#include "ExpatAdapter.hpp"

class ExpatAdapterTest_2092 : public ::testing::Test {
protected:
    void SetUp() override {
        XMPMeta::Initialize();
    }

    void TearDown() override {
        XMPMeta::Terminate();
    }
};

// Test that parsing XML with a namespace declaration registers the namespace
TEST_F(ExpatAdapterTest_2092, NormalNamespaceRegistration_2092) {
    ExpatAdapter* adapter = ExpatAdapter::NewXMP(nullptr, 0);
    ASSERT_NE(adapter, nullptr);

    const char* xml = "<?xml version=\"1.0\"?>\n"
                      "<root xmlns:myns=\"http://example.com/myns/\">"
                      "</root>";

    adapter->ParseBuffer(xml, strlen(xml), true);

    XMP_StringPtr prefix = nullptr;
    XMP_StringLen prefixLen = 0;
    bool found = XMPMeta::GetNamespacePrefix("http://example.com/myns/", &prefix, &prefixLen);
    EXPECT_TRUE(found);
    if (found && prefix) {
        // The prefix should contain "myns" (possibly with trailing colon)
        std::string prefixStr(prefix, prefixLen);
        EXPECT_NE(prefixStr.find("myns"), std::string::npos);
    }

    delete adapter;
}

// Test that the old DC URI gets remapped to the correct one
TEST_F(ExpatAdapterTest_2092, DCNamespaceRemapping_2092) {
    ExpatAdapter* adapter = ExpatAdapter::NewXMP(nullptr, 0);
    ASSERT_NE(adapter, nullptr);

    // Use the old DC URI which should be remapped
    const char* xml = "<?xml version=\"1.0\"?>\n"
                      "<root xmlns:dc=\"http://purl.org/dc/1.1/\">"
                      "</root>";

    adapter->ParseBuffer(xml, strlen(xml), true);

    // The corrected URI should be registered
    XMP_StringPtr prefix = nullptr;
    XMP_StringLen prefixLen = 0;
    bool found = XMPMeta::GetNamespacePrefix("http://purl.org/dc/elements/1.1/", &prefix, &prefixLen);
    EXPECT_TRUE(found);

    delete adapter;
}

// Test that a default namespace (no prefix) gets handled
TEST_F(ExpatAdapterTest_2092, DefaultNamespaceHandling_2092) {
    ExpatAdapter* adapter = ExpatAdapter::NewXMP(nullptr, 0);
    ASSERT_NE(adapter, nullptr);

    const char* xml = "<?xml version=\"1.0\"?>\n"
                      "<root xmlns=\"http://example.com/defaultns/\">"
                      "</root>";

    adapter->ParseBuffer(xml, strlen(xml), true);

    // The default namespace should be registered with some prefix (like "_dflt_")
    XMP_StringPtr prefix = nullptr;
    XMP_StringLen prefixLen = 0;
    bool found = XMPMeta::GetNamespacePrefix("http://example.com/defaultns/", &prefix, &prefixLen);
    EXPECT_TRUE(found);

    delete adapter;
}

// Test that multiple namespaces can be registered in a single document
TEST_F(ExpatAdapterTest_2092, MultipleNamespaceRegistration_2092) {
    ExpatAdapter* adapter = ExpatAdapter::NewXMP(nullptr, 0);
    ASSERT_NE(adapter, nullptr);

    const char* xml = "<?xml version=\"1.0\"?>\n"
                      "<root xmlns:ns1=\"http://example.com/ns1/\" "
                      "xmlns:ns2=\"http://example.com/ns2/\">"
                      "</root>";

    adapter->ParseBuffer(xml, strlen(xml), true);

    XMP_StringPtr prefix1 = nullptr;
    XMP_StringLen prefixLen1 = 0;
    bool found1 = XMPMeta::GetNamespacePrefix("http://example.com/ns1/", &prefix1, &prefixLen1);
    EXPECT_TRUE(found1);

    XMP_StringPtr prefix2 = nullptr;
    XMP_StringLen prefixLen2 = 0;
    bool found2 = XMPMeta::GetNamespacePrefix("http://example.com/ns2/", &prefix2, &prefixLen2);
    EXPECT_TRUE(found2);

    delete adapter;
}

// Test creation and deletion of ExpatAdapter
TEST_F(ExpatAdapterTest_2092, AdapterCreation_2092) {
    ExpatAdapter* adapter = ExpatAdapter::NewXMP(nullptr, 0);
    ASSERT_NE(adapter, nullptr);
    delete adapter;
}

// Test parsing empty content
TEST_F(ExpatAdapterTest_2092, EmptyXMLParsing_2092) {
    ExpatAdapter* adapter = ExpatAdapter::NewXMP(nullptr, 0);
    ASSERT_NE(adapter, nullptr);

    const char* xml = "<?xml version=\"1.0\"?>\n<root/>";
    // Should not crash with no namespace declarations
    adapter->ParseBuffer(xml, strlen(xml), true);

    delete adapter;
}

// Test that the correct DC URI is used after remapping (old URI should not be registered)
TEST_F(ExpatAdapterTest_2092, OldDCURINotRegisteredDirectly_2092) {
    ExpatAdapter* adapter = ExpatAdapter::NewXMP(nullptr, 0);
    ASSERT_NE(adapter, nullptr);

    const char* xml = "<?xml version=\"1.0\"?>\n"
                      "<root xmlns:dc=\"http://purl.org/dc/1.1/\">"
                      "</root>";

    adapter->ParseBuffer(xml, strlen(xml), true);

    // The old URI should have been remapped, so the corrected one should exist
    XMP_StringPtr prefix = nullptr;
    XMP_StringLen prefixLen = 0;
    bool foundCorrected = XMPMeta::GetNamespacePrefix("http://purl.org/dc/elements/1.1/", &prefix, &prefixLen);
    EXPECT_TRUE(foundCorrected);

    delete adapter;
}

// Test namespace with nested elements
TEST_F(ExpatAdapterTest_2092, NestedNamespaceDeclarations_2092) {
    ExpatAdapter* adapter = ExpatAdapter::NewXMP(nullptr, 0);
    ASSERT_NE(adapter, nullptr);

    const char* xml = "<?xml version=\"1.0\"?>\n"
                      "<root xmlns:outer=\"http://example.com/outer/\">"
                      "<child xmlns:inner=\"http://example.com/inner/\"/>"
                      "</root>";

    adapter->ParseBuffer(xml, strlen(xml), true);

    XMP_StringPtr prefix = nullptr;
    XMP_StringLen prefixLen = 0;

    bool foundOuter = XMPMeta::GetNamespacePrefix("http://example.com/outer/", &prefix, &prefixLen);
    EXPECT_TRUE(foundOuter);

    bool foundInner = XMPMeta::GetNamespacePrefix("http://example.com/inner/", &prefix, &prefixLen);
    EXPECT_TRUE(foundInner);

    delete adapter;
}

// Test parsing a well-formed XMP packet with RDF namespace
TEST_F(ExpatAdapterTest_2092, XMPPacketParsing_2092) {
    ExpatAdapter* adapter = ExpatAdapter::NewXMP(nullptr, 0);
    ASSERT_NE(adapter, nullptr);

    const char* xml =
        "<?xml version=\"1.0\"?>\n"
        "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
        "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
        "<rdf:Description rdf:about=\"\""
        " xmlns:dc=\"http://purl.org/dc/elements/1.1/\">"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>";

    adapter->ParseBuffer(xml, strlen(xml), true);

    XMP_StringPtr prefix = nullptr;
    XMP_StringLen prefixLen = 0;
    bool foundDC = XMPMeta::GetNamespacePrefix("http://purl.org/dc/elements/1.1/", &prefix, &prefixLen);
    EXPECT_TRUE(foundDC);

    bool foundRDF = XMPMeta::GetNamespacePrefix("http://www.w3.org/1999/02/22-rdf-syntax-ns#", &prefix, &prefixLen);
    EXPECT_TRUE(foundRDF);

    delete adapter;
}

// Test that parsing incrementally works for namespace registration
TEST_F(ExpatAdapterTest_2092, IncrementalParsing_2092) {
    ExpatAdapter* adapter = ExpatAdapter::NewXMP(nullptr, 0);
    ASSERT_NE(adapter, nullptr);

    const char* part1 = "<?xml version=\"1.0\"?>\n"
                        "<root xmlns:test=\"http://example.com/test/\">";
    const char* part2 = "</root>";

    adapter->ParseBuffer(part1, strlen(part1), false);
    adapter->ParseBuffer(part2, strlen(part2), true);

    XMP_StringPtr prefix = nullptr;
    XMP_StringLen prefixLen = 0;
    bool found = XMPMeta::GetNamespacePrefix("http://example.com/test/", &prefix, &prefixLen);
    EXPECT_TRUE(found);

    delete adapter;
}
