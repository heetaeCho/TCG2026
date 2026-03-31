#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <stdexcept>

// Include necessary headers
#include "XMP_Const.h"
#include "XMLParserAdapter.hpp"
#include "XMPCore_Impl.hpp"

// We need access to RDF_PropertyElement which is static in ParseRDF.cpp
// Since it's static, we test through the public parsing interface
// Include the XMP SDK public headers
#include "XMP.hpp"

// For XMP_Throw
#include "XMP_Environment.h"

class RDFPropertyElementTest_2130 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create an XML attribute node
    XML_Node* MakeAttr(XML_Node* parent, const std::string& name, const std::string& value) {
        XML_Node* attr = new XML_Node(parent, name.c_str(), kAttrNode);
        attr->value = value;
        return attr;
    }

    // Helper to create an XML element node
    XML_Node* MakeElem(XML_Node* parent, const std::string& name) {
        XML_Node* elem = new XML_Node(parent, name.c_str(), kElemNode);
        return elem;
    }

    // Helper to create a CData node
    XML_Node* MakeCData(XML_Node* parent, const std::string& value) {
        XML_Node* cdata = new XML_Node(parent, "", kCDataNode);
        cdata->value = value;
        return cdata;
    }
};

// Test: Parsing a simple RDF/XMP literal property through the full XMP parsing API
TEST_F(RDFPropertyElementTest_2130, ParseSimpleLiteralProperty_2130) {
    std::string rdfXml =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description rdf:about='' xmlns:dc='http://purl.org/dc/elements/1.1/'>"
        "<dc:title>Test Title</dc:title>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";

    SXMPMeta meta;
    EXPECT_NO_THROW(meta.ParseFromBuffer(rdfXml.c_str(), static_cast<XMP_StringLen>(rdfXml.size())));

    std::string value;
    bool found = meta.GetProperty("http://purl.org/dc/elements/1.1/", "title", &value, nullptr);
    EXPECT_TRUE(found);
    EXPECT_EQ(value, "Test Title");
}

// Test: Parsing a property with rdf:parseType="Resource"
TEST_F(RDFPropertyElementTest_2130, ParseTypeResourceProperty_2130) {
    std::string rdfXml =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description rdf:about='' xmlns:dc='http://purl.org/dc/elements/1.1/'>"
        "<dc:creator rdf:parseType='Resource'>"
        "<dc:title>Author</dc:title>"
        "</dc:creator>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";

    SXMPMeta meta;
    EXPECT_NO_THROW(meta.ParseFromBuffer(rdfXml.c_str(), static_cast<XMP_StringLen>(rdfXml.size())));
}

// Test: Parsing an empty property element (no content, no meaningful attrs)
TEST_F(RDFPropertyElementTest_2130, EmptyPropertyElement_2130) {
    std::string rdfXml =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description rdf:about='' xmlns:dc='http://purl.org/dc/elements/1.1/'>"
        "<dc:title/>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";

    SXMPMeta meta;
    EXPECT_NO_THROW(meta.ParseFromBuffer(rdfXml.c_str(), static_cast<XMP_StringLen>(rdfXml.size())));
}

// Test: Parsing a property with rdf:datatype attribute (literal property)
TEST_F(RDFPropertyElementTest_2130, DataTypeProperty_2130) {
    std::string rdfXml =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description rdf:about='' xmlns:dc='http://purl.org/dc/elements/1.1/'>"
        "<dc:title rdf:datatype='http://www.w3.org/2001/XMLSchema#string'>Typed Title</dc:title>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";

    SXMPMeta meta;
    EXPECT_NO_THROW(meta.ParseFromBuffer(rdfXml.c_str(), static_cast<XMP_StringLen>(rdfXml.size())));

    std::string value;
    bool found = meta.GetProperty("http://purl.org/dc/elements/1.1/", "title", &value, nullptr);
    EXPECT_TRUE(found);
    EXPECT_EQ(value, "Typed Title");
}

// Test: Parsing a property with xml:lang attribute (literal with qualifier)
TEST_F(RDFPropertyElementTest_2130, XmlLangProperty_2130) {
    std::string rdfXml =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description rdf:about='' xmlns:dc='http://purl.org/dc/elements/1.1/'>"
        "<dc:title xml:lang='en'>English Title</dc:title>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";

    SXMPMeta meta;
    EXPECT_NO_THROW(meta.ParseFromBuffer(rdfXml.c_str(), static_cast<XMP_StringLen>(rdfXml.size())));

    std::string value;
    bool found = meta.GetProperty("http://purl.org/dc/elements/1.1/", "title", &value, nullptr);
    EXPECT_TRUE(found);
}

