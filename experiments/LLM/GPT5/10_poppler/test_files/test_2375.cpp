// Copyright 2026
#include <gtest/gtest.h>

#include <glib.h>

#include "poppler-form-field.h"

// The function under test (from poppler-form-field.cc):
// const PopplerColor *poppler_signing_data_get_border_color(const PopplerSigningData *signing_data);

namespace {

class PopplerSigningDataBorderColorTest_2375 : public ::testing::Test {
protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(PopplerSigningDataBorderColorTest_2375, NullSigningDataReturnsNull_2375) {
  const PopplerColor* color = poppler_signing_data_get_border_color(nullptr);
  EXPECT_EQ(color, nullptr);
}

TEST_F(PopplerSigningDataBorderColorTest_2375, ReturnsNonNullPointerForValidObject_2375) {
  PopplerSigningData signing_data{};
  const PopplerColor* color = poppler_signing_data_get_border_color(&signing_data);
  EXPECT_NE(color, nullptr);
}

TEST_F(PopplerSigningDataBorderColorTest_2375, ReturnedPointerIsStableAcrossMultipleCalls_2375) {
  PopplerSigningData signing_data{};
  const PopplerColor* c1 = poppler_signing_data_get_border_color(&signing_data);
  const PopplerColor* c2 = poppler_signing_data_get_border_color(&signing_data);

  ASSERT_NE(c1, nullptr);
  ASSERT_NE(c2, nullptr);
  EXPECT_EQ(c1, c2);
}

TEST_F(PopplerSigningDataBorderColorTest_2375, ReturnedPointerDiffersForDifferentObjects_2375) {
  PopplerSigningData signing_data1{};
  PopplerSigningData signing_data2{};

  const PopplerColor* c1 = poppler_signing_data_get_border_color(&signing_data1);
  const PopplerColor* c2 = poppler_signing_data_get_border_color(&signing_data2);

  ASSERT_NE(c1, nullptr);
  ASSERT_NE(c2, nullptr);

  // Boundary-ish: ensure we aren't accidentally returning a process-global pointer.
  EXPECT_NE(c1, c2);
}

TEST_F(PopplerSigningDataBorderColorTest_2375, ReturnedPointerReflectsUnderlyingStructMutation_2375) {
  PopplerSigningData signing_data{};
  const PopplerColor* c1 = poppler_signing_data_get_border_color(&signing_data);
  ASSERT_NE(c1, nullptr);

  // Mutate through the owning object and ensure the returned pointer still refers to the same storage.
  // (We do not assume any specific component names beyond the struct layout implied by the API.)
  signing_data.border_color = PopplerColor{0u, 0u, 0u};

  const PopplerColor* c2 = poppler_signing_data_get_border_color(&signing_data);
  ASSERT_NE(c2, nullptr);
  EXPECT_EQ(c1, c2);
}

}  // namespace