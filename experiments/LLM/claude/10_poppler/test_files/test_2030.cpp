#include <glib.h>
#include <glib-object.h>
#include <poppler.h>
#include <gtest/gtest.h>
#include <cstring>
#include <cstdio>

class PopplerMediaTest_2030 : public ::testing::Test {
protected:
    void SetUp() override {
        // We need a PDF with media/screen annotations to get PopplerMedia objects
        // For basic type checking tests, we can work without actual media objects
    }

    void TearDown() override {
    }

    PopplerDocument *loadDocumentWithMedia(const char *path) {
        GError *error = nullptr;
        gchar *uri = g_filename_to_uri(path, nullptr, &error);
        if (!uri) {
            if (error) g_error_free(error);
            return nullptr;
        }
        PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
        g_free(uri);
        if (error) g_error_free(error);
        return doc;
    }
};

// Test that the PopplerMedia GType is properly registered
TEST_F(PopplerMediaTest_2030, TypeRegistration_2030) {
    GType media_type = poppler_media_get_type();
    EXPECT_NE(media_type, G_TYPE_INVALID);
}

// Test that PopplerMedia type name is correct
TEST_F(PopplerMediaTest_2030, TypeName_2030) {
    GType media_type = poppler_media_get_type();
    const gchar *name = g_type_name(media_type);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "PopplerMedia");
}

// Test that PopplerMedia is derived from GObject
TEST_F(PopplerMediaTest_2030, DerivedFromGObject_2030) {
    GType media_type = poppler_media_get_type();
    EXPECT_TRUE(g_type_is_a(media_type, G_TYPE_OBJECT));
}

// Test that the type is not abstract (can be instantiated in principle)
TEST_F(PopplerMediaTest_2030, TypeIsInstantiable_2030) {
    GType media_type = poppler_media_get_type();
    // GObject types that are not abstract should be instantiable
    EXPECT_FALSE(G_TYPE_IS_ABSTRACT(media_type));
}

// Test type parent is GObject
TEST_F(PopplerMediaTest_2030, ParentTypeIsGObject_2030) {
    GType media_type = poppler_media_get_type();
    GType parent = g_type_parent(media_type);
    EXPECT_EQ(parent, G_TYPE_OBJECT);
}

// Test that multiple calls to get_type return the same type
TEST_F(PopplerMediaTest_2030, GetTypeConsistent_2030) {
    GType type1 = poppler_media_get_type();
    GType type2 = poppler_media_get_type();
    EXPECT_EQ(type1, type2);
}

// Test class size is reasonable (non-zero)
TEST_F(PopplerMediaTest_2030, ClassSizeNonZero_2030) {
    GType media_type = poppler_media_get_type();
    GTypeQuery query;
    g_type_query(media_type, &query);
    EXPECT_GT(query.class_size, 0u);
    EXPECT_GT(query.instance_size, 0u);
}

// Test that we can check type with POPPLER_IS_MEDIA macro concept via g_type_check
TEST_F(PopplerMediaTest_2030, TypeCheckFunctions_2030) {
    GType media_type = poppler_media_get_type();
    // Verify that the type system recognizes this as a valid fundamental derived type
    EXPECT_TRUE(G_TYPE_IS_OBJECT(media_type));
    EXPECT_TRUE(G_TYPE_IS_DERIVED(media_type));
}

// Test that the type is classed (as expected for GObject subtypes)
TEST_F(PopplerMediaTest_2030, TypeIsClassed_2030) {
    GType media_type = poppler_media_get_type();
    EXPECT_TRUE(G_TYPE_IS_CLASSED(media_type));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