// Test: Property with rdf:parseType="Literal" (XML literal)
TEST_F(RDFPropertyElementTest_2130, ParseTypeLiteralProperty_2130) {
    std::string rdfXml =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description rdf:about='' xmlns:dc='http://purl.org/dc/elements/1.1/'>"
        "<dc:description rdf:parseType='Literal'><b>Bold text</b></dc:description>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";

    SXMPMeta meta;
    EXPECT_NO_THROW(meta.ParseFromBuffer(rdfXml.c_str(), static_cast<XMP_StringLen>(rdfXml.size())));
}

// Test: Property with rdf:parseType="Collection"
TEST_F(RDFPropertyElementTest_2130, ParseTypeCollectionProperty_2130) {
    std::string rdfXml =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description rdf:about='' xmlns:dc='http://purl.org/dc/elements/1.1/'>"
        "<dc:subject rdf:parseType='Collection'>"
        "<rdf:Description dc:title='Item1'/>"
        "</dc:subject>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";

    SXMPMeta meta;
    // Collection parseType may throw or be handled specially
    EXPECT_NO_THROW(meta.ParseFromBuffer(rdfXml.c_str(), static_cast<XMP_StringLen>(rdfXml.size())));
}

// Test: Property with rdf:parseType="Other" (unknown parse type)
TEST_F(RDFPropertyElementTest_2130, ParseTypeOtherProperty_2130) {
    std::string rdfXml =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description rdf:about='' xmlns:dc='http://purl.org/dc/elements/1.1/'>"
        "<dc:subject rdf:parseType='CustomType'>"
        "<someElement>content</someElement>"
        "</dc:subject>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";

    SXMPMeta meta;
    EXPECT_NO_THROW(meta.ParseFromBuffer(rdfXml.c_str(), static_cast<XMP_StringLen>(rdfXml.size())));
}

// Test: Resource property element (content has non-CData children)
TEST_F(RDFPropertyElementTest_2130, ResourcePropertyElement_2130) {
    std::string rdfXml =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description rdf:about='' xmlns:dc='http://purl.org/dc/elements/1.1/'>"
        "<dc:creator>"
        "<rdf:Seq>"
        "<rdf:li>Author Name</rdf:li>"
        "</rdf:Seq>"
        "</dc:creator>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";

    SXMPMeta meta;
    EXPECT_NO_THROW(meta.ParseFromBuffer(rdfXml.c_str(), static_cast<XMP_StringLen>(rdfXml.size())));

    std::string value;
    bool found = meta.GetArrayItem("http://purl.org/dc/elements/1.1/", "creator", 1, &value, nullptr);
    EXPECT_TRUE(found);
    EXPECT_EQ(value, "Author Name");
}

// Test: Empty property with multiple attributes (more than 3 attrs -> empty property element path)
TEST_F(RDFPropertyElementTest_2130, MoreThan3AttrsEmptyProperty_2130) {
    std::string rdfXml =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description rdf:about='' "
        "xmlns:dc='http://purl.org/dc/elements/1.1/' "
        "xmlns:xmp='http://ns.adobe.com/xap/1.0/'>"
        "<dc:description xml:lang='en' rdf:ID='id1' xmp:Rating='5' dc:title='test'/>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";

    SXMPMeta meta;
    EXPECT_NO_THROW(meta.ParseFromBuffer(rdfXml.c_str(), static_cast<XMP_StringLen>(rdfXml.size())));
}

// Test: Property with rdf:ID and xml:lang only (should reach the content-check branch)
TEST_F(RDFPropertyElementTest_2130, OnlyLangAndIDAttrs_2130) {
    std::string rdfXml =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description rdf:about='' xmlns:dc='http://purl.org/dc/elements/1.1/'>"
        "<dc:title xml:lang='en' rdf:ID='myid'>Hello</dc:title>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";

    SXMPMeta meta;
    EXPECT_NO_THROW(meta.ParseFromBuffer(rdfXml.c_str(), static_cast<XMP_StringLen>(rdfXml.size())));
}

// Test: Invalid property element name should cause an error
TEST_F(RDFPropertyElementTest_2130, InvalidPropertyElementName_2130) {
    // Using rdf:RDF as a property element name is invalid
    std::string rdfXml =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description rdf:about=''>"
        "<rdf:RDF>invalid</rdf:RDF>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";

    SXMPMeta meta;
    EXPECT_ANY_THROW(meta.ParseFromBuffer(rdfXml.c_str(), static_cast<XMP_StringLen>(rdfXml.size())));
}

