// File: poppler-structure-element-class-init-test-2518.cc
#include <gtest/gtest.h>

#include <glib-object.h>

// Include the implementation file to access the static function under test.
// This is a common unit-testing technique for file-local (static) functions.
#include "./TestProjects/poppler/glib/poppler-structure-element.cc"

namespace {

class PopplerStructureElementClassInitTest_2518 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Ensure GType/GObject is initialized for any GLib macros/types we touch.
    // (Safe to call multiple times; no-op on newer GLib.)
#if !GLIB_CHECK_VERSION(2, 36, 0)
    g_type_init();
#endif
  }
};

TEST_F(PopplerStructureElementClassInitTest_2518, SetsFinalizeToPopplerFinalize_2518) {
  // Arrange: use a real GObjectClass storage and treat it as PopplerStructureElementClass.
  GObjectClass gobject_class_storage;
  gobject_class_storage.finalize = nullptr;

  auto* klass =
      reinterpret_cast<PopplerStructureElementClass*>(&gobject_class_storage);

  // Act
  poppler_structure_element_class_init(klass);

  // Assert
  EXPECT_EQ(gobject_class_storage.finalize, poppler_structure_element_finalize);
}

TEST_F(PopplerStructureElementClassInitTest_2518, OverwritesExistingFinalizePointer_2518) {
  // Arrange
  GObjectClass gobject_class_storage;

  // Set an existing finalize pointer to ensure class_init overwrites it.
  gobject_class_storage.finalize = reinterpret_cast<GObjectFinalizeFunc>(+[] (GObject*) {});

  auto* klass =
      reinterpret_cast<PopplerStructureElementClass*>(&gobject_class_storage);

  // Act
  poppler_structure_element_class_init(klass);

  // Assert
  EXPECT_EQ(gobject_class_storage.finalize, poppler_structure_element_finalize);
}

TEST_F(PopplerStructureElementClassInitTest_2518, DiesOnNullKlass_2518) {
  // Exceptional/error case (observable): passing nullptr should crash due to dereference.
  ASSERT_DEATH(
      {
        poppler_structure_element_class_init(nullptr);
      },
      ".*");
}

}  // namespace