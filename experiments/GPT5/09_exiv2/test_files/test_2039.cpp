// =================================================================================================
// UNIT TESTS for WXMPMeta_CountArrayItems_1
// TEST_ID = 2039
// =================================================================================================

#include <gtest/gtest.h>

#include <cstring>
#include <string>

// Project headers (expected to be available in the real codebase include paths).
#include "XMP_Const.h"
#include "XMPMeta.hpp"
#include "client-glue/WXMP_Common.hpp"

// If the real project already defines XMPMetaRef elsewhere, this typedef should be compatible.
// (In Adobe XMP SDK client glue, XMPMetaRef is typically a pointer-like handle.)
#ifndef __XMPMETA_REF_TYPEDEF_GUARD_2039__
#define __XMPMETA_REF_TYPEDEF_GUARD_2039__
using XMPMetaRef = void*;
#endif

// Function under test (implemented in WXMPMeta.cpp).
extern void WXMPMeta_CountArrayItems_1(
    XMPMetaRef xmpRef,
    XMP_StringPtr schemaNS,
    XMP_StringPtr arrayName,
    WXMP_Result* wResult);

// -------------------------------------------------------------------------------------------------
// Test fixture
// -------------------------------------------------------------------------------------------------
class WXMPMeta_CountArrayItems_1_Test_2039 : public ::testing::Test {
protected:
  static constexpr XMP_StringPtr kDublinCoreNS = "http://purl.org/dc/elements/1.1/";
  static constexpr XMP_StringPtr kArrayName    = "dc:subject";

  static XMPMetaRef AsRef(XMPMeta& meta) { return reinterpret_cast<XMPMetaRef>(&meta); }

  struct CallOutcome {
    bool threwXmpError = false;
    XMP_Int32 xmpErrId = 0;
    std::string xmpErrMsg;

    const char* wErrMessage = nullptr;
    XMP_Uns32 int32Result = 0;
  };

  static CallOutcome CallCountArrayItems(
      XMPMetaRef ref, XMP_StringPtr schemaNS, XMP_StringPtr arrayName) {
    WXMP_Result w;
    CallOutcome out;

    try {
      WXMPMeta_CountArrayItems_1(ref, schemaNS, arrayName, &w);
      out.wErrMessage = w.errMessage;
      out.int32Result = w.int32Result;
    } catch (const XMP_Error& e) {
      out.threwXmpError = true;
      out.xmpErrId = e.GetID();
      if (e.GetErrMsg() != nullptr) out.xmpErrMsg = e.GetErrMsg();
    } catch (...) {
      // If something else is thrown, treat it as an unexpected failure.
      ADD_FAILURE() << "Unexpected non-XMP_Error exception thrown.";
    }

    return out;
  }

  static void ParseXmp(XMPMeta& meta, const std::string& rdf) {
    // The SDK generally accepts 0 options for ParseFromBuffer.
    meta.ParseFromBuffer(rdf.c_str(), static_cast<XMP_StringLen>(rdf.size()), /*options*/ 0);
  }
};

// -------------------------------------------------------------------------------------------------
// Normal operation
// -------------------------------------------------------------------------------------------------

TEST_F(WXMPMeta_CountArrayItems_1_Test_2039, ReturnsZeroWhenArrayPresentButEmpty_2039) {
  XMPMeta meta;

  const std::string rdf =
      "<?xpacket begin=\"\xEF\xBB\xBF\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
      "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
      " <rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\""
      "          xmlns:dc=\"http://purl.org/dc/elements/1.1/\">"
      "  <rdf:Description rdf:about=\"\">"
      "   <dc:subject>"
      "    <rdf:Bag>"
      "    </rdf:Bag>"
      "   </dc:subject>"
      "  </rdf:Description>"
      " </rdf:RDF>"
      "</x:xmpmeta>"
      "<?xpacket end=\"w\"?>";

  ASSERT_NO_THROW(ParseXmp(meta, rdf));

  const auto out = CallCountArrayItems(AsRef(meta), kDublinCoreNS, kArrayName);

  ASSERT_FALSE(out.threwXmpError);
  EXPECT_TRUE(out.wErrMessage == nullptr || out.wErrMessage[0] == '\0');
  EXPECT_EQ(out.int32Result, 0u);
}

