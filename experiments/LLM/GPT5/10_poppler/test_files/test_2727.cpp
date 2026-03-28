// printTSVBBox_test_2727.cc
#include <gtest/gtest.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <functional>
#include <optional>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "poppler/PDFDoc.h"
#include "poppler/TextOutputDev.h"
#include "goo/GooString.h"

// -----------------------------------------------------------------------------
// SUT declaration
// -----------------------------------------------------------------------------
// The function under test lives in utils/pdftotext.cc (already compiled in the project).
// We treat it as a black box and only test observable output.
void printTSVBBox(FILE *f, PDFDoc *doc, TextOutputDev *textOut, int first, int last);

// -----------------------------------------------------------------------------
// Global variables referenced by printTSVBBox (declared in utils/pdftoppm.cc).
// In many unit-test builds, those TUs are not linked, so we provide definitions here.
// If your build already links pdftoppm.cc, remove these definitions to avoid duplicates.
// -----------------------------------------------------------------------------
double resolution = 72.0;
bool useCropBox = false;

// -----------------------------------------------------------------------------
// Test helpers
// -----------------------------------------------------------------------------
namespace {

struct TempFile {
  std::string path;

  TempFile() {
    // Create a unique temp file path (mkstemp creates the file).
    char tmpl[] = "/tmp/printTSVBBox_XXXXXX";
    int fd = ::mkstemp(tmpl);
    if (fd < 0) {
      // Fall back to a very simple path if mkstemp fails (rare in CI, but keep tests robust).
      path = "/tmp/printTSVBBox_fallback.pdf";
      return;
    }
    ::close(fd);
    path = tmpl;
  }

  ~TempFile() {
    if (!path.empty()) {
      ::remove(path.c_str());
    }
  }

  TempFile(const TempFile &) = delete;
  TempFile &operator=(const TempFile &) = delete;
  TempFile(TempFile &&) = default;
  TempFile &operator=(TempFile &&) = default;
};

// Builds a minimal PDF with N pages containing one word per page ("Hello", "World", ...).
// Optionally adds a CropBox distinct from MediaBox.
// This is test-only fixture construction; it is not attempting to mirror poppler internals.
static std::string BuildMinimalPdfBytes(int num_pages,
                                       bool add_cropbox,
                                       int media_w = 200,
                                       int media_h = 200,
                                       int crop_w = 100,
                                       int crop_h = 100) {
  if (num_pages <= 0) num_pages = 1;

  // Simple page texts: Page1 "Hello", Page2 "World", Page3 "Poppler", ...
  std::vector<std::string> page_words;
  page_words.reserve(num_pages);
  const std::vector<std::string> pool = {"Hello", "World", "Poppler", "BBox", "TSV"};
  for (int i = 0; i < num_pages; ++i) {
    page_words.push_back(pool[static_cast<size_t>(i) % pool.size()]);
  }

  // We will emit classic PDF objects with a computed xref.
  // Object plan:
  // 1 0 obj: Catalog -> Pages 2 0 R
  // 2 0 obj: Pages -> Kids [page objs], Count N
  // For each page i:
  //   pageObj: /Type /Page /Parent 2 0 R /Resources << /Font << /F1 3 0 R >> >> /MediaBox ... [/CropBox ...] /Contents contentObj
  // For each page i:
  //   contentObj: stream with "BT /F1 24 Tf 50 150 Td (WORD) Tj ET"
  // 3 0 obj: Font (Helvetica)
  // xref + trailer

  struct Obj {
    int num = 0;
    std::string body;
  };
  std::vector<Obj> objs;

  // 1: catalog
  objs.push_back({1, "<< /Type /Catalog /Pages 2 0 R >>"});

  // 2: pages
  {
    std::ostringstream kids;
    kids << "[ ";
    // page object numbers will start at 4
    for (int i = 0; i < num_pages; ++i) {
      kids << (4 + i) << " 0 R ";
    }
    kids << "]";
    std::ostringstream pages;
    pages << "<< /Type /Pages /Kids " << kids.str() << " /Count " << num_pages << " >>";
    objs.push_back({2, pages.str()});
  }

  // 3: font
  objs.push_back({3, "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>"});

  // Page objects (4..)
  // Content objects after pages: start at (4 + num_pages)
  const int first_page_obj = 4;
  const int first_content_obj = first_page_obj + num_pages;

  for (int i = 0; i < num_pages; ++i) {
    const int page_obj_num = first_page_obj + i;
    const int content_obj_num = first_content_obj + i;

    std::ostringstream page;
    page << "<< /Type /Page /Parent 2 0 R "
         << "/Resources << /Font << /F1 3 0 R >> >> "
         << "/MediaBox [0 0 " << media_w << " " << media_h << "] ";
    if (add_cropbox) {
      page << "/CropBox [0 0 " << crop_w << " " << crop_h << "] ";
    }
    page << "/Contents " << content_obj_num << " 0 R >>";

    objs.push_back({page_obj_num, page.str()});
  }

  // Content streams
  for (int i = 0; i < num_pages; ++i) {
    const int content_obj_num = first_content_obj + i;
    const std::string &word = page_words[static_cast<size_t>(i)];

    std::ostringstream stream;
    stream << "BT\n"
           << "/F1 24 Tf\n"
           << "50 150 Td\n"
           << "(" << word << ") Tj\n"
           << "ET\n";
    const std::string s = stream.str();

    std::ostringstream content;
    content << "<< /Length " << s.size() << " >>\n"
            << "stream\n"
            << s
            << "endstream";

    objs.push_back({content_obj_num, content.str()});
  }

  // Now serialize with xref offsets.
  std::ostringstream out;
  out << "%PDF-1.4\n";

  // xref table needs entry for object 0 too.
  // We'll record offsets for obj num up to max.
  int max_obj_num = 0;
  for (const auto &o : objs) {
    if (o.num > max_obj_num) max_obj_num = o.num;
  }
  std::vector<long> offsets(static_cast<size_t>(max_obj_num + 1), 0);

  // Ensure objects are ordered by object number.
  std::vector<Obj> ordered = objs;
  std::sort(ordered.begin(), ordered.end(), [](const Obj &a, const Obj &b) { return a.num < b.num; });

  for (const auto &o : ordered) {
    offsets[static_cast<size_t>(o.num)] = static_cast<long>(out.tellp());
    out << o.num << " 0 obj\n" << o.body << "\nendobj\n";
  }

  const long xref_pos = static_cast<long>(out.tellp());
  out << "xref\n";
  out << "0 " << (max_obj_num + 1) << "\n";
  out << "0000000000 65535 f \n";
  for (int n = 1; n <= max_obj_num; ++n) {
    char buf[64];
    std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[static_cast<size_t>(n)]);
    out << buf;
  }

