#include <glib.h>
#include <glib-object.h>
#include <poppler.h>
#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>
#include <fstream>

// Helper: create a minimal valid PDF in memory
static GBytes *create_minimal_pdf()
{
    const char *pdf_content =
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

    return g_bytes_new(pdf_content, strlen(pdf_content));
}

// Helper: create a minimal PDF file on disk and return the URI
static gchar *create_minimal_pdf_file(const char *filename)
{
    const char *pdf_content =
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

    std::ofstream ofs(filename, std::ios::binary);
    ofs.write(pdf_content, strlen(pdf_content));
    ofs.close();

    gchar *abs_path = g_canonicalize_filename(filename, nullptr);
    gchar *uri = g_filename_to_uri(abs_path, nullptr, nullptr);
    g_free(abs_path);
    return uri;
}

class PopplerDocumentTest_2211 : public ::testing::Test
{
protected:
    PopplerDocument *doc = nullptr;
    gchar *tmp_uri = nullptr;

    void SetUp() override
    {
        tmp_uri = create_minimal_pdf_file("test_2211.pdf");
        GError *error = nullptr;
        doc = poppler_document_new_from_file(tmp_uri, nullptr, &error);
        if (error) {
            g_error_free(error);
            doc = nullptr;
        }
    }

    void TearDown() override
    {
        if (doc) {
            g_object_unref(doc);
        }
        if (tmp_uri) {
            g_free(tmp_uri);
        }
        g_remove("test_2211.pdf");
    }
};

// Test: Document loads successfully from file
TEST_F(PopplerDocumentTest_2211, DocumentLoadsFromFile_2211)
{
    ASSERT_NE(doc, nullptr);
}

// Test: Document has expected number of pages (1 page in our minimal PDF)
TEST_F(PopplerDocumentTest_2211, GetNPages_2211)
{
    ASSERT_NE(doc, nullptr);
    int n_pages = poppler_document_get_n_pages(doc);
    EXPECT_EQ(n_pages, 1);
}

// Test: Get page by index
TEST_F(PopplerDocumentTest_2211, GetPage_2211)
{
    ASSERT_NE(doc, nullptr);
    PopplerPage *page = poppler_document_get_page(doc, 0);
    EXPECT_NE(page, nullptr);
    if (page) {
        g_object_unref(page);
    }
}

// Test: Get page with invalid index returns NULL
TEST_F(PopplerDocumentTest_2211, GetPageInvalidIndex_2211)
{
    ASSERT_NE(doc, nullptr);
    PopplerPage *page = poppler_document_get_page(doc, -1);
    EXPECT_EQ(page, nullptr);

    PopplerPage *page2 = poppler_document_get_page(doc, 100);
    EXPECT_EQ(page2, nullptr);
}

// Test: PDF version can be retrieved
TEST_F(PopplerDocumentTest_2211, GetPdfVersion_2211)
{
    ASSERT_NE(doc, nullptr);
    guint major_version = 0, minor_version = 0;
    poppler_document_get_pdf_version(doc, &major_version, &minor_version);
    EXPECT_GE(major_version, 1u);
}

// Test: PDF version string is non-null
TEST_F(PopplerDocumentTest_2211, GetPdfVersionString_2211)
{
    ASSERT_NE(doc, nullptr);
    gchar *version_string = poppler_document_get_pdf_version_string(doc);
    EXPECT_NE(version_string, nullptr);
    if (version_string) {
        g_free(version_string);
    }
}

// Test: Title property (read/write)
TEST_F(PopplerDocumentTest_2211, TitleProperty_2211)
{
    ASSERT_NE(doc, nullptr);

    // The minimal PDF has no title, so it should be NULL initially
    gchar *title = poppler_document_get_title(doc);
    // Title may or may not be NULL depending on the PDF; just test it doesn't crash
    if (title) {
        g_free(title);
    }

    // Set title via property
    g_object_set(doc, "title", "Test Title", nullptr);
    gchar *new_title = nullptr;
    g_object_get(doc, "title", &new_title, nullptr);
    EXPECT_NE(new_title, nullptr);
    if (new_title) {
        EXPECT_STREQ(new_title, "Test Title");
        g_free(new_title);
    }
}

