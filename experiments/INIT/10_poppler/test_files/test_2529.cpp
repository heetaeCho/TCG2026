// Test file for poppler_structure_element_get_title
// TEST_ID: 2529

#include <gtest/gtest.h>

#include <glib.h>
#include <poppler/glib/poppler.h>

#include <iomanip>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace {

static std::string MakeXrefEntry(std::size_t offset, bool in_use) {
  std::ostringstream oss;
  oss << std::setw(10) << std::setfill('0') << offset << " "
      << std::setw(5) << std::setfill('0') << 0 << " " << (in_use ? "n" : "f")
      << " \n";
  return oss.str();
}

static std::string BuildMinimalTaggedPdfWithStructTitle(const std::string& title_entry_or_empty) {
  // title_entry_or_empty example: "/T (Hello)\n" or "/T <FEFF00480065006C006C006F>\n" or "".
  //
  // We construct a minimal PDF with:
  // - Catalog referencing /StructTreeRoot
  // - StructTreeRoot referencing a single StructElem
  // - StructElem optionally carrying /T (Title)
  //
  // This is test data generation and not related to the implementation under test.
  const std::string header = "%PDF-1.7\n%\xE2\xE3\xCF\xD3\n";

  std::vector<std::string> objs;
  objs.reserve(6);

  // 1 0 obj: Catalog
  objs.push_back(
      "1 0 obj\n"
      "<< /Type /Catalog\n"
      "   /Pages 2 0 R\n"
      "   /StructTreeRoot 5 0 R\n"
      ">>\n"
      "endobj\n");

  // 2 0 obj: Pages
  objs.push_back(
      "2 0 obj\n"
      "<< /Type /Pages\n"
      "   /Kids [3 0 R]\n"
      "   /Count 1\n"
      ">>\n"
      "endobj\n");

  // 3 0 obj: Page
  objs.push_back(
      "3 0 obj\n"
      "<< /Type /Page\n"
      "   /Parent 2 0 R\n"
      "   /MediaBox [0 0 200 200]\n"
      "   /Resources << >>\n"
      "   /Contents 4 0 R\n"
      ">>\n"
      "endobj\n");

  // 4 0 obj: Contents stream
  const std::string contents = "BT /F1 12 Tf 72 720 Td (Hi) Tj ET\n";
  {
    std::ostringstream oss;
    oss << "4 0 obj\n"
        << "<< /Length " << contents.size() << " >>\n"
        << "stream\n"
        << contents
        << "endstream\n"
        << "endobj\n";
    objs.push_back(oss.str());
  }

  // 5 0 obj: StructTreeRoot
  objs.push_back(
      "5 0 obj\n"
      "<< /Type /StructTreeRoot\n"
      "   /K 6 0 R\n"
      ">>\n"
      "endobj\n");

  // 6 0 obj: StructElem (with optional title)
  {
    std::ostringstream oss;
    oss << "6 0 obj\n"
        << "<< /Type /StructElem\n"
        << "   /S /Document\n"
        << "   /P 5 0 R\n";
    if (!title_entry_or_empty.empty()) {
      oss << "   " << title_entry_or_empty;
      if (title_entry_or_empty.back() != '\n') {
        oss << "\n";
      }
    }
    oss << "   /K []\n"
        << ">>\n"
        << "endobj\n";
    objs.push_back(oss.str());
  }

  // Assemble file and compute xref offsets.
  std::string body;
  body.reserve(4096);
  body += header;

  std::vector<std::size_t> offsets;
  offsets.resize(objs.size() + 1);
  offsets[0] = 0; // object 0 is the free entry

  for (std::size_t i = 0; i < objs.size(); ++i) {
    offsets[i + 1] = body.size();
    body += objs[i];
  }

  const std::size_t xref_offset = body.size();

  std::ostringstream xref;
  xref << "xref\n"
       << "0 " << (objs.size() + 1) << "\n"
       << "0000000000 65535 f \n";
  for (std::size_t i = 1; i < offsets.size(); ++i) {
    xref << MakeXrefEntry(offsets[i], /*in_use=*/true);
  }

  std::ostringstream trailer;
  trailer << "trailer\n"
          << "<< /Size " << (objs.size() + 1) << "\n"
          << "   /Root 1 0 R\n"
          << ">>\n"
          << "startxref\n"
          << xref_offset << "\n"
          << "%%EOF\n";

  body += xref.str();
  body += trailer.str();
  return body;
}

static std::string WriteTempPdf(const std::string& pdf_bytes) {
  gchar* path = nullptr;
  GError* error = nullptr;
  const int fd = g_file_open_tmp("poppler-structure-title-XXXXXX.pdf", &path, &error);
  if (fd < 0) {
    std::string msg = "g_file_open_tmp failed";
    if (error) {
      msg += ": ";
      msg += error->message;
      g_error_free(error);
    }
    ADD_FAILURE() << msg;
    return std::string();
  }

  // Close FD; we'll use g_file_set_contents for simplicity.
  close(fd);

  if (!g_file_set_contents(path, pdf_bytes.data(), static_cast<gssize>(pdf_bytes.size()), &error)) {
    std::string msg = "g_file_set_contents failed";
    if (error) {
      msg += ": ";
      msg += error->message;
      g_error_free(error);
    }
    ADD_FAILURE() << msg;
    g_free(path);
    return std::string();
  }

  std::string out(path);
  g_free(path);
  return out;
}

