// poppler_signing_data_get_background_color_test.cpp
//
// Unit tests for:
//   const PopplerColor *poppler_signing_data_get_background_color(const PopplerSigningData *signing_data);
//
// Constraints honored:
// - Treat implementation as black box
// - Only use public interface/observable behavior
// - No access to private/internal state beyond what is required to construct valid inputs
// - Include normal, boundary, and error cases
//
// NOTE: This test assumes Poppler GLib headers are available in the include path.

#include <gtest/gtest.h>

#include <glib.h>

// Poppler GLib headers (path may vary by project setup)
#include <poppler.h>

// Function under test (declared in poppler headers, but declare defensively if needed)
extern "C" const PopplerColor *poppler_signing_data_get_background_color(
    const PopplerSigningData *signing_data);

namespace {

class PopplerSigningDataGetBackgroundColorTest_2379 : public ::testing::Test {
protected:
  void SetUp() override {
    // Nothing
  }
  void TearDown() override {
    // Nothing
  }
};

TEST_F(PopplerSigningDataGetBackgroundColorTest_2379, NullSigningDataReturnsNull_2379) {
  const PopplerColor *color = poppler_signing_data_get_background_color(nullptr);
  EXPECT_EQ(color, nullptr);
}

TEST_F(PopplerSigningDataGetBackgroundColorTest_2379, ReturnsNonNullForValidSigningData_2379) {
  PopplerSigningData sd{};
  const PopplerColor *color = poppler_signing_data_get_background_color(&sd);
  ASSERT_NE(color, nullptr);
}

TEST_F(PopplerSigningDataGetBackgroundColorTest_2379, ReturnsStablePointerForSameObject_2379) {
  PopplerSigningData sd{};
  const PopplerColor *c1 = poppler_signing_data_get_background_color(&sd);
  const PopplerColor *c2 = poppler_signing_data_get_background_color(&sd);

  ASSERT_NE(c1, nullptr);
  ASSERT_NE(c2, nullptr);
  EXPECT_EQ(c1, c2) << "Expected the returned pointer to be stable for the same signing_data instance";
}

TEST_F(PopplerSigningDataGetBackgroundColorTest_2379, DifferentObjectsReturnDifferentAddresses_2379) {
  PopplerSigningData sd1{};
  PopplerSigningData sd2{};

  const PopplerColor *c1 = poppler_signing_data_get_background_color(&sd1);
  const PopplerColor *c2 = poppler_signing_data_get_background_color(&sd2);

  ASSERT_NE(c1, nullptr);
  ASSERT_NE(c2, nullptr);

  // Each returned pointer should refer to each object's own background color storage.
  EXPECT_NE(c1, c2);
}

TEST_F(PopplerSigningDataGetBackgroundColorTest_2379, DoesNotCrashWithUnusualColorValues_2379) {
  // Boundary-ish: set extreme-ish channel values (PopplerColor channels are typically 0..65535).
  // We don't assert specific contents (black-box), only that function returns a valid pointer.
  PopplerSigningData sd{};
  sd.background_color.red = 0;
  sd.background_color.green = 65535;
  sd.background_color.blue = 65535;

  const PopplerColor *color = poppler_signing_data_get_background_color(&sd);
  ASSERT_NE(color, nullptr);

  // Observably, the pointer should remain stable across calls.
  EXPECT_EQ(color, poppler_signing_data_get_background_color(&sd));
}

}  // namespace