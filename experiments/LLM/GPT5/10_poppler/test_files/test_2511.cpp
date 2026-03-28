// poppler-layer-hide-test.cc
//
// Unit tests for poppler_layer_hide()
// TEST_ID: 2511

#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

#include "poppler-layer.h"

// Internal structs are referenced by the provided partial code/dependencies.
#include "poppler-private.h"

#include "OptionalContent.h"

namespace {

class ScopedLogCatcher {
 public:
  explicit ScopedLogCatcher(GLogLevelFlags levels)
      : levels_(levels) {
    // Catch common domains used by g_return_if_fail() and libraries.
    AddHandler(nullptr);          // default domain
    AddHandler("GLib");
    AddHandler("GLib-GObject");
    AddHandler("Poppler");
  }

  ~ScopedLogCatcher() {
    for (const auto& h : handlers_) {
      g_log_remove_handler(h.domain, h.id);
    }
  }

  int critical_count() const { return critical_count_; }

 private:
  struct Handler {
    const char* domain;
    guint id;
  };

  static void HandlerFunc(const gchar* /*log_domain*/,
                          GLogLevelFlags log_level,
                          const gchar* /*message*/,
                          gpointer user_data) {
    auto* self = static_cast<ScopedLogCatcher*>(user_data);
    if (log_level & G_LOG_LEVEL_CRITICAL) {
      self->critical_count_++;
    }
  }

  void AddHandler(const char* domain) {
    guint id = g_log_set_handler(domain, levels_, &ScopedLogCatcher::HandlerFunc, this);
    handlers_.push_back(Handler{domain, id});
  }

  GLogLevelFlags levels_;
  int critical_count_ = 0;
  std::vector<Handler> handlers_;
};

static PopplerLayer* CreatePopplerLayerWithOC(OptionalContentGroup* oc, Layer** out_layer_struct) {
  PopplerLayer* poppler_layer = POPPLER_LAYER(g_object_new(POPPLER_TYPE_LAYER, nullptr));
  EXPECT_TRUE(POPPLER_IS_LAYER(poppler_layer));

  Layer* layer_struct = g_new0(Layer, 1);
  layer_struct->oc = oc;

  // Wire the internal struct as shown in the provided partial implementation.
  _PopplerLayer* internal = reinterpret_cast<_PopplerLayer*>(poppler_layer);
  internal->layer = layer_struct;

  if (out_layer_struct) {
    *out_layer_struct = layer_struct;
  }
  return poppler_layer;
}

static void DestroyPopplerLayerAndLayerStruct(PopplerLayer* poppler_layer, Layer* layer_struct) {
  if (poppler_layer) {
    g_object_unref(poppler_layer);
  }
  if (layer_struct) {
    g_free(layer_struct);
  }
}

}  // namespace

TEST(PopplerLayerHideTest_2511, NullPointerTriggersCritical_2511) {
  ScopedLogCatcher catcher(static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL));

  poppler_layer_hide(nullptr);

  EXPECT_GE(catcher.critical_count(), 1);
}

TEST(PopplerLayerHideTest_2511, NonLayerObjectTriggersCritical_2511) {
  ScopedLogCatcher catcher(static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL));

  GObject* not_a_layer = g_object_new(G_TYPE_OBJECT, nullptr);
  ASSERT_NE(not_a_layer, nullptr);

  poppler_layer_hide(reinterpret_cast<PopplerLayer*>(not_a_layer));

  g_object_unref(not_a_layer);

  EXPECT_GE(catcher.critical_count(), 1);
}

TEST(PopplerLayerHideTest_2511, HideSetsOptionalContentGroupToOffWhenNotOff_2511) {
  // Construct an OptionalContentGroup with a minimal/null Dict* as allowed by the interface.
  // (The production implementation is treated as a black box; we only observe state changes.)
  OptionalContentGroup* oc = new OptionalContentGroup(nullptr);
  ASSERT_NE(oc, nullptr);

  // Ensure it's not Off first (boundary: any non-Off should be forced to Off by hide()).
  // We avoid relying on internal logic; we only need a value different from Off.
  oc->setState(static_cast<OptionalContentGroup::State>(OptionalContentGroup::Off + 1));
  EXPECT_NE(oc->getState(), OptionalContentGroup::Off);

  Layer* layer_struct = nullptr;
  PopplerLayer* poppler_layer = CreatePopplerLayerWithOC(oc, &layer_struct);
  ASSERT_NE(poppler_layer, nullptr);
  ASSERT_NE(layer_struct, nullptr);

  ScopedLogCatcher catcher(static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL));

  poppler_layer_hide(poppler_layer);

  EXPECT_EQ(oc->getState(), OptionalContentGroup::Off);
  EXPECT_EQ(catcher.critical_count(), 0);

  DestroyPopplerLayerAndLayerStruct(poppler_layer, layer_struct);
  delete oc;
}

TEST(PopplerLayerHideTest_2511, HideIsNoOpWhenOptionalContentGroupAlreadyOff_2511) {
  OptionalContentGroup* oc = new OptionalContentGroup(nullptr);
  ASSERT_NE(oc, nullptr);

  oc->setState(OptionalContentGroup::Off);
  EXPECT_EQ(oc->getState(), OptionalContentGroup::Off);

  Layer* layer_struct = nullptr;
  PopplerLayer* poppler_layer = CreatePopplerLayerWithOC(oc, &layer_struct);
  ASSERT_NE(poppler_layer, nullptr);
  ASSERT_NE(layer_struct, nullptr);

  ScopedLogCatcher catcher(static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL));

  // Calling twice exercises the "already Off" boundary condition and idempotency.
  poppler_layer_hide(poppler_layer);
  EXPECT_EQ(oc->getState(), OptionalContentGroup::Off);

  poppler_layer_hide(poppler_layer);
  EXPECT_EQ(oc->getState(), OptionalContentGroup::Off);

  EXPECT_EQ(catcher.critical_count(), 0);

  DestroyPopplerLayerAndLayerStruct(poppler_layer, layer_struct);
  delete oc;
}