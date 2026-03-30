// =================================================================================================
// TEST_ID: 2045
// Unit tests for WXMPMeta_ParseFromBuffer_1
// =================================================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <cstring>
#include <string>

#if __has_include("client-glue/WXMP_Common.hpp")
  #include "client-glue/WXMP_Common.hpp"
#elif __has_include("WXMP_Common.hpp")
  #include "WXMP_Common.hpp"
#else
  // If your build system does not expose the header path, add it to include dirs.
  #error "Cannot find WXMP_Common.hpp (needed for WXMP_Result)."
#endif

#if __has_include("XMP_Const.h")
  #include "XMP_Const.h"
#elif __has_include("xmpsdk/include/XMP_Const.h")
  #include "xmpsdk/include/XMP_Const.h"
#else
  #error "Cannot find XMP_Const.h (needed for XMP types)."
#endif

#if __has_include("XMPMeta.hpp")
  #include "XMPMeta.hpp"
#elif __has_include("xmpsdk/src/XMPMeta.hpp")
  #include "xmpsdk/src/XMPMeta.hpp"
#else
  #error "Cannot find XMPMeta.hpp (needed to construct XMPMeta for black-box wrapper tests)."
#endif

// The wrapper function under test (C interface). We only declare it here; implementation is in WXMPMeta.cpp.
extern "C" {
void WXMPMeta_ParseFromBuffer_1(XMPMetaRef xmpRef,
                               XMP_StringPtr buffer,
                               XMP_StringLen bufferSize,
                               XMP_OptionBits options,
                               WXMP_Result* wResult);
} // extern "C"

// ------------------------------
// Test fixture
// ------------------------------
class WXMPMeta_ParseFromBuffer_1_Test_2045 : public ::testing::Test {
protected:
  static std::string MinimalValidXmpPacket() {
    // A minimal, commonly-accepted XMP packet with one simple Dublin Core property.
    // We do not assume any internal parsing rules beyond "valid vs invalid".
    return std::string(
        "<?xpacket begin='﻿' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        " <rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "  <rdf:Description rdf:about='' xmlns:dc='http://purl.org/dc/elements/1.1/'>"
        "   <dc:creator>"
        "    <rdf:Seq>"
        "     <rdf:li>UnitTest</rdf:li>"
        "    </rdf:Seq>"
        "   </dc:creator>"
        "  </rdf:Description>"
        " </rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>");
  }

  static std::string ClearlyInvalidXmpPayload() {
    return std::string("this is not xml / not xmp / not rdf");
  }
};

// ------------------------------
// Normal operation
// ------------------------------

TEST_F(WXMPMeta_ParseFromBuffer_1_Test_2045, ParsesValidXmpBufferWithoutError_2045) {
  XMPMeta meta;
  WXMP_Result result;

  const std::string xmp = MinimalValidXmpPacket();

  // Treat the wrapper as a black box: we only provide an object reference and verify observable outcome.
  WXMPMeta_ParseFromBuffer_1(reinterpret_cast<XMPMetaRef>(&meta),
                            xmp.c_str(),
                            static_cast<XMP_StringLen>(xmp.size()),
                            static_cast<XMP_OptionBits>(0),
                            &result);

  // Observable wrapper outcome: on success, errMessage should remain null.
  EXPECT_EQ(nullptr, result.errMessage);

  // Additional observable behavior via public interface: parsed content should make at least one property exist.
  // We avoid asserting exact parsing semantics beyond "something retrievable that matches what we provided".
  XMP_StringPtr propValue = nullptr;
  XMP_StringLen valueSize = 0;
  XMP_OptionBits propOptions = 0;

  const bool gotCreator =
      meta.GetProperty("http://purl.org/dc/elements/1.1/", "creator", &propValue, &valueSize, &propOptions);

  // Depending on how the SDK exposes array values via GetProperty, it might be true or false.
  // To keep the test black-box and robust, we assert that parsing succeeded and either:
  // - creator exists as a property, OR
  // - the array item exists at index 1 (common in XMP APIs).
  if (!gotCreator) {
    XMP_StringPtr itemValue = nullptr;
    XMP_StringLen itemSize = 0;
    XMP_OptionBits itemOptions = 0;
    const bool gotItem =
        meta.GetArrayItem("http://purl.org/dc/elements/1.1/", "creator", /*itemIndex*/ 1, &itemValue, &itemSize,
                          &itemOptions);
    EXPECT_TRUE(gotItem);
    if (gotItem) {
      EXPECT_NE(nullptr, itemValue);
      EXPECT_GT(itemSize, 0u);
    }
  } else {
    EXPECT_NE(nullptr, propValue);
    EXPECT_GT(valueSize, 0u);
  }
}

