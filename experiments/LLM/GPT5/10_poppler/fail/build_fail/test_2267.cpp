// poppler_attachment_init_test_2267.cc
//
// Unit tests for poppler_attachment_init() (static function in poppler-attachment.cc).
// We include the .cc directly to access the static symbol, and provide a small,
// test-only GET_PRIVATE + private storage harness to make the observable effect testable.

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <mutex>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

// Include the public header (as provided by the project).
#include "./TestProjects/poppler/glib/poppler-attachment.h"

// The production .cc uses GET_PRIVATE(attachment) and PopplerAttachmentPrivate.
// In real builds these come from Poppler's GLib/GObject private-data plumbing.
// For this unit test, we provide a minimal test harness for both so that:
//  - GET_PRIVATE returns a stable, per-instance aligned buffer
//  - PopplerAttachmentPrivate constructor writes a sentinel that we can assert on

namespace poppler_attachment_init_test_2267 {

struct PrivateState2267 {
  // Sentinel that the ctor will set, so we can assert that placement-new ran.
  uint32_t magic = 0;
  uint32_t ctor_seq = 0;
};

static constexpr uint32_t kMagic2267 = 0x226700D1u;

// This class name must match what poppler-attachment.cc uses.
class PopplerAttachmentPrivate {
public:
  PopplerAttachmentPrivate() {
    ++CtorCount();
    // Write into the associated PrivateState via TLS "current construction target".
    // This is test harness only; it makes ctor-effects observable without reading
    // any private fields from PopplerAttachment itself.
    auto* st = CurrentStatePtr();
    if (st) {
      st->magic = kMagic2267;
      st->ctor_seq = CtorCount();
    }
  }

  static uint32_t& CtorCount() {
    static uint32_t count = 0;
    return count;
  }

  static PrivateState2267*& CurrentStatePtr() {
    static thread_local PrivateState2267* ptr = nullptr;
    return ptr;
  }
};

// Per-attachment storage record: aligned bytes + a sidecar state block.
struct PerAttachmentStorage2267 {
  std::aligned_storage_t<sizeof(PopplerAttachmentPrivate), alignof(PopplerAttachmentPrivate)> buf;
  PrivateState2267 state;
};

static std::mutex& StorageMutex2267() {
  static std::mutex m;
  return m;
}

static std::unordered_map<PopplerAttachment*, PerAttachmentStorage2267>& StorageMap2267() {
  static std::unordered_map<PopplerAttachment*, PerAttachmentStorage2267> m;
  return m;
}

static void ResetHarness2267() {
  std::lock_guard<std::mutex> lock(StorageMutex2267());
  StorageMap2267().clear();
  PopplerAttachmentPrivate::CtorCount() = 0;
}

// Returns the aligned buffer pointer used by placement-new, and sets TLS so the ctor
// can update the correct state record.
static void* GetPrivateBuffer2267(PopplerAttachment* attachment) {
  std::lock_guard<std::mutex> lock(StorageMutex2267());
  auto& rec = StorageMap2267()[attachment];  // creates if absent
  PopplerAttachmentPrivate::CurrentStatePtr() = &rec.state;
  return &rec.buf;
}

static PrivateState2267 ReadState2267(PopplerAttachment* attachment) {
  std::lock_guard<std::mutex> lock(StorageMutex2267());
  auto it = StorageMap2267().find(attachment);
  if (it == StorageMap2267().end()) {
    return PrivateState2267{};
  }
  return it->second.state;
}

}  // namespace poppler_attachment_init_test_2267

// Provide GET_PRIVATE macro expected by the .cc file.
// If the production build already defines GET_PRIVATE before including this test,
// we do not override it.
#ifndef GET_PRIVATE
#define GET_PRIVATE(obj) ::poppler_attachment_init_test_2267::GetPrivateBuffer2267(reinterpret_cast<PopplerAttachment*>(obj))
#endif

// Include the .cc under test to get access to the static function.
#include "./TestProjects/poppler/glib/poppler-attachment.cc"

