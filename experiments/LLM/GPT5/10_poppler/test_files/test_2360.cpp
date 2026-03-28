// File: poppler-form-field-signing-data-page-test-2360.cc

#include <gtest/gtest.h>

#include <glib.h>
#include <limits.h>

extern "C" {

// Prefer the public Poppler GLib header if available in the build.
#if __has_include(<poppler.h>)
#include <poppler.h>
#elif __has_include(<poppler/glib/poppler.h>)
#include <poppler/glib/poppler.h>
#elif __has_include("poppler.h")
#include "poppler.h"
#endif

// Function under test (implemented in poppler-form-field.cc).
void poppler_signing_data_set_page(PopplerSigningData *signing_data, int page);

}  // extern "C"

namespace {

class PopplerSigningDataTest_2360 : public ::testing::Test {
 protected:
  void SetUp() override {
    data_ = static_cast<PopplerSigningData *>(g_malloc0(sizeof(PopplerSigningData)));
    ASSERT_NE(data_, nullptr);
    // Ensure a known initial value.
    data_->page = 7;
  }

  void TearDown() override {
    if (data_) {
      g_free(data_);
      data_ = nullptr;
    }
  }

  PopplerSigningData *data_ = nullptr;
};

TEST_F(PopplerSigningDataTest_2360, NullSigningDataEmitsCritical_2360) {
  // g_return_if_fail() logs a CRITICAL and returns.
  g_test_expect_message(G_LOG_DOMAIN, G_LOG_LEVEL_CRITICAL, "*signing_data != NULL*");
  poppler_signing_data_set_page(nullptr, 1);
  g_test_assert_expected_messages();
}

TEST_F(PopplerSigningDataTest_2360, NegativePageDoesNotChangeExistingPage_2360) {
  ASSERT_EQ(data_->page, 7);
  poppler_signing_data_set_page(data_, -1);
  EXPECT_EQ(data_->page, 7);
}

TEST_F(PopplerSigningDataTest_2360, ZeroPageIsAcceptedAndSetsPage_2360) {
  poppler_signing_data_set_page(data_, 0);
  EXPECT_EQ(data_->page, 0);
}

TEST_F(PopplerSigningDataTest_2360, PositivePageSetsPage_2360) {
  poppler_signing_data_set_page(data_, 12);
  EXPECT_EQ(data_->page, 12);
}

TEST_F(PopplerSigningDataTest_2360, LargePageValueSetsPage_2360) {
  poppler_signing_data_set_page(data_, INT_MAX);
  EXPECT_EQ(data_->page, INT_MAX);
}

TEST_F(PopplerSigningDataTest_2360, MultipleCallsUpdatePageAndIgnoreNegative_2360) {
  poppler_signing_data_set_page(data_, 3);
  EXPECT_EQ(data_->page, 3);

  poppler_signing_data_set_page(data_, 4);
  EXPECT_EQ(data_->page, 4);

  // Negative should be ignored (page remains unchanged).
  poppler_signing_data_set_page(data_, -123);
  EXPECT_EQ(data_->page, 4);

  poppler_signing_data_set_page(data_, 9);
  EXPECT_EQ(data_->page, 9);
}

}  // namespace

int main(int argc, char **argv) {
  // Initialize GLib testing framework so g_test_expect_message works reliably.
  g_test_init(&argc, &argv, nullptr);

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}