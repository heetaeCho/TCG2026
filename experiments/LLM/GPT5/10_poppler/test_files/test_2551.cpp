// poppler_structure_element_get_placement_test_2551.cc
//
// Unit tests for:
//   PopplerStructurePlacement poppler_structure_element_get_placement(PopplerStructureElement*)
//
// Constraints: treat implementation as black box; verify observable behavior only.

#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <utility>
#include <vector>

namespace {

struct ScopedDefaultLogHandler {
  static void Handler(const gchar* log_domain,
                      GLogLevelFlags log_level,
                      const gchar* message,
                      gpointer user_data) {
    auto* self = static_cast<ScopedDefaultLogHandler*>(user_data);
    if (log_level & G_LOG_LEVEL_CRITICAL) {
      self->saw_critical_ = true;
      if (log_domain) self->last_domain_ = log_domain;
      if (message) self->last_message_ = message;
    }
    // Swallow to keep test output clean.
  }

  ScopedDefaultLogHandler()
      : old_(g_log_set_default_handler(&ScopedDefaultLogHandler::Handler, this)) {}

  ~ScopedDefaultLogHandler() { g_log_set_default_handler(old_, nullptr); }

  bool saw_critical() const { return saw_critical_; }
  const std::string& last_domain() const { return last_domain_; }
  const std::string& last_message() const { return last_message_; }

