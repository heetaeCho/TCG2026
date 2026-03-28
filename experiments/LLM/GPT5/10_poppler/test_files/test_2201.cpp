// poppler-document-get-permissions-test_2201.cc
#include <gtest/gtest.h>

#include <glib-object.h>
#include <glib.h>

extern "C" {
#include <poppler.h>
}

// Helper: build a minimal valid PDF in-memory with correct xref offsets.
static std::string MakeMinimalPdf_2201() {
  std::string pdf;
  pdf.reserve(1024);

  auto append = [&](const std::string& s) { pdf += s; };
  auto offset = [&]() -> size_t { return pdf.size(); };

  append("%PDF-1.4\n");
  // Object 1: Catalog
  const size_t off1 = offset();
  append("1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n");
  // Object 2: Pages
  const size_t off2 = offset();
  append("2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n");
  // Object 3: Page
  const size_t off3 = offset();
  append("3 0 obj\n"
         "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200]\n"
         "   /Contents 4 0 R /Resources << >> >>\n"
         "endobj\n");
  // Object 4: empty contents stream
  const size_t off4 = offset();
  append("4 0 obj\n<< /Length 0 >>\nstream\nendstream\nendobj\n");

  // xref table
  const size_t xref_off = offset();
  append("xref\n");
  append("0 5\n");
  append("0000000000 65535 f \n");

  auto fmt_off = [](size_t off) {
    char buf[32];
    // PDF xref offsets are 10 digits, zero-padded.
    std::snprintf(buf, sizeof(buf), "%010zu", off);
    return std::string(buf);
  };

  append(fmt_off(off1) + " 00000 n \n");
  append(fmt_off(off2) + " 00000 n \n");
  append(fmt_off(off3) + " 00000 n \n");
  append(fmt_off(off4) + " 00000 n \n");

  // trailer + startxref
  append("trailer\n<< /Size 5 /Root 1 0 R >>\n");
  append("startxref\n");
  append(std::to_string(xref_off));
  append("\n%%EOF\n");

  return pdf;
}

class PopplerDocumentGetPermissionsTest_2201 : public ::testing::Test {
 protected:
  void TearDown() override {
    if (doc_) {
      g_object_unref(doc_);
      doc_ = nullptr;
    }
    if (error_) {
      g_error_free(error_);
      error_ = nullptr;
    }
  }

  void LoadMinimalPdf_2201() {
    const std::string pdf = MakeMinimalPdf_2201();
    doc_ = poppler_document_new_from_data(pdf.data(),
                                         static_cast<int>(pdf.size()),
                                         /*password=*/nullptr,
                                         &error_);
  }

  PopplerDocument* doc_ = nullptr;
  GError* error_ = nullptr;
};

TEST_F(PopplerDocumentGetPermissionsTest_2201, NullDocumentReturnsFull_2201) {
  // g_return_val_if_fail should return POPPLER_PERMISSIONS_FULL for invalid input.
  const PopplerPermissions perms = poppler_document_get_permissions(nullptr);
  EXPECT_EQ(perms, POPPLER_PERMISSIONS_FULL);
}

TEST_F(PopplerDocumentGetPermissionsTest_2201, NonDocumentGObjectReturnsFull_2201) {
  GObject* obj = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(obj, nullptr);

  // Intentionally pass a non-PopplerDocument pointer to exercise type checking.
  const PopplerPermissions perms =
      poppler_document_get_permissions(reinterpret_cast<PopplerDocument*>(obj));
  EXPECT_EQ(perms, POPPLER_PERMISSIONS_FULL);

  g_object_unref(obj);
}

TEST_F(PopplerDocumentGetPermissionsTest_2201, MinimalValidPdfLoads_2201) {
  LoadMinimalPdf_2201();
  ASSERT_EQ(error_, nullptr) << (error_ ? error_->message : "");
  ASSERT_NE(doc_, nullptr);
}

TEST_F(PopplerDocumentGetPermissionsTest_2201, UnencryptedPdfReturnsFullPermissions_2201) {
  LoadMinimalPdf_2201();
  ASSERT_EQ(error_, nullptr) << (error_ ? error_->message : "");
  ASSERT_NE(doc_, nullptr);

  const PopplerPermissions perms = poppler_document_get_permissions(doc_);
  EXPECT_EQ(perms, POPPLER_PERMISSIONS_FULL);
}

TEST_F(PopplerDocumentGetPermissionsTest_2201, ReturnedPermissionsAreWithinMask_2201) {
  LoadMinimalPdf_2201();
  ASSERT_EQ(error_, nullptr) << (error_ ? error_->message : "");
  ASSERT_NE(doc_, nullptr);

  const PopplerPermissions perms = poppler_document_get_permissions(doc_);
  const guint mask = static_cast<guint>(POPPLER_PERMISSIONS_FULL);
  const guint got = static_cast<guint>(perms);

  // Boundary condition: no bits outside the defined FULL mask.
  EXPECT_EQ((got & ~mask), 0u);
}

TEST_F(PopplerDocumentGetPermissionsTest_2201, FullPermissionsContainAllIndividualBits_2201) {
  LoadMinimalPdf_2201();
  ASSERT_EQ(error_, nullptr) << (error_ ? error_->message : "");
  ASSERT_NE(doc_, nullptr);

  const guint got = static_cast<guint>(poppler_document_get_permissions(doc_));

  EXPECT_NE((got & POPPLER_PERMISSIONS_OK_TO_PRINT), 0u);
  EXPECT_NE((got & POPPLER_PERMISSIONS_OK_TO_MODIFY), 0u);
  EXPECT_NE((got & POPPLER_PERMISSIONS_OK_TO_COPY), 0u);
  EXPECT_NE((got & POPPLER_PERMISSIONS_OK_TO_ADD_NOTES), 0u);
  EXPECT_NE((got & POPPLER_PERMISSIONS_OK_TO_FILL_FORM), 0u);
  EXPECT_NE((got & POPPLER_PERMISSIONS_OK_TO_EXTRACT_CONTENTS), 0u);
  EXPECT_NE((got & POPPLER_PERMISSIONS_OK_TO_ASSEMBLE), 0u);
  EXPECT_NE((got & POPPLER_PERMISSIONS_OK_TO_PRINT_HIGH_RESOLUTION), 0u);
}