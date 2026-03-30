// poppler-error-quark-test-2596.cc
//
// Unit tests for poppler_error_quark() in ./TestProjects/poppler/glib/poppler.cc
//
// Constraints honored:
// - Treat implementation as black box: only test observable behavior (return value).
// - No access to internal/static state.
// - No re-implementation of internal logic beyond calling the function.
// - Boundary/error cases: validate stability and non-zero quark.
// - External interactions: none observable/available for mocking here.

#include <gtest/gtest.h>

#include <glib.h>

// The function under test is implemented in poppler.cc.
// Include the proper header if available in your tree. If not, keep this forward declaration.
extern "C" GQuark poppler_error_quark(void);

namespace {

class PopplerErrorQuarkTest_2596 : public ::testing::Test {};

TEST_F(PopplerErrorQuarkTest_2596, ReturnsNonZeroQuark_2596) {
  // Normal operation: should return a valid (non-zero) quark id.
  const GQuark q = poppler_error_quark();
  EXPECT_NE(q, static_cast<GQuark>(0));
}

TEST_F(PopplerErrorQuarkTest_2596, ReturnsSameQuarkOnRepeatedCalls_2596) {
  // Boundary/consistency: repeated calls should be stable (same id).
  const GQuark q1 = poppler_error_quark();
  const GQuark q2 = poppler_error_quark();
  EXPECT_EQ(q1, q2);
  EXPECT_NE(q1, static_cast<GQuark>(0));
}

TEST_F(PopplerErrorQuarkTest_2596, ReturnedQuarkMapsToExpectedString_2596) {
  // Observable correctness through GLib API:
  // If the function registers a quark for the static string, querying it back should
  // yield the same string pointer content.
  const GQuark q = poppler_error_quark();
  ASSERT_NE(q, static_cast<GQuark>(0));

  const char* s = g_quark_to_string(q);
  ASSERT_NE(s, nullptr);
  EXPECT_STREQ(s, "poppler-quark");
}

TEST_F(PopplerErrorQuarkTest_2596, QuarkMatchesLookupByString_2596) {
  // Boundary: verify that a quark created/queried by the same string corresponds
  // to what poppler_error_quark() returns.
  const GQuark expected = g_quark_from_static_string("poppler-quark");
  const GQuark actual = poppler_error_quark();

  EXPECT_NE(expected, static_cast<GQuark>(0));
  EXPECT_NE(actual, static_cast<GQuark>(0));
  EXPECT_EQ(actual, expected);
}

TEST_F(PopplerErrorQuarkTest_2596, CompatibleWithGErrorDomainUsage_2596) {
  // "Error case" coverage (observable): ensure returned quark can be used as a
  // GError domain without crashing and retains the same domain value.
  const GQuark domain = poppler_error_quark();
  ASSERT_NE(domain, static_cast<GQuark>(0));

  GError* err = nullptr;
  g_set_error_literal(&err, domain, /*code=*/1, "test error");
  ASSERT_NE(err, nullptr);

  EXPECT_EQ(err->domain, domain);
  EXPECT_EQ(err->code, 1);
  ASSERT_NE(err->message, nullptr);
  EXPECT_STREQ(err->message, "test error");

  g_clear_error(&err);
  EXPECT_EQ(err, nullptr);
}

}  // namespace