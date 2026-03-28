// get_available_signing_certificates_test_2684.cc
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <utility>
#include <vector>

// Ensure NSS code path is not required for these unit tests unless the build enables it.
#ifndef ENABLE_NSS3
#define ENABLE_NSS3 0
#endif

// ---- Minimal collaborator stubs/mocks to let pdfsig.cc compile and to observe interactions ----

struct X509CertificateInfo {
  virtual ~X509CertificateInfo() = default;
};

// A trivial concrete cert type for creating unique_ptr<X509CertificateInfo>.
struct DummyCert final : public X509CertificateInfo {
  explicit DummyCert(int idIn) : id(idIn) {}
  int id;
};

namespace CryptoSign {

class Backend {
public:
  virtual ~Backend() = default;
  virtual std::vector<std::unique_ptr<X509CertificateInfo>> getAvailableSigningCertificates() = 0;
};

class Factory {
public:
  static std::unique_ptr<Backend> createActive();
};

} // namespace CryptoSign

// Global controls for our fake factory behavior & observability.
namespace {
std::unique_ptr<CryptoSign::Backend> g_nextBackend;
int g_createActiveCalls = 0;

void ResetFactoryState() {
  g_nextBackend.reset();
  g_createActiveCalls = 0;
}

// Fake Factory::createActive definition (used by pdfsig.cc when compiled into this TU).
std::unique_ptr<CryptoSign::Backend> CryptoSign::Factory::createActive() {
  ++g_createActiveCalls;
  return std::move(g_nextBackend);
}

class MockBackend final : public CryptoSign::Backend {
public:
  MOCK_METHOD(std::vector<std::unique_ptr<X509CertificateInfo>>, getAvailableSigningCertificates, (), (override));
};

} // namespace

// ---- Include the production implementation so we can call the static function (black-box) ----
// NOTE: This is intentionally included (not reimplemented) to access the TU-local static function.
#include "TestProjects/poppler/utils/pdfsig.cc"

// ---- Tests ----

class GetAvailableSigningCertificatesTest_2684 : public ::testing::Test {
protected:
  void SetUp() override { ResetFactoryState(); }
  void TearDown() override { ResetFactoryState(); }
};

TEST_F(GetAvailableSigningCertificatesTest_2684,
       NoBackendSetsErrorReturnsEmptyAndPrintsMessage_2684) {
  bool error = false;
  g_nextBackend.reset(); // Factory returns nullptr.

  testing::internal::CaptureStdout();
  auto certs = getAvailableSigningCertificates(&error);
  const std::string out = testing::internal::GetCapturedStdout();

  EXPECT_TRUE(error);
  EXPECT_TRUE(certs.empty());
  EXPECT_THAT(out, testing::HasSubstr("No backends for cryptographic signatures available"));
  EXPECT_EQ(g_createActiveCalls, 1);
}

TEST_F(GetAvailableSigningCertificatesTest_2684,
       BackendReturnsTwoCertsClearsErrorAndCallsBackendOnce_2684) {
  bool error = true; // ensure it gets overwritten on success.

  auto mock = std::make_unique<MockBackend>();
  MockBackend* mockPtr = mock.get();

  std::vector<std::unique_ptr<X509CertificateInfo>> produced;
  produced.emplace_back(std::make_unique<DummyCert>(1));
  produced.emplace_back(std::make_unique<DummyCert>(2));

  EXPECT_CALL(*mockPtr, getAvailableSigningCertificates())
      .Times(1)
      .WillOnce(::testing::Return(ByMove(std::move(produced))));

  g_nextBackend = std::move(mock);

  testing::internal::CaptureStdout();
  auto certs = getAvailableSigningCertificates(&error);
  const std::string out = testing::internal::GetCapturedStdout();

  EXPECT_FALSE(error);
  EXPECT_EQ(certs.size(), 2u);
  EXPECT_TRUE(out.empty()); // no error message expected on success path
  EXPECT_EQ(g_createActiveCalls, 1);
}

TEST_F(GetAvailableSigningCertificatesTest_2684,
       BackendReturnsEmptyVectorStillClearsError_2684) {
  bool error = true;

  auto mock = std::make_unique<MockBackend>();
  MockBackend* mockPtr = mock.get();

  std::vector<std::unique_ptr<X509CertificateInfo>> produced; // empty
  EXPECT_CALL(*mockPtr, getAvailableSigningCertificates())
      .Times(1)
      .WillOnce(::testing::Return(ByMove(std::move(produced))));

  g_nextBackend = std::move(mock);

  auto certs = getAvailableSigningCertificates(&error);

  EXPECT_FALSE(error);
  EXPECT_TRUE(certs.empty());
  EXPECT_EQ(g_createActiveCalls, 1);
}

TEST_F(GetAvailableSigningCertificatesTest_2684,
       MultipleCallsOverwriteErrorAndInvokeFactoryEachTime_2684) {
  bool error = false;

  // 1st call: nullptr backend -> error true
  g_nextBackend.reset();
  auto certs1 = getAvailableSigningCertificates(&error);
  EXPECT_TRUE(error);
  EXPECT_TRUE(certs1.empty());

  // 2nd call: backend -> error false
  auto mock = std::make_unique<MockBackend>();
  MockBackend* mockPtr = mock.get();

  std::vector<std::unique_ptr<X509CertificateInfo>> produced;
  produced.emplace_back(std::make_unique<DummyCert>(7));
  EXPECT_CALL(*mockPtr, getAvailableSigningCertificates())
      .Times(1)
      .WillOnce(::testing::Return(ByMove(std::move(produced))));
  g_nextBackend = std::move(mock);

  auto certs2 = getAvailableSigningCertificates(&error);
  EXPECT_FALSE(error);
  EXPECT_EQ(certs2.size(), 1u);

  EXPECT_EQ(g_createActiveCalls, 2);
}

#if GTEST_HAS_DEATH_TEST
TEST_F(GetAvailableSigningCertificatesTest_2684,
       NullErrorPointerCausesDeath_2684) {
  // Regardless of backend availability, dereferencing a null error pointer is observable as a crash.
  g_nextBackend.reset(); // also exercises the path that writes to *error early
  ASSERT_DEATH(
      {
        (void)getAvailableSigningCertificates(nullptr);
      },
      ".*");
}
#endif