// File: poppler-form-field-new-test_2307.cc
//
// Unit tests for _poppler_form_field_new() in poppler-form-field.cc
// TEST_ID: 2307

#include <gtest/gtest.h>

#include <glib-object.h>
#include <poppler.h>

#include "poppler-private.h"          // for PopplerFormField (opaque-ish) and internal helpers
#include "../poppler/Form.h"          // for FormWidget

extern "C" {
// Function under test (internal)
PopplerFormField *_poppler_form_field_new(PopplerDocument *document, FormWidget *field);
}

namespace {

class PopplerFormFieldNewTest_2307 : public ::testing::Test {
protected:
  static std::string BuildMinimalPdfData() {
    // Build a tiny valid PDF with computed xref offsets so Poppler can parse it reliably.
    // Objects:
    //  1: Catalog -> Pages 2
    //  2: Pages -> Kid 3
    //  3: Page -> Contents 4
    //  4: Empty contents stream
    std::string pdf;
    pdf += "%PDF-1.4\n";
    pdf += "%\xE2\xE3\xCF\xD3\n"; // binary comment

    struct Obj {
      int num;
      std::string body;
    };
    std::vector<Obj> objs = {
        {1, "<< /Type /Catalog /Pages 2 0 R >>"},
        {2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>"},
        {3, "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 4 0 R >>"},
        {4, "<< /Length 0 >>\nstream\n\nendstream"},
    };

    // Track byte offsets for xref (object numbers start at 1).
    std::vector<size_t> offsets(5, 0);

    for (const auto &o : objs) {
      offsets[o.num] = pdf.size();
      pdf += std::to_string(o.num) + " 0 obj\n";
      pdf += o.body + "\n";
      pdf += "endobj\n";
    }

    const size_t xref_offset = pdf.size();
    pdf += "xref\n";
    pdf += "0 5\n";
    pdf += "0000000000 65535 f \n";
    for (int i = 1; i <= 4; ++i) {
      char buf[32];
      // 10-digit, zero-padded offsets, generation 00000, in-use 'n'
      snprintf(buf, sizeof(buf), "%010lu 00000 n \n",
               static_cast<unsigned long>(offsets[i]));
      pdf += buf;
    }

    pdf += "trailer\n";
    pdf += "<< /Size 5 /Root 1 0 R >>\n";
    pdf += "startxref\n";
    pdf += std::to_string(xref_offset) + "\n";
    pdf += "%%EOF\n";
    return pdf;
  }

  static PopplerDocument *NewDocFromMinimalPdfOrFail() {
    const std::string pdf = BuildMinimalPdfData();
    GError *error = nullptr;
    PopplerDocument *doc =
        poppler_document_new_from_data(pdf.c_str(), static_cast<int>(pdf.size()), nullptr, &error);
    if (!doc) {
      std::string msg = "poppler_document_new_from_data failed";
      if (error && error->message) {
        msg += std::string(": ") + error->message;
      }
      if (error) {
        g_error_free(error);
      }
      ADD_FAILURE() << msg;
      return nullptr;
    }
    if (error) {
      g_error_free(error);
    }
    return doc;
  }

  static void WeakNotifySetBool(gpointer data, GObject * /*where_the_object_was*/) {
    auto *flag = static_cast<bool *>(data);
    *flag = true;
  }

  static FormWidget *DummyNonNullFormWidgetPtr() {
    // Only used as a non-null pointer for g_return_val_if_fail checks and storage.
    // We never dereference it in these tests.
    static alignas(void *) unsigned char dummy[sizeof(void *)];
    return reinterpret_cast<FormWidget *>(&dummy[0]);
  }
};

TEST_F(PopplerFormFieldNewTest_2307, NullDocumentReturnsNull_2307) {
  FormWidget *dummy = DummyNonNullFormWidgetPtr();
  PopplerFormField *field = _poppler_form_field_new(nullptr, dummy);
  EXPECT_EQ(field, nullptr);
}

TEST_F(PopplerFormFieldNewTest_2307, NonDocumentGObjectReturnsNull_2307) {
  // Pass an object that is not a PopplerDocument to trigger POPPLER_IS_DOCUMENT failure.
  GObject *not_a_doc = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(not_a_doc, nullptr);

  FormWidget *dummy = DummyNonNullFormWidgetPtr();
  PopplerFormField *field =
      _poppler_form_field_new(reinterpret_cast<PopplerDocument *>(not_a_doc), dummy);

  EXPECT_EQ(field, nullptr);

  g_object_unref(not_a_doc);
}

TEST_F(PopplerFormFieldNewTest_2307, NullFieldReturnsNull_2307) {
  PopplerDocument *doc = NewDocFromMinimalPdfOrFail();
  ASSERT_NE(doc, nullptr);

  PopplerFormField *field = _poppler_form_field_new(doc, nullptr);
  EXPECT_EQ(field, nullptr);

  g_object_unref(doc);
}

TEST_F(PopplerFormFieldNewTest_2307, SuccessReturnsFormFieldObject_2307) {
  PopplerDocument *doc = NewDocFromMinimalPdfOrFail();
  ASSERT_NE(doc, nullptr);

  FormWidget *dummy = DummyNonNullFormWidgetPtr();
  PopplerFormField *field = _poppler_form_field_new(doc, dummy);

  ASSERT_NE(field, nullptr);
  EXPECT_TRUE(POPPLER_IS_FORM_FIELD(field));

  g_object_unref(field);
  g_object_unref(doc);
}

TEST_F(PopplerFormFieldNewTest_2307, HoldsReferenceToDocumentUntilFieldUnref_2307) {
  PopplerDocument *doc = NewDocFromMinimalPdfOrFail();
  ASSERT_NE(doc, nullptr);

  bool doc_finalized = false;
  g_object_weak_ref(G_OBJECT(doc), &WeakNotifySetBool, &doc_finalized);

  FormWidget *dummy = DummyNonNullFormWidgetPtr();
  PopplerFormField *field = _poppler_form_field_new(doc, dummy);
  ASSERT_NE(field, nullptr);

  // Drop our original ref to doc: if _poppler_form_field_new() refs the document,
  // doc should not be finalized yet.
  g_object_unref(doc);
  EXPECT_FALSE(doc_finalized);

  // When the PopplerFormField is released, it should release its reference too,
  // allowing doc to finalize (observable via weak notify).
  g_object_unref(field);
  EXPECT_TRUE(doc_finalized);
}

TEST_F(PopplerFormFieldNewTest_2307, MultipleFieldsKeepDocumentAliveUntilLastUnref_2307) {
  PopplerDocument *doc = NewDocFromMinimalPdfOrFail();
  ASSERT_NE(doc, nullptr);

  bool doc_finalized = false;
  g_object_weak_ref(G_OBJECT(doc), &WeakNotifySetBool, &doc_finalized);

  FormWidget *dummy = DummyNonNullFormWidgetPtr();
  PopplerFormField *field1 = _poppler_form_field_new(doc, dummy);
  PopplerFormField *field2 = _poppler_form_field_new(doc, dummy);
  ASSERT_NE(field1, nullptr);
  ASSERT_NE(field2, nullptr);

  // Release our direct reference to the document; it should stay alive due to field1+field2.
  g_object_unref(doc);
  EXPECT_FALSE(doc_finalized);

  // Release one field: document should still be alive.
  g_object_unref(field1);
  EXPECT_FALSE(doc_finalized);

  // Release the last field: document can now be finalized.
  g_object_unref(field2);
  EXPECT_TRUE(doc_finalized);
}

} // namespace