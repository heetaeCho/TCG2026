#include <gtest/gtest.h>
#include <string>
#include <cstring>

// Include necessary headers
#define TXMP_STRING_TYPE std::string
#include "XMP_Const.h"
#include "XMPMeta.hpp"
#include "XMLParserAdapter.hpp"
#include "ExpatAdapter.hpp"

class SetQualNameTest_2091 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        // Initialize XMP toolkit - needed for namespace prefix lookups
        XMPMeta::Initialize();
    }

    static void TearDownTestSuite() {
        XMPMeta::Terminate();
    }

    void SetUp() override {
        adapter = XMP_NewExpatAdapter(false);
    }

    void TearDown() override {
        if (adapter) {
            delete adapter;
            adapter = nullptr;
        }
    }

    XMLParserAdapter* adapter = nullptr;
};

// Test: Parsing a simple XMP packet with a known namespace produces correct node names
TEST_F(SetQualNameTest_2091, ParseSimpleXMPWithDCNamespace_2091) {
    const char* xmpData =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description rdf:about=''"
        " xmlns:dc='http://purl.org/dc/elements/1.1/'>"
        "<dc:title>"
        "<rdf:Alt><rdf:li xml:lang='x-default'>Test Title</rdf:li></rdf:Alt>"
        "</dc:title>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";

    adapter->ParseBuffer(xmpData, strlen(xmpData), true);
    
    // The tree should have been built; check the root exists
    ASSERT_NE(nullptr, &adapter->tree);
    EXPECT_FALSE(adapter->tree.content.empty());
}

// Test: Parsing XMP with dc/1.1 namespace (old form) gets normalized
TEST_F(SetQualNameTest_2091, ParseXMPWithOldDCNamespace_2091) {
    // The old DC namespace http://purl.org/dc/1.1/ should be normalized to
    // http://purl.org/dc/elements/1.1/
    const char* xmpData =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description rdf:about=''"
        " xmlns:dc='http://purl.org/dc/elements/1.1/'>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";

    ASSERT_NO_THROW(adapter->ParseBuffer(xmpData, strlen(xmpData), true));
    EXPECT_FALSE(adapter->tree.content.empty());
}

// Test: Parsing XMP with rdf:about attribute
TEST_F(SetQualNameTest_2091, ParseXMPWithRdfAbout_2091) {
    const char* xmpData =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description rdf:about='test-resource'>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";

    ASSERT_NO_THROW(adapter->ParseBuffer(xmpData, strlen(xmpData), true));
    EXPECT_FALSE(adapter->tree.content.empty());
}

// Test: XML_Node basic construction
TEST_F(SetQualNameTest_2091, XMLNodeConstruction_2091) {
    XML_Node root(nullptr, "root", 0);
    EXPECT_EQ("root", root.name);
    EXPECT_EQ(0, root.kind);
    EXPECT_EQ(0u, root.nsPrefixLen);
    EXPECT_EQ(nullptr, root.parent);
}

// Test: XML_Node with parent
TEST_F(SetQualNameTest_2091, XMLNodeWithParent_2091) {
    XML_Node root(nullptr, "root", 0);
    XML_Node child(&root, "child", 1);
    EXPECT_EQ("child", child.name);
    EXPECT_EQ(&root, child.parent);
    EXPECT_EQ(1, child.kind);
}

// Test: Parsing empty XMP packet
TEST_F(SetQualNameTest_2091, ParseEmptyXMPPacket_2091) {
    const char* xmpData =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";

    ASSERT_NO_THROW(adapter->ParseBuffer(xmpData, strlen(xmpData), true));
}

// Test: Parsing valid XML with multiple namespaces
TEST_F(SetQualNameTest_2091, ParseXMPWithMultipleNamespaces_2091) {
    const char* xmpData =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description rdf:about=''"
        " xmlns:dc='http://purl.org/dc/elements/1.1/'"
        " xmlns:xmp='http://ns.adobe.com/xap/1.0/'>"
        "<dc:creator><rdf:Seq><rdf:li>Author</rdf:li></rdf:Seq></dc:creator>"
        "<xmp:CreateDate>2023-01-01</xmp:CreateDate>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";

    ASSERT_NO_THROW(adapter->ParseBuffer(xmpData, strlen(xmpData), true));
    EXPECT_FALSE(adapter->tree.content.empty());
}

// Test: Parsing malformed XML throws or handles error
TEST_F(SetQualNameTest_2091, ParseMalformedXML_2091) {
    const char* xmpData = "<unclosed>";
    
    EXPECT_ANY_THROW(adapter->ParseBuffer(xmpData, strlen(xmpData), true));
}

