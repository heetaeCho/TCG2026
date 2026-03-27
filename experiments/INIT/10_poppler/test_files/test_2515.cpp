// info_create_widget_test_2515.cc
#include <gtest/gtest.h>

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>

#include <gtk/gtk.h>
#include <poppler.h>

// Function under test (implemented in the codebase).
extern "C" GtkWidget* pgd_info_create_widget(PopplerDocument* document);

namespace {

class PgdInfoCreateWidgetTest_2515 : public ::testing::Test {
 protected:
  static void SetUpTestSuite() {
    // Initialize GTK once for the whole test suite.
    // Using gtk_init_check so tests can run headless in CI.
    int argc = 0;
    char** argv = nullptr;
    (void)gtk_init_check(&argc, &argv);
  }

  static std::string BuildMinimalPdfWithInfoAndOptionalId(bool include_id,
                                                         const std::string& title,
                                                         const std::string& author,
                                                         const std::string& subject,
                                                         const std::string& keywords,
                                                         const std::string& creator,
                                                         const std::string& producer,
                                                         const std::string& creation_date_pdf,
                                                         const std::string& mod_date_pdf,
                                                         const std::string& perm_id_32,
                                                         const std::string& up_id_32) {
    // Generates a tiny, syntactically valid PDF with:
    // - Catalog includes /PageMode and /PageLayout
    // - Info dictionary includes common metadata
    // - Optional Trailer /ID with two 16-byte strings represented as 32 ASCII chars each
    //
    // NOTE: This is a *data fixture builder*, not re-implementing any Poppler logic.

    auto pdf_escape = [](const std::string& s) {
      // Minimal escaping for PDF literal strings.
      std::string out;
      out.reserve(s.size());
      for (char c : s) {
        if (c == '(' || c == ')' || c == '\\') out.push_back('\\');
        out.push_back(c);
      }
      return out;
    };

    std::ostringstream body;
    body << "%PDF-1.7\n";
    body << "%\xE2\xE3\xCF\xD3\n";  // binary comment line

    // Track offsets for xref.
    std::vector<long> offsets;
    offsets.push_back(0);  // object 0 (free)

    auto add_obj = [&](int obj_num, const std::string& content) {
      offsets.resize(std::max<size_t>(offsets.size(), static_cast<size_t>(obj_num + 1)));
      offsets[obj_num] = static_cast<long>(body.tellp());
      body << obj_num << " 0 obj\n" << content << "\nendobj\n";
    };

    // 1: Catalog
    add_obj(1,
            "<< /Type /Catalog /Pages 2 0 R"
            " /PageMode /UseThumbs"
            " /PageLayout /TwoColumnLeft"
            " >>");

    // 2: Pages
    add_obj(2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>");

    // 3: Page
    add_obj(3,
            "<< /Type /Page /Parent 2 0 R"
            " /MediaBox [0 0 200 200]"
            " /Contents 4 0 R"
            " /Resources << >>"
            " >>");

    // 4: Contents (empty)
    add_obj(4, "<< /Length 0 >>\nstream\n\nendstream");

    // 5: Info
    {
      std::ostringstream info;
      info << "<<"
           << " /Title (" << pdf_escape(title) << ")"
           << " /Author (" << pdf_escape(author) << ")"
           << " /Subject (" << pdf_escape(subject) << ")"
           << " /Keywords (" << pdf_escape(keywords) << ")"
           << " /Creator (" << pdf_escape(creator) << ")"
           << " /Producer (" << pdf_escape(producer) << ")";
      if (!creation_date_pdf.empty()) info << " /CreationDate (" << pdf_escape(creation_date_pdf) << ")";
      if (!mod_date_pdf.empty()) info << " /ModDate (" << pdf_escape(mod_date_pdf) << ")";
      info << " >>";
      add_obj(5, info.str());
    }

    // Xref
    long xref_pos = static_cast<long>(body.tellp());
    body << "xref\n";
    body << "0 6\n";
    body << "0000000000 65535 f \n";
    for (int i = 1; i <= 5; ++i) {
      body << std::setw(10) << std::setfill('0') << offsets[i] << " 00000 n \n";
    }

    // Trailer
    body << "trailer\n";
    body << "<< /Size 6 /Root 1 0 R /Info 5 0 R";
    if (include_id) {
      // /ID takes two strings; Poppler's glib API commonly exposes 32-char IDs.
      // Use literal strings of length 32 (ASCII) to make them easy to observe.
      body << " /ID [(" << pdf_escape(perm_id_32) << ")(" << pdf_escape(up_id_32) << ")]";
    }
    body << " >>\n";
    body << "startxref\n" << xref_pos << "\n%%EOF\n";

    return body.str();
  }

  static PopplerDocument* LoadDocFromPdfData(const std::string& pdf_bytes) {
    GError* error = nullptr;
    PopplerDocument* doc =
        poppler_document_new_from_data(pdf_bytes.data(),
                                       static_cast<int>(pdf_bytes.size()),
                                       /*password=*/nullptr,
                                       &error);
    if (!doc && error) {
      g_error_free(error);
    }
    return doc;
  }

  static void CollectLabelTexts(GtkWidget* widget, std::vector<std::string>* out) {
    if (!widget || !out) return;

    if (GTK_IS_LABEL(widget)) {
      const char* txt = gtk_label_get_text(GTK_LABEL(widget));
      if (txt) out->push_back(txt);
      return;
    }

#if GTK_CHECK_VERSION(4, 0, 0)
    for (GtkWidget* child = gtk_widget_get_first_child(widget); child;
         child = gtk_widget_get_next_sibling(child)) {
      CollectLabelTexts(child, out);
    }
#else
    if (GTK_IS_CONTAINER(widget)) {
      GList* children = gtk_container_get_children(GTK_CONTAINER(widget));
      for (GList* it = children; it; it = it->next) {
        CollectLabelTexts(GTK_WIDGET(it->data), out);
      }
      g_list_free(children);
    }
#endif
  }

  static bool AnyLabelContains(const std::vector<std::string>& labels, const std::string& needle) {
    return std::any_of(labels.begin(), labels.end(), [&](const std::string& s) {
      return s.find(needle) != std::string::npos;
    });
  }

  static bool AnyLabelEquals(const std::vector<std::string>& labels, const std::string& needle) {
    return std::any_of(labels.begin(), labels.end(), [&](const std::string& s) { return s == needle; });
  }
};

TEST_F(PgdInfoCreateWidgetTest_2515, CreatesVBoxWithHeaderAndFrame_2515) {
  const std::string perm_id = "0123456789abcdef0123456789abcdef";
  const std::string up_id   = "fedcba9876543210fedcba9876543210";

  std::string pdf = BuildMinimalPdfWithInfoAndOptionalId(
      /*include_id=*/true,
      /*title=*/"MyTitle",
      /*author=*/"MyAuthor",
      /*subject=*/"MySubject",
      /*keywords=*/"MyKeywords",
      /*creator=*/"MyCreator",
      /*producer=*/"MyProducer",
      /*creation_date_pdf=*/"D:20260101000000Z",
      /*mod_date_pdf=*/"D:20260201000000Z",
      perm_id, up_id);

  PopplerDocument* doc = LoadDocFromPdfData(pdf);
  ASSERT_NE(doc, nullptr);

  GtkWidget* widget = pgd_info_create_widget(doc);
  ASSERT_NE(widget, nullptr);
  EXPECT_TRUE(GTK_IS_BOX(widget));

#if !GTK_CHECK_VERSION(4, 0, 0)
  // In GTK3, we can verify children count via container list.
  GList* children = gtk_container_get_children(GTK_CONTAINER(widget));
  ASSERT_NE(children, nullptr);
  // Expected structure: [header label, frame] at minimum.
  EXPECT_GE(g_list_length(children), 2u);
  g_list_free(children);
#endif

  // Find labels and ensure the header includes "Poppler".
  std::vector<std::string> labels;
  CollectLabelTexts(widget, &labels);
  EXPECT_TRUE(AnyLabelContains(labels, "Poppler"));

  g_object_unref(doc);
}

TEST_F(PgdInfoCreateWidgetTest_2515, IncludesDocumentPropertyValues_2515) {
  const std::string perm_id = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
  const std::string up_id   = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb";

  std::string pdf = BuildMinimalPdfWithInfoAndOptionalId(
      /*include_id=*/true,
      /*title=*/"Title_2515",
      /*author=*/"Author_2515",
      /*subject=*/"Subject_2515",
      /*keywords=*/"Keywords_2515",
      /*creator=*/"Creator_2515",
      /*producer=*/"Producer_2515",
      /*creation_date_pdf=*/"D:20260101000000Z",
      /*mod_date_pdf=*/"D:20260201000000Z",
      perm_id, up_id);

  PopplerDocument* doc = LoadDocFromPdfData(pdf);
  ASSERT_NE(doc, nullptr);

  GtkWidget* widget = pgd_info_create_widget(doc);
  ASSERT_NE(widget, nullptr);

  std::vector<std::string> labels;
  CollectLabelTexts(widget, &labels);

  // Values from the /Info dictionary should appear as label texts somewhere in the widget tree.
  EXPECT_TRUE(AnyLabelContains(labels, "Title_2515"));
  EXPECT_TRUE(AnyLabelContains(labels, "Author_2515"));
  EXPECT_TRUE(AnyLabelContains(labels, "Subject_2515"));
  EXPECT_TRUE(AnyLabelContains(labels, "Keywords_2515"));
  EXPECT_TRUE(AnyLabelContains(labels, "Creator_2515"));
  EXPECT_TRUE(AnyLabelContains(labels, "Producer_2515"));

  // Linearized is shown as "Yes"/"No". For this synthetic PDF (not linearized), "No" should appear.
  // (We don't assert where, only that the UI contains the expected visible string.)
  EXPECT_TRUE(AnyLabelEquals(labels, "No") || AnyLabelEquals(labels, "Yes"));

  g_object_unref(doc);
}

TEST_F(PgdInfoCreateWidgetTest_2515, IncludesPermanentAndUpdateIdWhenAvailable_2515) {
  const std::string perm_id = "0123456789abcdef0123456789abcdef";
  const std::string up_id   = "fedcba9876543210fedcba9876543210";

  std::string pdf = BuildMinimalPdfWithInfoAndOptionalId(
      /*include_id=*/true,
      /*title=*/"T",
      /*author=*/"A",
      /*subject=*/"S",
      /*keywords=*/"K",
      /*creator=*/"C",
      /*producer=*/"P",
      /*creation_date_pdf=*/"D:20260101000000Z",
      /*mod_date_pdf=*/"D:20260201000000Z",
      perm_id, up_id);

  PopplerDocument* doc = LoadDocFromPdfData(pdf);
  ASSERT_NE(doc, nullptr);

  GtkWidget* widget = pgd_info_create_widget(doc);
  ASSERT_NE(widget, nullptr);

  std::vector<std::string> labels;
  CollectLabelTexts(widget, &labels);

  // The implementation takes the first 32 chars via g_strndup(..., 32).
  EXPECT_TRUE(AnyLabelContains(labels, perm_id.substr(0, 32)));
  EXPECT_TRUE(AnyLabelContains(labels, up_id.substr(0, 32)));

  g_object_unref(doc);
}

TEST_F(PgdInfoCreateWidgetTest_2515, OmitsIdRowsWhenDocumentHasNoId_2515) {
  const std::string perm_id = "0123456789abcdef0123456789abcdef";
  const std::string up_id   = "fedcba9876543210fedcba9876543210";

  std::string pdf = BuildMinimalPdfWithInfoAndOptionalId(
      /*include_id=*/false,
      /*title=*/"NoIdTitle_2515",
      /*author=*/"NoIdAuthor_2515",
      /*subject=*/"NoIdSubject_2515",
      /*keywords=*/"NoIdKeywords_2515",
      /*creator=*/"NoIdCreator_2515",
      /*producer=*/"NoIdProducer_2515",
      /*creation_date_pdf=*/"D:20260101000000Z",
      /*mod_date_pdf=*/"D:20260201000000Z",
      perm_id, up_id);

  PopplerDocument* doc = LoadDocFromPdfData(pdf);
  ASSERT_NE(doc, nullptr);

  GtkWidget* widget = pgd_info_create_widget(doc);
  ASSERT_NE(widget, nullptr);

  std::vector<std::string> labels;
  CollectLabelTexts(widget, &labels);

  // When /ID is absent, the "Permanent ID"/"Update ID" values should not be present.
  EXPECT_FALSE(AnyLabelContains(labels, perm_id.substr(0, 32)));
  EXPECT_FALSE(AnyLabelContains(labels, up_id.substr(0, 32)));

  g_object_unref(doc);
}

TEST_F(PgdInfoCreateWidgetTest_2515, HandlesLongMetadataStrings_2515) {
  std::string long_title(256, 'X');
  long_title.replace(0, 12, "LONGTITLE_");

  const std::string perm_id = "cccccccccccccccccccccccccccccccc";
  const std::string up_id   = "dddddddddddddddddddddddddddddddd";

  std::string pdf = BuildMinimalPdfWithInfoAndOptionalId(
      /*include_id=*/true,
      /*title=*/long_title,
      /*author=*/"AuthorLong_2515",
      /*subject=*/"SubjectLong_2515",
      /*keywords=*/"KeywordsLong_2515",
      /*creator=*/"CreatorLong_2515",
      /*producer=*/"ProducerLong_2515",
      /*creation_date_pdf=*/"D:20260101000000Z",
      /*mod_date_pdf=*/"D:20260201000000Z",
      perm_id, up_id);

  PopplerDocument* doc = LoadDocFromPdfData(pdf);
  ASSERT_NE(doc, nullptr);

  GtkWidget* widget = pgd_info_create_widget(doc);
  ASSERT_NE(widget, nullptr);

  std::vector<std::string> labels;
  CollectLabelTexts(widget, &labels);

  // Ensure the long title is surfaced somewhere in the widget tree (no crash and visible text).
  EXPECT_TRUE(AnyLabelContains(labels, "LONGTITLE_"));
  EXPECT_TRUE(AnyLabelContains(labels, long_title));

  g_object_unref(doc);
}

}  // namespace