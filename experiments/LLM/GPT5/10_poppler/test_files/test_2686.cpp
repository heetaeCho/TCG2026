// File: pdfsig_typeToString_test_2686.cc
//
// Unit tests for:
//   static const char *typeToString(CertificateType type)
//
// Constraints respected:
// - Treat implementation as black box (no re-implementation beyond calling it).
// - Verify only observable behavior (returned C-string contents / pointer validity).
// - Include normal + boundary/unknown + (observable) error cases.

#include <gtest/gtest.h>

#include <cstring>
#include <string>

// Mirror the dependency enum (as provided).
enum class CertificateType { X509 = 0, PGP = 1 };

// Forward declaration of the function under test.
// In the real codebase, this is in utils/pdfsig.cc and is `static`.
// For unit testing, your build system should compile/link pdfsig.cc into the test
// (or expose the symbol via an internal header / test-only translation unit include).
static const char *typeToString(CertificateType type);

namespace {

// Helper to safely compare returned C-strings.
static std::string SafeStr(const char *s) { return s ? std::string(s) : std::string(); }

class PdfsigTypeToStringTest_2686 : public ::testing::Test {};

TEST_F(PdfsigTypeToStringTest_2686, ReturnsPGPForPGP_2686) {
  const char *out = typeToString(CertificateType::PGP);
  ASSERT_NE(out, nullptr);
  EXPECT_STREQ(out, "PGP");
}

TEST_F(PdfsigTypeToStringTest_2686, ReturnsSMimeForX509_2686) {
  const char *out = typeToString(CertificateType::X509);
  ASSERT_NE(out, nullptr);
  EXPECT_STREQ(out, "S/Mime");
}

TEST_F(PdfsigTypeToStringTest_2686, ReturnsEmptyStringForUnknownEnumValue_2686) {
  // Boundary / error-like case: value not covered by known enumerators.
  // Observable behavior: function should return a valid C-string (not nullptr),
  // and (per interface) it returns "" for unknown.
  const auto unknown = static_cast<CertificateType>(-1);
  const char *out = typeToString(unknown);

  ASSERT_NE(out, nullptr);
  EXPECT_STREQ(out, "");
}

TEST_F(PdfsigTypeToStringTest_2686, ReturnsEmptyStringForOutOfRangePositiveEnumValue_2686) {
  // Another boundary case: large out-of-range value.
  const auto unknown = static_cast<CertificateType>(999);
  const char *out = typeToString(unknown);

  ASSERT_NE(out, nullptr);
  EXPECT_STREQ(out, "");
}

TEST_F(PdfsigTypeToStringTest_2686, ReturnedPointerIsStableAcrossCallsForKnownValues_2686) {
  // Observable behavior: since the function returns string literals,
  // repeated calls for the same input should yield the same pointer
  // (this is safe to assert for string literals).
  const char *a1 = typeToString(CertificateType::PGP);
  const char *a2 = typeToString(CertificateType::PGP);
  ASSERT_NE(a1, nullptr);
  ASSERT_NE(a2, nullptr);
  EXPECT_EQ(a1, a2);

  const char *b1 = typeToString(CertificateType::X509);
  const char *b2 = typeToString(CertificateType::X509);
  ASSERT_NE(b1, nullptr);
  ASSERT_NE(b2, nullptr);
  EXPECT_EQ(b1, b2);
}

TEST_F(PdfsigTypeToStringTest_2686, ReturnedStringsAreNullTerminated_2686) {
  // Basic safety/contract check: returned C-string should be null-terminated.
  // We verify by ensuring strlen doesn't crash and matches expected content.
  const char *pgp = typeToString(CertificateType::PGP);
  const char *smime = typeToString(CertificateType::X509);
  const char *unk = typeToString(static_cast<CertificateType>(12345));

  ASSERT_NE(pgp, nullptr);
  ASSERT_NE(smime, nullptr);
  ASSERT_NE(unk, nullptr);

  EXPECT_EQ(std::strlen(pgp), SafeStr(pgp).size());
  EXPECT_EQ(std::strlen(smime), SafeStr(smime).size());
  EXPECT_EQ(std::strlen(unk), SafeStr(unk).size());
}

}  // namespace