// poppler-action-layer-copy-test_2286.cc
#include <gtest/gtest.h>

#include <glib-object.h>
#include <glib.h>

// Include the implementation file so we can call the file-local (static) function
// without changing production code.
#include "./TestProjects/poppler/glib/poppler-action.cc"

namespace {

void WeakNotifySetBool(gpointer data, GObject * /*where_the_object_was*/) {
    auto *flag = static_cast<bool *>(data);
    *flag = true;
}

static void FreeActionLayerAndUnrefListObjects(PopplerActionLayer *layer) {
    if (!layer)
        return;

    // poppler_action_layer_copy() refs each object in the copied list, so tests
    // should unref objects for whichever list they "own" before freeing the list.
    for (GList *l = layer->layers; l != nullptr; l = l->next) {
        if (l->data) {
            g_object_unref(G_OBJECT(l->data));
        }
    }
    g_list_free(layer->layers);
    layer->layers = nullptr;

    g_slice_free(PopplerActionLayer, layer);
}

static PopplerActionLayer *MakeLayerWithObjects(const std::vector<GObject *> &objs) {
    auto *layer = g_slice_new0(PopplerActionLayer);
    layer->layers = nullptr;
    for (auto *obj : objs) {
        // Store the object pointer; we treat the list as holding one owning ref per entry
        // for the purpose of deterministic lifetime in tests.
        g_object_ref(obj);
        layer->layers = g_list_append(layer->layers, obj);
    }
    return layer;
}

} // namespace

TEST(PopplerActionLayerCopyTest_2286, CopiesEmptyList_2286) {
    auto *original = g_slice_new0(PopplerActionLayer);
    original->layers = nullptr;

    PopplerActionLayer *copy = poppler_action_layer_copy(original);
    ASSERT_NE(copy, nullptr);
    EXPECT_NE(copy, original);

    EXPECT_EQ(original->layers, nullptr);
    EXPECT_EQ(copy->layers, nullptr);

    // Cleanup
    g_slice_free(PopplerActionLayer, copy);
    g_slice_free(PopplerActionLayer, original);
}

TEST(PopplerActionLayerCopyTest_2286, CopiesListStructureAndPreservesObjectPointers_2286) {
    GObject *o1 = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
    ASSERT_NE(o1, nullptr);

    auto *original = MakeLayerWithObjects({o1});
    ASSERT_NE(original, nullptr);
    ASSERT_NE(original->layers, nullptr);
    ASSERT_NE(original->layers->data, nullptr);

    PopplerActionLayer *copy = poppler_action_layer_copy(original);
    ASSERT_NE(copy, nullptr);
    EXPECT_NE(copy, original);

    ASSERT_NE(copy->layers, nullptr);
    EXPECT_NE(copy->layers, original->layers) << "List nodes should be copied, not shared";
    EXPECT_EQ(g_list_length(copy->layers), g_list_length(original->layers));
    EXPECT_EQ(copy->layers->data, original->layers->data) << "Object pointers should match";

    // Cleanup: release our explicit test-created ownership
    FreeActionLayerAndUnrefListObjects(copy);
    FreeActionLayerAndUnrefListObjects(original);

    // Release the standalone creation ref for o1 (MakeLayerWithObjects took its own ref).
    g_object_unref(o1);
}

TEST(PopplerActionLayerCopyTest_2286, CopyAddsRefsSoObjectsOutliveOriginal_2286) {
    GObject *o1 = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
    GObject *o2 = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
    ASSERT_NE(o1, nullptr);
    ASSERT_NE(o2, nullptr);

    bool finalized1 = false;
    bool finalized2 = false;
    g_object_weak_ref(o1, WeakNotifySetBool, &finalized1);
    g_object_weak_ref(o2, WeakNotifySetBool, &finalized2);

    // original holds one ref per entry (via MakeLayerWithObjects).
    auto *original = MakeLayerWithObjects({o1, o2});
    ASSERT_NE(original, nullptr);

    // copy should take an additional ref per entry.
    PopplerActionLayer *copy = poppler_action_layer_copy(original);
    ASSERT_NE(copy, nullptr);
    ASSERT_EQ(g_list_length(copy->layers), 2);

    // Drop original's list-held refs; objects should remain alive thanks to copy's refs.
    FreeActionLayerAndUnrefListObjects(original);
    EXPECT_FALSE(finalized1);
    EXPECT_FALSE(finalized2);

    // Now drop copy's list-held refs; objects should be finalized (no refs remain except
    // the standalone creation refs below).
    FreeActionLayerAndUnrefListObjects(copy);

    // At this point, objects may still be alive because we still hold the initial creation refs.
    // Releasing them should trigger finalization, observable via weak notify.
    EXPECT_FALSE(finalized1);
    EXPECT_FALSE(finalized2);

    g_object_unref(o1);
    g_object_unref(o2);

    EXPECT_TRUE(finalized1);
    EXPECT_TRUE(finalized2);
}