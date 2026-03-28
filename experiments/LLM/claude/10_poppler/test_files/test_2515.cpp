#include <gtest/gtest.h>
#include <gtk/gtk.h>
#include <poppler.h>

class PgdInfoCreateWidgetTest_2515 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        // Initialize GTK once for all tests
        int argc = 0;
        char **argv = nullptr;
        gtk_init(&argc, &argv);
    }

    void SetUp() override {
        document_ = nullptr;
    }

    void TearDown() override {
        if (document_) {
            g_object_unref(document_);
            document_ = nullptr;
        }
    }

    PopplerDocument *document_;
};

// Helper to create a simple PDF in memory for testing
static PopplerDocument *create_test_document_from_file(const char *path) {
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

// Create a minimal PDF in memory
static PopplerDocument *create_minimal_pdf_document() {
    // Minimal valid PDF
    const char *pdf_data =
        "%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\n"
        "endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n"
        "<< /Size 4 /Root 1 0 R /Info << /Title (Test Title) /Author (Test Author) /Subject (Test Subject) /Keywords (test keywords) /Creator (Test Creator) /Producer (Test Producer) /CreationDate (D:20230101120000Z) /ModDate (D:20230615120000Z) >> >>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    gsize len = strlen(pdf_data);
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_data((char *)pdf_data, (int)len, nullptr, &error);
    if (error) {
        g_error_free(error);
        return nullptr;
    }
    return doc;
}

static PopplerDocument *create_minimal_pdf_document_bytes() {
    const char *pdf_data =
        "%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\n"
        "endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n"
        "<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    gsize len = strlen(pdf_data);
    GBytes *bytes = g_bytes_new(pdf_data, len);
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_bytes(bytes, nullptr, &error);
    g_bytes_unref(bytes);
    if (error) {
        g_error_free(error);
        return nullptr;
    }
    return doc;
}

// Declare the function under test
extern "C" {
    GtkWidget *pgd_info_create_widget(PopplerDocument *document);
}

TEST_F(PgdInfoCreateWidgetTest_2515, ReturnsNonNullWidget_2515) {
    document_ = create_minimal_pdf_document();
    if (!document_) {
        document_ = create_minimal_pdf_document_bytes();
    }
    if (!document_) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    GtkWidget *widget = pgd_info_create_widget(document_);
    ASSERT_NE(widget, nullptr);
    gtk_widget_destroy(widget);
}

TEST_F(PgdInfoCreateWidgetTest_2515, ReturnsGtkBox_2515) {
    document_ = create_minimal_pdf_document();
    if (!document_) {
        document_ = create_minimal_pdf_document_bytes();
    }
    if (!document_) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    GtkWidget *widget = pgd_info_create_widget(document_);
    ASSERT_NE(widget, nullptr);
    EXPECT_TRUE(GTK_IS_BOX(widget));
    gtk_widget_destroy(widget);
}

TEST_F(PgdInfoCreateWidgetTest_2515, BoxIsVertical_2515) {
    document_ = create_minimal_pdf_document();
    if (!document_) {
        document_ = create_minimal_pdf_document_bytes();
    }
    if (!document_) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    GtkWidget *widget = pgd_info_create_widget(document_);
    ASSERT_NE(widget, nullptr);
    ASSERT_TRUE(GTK_IS_BOX(widget));
    GtkOrientation orientation = gtk_orientable_get_orientation(GTK_ORIENTABLE(widget));
    EXPECT_EQ(orientation, GTK_ORIENTATION_VERTICAL);
    gtk_widget_destroy(widget);
}

TEST_F(PgdInfoCreateWidgetTest_2515, BoxHasChildren_2515) {
    document_ = create_minimal_pdf_document();
    if (!document_) {
        document_ = create_minimal_pdf_document_bytes();
    }
    if (!document_) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    GtkWidget *widget = pgd_info_create_widget(document_);
    ASSERT_NE(widget, nullptr);
    ASSERT_TRUE(GTK_IS_CONTAINER(widget));

    GList *children = gtk_container_get_children(GTK_CONTAINER(widget));
    // Should have at least 2 children: a label and a frame
    EXPECT_GE(g_list_length(children), 2u);
    g_list_free(children);
    gtk_widget_destroy(widget);
}

TEST_F(PgdInfoCreateWidgetTest_2515, FirstChildIsLabel_2515) {
    document_ = create_minimal_pdf_document();
    if (!document_) {
        document_ = create_minimal_pdf_document_bytes();
    }
    if (!document_) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    GtkWidget *widget = pgd_info_create_widget(document_);
    ASSERT_NE(widget, nullptr);

    GList *children = gtk_container_get_children(GTK_CONTAINER(widget));
    ASSERT_NE(children, nullptr);
    GtkWidget *first_child = GTK_WIDGET(children->data);
    EXPECT_TRUE(GTK_IS_LABEL(first_child));
    g_list_free(children);
    gtk_widget_destroy(widget);
}

TEST_F(PgdInfoCreateWidgetTest_2515, SecondChildIsFrame_2515) {
    document_ = create_minimal_pdf_document();
    if (!document_) {
        document_ = create_minimal_pdf_document_bytes();
    }
    if (!document_) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    GtkWidget *widget = pgd_info_create_widget(document_);
    ASSERT_NE(widget, nullptr);

    GList *children = gtk_container_get_children(GTK_CONTAINER(widget));
    ASSERT_NE(children, nullptr);
    ASSERT_NE(children->next, nullptr);
    GtkWidget *second_child = GTK_WIDGET(children->next->data);
    EXPECT_TRUE(GTK_IS_FRAME(second_child));
    g_list_free(children);
    gtk_widget_destroy(widget);
}

TEST_F(PgdInfoCreateWidgetTest_2515, LabelContainsPopplerVersion_2515) {
    document_ = create_minimal_pdf_document();
    if (!document_) {
        document_ = create_minimal_pdf_document_bytes();
    }
    if (!document_) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    GtkWidget *widget = pgd_info_create_widget(document_);
    ASSERT_NE(widget, nullptr);

    GList *children = gtk_container_get_children(GTK_CONTAINER(widget));
    ASSERT_NE(children, nullptr);
    GtkWidget *first_child = GTK_WIDGET(children->data);
    ASSERT_TRUE(GTK_IS_LABEL(first_child));

    const gchar *text = gtk_label_get_text(GTK_LABEL(first_child));
    ASSERT_NE(text, nullptr);
    // The label should contain the poppler version string
    const char *version = poppler_get_version();
    EXPECT_NE(strstr(text, version), nullptr);

    g_list_free(children);
    gtk_widget_destroy(widget);
}

TEST_F(PgdInfoCreateWidgetTest_2515, FrameContainsGrid_2515) {
    document_ = create_minimal_pdf_document();
    if (!document_) {
        document_ = create_minimal_pdf_document_bytes();
    }
    if (!document_) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    GtkWidget *widget = pgd_info_create_widget(document_);
    ASSERT_NE(widget, nullptr);

    GList *children = gtk_container_get_children(GTK_CONTAINER(widget));
    ASSERT_NE(children, nullptr);
    ASSERT_NE(children->next, nullptr);
    GtkWidget *frame = GTK_WIDGET(children->next->data);
    ASSERT_TRUE(GTK_IS_FRAME(frame));

    GtkWidget *frame_child = gtk_bin_get_child(GTK_BIN(frame));
    ASSERT_NE(frame_child, nullptr);
    EXPECT_TRUE(GTK_IS_GRID(frame_child));

    g_list_free(children);
    gtk_widget_destroy(widget);
}

TEST_F(PgdInfoCreateWidgetTest_2515, FrameShadowTypeIsNone_2515) {
    document_ = create_minimal_pdf_document();
    if (!document_) {
        document_ = create_minimal_pdf_document_bytes();
    }
    if (!document_) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    GtkWidget *widget = pgd_info_create_widget(document_);
    ASSERT_NE(widget, nullptr);

    GList *children = gtk_container_get_children(GTK_CONTAINER(widget));
    ASSERT_NE(children, nullptr);
    ASSERT_NE(children->next, nullptr);
    GtkWidget *frame = GTK_WIDGET(children->next->data);
    ASSERT_TRUE(GTK_IS_FRAME(frame));

    GtkShadowType shadow = gtk_frame_get_shadow_type(GTK_FRAME(frame));
    EXPECT_EQ(shadow, GTK_SHADOW_NONE);

    g_list_free(children);
    gtk_widget_destroy(widget);
}

TEST_F(PgdInfoCreateWidgetTest_2515, FrameLabelWidgetIsLabel_2515) {
    document_ = create_minimal_pdf_document();
    if (!document_) {
        document_ = create_minimal_pdf_document_bytes();
    }
    if (!document_) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    GtkWidget *widget = pgd_info_create_widget(document_);
    ASSERT_NE(widget, nullptr);

    GList *children = gtk_container_get_children(GTK_CONTAINER(widget));
    ASSERT_NE(children, nullptr);
    ASSERT_NE(children->next, nullptr);
    GtkWidget *frame = GTK_WIDGET(children->next->data);
    ASSERT_TRUE(GTK_IS_FRAME(frame));

    GtkWidget *label_widget = gtk_frame_get_label_widget(GTK_FRAME(frame));
    ASSERT_NE(label_widget, nullptr);
    EXPECT_TRUE(GTK_IS_LABEL(label_widget));

    // Check label text contains "Document properties"
    const gchar *text = gtk_label_get_text(GTK_LABEL(label_widget));
    ASSERT_NE(text, nullptr);
    EXPECT_NE(strstr(text, "Document properties"), nullptr);

    g_list_free(children);
    gtk_widget_destroy(widget);
}

TEST_F(PgdInfoCreateWidgetTest_2515, GridHasMultipleRows_2515) {
    document_ = create_minimal_pdf_document();
    if (!document_) {
        document_ = create_minimal_pdf_document_bytes();
    }
    if (!document_) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    GtkWidget *widget = pgd_info_create_widget(document_);
    ASSERT_NE(widget, nullptr);

    GList *children = gtk_container_get_children(GTK_CONTAINER(widget));
    ASSERT_NE(children, nullptr);
    ASSERT_NE(children->next, nullptr);
    GtkWidget *frame = GTK_WIDGET(children->next->data);
    GtkWidget *grid = gtk_bin_get_child(GTK_BIN(frame));
    ASSERT_TRUE(GTK_IS_GRID(grid));

    // The grid should have children for the properties
    GList *grid_children = gtk_container_get_children(GTK_CONTAINER(grid));
    // At minimum we expect properties: Format, Title, Author, Subject, Keywords,
    // Creator, Producer, Linearized, Creation Date, Mod Date, Page Mode, Page Layout
    // Each property has 2 widgets (label + value), so at least 24 children
    guint count = g_list_length(grid_children);
    EXPECT_GE(count, 24u);
    g_list_free(grid_children);

    g_list_free(children);
    gtk_widget_destroy(widget);
}

TEST_F(PgdInfoCreateWidgetTest_2515, WidgetIsVisible_2515) {
    document_ = create_minimal_pdf_document();
    if (!document_) {
        document_ = create_minimal_pdf_document_bytes();
    }
    if (!document_) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    GtkWidget *widget = pgd_info_create_widget(document_);
    ASSERT_NE(widget, nullptr);

    // The children should be shown
    GList *children = gtk_container_get_children(GTK_CONTAINER(widget));
    ASSERT_NE(children, nullptr);
    GtkWidget *first_child = GTK_WIDGET(children->data);
    EXPECT_TRUE(gtk_widget_get_visible(first_child));

    if (children->next) {
        GtkWidget *second_child = GTK_WIDGET(children->next->data);
        EXPECT_TRUE(gtk_widget_get_visible(second_child));
    }

    g_list_free(children);
    gtk_widget_destroy(widget);
}

TEST_F(PgdInfoCreateWidgetTest_2515, GridSpacingIsSet_2515) {
    document_ = create_minimal_pdf_document();
    if (!document_) {
        document_ = create_minimal_pdf_document_bytes();
    }
    if (!document_) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    GtkWidget *widget = pgd_info_create_widget(document_);
    ASSERT_NE(widget, nullptr);

    GList *children = gtk_container_get_children(GTK_CONTAINER(widget));
    ASSERT_NE(children, nullptr);
    ASSERT_NE(children->next, nullptr);
    GtkWidget *frame = GTK_WIDGET(children->next->data);
    GtkWidget *grid = gtk_bin_get_child(GTK_BIN(frame));
    ASSERT_TRUE(GTK_IS_GRID(grid));

    EXPECT_EQ(gtk_grid_get_column_spacing(GTK_GRID(grid)), 6u);
    EXPECT_EQ(gtk_grid_get_row_spacing(GTK_GRID(grid)), 6u);

    g_list_free(children);
    gtk_widget_destroy(widget);
}

TEST_F(PgdInfoCreateWidgetTest_2515, GridMarginsAreSet_2515) {
    document_ = create_minimal_pdf_document();
    if (!document_) {
        document_ = create_minimal_pdf_document_bytes();
    }
    if (!document_) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    GtkWidget *widget = pgd_info_create_widget(document_);
    ASSERT_NE(widget, nullptr);

    GList *children = gtk_container_get_children(GTK_CONTAINER(widget));
    ASSERT_NE(children, nullptr);
    ASSERT_NE(children->next, nullptr);
    GtkWidget *frame = GTK_WIDGET(children->next->data);
    GtkWidget *grid = gtk_bin_get_child(GTK_BIN(frame));
    ASSERT_TRUE(GTK_IS_GRID(grid));

    EXPECT_EQ(gtk_widget_get_margin_top(grid), 5);
    EXPECT_EQ(gtk_widget_get_margin_bottom(grid), 5);
    EXPECT_EQ(gtk_widget_get_margin_start(grid), 12);
    EXPECT_EQ(gtk_widget_get_margin_end(grid), 5);

    g_list_free(children);
    gtk_widget_destroy(widget);
}

TEST_F(PgdInfoCreateWidgetTest_2515, BoxSpacingIsTwelve_2515) {
    document_ = create_minimal_pdf_document();
    if (!document_) {
        document_ = create_minimal_pdf_document_bytes();
    }
    if (!document_) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    GtkWidget *widget = pgd_info_create_widget(document_);
    ASSERT_NE(widget, nullptr);
    ASSERT_TRUE(GTK_IS_BOX(widget));

    gint spacing = gtk_box_get_spacing(GTK_BOX(widget));
    EXPECT_EQ(spacing, 12);

    gtk_widget_destroy(widget);
}