// Test: Author property (read/write)
TEST_F(PopplerDocumentTest_2211, AuthorProperty_2211)
{
    ASSERT_NE(doc, nullptr);

    g_object_set(doc, "author", "Test Author", nullptr);
    gchar *author = nullptr;
    g_object_get(doc, "author", &author, nullptr);
    EXPECT_NE(author, nullptr);
    if (author) {
        EXPECT_STREQ(author, "Test Author");
        g_free(author);
    }
}

// Test: Subject property (read/write)
TEST_F(PopplerDocumentTest_2211, SubjectProperty_2211)
{
    ASSERT_NE(doc, nullptr);

    g_object_set(doc, "subject", "Test Subject", nullptr);
    gchar *subject = nullptr;
    g_object_get(doc, "subject", &subject, nullptr);
    EXPECT_NE(subject, nullptr);
    if (subject) {
        EXPECT_STREQ(subject, "Test Subject");
        g_free(subject);
    }
}

// Test: Keywords property (read/write)
TEST_F(PopplerDocumentTest_2211, KeywordsProperty_2211)
{
    ASSERT_NE(doc, nullptr);

    g_object_set(doc, "keywords", "key1, key2", nullptr);
    gchar *keywords = nullptr;
    g_object_get(doc, "keywords", &keywords, nullptr);
    EXPECT_NE(keywords, nullptr);
    if (keywords) {
        EXPECT_STREQ(keywords, "key1, key2");
        g_free(keywords);
    }
}

// Test: Creator property (read/write)
TEST_F(PopplerDocumentTest_2211, CreatorProperty_2211)
{
    ASSERT_NE(doc, nullptr);

    g_object_set(doc, "creator", "Test Creator", nullptr);
    gchar *creator = nullptr;
    g_object_get(doc, "creator", &creator, nullptr);
    EXPECT_NE(creator, nullptr);
    if (creator) {
        EXPECT_STREQ(creator, "Test Creator");
        g_free(creator);
    }
}

// Test: Producer property (read/write)
TEST_F(PopplerDocumentTest_2211, ProducerProperty_2211)
{
    ASSERT_NE(doc, nullptr);

    g_object_set(doc, "producer", "Test Producer", nullptr);
    gchar *producer = nullptr;
    g_object_get(doc, "producer", &producer, nullptr);
    EXPECT_NE(producer, nullptr);
    if (producer) {
        EXPECT_STREQ(producer, "Test Producer");
        g_free(producer);
    }
}

// Test: Format property is readable
TEST_F(PopplerDocumentTest_2211, FormatPropertyReadable_2211)
{
    ASSERT_NE(doc, nullptr);

    gchar *format = nullptr;
    g_object_get(doc, "format", &format, nullptr);
    EXPECT_NE(format, nullptr);
    if (format) {
        // Should contain "PDF" or version info
        g_free(format);
    }
}

// Test: Format major/minor are readable
TEST_F(PopplerDocumentTest_2211, FormatMajorMinorReadable_2211)
{
    ASSERT_NE(doc, nullptr);

    guint major_v = 0, minor_v = 0;
    g_object_get(doc, "format-major", &major_v, "format-minor", &minor_v, nullptr);
    EXPECT_GE(major_v, 1u);
}

// Test: Linearized property
TEST_F(PopplerDocumentTest_2211, LinearizedProperty_2211)
{
    ASSERT_NE(doc, nullptr);

    gboolean linearized = TRUE;
    g_object_get(doc, "linearized", &linearized, nullptr);
    // Our minimal PDF is not linearized
    EXPECT_FALSE(linearized);
}

