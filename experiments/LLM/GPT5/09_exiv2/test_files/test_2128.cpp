// =================================================================================================
// TEST_ID: 2128
// Unit tests for RDF_NodeElementAttrs (ParseRDF.cpp)
// =================================================================================================

#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <vector>

#if __has_include("XMP.hpp")
#include "XMP.hpp" // May define XMP_Error, XMP_Throw, etc.
#endif
#if __has_include("XMP_Const.h")
#include "XMP_Const.h"
#endif

// Pull in the real implementation so we can call the TU-local static function.
// This keeps the implementation as a black box (we do not re-implement it),
// while still allowing direct unit testing of this internal helper.
#include "TestProjects/exiv2/xmpsdk/src/ParseRDF.cpp"

#include "TestProjects/exiv2/xmpsdk/src/XMPCore_Impl.hpp"
#include "TestProjects/exiv2/xmpsdk/src/XMLParserAdapter.hpp"

namespace {

// --- Small helpers (only building inputs / observing public fields) ---

static XML_NodePtr MakeAttr(XML_NodePtr parent, const std::string& name, const std::string& value) {
  XML_NodePtr attr = std::make_shared<XML_Node>(parent, name, /*kind*/ 0);
  attr->name = name;
  attr->value = value;
  return attr;
}

static XML_Node MakeElemWithAttrs(const std::vector<std::pair<std::string, std::string>>& attrs) {
  XML_Node elem(/*parent*/ XML_NodePtr(), "rdf:Description", /*kind*/ 0);
  elem.name = "rdf:Description";
  elem.value.clear();
  elem.attrs.clear();
  for (const auto& kv : attrs) {
    elem.attrs.push_back(MakeAttr(/*parent*/ XML_NodePtr(), kv.first, kv.second));
  }
  return elem;
}

// If XMP_Error is available, try to read its ID (error code) for stronger assertions.
template <typename E>
static int TryGetXmpErrId(const E& e) {
  // Default: unknown/unavailable
  (void)e;
  return -1;
}

#if defined(XMP_Error) || __has_include("XMP.hpp")
static int TryGetXmpErrId(const XMP_Error& e) { return e.GetID(); }
#endif

class RDF_NodeElementAttrsTest_2128 : public ::testing::Test {
 protected:
  RDF_NodeElementAttrsTest_2128() = default;

  static XMP_Node MakeRoot() {
    // Root node must have parent == 0 (see assertion in the code when top-level rdf:about is used).
    XMP_Node root(/*parent*/ nullptr, /*name*/ "", /*options*/ 0);
    return root;
  }
};

}  // namespace

// -------------------------------------------------------------------------------------------------
// Normal operation
// -------------------------------------------------------------------------------------------------

TEST_F(RDF_NodeElementAttrsTest_2128, TopLevelAboutSetsEmptyRootName_2128) {
  XMP_Node root = MakeRoot();

  XML_Node elem = MakeElemWithAttrs({
      {"rdf:about", "uuid:root-subject"},
  });

  EXPECT_NO_THROW(RDF_NodeElementAttrs(&root, elem, /*isTopLevel*/ true));
  EXPECT_EQ(root.name, "uuid:root-subject");
}

TEST_F(RDF_NodeElementAttrsTest_2128, TopLevelAboutMatchesExistingRootName_NoThrow_2128) {
  XMP_Node root = MakeRoot();
  root.name = "uuid:same";

  XML_Node elem = MakeElemWithAttrs({
      {"rdf:about", "uuid:same"},
  });

  EXPECT_NO_THROW(RDF_NodeElementAttrs(&root, elem, /*isTopLevel*/ true));
  EXPECT_EQ(root.name, "uuid:same");
}

TEST_F(RDF_NodeElementAttrsTest_2128, TopLevelAboutWithEmptyValueDoesNotForceMismatch_2128) {
  XMP_Node root = MakeRoot();
  root.name = "uuid:existing";

  XML_Node elem = MakeElemWithAttrs({
      {"rdf:about", ""},  // Empty should not trigger mismatch throw per observable behavior.
  });

  EXPECT_NO_THROW(RDF_NodeElementAttrs(&root, elem, /*isTopLevel*/ true));
  EXPECT_EQ(root.name, "uuid:existing");
}

// -------------------------------------------------------------------------------------------------
// Boundary / interaction-ish behavior
// -------------------------------------------------------------------------------------------------

