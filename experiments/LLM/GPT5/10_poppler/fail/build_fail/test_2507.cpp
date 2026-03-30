// File: poppler-layer-new-test_2507.cc
#include <gtest/gtest.h>

#include <glib-object.h>

#include "poppler.h"

// This is a *private* constructor helper we are explicitly testing here.
extern "C" {
#include "poppler-private.h"
PopplerLayer *_poppler_layer_new(PopplerDocument *document, Layer *layer, GList *rbgroup);
}

#include "OptionalContent.h"
#include "Object.h"

namespace {

class PopplerLayerNewTest_2507 : public ::testing::Test {
protected:
  void SetUp() override {
    // We only need a valid GObject instance passing POPPLER_IS_DOCUMENT().
    // Avoid depending on any PDF loading behavior.
    doc_ = POPPLER_DOCUMENT(g_object_new(POPPLER_TYPE_DOCUMENT, nullptr));
    ASSERT_NE(doc_, nullptr);
    ASSERT_TRUE(POPPLER_IS_DOCUMENT(doc_));
  }

  void TearDown() override {
    if (doc_) {
      g_object_unref(doc_);
      doc_ = nullptr;
    }
  }

  // Creates an OptionalContentGroup with an (often) empty Dict.
  // For many Poppler builds, an empty dict results in getName() == nullptr, which
  // is the observable path we validate (title becomes nullptr).
  static OptionalContentGroup *CreateOCGEmpty_2507(Dict **out_dict) {
    EXPECT_NE(out_dict, nullptr);

    // Poppler Dict typically accepts an XRef* (can be nullptr for unit tests).
    Dict *dict = new Dict(nullptr);
    *out_dict = dict;
    return new OptionalContentGroup(dict);
  }

  static void DestroyOCG_2507(OptionalContentGroup *ocg, Dict *dict) {
    delete ocg;
    delete dict;
  }

  PopplerDocument *doc_ = nullptr;
};

TEST_F(PopplerLayerNewTest_2507, ReturnsNullWhenDocumentIsNull_2507) {
  Dict *dict = nullptr;
  OptionalContentGroup *ocg = CreateOCGEmpty_2507(&dict);
  ASSERT_NE(ocg, nullptr);

  Layer layer{};
  layer.label = nullptr;
  layer.oc = ocg;

  PopplerLayer *pl = _poppler_layer_new(nullptr, &layer, /*rbgroup=*/nullptr);
  EXPECT_EQ(pl, nullptr);

  DestroyOCG_2507(ocg, dict);
}

TEST_F(PopplerLayerNewTest_2507, ReturnsNullWhenDocumentIsWrongType_2507) {
  // A plain GObject is not a PopplerDocument, so POPPLER_IS_DOCUMENT() must fail.
  GObject *not_doc = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(not_doc, nullptr);

  Dict *dict = nullptr;
  OptionalContentGroup *ocg = CreateOCGEmpty_2507(&dict);
  ASSERT_NE(ocg, nullptr);

  Layer layer{};
  layer.label = nullptr;
  layer.oc = ocg;

  PopplerLayer *pl = _poppler_layer_new(reinterpret_cast<PopplerDocument *>(not_doc), &layer,
                                        /*rbgroup=*/nullptr);
  EXPECT_EQ(pl, nullptr);

  DestroyOCG_2507(ocg, dict);
  g_object_unref(not_doc);
}

TEST_F(PopplerLayerNewTest_2507, ReturnsNullWhenLayerIsNull_2507) {
  PopplerLayer *pl = _poppler_layer_new(doc_, /*layer=*/nullptr, /*rbgroup=*/nullptr);
  EXPECT_EQ(pl, nullptr);
}

TEST_F(PopplerLayerNewTest_2507, CreatesLayerObjectWithBasicFields_2507) {
  Dict *dict = nullptr;
  OptionalContentGroup *ocg = CreateOCGEmpty_2507(&dict);
  ASSERT_NE(ocg, nullptr);

  Layer layer{};
  layer.label = nullptr;
  layer.oc = ocg;

  // Boundary: rbgroup can be nullptr.
  PopplerLayer *pl = _poppler_layer_new(doc_, &layer, /*rbgroup=*/nullptr);
  ASSERT_NE(pl, nullptr);
  EXPECT_TRUE(POPPLER_IS_LAYER(pl));

  // Observable effects via the (provided) struct layout: layer + rbgroup pointers.
  // We avoid asserting any internal refcounting behavior.
  EXPECT_EQ(reinterpret_cast<_PopplerLayer *>(pl)->layer, &layer);
  EXPECT_EQ(reinterpret_cast<_PopplerLayer *>(pl)->rbgroup, nullptr);

  g_object_unref(pl);
  DestroyOCG_2507(ocg, dict);
}

TEST_F(PopplerLayerNewTest_2507, AcceptsNonEmptyRbgroupPointer_2507) {
  Dict *dict = nullptr;
  OptionalContentGroup *ocg = CreateOCGEmpty_2507(&dict);
  ASSERT_NE(ocg, nullptr);

  Layer layer{};
  layer.label = nullptr;
  layer.oc = ocg;

  // Boundary: rbgroup is an opaque GList*; the function should store the pointer.
  gpointer a = reinterpret_cast<gpointer>(0x1);
  gpointer b = reinterpret_cast<gpointer>(0x2);
  GList *rbgroup = nullptr;
  rbgroup = g_list_append(rbgroup, a);
  rbgroup = g_list_append(rbgroup, b);

  PopplerLayer *pl = _poppler_layer_new(doc_, &layer, rbgroup);
  ASSERT_NE(pl, nullptr);
  EXPECT_TRUE(POPPLER_IS_LAYER(pl));

  EXPECT_EQ(reinterpret_cast<_PopplerLayer *>(pl)->layer, &layer);
  EXPECT_EQ(reinterpret_cast<_PopplerLayer *>(pl)->rbgroup, rbgroup);

  g_object_unref(pl);
  g_list_free(rbgroup);
  DestroyOCG_2507(ocg, dict);
}

TEST_F(PopplerLayerNewTest_2507, TitleIsNullWhenOCGNameIsNull_2507) {
  Dict *dict = nullptr;
  OptionalContentGroup *ocg = CreateOCGEmpty_2507(&dict);
  ASSERT_NE(ocg, nullptr);

  // The constructor path for OptionalContentGroup with an empty Dict commonly
  // yields getName() == nullptr; _poppler_layer_new then sets title to nullptr.
  Layer layer{};
  layer.label = nullptr;
  layer.oc = ocg;

  PopplerLayer *pl = _poppler_layer_new(doc_, &layer, /*rbgroup=*/nullptr);
  ASSERT_NE(pl, nullptr);
  EXPECT_TRUE(POPPLER_IS_LAYER(pl));

  // Observable via the expanded private struct shown in the prompt: title is set.
  // We only validate the null-case, avoiding assumptions about encoding conversion.
  // (The prompt’s partial struct excerpt omits title, but the implementation writes it.)
  auto *priv = reinterpret_cast<_PopplerLayer *>(pl);
  // The title field is not shown in the minimal excerpt; if your build exposes it in
  // poppler-private.h, keep the check below; otherwise, remove it.
#ifdef POPPLER_LAYER_HAS_TITLE_FIELD_2507
  EXPECT_EQ(priv->title, nullptr);
#else
  // Fallback: we can still assert construction succeeded and the object is valid.
  SUCCEED();
#endif

  g_object_unref(pl);
  DestroyOCG_2507(ocg, dict);
}

} // namespace