// poppler-action-build-movie-test_2297.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstdio>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace {

class PopplerBuildMovieTest_2297 : public ::testing::Test {
 protected:
  void TearDown() override {
    if (!tmp_path_.empty()) {
      std::remove(tmp_path_.c_str());
      tmp_path_.clear();
    }
  }

  static std::string MakeFileUri(const std::string& path) {
#ifdef G_OS_WIN32
    // Best-effort: Poppler GLib supports file:// URIs; Windows paths may need extra handling.
    // In this project context (Linux-like), this is unlikely used.
    return std::string("file:///") + path;
#else
    return std::string("file://") + path;
#endif
  }

  static std::string BuildPdfWithObjects(const std::vector<std::string>& objs) {
    // objs is 1-based: objs[i-1] is "i 0 obj ... endobj"
    std::ostringstream out;
    out << "%PDF-1.7\n%\xE2\xE3\xCF\xD3\n";

    std::vector<long> offsets;
    offsets.reserve(objs.size() + 1);
    offsets.push_back(0);  // object 0

    for (const auto& obj : objs) {
      long pos = static_cast<long>(out.tellp());
      offsets.push_back(pos);
      out << obj;
      if (obj.empty() || obj.back() != '\n') out << "\n";
    }

    long xref_pos = static_cast<long>(out.tellp());
    out << "xref\n";
    out << "0 " << (objs.size() + 1) << "\n";
    out << "0000000000 65535 f \n";
    for (size_t i = 1; i < offsets.size(); ++i) {
      char buf[32];
      std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
      out << buf;
    }

    out << "trailer\n";
    out << "<< /Size " << (objs.size() + 1) << " /Root 1 0 R >>\n";
    out << "startxref\n";
    out << xref_pos << "\n";
    out << "%%EOF\n";
    return out.str();
  }

