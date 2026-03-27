// ============================================================================
// Test file for ./TestProjects/exiv2/xmpsdk/src/ParseRDF.cpp
// Target: static void RDF_ParseTypeOtherPropertyElement(...)
// TEST_ID: 2136
// ============================================================================

#include <gtest/gtest.h>

#include <string>
#include <type_traits>

// Include the implementation file so the internal-linkage (static) function is
// visible in this translation unit. This follows the black-box rule: we are not
// re-implementing logic; we are invoking the real code.
#include "TestProjects/exiv2/xmpsdk/src/ParseRDF.cpp"

// ---- Optional exception-introspection helpers (compile-time detected) ----
namespace {

template <typename E, typename = void>
struct HasGetID : std::false_type {};
template <typename E>
struct HasGetID<E, std::void_t<decltype(std::declval<const E&>().GetID())>> : std::true_type {};

template <typename E, typename = void>
struct HasIdMember : std::false_type {};
template <typename E>
struct HasIdMember<E, std::void_t<decltype(std::declval<const E&>().id)>> : std::true_type {};

template <typename E, typename = void>
struct HasGetErrMsg : std::false_type {};
template <typename E>
struct HasGetErrMsg<E, std::void_t<decltype(std::declval<const E&>().GetErrMsg())>> : std::true_type {};

template <typename E, typename = void>
struct HasErrMsgMember : std::false_type {};
template <typename E>
struct HasErrMsgMember<E, std::void_t<decltype(std::declval<const E&>().errMsg)>> : std::true_type {};

template <typename E>
static int GetXmpErrIdIfPossible(const E& e) {
  if constexpr (HasGetID<E>::value) {
    return static_cast<int>(e.GetID());
  } else if constexpr (HasIdMember<E>::value) {
    return static_cast<int>(e.id);
  } else {
    return -1;  // Unknown / not accessible
  }
}

template <typename E>
static std::string GetXmpErrMsgIfPossible(const E& e) {
  if constexpr (HasGetErrMsg<E>::value) {
    return std::string(e.GetErrMsg());
  } else if constexpr (HasErrMsgMember<E>::value) {
    return std::string(e.errMsg.c_str());
  } else {
    return std::string();  // Unknown / not accessible
  }
}

}  // namespace

// ----------------------------------------------------------------------------

class RDF_ParseTypeOtherPropertyElementTest_2136 : public ::testing::Test {};

TEST_F(RDF_ParseTypeOtherPropertyElementTest_2136, ThrowsForTypicalInputs_2136) {
  // Arrange: Create typical objects where possible. The function is specified
  // to take an XMP_Node* and an XML_Node&, so we provide valid instances.
  XMP_Node parent(/*_parent*/ nullptr, /*_name*/ "p", /*_options*/ 0);
  XML_Node xml(/*_parent*/ XML_NodePtr(), /*_name*/ "rdf:Description", /*_kind*/ 0);

  // Act / Assert: Must throw (observable error case).
  // We do not assume the exact exception type beyond what the SDK exposes.
  EXPECT_ANY_THROW(RDF_ParseTypeOtherPropertyElement(&parent, xml, /*isTopLevel*/ true));
}

TEST_F(RDF_ParseTypeOtherPropertyElementTest_2136, ThrowsWhenParentIsNull_2136) {
  // Boundary: xmpParent is a pointer; passing nullptr is a reasonable boundary.
  XML_Node xml(/*_parent*/ XML_NodePtr(), /*_name*/ "rdf:Description", /*_kind*/ 0);

  EXPECT_ANY_THROW(RDF_ParseTypeOtherPropertyElement(nullptr, xml, /*isTopLevel*/ false));
}

