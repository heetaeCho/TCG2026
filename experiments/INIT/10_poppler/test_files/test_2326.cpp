// poppler_signature_info_free_test_2326.cc
#include <gtest/gtest.h>

#include <cstdlib>
#include <unordered_set>

// ---- Minimal types / declarations (based on provided snippet) ----
extern "C" {

typedef struct _PopplerCertificateInfo PopplerCertificateInfo;
typedef int PopplerCertificateStatus;

struct _PopplerCertificateInfo {
  int dummy;
};

typedef struct _PopplerSignatureInfo PopplerSignatureInfo;

struct _PopplerSignatureInfo {
public:
  int sig_status;
  PopplerCertificateStatus cert_status;
  char* signer_name;
  int* local_signing_time;                 // As provided (even though unref name suggests GDateTime*)
  PopplerCertificateInfo* certificate_info;
};

// Function under test (provided by the production object/library).
void poppler_signature_info_free(PopplerSignatureInfo* siginfo);

// Collaborators called by the function under test (we intercept these).
void g_date_time_unref(void* dt);
void g_free(void* p);
void poppler_certificate_info_free(PopplerCertificateInfo* certinfo);

}  // extern "C"

// ---- Interceptors / counters for external interactions ----
namespace {

struct CallCounters {
  int g_date_time_unref_calls = 0;
  int g_free_calls = 0;
  int poppler_certificate_info_free_calls = 0;

  std::unordered_set<void*> freed_ptrs;
  std::unordered_set<void*> unref_ptrs;
  std::unordered_set<void*> certfree_ptrs;

  void Reset() {
    g_date_time_unref_calls = 0;
    g_free_calls = 0;
    poppler_certificate_info_free_calls = 0;
    freed_ptrs.clear();
    unref_ptrs.clear();
    certfree_ptrs.clear();
  }
};

CallCounters& Counters() {
  static CallCounters c;
  return c;
}

}  // namespace

extern "C" {

// Intercept GLib free used by the function under test.
void g_free(void* p) {
  Counters().g_free_calls++;
  Counters().freed_ptrs.insert(p);
  std::free(p);  // free(nullptr) is OK
}

// Intercept the "unref" function.
void g_date_time_unref(void* dt) {
  Counters().g_date_time_unref_calls++;
  Counters().unref_ptrs.insert(dt);
  std::free(dt);  // safe for nullptr as well
}

// Intercept Poppler certificate free.
void poppler_certificate_info_free(PopplerCertificateInfo* certinfo) {
  Counters().poppler_certificate_info_free_calls++;
  Counters().certfree_ptrs.insert(certinfo);
  std::free(certinfo);  // free(nullptr) is OK
}

}  // extern "C"

// ---- Test fixture ----
class PopplerSignatureInfoFreeTest_2326 : public ::testing::Test {
protected:
  void SetUp() override { Counters().Reset(); }
  void TearDown() override { Counters().Reset(); }
};

// ---- Tests ----

TEST_F(PopplerSignatureInfoFreeTest_2326, NullptrDoesNothing_2326) {
  poppler_signature_info_free(nullptr);

  EXPECT_EQ(Counters().g_date_time_unref_calls, 0);
  EXPECT_EQ(Counters().poppler_certificate_info_free_calls, 0);
  EXPECT_EQ(Counters().g_free_calls, 0);
  EXPECT_TRUE(Counters().freed_ptrs.empty());
}

TEST_F(PopplerSignatureInfoFreeTest_2326, FreesStructAndUnrefsTime_WhenOptionalFieldsNull_2326) {
  // Arrange: allocate the main struct via malloc so our g_free(std::free) is compatible.
  auto* siginfo = static_cast<PopplerSignatureInfo*>(std::malloc(sizeof(PopplerSignatureInfo)));
  ASSERT_NE(siginfo, nullptr);

  siginfo->sig_status = 0;
  siginfo->cert_status = 0;

  // signer_name null and certificate_info null are boundary-ish inputs.
  siginfo->signer_name = nullptr;
  siginfo->certificate_info = nullptr;

  // Provide a non-null pointer for local_signing_time to avoid depending on null-handling.
  siginfo->local_signing_time = static_cast<int*>(std::malloc(sizeof(int)));
  ASSERT_NE(siginfo->local_signing_time, nullptr);
  *siginfo->local_signing_time = 123;

  void* const time_ptr = siginfo->local_signing_time;
  void* const struct_ptr = siginfo;

  // Act
  poppler_signature_info_free(siginfo);

  // Assert external interactions (observable via our interceptors)
  EXPECT_EQ(Counters().g_date_time_unref_calls, 1);
  EXPECT_TRUE(Counters().unref_ptrs.count(time_ptr));

  EXPECT_EQ(Counters().poppler_certificate_info_free_calls, 0);

  // g_free should be called for the struct itself; signer_name is nullptr (still a call in prod code,
  // but even if it is called, free(nullptr) is fine). We assert at least the struct pointer was freed.
  EXPECT_TRUE(Counters().freed_ptrs.count(struct_ptr));
  EXPECT_GE(Counters().g_free_calls, 1);
}

