// poppler-document-set-property-test-2210.cc
//
// Unit tests for PopplerDocument GObject property setter routing.
//
// Constraints honored:
// - Treat implementation as a black box (no internal logic assumptions).
// - Test only via public/observable behavior (g_object_set/g_object_get and public constructor).
// - No private/internal state access.

#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

#include <poppler.h>

#include <climits>
#include <cstring>
#include <memory>
#include <string>

namespace {

struct GObjectUnrefDeleter {
  void operator()(gpointer p) const {
    if (p) {
      g_object_unref(p);
    }
  }
};
using PopplerDocumentPtr = std::unique_ptr<PopplerDocument, GObjectUnrefDeleter>;

static std::string TryBuildPdfPath() {
  // Try common layouts used by Poppler/GLib test harnesses. If none exist, tests will skip.
  const char* candidates[] = {
#ifdef TESTDATADIR
      TESTDATADIR "/basic.pdf",
      TESTDATADIR "/tests/basic.pdf",
      TESTDATADIR "/data/basic.pdf",
      TESTDATADIR "/pdfs/basic.pdf",
#endif
#ifdef SRCDIR
      SRCDIR "/basic.pdf",
      SRCDIR "/tests/basic.pdf",
      SRCDIR "/data/basic.pdf",
      SRCDIR "/pdfs/basic.pdf",
      SRCDIR "/testfiles/basic.pdf",
#endif
      // Some projects place test PDFs under a "files" directory.
      "files/basic.pdf",
      "testfiles/basic.pdf",
      "data/basic.pdf",
  };

  for (const char* c : candidates) {
    if (!c) continue;
    if (g_file_test(c, G_FILE_TEST_IS_REGULAR)) {
      return std::string(c);
    }
  }
  return {};
}

static PopplerDocumentPtr OpenAnyTestDocumentOrSkip() {
  std::string path = TryBuildPdfPath();
  if (path.empty()) {
    GTEST_SKIP() << "No test PDF found (tried common TESTDATADIR/SRCDIR locations).";
  }

  GError* error = nullptr;

  // poppler_document_new_from_file expects an URI.
  gchar* uri = g_filename_to_uri(path.c_str(), /*hostname=*/nullptr, &error);
  if (!uri) {
    std::string msg = error ? error->message : "unknown";
    if (error) g_error_free(error);
    GTEST_SKIP() << "Failed to build file URI for '" << path << "': " << msg;
  }

  PopplerDocument* doc = poppler_document_new_from_file(uri, /*password=*/nullptr, &error);
  g_free(uri);

  if (!doc) {
    std::string msg = error ? error->message : "unknown";
    if (error) g_error_free(error);
    GTEST_SKIP() << "Failed to open PopplerDocument from '" << path << "': " << msg;
  }

  if (error) g_error_free(error);
  return PopplerDocumentPtr(doc);
}

static std::string GetStringProperty(GObject* obj, const char* prop_name) {
  gchar* out = nullptr;
  g_object_get(obj, prop_name, &out, nullptr);
  std::string s = out ? out : "";
  g_free(out);
  return s;
}

static bool IsNullOrEmptyStringProperty(GObject* obj, const char* prop_name) {
  gchar* out = nullptr;
  g_object_get(obj, prop_name, &out, nullptr);
  bool ok = (out == nullptr) || (out[0] == '\0');
  g_free(out);
  return ok;
}

static int GetIntProperty(GObject* obj, const char* prop_name) {
  gint out = 0;
  g_object_get(obj, prop_name, &out, nullptr);
  return static_cast<int>(out);
}

static GDateTime* GetDateTimeProperty(GObject* obj, const char* prop_name) {
  // Caller owns returned reference (boxed copy semantics depend on property;
  // treat as opaque and unref if non-null).
  GDateTime* out = nullptr;
  g_object_get(obj, prop_name, &out, nullptr);
  return out;
}

// Simple log capture to verify warnings (exceptional/edge observable behavior).
struct LogCapture {
  static void Handler(const gchar* log_domain,
                      GLogLevelFlags log_level,
                      const gchar* message,
                      gpointer user_data) {
    auto* self = static_cast<LogCapture*>(user_data);
    if (self->domain && log_domain && std::strcmp(self->domain, log_domain) != 0) {
      return;
    }
    if ((log_level & self->level_mask) == 0) return;
    if (self->must_contain.empty() || (message && std::strstr(message, self->must_contain.c_str()))) {
      self->count++;
      self->last_message = message ? message : "";
    }
  }

  LogCapture(const char* d, GLogLevelFlags mask, std::string contains)
      : domain(d), level_mask(mask), must_contain(std::move(contains)) {
    handler_id = g_log_set_handler(domain, level_mask, &LogCapture::Handler, this);
  }

