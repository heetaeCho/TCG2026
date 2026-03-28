#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler-form.h" // Include the header for the class you're testing

namespace Poppler {
  
// Test fixture class (if needed)
class PopplerFormTest_1376 : public ::testing::Test {
protected:
  // Setup and teardown methods if necessary
  void SetUp() override {
    // Any setup code goes here
  }

  void TearDown() override {
    // Any teardown code goes here
  }
};

// Test for hasNSSBackendFeature function for the BackendAsksPassphrase feature
TEST_F(PopplerFormTest_1376, hasNSSBackendFeature_BackendAsksPassphrase_1376) {
  EXPECT_FALSE(hasNSSBackendFeature(CryptoSignBackendFeature::BackendAsksPassphrase));
}

// Additional test cases can be added for other features if necessary, even though in the provided code, all features seem to return false.
TEST_F(PopplerFormTest_1376, hasNSSBackendFeature_UnknownFeature_1376) {
  // Using a feature not implemented in the switch case
  // Expecting false because all features return false based on the implementation.
  EXPECT_FALSE(hasNSSBackendFeature(static_cast<CryptoSignBackendFeature>(999)));
}

}  // namespace Poppler