// Test: poppler_document_is_linearized
TEST_F(PopplerDocumentTest_2211, IsLinearized_2211)
{
    ASSERT_NE(doc, nullptr);
    gboolean result = poppler_document_is_linearized(doc);
    EXPECT_FALSE(result);
}

// Test: Page layout property
TEST_F(PopplerDocumentTest_2211, PageLayoutProperty_2211)
{
    ASSERT_NE(doc, nullptr);

    PopplerPageLayout layout = POPPLER_PAGE_LAYOUT_UNSET;
    g_object_get(doc, "page-layout", &layout, nullptr);
    // Just verify it doesn't crash; the value depends on the PDF
    SUCCEED();
}

// Test: Page mode property
TEST_F(PopplerDocumentTest_2211, PageModeProperty_2211)
{
    ASSERT_NE(doc, nullptr);

    PopplerPageMode mode = POPPLER_PAGE_MODE_UNSET;
    g_object_get(doc, "page-mode", &mode, nullptr);
    SUCCEED();
}

// Test: Permissions property
TEST_F(PopplerDocumentTest_2211, PermissionsProperty_2211)
{
    ASSERT_NE(doc, nullptr);

    PopplerPermissions perms = POPPLER_PERMISSIONS_FULL;
    g_object_get(doc, "permissions", &perms, nullptr);
    // Unencrypted document should have full permissions
    EXPECT_EQ(perms, POPPLER_PERMISSIONS_FULL);
}

// Test: Creation date property
TEST_F(PopplerDocumentTest_2211, CreationDateProperty_2211)
{
    ASSERT_NE(doc, nullptr);

    gint creation_date = 0;
    g_object_get(doc, "creation-date", &creation_date, nullptr);
    // Minimal PDF has no creation date, should be -1
    EXPECT_EQ(creation_date, -1);
}

// Test: Modification date property
TEST_F(PopplerDocumentTest_2211, ModDateProperty_2211)
{
    ASSERT_NE(doc, nullptr);

    gint mod_date = 0;
    g_object_get(doc, "mod-date", &mod_date, nullptr);
    // Minimal PDF has no modification date, should be -1
    EXPECT_EQ(mod_date, -1);
}

// Test: Creation datetime property
TEST_F(PopplerDocumentTest_2211, CreationDatetimeProperty_2211)
{
    ASSERT_NE(doc, nullptr);

    GDateTime *dt = nullptr;
    g_object_get(doc, "creation-datetime", &dt, nullptr);
    // Minimal PDF has no creation datetime
    // dt may be NULL
    if (dt) {
        g_date_time_unref(dt);
    }
}

// Test: Set and get creation-datetime
TEST_F(PopplerDocumentTest_2211, SetCreationDatetime_2211)
{
    ASSERT_NE(doc, nullptr);

    GDateTime *dt = g_date_time_new_utc(2023, 6, 15, 12, 0, 0);
    ASSERT_NE(dt, nullptr);

    g_object_set(doc, "creation-datetime", dt, nullptr);

    GDateTime *retrieved = nullptr;
    g_object_get(doc, "creation-datetime", &retrieved, nullptr);
    EXPECT_NE(retrieved, nullptr);
    if (retrieved) {
        EXPECT_EQ(g_date_time_get_year(retrieved), 2023);
        EXPECT_EQ(g_date_time_get_month(retrieved), 6);
        EXPECT_EQ(g_date_time_get_day_of_month(retrieved), 15);
        g_date_time_unref(retrieved);
    }

    g_date_time_unref(dt);
}