// Test: Property with non-rdf, non-lang attribute triggers empty property element
TEST_F(RDFPropertyElementTest_2130, NonRDFAttrTriggersEmptyProperty_2130) {
    std::string rdfXml =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description rdf:about='' xmlns:dc='http://purl.org/dc/elements/1.1/'>"
        "<dc:title rdf:resource='http://example.com/resource'/>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";

    SXMPMeta meta;
    EXPECT_NO_THROW(meta.ParseFromBuffer(rdfXml.c_str(), static_cast<XMP_StringLen>(rdfXml.size())));
}

// Test: Structured (bag) property
TEST_F(RDFPropertyElementTest_2130, BagPropertyElement_2130) {
    std::string rdfXml =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description rdf:about='' xmlns:dc='http://purl.org/dc/elements/1.1/'>"
        "<dc:subject>"
        "<rdf:Bag>"
        "<rdf:li>keyword1</rdf:li>"
        "<rdf:li>keyword2</rdf:li>"
        "</rdf:Bag>"
        "</dc:subject>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";

    SXMPMeta meta;
    EXPECT_NO_THROW(meta.ParseFromBuffer(rdfXml.c_str(), static_cast<XMP_StringLen>(rdfXml.size())));

    XMP_Int32 count = meta.CountArrayItems("http://purl.org/dc/elements/1.1/", "subject");
    EXPECT_EQ(count, 2);

    std::string val1, val2;
    meta.GetArrayItem("http://purl.org/dc/elements/1.1/", "subject", 1, &val1, nullptr);
    meta.GetArrayItem("http://purl.org/dc/elements/1.1/", "subject", 2, &val2, nullptr);
    EXPECT_EQ(val1, "keyword1");
    EXPECT_EQ(val2, "keyword2");
}

// Test: Alt property with multiple language alternatives
TEST_F(RDFPropertyElementTest_2130, AltPropertyElement_2130) {
    std::string rdfXml =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description rdf:about='' xmlns:dc='http://purl.org/dc/elements/1.1/'>"
        "<dc:title>"
        "<rdf:Alt>"
        "<rdf:li xml:lang='x-default'>Default Title</rdf:li>"
        "<rdf:li xml:lang='en'>English Title</rdf:li>"
        "</rdf:Alt>"
        "</dc:title>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";

    SXMPMeta meta;
    EXPECT_NO_THROW(meta.ParseFromBuffer(rdfXml.c_str(), static_cast<XMP_StringLen>(rdfXml.size())));

    std::string value;
    bool found = meta.GetLocalizedText("http://purl.org/dc/elements/1.1/", "title",
                                        "en", "en", nullptr, &value, nullptr);
    EXPECT_TRUE(found);
    EXPECT_EQ(value, "English Title");
}

// Test: Completely empty RDF (no properties)
TEST_F(RDFPropertyElementTest_2130, EmptyRDF_2130) {
    std::string rdfXml =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description rdf:about=''/>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";

    SXMPMeta meta;
    EXPECT_NO_THROW(meta.ParseFromBuffer(rdfXml.c_str(), static_cast<XMP_StringLen>(rdfXml.size())));
}

// Test: Malformed RDF throws exception
TEST_F(RDFPropertyElementTest_2130, MalformedRDFThrows_2130) {
    std::string rdfXml =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<not_rdf_description>bad</not_rdf_description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";

    SXMPMeta meta;
    EXPECT_ANY_THROW(meta.ParseFromBuffer(rdfXml.c_str(), static_cast<XMP_StringLen>(rdfXml.size())));
}

// Test: Multiple properties in single description
TEST_F(RDFPropertyElementTest_2130, MultiplePropertiesInDescription_2130) {
    std::string rdfXml =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description rdf:about='' "
        "xmlns:dc='http://purl.org/dc/elements/1.1/' "
        "xmlns:xmp='http://ns.adobe.com/xap/1.0/'>"
        "<dc:title>My Title</dc:title>"
        "<dc:description>My Description</dc:description>"
        "<xmp:Rating>5</xmp:Rating>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";

    SXMPMeta meta;
    EXPECT_NO_THROW(meta.ParseFromBuffer(rdfXml.c_str(), static_cast<XMP_StringLen>(rdfXml.size())));

    std::string title, desc, rating;
    EXPECT_TRUE(meta.GetProperty("http://purl.org/dc/elements/1.1/", "title", &title, nullptr));
    EXPECT_EQ(title, "My Title");

    EXPECT_TRUE(meta.GetProperty("http://purl.org/dc/elements/1.1/", "description", &desc, nullptr));
    EXPECT_EQ(desc, "My Description");

    EXPECT_TRUE(meta.GetProperty("http://ns.adobe.com/xap/1.0/", "Rating", &rating, nullptr));
    EXPECT_EQ(rating, "5");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
