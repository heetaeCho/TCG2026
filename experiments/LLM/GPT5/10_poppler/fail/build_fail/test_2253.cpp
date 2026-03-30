// poppler-ps-file-class-init-test-2253.cc
//
// Unit tests for poppler_ps_file_class_init() from poppler-document.cc
// Constraints respected:
//  - Treat implementation as black box (no reimplementation of logic)
//  - Test only observable behavior via public/visible fields (GObjectClass vfunc pointers)
//  - No access to private/internal state beyond what the interface exposes

#include <gtest/gtest.h>

#include <glib-object.h>
#include <cstdlib>
#include <cstring>

// Include the implementation unit to access the static function under test.
// This is a common pattern for testing file-local (static) functions.
#include "TestProjects/poppler/glib/poppler-document.cc"

namespace {

class PopplerPSFileClassInitTest_2253 : public ::testing::Test {
protected:
  // Allocate a buffer that is certainly large enough to hold a GObjectClass at offset 0.
  // We then treat it as PopplerPSFileClass* so poppler_ps_file_class_init() can operate on it.
  static PopplerPSFileClass* AllocFakeKlass() {
    constexpr size_t kExtra = 256; // safety padding
    void* mem = std::calloc(1, sizeof(GObjectClass) + kExtra);
    return reinterpret_cast<PopplerPSFileClass*>(mem);
  }

  static void FreeFakeKlass(PopplerPSFileClass* klass) {
    std::free(reinterpret_cast<void*>(klass));
  }

  static void DummyDispose(GObject* /*object*/) {}
  static void DummyFinalize(GObject* /*object*/) {}
};

TEST_F(PopplerPSFileClassInitTest_2253, SetsFinalizeVFunc_2253) {
  PopplerPSFileClass* klass = AllocFakeKlass();
  ASSERT_NE(klass, nullptr);

  // Precondition: finalize is null in the zeroed buffer.
  GObjectClass* gobject_class_pre = G_OBJECT_CLASS(klass);
  ASSERT_NE(gobject_class_pre, nullptr);
  EXPECT_EQ(gobject_class_pre->finalize, nullptr);

  poppler_ps_file_class_init(klass);

  // Observable behavior: finalize vfunc is set to poppler_ps_file_finalize.
  GObjectClass* gobject_class_post = G_OBJECT_CLASS(klass);
  ASSERT_NE(gobject_class_post, nullptr);
  EXPECT_EQ(gobject_class_post->finalize, poppler_ps_file_finalize);

  FreeFakeKlass(klass);
}

TEST_F(PopplerPSFileClassInitTest_2253, DoesNotClobberOtherVFuncs_2253) {
  PopplerPSFileClass* klass = AllocFakeKlass();
  ASSERT_NE(klass, nullptr);

  GObjectClass* gobject_class = G_OBJECT_CLASS(klass);
  ASSERT_NE(gobject_class, nullptr);

  // Set other vfuncs to sentinels to verify they remain unchanged.
  gobject_class->dispose = &DummyDispose;
  gobject_class->finalize = &DummyFinalize; // will be overwritten by class_init

  poppler_ps_file_class_init(klass);

  EXPECT_EQ(gobject_class->finalize, poppler_ps_file_finalize);
  EXPECT_EQ(gobject_class->dispose, &DummyDispose); // class_init should not change this

  FreeFakeKlass(klass);
}

TEST_F(PopplerPSFileClassInitTest_2253, IdempotentWhenCalledMultipleTimes_2253) {
  PopplerPSFileClass* klass = AllocFakeKlass();
  ASSERT_NE(klass, nullptr);

  poppler_ps_file_class_init(klass);
  GObjectClass* gobject_class = G_OBJECT_CLASS(klass);
  ASSERT_NE(gobject_class, nullptr);
  auto first = gobject_class->finalize;

  // Call again; observable result should be stable.
  poppler_ps_file_class_init(klass);
  EXPECT_EQ(gobject_class->finalize, first);
  EXPECT_EQ(gobject_class->finalize, poppler_ps_file_finalize);

  FreeFakeKlass(klass);
}

#if GTEST_HAS_DEATH_TEST
TEST_F(PopplerPSFileClassInitTest_2253, NullKlassPointerDies_2253) {
  // If the implementation dereferences klass (likely via G_OBJECT_CLASS),
  // passing nullptr should be an observable error (process termination).
  // Guarded as a death test to avoid flakiness on platforms/builds without it.
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  EXPECT_DEATH({ poppler_ps_file_class_init(nullptr); }, ".*");
}
#endif

} // namespace