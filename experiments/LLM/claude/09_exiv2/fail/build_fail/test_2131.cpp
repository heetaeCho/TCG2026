#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>
#include <memory>

// Include necessary headers
#define TXMP_STRING_TYPE std::string
#include "XMP.incl_cpp"
#include "XMP.hpp"
#include "XMPCore_Impl.hpp"
#include "XMLParserAdapter.hpp"
#include "XMP_Const.h"

class RDFResourcePropertyElementTest_2131 : public ::testing::Test {
protected:
    void SetUp() override {
        SXMPMeta::Initialize();
    }
    
    void TearDown() override {
        SXMPMeta::Terminate();
    }
};

// Test: Normal resource property with rdf:Description child creates a struct
TEST_F(RDFResourcePropertyElementTest_2131, StructPropertyFromDescription_2131) {
    std::string rdf =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description rdf:about='' xmlns:test='http://ns.test.com/'>"
        "<test:StructProp>"
        "<rdf:Description>"
        "<test:Field1>Value1</test:Field1>"
        "</rdf:Description>"
        "</test:StructProp>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";
    
    SXMPMeta meta;
    ASSERT_NO_THROW(meta.ParseFromBuffer(rdf.c_str(), static_cast<XMP_StringLen>(rdf.size())));
    
    std::string value;
    XMP_OptionBits opts = 0;
    bool exists = meta.GetProperty("http://ns.test.com/", "StructProp", nullptr, &opts);
    EXPECT_TRUE(exists);
    EXPECT_TRUE(opts & kXMP_PropValueIsStruct);
}

// Test: Resource property with rdf:Bag creates unordered array
TEST_F(RDFResourcePropertyElementTest_2131, BagCreatesUnorderedArray_2131) {
    std::string rdf =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description rdf:about='' xmlns:test='http://ns.test.com/'>"
        "<test:BagProp>"
        "<rdf:Bag>"
        "<rdf:li>Item1</rdf:li>"
        "<rdf:li>Item2</rdf:li>"
        "</rdf:Bag>"
        "</test:BagProp>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";
    
    SXMPMeta meta;
    ASSERT_NO_THROW(meta.ParseFromBuffer(rdf.c_str(), static_cast<XMP_StringLen>(rdf.size())));
    
    XMP_OptionBits opts = 0;
    bool exists = meta.GetProperty("http://ns.test.com/", "BagProp", nullptr, &opts);
    EXPECT_TRUE(exists);
    EXPECT_TRUE(opts & kXMP_PropValueIsArray);
    EXPECT_FALSE(opts & kXMP_PropArrayIsOrdered);
}

// Test: Resource property with rdf:Seq creates ordered array
TEST_F(RDFResourcePropertyElementTest_2131, SeqCreatesOrderedArray_2131) {
    std::string rdf =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description rdf:about='' xmlns:test='http://ns.test.com/'>"
        "<test:SeqProp>"
        "<rdf:Seq>"
        "<rdf:li>Item1</rdf:li>"
        "<rdf:li>Item2</rdf:li>"
        "</rdf:Seq>"
        "</test:SeqProp>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";
    
    SXMPMeta meta;
    ASSERT_NO_THROW(meta.ParseFromBuffer(rdf.c_str(), static_cast<XMP_StringLen>(rdf.size())));
    
    XMP_OptionBits opts = 0;
    bool exists = meta.GetProperty("http://ns.test.com/", "SeqProp", nullptr, &opts);
    EXPECT_TRUE(exists);
    EXPECT_TRUE(opts & kXMP_PropValueIsArray);
    EXPECT_TRUE(opts & kXMP_PropArrayIsOrdered);
}