  ~LogCapture() {
    if (handler_id != 0) {
      g_log_remove_handler(domain, handler_id);
    }
  }

  const char* domain = nullptr;
  GLogLevelFlags level_mask = static_cast<GLogLevelFlags>(0);
  std::string must_contain;
  guint handler_id = 0;

  int count = 0;
  std::string last_message;
};

class PopplerDocumentSetPropertyTest_2210 : public ::testing::Test {
 protected:
  void SetUp() override { doc_ = OpenAnyTestDocumentOrSkip(); }

  PopplerDocumentPtr doc_;
};

TEST_F(PopplerDocumentSetPropertyTest_2210, SetTitleRoutesToSetterAndIsObservableViaGet_2210) {
  ASSERT_NE(doc_.get(), nullptr);

  g_object_set(G_OBJECT(doc_.get()), "title", "UnitTest Title", nullptr);
  EXPECT_EQ(GetStringProperty(G_OBJECT(doc_.get()), "title"), "UnitTest Title");
}

TEST_F(PopplerDocumentSetPropertyTest_2210, SetAuthorRoutesToSetterAndIsObservableViaGet_2210) {
  ASSERT_NE(doc_.get(), nullptr);

  g_object_set(G_OBJECT(doc_.get()), "author", "UnitTest Author", nullptr);
  EXPECT_EQ(GetStringProperty(G_OBJECT(doc_.get()), "author"), "UnitTest Author");
}

TEST_F(PopplerDocumentSetPropertyTest_2210, SetSubjectRoutesToSetterAndIsObservableViaGet_2210) {
  ASSERT_NE(doc_.get(), nullptr);

  g_object_set(G_OBJECT(doc_.get()), "subject", "UnitTest Subject", nullptr);
  EXPECT_EQ(GetStringProperty(G_OBJECT(doc_.get()), "subject"), "UnitTest Subject");
}

TEST_F(PopplerDocumentSetPropertyTest_2210, SetKeywordsRoutesToSetterAndIsObservableViaGet_2210) {
  ASSERT_NE(doc_.get(), nullptr);

  g_object_set(G_OBJECT(doc_.get()), "keywords", "k1, k2, k3", nullptr);
  EXPECT_EQ(GetStringProperty(G_OBJECT(doc_.get()), "keywords"), "k1, k2, k3");
}

TEST_F(PopplerDocumentSetPropertyTest_2210, SetCreatorRoutesToSetterAndIsObservableViaGet_2210) {
  ASSERT_NE(doc_.get(), nullptr);

  g_object_set(G_OBJECT(doc_.get()), "creator", "UnitTest Creator", nullptr);
  EXPECT_EQ(GetStringProperty(G_OBJECT(doc_.get()), "creator"), "UnitTest Creator");
}

TEST_F(PopplerDocumentSetPropertyTest_2210, SetProducerRoutesToSetterAndIsObservableViaGet_2210) {
  ASSERT_NE(doc_.get(), nullptr);

  g_object_set(G_OBJECT(doc_.get()), "producer", "UnitTest Producer", nullptr);
  EXPECT_EQ(GetStringProperty(G_OBJECT(doc_.get()), "producer"), "UnitTest Producer");
}

TEST_F(PopplerDocumentSetPropertyTest_2210, StringPropertiesHandleEmptyStringBoundary_2210) {
  ASSERT_NE(doc_.get(), nullptr);

  g_object_set(G_OBJECT(doc_.get()), "title", "", "author", "", "subject", "", "keywords", "", nullptr);

  EXPECT_EQ(GetStringProperty(G_OBJECT(doc_.get()), "title"), "");
  EXPECT_EQ(GetStringProperty(G_OBJECT(doc_.get()), "author"), "");
  EXPECT_EQ(GetStringProperty(G_OBJECT(doc_.get()), "subject"), "");
  EXPECT_EQ(GetStringProperty(G_OBJECT(doc_.get()), "keywords"), "");
}

TEST_F(PopplerDocumentSetPropertyTest_2210, StringPropertiesHandleNullStringBoundaryWithoutCrash_2210) {
  ASSERT_NE(doc_.get(), nullptr);

  // Observable requirement here: no crash, and property becomes either NULL or empty string.
  g_object_set(G_OBJECT(doc_.get()), "title", static_cast<const gchar*>(nullptr), nullptr);
  g_object_set(G_OBJECT(doc_.get()), "author", static_cast<const gchar*>(nullptr), nullptr);
  g_object_set(G_OBJECT(doc_.get()), "subject", static_cast<const gchar*>(nullptr), nullptr);
  g_object_set(G_OBJECT(doc_.get()), "keywords", static_cast<const gchar*>(nullptr), nullptr);

  EXPECT_TRUE(IsNullOrEmptyStringProperty(G_OBJECT(doc_.get()), "title"));
  EXPECT_TRUE(IsNullOrEmptyStringProperty(G_OBJECT(doc_.get()), "author"));
  EXPECT_TRUE(IsNullOrEmptyStringProperty(G_OBJECT(doc_.get()), "subject"));
  EXPECT_TRUE(IsNullOrEmptyStringProperty(G_OBJECT(doc_.get()), "keywords"));
}

TEST_F(PopplerDocumentSetPropertyTest_2210, StringPropertiesSupportLongValuesBoundary_2210) {
  ASSERT_NE(doc_.get(), nullptr);

  std::string long_str(4096, 'A');
  g_object_set(G_OBJECT(doc_.get()), "producer", long_str.c_str(), nullptr);

  EXPECT_EQ(GetStringProperty(G_OBJECT(doc_.get()), "producer").size(), long_str.size());
  EXPECT_EQ(GetStringProperty(G_OBJECT(doc_.get()), "producer"), long_str);
}

TEST_F(PopplerDocumentSetPropertyTest_2210, SetCreationAndModificationDateIntAreObservableViaGet_2210) {
  ASSERT_NE(doc_.get(), nullptr);

  // Boundary values for gint (we use INT_* as conservative boundaries here).
  g_object_set(G_OBJECT(doc_.get()), "creation-date", 0, nullptr);
  EXPECT_EQ(GetIntProperty(G_OBJECT(doc_.get()), "creation-date"), 0);

  g_object_set(G_OBJECT(doc_.get()), "mod-date", INT_MAX, nullptr);
  EXPECT_EQ(GetIntProperty(G_OBJECT(doc_.get()), "mod-date"), INT_MAX);

  g_object_set(G_OBJECT(doc_.get()), "creation-date", INT_MIN, nullptr);
  EXPECT_EQ(GetIntProperty(G_OBJECT(doc_.get()), "creation-date"), INT_MIN);
}

TEST_F(PopplerDocumentSetPropertyTest_2210, SetCreationAndModificationDateTimeAreObservableViaGet_2210) {
  ASSERT_NE(doc_.get(), nullptr);

  GDateTime* dt = g_date_time_new_utc(2020, 1, 2, 3, 4, 5);
  ASSERT_NE(dt, nullptr);

  g_object_set(G_OBJECT(doc_.get()), "creation-datetime", dt, nullptr);
  g_object_set(G_OBJECT(doc_.get()), "mod-datetime", dt, nullptr);

  GDateTime* got_creation = GetDateTimeProperty(G_OBJECT(doc_.get()), "creation-datetime");
  GDateTime* got_mod = GetDateTimeProperty(G_OBJECT(doc_.get()), "mod-datetime");

  // Observable behavior: returned boxed values, if non-null, represent the same moment.
  // (We do not assume pointer identity.)
  ASSERT_NE(got_creation, nullptr);
  ASSERT_NE(got_mod, nullptr);

  EXPECT_EQ(g_date_time_to_unix(got_creation), g_date_time_to_unix(dt));
  EXPECT_EQ(g_date_time_to_unix(got_mod), g_date_time_to_unix(dt));

  g_date_time_unref(got_creation);
  g_date_time_unref(got_mod);
  g_date_time_unref(dt);
}

TEST_F(PopplerDocumentSetPropertyTest_2210, SettingNullDateTimeDoesNotCrashAndIsObservable_2210) {
  ASSERT_NE(doc_.get(), nullptr);

  g_object_set(G_OBJECT(doc_.get()), "creation-datetime", static_cast<GDateTime*>(nullptr), nullptr);
  g_object_set(G_OBJECT(doc_.get()), "mod-datetime", static_cast<GDateTime*>(nullptr), nullptr);

  GDateTime* got_creation = GetDateTimeProperty(G_OBJECT(doc_.get()), "creation-datetime");
  GDateTime* got_mod = GetDateTimeProperty(G_OBJECT(doc_.get()), "mod-datetime");

  // Accept either null (cleared) or non-null (implementation-defined), but must not crash.
  if (got_creation) g_date_time_unref(got_creation);
  if (got_mod) g_date_time_unref(got_mod);
}

TEST_F(PopplerDocumentSetPropertyTest_2210, SettingUnknownPropertyEmitsWarning_2210) {
  ASSERT_NE(doc_.get(), nullptr);

  // Verify observable exceptional behavior: GObject warns for unknown properties.
  LogCapture capture("GLib-GObject", static_cast<GLogLevelFlags>(G_LOG_LEVEL_WARNING),
                     "has no property named");

  // Use a property name that should not exist on PopplerDocument.
  g_object_set(G_OBJECT(doc_.get()), "this-property-should-not-exist-2210", 1, nullptr);

  EXPECT_GE(capture.count, 1) << "Expected a GLib-GObject warning for unknown property.";
}

}  // namespace