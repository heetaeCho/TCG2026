#include <gtest/gtest.h>
#include <string>
#include <stdexcept>

// Include necessary headers
#include "XMP_Const.h"
#include "XMPCore_Impl.hpp"
#include "XMLParserAdapter.hpp"

// We need access to the XMP parsing functionality
// The RDF_NodeElement is called internally during XMP parsing
#define TXMP_STRING_TYPE std::string
#include "XMP.hpp"
#include "XMP.incl_cpp"

class ParseRDFTest_2127 : public ::testing::Test {
protected:
    void SetUp() override {
        SXMPMeta::Initialize();
    }

    void TearDown() override {
        SXMPMeta::Terminate();
    }
};

// Test that a valid rdf:Description node element parses without error
TEST_F(ParseRDFTest_2127, ValidDescriptionNodeElement_2127) {
    const char* xmpPacket =
        "<?xpacket begin=\"\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
        "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
        "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
        "<rdf:Description rdf:about=\"\" xmlns:dc=\"http://purl.org/dc/elements/1.1/\">"
        "<dc:title>Test</dc:title>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end=\"w\"?>";

    EXPECT_NO_THROW({
        SXMPMeta meta(xmpPacket, static_cast<XMP_StringLen>(strlen(xmpPacket)));
    });
}

// Test that a top-level typed node (not rdf:Description) throws kXMPErr_BadXMP
TEST_F(ParseRDFTest_2127, TopLevelTypedNodeThrows_2127) {
    const char* xmpPacket =
        "<?xpacket begin=\"\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
        "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
        "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
        "<dc:SomeType xmlns:dc=\"http://purl.org/dc/elements/1.1/\" rdf:about=\"\">"
        "<dc:title>Test</dc:title>"
        "</dc:SomeType>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end=\"w\"?>";

    EXPECT_ANY_THROW({
        SXMPMeta meta(xmpPacket, static_cast<XMP_StringLen>(strlen(xmpPacket)));
    });
}

// Test that an invalid RDF term as node element throws kXMPErr_BadRDF
TEST_F(ParseRDFTest_2127, InvalidRDFTermAsNodeElementThrows_2127) {
    const char* xmpPacket =
        "<?xpacket begin=\"\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
        "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
        "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
        "<rdf:Seq rdf:about=\"\">"
        "<rdf:li>Test</rdf:li>"
        "</rdf:Seq>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end=\"w\"?>";

    EXPECT_ANY_THROW({
        SXMPMeta meta(xmpPacket, static_cast<XMP_StringLen>(strlen(xmpPacket)));
    });
}

// Test that rdf:Bag used as node element throws
TEST_F(ParseRDFTest_2127, RDFBagAsNodeElementThrows_2127) {
    const char* xmpPacket =
        "<?xpacket begin=\"\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
        "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
        "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
        "<rdf:Bag rdf:about=\"\">"
        "<rdf:li>Test</rdf:li>"
        "</rdf:Bag>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end=\"w\"?>";

    EXPECT_ANY_THROW({
        SXMPMeta meta(xmpPacket, static_cast<XMP_StringLen>(strlen(xmpPacket)));
    });
}

// Test that rdf:Alt used as node element throws
TEST_F(ParseRDFTest_2127, RDFAltAsNodeElementThrows_2127) {
    const char* xmpPacket =
        "<?xpacket begin=\"\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
        "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
        "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
        "<rdf:Alt rdf:about=\"\">"
        "<rdf:li>Test</rdf:li>"
        "</rdf:Alt>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end=\"w\"?>";

    EXPECT_ANY_THROW({
        SXMPMeta meta(xmpPacket, static_cast<XMP_StringLen>(strlen(xmpPacket)));
    });
}

// Test valid rdf:Description with multiple properties
TEST_F(ParseRDFTest_2127, ValidDescriptionMultipleProperties_2127) {
    const char* xmpPacket =
        "<?xpacket begin=\"\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
        "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
        "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
        "<rdf:Description rdf:about=\"\" "
        "xmlns:dc=\"http://purl.org/dc/elements/1.1/\" "
        "xmlns:xmp=\"http://ns.adobe.com/xap/1.0/\">"
        "<dc:title>Title</dc:title>"
        "<dc:creator><rdf:Seq><rdf:li>Author</rdf:li></rdf:Seq></dc:creator>"
        "<xmp:CreateDate>2023-01-01</xmp:CreateDate>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end=\"w\"?>";

    SXMPMeta meta;
    EXPECT_NO_THROW({
        meta = SXMPMeta(xmpPacket, static_cast<XMP_StringLen>(strlen(xmpPacket)));
    });

    std::string value;
    EXPECT_TRUE(meta.GetProperty("http://ns.adobe.com/xap/1.0/", "CreateDate", &value, nullptr));
    EXPECT_EQ("2023-01-01", value);
}