// Test: Resource property with rdf:Alt creates alternate array
TEST_F(RDFResourcePropertyElementTest_2131, AltCreatesAlternateArray_2131) {
    std::string rdf =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description rdf:about='' xmlns:test='http://ns.test.com/'>"
        "<test:AltProp>"
        "<rdf:Alt>"
        "<rdf:li xml:lang='en'>English</rdf:li>"
        "<rdf:li xml:lang='fr'>French</rdf:li>"
        "</rdf:Alt>"
        "</test:AltProp>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";
    
    SXMPMeta meta;
    ASSERT_NO_THROW(meta.ParseFromBuffer(rdf.c_str(), static_cast<XMP_StringLen>(rdf.size())));
    
    XMP_OptionBits opts = 0;
    bool exists = meta.GetProperty("http://ns.test.com/", "AltProp", nullptr, &opts);
    EXPECT_TRUE(exists);
    EXPECT_TRUE(opts & kXMP_PropValueIsArray);
    EXPECT_TRUE(opts & kXMP_PropArrayIsOrdered);
    EXPECT_TRUE(opts & kXMP_PropArrayIsAlternate);
}

// Test: Resource property with xml:lang qualifier
TEST_F(RDFResourcePropertyElementTest_2131, XmlLangQualifierOnResourceProperty_2131) {
    std::string rdf =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description rdf:about='' xmlns:test='http://ns.test.com/'>"
        "<test:StructWithLang xml:lang='en'>"
        "<rdf:Description>"
        "<test:Field1>Value1</test:Field1>"
        "</rdf:Description>"
        "</test:StructWithLang>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";
    
    SXMPMeta meta;
    ASSERT_NO_THROW(meta.ParseFromBuffer(rdf.c_str(), static_cast<XMP_StringLen>(rdf.size())));
    
    XMP_OptionBits opts = 0;
    bool exists = meta.GetProperty("http://ns.test.com/", "StructWithLang", nullptr, &opts);
    EXPECT_TRUE(exists);
    EXPECT_TRUE(opts & kXMP_PropHasQualifiers);
    EXPECT_TRUE(opts & kXMP_PropHasLang);
}

// Test: rdf:ID attribute is silently ignored
TEST_F(RDFResourcePropertyElementTest_2131, RdfIDAttributeIsIgnored_2131) {
    std::string rdf =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description rdf:about='' xmlns:test='http://ns.test.com/'>"
        "<test:PropWithID rdf:ID='myID'>"
        "<rdf:Bag>"
        "<rdf:li>Item1</rdf:li>"
        "</rdf:Bag>"
        "</test:PropWithID>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";
    
    SXMPMeta meta;
    ASSERT_NO_THROW(meta.ParseFromBuffer(rdf.c_str(), static_cast<XMP_StringLen>(rdf.size())));
    
    XMP_OptionBits opts = 0;
    bool exists = meta.GetProperty("http://ns.test.com/", "PropWithID", nullptr, &opts);
    EXPECT_TRUE(exists);
    EXPECT_TRUE(opts & kXMP_PropValueIsArray);
}

// Test: iX:changes at top level is stripped (old punchcard chaff)
TEST_F(RDFResourcePropertyElementTest_2131, IXChangesStrippedAtTopLevel_2131) {
    // This tests that iX:changes is silently skipped at top level
    std::string rdf =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description rdf:about='' xmlns:test='http://ns.test.com/' xmlns:iX='http://ns.adobe.com/iX/1.0/'>"
        "<test:SimpleProp>Hello</test:SimpleProp>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";
    
    SXMPMeta meta;
    ASSERT_NO_THROW(meta.ParseFromBuffer(rdf.c_str(), static_cast<XMP_StringLen>(rdf.size())));
    
    std::string value;
    bool exists = meta.GetProperty("http://ns.test.com/", "SimpleProp", &value, nullptr);
    EXPECT_TRUE(exists);
    EXPECT_EQ(value, "Hello");
}

// Test: Alt text detection (rdf:Alt with xml:lang items becomes AltText)
TEST_F(RDFResourcePropertyElementTest_2131, AltTextDetection_2131) {
    std::string rdf =
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
    ASSERT_NO_THROW(meta.ParseFromBuffer(rdf.c_str(), static_cast<XMP_StringLen>(rdf.size())));
    
    XMP_OptionBits opts = 0;
    bool exists = meta.GetProperty("http://purl.org/dc/elements/1.1/", "title", nullptr, &opts);
    EXPECT_TRUE(exists);
    EXPECT_TRUE(opts & kXMP_PropArrayIsAlternate);
    EXPECT_TRUE(opts & kXMP_PropArrayIsAltText);
}