 private:
  GLogFunc old_ = nullptr;
  bool saw_critical_ = false;
  std::string last_domain_;
  std::string last_message_;
};

// Very small PDF builder (enough for Poppler to parse a tagged PDF with structure tree).
// Not related to Poppler internals; this is just test data generation.
class MinimalPdf {
 public:
  explicit MinimalPdf(std::string struct_elem_attr_dict) {
    // Objects we will emit (1..8). We'll build them as complete "N 0 obj ... endobj\n" strings.
    // 1: Catalog with StructTreeRoot
    objs_.push_back(
        "1 0 obj\n"
        "<< /Type /Catalog\n"
        "   /Pages 2 0 R\n"
        "   /StructTreeRoot 5 0 R\n"
        "   /MarkInfo << /Marked true >>\n"
        ">>\n"
        "endobj\n");

    // 2: Pages
    objs_.push_back(
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n");

    // 3: Page (StructParents used by ParentTree; kept minimal)
    objs_.push_back(
        "3 0 obj\n"
        "<< /Type /Page\n"
        "   /Parent 2 0 R\n"
        "   /MediaBox [0 0 200 200]\n"
        "   /Contents 4 0 R\n"
        "   /Resources << /ProcSet [/PDF /Text] /Font << /F1 6 0 R >> >>\n"
        "   /StructParents 0\n"
        ">>\n"
        "endobj\n");

    // 4: Content stream with marked-content sequence (MCID 0)
    const std::string stream =
        "BT\n"
        "/F1 12 Tf\n"
        "10 10 Td\n"
        "/P <</MCID 0>> BDC\n"
        "(Hello) Tj\n"
        "EMC\n"
        "ET\n";
    objs_.push_back(MakeStreamObj(4, stream));

    // 5: StructTreeRoot
    objs_.push_back(
        "5 0 obj\n"
        "<< /Type /StructTreeRoot\n"
        "   /K [7 0 R]\n"
        "   /ParentTree 8 0 R\n"
        ">>\n"
        "endobj\n");

    // 6: Font
    objs_.push_back(
        "6 0 obj\n"
        "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\n"
        "endobj\n");

    // 7: StructElem with (optional) attribute dictionary containing Placement.
    //    Parent is StructTreeRoot; /K is MCID 0; /Pg points to page.
    //    If struct_elem_attr_dict is empty, we omit /A entirely.
    std::string obj7 =
        "7 0 obj\n"
        "<< /Type /StructElem\n"
        "   /S /P\n"
        "   /P 5 0 R\n"
        "   /Pg 3 0 R\n"
        "   /K 0\n";
    if (!struct_elem_attr_dict.empty()) {
      obj7 += "   /A " + struct_elem_attr_dict + "\n";
    }
    obj7 += ">>\nendobj\n";
    objs_.push_back(std::move(obj7));

    // 8: ParentTree mapping StructParents 0 -> struct element (array with 7 0 R)
    objs_.push_back(
        "8 0 obj\n"
        "<< /Nums [0 [7 0 R]] >>\n"
        "endobj\n");
  }

  std::string Build() const {
    // PDF header
    std::string out = "%PDF-1.7\n%\xE2\xE3\xCF\xD3\n";

    // Record offsets for xref: index is object number; 0 is special.
    std::vector<size_t> offsets(9, 0);

    for (size_t i = 0; i < objs_.size(); ++i) {
      const int obj_num = static_cast<int>(i) + 1;
      offsets[obj_num] = out.size();
      out += objs_[i];
    }

    const size_t xref_off = out.size();
    out += "xref\n";
    out += "0 9\n";
    out += "0000000000 65535 f \n";
    for (int i = 1; i <= 8; ++i) {
      out += Pad10(offsets[i]) + " 00000 n \n";
    }

    out += "trailer\n";
    out += "<< /Size 9 /Root 1 0 R >>\n";
    out += "startxref\n";
    out += std::to_string(xref_off) + "\n";
    out += "%%EOF\n";
    return out;
  }

 private:
  static std::string Pad10(size_t v) {
    std::string s = std::to_string(v);
    if (s.size() < 10) s.insert(s.begin(), 10 - s.size(), '0');
    return s;
  }

  static std::string MakeStreamObj(int obj_num, const std::string& stream) {
    std::string s;
    s += std::to_string(obj_num) + " 0 obj\n";
    s += "<< /Length " + std::to_string(stream.size()) + " >>\n";
    s += "stream\n";
    s += stream;
    s += "endstream\n";
    s += "endobj\n";
    return s;
  }

  std::vector<std::string> objs_;
};

static std::string WriteTempFileOrDie(const std::string& bytes) {
  gchar* name = nullptr;
  GError* err = nullptr;

  // Create a temp file.
  const int fd = g_file_open_tmp("poppler-structure-XXXXXX.pdf", &name, &err);
  if (fd < 0) {
    std::string msg = "g_file_open_tmp failed";
    if (err) {
      msg += ": ";
      msg += err->message ? err->message : "(no message)";
      g_error_free(err);
    }
    ADD_FAILURE() << msg;
    return "";
  }

  FILE* f = fdopen(fd, "wb");
  if (!f) {
    close(fd);
    g_free(name);
    ADD_FAILURE() << "fdopen failed";
    return "";
  }

  const size_t written = fwrite(bytes.data(), 1, bytes.size(), f);
  fclose(f);

  if (written != bytes.size()) {
    g_remove(name);
    std::string path = name;
    g_free(name);
    ADD_FAILURE() << "Failed to write full PDF to temp file";
    return "";
  }

  std::string path = name;
  g_free(name);
  return path;
}

static std::string FilePathToUri(const std::string& path) {
  // Poppler GLib uses URIs like file:///...
  gchar* uri = g_filename_to_uri(path.c_str(), nullptr, nullptr);
  std::string out = uri ? uri : "";
  g_free(uri);
  return out;
}

static PopplerStructureElement* GetFirstTopLevelStructElem(PopplerDocument* doc) {
  PopplerStructureElementIter* root = poppler_structure_element_iter_new(doc);
  if (!root) return nullptr;

  // Children iterator (top-level elements).
  PopplerStructureElementIter* child = poppler_structure_element_iter_get_child(root);
  poppler_structure_element_iter_free(root);
  if (!child) return nullptr;

  PopplerStructureElement* elem = poppler_structure_element_iter_get_element(child);
  poppler_structure_element_iter_free(child);
  return elem;  // transfer full per docs; caller owns ref
}

class PopplerStructureElementGetPlacementTest_2551 : public ::testing::Test {
 protected:
  void TearDown() override {
    for (const auto& p : temp_paths_) {
      if (!p.empty()) g_remove(p.c_str());
    }
    temp_paths_.clear();
  }

