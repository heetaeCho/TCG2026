#include <gtest/gtest.h>
#include <string>
#include <map>

// Reproduce the types used in the code under test
typedef const char* XMP_StringPtr;
typedef int32_t XMP_Index;
typedef std::string XMP_VarString;
typedef std::map<std::string, std::string> XMP_StringMap;
typedef XMP_StringMap::iterator XMP_StringMapPos;

// The global namespace map used by the code
XMP_StringMap* sNamespacePrefixToURIMap = nullptr;

// XMP_Enforce throws on failure (kXMPErr_EnforceFailure = 7)
#include <stdexcept>

struct XMP_Error : public std::exception {
    int id_;
    std::string msg_;
    XMP_Error(int id, const char* msg) : id_(id), msg_(msg) {}
    const char* what() const noexcept override { return msg_.c_str(); }
    int GetID() const { return id_; }
};

#define XMP_Enforce(expr) \
    if (!(expr)) throw XMP_Error(7, "XMP_Enforce failure")

// DeclareOneNamespace - we need to provide a definition since DeclareElemNamespace calls it.
// We'll track calls to it for verification purposes.
struct DeclareOneNamespaceCall {
    XMP_VarString nsPrefix;
    XMP_VarString nsURI;
    XMP_VarString usedNS;
    XMP_VarString outputStr;
    XMP_StringPtr newline;
    XMP_StringPtr indentStr;
    XMP_Index indent;
};

static std::vector<DeclareOneNamespaceCall> g_declareOneNamespaceCalls;

static void DeclareOneNamespace(
    const XMP_VarString& nsPrefix,
    const XMP_VarString& nsURI,
    XMP_VarString& usedNS,
    XMP_VarString& outputStr,
    XMP_StringPtr newline,
    XMP_StringPtr indentStr,
    XMP_Index indent)
{
    DeclareOneNamespaceCall call;
    call.nsPrefix = nsPrefix;
    call.nsURI = nsURI;
    call.usedNS = usedNS;
    call.outputStr = outputStr;
    call.newline = newline ? newline : "";
    call.indentStr = indentStr ? indentStr : "";
    call.indent = indent;
    g_declareOneNamespaceCalls.push_back(call);

    // Simulate typical behavior: append namespace declaration info
    if (usedNS.find(nsPrefix) == std::string::npos) {
        usedNS += nsPrefix;
        outputStr += std::string("xmlns:") + nsPrefix + "=\"" + nsURI + "\"";
    }
}

// The function under test (copy from the source)
static void DeclareElemNamespace(
    const XMP_VarString& elemName,
    XMP_VarString& usedNS,
    XMP_VarString& outputStr,
    XMP_StringPtr newline,
    XMP_StringPtr indentStr,
    XMP_Index indent)
{
    size_t colonPos = elemName.find(':');
    if (colonPos != XMP_VarString::npos) {
        XMP_VarString nsPrefix(elemName.substr(0, colonPos + 1));
        XMP_StringMapPos prefixPos = sNamespacePrefixToURIMap->find(nsPrefix);
        XMP_Enforce(prefixPos != sNamespacePrefixToURIMap->end());
        DeclareOneNamespace(nsPrefix, prefixPos->second, usedNS, outputStr, newline, indentStr, indent);
    }
}

class DeclareElemNamespaceTest_2105 : public ::testing::Test {
protected:
    void SetUp() override {
        namespaceMap_.clear();
        sNamespacePrefixToURIMap = &namespaceMap_;
        g_declareOneNamespaceCalls.clear();
    }

    void TearDown() override {
        sNamespacePrefixToURIMap = nullptr;
        g_declareOneNamespaceCalls.clear();
    }

    XMP_StringMap namespaceMap_;
};

// Test: Element name with a known namespace prefix calls DeclareOneNamespace
TEST_F(DeclareElemNamespaceTest_2105, KnownPrefixCallsDeclareOneNamespace_2105) {
    namespaceMap_["dc:"] = "http://purl.org/dc/elements/1.1/";

    XMP_VarString usedNS;
    XMP_VarString outputStr;

    DeclareElemNamespace("dc:title", usedNS, outputStr, "\n", "  ", 0);

    ASSERT_EQ(g_declareOneNamespaceCalls.size(), 1u);
    EXPECT_EQ(g_declareOneNamespaceCalls[0].nsPrefix, "dc:");
    EXPECT_EQ(g_declareOneNamespaceCalls[0].nsURI, "http://purl.org/dc/elements/1.1/");
}

