// poppler-get-available-signing-certificates-test.cc
//
// Unit tests for:
//   GList *poppler_get_available_signing_certificates(void)
//
// TEST_ID: 2407
//
// Notes:
// - These tests treat the implementation as a black box.
// - We only verify observable behavior via the public function return value.
// - We use Google Mock only to mock the external collaborator (CryptoSign backend).
//
// Important build assumption (common in C/C++ unit-test seams):
// - CryptoSign::Factory::createActive() is link-seam overridable (or weak), so the test can
//   provide its own definition to return a mock backend.
// If your build does not allow this, keep the test logic but adapt the seam (e.g. --wrap,
//   dependency injection hook, or a test-only factory setter if your tree provides one).

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <glib.h>

#include <memory>
#include <utility>
#include <vector>

// Include the header that declares poppler_get_available_signing_certificates().
#include "poppler-form-field.h"

// These headers may vary by Poppler tree/layout. If your build fails here,
// include the correct internal headers that declare CryptoSign and X509CertificateInfo.
#include "CryptoSign.h"
#include "X509CertificateInfo.h"

using ::testing::Return;
using ::testing::StrictMock;

// -------------------------
// Mock backend + factory seam
// -------------------------

namespace {

class MockCryptoSignBackend final : public CryptoSign {
public:
  MOCK_METHOD(std::vector<std::unique_ptr<X509CertificateInfo>>,
              getAvailableSigningCertificates,
              (),
              (override));
};

// Global pointer used by the factory seam. Tests set/clear this.
MockCryptoSignBackend *g_mock_backend = nullptr;

} // namespace

// Link-seam override for the factory method used by the SUT.
// If your project defines this symbol as non-overridable, adapt with your build’s
// wrapping/interposition mechanism.
namespace CryptoSign::Factory {
std::unique_ptr<CryptoSign> createActive()
{
  if (!g_mock_backend) {
    return nullptr;
  }
  // Transfer ownership to caller; tests keep the raw pointer for expectation setting.
  // The unique_ptr will delete it at end of SUT call.
  return std::unique_ptr<CryptoSign>(g_mock_backend);
}
} // namespace CryptoSign::Factory

namespace {

class PopplerGetAvailableSigningCertificatesTest_2407 : public ::testing::Test {
protected:
  void TearDown() override
  {
    // Ensure we don't leave dangling state between tests.
    g_mock_backend = nullptr;
  }

  // Helper: free the GList nodes. We do not assume element ownership semantics here.
  // If PopplerCertificateInfo elements are GObjects in your tree, consider:
  //   g_list_free_full(list, (GDestroyNotify)g_object_unref);
  // but we keep it conservative and only free the list container.
  static void FreeListContainerOnly(GList *list)
  {
    if (list) {
      g_list_free(list);
    }
  }
};

TEST_F(PopplerGetAvailableSigningCertificatesTest_2407, ReturnsNullWhenBackendUnavailable_2407)
{
  // Arrange: factory returns nullptr (no active backend)
  g_mock_backend = nullptr;

  // Act
  GList *list = poppler_get_available_signing_certificates();

  // Assert
  EXPECT_EQ(list, nullptr);
}

TEST_F(PopplerGetAvailableSigningCertificatesTest_2407, ReturnsNullWhenBackendReturnsEmptyVector_2407)
{
  // Arrange
  auto *backend = new StrictMock<MockCryptoSignBackend>();
  g_mock_backend = backend;

  EXPECT_CALL(*backend, getAvailableSigningCertificates()).WillOnce(Return(std::vector<std::unique_ptr<X509CertificateInfo>>{}));

  // Act
  GList *list = poppler_get_available_signing_certificates();

  // Assert: implementation starts list as nullptr and appends none => observable nullptr.
  EXPECT_EQ(list, nullptr);
}

TEST_F(PopplerGetAvailableSigningCertificatesTest_2407, ReturnsListWithSameLengthAsReturnedCertificates_2407)
{
  // Arrange
  auto *backend = new StrictMock<MockCryptoSignBackend>();
  g_mock_backend = backend;

  std::vector<std::unique_ptr<X509CertificateInfo>> certs;
  // We only need distinct, valid objects. Use default constructor if available.
  // If X509CertificateInfo requires specific construction in your tree,
  // replace these with the appropriate test constructors/helpers.
  certs.emplace_back(std::make_unique<X509CertificateInfo>());
  certs.emplace_back(std::make_unique<X509CertificateInfo>());
  certs.emplace_back(std::make_unique<X509CertificateInfo>());

  EXPECT_CALL(*backend, getAvailableSigningCertificates()).WillOnce(Return(::testing::ByMove(std::move(certs))));

  // Act
  GList *list = poppler_get_available_signing_certificates();

  // Assert
  ASSERT_NE(list, nullptr);
  EXPECT_EQ(g_list_length(list), 3);

  // Basic sanity: list entries should be non-null pointers.
  for (GList *it = list; it != nullptr; it = it->next) {
    EXPECT_NE(it->data, nullptr);
  }

  FreeListContainerOnly(list);
}

TEST_F(PopplerGetAvailableSigningCertificatesTest_2407, BoundarySingleCertificateProducesSingleNodeList_2407)
{
  // Arrange
  auto *backend = new StrictMock<MockCryptoSignBackend>();
  g_mock_backend = backend;

  std::vector<std::unique_ptr<X509CertificateInfo>> certs;
  certs.emplace_back(std::make_unique<X509CertificateInfo>());

  EXPECT_CALL(*backend, getAvailableSigningCertificates()).WillOnce(Return(::testing::ByMove(std::move(certs))));

  // Act
  GList *list = poppler_get_available_signing_certificates();

  // Assert
  ASSERT_NE(list, nullptr);
  EXPECT_EQ(g_list_length(list), 1);
  EXPECT_NE(list->data, nullptr);
  EXPECT_EQ(list->next, nullptr);

  FreeListContainerOnly(list);
}

} // namespace