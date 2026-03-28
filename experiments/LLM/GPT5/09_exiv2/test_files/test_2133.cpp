// ============================================================================
// TEST_ID: 2133
// Unit tests for RDF_ParseTypeLiteralPropertyElement
// File: ./TestProjects/exiv2/xmpsdk/src/ParseRDF.cpp
// ============================================================================

#include <gtest/gtest.h>

#include <string>
#include <type_traits>
#include <utility>

// Pull in concrete types used by the function signature.
#include "./TestProjects/exiv2/xmpsdk/src/XMPCore_Impl.hpp"
#include "./TestProjects/exiv2/xmpsdk/src/XMLParserAdapter.hpp"
#include "XMP_Const.h"

// NOTE:
// RDF_ParseTypeLiteralPropertyElement is declared "static" in ParseRDF.cpp,
// so it has internal linkage. To test it directly, we include the .cpp here.
// This is a common unit-testing technique for internal-linkage helpers.
#include "./TestProjects/exiv2/xmpsdk/src/ParseRDF.cpp"

namespace {

// ---- Introspection helpers to verify exception details only if observable. ----

template <typename T, typename = void>
struct HasGetID : std::false_type {};
template <typename T>
struct HasGetID<T, decltype((void)std::declval<const T&>().GetID(), void())> : std::true_type {};

template <typename T, typename = void>
struct HasGetErrMsg : std::false_type {};
template <typename T>
struct HasGetErrMsg<T, decltype((void)std::declval<const T&>().GetErrMsg(), void())> : std::true_type {};

template <typename T, typename = void>
struct HasGetErrorMsg : std::false_type {};
template <typename T>
struct HasGetErrorMsg<T, decltype((void)std::declval<const T&>().GetErrorMsg(), void())> : std::true_type {};

template <typename T, typename = void>
struct HasWhat : std::false_type {};
template <typename T>
struct HasWhat<T, decltype((void)std::declval<const T&>().what(), void())> : std::true_type {};

template <typename XmpErrT>
static void VerifyXmpErrorDetailsIfPossible(const XmpErrT& err) {
  // Verify error ID if the exception exposes it.
  if constexpr (HasGetID<XmpErrT>::value) {
    EXPECT_EQ(err.GetID(), kXMPErr_BadXMP);
  }

  // Verify message if the exception exposes it (any of common accessors).
  auto contains_expected = [](const std::string& msg) {
    return msg.find("ParseTypeLiteral property element not allowed") != std::string::npos;
  };

  if constexpr (HasGetErrMsg<XmpErrT>::value) {
    EXPECT_TRUE(contains_expected(err.GetErrMsg()));
  } else if constexpr (HasGetErrorMsg<XmpErrT>::value) {
    EXPECT_TRUE(contains_expected(err.GetErrorMsg()));
  } else if constexpr (HasWhat<XmpErrT>::value) {
    // If it derives from std::exception, at least check what().
    EXPECT_TRUE(contains_expected(err.what()));
  }
}

// Minimal helper to build a non-null XMP_Node without assuming anything else.
static XMP_Node MakeXmpNode(XMP_Node* parent, const char* name) {
  // Options are opaque here; use 0 (default-ish) as a black-box friendly value.
  return XMP_Node(parent, name, static_cast<XMP_OptionBits>(0));
}

// Minimal helper to build an XML_Node instance.
static XML_Node MakeXmlNode(XML_NodePtr parent, const char* name, XMP_Uns8 kind) {
  return XML_Node(parent, name, kind);
}

class ParseTypeLiteralPropertyElementTest_2133 : public ::testing::Test {};

TEST_F(ParseTypeLiteralPropertyElementTest_2133, ThrowsForTypicalInputs_2133) {
  XMP_Node xmpParent = MakeXmpNode(/*parent*/ nullptr, "parent");
  XML_Node xmlNode = MakeXmlNode(/*parent*/ XML_NodePtr(), "node", /*kind*/ 1);

  try {
    RDF_ParseTypeLiteralPropertyElement(&xmpParent, xmlNode, /*isTopLevel*/ true);
    FAIL() << "Expected an exception to be thrown.";
  } catch (const XMP_Error& e) {
    VerifyXmpErrorDetailsIfPossible(e);
  } catch (...) {
    FAIL() << "Expected XMP_Error (or compatible XMP exception type) to be thrown.";
  }
}

TEST_F(ParseTypeLiteralPropertyElementTest_2133, ThrowsWhenParentIsNull_2133) {
  XML_Node xmlNode = MakeXmlNode(/*parent*/ XML_NodePtr(), "node", /*kind*/ 1);

  try {
    RDF_ParseTypeLiteralPropertyElement(/*xmpParent*/ nullptr, xmlNode, /*isTopLevel*/ true);
    FAIL() << "Expected an exception to be thrown.";
  } catch (const XMP_Error& e) {
    VerifyXmpErrorDetailsIfPossible(e);
  } catch (...) {
    FAIL() << "Expected XMP_Error (or compatible XMP exception type) to be thrown.";
  }
}

TEST_F(ParseTypeLiteralPropertyElementTest_2133, ThrowsWhenIsTopLevelFalse_2133) {
  XMP_Node xmpParent = MakeXmpNode(/*parent*/ nullptr, "parent");
  XML_Node xmlNode = MakeXmlNode(/*parent*/ XML_NodePtr(), "node", /*kind*/ 1);

  try {
    RDF_ParseTypeLiteralPropertyElement(&xmpParent, xmlNode, /*isTopLevel*/ false);
    FAIL() << "Expected an exception to be thrown.";
  } catch (const XMP_Error& e) {
    VerifyXmpErrorDetailsIfPossible(e);
  } catch (...) {
    FAIL() << "Expected XMP_Error (or compatible XMP exception type) to be thrown.";
  }
}

TEST_F(ParseTypeLiteralPropertyElementTest_2133, ThrowsForDifferentXmlKinds_2133) {
  XMP_Node xmpParent = MakeXmpNode(/*parent*/ nullptr, "parent");

  // Boundary-ish coverage: try a couple of distinct kind values.
  for (XMP_Uns8 kind : {static_cast<XMP_Uns8>(0), static_cast<XMP_Uns8>(255)}) {
    XML_Node xmlNode = MakeXmlNode(/*parent*/ XML_NodePtr(), "node", kind);

    try {
      RDF_ParseTypeLiteralPropertyElement(&xmpParent, xmlNode, /*isTopLevel*/ true);
      FAIL() << "Expected an exception to be thrown for kind=" << static_cast<int>(kind);
    } catch (const XMP_Error& e) {
      VerifyXmpErrorDetailsIfPossible(e);
    } catch (...) {
      FAIL() << "Expected XMP_Error (or compatible XMP exception type) for kind="
             << static_cast<int>(kind);
    }
  }
}

}  // namespace