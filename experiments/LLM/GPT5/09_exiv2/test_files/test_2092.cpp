// ============================================================================
// TEST_ID: 2092
// Unit tests for StartNamespaceDeclHandler in ExpatAdapter.cpp
// ============================================================================

#include <gtest/gtest.h>

#include <string>

// Include the implementation file so the file-scope static handler is visible
// within this translation unit (black-box test of observable behavior via XMPMeta).
#include "TestProjects/exiv2/xmpsdk/src/ExpatAdapter.cpp"

#include "TestProjects/exiv2/xmpsdk/src/XMPMeta.hpp"

namespace {

class ExpatAdapterStartNamespaceDeclHandlerTest_2092 : public ::testing::Test {
protected:
  static void SetUpTestSuite() {
    // XMPMeta namespace registry is global; ensure the toolkit is initialized.
    // If already initialized elsewhere in the test runner, Initialize() should
    // typically be idempotent (but we only assert success here).
    ASSERT_TRUE(XMPMeta::Initialize());
  }

  static void TearDownTestSuite() {
    XMPMeta::Terminate();
  }

  static std::string GetPrefixForURI(const char* uri) {
    XMP_StringPtr nsPrefix = nullptr;
    XMP_StringLen prefixSize = 0;
    const bool ok = XMPMeta::GetNamespacePrefix(uri, &nsPrefix, &prefixSize);
    if (!ok) return std::string();
    return std::string(nsPrefix, static_cast<size_t>(prefixSize));
  }

  static bool HasURI(const char* uri) {
    XMP_StringPtr nsPrefix = nullptr;
    XMP_StringLen prefixSize = 0;
    return XMPMeta::GetNamespacePrefix(uri, &nsPrefix, &prefixSize);
  }

  static bool HasPrefix(const char* prefix) {
    XMP_StringPtr nsURI = nullptr;
    XMP_StringLen uriSize = 0;
    return XMPMeta::GetNamespaceURI(prefix, &nsURI, &uriSize);
  }

  static void CleanupURI(const char* uri) {
    // Safe cleanup if present; DeleteNamespace is a no-op if not present in most implementations.
    XMPMeta::DeleteNamespace(uri);
  }
};

TEST_F(ExpatAdapterStartNamespaceDeclHandlerTest_2092,
       NullPrefixRegistersDefaultPrefix_2092) {
  const char* kURI = "http://ns.example.com/xmp/unit/2092/default-prefix/";
  CleanupURI(kURI);

  // prefix == 0 => should use "_dflt_" (observable by looking up the registered prefix for URI)
  StartNamespaceDeclHandler(/*userData*/ nullptr, /*prefix*/ nullptr, /*uri*/ kURI);

  EXPECT_TRUE(HasURI(kURI));
  EXPECT_EQ(GetPrefixForURI(kURI), "_dflt_");

  CleanupURI(kURI);
}

TEST_F(ExpatAdapterStartNamespaceDeclHandlerTest_2092,
       NonNullPrefixRegistersAsProvided_2092) {
  const char* kURI = "http://ns.example.com/xmp/unit/2092/explicit-prefix/";
  CleanupURI(kURI);

  StartNamespaceDeclHandler(/*userData*/ nullptr, /*prefix*/ "pre2092", /*uri*/ kURI);

  EXPECT_TRUE(HasURI(kURI));
  EXPECT_EQ(GetPrefixForURI(kURI), "pre2092");

  CleanupURI(kURI);
}

TEST_F(ExpatAdapterStartNamespaceDeclHandlerTest_2092,
       NullUriDoesNotRegisterNamespace_2092) {
  // The handler returns early if uri == 0. We verify this by ensuring the
  // provided prefix does not become registered to any namespace URI.
  const char* kPrefix = "noUriPrefix2092";

  // Precondition: prefix should not be registered.
  EXPECT_FALSE(HasPrefix(kPrefix));

  StartNamespaceDeclHandler(/*userData*/ nullptr, /*prefix*/ kPrefix, /*uri*/ nullptr);

  // Postcondition: still not registered.
  EXPECT_FALSE(HasPrefix(kPrefix));
}

TEST_F(ExpatAdapterStartNamespaceDeclHandlerTest_2092,
       DcNamespaceUriIsCanonicalizedBeforeRegister_2092) {
  // The handler maps "http://purl.org/dc/1.1/" to "http://purl.org/dc/elements/1.1/".
  const char* kOriginal = "http://purl.org/dc/1.1/";
  const char* kCanonical = "http://purl.org/dc/elements/1.1/";

  // Clean both, to avoid interference if the environment already has one registered.
  CleanupURI(kOriginal);
  CleanupURI(kCanonical);

  StartNamespaceDeclHandler(/*userData*/ nullptr, /*prefix*/ "dc2092", /*uri*/ kOriginal);

  // Observable effect: canonical URI should be registered with prefix "dc2092".
  EXPECT_TRUE(HasURI(kCanonical));
  EXPECT_EQ(GetPrefixForURI(kCanonical), "dc2092");

  // Also ensure we didn't end up registering the original URI under the prefix in this call.
  // (If it existed before due to environment, we cleaned it above.)
  EXPECT_FALSE(HasURI(kOriginal));

  CleanupURI(kCanonical);
  CleanupURI(kOriginal);
}

}  // namespace