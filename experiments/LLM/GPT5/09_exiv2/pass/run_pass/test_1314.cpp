// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_xmpparser_initialize_1314.cpp
//
// Unit tests for Exiv2::XmpParser::initialize (black-box tests)
//
// Constraints honored:
// - No assumptions about internal state (initialized_ etc.)
// - Only observable behavior via public API / external library surface (namespace lookup)

#include <gtest/gtest.h>

#include <string>

#include <exiv2/xmp_exiv2.hpp>

namespace {

class XmpParserInitializeTest_1314 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Intentionally empty:
    // - initialize() is expected to be idempotent and safe to call multiple times.
    // - We avoid calling terminate() here because it is not part of the provided partial code
    //   and may have global side effects across the test binary.
  }
};

TEST_F(XmpParserInitializeTest_1314, InitializeWithNullLockDoesNotCrash_1314) {
#if defined(EXV_HAVE_XMP_TOOLKIT) || defined(EXV_HAVE_XMP_SDK) || defined(EXIV2_ENABLE_XMP)
  // Boundary: pass nullptr lock function and nullptr lock data.
  const bool first = Exiv2::XmpParser::initialize(nullptr, nullptr);
  const bool second = Exiv2::XmpParser::initialize(nullptr, nullptr);

  // Observable behavior: function returns a bool and should be stable across repeated calls.
  EXPECT_EQ(first, second);
#else
  GTEST_SKIP() << "XMP toolkit support not enabled in this build.";
#endif
}

TEST_F(XmpParserInitializeTest_1314, InitializeRegistersLightroomNamespacePrefix_1314) {
#if defined(EXV_HAVE_XMP_TOOLKIT) || defined(EXV_HAVE_XMP_SDK) || defined(EXIV2_ENABLE_XMP)
  const bool okInit = Exiv2::XmpParser::initialize(nullptr, nullptr);
  if (!okInit) {
    GTEST_SKIP() << "XmpParser::initialize returned false (XMP toolkit not initialized).";
  }

  std::string prefix;
  const bool ok = SXMPMeta::GetNamespacePrefix("http://ns.adobe.com/lightroom/1.0/", &prefix);

  EXPECT_TRUE(ok);
  EXPECT_EQ(prefix, "lr");
#else
  GTEST_SKIP() << "XMP toolkit support not enabled in this build.";
#endif
}

TEST_F(XmpParserInitializeTest_1314, InitializeRegistersAudioAndVideoNamespaces_1314) {
#if defined(EXV_HAVE_XMP_TOOLKIT) || defined(EXV_HAVE_XMP_SDK) || defined(EXIV2_ENABLE_XMP)
  const bool okInit = Exiv2::XmpParser::initialize(nullptr, nullptr);
  if (!okInit) {
    GTEST_SKIP() << "XmpParser::initialize returned false (XMP toolkit not initialized).";
  }

  {
    std::string prefix;
    const bool ok = SXMPMeta::GetNamespacePrefix("http://www.audio/", &prefix);
    EXPECT_TRUE(ok);
    EXPECT_EQ(prefix, "audio");
  }

  {
    std::string prefix;
    const bool ok = SXMPMeta::GetNamespacePrefix("http://www.video/", &prefix);
    EXPECT_TRUE(ok);
    EXPECT_EQ(prefix, "video");
  }
#else
  GTEST_SKIP() << "XMP toolkit support not enabled in this build.";
#endif
}

TEST_F(XmpParserInitializeTest_1314, InitializeIsIdempotent_NamespacePrefixStillPresentAfterSecondCall_1314) {
#if defined(EXV_HAVE_XMP_TOOLKIT) || defined(EXV_HAVE_XMP_SDK) || defined(EXIV2_ENABLE_XMP)
  const bool okInit1 = Exiv2::XmpParser::initialize(nullptr, nullptr);
  if (!okInit1) {
    GTEST_SKIP() << "XmpParser::initialize returned false (XMP toolkit not initialized).";
  }

  std::string prefix1;
  ASSERT_TRUE(SXMPMeta::GetNamespacePrefix("http://purl.org/dc/terms/", &prefix1));
  EXPECT_EQ(prefix1, "dcterms");

  // Call initialize again (boundary / idempotence). We do not assume anything about internal caching,
  // only that it should not break previously-registered namespaces.
  const bool okInit2 = Exiv2::XmpParser::initialize(nullptr, nullptr);
  EXPECT_TRUE(okInit2);

  std::string prefix2;
  ASSERT_TRUE(SXMPMeta::GetNamespacePrefix("http://purl.org/dc/terms/", &prefix2));
  EXPECT_EQ(prefix2, "dcterms");
#else
  GTEST_SKIP() << "XMP toolkit support not enabled in this build.";
#endif
}

}  // namespace