// Test empty rdf:Description is valid
TEST_F(ParseRDFTest_2127, EmptyDescriptionIsValid_2127) {
    const char* xmpPacket =
        "<?xpacket begin=\"\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
        "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
        "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
        "<rdf:Description rdf:about=\"\"/>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end=\"w\"?>";

    EXPECT_NO_THROW({
        SXMPMeta meta(xmpPacket, static_cast<XMP_StringLen>(strlen(xmpPacket)));
    });
}

// Test rdf:li used as top-level node element throws
TEST_F(ParseRDFTest_2127, RDFLiAsNodeElementThrows_2127) {
    const char* xmpPacket =
        "<?xpacket begin=\"\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
        "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
        "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
        "<rdf:li rdf:about=\"\">"
        "<dc:title xmlns:dc=\"http://purl.org/dc/elements/1.1/\">Test</dc:title>"
        "</rdf:li>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end=\"w\"?>";

    EXPECT_ANY_THROW({
        SXMPMeta meta(xmpPacket, static_cast<XMP_StringLen>(strlen(xmpPacket)));
    });
}

// Test rdf:value used as top-level node element throws
TEST_F(ParseRDFTest_2127, RDFValueAsNodeElementThrows_2127) {
    const char* xmpPacket =
        "<?xpacket begin=\"\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
        "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
        "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
        "<rdf:value rdf:about=\"\">"
        "<dc:title xmlns:dc=\"http://purl.org/dc/elements/1.1/\">Test</dc:title>"
        "</rdf:value>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end=\"w\"?>";

    EXPECT_ANY_THROW({
        SXMPMeta meta(xmpPacket, static_cast<XMP_StringLen>(strlen(xmpPacket)));
    });
}

// Test valid non-top-level typed node (nested typed node should be allowed)
TEST_F(ParseRDFTest_2127, NestedTypedNodeValid_2127) {
    const char* xmpPacket =
        "<?xpacket begin=\"\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
        "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
        "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
        "<rdf:Description rdf:about=\"\" xmlns:dc=\"http://purl.org/dc/elements/1.1/\">"
        "<dc:title rdf:parseType=\"Resource\">"
        "<rdf:value>Test Title</rdf:value>"
        "</dc:title>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end=\"w\"?>";

    EXPECT_NO_THROW({
        SXMPMeta meta(xmpPacket, static_cast<XMP_StringLen>(strlen(xmpPacket)));
    });
}

// Test multiple Description elements at top level
TEST_F(ParseRDFTest_2127, MultipleTopLevelDescriptions_2127) {
    const char* xmpPacket =
        "<?xpacket begin=\"\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
        "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
        "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
        "<rdf:Description rdf:about=\"\" xmlns:dc=\"http://purl.org/dc/elements/1.1/\">"
        "<dc:title>Title1</dc:title>"
        "</rdf:Description>"
        "<rdf:Description rdf:about=\"\" xmlns:xmp=\"http://ns.adobe.com/xap/1.0/\">"
        "<xmp:CreateDate>2023-01-01</xmp:CreateDate>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end=\"w\"?>";

    SXMPMeta meta;
    EXPECT_NO_THROW({
        meta = SXMPMeta(xmpPacket, static_cast<XMP_StringLen>(strlen(xmpPacket)));
    });

    std::string value;
    EXPECT_TRUE(meta.GetProperty("http://ns.adobe.com/xap/1.0/", "CreateDate", &value, nullptr));
    EXPECT_EQ("2023-01-01", value);
}

// Test Description with attributes as property values
TEST_F(ParseRDFTest_2127, DescriptionWithAttributeProperties_2127) {
    const char* xmpPacket =
        "<?xpacket begin=\"\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
        "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
        "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
        "<rdf:Description rdf:about=\"\" "
        "xmlns:dc=\"http://purl.org/dc/elements/1.1/\" "
        "dc:format=\"image/jpeg\"/>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end=\"w\"?>";

    SXMPMeta meta;
    EXPECT_NO_THROW({
        meta = SXMPMeta(xmpPacket, static_cast<XMP_StringLen>(strlen(xmpPacket)));
    });

    std::string value;
    EXPECT_TRUE(meta.GetProperty("http://purl.org/dc/elements/1.1/", "format", &value, nullptr));
    EXPECT_EQ("image/jpeg", value);
}