// Test: Element name without a colon does not call DeclareOneNamespace
TEST_F(DeclareElemNamespaceTest_2105, NoPrefixDoesNothing_2105) {
    XMP_VarString usedNS;
    XMP_VarString outputStr;

    DeclareElemNamespace("title", usedNS, outputStr, "\n", "  ", 0);

    EXPECT_EQ(g_declareOneNamespaceCalls.size(), 0u);
    EXPECT_TRUE(usedNS.empty());
    EXPECT_TRUE(outputStr.empty());
}

// Test: Element name with unknown prefix throws XMP_Enforce failure
TEST_F(DeclareElemNamespaceTest_2105, UnknownPrefixThrowsEnforceFailure_2105) {
    // Don't add any prefix to the map
    XMP_VarString usedNS;
    XMP_VarString outputStr;

    EXPECT_THROW(
        DeclareElemNamespace("unknown:element", usedNS, outputStr, "\n", "  ", 0),
        XMP_Error
    );
}

// Test: Verify the XMP_Error has the correct ID for enforce failure
TEST_F(DeclareElemNamespaceTest_2105, UnknownPrefixThrowsCorrectErrorID_2105) {
    XMP_VarString usedNS;
    XMP_VarString outputStr;

    try {
        DeclareElemNamespace("bad:elem", usedNS, outputStr, "\n", "  ", 0);
        FAIL() << "Expected XMP_Error to be thrown";
    } catch (const XMP_Error& e) {
        EXPECT_EQ(e.GetID(), 7); // kXMPErr_EnforceFailure
    }
}

// Test: Empty element name does not call DeclareOneNamespace
TEST_F(DeclareElemNamespaceTest_2105, EmptyElemNameDoesNothing_2105) {
    XMP_VarString usedNS;
    XMP_VarString outputStr;

    DeclareElemNamespace("", usedNS, outputStr, "\n", "  ", 0);

    EXPECT_EQ(g_declareOneNamespaceCalls.size(), 0u);
}

// Test: Element name with colon at the beginning (prefix is just ":")
TEST_F(DeclareElemNamespaceTest_2105, ColonAtBeginningExtractsEmptyPrefix_2105) {
    // The prefix extracted would be ":" (substr(0, 0+1) = ":")
    namespaceMap_[":"] = "http://example.com/empty-prefix/";

    XMP_VarString usedNS;
    XMP_VarString outputStr;

    DeclareElemNamespace(":element", usedNS, outputStr, "\n", "  ", 0);

    ASSERT_EQ(g_declareOneNamespaceCalls.size(), 1u);
    EXPECT_EQ(g_declareOneNamespaceCalls[0].nsPrefix, ":");
    EXPECT_EQ(g_declareOneNamespaceCalls[0].nsURI, "http://example.com/empty-prefix/");
}

// Test: Element name with colon at the end
TEST_F(DeclareElemNamespaceTest_2105, ColonAtEndExtractsFullAsPrefix_2105) {
    namespaceMap_["element:"] = "http://example.com/full-as-prefix/";

    XMP_VarString usedNS;
    XMP_VarString outputStr;

    DeclareElemNamespace("element:", usedNS, outputStr, "\n", "  ", 0);

    ASSERT_EQ(g_declareOneNamespaceCalls.size(), 1u);
    EXPECT_EQ(g_declareOneNamespaceCalls[0].nsPrefix, "element:");
}

// Test: Multiple colons - only the first colon is used for prefix extraction
TEST_F(DeclareElemNamespaceTest_2105, MultipleColonsUsesFirstColon_2105) {
    namespaceMap_["ns:"] = "http://example.com/ns/";

    XMP_VarString usedNS;
    XMP_VarString outputStr;

    DeclareElemNamespace("ns:sub:element", usedNS, outputStr, "\n", "  ", 0);

    ASSERT_EQ(g_declareOneNamespaceCalls.size(), 1u);
    EXPECT_EQ(g_declareOneNamespaceCalls[0].nsPrefix, "ns:");
}