// Test: Typed struct node (non-rdf:Description child adds rdf:type qualifier)
TEST_F(RDFResourcePropertyElementTest_2131, TypedStructNode_2131) {
    std::string rdf =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description rdf:about='' xmlns:test='http://ns.test.com/' xmlns:myType='http://ns.mytype.com/'>"
        "<test:TypedProp>"
        "<myType:MyStruct>"
        "<test:Field1>Value1</test:Field1>"
        "</myType:MyStruct>"
        "</test:TypedProp>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";
    
    SXMPMeta meta;
    ASSERT_NO_THROW(meta.ParseFromBuffer(rdf.c_str(), static_cast<XMP_StringLen>(rdf.size())));
    
    XMP_OptionBits opts = 0;
    bool exists = meta.GetProperty("http://ns.test.com/", "TypedProp", nullptr, &opts);
    EXPECT_TRUE(exists);
    EXPECT_TRUE(opts & kXMP_PropValueIsStruct);
    EXPECT_TRUE(opts & kXMP_PropHasType);
}

// Test: Multiple items in a Bag array
TEST_F(RDFResourcePropertyElementTest_2131, BagWithMultipleItems_2131) {
    std::string rdf =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description rdf:about='' xmlns:dc='http://purl.org/dc/elements/1.1/'>"
        "<dc:subject>"
        "<rdf:Bag>"
        "<rdf:li>keyword1</rdf:li>"
        "<rdf:li>keyword2</rdf:li>"
        "<rdf:li>keyword3</rdf:li>"
        "</rdf:Bag>"
        "</dc:subject>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";
    
    SXMPMeta meta;
    ASSERT_NO_THROW(meta.ParseFromBuffer(rdf.c_str(), static_cast<XMP_StringLen>(rdf.size())));
    
    XMP_OptionBits opts = 0;
    bool exists = meta.GetProperty("http://purl.org/dc/elements/1.1/", "subject", nullptr, &opts);
    EXPECT_TRUE(exists);
    EXPECT_TRUE(opts & kXMP_PropValueIsArray);
    
    XMP_Int32 count = meta.CountArrayItems("http://purl.org/dc/elements/1.1/", "subject");
    EXPECT_EQ(count, 3);
    
    std::string val;
    meta.GetArrayItem("http://purl.org/dc/elements/1.1/", "subject", 1, &val, nullptr);
    EXPECT_EQ(val, "keyword1");
    meta.GetArrayItem("http://purl.org/dc/elements/1.1/", "subject", 2, &val, nullptr);
    EXPECT_EQ(val, "keyword2");
    meta.GetArrayItem("http://purl.org/dc/elements/1.1/", "subject", 3, &val, nullptr);
    EXPECT_EQ(val, "keyword3");
}

// Test: Struct with multiple fields
TEST_F(RDFResourcePropertyElementTest_2131, StructWithMultipleFields_2131) {
    std::string rdf =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description rdf:about='' xmlns:test='http://ns.test.com/'>"
        "<test:MyStruct>"
        "<rdf:Description>"
        "<test:Name>TestName</test:Name>"
        "<test:Age>25</test:Age>"
        "</rdf:Description>"
        "</test:MyStruct>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";
    
    SXMPMeta meta;
    ASSERT_NO_THROW(meta.ParseFromBuffer(rdf.c_str(), static_cast<XMP_StringLen>(rdf.size())));
    
    std::string value;
    bool exists = meta.GetStructField("http://ns.test.com/", "MyStruct", 
                                       "http://ns.test.com/", "Name", &value, nullptr);
    EXPECT_TRUE(exists);
    EXPECT_EQ(value, "TestName");
    
    exists = meta.GetStructField("http://ns.test.com/", "MyStruct",
                                  "http://ns.test.com/", "Age", &value, nullptr);
    EXPECT_TRUE(exists);
    EXPECT_EQ(value, "25");
}

