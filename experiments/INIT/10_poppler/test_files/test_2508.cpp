// poppler-layer-get-title-test_2508.cc
#include <gtest/gtest.h>

#include <glib-object.h>
#include <poppler.h>

namespace {

constexpr const char* kPropTitle = "title";
constexpr const char* kPropName = "name";

static PopplerLayer* CreateLayerOrSkip_2508() {
#ifndef POPPLER_TYPE_LAYER
  GTEST_SKIP() << "POPPLER_TYPE_LAYER is not available in this build.";
  return nullptr;
#else
  PopplerLayer* layer = POPPLER_LAYER(g_object_new(POPPLER_TYPE_LAYER, nullptr));
  if (!layer) {
    GTEST_SKIP() << "Failed to construct PopplerLayer via g_object_new().";
  }
  return layer;
#endif
}

static const char* FindSettableStringPropOrSkip_2508(GObject* obj) {
  if (!obj) {
    GTEST_SKIP() << "Null GObject passed.";
    return nullptr;
  }

  GParamSpec* pspec = g_object_class_find_property(G_OBJECT_GET_CLASS(obj), kPropTitle);
  if (pspec && (pspec->value_type == G_TYPE_STRING) &&
      (pspec->flags & G_PARAM_WRITABLE)) {
    return kPropTitle;
  }

  pspec = g_object_class_find_property(G_OBJECT_GET_CLASS(obj), kPropName);
  if (pspec && (pspec->value_type == G_TYPE_STRING) &&
      (pspec->flags & G_PARAM_WRITABLE)) {
    return kPropName;
  }

  GTEST_SKIP() << "Neither a writable string 'title' nor 'name' property exists on PopplerLayer.";
  return nullptr;
}

}  // namespace

TEST(PopplerLayerGetTitleTest_2508, NullPointerReturnsNull_2508) {
  const gchar* title = poppler_layer_get_title(nullptr);
  EXPECT_EQ(title, nullptr);
}

TEST(PopplerLayerGetTitleTest_2508, WrongGObjectTypeReturnsNull_2508) {
  GObject* not_a_layer = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(not_a_layer, nullptr);

  const gchar* title =
      poppler_layer_get_title(reinterpret_cast<PopplerLayer*>(not_a_layer));
  EXPECT_EQ(title, nullptr);

  g_object_unref(not_a_layer);
}

TEST(PopplerLayerGetTitleTest_2508, ReturnsTitleThatWasSet_2508) {
  PopplerLayer* layer = CreateLayerOrSkip_2508();
  ASSERT_NE(layer, nullptr);

  const char* prop = FindSettableStringPropOrSkip_2508(G_OBJECT(layer));
  ASSERT_NE(prop, nullptr);

  const gchar* kExpected = "My Layer Title";
  g_object_set(G_OBJECT(layer), prop, kExpected, nullptr);

  const gchar* title = poppler_layer_get_title(layer);
  ASSERT_NE(title, nullptr);
  EXPECT_STREQ(title, kExpected);

  g_object_unref(layer);
}

TEST(PopplerLayerGetTitleTest_2508, EmptyTitleIsReturnedAsEmptyString_2508) {
  PopplerLayer* layer = CreateLayerOrSkip_2508();
  ASSERT_NE(layer, nullptr);

  const char* prop = FindSettableStringPropOrSkip_2508(G_OBJECT(layer));
  ASSERT_NE(prop, nullptr);

  const gchar* kExpected = "";
  g_object_set(G_OBJECT(layer), prop, kExpected, nullptr);

  const gchar* title = poppler_layer_get_title(layer);
  ASSERT_NE(title, nullptr);
  EXPECT_STREQ(title, kExpected);

  g_object_unref(layer);
}

TEST(PopplerLayerGetTitleTest_2508, Utf8TitleIsReturned_2508) {
  PopplerLayer* layer = CreateLayerOrSkip_2508();
  ASSERT_NE(layer, nullptr);

  const char* prop = FindSettableStringPropOrSkip_2508(G_OBJECT(layer));
  ASSERT_NE(prop, nullptr);

  // UTF-8 string (Korean + emoji).
  const gchar* kExpected = u8"레이어 제목 ✅";
  g_object_set(G_OBJECT(layer), prop, kExpected, nullptr);

  const gchar* title = poppler_layer_get_title(layer);
  ASSERT_NE(title, nullptr);
  EXPECT_STREQ(title, kExpected);

  g_object_unref(layer);
}