namespace poppler_attachment_init_test_2267 {

class PopplerAttachmentInitTest_2267 : public ::testing::Test {
protected:
  void SetUp() override { ResetHarness2267(); }
  void TearDown() override { ResetHarness2267(); }
};

TEST_F(PopplerAttachmentInitTest_2267, InitConstructsPrivateInProvidedStorage_2267) {
  PopplerAttachment attachment{};
  // Ensure state is default before init (no magic).
  auto before = ReadState2267(&attachment);
  EXPECT_NE(before.magic, kMagic2267);
  EXPECT_EQ(before.ctor_seq, 0u);

  // Call the function under test.
  poppler_attachment_init(&attachment);

  // Verify constructor ran and wrote sentinel.
  auto after = ReadState2267(&attachment);
  EXPECT_EQ(after.magic, kMagic2267);
  EXPECT_EQ(after.ctor_seq, 1u);
  EXPECT_EQ(PopplerAttachmentPrivate::CtorCount(), 1u);
}

TEST_F(PopplerAttachmentInitTest_2267, InitOnSameObjectTwiceConstructsTwice_2267) {
  PopplerAttachment attachment{};

  poppler_attachment_init(&attachment);
  auto after1 = ReadState2267(&attachment);
  EXPECT_EQ(after1.magic, kMagic2267);
  EXPECT_EQ(after1.ctor_seq, 1u);

  poppler_attachment_init(&attachment);
  auto after2 = ReadState2267(&attachment);
  EXPECT_EQ(after2.magic, kMagic2267);
  EXPECT_EQ(after2.ctor_seq, 2u);

  EXPECT_EQ(PopplerAttachmentPrivate::CtorCount(), 2u);
}

TEST_F(PopplerAttachmentInitTest_2267, InitOnMultipleObjectsUsesIndependentStorage_2267) {
  PopplerAttachment a{};
  PopplerAttachment b{};
  PopplerAttachment c{};

  poppler_attachment_init(&a);
  poppler_attachment_init(&b);
  poppler_attachment_init(&c);

  auto sa = ReadState2267(&a);
  auto sb = ReadState2267(&b);
  auto sc = ReadState2267(&c);

  EXPECT_EQ(sa.magic, kMagic2267);
  EXPECT_EQ(sb.magic, kMagic2267);
  EXPECT_EQ(sc.magic, kMagic2267);

  // Each should have observed increasing ctor sequence numbers.
  EXPECT_EQ(sa.ctor_seq, 1u);
  EXPECT_EQ(sb.ctor_seq, 2u);
  EXPECT_EQ(sc.ctor_seq, 3u);

  EXPECT_EQ(PopplerAttachmentPrivate::CtorCount(), 3u);
}

TEST_F(PopplerAttachmentInitTest_2267, BoundaryManyAttachmentsAllInitialized_2267) {
  constexpr int kN = 128;
  std::vector<PopplerAttachment> attachments(static_cast<size_t>(kN));

  for (int i = 0; i < kN; ++i) {
    poppler_attachment_init(&attachments[static_cast<size_t>(i)]);
  }

  EXPECT_EQ(PopplerAttachmentPrivate::CtorCount(), static_cast<uint32_t>(kN));

  for (int i = 0; i < kN; ++i) {
    auto st = ReadState2267(&attachments[static_cast<size_t>(i)]);
    EXPECT_EQ(st.magic, kMagic2267);
    EXPECT_NE(st.ctor_seq, 0u);
  }
}

#if GTEST_HAS_DEATH_TEST
TEST_F(PopplerAttachmentInitTest_2267, InitWithNullptrDies_2267) {
  // The implementation dereferences the pointer via GET_PRIVATE(attachment),
  // so nullptr is expected to be an error case (observable as process death).
  ASSERT_DEATH({ poppler_attachment_init(nullptr); }, "");
}
#endif

}  // namespace poppler_attachment_init_test_2267