TEST_F(RDF_NodeElementAttrsTest_2128, NonRdfAttributeAddsChildNodeOrEquivalent_2128) {
  XMP_Node root = MakeRoot();
  const size_t beforeChildren = root.children.size();
  const size_t beforeQualifiers = root.qualifiers.size();

  // Attribute not expected to be an RDF core attribute; should be treated as "Other".
  XML_Node elem = MakeElemWithAttrs({
      {"ex:customAttr", "customValue"},
  });

  EXPECT_NO_THROW(RDF_NodeElementAttrs(&root, elem, /*isTopLevel*/ true));

  // We don't assume exact internal structure of AddChildNode; we only check that some visible
  // offspring changed (children and/or qualifiers are public on XMP_Node).
  const bool changed = (root.children.size() != beforeChildren) || (root.qualifiers.size() != beforeQualifiers);
  EXPECT_TRUE(changed);
}

// -------------------------------------------------------------------------------------------------
// Exceptional / error cases (observable through throws)
// -------------------------------------------------------------------------------------------------

TEST_F(RDF_NodeElementAttrsTest_2128, TopLevelAboutMismatchThrows_2128) {
  XMP_Node root = MakeRoot();
  root.name = "uuid:one";

  XML_Node elem = MakeElemWithAttrs({
      {"rdf:about", "uuid:two"},
  });

  try {
    RDF_NodeElementAttrs(&root, elem, /*isTopLevel*/ true);
    FAIL() << "Expected an exception for mismatched top level rdf:about values";
  } catch (
#if defined(XMP_Error) || __has_include("XMP.hpp")
      const XMP_Error& e
#else
      const std::exception& e
#endif
  ) {
#if defined(XMP_Error) || __has_include("XMP.hpp")
    EXPECT_EQ(TryGetXmpErrId(e), kXMPErr_BadXMP);
#else
    (void)e;  // Best-effort if XMP_Error isn't visible in this build.
#endif
  } catch (...) {
    SUCCEED() << "Caught a non-std exception type (acceptable if XMP_Throw uses custom types)";
  }
}

TEST_F(RDF_NodeElementAttrsTest_2128, MutuallyExclusiveAboutAndIdThrowsBadRdf_2128) {
  XMP_Node root = MakeRoot();

  XML_Node elem = MakeElemWithAttrs({
      {"rdf:about", "uuid:root"},
      {"rdf:ID", "someId"},
  });

  try {
    RDF_NodeElementAttrs(&root, elem, /*isTopLevel*/ true);
    FAIL() << "Expected an exception for mutually exclusive rdf:about and rdf:ID attributes";
  } catch (
#if defined(XMP_Error) || __has_include("XMP.hpp")
      const XMP_Error& e
#else
      const std::exception& e
#endif
  ) {
#if defined(XMP_Error) || __has_include("XMP.hpp")
    EXPECT_EQ(TryGetXmpErrId(e), kXMPErr_BadRDF);
#else
    (void)e;
#endif
  } catch (...) {
    SUCCEED() << "Caught a non-std exception type (acceptable if XMP_Throw uses custom types)";
  }
}

TEST_F(RDF_NodeElementAttrsTest_2128, MutuallyExclusiveNodeIdAndIdThrowsBadRdf_2128) {
  XMP_Node root = MakeRoot();

  XML_Node elem = MakeElemWithAttrs({
      {"rdf:nodeID", "n1"},
      {"rdf:ID", "id1"},
  });

  try {
    RDF_NodeElementAttrs(&root, elem, /*isTopLevel*/ false);
    FAIL() << "Expected an exception for mutually exclusive rdf:nodeID and rdf:ID attributes";
  } catch (
#if defined(XMP_Error) || __has_include("XMP.hpp")
      const XMP_Error& e
#else
      const std::exception& e
#endif
  ) {
#if defined(XMP_Error) || __has_include("XMP.hpp")
    EXPECT_EQ(TryGetXmpErrId(e), kXMPErr_BadRDF);
#else
    (void)e;
#endif
  } catch (...) {
    SUCCEED();
  }
}

TEST_F(RDF_NodeElementAttrsTest_2128, InvalidNodeElementAttributeThrowsBadRdf_2128) {
  XMP_Node root = MakeRoot();

  // A known RDF attribute that is typically not valid for node element attrs in this context.
  // We don't assume exact mapping beyond the observable behavior that some attributes are invalid here.
  XML_Node elem = MakeElemWithAttrs({
      {"rdf:parseType", "Resource"},
  });

  try {
    RDF_NodeElementAttrs(&root, elem, /*isTopLevel*/ false);
    FAIL() << "Expected an exception for an invalid nodeElement attribute";
  } catch (
#if defined(XMP_Error) || __has_include("XMP.hpp")
      const XMP_Error& e
#else
      const std::exception& e
#endif
  ) {
#if defined(XMP_Error) || __has_include("XMP.hpp")
    EXPECT_EQ(TryGetXmpErrId(e), kXMPErr_BadRDF);
#else
    (void)e;
#endif
  } catch (...) {
    SUCCEED();
  }
}