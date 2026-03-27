// File: src/get_load_average_test_157.cc

#include "gtest/gtest.h"
#include "util.h"   // Declares double GetLoadAverage().
#include <cmath>

// Test double for the external collaborator getloadavg().
// We override the symbol in the test binary to fully control
// its observable behavior for GetLoadAverage() tests.
namespace {

struct FakeGetLoadAvgState {
  int return_value;
  double sample0;
  int last_nelem;
  int call_count;
};

FakeGetLoadAvgState g_fake_getloadavg_state;

// C-linkage to match the real getloadavg().
extern "C" int getloadavg(double* loadavg, int nelem) {
  FakeGetLoadAvgState& s = g_fake_getloadavg_state;
  s.call_count++;
  s.last_nelem = nelem;

  if (s.return_value >= 0 && loadavg != nullptr && nelem > 0) {
    // Provide the first load average sample.
    loadavg[0] = s.sample0;
  }

  return s.return_value;
}

class GetLoadAverageTest_157 : public ::testing::Test {
 protected:
  void SetUp() override {
    g_fake_getloadavg_state.return_value = 0;
    g_fake_getloadavg_state.sample0 = 0.0;
    g_fake_getloadavg_state.last_nelem = 0;
    g_fake_getloadavg_state.call_count = 0;
  }
};

}  // namespace

// Verifies that GetLoadAverage calls getloadavg() once and requests
// exactly three samples (matching the interface usage).
TEST_F(GetLoadAverageTest_157, CallsGetloadavgWithThreeSamples_157) {
  g_fake_getloadavg_state.return_value = 1;
  g_fake_getloadavg_state.sample0 = 1.0;

  (void)GetLoadAverage();

  EXPECT_EQ(1, g_fake_getloadavg_state.call_count);
  EXPECT_EQ(3, g_fake_getloadavg_state.last_nelem);
}

// Verifies that on success, GetLoadAverage returns the first element
// of the array provided by getloadavg().
TEST_F(GetLoadAverageTest_157, ReturnsFirstSampleOnSuccess_157) {
  const double kExpectedLoad = 1.23;
  g_fake_getloadavg_state.return_value = 3;  // Success with multiple samples.
  g_fake_getloadavg_state.sample0 = kExpectedLoad;

  double result = GetLoadAverage();

  EXPECT_DOUBLE_EQ(kExpectedLoad, result);
}

// Verifies that when getloadavg() indicates an error (negative return),
// GetLoadAverage returns -0.0 (negative zero).
TEST_F(GetLoadAverageTest_157, ReturnsNegativeZeroOnError_157) {
  g_fake_getloadavg_state.return_value = -1;  // Error.
  g_fake_getloadavg_state.sample0 = 42.0;     // Should be ignored on error.

  double result = GetLoadAverage();

  // Numerically equal to 0.0 …
  EXPECT_DOUBLE_EQ(0.0, result);
  // … but with a negative sign bit.
  EXPECT_TRUE(std::signbit(result));
}
