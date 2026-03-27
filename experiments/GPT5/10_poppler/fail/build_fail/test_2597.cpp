// poppler-get-backend-test-2597.cc
#include <gtest/gtest.h>

#include "poppler.h"

// NOTE:
// - Treat poppler_get_backend() as a black box: we only assert observable behavior.
// - No mocking needed: function has no parameters/collaborators.

namespace {

class PopplerGetBackendTest_2597 : public ::testing::Test {};

TEST_F(PopplerGetBackendTest_2597, ReturnsKnownEnumValue_2597) {
  const PopplerBackend backend = poppler_get_backend();

  // Boundary/validity: backend should be one of the defined enum constants.
  EXPECT_TRUE(backend == POPPLER_BACKEND_UNKNOWN || backend == POPPLER_BACKEND_SPLASH ||
              backend == POPPLER_BACKEND_CAIRO);
}

TEST_F(PopplerGetBackendTest_2597, ReturnsCairoBackend_2597) {
  // Normal operation: current build is expected to report CAIRO backend.
  EXPECT_EQ(poppler_get_backend(), POPPLER_BACKEND_CAIRO);
}

TEST_F(PopplerGetBackendTest_2597, IsDeterministicAcrossMultipleCalls_2597) {
  // Boundary-ish: repeated calls should be stable (no observable state changes).
  const PopplerBackend first = poppler_get_backend();
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(poppler_get_backend(), first);
  }
}

TEST_F(PopplerGetBackendTest_2597, DoesNotReturnUnknownOrSplash_2597) {
  // Error/exceptional (observable): verify it is not returning other known backends.
  const PopplerBackend backend = poppler_get_backend();
  EXPECT_NE(backend, POPPLER_BACKEND_UNKNOWN);
  EXPECT_NE(backend, POPPLER_BACKEND_SPLASH);
}

}  // namespace