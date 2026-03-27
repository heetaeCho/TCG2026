// =================================================================================================
// TEST_ID: 2114
// Unit tests for SerializeCompactRDFSchemas (XMPMeta-Serialize.cpp)
// =================================================================================================

#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <vector>

// Pull in core types (XMP_Node, XMP_VarString, XMP_StringPtr, XMP_Index, XMP_StringMap, option bits).
// These headers exist in the XMP SDK codebase under exiv2/xmpsdk/src.
#include "XMPCore_Impl.hpp"
#include "XMP_Const.h"

// -----------------------------------------------------------------------------------------------
// Include the implementation file directly so we can call the internal-linkage (static) function.
// This is a common pattern for unit testing file-local helpers without changing production code.
// -----------------------------------------------------------------------------------------------
#include "XMPMeta-Serialize.cpp"

// Some builds keep these in the global namespace; ensure we see the externs.
extern XMP_StringMap* sNamespacePrefixToURIMap;
extern const char* kRDF_SchemaStart;
extern const char* kRDF_SchemaEnd;

namespace {

class NamespaceMapGuard {
public:
  NamespaceMapGuard() : old_(sNamespacePrefixToURIMap) {
    owned_ = std::make_unique<XMP_StringMap>();
    sNamespacePrefixToURIMap = owned_.get();
  }

  explicit NamespaceMapGuard(std::initializer_list<std::pair<const char*, const char*>> init)
      : old_(sNamespacePrefixToURIMap) {
    owned_ = std::make_unique<XMP_StringMap>();
    for (const auto& kv : init) {
      (*owned_)[kv.first] = kv.second;
    }
    sNamespacePrefixToURIMap = owned_.get();
  }

  ~NamespaceMapGuard() { sNamespacePrefixToURIMap = old_; }

  XMP_StringMap& map() { return *owned_; }

private:
  XMP_StringMap* old_ = nullptr;
  std::unique_ptr<XMP_StringMap> owned_;
};

// Simple helper to build repeated indentation.
static std::string Repeat(const char* s, int count) {
  std::string out;
  for (int i = 0; i < count; ++i) out += s;
  return out;
}

class SerializeCompactRDFSchemasTest_2114 : public ::testing::Test {
protected:
  // Keep nodes alive for the duration of the test.
  std::vector<std::unique_ptr<XMP_Node>> nodes_;

  XMP_Node* NewNode(XMP_Node* parent, const char* name, XMP_OptionBits options = 0) {
    nodes_.push_back(std::make_unique<XMP_Node>(parent, name, options));
    return nodes_.back().get();
  }

  XMP_Node* NewNodeWithValue(XMP_Node* parent, const char* name, const char* value,
                             XMP_OptionBits options = 0) {
    nodes_.push_back(std::make_unique<XMP_Node>(parent, name, value, options));
    return nodes_.back().get();
  }
};

}  // namespace

// -------------------------------------------------------------------------------------------------
// Normal / boundary: xmpTree has NO schema children => loops are skipped and it must self-close.
// This is fully observable and does not depend on internal decisions of sub-serializers.
// -------------------------------------------------------------------------------------------------
TEST_F(SerializeCompactRDFSchemasTest_2114, EmptyChildren_SelfClosesAndContainsAbout_2114) {
  NamespaceMapGuard nsGuard({{"rdf", "http://www.w3.org/1999/02/22-rdf-syntax-ns#"}});

  XMP_Node xmpTree(/*parent*/ nullptr, "uuid:doc-2114", /*options*/ 0);

  XMP_VarString out;
  const char* newline = "\n";
  const char* indent = "  ";
  XMP_Index baseIndent = 0;

  SerializeCompactRDFSchemas(xmpTree, out, newline, indent, baseIndent);

  const std::string expectedPrefix = Repeat(indent, static_cast<int>(baseIndent + 2));
  ASSERT_GE(out.size(), expectedPrefix.size());
  EXPECT_EQ(out.substr(0, expectedPrefix.size()), expectedPrefix);

  // Must contain start tag and the rdf:about value (quoted tree name).
  EXPECT_NE(out.find(kRDF_SchemaStart), std::string::npos);
  EXPECT_NE(out.find("\"uuid:doc-2114\""), std::string::npos);

  // With no schemas, allAreAttrs stays true and it returns with "/>" + newline.
  EXPECT_TRUE(out.size() >= 3);
  EXPECT_EQ(out.substr(out.size() - 3), std::string("/>\n"));
  // Must not contain the end tag because it returns early in self-closed case.
  EXPECT_EQ(out.find(kRDF_SchemaEnd), std::string::npos);
}

// -------------------------------------------------------------------------------------------------
// Normal: xmpTree has a schema child. We avoid asserting the full string (namespaces/attrs are
// declared by other helpers), but we do assert stable externally visible structure.
// -------------------------------------------------------------------------------------------------
TEST_F(SerializeCompactRDFSchemasTest_2114, OneEmptySchemaChild_StillEmitsDescriptionStart_2114) {
  NamespaceMapGuard nsGuard({
      {"rdf", "http://www.w3.org/1999/02/22-rdf-syntax-ns#"},
      {"dc", "http://purl.org/dc/elements/1.1/"},
  });

  XMP_Node xmpTree(/*parent*/ nullptr, "about:one-schema-2114", /*options*/ 0);

  // Add one schema node (no properties under it).
  XMP_Node* schema = NewNode(&xmpTree, "http://example.com/ns/schema1/", /*options*/ 0);
  xmpTree.children.push_back(schema);

  XMP_VarString out;
  const char* newline = "\n";
  const char* indent = " ";
  XMP_Index baseIndent = 1;

  SerializeCompactRDFSchemas(xmpTree, out, newline, indent, baseIndent);

  const std::string expectedPrefix = Repeat(indent, static_cast<int>(baseIndent + 2));
  ASSERT_GE(out.size(), expectedPrefix.size());
  EXPECT_EQ(out.substr(0, expectedPrefix.size()), expectedPrefix);

  EXPECT_NE(out.find(kRDF_SchemaStart), std::string::npos);
  EXPECT_NE(out.find("\"about:one-schema-2114\""), std::string::npos);

  // The function must end with a newline in both branches.
  ASSERT_FALSE(out.empty());
  EXPECT_EQ(out.back(), '\n');
}