  // Creates a minimal one-page PDF with:
  // - an "annotation" object (either /Subtype /Movie or /Subtype /Text)
  // - a /Link annotation with a /Movie action (/S /Movie), optionally containing /Annot and /Operation
  //
  // operation_name: "Play", "Pause", "Resume", "Stop" (PDF name without leading '/')
  // include_operation: if false, /Operation omitted (should default to "Play")
  // include_annot_ref: if false, /Annot omitted (should result in no PopplerMovie created)
  // annot_is_movie: if false, annot uses /Subtype /Text (so lookup should fail)
  std::string WriteTempPdfMovieAction(const std::string& operation_name,
                                      bool include_operation,
                                      bool include_annot_ref,
                                      bool annot_is_movie) {
    // Object numbering:
    // 1: Catalog
    // 2: Pages
    // 3: Page
    // 4: Target annotation (Movie or Text)
    // 5: Link annotation (with /A Movie action)
    std::vector<std::string> objs;

    objs.push_back(
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n");

    objs.push_back(
        "2 0 obj\n"
        "<< /Type /Pages /Count 1 /Kids [3 0 R] >>\n"
        "endobj\n");

    // Annots array includes both objects 4 and 5, regardless of their subtype.
    objs.push_back(
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R\n"
        "   /MediaBox [0 0 300 300]\n"
        "   /Resources << >>\n"
        "   /Annots [4 0 R 5 0 R]\n"
        ">>\n"
        "endobj\n");

    if (annot_is_movie) {
      // Minimal Movie annotation. The /Movie dictionary is kept simple.
      objs.push_back(
          "4 0 obj\n"
          "<< /Type /Annot /Subtype /Movie /Rect [10 10 50 50]\n"
          "   /Movie << /F (movie.mov) >>\n"
          ">>\n"
          "endobj\n");
    } else {
      // Non-movie annotation to ensure lookup does not yield a Movie.
      objs.push_back(
          "4 0 obj\n"
          "<< /Type /Annot /Subtype /Text /Rect [10 10 50 50]\n"
          "   /Contents (Not a movie)\n"
          ">>\n"
          "endobj\n");
    }

    std::ostringstream action_dict;
    action_dict << "<< /S /Movie ";
    if (include_annot_ref) {
      action_dict << "/Annot 4 0 R ";
    }
    if (include_operation) {
      action_dict << "/Operation /" << operation_name << " ";
    }
    action_dict << ">>";

    std::ostringstream link_annot;
    link_annot
        << "5 0 obj\n"
        << "<< /Type /Annot /Subtype /Link /Rect [60 60 120 120]\n"
        << "   /Border [0 0 0]\n"
        << "   /A " << action_dict.str() << "\n"
        << ">>\n"
        << "endobj\n";
    objs.push_back(link_annot.str());

    std::string pdf = BuildPdfWithObjects(objs);

    // Write to a unique temp path.
    gchar* tmp_name = g_strdup_printf("poppler_build_movie_2297_%u.pdf", g_random_int());
    tmp_path_ = tmp_name;
    g_free(tmp_name);

    std::ofstream f(tmp_path_, std::ios::binary);
    f.write(pdf.data(), static_cast<std::streamsize>(pdf.size()));
    f.close();

    return tmp_path_;
  }

  struct ExtractedAction {
    PopplerAction* action = nullptr;     // owned by mapping list
    PopplerPage* page = nullptr;         // owned by caller
    PopplerDocument* doc = nullptr;      // owned by caller
    GList* mappings = nullptr;           // owned by caller (free via poppler_page_free_link_mapping)
  };

  static ExtractedAction LoadFirstLinkAction(const std::string& file_path) {
    ExtractedAction out;

    GError* err = nullptr;
    std::string uri = MakeFileUri(file_path);

    out.doc = poppler_document_new_from_file(uri.c_str(), /*password=*/nullptr, &err);
    EXPECT_EQ(err, nullptr) << (err ? err->message : "");
    if (!out.doc) {
      if (err) g_error_free(err);
      return out;
    }

    out.page = poppler_document_get_page(out.doc, 0);
    EXPECT_NE(out.page, nullptr);
    if (!out.page) {
      g_object_unref(out.doc);
      out.doc = nullptr;
      return out;
    }

    out.mappings = poppler_page_get_link_mapping(out.page);
    EXPECT_NE(out.mappings, nullptr);
    if (!out.mappings) return out;

    auto* first = static_cast<PopplerLinkMapping*>(out.mappings->data);
    EXPECT_NE(first, nullptr);
    if (!first) return out;

    out.action = first->action;
    EXPECT_NE(out.action, nullptr);
    return out;
  }

  static void CleanupExtracted(ExtractedAction* ex) {
    if (!ex) return;
    if (ex->mappings) {
      poppler_page_free_link_mapping(ex->mappings);
      ex->mappings = nullptr;
      ex->action = nullptr;
    }
    if (ex->page) {
      g_object_unref(ex->page);
      ex->page = nullptr;
    }
    if (ex->doc) {
      g_object_unref(ex->doc);
      ex->doc = nullptr;
    }
  }

  static void ExpectMovieActionBasics(PopplerAction* action) {
    ASSERT_NE(action, nullptr);
    EXPECT_EQ(action->type, POPPLER_ACTION_MOVIE);
  }

  std::string tmp_path_;
};

TEST_F(PopplerBuildMovieTest_2297, PauseOperationSetsEnumAndCreatesMovie_2297) {
  const std::string path = WriteTempPdfMovieAction("Pause", /*include_operation=*/true,
                                                   /*include_annot_ref=*/true,
                                                   /*annot_is_movie=*/true);
  auto ex = LoadFirstLinkAction(path);
  ASSERT_NE(ex.action, nullptr);
  ExpectMovieActionBasics(ex.action);

  EXPECT_EQ(ex.action->movie.operation, POPPLER_ACTION_MOVIE_PAUSE);
  EXPECT_NE(ex.action->movie.movie, nullptr);

  CleanupExtracted(&ex);
}

TEST_F(PopplerBuildMovieTest_2297, ResumeOperationSetsEnumAndCreatesMovie_2297) {
  const std::string path = WriteTempPdfMovieAction("Resume", /*include_operation=*/true,
                                                   /*include_annot_ref=*/true,
                                                   /*annot_is_movie=*/true);
  auto ex = LoadFirstLinkAction(path);
  ASSERT_NE(ex.action, nullptr);
  ExpectMovieActionBasics(ex.action);

  EXPECT_EQ(ex.action->movie.operation, POPPLER_ACTION_MOVIE_RESUME);
  EXPECT_NE(ex.action->movie.movie, nullptr);

  CleanupExtracted(&ex);
}

TEST_F(PopplerBuildMovieTest_2297, StopOperationSetsEnumAndCreatesMovie_2297) {
  const std::string path = WriteTempPdfMovieAction("Stop", /*include_operation=*/true,
                                                   /*include_annot_ref=*/true,
                                                   /*annot_is_movie=*/true);
  auto ex = LoadFirstLinkAction(path);
  ASSERT_NE(ex.action, nullptr);
  ExpectMovieActionBasics(ex.action);

  EXPECT_EQ(ex.action->movie.operation, POPPLER_ACTION_MOVIE_STOP);
  EXPECT_NE(ex.action->movie.movie, nullptr);

  CleanupExtracted(&ex);
}

TEST_F(PopplerBuildMovieTest_2297, PlayOperationSetsEnumAndCreatesMovie_2297) {
  const std::string path = WriteTempPdfMovieAction("Play", /*include_operation=*/true,
                                                   /*include_annot_ref=*/true,
                                                   /*annot_is_movie=*/true);
  auto ex = LoadFirstLinkAction(path);
  ASSERT_NE(ex.action, nullptr);
  ExpectMovieActionBasics(ex.action);

  EXPECT_EQ(ex.action->movie.operation, POPPLER_ACTION_MOVIE_PLAY);
  EXPECT_NE(ex.action->movie.movie, nullptr);

  CleanupExtracted(&ex);
}

TEST_F(PopplerBuildMovieTest_2297, MissingOperationDefaultsToPlay_2297) {
  const std::string path = WriteTempPdfMovieAction("Pause", /*include_operation=*/false,
                                                   /*include_annot_ref=*/true,
                                                   /*annot_is_movie=*/true);
  auto ex = LoadFirstLinkAction(path);
  ASSERT_NE(ex.action, nullptr);
  ExpectMovieActionBasics(ex.action);

  // When /Operation is missing, build_movie's switch default maps to PLAY.
  EXPECT_EQ(ex.action->movie.operation, POPPLER_ACTION_MOVIE_PLAY);
  EXPECT_NE(ex.action->movie.movie, nullptr);

  CleanupExtracted(&ex);
}

TEST_F(PopplerBuildMovieTest_2297, MissingAnnotRefDoesNotCreateMovie_2297) {
  const std::string path = WriteTempPdfMovieAction("Pause", /*include_operation=*/true,
                                                   /*include_annot_ref=*/false,
                                                   /*annot_is_movie=*/true);
  auto ex = LoadFirstLinkAction(path);
  ASSERT_NE(ex.action, nullptr);
  ExpectMovieActionBasics(ex.action);

  EXPECT_EQ(ex.action->movie.operation, POPPLER_ACTION_MOVIE_PAUSE);
  // If the action can't be associated with an AnnotMovie, movie stays null.
  EXPECT_EQ(ex.action->movie.movie, nullptr);

  CleanupExtracted(&ex);
}

TEST_F(PopplerBuildMovieTest_2297, NonMovieAnnotDoesNotCreateMovie_2297) {
  const std::string path = WriteTempPdfMovieAction("Stop", /*include_operation=*/true,
                                                   /*include_annot_ref=*/true,
                                                   /*annot_is_movie=*/false);
  auto ex = LoadFirstLinkAction(path);
  ASSERT_NE(ex.action, nullptr);
  ExpectMovieActionBasics(ex.action);

  EXPECT_EQ(ex.action->movie.operation, POPPLER_ACTION_MOVIE_STOP);
  // Annot exists, but is not a Movie annotation; lookup should fail => null movie.
  EXPECT_EQ(ex.action->movie.movie, nullptr);

  CleanupExtracted(&ex);
}

}  // namespace