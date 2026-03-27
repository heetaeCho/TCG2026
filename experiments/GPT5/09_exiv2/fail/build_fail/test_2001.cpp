// File: test_WXMPMeta_DeleteNamespace_1_2001.cpp

#include <gtest/gtest.h>

#include <cstring>
#include <string>

#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPMeta.hpp"

// The wrapper under test (implemented in WXMPMeta.cpp).
extern "C" void WXMPMeta_DeleteNamespace_1(XMP_StringPtr namespaceURI, WXMP_Result* wResult);

namespace {

class WXMPMeta_DeleteNamespace_1_Test_2001 : public ::testing::Test {
protected:
  static void SetUpTestSuite() {
    (void)XMPMeta::Initialize();
  }

  static void TearDownTestSuite() {
    XMPMeta::Terminate();
  }

  static std::string ToStdString(XMP_StringPtr s, XMP_StringLen n) {
    if (s == nullptr) return {};
    if (n > 0) return std::string(s, s + n);
    return std::string(s);
  }
};

TEST_F(WXMPMeta_DeleteNamespace_1_Test_2001, DeletesRegisteredNamespace_2001) {
  const char* kURI = "http://ns.example.com/wxmptest/2001/";
  const char* kPrefix = "tst";

  // Register and verify it exists.
  ASSERT_NO_THROW(XMPMeta::RegisterNamespace(kURI, kPrefix));

  XMP_StringPtr gotPrefix = nullptr;
  XMP_StringLen gotPrefixSize = 0;
  ASSERT_TRUE(XMPMeta::GetNamespacePrefix(kURI, &gotPrefix, &gotPrefixSize));
  EXPECT_FALSE(ToStdString(gotPrefix, gotPrefixSize).empty());

  // Delete via wrapper.
  WXMP_Result wr;
  WXMPMeta_DeleteNamespace_1(kURI, &wr);

  EXPECT_EQ(wr.errMessage, nullptr);

  // Verify it no longer resolves.
  gotPrefix = nullptr;
  gotPrefixSize = 0;
  EXPECT_FALSE(XMPMeta::GetNamespacePrefix(kURI, &gotPrefix, &gotPrefixSize));
}

TEST_F(WXMPMeta_DeleteNamespace_1_Test_2001, NullNamespaceURISetsError_2001) {
  WXMP_Result wr;
  WXMPMeta_DeleteNamespace_1(nullptr, &wr);

  ASSERT_NE(wr.errMessage, nullptr);
  EXPECT_NE(std::strstr(wr.errMessage, "Empty namespace URI"), nullptr);
}

TEST_F(WXMPMeta_DeleteNamespace_1_Test_2001, EmptyNamespaceURISetsError_2001) {
  WXMP_Result wr;
  WXMPMeta_DeleteNamespace_1("", &wr);

  ASSERT_NE(wr.errMessage, nullptr);
  EXPECT_NE(std::strstr(wr.errMessage, "Empty namespace URI"), nullptr);
}

TEST_F(WXMPMeta_DeleteNamespace_1_Test_2001, DeletingUnknownNamespaceDoesNotCrash_2001) {
  const char* kUnknownURI = "http://ns.example.com/wxmptest/2001/unknown";

  WXMP_Result wr;
  WXMPMeta_DeleteNamespace_1(kUnknownURI, &wr);

  // Observable behavior: should complete without reporting the "empty URI" error.
  if (wr.errMessage != nullptr) {
    EXPECT_EQ(std::strstr(wr.errMessage, "Empty namespace URI"), nullptr);
  }
}

}  // namespace