// Test: Correct parameters are forwarded to DeclareOneNamespace
TEST_F(DeclareElemNamespaceTest_2105, CorrectParametersForwarded_2105) {
    namespaceMap_["rdf:"] = "http://www.w3.org/1999/02/22-rdf-syntax-ns#";

    XMP_VarString usedNS = "existing:";
    XMP_VarString outputStr = "<existing/>";
    const char* newline = "\r\n";
    const char* indentStr = "\t";
    XMP_Index indent = 3;

    DeclareElemNamespace("rdf:Description", usedNS, outputStr, newline, indentStr, indent);

    ASSERT_EQ(g_declareOneNamespaceCalls.size(), 1u);
    EXPECT_EQ(g_declareOneNamespaceCalls[0].nsPrefix, "rdf:");
    EXPECT_EQ(g_declareOneNamespaceCalls[0].nsURI, "http://www.w3.org/1999/02/22-rdf-syntax-ns#");
    EXPECT_EQ(g_declareOneNamespaceCalls[0].newline, "\r\n");
    EXPECT_EQ(g_declareOneNamespaceCalls[0].indentStr, "\t");
    EXPECT_EQ(g_declareOneNamespaceCalls[0].indent, 3);
}

// Test: Different namespace prefixes work correctly
TEST_F(DeclareElemNamespaceTest_2105, DifferentNamespacePrefixes_2105) {
    namespaceMap_["xmp:"] = "http://ns.adobe.com/xap/1.0/";
    namespaceMap_["exif:"] = "http://ns.adobe.com/exif/1.0/";

    XMP_VarString usedNS;
    XMP_VarString outputStr;

    DeclareElemNamespace("xmp:CreateDate", usedNS, outputStr, "\n", "  ", 0);

    ASSERT_EQ(g_declareOneNamespaceCalls.size(), 1u);
    EXPECT_EQ(g_declareOneNamespaceCalls[0].nsPrefix, "xmp:");
    EXPECT_EQ(g_declareOneNamespaceCalls[0].nsURI, "http://ns.adobe.com/xap/1.0/");

    g_declareOneNamespaceCalls.clear();

    DeclareElemNamespace("exif:ExposureTime", usedNS, outputStr, "\n", "  ", 1);

    ASSERT_EQ(g_declareOneNamespaceCalls.size(), 1u);
    EXPECT_EQ(g_declareOneNamespaceCalls[0].nsPrefix, "exif:");
    EXPECT_EQ(g_declareOneNamespaceCalls[0].nsURI, "http://ns.adobe.com/exif/1.0/");
}

// Test: Indent value is correctly passed through
TEST_F(DeclareElemNamespaceTest_2105, IndentValuePassedCorrectly_2105) {
    namespaceMap_["dc:"] = "http://purl.org/dc/elements/1.1/";

    XMP_VarString usedNS;
    XMP_VarString outputStr;

    DeclareElemNamespace("dc:creator", usedNS, outputStr, "\n", "  ", 42);

    ASSERT_EQ(g_declareOneNamespaceCalls.size(), 1u);
    EXPECT_EQ(g_declareOneNamespaceCalls[0].indent, 42);
}

// Test: Single character prefix before colon
TEST_F(DeclareElemNamespaceTest_2105, SingleCharPrefix_2105) {
    namespaceMap_["x:"] = "http://example.com/x/";

    XMP_VarString usedNS;
    XMP_VarString outputStr;

    DeclareElemNamespace("x:element", usedNS, outputStr, "\n", "  ", 0);

    ASSERT_EQ(g_declareOneNamespaceCalls.size(), 1u);
    EXPECT_EQ(g_declareOneNamespaceCalls[0].nsPrefix, "x:");
    EXPECT_EQ(g_declareOneNamespaceCalls[0].nsURI, "http://example.com/x/");
}

// Test: Just a colon character as element name
TEST_F(DeclareElemNamespaceTest_2105, JustColonCharacter_2105) {
    namespaceMap_[":"] = "http://example.com/just-colon/";

    XMP_VarString usedNS;
    XMP_VarString outputStr;

    DeclareElemNamespace(":", usedNS, outputStr, "\n", "  ", 0);

    ASSERT_EQ(g_declareOneNamespaceCalls.size(), 1u);
    EXPECT_EQ(g_declareOneNamespaceCalls[0].nsPrefix, ":");
}

// Test: Negative indent value
TEST_F(DeclareElemNamespaceTest_2105, NegativeIndent_2105) {
    namespaceMap_["dc:"] = "http://purl.org/dc/elements/1.1/";

    XMP_VarString usedNS;
    XMP_VarString outputStr;

    DeclareElemNamespace("dc:title", usedNS, outputStr, "\n", "  ", -1);

    ASSERT_EQ(g_declareOneNamespaceCalls.size(), 1u);
    EXPECT_EQ(g_declareOneNamespaceCalls[0].indent, -1);
}