static PopplerDocument* LoadDocFromPath(const std::string& path) {
  GError* error = nullptr;
  gchar* uri = g_filename_to_uri(path.c_str(), nullptr, &error);
  if (!uri) {
    std::string msg = "g_filename_to_uri failed";
    if (error) {
      msg += ": ";
      msg += error->message;
      g_error_free(error);
    }
    ADD_FAILURE() << msg;
    return nullptr;
  }

  PopplerDocument* doc = poppler_document_new_from_file(uri, /*password=*/nullptr, &error);
  g_free(uri);

  if (!doc) {
    std::string msg = "poppler_document_new_from_file failed";
    if (error) {
      msg += ": ";
      msg += error->message;
      g_error_free(error);
    }
    ADD_FAILURE() << msg;
    return nullptr;
  }

  return doc;
}

static PopplerStructureElement* GetFirstStructureElement(PopplerDocument* doc) {
  if (!doc) {
    return nullptr;
  }

  PopplerStructureElementIter* iter = poppler_structure_element_iter_new(doc);
  if (!iter) {
    return nullptr;
  }

  PopplerStructureElement* elem = poppler_structure_element_iter_get_element(iter);
  // get_element returns a ref'ed GObject (in poppler-glib APIs this is typical);
  // to be safe, we ref it if non-null and free iterator afterwards.
  if (elem) {
    g_object_ref(elem);
  }
  poppler_structure_element_iter_free(iter);
  return elem;
}

} // namespace

TEST(PopplerStructureElementGetTitleTest_2529, ReturnsNullForNullElement_2529) {
  // Error case: invalid argument should return NULL (as per g_return_val_if_fail).
  gchar* title = poppler_structure_element_get_title(nullptr);
  EXPECT_EQ(title, nullptr);
}

TEST(PopplerStructureElementGetTitleTest_2529, ReturnsNullForFreshlyConstructedElementWithoutBackingStruct_2529) {
  // Boundary/error case: a newly constructed instance should not have a backing StructElement,
  // thus title retrieval should return NULL (observed through the interface).
  PopplerStructureElement* elem =
      POPPLER_STRUCTURE_ELEMENT(g_object_new(POPPLER_TYPE_STRUCTURE_ELEMENT, nullptr));
  ASSERT_NE(elem, nullptr);

  gchar* title = poppler_structure_element_get_title(elem);
  EXPECT_EQ(title, nullptr);

  g_object_unref(elem);
}

TEST(PopplerStructureElementGetTitleTest_2529, ReturnsTitleForTaggedPdfStructureElement_2529) {
  const std::string pdf = BuildMinimalTaggedPdfWithStructTitle("/T (Hello)\n");
  const std::string path = WriteTempPdf(pdf);
  ASSERT_FALSE(path.empty());

  PopplerDocument* doc = LoadDocFromPath(path);
  ASSERT_NE(doc, nullptr);

  PopplerStructureElement* elem = GetFirstStructureElement(doc);
  ASSERT_NE(elem, nullptr);

  gchar* title = poppler_structure_element_get_title(elem);
  ASSERT_NE(title, nullptr);
  EXPECT_STREQ(title, "Hello");

  g_free(title);
  g_object_unref(elem);
  g_object_unref(doc);

  g_remove(path.c_str());
}

TEST(PopplerStructureElementGetTitleTest_2529, ReturnsNullWhenTitleMissing_2529) {
  const std::string pdf = BuildMinimalTaggedPdfWithStructTitle(/*title_entry_or_empty=*/"");
  const std::string path = WriteTempPdf(pdf);
  ASSERT_FALSE(path.empty());

  PopplerDocument* doc = LoadDocFromPath(path);
  ASSERT_NE(doc, nullptr);

  PopplerStructureElement* elem = GetFirstStructureElement(doc);
  ASSERT_NE(elem, nullptr);

  gchar* title = poppler_structure_element_get_title(elem);
  EXPECT_EQ(title, nullptr);

  g_object_unref(elem);
  g_object_unref(doc);

  g_remove(path.c_str());
}

TEST(PopplerStructureElementGetTitleTest_2529, ReturnsEmptyStringWhenTitleIsEmpty_2529) {
  const std::string pdf = BuildMinimalTaggedPdfWithStructTitle("/T ()\n");
  const std::string path = WriteTempPdf(pdf);
  ASSERT_FALSE(path.empty());

  PopplerDocument* doc = LoadDocFromPath(path);
  ASSERT_NE(doc, nullptr);

  PopplerStructureElement* elem = GetFirstStructureElement(doc);
  ASSERT_NE(elem, nullptr);

  gchar* title = poppler_structure_element_get_title(elem);
  ASSERT_NE(title, nullptr);
  EXPECT_STREQ(title, "");

  g_free(title);
  g_object_unref(elem);
  g_object_unref(doc);

  g_remove(path.c_str());
}

TEST(PopplerStructureElementGetTitleTest_2529, ConvertsUtf16HexTitleToUtf8_2529) {
  // "Grüße" in UTF-16BE with BOM:
  // FE FF 00 47 00 72 00 FC 00 DF 00 65
  const std::string pdf = BuildMinimalTaggedPdfWithStructTitle("/T <FEFF0047007200FC00DF0065>\n");
  const std::string path = WriteTempPdf(pdf);
  ASSERT_FALSE(path.empty());

  PopplerDocument* doc = LoadDocFromPath(path);
  ASSERT_NE(doc, nullptr);

  PopplerStructureElement* elem = GetFirstStructureElement(doc);
  ASSERT_NE(elem, nullptr);

  gchar* title = poppler_structure_element_get_title(elem);
  ASSERT_NE(title, nullptr);
  EXPECT_STREQ(title, u8"Grüße");

  g_free(title);
  g_object_unref(elem);
  g_object_unref(doc);

  g_remove(path.c_str());
}