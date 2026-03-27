// poppler-layer-test-2506.cc
#include <gtest/gtest.h>

#include <glib-object.h>

// Include the implementation file to access internal static functions for testing.
// This keeps the tests based on observable effects of the provided interface.
#include "TestProjects/poppler/glib/poppler-layer.cc"

namespace {

void DummyFinalize(GObject* /*object*/) {
  // No-op dummy finalize used to ensure poppler_layer_class_init overwrites it.
}

class PopplerLayerClassInitTest_2506 : public ::testing::Test {
 protected:
  PopplerLayerClassInitTest_2506() {
    // Ensure the memory is zeroed like a typical class init scenario.
    std::memset(&klass_, 0, sizeof(klass_));
  }

  PopplerLayerClass klass_;
};

TEST_F(PopplerLayerClassInitTest_2506, SetsFinalizeToPopplerLayerFinalize_2506) {
  GObjectClass* gobject_class = G_OBJECT_CLASS(&klass_);
  ASSERT_NE(gobject_class, nullptr);

  gobject_class->finalize = &DummyFinalize;
  ASSERT_EQ(gobject_class->finalize, &DummyFinalize);

  poppler_layer_class_init(&klass_);

  // Observable effect: finalize function pointer is set to poppler_layer_finalize.
  EXPECT_EQ(gobject_class->finalize, poppler_layer_finalize);
  EXPECT_NE(gobject_class->finalize, &DummyFinalize);
}

TEST_F(PopplerLayerClassInitTest_2506, OverwritesExistingFinalizePointer_2506) {
  GObjectClass* gobject_class = G_OBJECT_CLASS(&klass_);
  ASSERT_NE(gobject_class, nullptr);

  // Set to something else first.
  gobject_class->finalize = &DummyFinalize;

  poppler_layer_class_init(&klass_);
  EXPECT_EQ(gobject_class->finalize, poppler_layer_finalize);

  // Change it again to ensure calling class_init overwrites again.
  gobject_class->finalize = &DummyFinalize;
  ASSERT_EQ(gobject_class->finalize, &DummyFinalize);

  poppler_layer_class_init(&klass_);
  EXPECT_EQ(gobject_class->finalize, poppler_layer_finalize);
}

TEST_F(PopplerLayerClassInitTest_2506, IdempotentWhenCalledMultipleTimes_2506) {
  GObjectClass* gobject_class = G_OBJECT_CLASS(&klass_);
  ASSERT_NE(gobject_class, nullptr);

  poppler_layer_class_init(&klass_);
  auto* first = gobject_class->finalize;
  EXPECT_EQ(first, poppler_layer_finalize);

  poppler_layer_class_init(&klass_);
  auto* second = gobject_class->finalize;

  // Observable effect: remains set to the same finalize function.
  EXPECT_EQ(second, poppler_layer_finalize);
  EXPECT_EQ(first, second);
}

}  // namespace