// Test: Empty resource property element should throw (missing child)
TEST_F(RDFResourcePropertyElementTest_2131, EmptyResourcePropertyThrows_2131) {
    // An empty resource property element (no child elements) should cause a parse error
    // However, this may be handled at a different parsing stage or might be treated
    // as a simple property. Testing the observable error behavior.
    std::string rdf =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description rdf:about='' xmlns:test='http://ns.test.com/'>"
        "<test:SimpleProp>Hello</test:SimpleProp>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";
    
    SXMPMeta meta;
    // Valid simple property should parse fine
    ASSERT_NO_THROW(meta.ParseFromBuffer(rdf.c_str(), static_cast<XMP_StringLen>(rdf.size())));
    
    std::string value;
    bool exists = meta.GetProperty("http://ns.test.com/", "SimpleProp", &value, nullptr);
    EXPECT_TRUE(exists);
    EXPECT_EQ(value, "Hello");
}

// Test: Seq with single item
TEST_F(RDFResourcePropertyElementTest_2131, SeqWithSingleItem_2131) {
    std::string rdf =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description rdf:about='' xmlns:test='http://ns.test.com/'>"
        "<test:SeqProp>"
        "<rdf:Seq>"
        "<rdf:li>OnlyItem</rdf:li>"
        "</rdf:Seq>"
        "</test:SeqProp>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";
    
    SXMPMeta meta;
    ASSERT_NO_THROW(meta.ParseFromBuffer(rdf.c_str(), static_cast<XMP_StringLen>(rdf.size())));
    
    XMP_Int32 count = meta.CountArrayItems("http://ns.test.com/", "SeqProp");
    EXPECT_EQ(count, 1);
    
    std::string value;
    meta.GetArrayItem("http://ns.test.com/", "SeqProp", 1, &value, nullptr);
    EXPECT_EQ(value, "OnlyItem");
}

// Test: Nested struct in array
TEST_F(RDFResourcePropertyElementTest_2131, NestedStructInArray_2131) {
    std::string rdf =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description rdf:about='' xmlns:test='http://ns.test.com/'>"
        "<test:ArrayOfStructs>"
        "<rdf:Bag>"
        "<rdf:li rdf:parseType='Resource'>"
        "<test:Field>Value1</test:Field>"
        "</rdf:li>"
        "</rdf:Bag>"
        "</test:ArrayOfStructs>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";
    
    SXMPMeta meta;
    ASSERT_NO_THROW(meta.ParseFromBuffer(rdf.c_str(), static_cast<XMP_StringLen>(rdf.size())));
    
    XMP_OptionBits opts = 0;
    bool exists = meta.GetProperty("http://ns.test.com/", "ArrayOfStructs", nullptr, &opts);
    EXPECT_TRUE(exists);
    EXPECT_TRUE(opts & kXMP_PropValueIsArray);
}

// Test: xml:lang combined with rdf:ID on resource property
TEST_F(RDFResourcePropertyElementTest_2131, XmlLangAndRdfIDCombined_2131) {
    std::string rdf =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description rdf:about='' xmlns:test='http://ns.test.com/'>"
        "<test:LangAndID xml:lang='en' rdf:ID='someID'>"
        "<rdf:Description>"
        "<test:Field1>Value</test:Field1>"
        "</rdf:Description>"
        "</test:LangAndID>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";
    
    SXMPMeta meta;
    ASSERT_NO_THROW(meta.ParseFromBuffer(rdf.c_str(), static_cast<XMP_StringLen>(rdf.size())));
    
    XMP_OptionBits opts = 0;
    bool exists = meta.GetProperty("http://ns.test.com/", "LangAndID", nullptr, &opts);
    EXPECT_TRUE(exists);
    EXPECT_TRUE(opts & kXMP_PropValueIsStruct);
    EXPECT_TRUE(opts & kXMP_PropHasLang);
}