TEST_F(PopplerSignatureInfoFreeTest_2326, FreesSignerAndCertificateAndStruct_2326) {
  // Arrange
  auto* siginfo = static_cast<PopplerSignatureInfo*>(std::malloc(sizeof(PopplerSignatureInfo)));
  ASSERT_NE(siginfo, nullptr);

  siginfo->sig_status = 7;
  siginfo->cert_status = 42;

  // Allocate signer_name (as raw bytes) so our g_free(std::free) can free it.
  const char kName[] = "Signer";
  siginfo->signer_name = static_cast<char*>(std::malloc(sizeof(kName)));
  ASSERT_NE(siginfo->signer_name, nullptr);
  std::memcpy(siginfo->signer_name, kName, sizeof(kName));

  siginfo->local_signing_time = static_cast<int*>(std::malloc(sizeof(int)));
  ASSERT_NE(siginfo->local_signing_time, nullptr);
  *siginfo->local_signing_time = 999;

  siginfo->certificate_info =
      static_cast<PopplerCertificateInfo*>(std::malloc(sizeof(PopplerCertificateInfo)));
  ASSERT_NE(siginfo->certificate_info, nullptr);
  siginfo->certificate_info->dummy = 1;

  void* const name_ptr = siginfo->signer_name;
  void* const time_ptr = siginfo->local_signing_time;
  void* const cert_ptr = siginfo->certificate_info;
  void* const struct_ptr = siginfo;

  // Act
  poppler_signature_info_free(siginfo);

  // Assert collaborator calls and parameters
  EXPECT_EQ(Counters().g_date_time_unref_calls, 1);
  EXPECT_TRUE(Counters().unref_ptrs.count(time_ptr));

  EXPECT_EQ(Counters().poppler_certificate_info_free_calls, 1);
  EXPECT_TRUE(Counters().certfree_ptrs.count(cert_ptr));

  // g_free should include signer_name and the struct itself.
  EXPECT_TRUE(Counters().freed_ptrs.count(name_ptr));
  EXPECT_TRUE(Counters().freed_ptrs.count(struct_ptr));

  // Total g_free calls should be at least 2 (name + struct). If production code also g_free(nullptr)
  // in other scenarios, this remains robust.
  EXPECT_GE(Counters().g_free_calls, 2);
}

TEST_F(PopplerSignatureInfoFreeTest_2326, HandlesEmptySignerNameString_2326) {
  // Boundary: signer_name points to an empty C-string (still non-null).
  auto* siginfo = static_cast<PopplerSignatureInfo*>(std::malloc(sizeof(PopplerSignatureInfo)));
  ASSERT_NE(siginfo, nullptr);

  siginfo->sig_status = 0;
  siginfo->cert_status = 0;

  siginfo->signer_name = static_cast<char*>(std::malloc(1));
  ASSERT_NE(siginfo->signer_name, nullptr);
  siginfo->signer_name[0] = '\0';

  siginfo->local_signing_time = static_cast<int*>(std::malloc(sizeof(int)));
  ASSERT_NE(siginfo->local_signing_time, nullptr);
  *siginfo->local_signing_time = 0;

  siginfo->certificate_info = nullptr;

  void* const name_ptr = siginfo->signer_name;
  void* const time_ptr = siginfo->local_signing_time;
  void* const struct_ptr = siginfo;

  poppler_signature_info_free(siginfo);

  EXPECT_EQ(Counters().g_date_time_unref_calls, 1);
  EXPECT_TRUE(Counters().unref_ptrs.count(time_ptr));

  EXPECT_EQ(Counters().poppler_certificate_info_free_calls, 0);

  EXPECT_TRUE(Counters().freed_ptrs.count(name_ptr));
  EXPECT_TRUE(Counters().freed_ptrs.count(struct_ptr));
  EXPECT_GE(Counters().g_free_calls, 2);
}