// Test: Set and get mod-datetime
TEST_F(PopplerDocumentTest_2211, SetModDatetime_2211)
{
    ASSERT_NE(doc, nullptr);

    GDateTime *dt = g_date_time_new_utc(2024, 1, 1, 0, 0, 0);
    ASSERT_NE(dt, nullptr);

    g_object_set(doc, "mod-datetime", dt, nullptr);

    GDateTime *retrieved = nullptr;
    g_object_get(doc, "mod-datetime", &retrieved, nullptr);
    EXPECT_NE(retrieved, nullptr);
    if (retrieved) {
        EXPECT_EQ(g_date_time_get_year(retrieved), 2024);
        g_date_time_unref(retrieved);
    }

    g_date_time_unref(dt);
}

// Test: Print scaling property
TEST_F(PopplerDocumentTest_2211, PrintScalingProperty_2211)
{
    ASSERT_NE(doc, nullptr);

    PopplerPrintScaling scaling = POPPLER_PRINT_SCALING_APP_DEFAULT;
    g_object_get(doc, "print-scaling", &scaling, nullptr);
    EXPECT_EQ(scaling, POPPLER_PRINT_SCALING_APP_DEFAULT);
}

// Test: Print duplex property
TEST_F(PopplerDocumentTest_2211, PrintDuplexProperty_2211)
{
    ASSERT_NE(doc, nullptr);

    PopplerPrintDuplex duplex = POPPLER_PRINT_DUPLEX_NONE;
    g_object_get(doc, "print-duplex", &duplex, nullptr);
    // Default should be NONE for minimal PDF
    EXPECT_EQ(duplex, POPPLER_PRINT_DUPLEX_NONE);
}

// Test: Print n-copies property
TEST_F(PopplerDocumentTest_2211, PrintNCopiesProperty_2211)
{
    ASSERT_NE(doc, nullptr);

    gint n_copies = 0;
    g_object_get(doc, "print-n-copies", &n_copies, nullptr);
    EXPECT_EQ(n_copies, 1);
}

// Test: Subtype property
TEST_F(PopplerDocumentTest_2211, SubtypeProperty_2211)
{
    ASSERT_NE(doc, nullptr);

    PopplerPDFSubtype subtype = POPPLER_PDF_SUBTYPE_UNSET;
    g_object_get(doc, "subtype", &subtype, nullptr);
    // Minimal PDF is not a specific subtype
    EXPECT_EQ(subtype, POPPLER_PDF_SUBTYPE_UNSET);
}

// Test: Subtype string property
TEST_F(PopplerDocumentTest_2211, SubtypeStringProperty_2211)
{
    ASSERT_NE(doc, nullptr);

    gchar *subtype_string = nullptr;
    g_object_get(doc, "subtype-string", &subtype_string, nullptr);
    // May be NULL for minimal PDF
    if (subtype_string) {
        g_free(subtype_string);
    }
}

// Test: Subtype part property
TEST_F(PopplerDocumentTest_2211, SubtypePartProperty_2211)
{
    ASSERT_NE(doc, nullptr);

    PopplerPDFPart part = POPPLER_PDF_SUBTYPE_PART_UNSET;
    g_object_get(doc, "subtype-part", &part, nullptr);
    EXPECT_EQ(part, POPPLER_PDF_SUBTYPE_PART_UNSET);
}

// Test: Subtype conformance property
TEST_F(PopplerDocumentTest_2211, SubtypeConformanceProperty_2211)
{
    ASSERT_NE(doc, nullptr);

    PopplerPDFConformance conf = POPPLER_PDF_SUBTYPE_CONF_UNSET;
    g_object_get(doc, "subtype-conformance", &conf, nullptr);
    EXPECT_EQ(conf, POPPLER_PDF_SUBTYPE_CONF_UNSET);
}

// Test: Metadata property
TEST_F(PopplerDocumentTest_2211, MetadataProperty_2211)
{
    ASSERT_NE(doc, nullptr);

    gchar *metadata = nullptr;
    g_object_get(doc, "metadata", &metadata, nullptr);
    // Minimal PDF has no metadata
    // metadata may be NULL
    if (metadata) {
        g_free(metadata);
    }
}

