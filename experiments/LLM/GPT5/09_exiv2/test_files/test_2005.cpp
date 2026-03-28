// File: test_WXMPMeta_RegisterStandardAliases_1_2005.cpp
// Unit tests for WXMPMeta_RegisterStandardAliases_1
//
// Constraints honored:
// - Treat implementation as black box (no internal logic assumptions)
// - Test only observable behavior through the public wrapper interface
// - No private/internal state access
// - No mocking of internals

#include <gtest/gtest.h>

#include <cstddef>
#include <cstring>
#include <string>

// Bring in the SDK types used by the wrapper signature.
#include "client-glue/WXMP_Common.hpp" // WXMP_Result
#include "XMP_Const.h"                // XMP_StringPtr, etc.

// The function under test is implemented in WXMPMeta.cpp.
// Declare it here (do not re-implement).
extern "C" {
void WXMPMeta_RegisterStandardAliases_1(XMP_StringPtr schemaNS, WXMP_Result* wResult);
}

namespace {

class WXMPMeta_RegisterStandardAliases_1_Test_2005 : public ::testing::Test {
protected:
  WXMP_Result result; // ctor sets errMessage to 0 per provided snippet
};

TEST_F(WXMPMeta_RegisterStandardAliases_1_Test_2005, NullSchemaNS_DoesNotSetError_2005) {
  ASSERT_EQ(result.errMessage, nullptr);

  EXPECT_NO_THROW({
    WXMPMeta_RegisterStandardAliases_1(nullptr, &result);
  });

  EXPECT_EQ(result.errMessage, nullptr);
}

TEST_F(WXMPMeta_RegisterStandardAliases_1_Test_2005, EmptySchemaNS_DoesNotSetError_2005) {
  ASSERT_EQ(result.errMessage, nullptr);

  EXPECT_NO_THROW({
    WXMPMeta_RegisterStandardAliases_1("", &result);
  });

  EXPECT_EQ(result.errMessage, nullptr);
}

TEST_F(WXMPMeta_RegisterStandardAliases_1_Test_2005, ArbitrarySchemaNS_DoesNotSetError_2005) {
  ASSERT_EQ(result.errMessage, nullptr);

  // Use a plausible-but-arbitrary schema namespace. We do not assert any alias side effects,
  // only that the wrapper call completes without reporting an error.
  const char* schema = "http://example.com/ns/arbitrary/1.0/";

  EXPECT_NO_THROW({
    WXMPMeta_RegisterStandardAliases_1(schema, &result);
  });

  EXPECT_EQ(result.errMessage, nullptr);
}

TEST_F(WXMPMeta_RegisterStandardAliases_1_Test_2005, VeryLongSchemaNS_DoesNotSetError_2005) {
  ASSERT_EQ(result.errMessage, nullptr);

  // Boundary-ish input: long string.
  std::string longSchema(8192, 'a');
  longSchema = std::string("http://example.com/") + longSchema;

  EXPECT_NO_THROW({
    WXMPMeta_RegisterStandardAliases_1(longSchema.c_str(), &result);
  });

  EXPECT_EQ(result.errMessage, nullptr);
}

TEST_F(WXMPMeta_RegisterStandardAliases_1_Test_2005, RepeatedCalls_DoNotSetError_2005) {
  ASSERT_EQ(result.errMessage, nullptr);

  EXPECT_NO_THROW({
    WXMPMeta_RegisterStandardAliases_1(nullptr, &result);
    WXMPMeta_RegisterStandardAliases_1("", &result);
    WXMPMeta_RegisterStandardAliases_1("http://example.com/ns/arbitrary/1.0/", &result);
  });

  EXPECT_EQ(result.errMessage, nullptr);
}

} // namespace