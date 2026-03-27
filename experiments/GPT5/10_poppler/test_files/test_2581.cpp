// poppler-structure-element-get-ruby-align-test_2581.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstddef>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace {

struct GErrorDeleter {
  void operator()(GError *e) const {
    if (e)
      g_error_free(e);
  }
};
using UniqueGError = std::unique_ptr<GError, GErrorDeleter>;

struct GObjectUnrefDeleter {
  void operator()(gpointer p) const {
    if (p)
      g_object_unref(p);
  }
};
template <typename T>
using UniqueGObject = std::unique_ptr<T, GObjectUnrefDeleter>;

struct IterFreeDeleter {
  void operator()(PopplerStructureElementIter *iter) const {
    if (iter)
      poppler_structure_element_iter_free(iter);
  }
};
using UniqueIter = std::unique_ptr<PopplerStructureElementIter, IterFreeDeleter>;

static std::string BuildTaggedPdfWithSingleStructElem(const std::string &struct_type_name,
                                                      const std::optional<std::string> &ruby_align_name) {
  // Build a minimal, valid PDF with a structure tree containing one StructElem.
  // This is only a test fixture generator; it does not depend on Poppler internals.
  struct Obj {
    int num;
    std::string body; // without "n 0 obj" wrapper
  };

  // Object numbers:
  // 1: Catalog
  // 2: StructTreeRoot
  // 3: Pages
  // 4: Page
  // 5: Contents stream
  // 6: StructElem (the element we will query)
  std::vector<Obj> objs;

  objs.push_back(Obj{
      1,
      "<< /Type /Catalog /Pages 3 0 R /StructTreeRoot 2 0 R >>\n",
  });

  objs.push_back(Obj{
      3,
      "<< /Type /Pages /Count 1 /Kids [4 0 R] >>\n",
  });

  // Simple empty content stream (still provide a valid stream object).
  const std::string contents_stream = "q\nQ\n";
  objs.push_back(Obj{
      5,
      "<< /Length " + std::to_string(contents_stream.size()) + " >>\nstream\n" + contents_stream + "endstream\n",
  });

  objs.push_back(Obj{
      4,
      "<< /Type /Page /Parent 3 0 R /MediaBox [0 0 200 200] /Contents 5 0 R /Resources << >> >>\n",
  });

  // StructTreeRoot points to element 6.
  objs.push_back(Obj{
      2,
      "<< /Type /StructTreeRoot /K [6 0 R] >>\n",
  });

  std::string attr_dict;
  if (ruby_align_name.has_value()) {
    // Attribute dictionary for ruby alignment.
    // Example: /A << /RubyAlign /Center >>
    attr_dict = " /A << /RubyAlign /" + *ruby_align_name + " >>";
  }

  // StructElem with required keys: /Type /StructElem, /S (structure type), /P (parent).
  // Keep /K empty to avoid needing marked-content linkage.
  objs.push_back(Obj{
      6,
      "<< /Type /StructElem /S /" + struct_type_name + " /P 2 0 R" + attr_dict + " /K [] >>\n",
  });

  // Assemble PDF with xref offsets.
  std::string out;
  out += "%PDF-1.5\n";
  std::vector<std::size_t> offsets;
  offsets.resize(7, 0); // 0..6

  for (const auto &o : objs) {
    offsets[o.num] = out.size();
    out += std::to_string(o.num) + " 0 obj\n";
    out += o.body;
    out += "endobj\n";
  }

  const std::size_t xref_pos = out.size();
  out += "xref\n";
  out += "0 7\n";
  out += "0000000000 65535 f \n";
  for (int i = 1; i <= 6; ++i) {
    char buf[64];
    // xref entry: 10-digit offset, 5-digit generation, n/f
    std::snprintf(buf, sizeof(buf), "%010zu 00000 n \n", offsets[i]);
    out += buf;
  }

  out += "trailer\n";
  out += "<< /Size 7 /Root 1 0 R >>\n";
  out += "startxref\n";
  out += std::to_string(xref_pos) + "\n";
  out += "%%EOF\n";
  return out;
}

static UniqueGObject<PopplerDocument> LoadDocFromPdfData(const std::string &pdf_data) {
  UniqueGError err(nullptr);

  // poppler_document_new_from_data expects a mutable pointer, but it does not modify it.
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
  PopplerDocument *doc =
      poppler_document_new_from_data(const_cast<char *>(pdf_data.data()),
                                     static_cast<int>(pdf_data.size()),
                                     /*password*/ nullptr,
                                     &err.get());
  if (!doc) {
    // Provide a helpful assertion message if parsing fails in the test environment.
    ADD_FAILURE() << "Failed to load PDF data into PopplerDocument"
                  << (err ? std::string(": ") + err->message : std::string());
  }
  return UniqueGObject<PopplerDocument>(doc);
}

static PopplerStructureElement *FindFirstElementOfKind(PopplerStructureElementIter *iter,
                                                       PopplerStructureElementKind target_kind) {
  if (!iter)
    return nullptr;

  do {
    PopplerStructureElement *elem = poppler_structure_element_iter_get_element(iter);
    if (elem && poppler_structure_element_get_kind(elem) == target_kind) {
      return elem; // borrowed; owned by Poppler
    }

    PopplerStructureElementIter *child_raw = poppler_structure_element_iter_get_child(iter);
    UniqueIter child(child_raw);
    if (child) {
      if (PopplerStructureElement *found = FindFirstElementOfKind(child.get(), target_kind))
        return found;
    }
  } while (poppler_structure_element_iter_next(iter));

  return nullptr;
}

} // namespace