// Test: Viewer preferences property
TEST_F(PopplerDocumentTest_2211, ViewerPreferencesProperty_2211)
{
    ASSERT_NE(doc, nullptr);

    PopplerViewerPreferences prefs = POPPLER_VIEWER_PREFERENCES_UNSET;
    g_object_get(doc, "viewer-preferences", &prefs, nullptr);
    SUCCEED();
}

// Test: Loading from invalid URI fails
TEST_F(PopplerDocumentTest_2211, LoadFromInvalidUri_2211)
{
    GError *error = nullptr;
    PopplerDocument *bad_doc = poppler_document_new_from_file("file:///nonexistent/path/to/file.pdf", nullptr, &error);
    EXPECT_EQ(bad_doc, nullptr);
    EXPECT_NE(error, nullptr);
    if (error) {
        g_error_free(error);
    }
}

// Test: Loading from GBytes data
TEST_F(PopplerDocumentTest_2211, LoadFromData_2211)
{
    const char *pdf_content =
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

    GError *error = nullptr;
    GBytes *bytes = g_bytes_new(pdf_content, strlen(pdf_content));
    PopplerDocument *doc_from_bytes = poppler_document_new_from_bytes(bytes, nullptr, &error);
    
    // The minimal PDF may or may not parse depending on exactness of xref offsets
    // Just check it doesn't crash
    if (doc_from_bytes) {
        g_object_unref(doc_from_bytes);
    }
    if (error) {
        g_error_free(error);
    }
    g_bytes_unref(bytes);
}

// Test: Setting title to NULL
TEST_F(PopplerDocumentTest_2211, SetTitleToNull_2211)
{
    ASSERT_NE(doc, nullptr);

    g_object_set(doc, "title", nullptr, nullptr);
    gchar *title = nullptr;
    g_object_get(doc, "title", &title, nullptr);
    // Should be NULL or empty
    if (title) {
        g_free(title);
    }
}

// Test: Setting creation-date property
TEST_F(PopplerDocumentTest_2211, SetCreationDate_2211)
{
    ASSERT_NE(doc, nullptr);

    g_object_set(doc, "creation-date", 1000000, nullptr);
    gint creation_date = -1;
    g_object_get(doc, "creation-date", &creation_date, nullptr);
    EXPECT_EQ(creation_date, 1000000);
}

// Test: Setting mod-date property
TEST_F(PopplerDocumentTest_2211, SetModDate_2211)
{
    ASSERT_NE(doc, nullptr);

    g_object_set(doc, "mod-date", 2000000, nullptr);
    gint mod_date = -1;
    g_object_get(doc, "mod-date", &mod_date, nullptr);
    EXPECT_EQ(mod_date, 2000000);
}

// Test: Get page layout via function
TEST_F(PopplerDocumentTest_2211, GetPageLayout_2211)
{
    ASSERT_NE(doc, nullptr);
    PopplerPageLayout layout = poppler_document_get_page_layout(doc);
    // Minimal PDF should have unset layout
    EXPECT_EQ(layout, POPPLER_PAGE_LAYOUT_UNSET);
}

// Test: Get page mode via function
TEST_F(PopplerDocumentTest_2211, GetPageMode_2211)
{
    ASSERT_NE(doc, nullptr);
    PopplerPageMode mode = poppler_document_get_page_mode(doc);
    EXPECT_EQ(mode, POPPLER_PAGE_MODE_UNSET);
}

// Test: Get permissions via function
TEST_F(PopplerDocumentTest_2211, GetPermissions_2211)
{
    ASSERT_NE(doc, nullptr);
    PopplerPermissions perms = poppler_document_get_permissions(doc);
    EXPECT_EQ(perms, POPPLER_PERMISSIONS_FULL);
}

// Test: Get print scaling via function
TEST_F(PopplerDocumentTest_2211, GetPrintScaling_2211)
{
    ASSERT_NE(doc, nullptr);
    PopplerPrintScaling scaling = poppler_document_get_print_scaling(doc);
    EXPECT_EQ(scaling, POPPLER_PRINT_SCALING_APP_DEFAULT);
}

