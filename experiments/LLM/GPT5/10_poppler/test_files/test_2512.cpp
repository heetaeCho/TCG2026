// poppler-layer-is-parent-test.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

#include <poppler.h>

// Access to struct _PopplerLayer fields (layer, rbgroup)
#include "poppler-private.h"

// Try to find a header that defines `Layer` (used by PopplerLayer::layer).
#if defined(__has_include)
#  if __has_include("Layer.h")
#    include "Layer.h"
#    define POPPLER_TEST_HAS_LAYER_DEF 1
#  elif __has_include("OptionalContent.h")
#    include "OptionalContent.h"
#    define POPPLER_TEST_HAS_LAYER_DEF 1
#  elif __has_include(<poppler/OptionalContent.h>)
#    include <poppler/OptionalContent.h>
#    define POPPLER_TEST_HAS_LAYER_DEF 1
#  endif
#endif

namespace {

class PopplerLayerIsParentTest_2512 : public ::testing::Test {
 protected:
  static void ExpectCriticalMessage_(const char* pattern) {
    // g_return_val_if_fail emits a critical log. Domain may vary; NULL matches any domain in GLib tests.
    g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, pattern);
  }
};

TEST_F(PopplerLayerIsParentTest_2512, NullptrReturnsFalse_2512) {
  ExpectCriticalMessage_("*poppler_layer_is_parent*");
  EXPECT_FALSE(poppler_layer_is_parent(nullptr));
  g_test_assert_expected_messages();
}

TEST_F(PopplerLayerIsParentTest_2512, NonLayerGObjectReturnsFalse_2512) {
  // Pass a valid GObject that is not a PopplerLayer; the type check should fail.
  GObject* not_a_layer = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(not_a_layer, nullptr);

  ExpectCriticalMessage_("*POPPLER_IS_LAYER*");
  EXPECT_FALSE(poppler_layer_is_parent(reinterpret_cast<PopplerLayer*>(not_a_layer)));
  g_test_assert_expected_messages();

  g_object_unref(not_a_layer);
}

#if defined(POPPLER_TEST_HAS_LAYER_DEF) && POPPLER_TEST_HAS_LAYER_DEF
// Detect that Layer has a member named `kids` that is comparable to nullptr.
template <typename T, typename = void>
struct HasKidsMember : std::false_type {};
template <typename T>
struct HasKidsMember<T, std::void_t<decltype(std::declval<T&>().kids)>> : std::true_type {};

template <typename T, typename = void>
struct KidsIsNullablePtr : std::false_type {};
template <typename T>
struct KidsIsNullablePtr<T, std::void_t<decltype(std::declval<T&>().kids == nullptr)>> : std::true_type {};

TEST_F(PopplerLayerIsParentTest_2512, KidsNullReturnsFalse_2512) {
  if constexpr (!(HasKidsMember<Layer>::value && KidsIsNullablePtr<Layer>::value)) {
    GTEST_SKIP() << "Layer::kids is not accessible or not comparable to nullptr in this build.";
  } else {
    PopplerLayer* pl = POPPLER_LAYER(g_object_new(POPPLER_TYPE_LAYER, nullptr));
    ASSERT_NE(pl, nullptr);

    // Create a real Layer and wire it into PopplerLayer (public in poppler-private.h).
    Layer* layer = new Layer();
    layer->kids = nullptr;
    pl->layer = layer;

    EXPECT_FALSE(poppler_layer_is_parent(pl));

    // Cleanup
    delete layer;
    pl->layer = nullptr;
    g_object_unref(pl);
  }
}

TEST_F(PopplerLayerIsParentTest_2512, KidsNonNullReturnsTrue_2512) {
  if constexpr (!(HasKidsMember<Layer>::value && KidsIsNullablePtr<Layer>::value)) {
    GTEST_SKIP() << "Layer::kids is not accessible or not comparable to nullptr in this build.";
  } else {
    PopplerLayer* pl = POPPLER_LAYER(g_object_new(POPPLER_TYPE_LAYER, nullptr));
    ASSERT_NE(pl, nullptr);

    Layer* layer = new Layer();

    // Any non-null pointer value should satisfy the observable contract: returns TRUE when kids != nullptr.
    // Avoid allocating unknown kid structures; we only need a non-null sentinel.
    layer->kids = reinterpret_cast<decltype(layer->kids)>(static_cast<uintptr_t>(0x1));

    pl->layer = layer;

    EXPECT_TRUE(poppler_layer_is_parent(pl));

    delete layer;
    pl->layer = nullptr;
    g_object_unref(pl);
  }
}
#else
TEST_F(PopplerLayerIsParentTest_2512, LayerDefinitionUnavailable_Skipped_2512) {
  GTEST_SKIP() << "Could not include a header that defines Layer; only type-check/error-path tests run.";
}
#endif

}  // namespace