  out << "trailer\n";
  out << "<< /Size " << (max_obj_num + 1) << " /Root 1 0 R >>\n";
  out << "startxref\n";
  out << xref_pos << "\n";
  out << "%%EOF\n";

  return out.str();
}

static void WriteFileBytes(const std::string &path, const std::string &bytes) {
  FILE *fp = std::fopen(path.c_str(), "wb");
  ASSERT_NE(fp, nullptr);
  const size_t wrote = std::fwrite(bytes.data(), 1, bytes.size(), fp);
  std::fclose(fp);
  ASSERT_EQ(wrote, bytes.size());
}

static std::string ReadAllFromFILE(FILE *fp) {
  std::fflush(fp);
  std::rewind(fp);
  std::string s;
  char buf[4096];
  while (true) {
    const size_t n = std::fread(buf, 1, sizeof(buf), fp);
    if (n > 0) s.append(buf, buf + n);
    if (n < sizeof(buf)) break;
  }
  return s;
}

static int CountSubstring(const std::string &haystack, const std::string &needle) {
  if (needle.empty()) return 0;
  int count = 0;
  size_t pos = 0;
  while (true) {
    pos = haystack.find(needle, pos);
    if (pos == std::string::npos) break;
    ++count;
    pos += needle.size();
  }
  return count;
}

static std::unique_ptr<PDFDoc> OpenPdfDoc(const std::string &path) {
  auto name = std::make_unique<GooString>(path.c_str());
  auto cb = std::function<void(void)>([]() {});
  auto doc = std::make_unique<PDFDoc>(std::move(name), std::nullopt, std::nullopt, cb);
  return doc;
}

}  // namespace

// -----------------------------------------------------------------------------
// Tests
// -----------------------------------------------------------------------------

TEST(PrintTSVBBoxTest_2727, WritesHeaderAndPageMarkerForSinglePage_2727) {
  TempFile pdf;
  WriteFileBytes(pdf.path, BuildMinimalPdfBytes(/*num_pages=*/1, /*add_cropbox=*/false));

  auto doc = OpenPdfDoc(pdf.path);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  // TextOutputDev setup: we don't need to write to disk; pdftotext commonly passes nullptr.
  TextOutputDev textOut(nullptr, /*physLayoutA=*/false, /*fixedPitchA=*/0.0,
                        /*rawOrderA=*/false, /*append=*/false, /*discardDiagA=*/false);

  useCropBox = false;
  resolution = 72.0;

  FILE *out = tmpfile();
  ASSERT_NE(out, nullptr);

  printTSVBBox(out, doc.get(), &textOut, /*first=*/1, /*last=*/1);

  const std::string tsv = ReadAllFromFILE(out);
  std::fclose(out);

  // Observable behavior: header line and PAGE marker should exist.
  EXPECT_NE(tsv.find("level\tpage_num\tpar_num\tblock_num\tline_num\tword_num\tleft\ttop\twidth\theight\tconf\ttext\n"),
            std::string::npos);
  EXPECT_NE(tsv.find("###PAGE###"), std::string::npos);

  // The function always uses wordConf=100 for word lines and emits ###LINE### marker lines.
  // We don't assert exact bounding boxes (implementation/renderer dependent),
  // just that the markers exist.
  EXPECT_NE(tsv.find("###LINE###"), std::string::npos);

  // For our fixture, we expect to see the page word somewhere in the TSV.
  EXPECT_NE(tsv.find("Hello"), std::string::npos);
}