TEST(PopplerStructureElementGetRubyAlignTest_2581, NullElementReturnsDefaultStart_2581) {
  // Error/exceptional path should be observable as a default return value.
  // The implementation uses g_return_val_if_fail(...) with a default enum value.
  PopplerStructureRubyAlign align = poppler_structure_element_get_ruby_align(nullptr);
  EXPECT_EQ(align, POPPLER_STRUCTURE_RUBY_ALIGN_START);
}

TEST(PopplerStructureElementGetRubyAlignTest_2581, NonInlineElementReturnsDefaultStart_2581) {
  // Build a structure tree with a Paragraph element (block-level), then call get_ruby_align().
  // Since the API is specified for inline-level elements, it should return the default value.
  const std::string pdf = BuildTaggedPdfWithSingleStructElem("P", /*ruby_align_name*/ std::nullopt);
  auto doc = LoadDocFromPdfData(pdf);
  ASSERT_NE(doc.get(), nullptr);

  UniqueIter iter(poppler_structure_element_iter_new(doc.get()));
  ASSERT_NE(iter.get(), nullptr) << "Document did not expose a structure tree iterator";

  PopplerStructureElement *para =
      FindFirstElementOfKind(iter.get(), POPPLER_STRUCTURE_ELEMENT_PARAGRAPH);
  ASSERT_NE(para, nullptr) << "Failed to locate a paragraph element in the structure tree fixture";

  PopplerStructureRubyAlign align = poppler_structure_element_get_ruby_align(para);
  EXPECT_EQ(align, POPPLER_STRUCTURE_RUBY_ALIGN_START);
}

TEST(PopplerStructureElementGetRubyAlignTest_2581, RubyElementWithCenterAlignReturnsCenter_2581) {
  // Normal operation: Ruby element with a RubyAlign attribute should map to the corresponding enum.
  const std::string pdf = BuildTaggedPdfWithSingleStructElem("Ruby", std::make_optional<std::string>("Center"));
  auto doc = LoadDocFromPdfData(pdf);
  ASSERT_NE(doc.get(), nullptr);

  UniqueIter iter(poppler_structure_element_iter_new(doc.get()));
  ASSERT_NE(iter.get(), nullptr) << "Document did not expose a structure tree iterator";

  PopplerStructureElement *ruby =
      FindFirstElementOfKind(iter.get(), POPPLER_STRUCTURE_ELEMENT_RUBY);
  ASSERT_NE(ruby, nullptr) << "Failed to locate a Ruby element in the structure tree fixture";

  PopplerStructureRubyAlign align = poppler_structure_element_get_ruby_align(ruby);
  EXPECT_EQ(align, POPPLER_STRUCTURE_RUBY_ALIGN_CENTER);
}

TEST(PopplerStructureElementGetRubyAlignTest_2581, RubyElementWithJustifyAlignReturnsJustify_2581) {
  // Boundary-ish coverage over multiple enum members.
  const std::string pdf = BuildTaggedPdfWithSingleStructElem("Ruby", std::make_optional<std::string>("Justify"));
  auto doc = LoadDocFromPdfData(pdf);
  ASSERT_NE(doc.get(), nullptr);

  UniqueIter iter(poppler_structure_element_iter_new(doc.get()));
  ASSERT_NE(iter.get(), nullptr) << "Document did not expose a structure tree iterator";

  PopplerStructureElement *ruby =
      FindFirstElementOfKind(iter.get(), POPPLER_STRUCTURE_ELEMENT_RUBY);
  ASSERT_NE(ruby, nullptr) << "Failed to locate a Ruby element in the structure tree fixture";

  PopplerStructureRubyAlign align = poppler_structure_element_get_ruby_align(ruby);
  EXPECT_EQ(align, POPPLER_STRUCTURE_RUBY_ALIGN_JUSTIFY);
}

TEST(PopplerStructureElementGetRubyAlignTest_2581, RubyElementWithoutAlignAttributeReturnsDefaultStart_2581) {
  // When the ruby alignment attribute is not present, behavior should be observable via a stable default.
  const std::string pdf = BuildTaggedPdfWithSingleStructElem("Ruby", /*ruby_align_name*/ std::nullopt);
  auto doc = LoadDocFromPdfData(pdf);
  ASSERT_NE(doc.get(), nullptr);

  UniqueIter iter(poppler_structure_element_iter_new(doc.get()));
  ASSERT_NE(iter.get(), nullptr) << "Document did not expose a structure tree iterator";

  PopplerStructureElement *ruby =
      FindFirstElementOfKind(iter.get(), POPPLER_STRUCTURE_ELEMENT_RUBY);
  ASSERT_NE(ruby, nullptr) << "Failed to locate a Ruby element in the structure tree fixture";

  PopplerStructureRubyAlign align = poppler_structure_element_get_ruby_align(ruby);
  EXPECT_EQ(align, POPPLER_STRUCTURE_RUBY_ALIGN_START);
}