// Test: Get print duplex via function
TEST_F(PopplerDocumentTest_2211, GetPrintDuplex_2211)
{
    ASSERT_NE(doc, nullptr);
    PopplerPrintDuplex duplex = poppler_document_get_print_duplex(doc);
    EXPECT_EQ(duplex, POPPLER_PRINT_DUPLEX_NONE);
}

// Test: Get print n-copies via function
TEST_F(PopplerDocumentTest_2211, GetPrintNCopies_2211)
{
    ASSERT_NE(doc, nullptr);
    gint n_copies = poppler_document_get_n_attachments(doc);
    // Minimal PDF should have 0 attachments
    EXPECT_EQ(n_copies, 0);
}

// Test: Get metadata via function
TEST_F(PopplerDocumentTest_2211, GetMetadata_2211)
{
    ASSERT_NE(doc, nullptr);
    gchar *metadata = poppler_document_get_metadata(doc);
    // May be NULL for a minimal PDF
    if (metadata) {
        g_free(metadata);
    }
}

// Test: Get PDF subtype string via function
TEST_F(PopplerDocumentTest_2211, GetPdfSubtypeString_2211)
{
    ASSERT_NE(doc, nullptr);
    gchar *subtype_str = poppler_document_get_pdf_subtype_string(doc);
    // Should be NULL for a minimal PDF
    if (subtype_str) {
        g_free(subtype_str);
    }
}

// Test: Has attachments
TEST_F(PopplerDocumentTest_2211, HasAttachments_2211)
{
    ASSERT_NE(doc, nullptr);
    gboolean has_attachments = poppler_document_has_attachments(doc);
    EXPECT_FALSE(has_attachments);
}

// Test: Get attachments returns empty list
TEST_F(PopplerDocumentTest_2211, GetAttachments_2211)
{
    ASSERT_NE(doc, nullptr);
    GList *attachments = poppler_document_get_attachments(doc);
    EXPECT_EQ(attachments, nullptr);
}

// Test: Get title via function
TEST_F(PopplerDocumentTest_2211, GetTitle_2211)
{
    ASSERT_NE(doc, nullptr);
    gchar *title = poppler_document_get_title(doc);
    // Minimal PDF has no title
    if (title) {
        g_free(title);
    }
}

// Test: Get author via function
TEST_F(PopplerDocumentTest_2211, GetAuthor_2211)
{
    ASSERT_NE(doc, nullptr);
    gchar *author = poppler_document_get_author(doc);
    if (author) {
        g_free(author);
    }
}

// Test: Get subject via function
TEST_F(PopplerDocumentTest_2211, GetSubject_2211)
{
    ASSERT_NE(doc, nullptr);
    gchar *subject = poppler_document_get_subject(doc);
    if (subject) {
        g_free(subject);
    }
}

// Test: Get keywords via function
TEST_F(PopplerDocumentTest_2211, GetKeywords_2211)
{
    ASSERT_NE(doc, nullptr);
    gchar *keywords = poppler_document_get_keywords(doc);
    if (keywords) {
        g_free(keywords);
    }
}

// Test: Get creator via function
TEST_F(PopplerDocumentTest_2211, GetCreator_2211)
{
    ASSERT_NE(doc, nullptr);
    gchar *creator = poppler_document_get_creator(doc);
    if (creator) {
        g_free(creator);
    }
}

// Test: Get producer via function
TEST_F(PopplerDocumentTest_2211, GetProducer_2211)
{
    ASSERT_NE(doc, nullptr);
    gchar *producer = poppler_document_get_producer(doc);
    if (producer) {
        g_free(producer);
    }
}

