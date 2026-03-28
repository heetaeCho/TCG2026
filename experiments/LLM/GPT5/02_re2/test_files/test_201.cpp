// File: pcre_number_of_capturing_groups_test_201.cc

#include <gtest/gtest.h>
#include <string>

// --- Test-time stub for the external collaborator ---------------------------
// We mock pcre_fullinfo as an external dependency to control observable outcomes.
// NOTE: We do NOT simulate internal behavior of re2::PCRE; we only control the
// collaborator's outputs to observe PCRE::NumberOfCapturingGroups() behavior.

extern "C" {

// Globals to control the stubbed collaborator's behavior in tests.
static int g_pcre_fullinfo_rc = 0;
static int g_pcre_fullinfo_capturecount = 0;

// Minimal opaque type to satisfy the signature; real content is irrelevant
// to the unit test since PCRE treats it opaquely here.
struct pcre {};

int pcre_fullinfo(const pcre* re_partial,
                  const void* /*study_data*/,
                  int /*what*/,
                  void* where_out) {
  // If test wants an error code, return it immediately.
  if (g_pcre_fullinfo_rc != 0) {
    return g_pcre_fullinfo_rc;
  }
  // Simulate normal behavior only when a compiled regex object is present.
  if (re_partial == nullptr) {
    // In real PCRE this would be an error; returning any nonzero triggers -1.
    return 999;
  }
  // Write the capture count requested by the test.
  *static_cast<int*>(where_out) = g_pcre_fullinfo_capturecount;
  return 0;
}

} // extern "C"

// --- System under test -------------------------------------------------------
#include "re2/util/pcre.h"   // Uses the same pcre_fullinfo symbol we've stubbed.

using re2::PCRE;

// Test fixture to reset stub controls between tests.
class PCRENumberOfCapturingGroupsTest_201 : public ::testing::Test {
 protected:
  void SetUp() override {
    g_pcre_fullinfo_rc = 0;
    g_pcre_fullinfo_capturecount = 0;
  }
};

// -----------------------------------------------------------------------------
// Normal operation: valid pattern, zero capturing groups.
TEST_F(PCRENumberOfCapturingGroupsTest_201, ReturnsZeroWhenNoCaptures_201) {
  // Arrange
  g_pcre_fullinfo_capturecount = 0;
  PCRE re_no_caps("abc");  // Treat as black box; just needs to be constructible.

  // Act
  int count = re_no_caps.NumberOfCapturingGroups();

  // Assert
  EXPECT_EQ(count, 0);
}

// Normal operation: valid pattern with capturing groups.
TEST_F(PCRENumberOfCapturingGroupsTest_201, ReturnsActualCaptureCount_201) {
  // Arrange
  g_pcre_fullinfo_capturecount = 2;
  PCRE re_two_caps("(a)(b|c)");

  // Act
  int count = re_two_caps.NumberOfCapturingGroups();

  // Assert
  EXPECT_EQ(count, 2);
}

// Boundary/exceptional: underlying compiled object absent -> should return -1.
// We provoke this by using an invalid pattern so the internal compiled pointer
// is expected to be null (observable only via the public method's return).
TEST_F(PCRENumberOfCapturingGroupsTest_201, ReturnsMinusOneWhenUninitialized_201) {
  // Arrange
  // Keep stub in normal mode so the method's own null check is exercised.
  PCRE re_invalid("(");  // Invalid regex; treat class as a black box.

  // Act
  int count = re_invalid.NumberOfCapturingGroups();

  // Assert
  EXPECT_EQ(count, -1);
}

// Error path: collaborator returns a non-zero error code -> should return -1.
TEST_F(PCRENumberOfCapturingGroupsTest_201, ReturnsMinusOneOnFullinfoError_201) {
  // Arrange
  PCRE re_any("x(y)");  // Any valid pattern
  g_pcre_fullinfo_rc = 42;  // Non-zero forces error path

  // Act
  int count = re_any.NumberOfCapturingGroups();

  // Assert
  EXPECT_EQ(count, -1);
}
