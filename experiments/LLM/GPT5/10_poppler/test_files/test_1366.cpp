#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "CertificateInfo.h"

// Function under test: fromPopplerCore

namespace Poppler {

// Mock class for external dependencies if any
// If no external collaborator is needed, we can omit this section

class CertificateInfoTest_1366 : public ::testing::Test {
 protected:
  // Set up and Tear down can be implemented if necessary
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(CertificateInfoTest_1366, fromPopplerCore_ReturnsPGP_WhenTypeIsPGP_1366) {
  // Test case: when the input type is PGP, the function should return PGP
  CertificateType inputType = CertificateType::PGP;
  CertificateInfo::CertificateType result = fromPopplerCore(inputType);
  EXPECT_EQ(result, CertificateInfo::CertificateType::PGP);
}

TEST_F(CertificateInfoTest_1366, fromPopplerCore_ReturnsX509_WhenTypeIsX509_1366) {
  // Test case: when the input type is X509, the function should return X509
  CertificateType inputType = CertificateType::X509;
  CertificateInfo::CertificateType result = fromPopplerCore(inputType);
  EXPECT_EQ(result, CertificateInfo::CertificateType::X509);
}

TEST_F(CertificateInfoTest_1366, fromPopplerCore_ReturnsX509_WhenTypeIsInvalid_1366) {
  // Test case: when the input type is invalid, the function should return the fallback value (X509)
  // Since the function only recognizes PGP and X509, anything else should fallback to X509
  CertificateType inputType = static_cast<CertificateType>(-1);  // Invalid value
  CertificateInfo::CertificateType result = fromPopplerCore(inputType);
  EXPECT_EQ(result, CertificateInfo::CertificateType::X509);
}

}  // namespace Poppler