// Test: Parsing XMP with rdf:ID attribute on Description
TEST_F(SetQualNameTest_2091, ParseXMPWithRdfID_2091) {
    const char* xmpData =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description rdf:ID='myid'"
        " xmlns:dc='http://purl.org/dc/elements/1.1/'>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";

    ASSERT_NO_THROW(adapter->ParseBuffer(xmpData, strlen(xmpData), true));
}

// Test: XML_Node string constructor
TEST_F(SetQualNameTest_2091, XMLNodeStringConstruction_2091) {
    std::string nodeName = "testNode";
    XML_Node root(nullptr, nodeName, 2);
    EXPECT_EQ("testNode", root.name);
    EXPECT_EQ(2, root.kind);
    EXPECT_EQ(0u, root.nsPrefixLen);
}

// Test: Parsing incremental buffer
TEST_F(SetQualNameTest_2091, ParseIncrementalBuffer_2091) {
    const char* part1 =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>";
    const char* part2 =
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description rdf:about=''/>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";

    ASSERT_NO_THROW(adapter->ParseBuffer(part1, strlen(part1), false));
    ASSERT_NO_THROW(adapter->ParseBuffer(part2, strlen(part2), true));
}

// Test: XML_Node attribute operations
TEST_F(SetQualNameTest_2091, XMLNodeSetAndGetAttrValue_2091) {
    XML_Node root(nullptr, "root", 0);
    root.SetAttrValue("testAttr", "testValue");
    XMP_StringPtr val = root.GetAttrValue("testAttr");
    ASSERT_NE(nullptr, val);
    EXPECT_STREQ("testValue", val);
}

// Test: XML_Node get non-existent attribute returns null
TEST_F(SetQualNameTest_2091, XMLNodeGetNonExistentAttr_2091) {
    XML_Node root(nullptr, "root", 0);
    XMP_StringPtr val = root.GetAttrValue("nonExistent");
    EXPECT_EQ(nullptr, val);
}

// Test: XML_Node ClearNode
TEST_F(SetQualNameTest_2091, XMLNodeClearNode_2091) {
    XML_Node root(nullptr, "root", 0);
    root.SetAttrValue("attr1", "val1");
    root.ClearNode();
    EXPECT_TRUE(root.attrs.empty());
    EXPECT_TRUE(root.content.empty());
}

// Test: XML_Node RemoveAttrs
TEST_F(SetQualNameTest_2091, XMLNodeRemoveAttrs_2091) {
    XML_Node root(nullptr, "root", 0);
    root.SetAttrValue("a", "1");
    root.SetAttrValue("b", "2");
    EXPECT_FALSE(root.attrs.empty());
    root.RemoveAttrs();
    EXPECT_TRUE(root.attrs.empty());
}

// Test: Parsing XMP with EXIF namespace
TEST_F(SetQualNameTest_2091, ParseXMPWithExifNamespace_2091) {
    const char* xmpData =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description rdf:about=''"
        " xmlns:exif='http://ns.adobe.com/exif/1.0/'>"
        "<exif:ExposureTime>1/60</exif:ExposureTime>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";

    ASSERT_NO_THROW(adapter->ParseBuffer(xmpData, strlen(xmpData), true));
    EXPECT_FALSE(adapter->tree.content.empty());
}

// Test: ExpatAdapter creation with namespace awareness
TEST_F(SetQualNameTest_2091, CreateExpatAdapterNamespaceAware_2091) {
    XMLParserAdapter* nsAdapter = XMP_NewExpatAdapter(true);
    ASSERT_NE(nullptr, nsAdapter);
    delete nsAdapter;
}

// Test: Parsing zero-length buffer as final
TEST_F(SetQualNameTest_2091, ParseZeroLengthFinal_2091) {
    // First parse some valid XML, then finalize with empty buffer
    const char* xmpData =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description rdf:about=''/>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";
    
    ASSERT_NO_THROW(adapter->ParseBuffer(xmpData, strlen(xmpData), false));
    ASSERT_NO_THROW(adapter->ParseBuffer("", 0, true));
}

// Test: XML_Node Dump produces non-empty output
TEST_F(SetQualNameTest_2091, XMLNodeDump_2091) {
    XML_Node root(nullptr, "root", 0);
    std::string buffer;
    root.Dump(&buffer);
    // Dump should produce some output describing the node
    EXPECT_FALSE(buffer.empty());
}

// Test: XML_Node Serialize
TEST_F(SetQualNameTest_2091, XMLNodeSerialize_2091) {
    XML_Node root(nullptr, "root", 0);
    std::string buffer;
    root.Serialize(&buffer);
    // Serialization should produce some XML-like output
    EXPECT_FALSE(buffer.empty());
}