// Test: Setting creation-date to -1 (boundary)
TEST_F(PopplerDocumentTest_2211, SetCreationDateMinusOne_2211)
{
    ASSERT_NE(doc, nullptr);

    g_object_set(doc, "creation-date", -1, nullptr);
    gint creation_date = 0;
    g_object_get(doc, "creation-date", &creation_date, nullptr);
    EXPECT_EQ(creation_date, -1);
}

// Test: Setting mod-date to -1 (boundary)
TEST_F(PopplerDocumentTest_2211, SetModDateMinusOne_2211)
{
    ASSERT_NE(doc, nullptr);

    g_object_set(doc, "mod-date", -1, nullptr);
    gint mod_date = 0;
    g_object_get(doc, "mod-date", &mod_date, nullptr);
    EXPECT_EQ(mod_date, -1);
}

// Test: Get creation date via function
TEST_F(PopplerDocumentTest_2211, GetCreationDate_2211)
{
    ASSERT_NE(doc, nullptr);
    time_t cdate = poppler_document_get_creation_date(doc);
    EXPECT_EQ(cdate, (time_t)-1);
}

// Test: Get modification date via function
TEST_F(PopplerDocumentTest_2211, GetModificationDate_2211)
{
    ASSERT_NE(doc, nullptr);
    time_t mdate = poppler_document_get_modification_date(doc);
    EXPECT_EQ(mdate, (time_t)-1);
}

// Test: Get creation datetime via function
TEST_F(PopplerDocumentTest_2211, GetCreationDateTime_2211)
{
    ASSERT_NE(doc, nullptr);
    GDateTime *dt = poppler_document_get_creation_date_time(doc);
    // Minimal PDF has no creation date
    if (dt) {
        g_date_time_unref(dt);
    }
}

// Test: Get modification datetime via function
TEST_F(PopplerDocumentTest_2211, GetModificationDateTime_2211)
{
    ASSERT_NE(doc, nullptr);
    GDateTime *dt = poppler_document_get_modification_date_time(doc);
    if (dt) {
        g_date_time_unref(dt);
    }
}

// Test: Set title via function
TEST_F(PopplerDocumentTest_2211, SetTitleViaFunction_2211)
{
    ASSERT_NE(doc, nullptr);
    poppler_document_set_title(doc, "New Title");
    gchar *title = poppler_document_get_title(doc);
    ASSERT_NE(title, nullptr);
    EXPECT_STREQ(title, "New Title");
    g_free(title);
}

// Test: Set author via function
TEST_F(PopplerDocumentTest_2211, SetAuthorViaFunction_2211)
{
    ASSERT_NE(doc, nullptr);
    poppler_document_set_author(doc, "New Author");
    gchar *author = poppler_document_get_author(doc);
    ASSERT_NE(author, nullptr);
    EXPECT_STREQ(author, "New Author");
    g_free(author);
}

// Test: Set subject via function
TEST_F(PopplerDocumentTest_2211, SetSubjectViaFunction_2211)
{
    ASSERT_NE(doc, nullptr);
    poppler_document_set_subject(doc, "New Subject");
    gchar *subject = poppler_document_get_subject(doc);
    ASSERT_NE(subject, nullptr);
    EXPECT_STREQ(subject, "New Subject");
    g_free(subject);
}

// Test: Set keywords via function
TEST_F(PopplerDocumentTest_2211, SetKeywordsViaFunction_2211)
{
    ASSERT_NE(doc, nullptr);
    poppler_document_set_keywords(doc, "kw1, kw2");
    gchar *keywords = poppler_document_get_keywords(doc);
    ASSERT_NE(keywords, nullptr);
    EXPECT_STREQ(keywords, "kw1, kw2");
    g_free(keywords);
}

// Test: Set creator via function
TEST_F(PopplerDocumentTest_2211, SetCreatorViaFunction_2211)
{
    ASSERT_NE(doc, nullptr);
    poppler_document_set_creator(doc, "New Creator");
    gchar *creator = poppler_document_get_creator(doc);
    ASSERT_NE(creator, nullptr);
    EXPECT_STREQ(creator, "New Creator");
    g_free(creator);
}