TEST_F(RDF_ParseTypeOtherPropertyElementTest_2136, ThrowsRegardlessOfIsTopLevelFlag_2136) {
  XMP_Node parent(/*_parent*/ nullptr, /*_name*/ "p", /*_options*/ 0);
  XML_Node xml(/*_parent*/ XML_NodePtr(), /*_name*/ "rdf:Description", /*_kind*/ 0);

  EXPECT_ANY_THROW(RDF_ParseTypeOtherPropertyElement(&parent, xml, /*isTopLevel*/ true));
  EXPECT_ANY_THROW(RDF_ParseTypeOtherPropertyElement(&parent, xml, /*isTopLevel*/ false));
}

TEST_F(RDF_ParseTypeOtherPropertyElementTest_2136, ThrowsForOddXmlNodeValues_2136) {
  // Boundary-ish: unusual kind and empty name/value.
  XMP_Node parent(/*_parent*/ nullptr, /*_name*/ "", /*_options*/ 0);

  XML_Node xmlEmptyName(/*_parent*/ XML_NodePtr(), /*_name*/ "", /*_kind*/ 0xFF);
  xmlEmptyName.SetLeafContentValue("");

  EXPECT_ANY_THROW(RDF_ParseTypeOtherPropertyElement(&parent, xmlEmptyName, /*isTopLevel*/ true));
}

TEST_F(RDF_ParseTypeOtherPropertyElementTest_2136, IfXmpErrorExposedThenIdAndMessageMatchBadXmp_2136) {
  // This test verifies *observable* details of the thrown exception IF the SDK
  // exposes them (ID/message). If not exposed, the test still checks that an
  // exception is thrown, without peeking into private state.
  XMP_Node parent(/*_parent*/ nullptr, /*_name*/ "p", /*_options*/ 0);
  XML_Node xml(/*_parent*/ XML_NodePtr(), /*_name*/ "anything", /*_kind*/ 0);

  try {
    RDF_ParseTypeOtherPropertyElement(&parent, xml, /*isTopLevel*/ true);
    FAIL() << "Expected an exception to be thrown.";
  } catch (const std::exception& e) {
    // If the toolkit throws std::exception-derived types, that's still an
    // observable error path. We can't reliably get XMP error id here.
    (void)e;
    SUCCEED();
  } catch (...) {
    // Try to catch XMP_Error-like objects with id/message if available via
    // the compilation unit (ParseRDF.cpp includes the SDK headers).
    // Re-throw and catch by deduced type is not possible; instead, we do a
    // second try-block with a typed catch if XMP_Error is known.
    SUCCEED();
  }

  // Typed catch path: if XMP_Error exists in this build, validate its payload.
#ifdef XMP_Error
  // (This macro likely won't exist; keep the test robust.)
#endif

  // If the symbol XMP_Error is a type (typical in XMP SDK), this will compile;
  // otherwise the following block is excluded via SFINAE-like trick by putting
  // it in an unevaluated context would be messy. So instead we provide a second
  // try/catch guarded by a simple "is type" probe.
  struct XmpErrorProbe {
    template <typename T>
    static auto Test(int) -> decltype(sizeof(T), std::true_type{});
    template <typename>
    static auto Test(...) -> std::false_type;
  };

  constexpr bool hasXmpErrorType =
      decltype(XmpErrorProbe::Test<XMP_Error>(0))::value;

  if constexpr (hasXmpErrorType) {
    try {
      RDF_ParseTypeOtherPropertyElement(&parent, xml, /*isTopLevel*/ true);
      FAIL() << "Expected an exception to be thrown.";
    } catch (const XMP_Error& xe) {
      const int id = GetXmpErrIdIfPossible(xe);
      if (id != -1) {
        EXPECT_EQ(id, static_cast<int>(kXMPErr_BadXMP));
      }

      const std::string msg = GetXmpErrMsgIfPossible(xe);
      if (!msg.empty()) {
        EXPECT_NE(msg.find("ParseTypeOther"), std::string::npos);
      }
    } catch (...) {
      // If it isn't XMP_Error in this build, we already verified it throws above.
      SUCCEED();
    }
  }
}