TEST(PrintTSVBBoxTest_2727, UseCropBoxChangesReportedPageDimensions_2727) {
  TempFile pdf;
  // MediaBox 200x200, CropBox 100x100.
  WriteFileBytes(pdf.path,
                 BuildMinimalPdfBytes(/*num_pages=*/1, /*add_cropbox=*/true,
                                      /*media_w=*/200, /*media_h=*/200,
                                      /*crop_w=*/100, /*crop_h=*/100));

  auto doc = OpenPdfDoc(pdf.path);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  TextOutputDev textOut(nullptr, /*physLayoutA=*/false, /*fixedPitchA=*/0.0,
                        /*rawOrderA=*/false, /*append=*/false, /*discardDiagA=*/false);

  // 1) Without crop box
  useCropBox = false;
  FILE *out_media = tmpfile();
  ASSERT_NE(out_media, nullptr);
  printTSVBBox(out_media, doc.get(), &textOut, /*first=*/1, /*last=*/1);
  const std::string tsv_media = ReadAllFromFILE(out_media);
  std::fclose(out_media);

  // 2) With crop box
  useCropBox = true;
  FILE *out_crop = tmpfile();
  ASSERT_NE(out_crop, nullptr);
  printTSVBBox(out_crop, doc.get(), &textOut, /*first=*/1, /*last=*/1);
  const std::string tsv_crop = ReadAllFromFILE(out_crop);
  std::fclose(out_crop);

  // We don't rely on exact float formatting beyond presence of "200" vs "100" in the PAGE line.
  // PAGE line includes: left=0 top=0 width=wid height=hgt ... ###PAGE###
  // For our constructed PDF, we expect reported width/height to differ when useCropBox flips.
  EXPECT_NE(tsv_media, tsv_crop);

  // Stronger but still tolerant: crop output should contain "100" near PAGE marker,
  // media output should contain "200" near PAGE marker.
  const auto media_page_pos = tsv_media.find("###PAGE###");
  const auto crop_page_pos = tsv_crop.find("###PAGE###");
  ASSERT_NE(media_page_pos, std::string::npos);
  ASSERT_NE(crop_page_pos, std::string::npos);

  EXPECT_NE(tsv_media.rfind("200", media_page_pos), std::string::npos);
  EXPECT_NE(tsv_crop.rfind("100", crop_page_pos), std::string::npos);
}

TEST(PrintTSVBBoxTest_2727, FirstGreaterThanLastWritesOnlyHeader_2727) {
  TempFile pdf;
  WriteFileBytes(pdf.path, BuildMinimalPdfBytes(/*num_pages=*/1, /*add_cropbox=*/false));

  auto doc = OpenPdfDoc(pdf.path);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  TextOutputDev textOut(nullptr, /*physLayoutA=*/false, /*fixedPitchA=*/0.0,
                        /*rawOrderA=*/false, /*append=*/false, /*discardDiagA=*/false);

  useCropBox = false;
  FILE *out = tmpfile();
  ASSERT_NE(out, nullptr);

  // Boundary: empty range -> loop body should not execute, but header is always printed.
  printTSVBBox(out, doc.get(), &textOut, /*first=*/2, /*last=*/1);

  const std::string tsv = ReadAllFromFILE(out);
  std::fclose(out);

  EXPECT_NE(tsv.find("level\tpage_num\tpar_num\tblock_num\tline_num\tword_num\tleft\ttop\twidth\theight\tconf\ttext\n"),
            std::string::npos);
  EXPECT_EQ(tsv.find("###PAGE###"), std::string::npos);
  EXPECT_EQ(tsv.find("###LINE###"), std::string::npos);
}

TEST(PrintTSVBBoxTest_2727, MultiPageRangeEmitsMultiplePageMarkers_2727) {
  TempFile pdf;
  WriteFileBytes(pdf.path, BuildMinimalPdfBytes(/*num_pages=*/2, /*add_cropbox=*/false));

  auto doc = OpenPdfDoc(pdf.path);
  ASSERT_TRUE(doc);
  ASSERT_TRUE(doc->isOk());

  TextOutputDev textOut(nullptr, /*physLayoutA=*/false, /*fixedPitchA=*/0.0,
                        /*rawOrderA=*/false, /*append=*/false, /*discardDiagA=*/false);

  useCropBox = false;
  FILE *out = tmpfile();
  ASSERT_NE(out, nullptr);

  printTSVBBox(out, doc.get(), &textOut, /*first=*/1, /*last=*/2);

  const std::string tsv = ReadAllFromFILE(out);
  std::fclose(out);

  // Should have one PAGE marker per page.
  EXPECT_EQ(CountSubstring(tsv, "###PAGE###"), 2);

  // Fixture words should appear (Hello on page 1, World on page 2).
  EXPECT_NE(tsv.find("Hello"), std::string::npos);
  EXPECT_NE(tsv.find("World"), std::string::npos);
}