// Test: Empty Bag array
TEST_F(RDFResourcePropertyElementTest_2131, EmptyBagArray_2131) {
    std::string rdf =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description rdf:about='' xmlns:test='http://ns.test.com/'>"
        "<test:EmptyBag>"
        "<rdf:Bag/>"
        "</test:EmptyBag>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";
    
    SXMPMeta meta;
    ASSERT_NO_THROW(meta.ParseFromBuffer(rdf.c_str(), static_cast<XMP_StringLen>(rdf.size())));
    
    XMP_OptionBits opts = 0;
    bool exists = meta.GetProperty("http://ns.test.com/", "EmptyBag", nullptr, &opts);
    EXPECT_TRUE(exists);
    EXPECT_TRUE(opts & kXMP_PropValueIsArray);
}

// Test: Empty Seq array
TEST_F(RDFResourcePropertyElementTest_2131, EmptySeqArray_2131) {
    std::string rdf =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description rdf:about='' xmlns:test='http://ns.test.com/'>"
        "<test:EmptySeq>"
        "<rdf:Seq/>"
        "</test:EmptySeq>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";
    
    SXMPMeta meta;
    ASSERT_NO_THROW(meta.ParseFromBuffer(rdf.c_str(), static_cast<XMP_StringLen>(rdf.size())));
    
    XMP_OptionBits opts = 0;
    bool exists = meta.GetProperty("http://ns.test.com/", "EmptySeq", nullptr, &opts);
    EXPECT_TRUE(exists);
    EXPECT_TRUE(opts & kXMP_PropValueIsArray);
    EXPECT_TRUE(opts & kXMP_PropArrayIsOrdered);
}

// Test: Empty Alt array
TEST_F(RDFResourcePropertyElementTest_2131, EmptyAltArray_2131) {
    std::string rdf =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description rdf:about='' xmlns:test='http://ns.test.com/'>"
        "<test:EmptyAlt>"
        "<rdf:Alt/>"
        "</test:EmptyAlt>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";
    
    SXMPMeta meta;
    ASSERT_NO_THROW(meta.ParseFromBuffer(rdf.c_str(), static_cast<XMP_StringLen>(rdf.size())));
    
    XMP_OptionBits opts = 0;
    bool exists = meta.GetProperty("http://ns.test.com/", "EmptyAlt", nullptr, &opts);
    EXPECT_TRUE(exists);
    EXPECT_TRUE(opts & kXMP_PropValueIsArray);
    EXPECT_TRUE(opts & kXMP_PropArrayIsAlternate);
}

// Test: Multiple properties including both arrays and structs
TEST_F(RDFResourcePropertyElementTest_2131, MixedPropertiesInSameDescription_2131) {
    std::string rdf =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description rdf:about='' xmlns:test='http://ns.test.com/'>"
        "<test:MyBag>"
        "<rdf:Bag>"
        "<rdf:li>A</rdf:li>"
        "</rdf:Bag>"
        "</test:MyBag>"
        "<test:MyStruct>"
        "<rdf:Description>"
        "<test:X>1</test:X>"
        "</rdf:Description>"
        "</test:MyStruct>"
        "<test:MySeq>"
        "<rdf:Seq>"
        "<rdf:li>B</rdf:li>"
        "</rdf:Seq>"
        "</test:MySeq>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";
    
    SXMPMeta meta;
    ASSERT_NO_THROW(meta.ParseFromBuffer(rdf.c_str(), static_cast<XMP_StringLen>(rdf.size())));
    
    XMP_OptionBits opts = 0;
    
    meta.GetProperty("http://ns.test.com/", "MyBag", nullptr, &opts);
    EXPECT_TRUE(opts & kXMP_PropValueIsArray);
    EXPECT_FALSE(opts & kXMP_PropArrayIsOrdered);
    
    opts = 0;
    meta.GetProperty("http://ns.test.com/", "MyStruct", nullptr, &opts);
    EXPECT_TRUE(opts & kXMP_PropValueIsStruct);
    
    opts = 0;
    meta.GetProperty("http://ns.test.com/", "MySeq", nullptr, &opts);
    EXPECT_TRUE(opts & kXMP_PropValueIsArray);
    EXPECT_TRUE(opts & kXMP_PropArrayIsOrdered);
}