// ------------------------------
// Boundary conditions
// ------------------------------

TEST_F(WXMPMeta_ParseFromBuffer_1_Test_2045, AcceptsZeroSizeBufferGracefully_2045) {
  XMPMeta meta;
  WXMP_Result result;

  const char* empty = "";

  WXMPMeta_ParseFromBuffer_1(reinterpret_cast<XMPMetaRef>(&meta),
                            empty,
                            static_cast<XMP_StringLen>(0),
                            static_cast<XMP_OptionBits>(0),
                            &result);

  // Observable behavior: either it is treated as empty/no-op (no error),
  // or it is treated as a parse error (errMessage set). We assert it does not crash and produces a stable result.
  // Since we can't rely on internal policy, we only require that the result pointer is usable.
  // If there is an error, errMessage should be non-null.
  if (result.errMessage != nullptr) {
    EXPECT_NE('\0', result.errMessage[0]);
  }
}

TEST_F(WXMPMeta_ParseFromBuffer_1_Test_2045, RejectsNullBufferWithNonZeroSize_2045) {
  XMPMeta meta;
  WXMP_Result result;

  WXMPMeta_ParseFromBuffer_1(reinterpret_cast<XMPMetaRef>(&meta),
                            /*buffer*/ nullptr,
                            static_cast<XMP_StringLen>(10),
                            static_cast<XMP_OptionBits>(0),
                            &result);

  // Observable error reporting via WXMP_Result.
  EXPECT_NE(nullptr, result.errMessage);
  if (result.errMessage != nullptr) {
    EXPECT_NE('\0', result.errMessage[0]);
  }
}

TEST_F(WXMPMeta_ParseFromBuffer_1_Test_2045, HandlesTruncatedBufferSize_2045) {
  XMPMeta meta;
  WXMP_Result result;

  const std::string xmp = MinimalValidXmpPacket();
  const XMP_StringLen truncatedSize = static_cast<XMP_StringLen>(xmp.size() / 2); // intentionally too small

  WXMPMeta_ParseFromBuffer_1(reinterpret_cast<XMPMetaRef>(&meta),
                            xmp.c_str(),
                            truncatedSize,
                            static_cast<XMP_OptionBits>(0),
                            &result);

  // Truncation might parse or might error depending on the parser. If it errors, errMessage should be set.
  if (result.errMessage != nullptr) {
    EXPECT_NE('\0', result.errMessage[0]);
  }
}

// ------------------------------
// Exceptional / error cases (observable via interface)
// ------------------------------

TEST_F(WXMPMeta_ParseFromBuffer_1_Test_2045, ReportsErrorForInvalidPayload_2045) {
  XMPMeta meta;
  WXMP_Result result;

  const std::string bad = ClearlyInvalidXmpPayload();

  WXMPMeta_ParseFromBuffer_1(reinterpret_cast<XMPMetaRef>(&meta),
                            bad.c_str(),
                            static_cast<XMP_StringLen>(bad.size()),
                            static_cast<XMP_OptionBits>(0),
                            &result);

  // For invalid input, wrapper should report an error via WXMP_Result (observable behavior).
  EXPECT_NE(nullptr, result.errMessage);
  if (result.errMessage != nullptr) {
    EXPECT_NE('\0', result.errMessage[0]);
  }
}

TEST_F(WXMPMeta_ParseFromBuffer_1_Test_2045, ReportsErrorForNullXmpRef_2045) {
  WXMP_Result result;
  const std::string xmp = MinimalValidXmpPacket();

  WXMPMeta_ParseFromBuffer_1(/*xmpRef*/ nullptr,
                            xmp.c_str(),
                            static_cast<XMP_StringLen>(xmp.size()),
                            static_cast<XMP_OptionBits>(0),
                            &result);

  EXPECT_NE(nullptr, result.errMessage);
  if (result.errMessage != nullptr) {
    EXPECT_NE('\0', result.errMessage[0]);
  }
}