  std::string MakeTaggedPdfPathWithPlacementAttr(const char* placement_name_or_null) {
    std::string attr;
    if (placement_name_or_null) {
      // Attribute dictionary containing /Placement <Name>
      attr = std::string("<< /Placement /") + placement_name_or_null + " >>";
    } else {
      attr = "";  // omit /A completely
    }
    MinimalPdf pdf(attr);
    std::string path = WriteTempFileOrDie(pdf.Build());
    temp_paths_.push_back(path);
    return path;
  }

 private:
    std::vector<std::string> temp_paths_;
};

TEST_F(PopplerStructureElementGetPlacementTest_2551, NullElementReturnsDefaultAndLogsCritical_2551) {
  ScopedDefaultLogHandler log;

  const PopplerStructurePlacement v = poppler_structure_element_get_placement(nullptr);

  EXPECT_TRUE(log.saw_critical());
  EXPECT_EQ(v, POPPLER_STRUCTURE_PLACEMENT_BLOCK);
}

TEST_F(PopplerStructureElementGetPlacementTest_2551, WrongGObjectTypeReturnsDefaultAndLogsCritical_2551) {
  ScopedDefaultLogHandler log;

  GObject* not_a_structure_element = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(not_a_structure_element, nullptr);

  const PopplerStructurePlacement v =
      poppler_structure_element_get_placement(reinterpret_cast<PopplerStructureElement*>(not_a_structure_element));

  EXPECT_TRUE(log.saw_critical());
  EXPECT_EQ(v, POPPLER_STRUCTURE_PLACEMENT_BLOCK);

  g_object_unref(not_a_structure_element);
}

TEST_F(PopplerStructureElementGetPlacementTest_2551, TaggedPdfWithInlinePlacementReturnsInline_2551) {
  const std::string path = MakeTaggedPdfPathWithPlacementAttr("Inline");
  ASSERT_FALSE(path.empty());

  const std::string uri = FilePathToUri(path);
  ASSERT_FALSE(uri.empty());

  GError* error = nullptr;
  PopplerDocument* doc = poppler_document_new_from_file(uri.c_str(), nullptr, &error);
  ASSERT_NE(doc, nullptr) << (error && error->message ? error->message : "poppler_document_new_from_file failed");
  if (error) g_error_free(error);

  PopplerStructureElement* elem = GetFirstTopLevelStructElem(doc);
  ASSERT_NE(elem, nullptr);

  const PopplerStructurePlacement placement = poppler_structure_element_get_placement(elem);
  EXPECT_EQ(placement, POPPLER_STRUCTURE_PLACEMENT_INLINE);

  g_object_unref(elem);
  g_object_unref(doc);
}

TEST_F(PopplerStructureElementGetPlacementTest_2551, TaggedPdfWithoutPlacementAttributeReturnsDefault_2551) {
  const std::string path = MakeTaggedPdfPathWithPlacementAttr(nullptr);
  ASSERT_FALSE(path.empty());

  const std::string uri = FilePathToUri(path);
  ASSERT_FALSE(uri.empty());

  GError* error = nullptr;
  PopplerDocument* doc = poppler_document_new_from_file(uri.c_str(), nullptr, &error);
  ASSERT_NE(doc, nullptr) << (error && error->message ? error->message : "poppler_document_new_from_file failed");
  if (error) g_error_free(error);

  PopplerStructureElement* elem = GetFirstTopLevelStructElem(doc);
  ASSERT_NE(elem, nullptr);

  // Boundary/default behavior: if the attribute isn't present, expect the default enum value.
  const PopplerStructurePlacement placement = poppler_structure_element_get_placement(elem);
  EXPECT_EQ(placement, POPPLER_STRUCTURE_PLACEMENT_BLOCK);

  g_object_unref(elem);
  g_object_unref(doc);
}

}  // namespace