TEST_F(WXMPMeta_CountArrayItems_1_Test_2039, ReturnsCorrectCountForBagWithTwoItems_2039) {
  XMPMeta meta;

  const std::string rdf =
      "<?xpacket begin=\"\xEF\xBB\xBF\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
      "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
      " <rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\""
      "          xmlns:dc=\"http://purl.org/dc/elements/1.1/\">"
      "  <rdf:Description rdf:about=\"\">"
      "   <dc:subject>"
      "    <rdf:Bag>"
      "     <rdf:li>one</rdf:li>"
      "     <rdf:li>two</rdf:li>"
      "    </rdf:Bag>"
      "   </dc:subject>"
      "  </rdf:Description>"
      " </rdf:RDF>"
      "</x:xmpmeta>"
      "<?xpacket end=\"w\"?>";

  ASSERT_NO_THROW(ParseXmp(meta, rdf));

  const auto out = CallCountArrayItems(AsRef(meta), kDublinCoreNS, kArrayName);

  ASSERT_FALSE(out.threwXmpError);
  EXPECT_TRUE(out.wErrMessage == nullptr || out.wErrMessage[0] == '\0');
  EXPECT_EQ(out.int32Result, 2u);
}

// -------------------------------------------------------------------------------------------------
// Boundary conditions
// -------------------------------------------------------------------------------------------------

TEST_F(WXMPMeta_CountArrayItems_1_Test_2039, ReturnsZeroWhenArrayDoesNotExist_2039) {
  XMPMeta meta;

  // No dc:subject in the packet.
  const std::string rdf =
      "<?xpacket begin=\"\xEF\xBB\xBF\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
      "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
      " <rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\""
      "          xmlns:dc=\"http://purl.org/dc/elements/1.1/\">"
      "  <rdf:Description rdf:about=\"\">"
      "   <dc:title>t</dc:title>"
      "  </rdf:Description>"
      " </rdf:RDF>"
      "</x:xmpmeta>"
      "<?xpacket end=\"w\"?>";

  ASSERT_NO_THROW(ParseXmp(meta, rdf));

  const auto out = CallCountArrayItems(AsRef(meta), kDublinCoreNS, kArrayName);

  // For a missing array, CountArrayItems is expected to be observable as a count.
  // We only assert it doesn't error through the wrapper and returns 0.
  ASSERT_FALSE(out.threwXmpError);
  EXPECT_TRUE(out.wErrMessage == nullptr || out.wErrMessage[0] == '\0');
  EXPECT_EQ(out.int32Result, 0u);
}

// -------------------------------------------------------------------------------------------------
// Exceptional / error cases (observable via exception or WXMP_Result::errMessage)
// -------------------------------------------------------------------------------------------------

TEST_F(WXMPMeta_CountArrayItems_1_Test_2039, ErrorsOnNullSchemaNS_2039) {
  XMPMeta meta;

  const auto out = CallCountArrayItems(AsRef(meta), /*schemaNS*/ nullptr, kArrayName);

  if (out.threwXmpError) {
    EXPECT_EQ(out.xmpErrId, kXMPErr_BadSchema);
  } else {
    ASSERT_NE(out.wErrMessage, nullptr);
    EXPECT_NE(out.wErrMessage[0], '\0');
  }
}

TEST_F(WXMPMeta_CountArrayItems_1_Test_2039, ErrorsOnEmptySchemaNS_2039) {
  XMPMeta meta;

  const auto out = CallCountArrayItems(AsRef(meta), /*schemaNS*/ "", kArrayName);

  if (out.threwXmpError) {
    EXPECT_EQ(out.xmpErrId, kXMPErr_BadSchema);
  } else {
    ASSERT_NE(out.wErrMessage, nullptr);
    EXPECT_NE(out.wErrMessage[0], '\0');
  }
}

TEST_F(WXMPMeta_CountArrayItems_1_Test_2039, ErrorsOnNullArrayName_2039) {
  XMPMeta meta;

  const auto out = CallCountArrayItems(AsRef(meta), kDublinCoreNS, /*arrayName*/ nullptr);

  if (out.threwXmpError) {
    EXPECT_EQ(out.xmpErrId, kXMPErr_BadXPath);
  } else {
    ASSERT_NE(out.wErrMessage, nullptr);
    EXPECT_NE(out.wErrMessage[0], '\0');
  }
}

TEST_F(WXMPMeta_CountArrayItems_1_Test_2039, ErrorsOnEmptyArrayName_2039) {
  XMPMeta meta;

  const auto out = CallCountArrayItems(AsRef(meta), kDublinCoreNS, /*arrayName*/ "");

  if (out.threwXmpError) {
    EXPECT_EQ(out.xmpErrId, kXMPErr_BadXPath);
  } else {
    ASSERT_NE(out.wErrMessage, nullptr);
    EXPECT_NE(out.wErrMessage[0], '\0');
  }
}