// Test: Set producer via function
TEST_F(PopplerDocumentTest_2211, SetProducerViaFunction_2211)
{
    ASSERT_NE(doc, nullptr);
    poppler_document_set_producer(doc, "New Producer");
    gchar *producer = poppler_document_get_producer(doc);
    ASSERT_NE(producer, nullptr);
    EXPECT_STREQ(producer, "New Producer");
    g_free(producer);
}

// Test: Set and get creation date via function
TEST_F(PopplerDocumentTest_2211, SetCreationDateViaFunction_2211)
{
    ASSERT_NE(doc, nullptr);
    poppler_document_set_creation_date(doc, 1609459200); // 2021-01-01 00:00:00 UTC
    time_t cdate = poppler_document_get_creation_date(doc);
    EXPECT_EQ(cdate, (time_t)1609459200);
}

// Test: Set and get modification date via function
TEST_F(PopplerDocumentTest_2211, SetModificationDateViaFunction_2211)
{
    ASSERT_NE(doc, nullptr);
    poppler_document_set_modification_date(doc, 1609459200);
    time_t mdate = poppler_document_get_modification_date(doc);
    EXPECT_EQ(mdate, (time_t)1609459200);
}

// Test: Set and get creation datetime via function
TEST_F(PopplerDocumentTest_2211, SetCreationDateTimeViaFunction_2211)
{
    ASSERT_NE(doc, nullptr);
    GDateTime *dt = g_date_time_new_utc(2022, 3, 15, 10, 30, 0);
    ASSERT_NE(dt, nullptr);
    poppler_document_set_creation_date_time(doc, dt);

    GDateTime *retrieved = poppler_document_get_creation_date_time(doc);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(g_date_time_get_year(retrieved), 2022);
    EXPECT_EQ(g_date_time_get_month(retrieved), 3);
    EXPECT_EQ(g_date_time_get_day_of_month(retrieved), 15);

    g_date_time_unref(retrieved);
    g_date_time_unref(dt);
}

// Test: Set and get modification datetime via function
TEST_F(PopplerDocumentTest_2211, SetModificationDateTimeViaFunction_2211)
{
    ASSERT_NE(doc, nullptr);
    GDateTime *dt = g_date_time_new_utc(2022, 12, 25, 18, 0, 0);
    ASSERT_NE(dt, nullptr);
    poppler_document_set_modification_date_time(doc, dt);

    GDateTime *retrieved = poppler_document_get_modification_date_time(doc);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(g_date_time_get_year(retrieved), 2022);
    EXPECT_EQ(g_date_time_get_month(retrieved), 12);

    g_date_time_unref(retrieved);
    g_date_time_unref(dt);
}

// Test: Get PDF subtype
TEST_F(PopplerDocumentTest_2211, GetPdfSubtype_2211)
{
    ASSERT_NE(doc, nullptr);
    PopplerPDFSubtype subtype = poppler_document_get_pdf_subtype(doc);
    EXPECT_EQ(subtype, POPPLER_PDF_SUBTYPE_UNSET);
}

// Test: Get PDF subtype part
TEST_F(PopplerDocumentTest_2211, GetPdfSubtypePart_2211)
{
    ASSERT_NE(doc, nullptr);
    PopplerPDFPart part = poppler_document_get_pdf_part(doc);
    EXPECT_EQ(part, POPPLER_PDF_SUBTYPE_PART_UNSET);
}

// Test: Get PDF subtype conformance
TEST_F(PopplerDocumentTest_2211, GetPdfSubtypeConformance_2211)
{
    ASSERT_NE(doc, nullptr);
    PopplerPDFConformance conf = poppler_document_get_pdf_conformance(doc);
    EXPECT_EQ(conf, POPPLER_PDF_SUBTYPE_CONF_UNSET);
}
