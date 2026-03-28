// File: poppler-annot-stamp-get-icon-test.cc
#include <gtest/gtest.h>

#include <poppler.h>

#include <glib.h>
#include <gio/gio.h>

#include <cerrno>
#include <cstdint>
#include <cstring>
#include <string>
#include <utility>
#include <vector>

namespace {

struct StampSpec {
  // If empty and emit_name == false => omit /Name entry entirely (expected NONE).
  bool emit_name = true;
  std::string name;      // used as PDF Name object: /Name /<name>
  std::string contents;  // used to find the annotation via poppler_annot_get_contents()
};

static std::string BuildPdfWithStampAnnots(const std::vector<StampSpec>& stamps) {
  // Minimal 1-page PDF with N Stamp annotations.
  // Object numbers:
  // 1: Catalog
  // 2: Pages
  // 3: Page
  // 4..: Annotations
  std::vector<std::pair<int, std::string>> objs;

  // 1 Catalog
  objs.emplace_back(1, "<< /Type /Catalog /Pages 2 0 R >>");

  // 2 Pages
  objs.emplace_back(2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>");

  // Page Annots array
  std::string annots_array = "[";
  for (size_t i = 0; i < stamps.size(); ++i) {
    int obj_no = 4 + static_cast<int>(i);
    annots_array += " " + std::to_string(obj_no) + " 0 R";
  }
  annots_array += " ]";

  // 3 Page
  // Keep it simple: no /Contents stream; Poppler can still load a page with just /MediaBox and /Annots.
  objs.emplace_back(
      3,
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Annots " + annots_array + " >>");

  // 4..N Annotations
  for (size_t i = 0; i < stamps.size(); ++i) {
    const auto& s = stamps[i];

    // Unique rect for each annot to avoid any accidental dedup.
    int x0 = 10 + static_cast<int>(i) * 5;
    int y0 = 10 + static_cast<int>(i) * 5;
    int x1 = 60 + static_cast<int>(i) * 5;
    int y1 = 60 + static_cast<int>(i) * 5;

    std::string dict = "<< /Type /Annot /Subtype /Stamp ";
    dict += "/Rect [" + std::to_string(x0) + " " + std::to_string(y0) + " " + std::to_string(x1) +
            " " + std::to_string(y1) + "] ";

    // /Contents is a string; keep it ASCII and parenthesis-safe for this test.
    dict += "/Contents (" + s.contents + ") ";

    // /Name is a PDF Name object; omit when requested.
    if (s.emit_name) {
      dict += "/Name /" + s.name + " ";
    }

    dict += ">>";
    objs.emplace_back(4 + static_cast<int>(i), dict);
  }

  // Serialize with correct xref offsets.
  std::string pdf;
  pdf += "%PDF-1.4\n";
  std::vector<uint64_t> offsets;
  offsets.resize(static_cast<size_t>(4 + stamps.size()), 0);

  for (const auto& [obj_no, body] : objs) {
    offsets[static_cast<size_t>(obj_no)] = static_cast<uint64_t>(pdf.size());
    pdf += std::to_string(obj_no) + " 0 obj\n";
    pdf += body + "\n";
    pdf += "endobj\n";
  }

  const uint64_t xref_off = static_cast<uint64_t>(pdf.size());
  const int size = 1 + static_cast<int>(offsets.size()) - 1;  // max obj no + 1

  pdf += "xref\n";
  pdf += "0 " + std::to_string(size) + "\n";
  pdf += "0000000000 65535 f \n";
  for (int i = 1; i < size; ++i) {
    char buf[32];
    // Each entry: 10-digit byte offset, 5-digit generation, 'n'
    std::snprintf(buf, sizeof(buf), "%010llu 00000 n \n",
                  static_cast<unsigned long long>(offsets[static_cast<size_t>(i)]));
    pdf += buf;
  }

  pdf += "trailer\n";
  pdf += "<< /Size " + std::to_string(size) + " /Root 1 0 R >>\n";
  pdf += "startxref\n";
  pdf += std::to_string(xref_off) + "\n";
  pdf += "%%EOF\n";
  return pdf;
}

static std::string WriteTempFileOrDie(const std::string& data) {
  gchar* filename = nullptr;
  GError* err = nullptr;

  // Template must end with "XXXXXX"
  int fd = g_file_open_tmp("poppler-stamp-icon-XXXXXX.pdf", &filename, &err);
  if (fd < 0) {
    std::string msg = "g_file_open_tmp failed: ";
    msg += (err && err->message) ? err->message : "unknown error";
    if (err) g_error_free(err);
    FAIL() << msg;
  }

  ssize_t wrote = 0;
  const char* p = data.data();
  size_t left = data.size();
  while (left > 0) {
    ssize_t n = ::write(fd, p + wrote, left);
    if (n < 0) {
      int e = errno;
      ::close(fd);
      std::string msg = "write failed: ";
      msg += std::strerror(e);
      g_free(filename);
      FAIL() << msg;
    }
    wrote += n;
    left -= static_cast<size_t>(n);
  }
  ::close(fd);

  std::string out = filename;
  g_free(filename);
  return out;
}

static PopplerDocument* LoadDocFromPathOrDie(const std::string& path) {
  GError* err = nullptr;
  gchar* uri = g_filename_to_uri(path.c_str(), nullptr, &err);
  if (!uri) {
    std::string msg = "g_filename_to_uri failed: ";
    msg += (err && err->message) ? err->message : "unknown error";
    if (err) g_error_free(err);
    FAIL() << msg;
  }

  PopplerDocument* doc = poppler_document_new_from_file(uri, /*password=*/nullptr, &err);
  g_free(uri);

  if (!doc) {
    std::string msg = "poppler_document_new_from_file failed: ";
    msg += (err && err->message) ? err->message : "unknown error";
    if (err) g_error_free(err);
    FAIL() << msg;
  }
  return doc;
}

static PopplerAnnotStamp* FindStampByContentsOrNull(PopplerPage* page, const char* want_contents) {
  GList* mapping = poppler_page_get_annot_mapping(page);
  for (GList* it = mapping; it != nullptr; it = it->next) {
    auto* m = static_cast<PopplerAnnotMapping*>(it->data);
    if (!m || !m->annot) continue;
    if (!POPPLER_IS_ANNOT_STAMP(m->annot)) continue;

    gchar* contents = poppler_annot_get_contents(m->annot);
    bool match = (contents != nullptr) && (std::string(contents) == want_contents);
    g_free(contents);

    if (match) {
      // Returned pointer is owned by mapping/page; caller must not unref it here.
      poppler_page_free_annot_mapping(mapping);
      return POPPLER_ANNOT_STAMP(m->annot);
    }
  }
  poppler_page_free_annot_mapping(mapping);
  return nullptr;
}

struct LogCapture {
  static void Handler(const gchar* /*log_domain*/, GLogLevelFlags /*log_level*/,
                      const gchar* /*message*/, gpointer user_data) {
    auto* self = static_cast<LogCapture*>(user_data);
    self->count++;
  }
  int count = 0;
  guint handler_id = 0;
  void Install() {
    count = 0;
    handler_id = g_log_set_handler(
        /*log_domain=*/G_LOG_DOMAIN,
        static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL | G_LOG_FLAG_FATAL | G_LOG_FLAG_RECURSION),
        &LogCapture::Handler, this);
  }
  void Uninstall() {
    if (handler_id != 0) {
      g_log_remove_handler(G_LOG_DOMAIN, handler_id);
      handler_id = 0;
    }
  }
};

}  // namespace

TEST(PopplerAnnotStampGetIconTest_2119, NullInputReturnsUnknownAndEmitsCritical_2119) {
  LogCapture cap;
  cap.Install();

  PopplerAnnotStampIcon icon = poppler_annot_stamp_get_icon(nullptr);

  cap.Uninstall();

  EXPECT_EQ(icon, POPPLER_ANNOT_STAMP_ICON_UNKNOWN);
  // g_return_val_if_fail should have emitted a critical log.
  EXPECT_GE(cap.count, 1);
}

TEST(PopplerAnnotStampGetIconTest_2119, MissingNameReturnsNone_2119) {
  std::vector<StampSpec> stamps = {
      // Omit /Name entirely -> AnnotStamp::getIcon() should be empty -> NONE.
      StampSpec{/*emit_name=*/false, /*name=*/"", /*contents=*/"NO_NAME"},
  };

  const std::string pdf = BuildPdfWithStampAnnots(stamps);
  const std::string path = WriteTempFileOrDie(pdf);

  GObject* doc_obj = G_OBJECT(LoadDocFromPathOrDie(path));
  PopplerPage* page = poppler_document_get_page(POPPLER_DOCUMENT(doc_obj), 0);
  ASSERT_NE(page, nullptr);

  PopplerAnnotStamp* stamp = FindStampByContentsOrNull(page, "NO_NAME");
  ASSERT_NE(stamp, nullptr);

  EXPECT_EQ(poppler_annot_stamp_get_icon(stamp), POPPLER_ANNOT_STAMP_ICON_NONE);

  g_object_unref(page);
  g_object_unref(doc_obj);
  g_remove(path.c_str());
}

TEST(PopplerAnnotStampGetIconTest_2119, UnknownNameReturnsUnknown_2119) {
  std::vector<StampSpec> stamps = {
      StampSpec{/*emit_name=*/true, /*name=*/"TotallyMadeUp", /*contents=*/"UNKNOWN_NAME"},
  };

  const std::string pdf = BuildPdfWithStampAnnots(stamps);
  const std::string path = WriteTempFileOrDie(pdf);

  GObject* doc_obj = G_OBJECT(LoadDocFromPathOrDie(path));
  PopplerPage* page = poppler_document_get_page(POPPLER_DOCUMENT(doc_obj), 0);
  ASSERT_NE(page, nullptr);

  PopplerAnnotStamp* stamp = FindStampByContentsOrNull(page, "UNKNOWN_NAME");
  ASSERT_NE(stamp, nullptr);

  EXPECT_EQ(poppler_annot_stamp_get_icon(stamp), POPPLER_ANNOT_STAMP_ICON_UNKNOWN);

  g_object_unref(page);
  g_object_unref(doc_obj);
  g_remove(path.c_str());
}

TEST(PopplerAnnotStampGetIconTest_2119, KnownIconNamesAreMappedCorrectly_2119) {
  // Put many annots on one page to cover normal operation + boundary of "multiple mappings".
  std::vector<std::pair<std::string, PopplerAnnotStampIcon>> cases = {
      {"Approved", POPPLER_ANNOT_STAMP_ICON_APPROVED},
      {"AsIs", POPPLER_ANNOT_STAMP_ICON_AS_IS},
      {"Confidential", POPPLER_ANNOT_STAMP_ICON_CONFIDENTIAL},
      {"Final", POPPLER_ANNOT_STAMP_ICON_FINAL},
      {"Experimental", POPPLER_ANNOT_STAMP_ICON_EXPERIMENTAL},
      {"Expired", POPPLER_ANNOT_STAMP_ICON_EXPIRED},
      {"NotApproved", POPPLER_ANNOT_STAMP_ICON_NOT_APPROVED},
      {"NotForPublicRelease", POPPLER_ANNOT_STAMP_ICON_NOT_FOR_PUBLIC_RELEASE},
      {"Sold", POPPLER_ANNOT_STAMP_ICON_SOLD},
      {"Departmental", POPPLER_ANNOT_STAMP_ICON_DEPARTMENTAL},
      {"ForComment", POPPLER_ANNOT_STAMP_ICON_FOR_COMMENT},
      {"ForPublicRelease", POPPLER_ANNOT_STAMP_ICON_FOR_PUBLIC_RELEASE},
      {"TopSecret", POPPLER_ANNOT_STAMP_ICON_TOP_SECRET},
  };

  std::vector<StampSpec> stamps;
  stamps.reserve(cases.size());
  for (const auto& [name, /*expected*/ _] : cases) {
    stamps.push_back(StampSpec{/*emit_name=*/true, /*name=*/name, /*contents=*/name});
  }

  const std::string pdf = BuildPdfWithStampAnnots(stamps);
  const std::string path = WriteTempFileOrDie(pdf);

  GObject* doc_obj = G_OBJECT(LoadDocFromPathOrDie(path));
  PopplerPage* page = poppler_document_get_page(POPPLER_DOCUMENT(doc_obj), 0);
  ASSERT_NE(page, nullptr);

  for (const auto& [name, expected] : cases) {
    PopplerAnnotStamp* stamp = FindStampByContentsOrNull(page, name.c_str());
    ASSERT_NE(stamp, nullptr) << "Failed to find stamp annot with Contents=" << name;
    EXPECT_EQ(poppler_annot_stamp_get_icon(stamp), expected) << "Name=" << name;
  }

  g_object_unref(page);
  g_object_unref(doc_obj);
  g_remove(path.c_str());
}