// -------------------------------------------------------------------------------------------------
// Error/exceptional (observable): Ensure the function does not crash when the namespace map is empty
// but valid (non-null). This is a robustness boundary case.
// -------------------------------------------------------------------------------------------------
TEST_F(SerializeCompactRDFSchemasTest_2114, EmptyNamespaceMapPointerNonNull_DoesNotCrash_2114) {
  NamespaceMapGuard nsGuard;  // installs a valid, empty map

  XMP_Node xmpTree(/*parent*/ nullptr, "about:empty-ns-map-2114", /*options*/ 0);

  XMP_VarString out;
  const char* newline = "\r\n";
  const char* indent = "\t";
  XMP_Index baseIndent = 0;

  // Observable: should produce some output and end in newline.
  SerializeCompactRDFSchemas(xmpTree, out, newline, indent, baseIndent);

  EXPECT_NE(out.find(kRDF_SchemaStart), std::string::npos);
  EXPECT_NE(out.find("\"about:empty-ns-map-2114\""), std::string::npos);
  ASSERT_GE(out.size(), 2u);
  EXPECT_EQ(out.substr(out.size() - 2), std::string("\r\n"));
}

// -------------------------------------------------------------------------------------------------
// Boundary: verify indentation behavior at a larger baseIndent for the START tag.
// We only assert the deterministic leading indentation and presence of core tag content.
// -------------------------------------------------------------------------------------------------
TEST_F(SerializeCompactRDFSchemasTest_2114, LargerBaseIndent_StartTagHasExpectedIndentation_2114) {
  NamespaceMapGuard nsGuard({{"rdf", "http://www.w3.org/1999/02/22-rdf-syntax-ns#"}});

  XMP_Node xmpTree(/*parent*/ nullptr, "about:indent-2114", /*options*/ 0);

  XMP_VarString out;
  const char* newline = "\n";
  const char* indent = "....";
  XMP_Index baseIndent = 3;

  SerializeCompactRDFSchemas(xmpTree, out, newline, indent, baseIndent);

  const std::string expectedPrefix = Repeat(indent, static_cast<int>(baseIndent + 2));
  ASSERT_GE(out.size(), expectedPrefix.size());
  EXPECT_EQ(out.substr(0, expectedPrefix.size()), expectedPrefix);

  EXPECT_NE(out.find(kRDF_SchemaStart), std::string::npos);
  EXPECT_NE(out.find("\"about:indent-2114\""), std::string::npos);
}

// -------------------------------------------------------------------------------------------------
// Normal + branch coverage attempt (best-effort, black-box):
// Create a schema with a child property that is commonly serialized as an element (arrays/structs),
// which typically forces non-attribute serialization. We don't assume exact formatting; we only
// assert that if it is not self-closed, the end tag appears.
// If it *is* self-closed in this build, the test still checks output consistency.
// -------------------------------------------------------------------------------------------------
TEST_F(SerializeCompactRDFSchemasTest_2114, ComplexProperty_MayRequireEndTagOrSelfCloseButIsConsistent_2114) {
  NamespaceMapGuard nsGuard({
      {"rdf", "http://www.w3.org/1999/02/22-rdf-syntax-ns#"},
      {"ex", "http://example.com/ns/ex/"},
  });

  XMP_Node xmpTree(/*parent*/ nullptr, "about:complex-2114", /*options*/ 0);

  XMP_Node* schema = NewNode(&xmpTree, "http://example.com/ns/ex/", /*options*/ 0);
  xmpTree.children.push_back(schema);

  // Add a property that is likely not representable as an attribute (array).
  // (We do not depend on specific internal logic; we only observe produced output.)
  XMP_Node* prop = NewNode(schema, "ex:ArrayProp", kXMP_PropValueIsArray);
  schema->children.push_back(prop);

  // Add an array item to make it non-empty.
  XMP_Node* item = NewNodeWithValue(prop, "[]", "v1", /*options*/ 0);
  prop->children.push_back(item);

  XMP_VarString out;
  const char* newline = "\n";
  const char* indent = "  ";
  XMP_Index baseIndent = 0;

  SerializeCompactRDFSchemas(xmpTree, out, newline, indent, baseIndent);

  EXPECT_NE(out.find(kRDF_SchemaStart), std::string::npos);
  EXPECT_NE(out.find("\"about:complex-2114\""), std::string::npos);
  ASSERT_FALSE(out.empty());
  EXPECT_EQ(out.back(), '\n');

  const bool isSelfClosed = (out.size() >= 3) && (out.substr(out.size() - 3) == "/>\n");
  if (!isSelfClosed) {
    // If not self-closed, it must contain an explicit end tag at the outer level.
    EXPECT_NE(out.find(kRDF_SchemaEnd), std::string::npos);
  }
}