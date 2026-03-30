// File: poppler-annot-square-set-interior-color-test_2118.cc
#include <gtest/gtest.h>

#include <glib-object.h>
#include <glib.h>

#include <poppler.h> // Poppler GLib API (provides PopplerAnnotSquare + type macros)

namespace {

class GlibLogCapture {
 public:
  GlibLogCapture() = default;

  void Install() {
    Reset();

    // Capture CRITICAL logs for both default and "Poppler" domains (domain can vary).
    default_handler_id_ = g_log_set_handler(
        /*log_domain=*/nullptr,
        static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL),
        &GlibLogCapture::HandlerThunk,
        this);

    poppler_handler_id_ = g_log_set_handler(
        /*log_domain=*/"Poppler",
        static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL),
        &GlibLogCapture::HandlerThunk,
        this);
  }

  void Uninstall() {
    if (default_handler_id_ != 0) {
      g_log_remove_handler(/*log_domain=*/nullptr, default_handler_id_);
      default_handler_id_ = 0;
    }
    if (poppler_handler_id_ != 0) {
      g_log_remove_handler(/*log_domain=*/"Poppler", poppler_handler_id_);
      poppler_handler_id_ = 0;
    }
  }

  ~GlibLogCapture() { Uninstall(); }

  int critical_count() const { return critical_count_; }
  const std::string& last_message() const { return last_message_; }
  const std::string& last_domain() const { return last_domain_; }

  void Reset() {
    critical_count_ = 0;
    last_message_.clear();
    last_domain_.clear();
  }

 private:
  static void HandlerThunk(const gchar* log_domain,
                           GLogLevelFlags log_level,
                           const gchar* message,
                           gpointer user_data) {
    static_cast<GlibLogCapture*>(user_data)->Handler(log_domain, log_level, message);
  }

  void Handler(const gchar* log_domain, GLogLevelFlags log_level, const gchar* message) {
    if ((log_level & G_LOG_LEVEL_CRITICAL) == 0) return;
    ++critical_count_;
    last_domain_ = log_domain ? log_domain : "";
    last_message_ = message ? message : "";
  }

  guint default_handler_id_ = 0;
  guint poppler_handler_id_ = 0;

  int critical_count_ = 0;
  std::string last_message_;
  std::string last_domain_;
};

static PopplerAnnotSquare* NewAnnotSquareOrSkip() {
#ifdef POPPLER_TYPE_ANNOT_SQUARE
  gpointer obj = g_object_new(POPPLER_TYPE_ANNOT_SQUARE, nullptr);
  if (!obj) {
    GTEST_SKIP() << "Failed to create PopplerAnnotSquare via g_object_new().";
  }
  return POPPLER_ANNOT_SQUARE(obj);
#else
  GTEST_SKIP() << "POPPLER_TYPE_ANNOT_SQUARE not available in headers/build.";
#endif
}

static const char* FindInteriorColorPropertyName(GObject* obj) {
  if (!obj) return nullptr;

  // Try common names; if none exist, tests that depend on it will skip.
  static const char* kCandidates[] = {
      "interior-color",
      "interior_color",
      "interior-color-rgb",
      "interior_color_rgb",
  };

  GObjectClass* klass = G_OBJECT_GET_CLASS(obj);
  if (!klass) return nullptr;

  for (const char* name : kCandidates) {
    if (g_object_class_find_property(klass, name) != nullptr) return name;
  }
  return nullptr;
}

static bool TryGetInteriorColor(GObject* obj, const char* prop_name, PopplerColor* out) {
  if (!obj || !prop_name || !out) return false;

  // We deliberately use a void* and interpret only if it looks like PopplerColor.
  // This keeps the test resilient to whether the property is boxed or pointer.
  gpointer value_ptr = nullptr;
  g_object_get(obj, prop_name, &value_ptr, nullptr);
  if (!value_ptr) return false;

  // Best-effort copy assuming it is a PopplerColor-like struct.
  // If it isn't, we won't crash by reading 3 ints? (still risky) -> guard by size? not possible.
  // Therefore, only proceed if PopplerColor is expected to be a 3-int struct (as per provided dependency).
  PopplerColor* c = static_cast<PopplerColor*>(value_ptr);
  out->red = c->red;
  out->green = c->green;
  out->blue = c->blue;

  // Free best-effort: if PopplerColor is registered as a boxed type, prefer g_boxed_free.
#ifdef POPPLER_TYPE_COLOR
  if (G_TYPE_FROM_INSTANCE(reinterpret_cast<GTypeInstance*>(value_ptr)) == POPPLER_TYPE_COLOR) {
    g_boxed_free(POPPLER_TYPE_COLOR, value_ptr);
    return true;
  }
#endif
  // In many GLib APIs, g_object_get() for boxed types returns a copy that should be freed.
  // If it isn't boxed, freeing might be wrong; however PopplerColor is typically boxed.
  // To be safer, only free when the interior-color property is boxed:
  GParamSpec* pspec = g_object_class_find_property(G_OBJECT_GET_CLASS(obj), prop_name);
  if (pspec && G_PARAM_SPEC_VALUE_TYPE(pspec) != G_TYPE_POINTER) {
    g_boxed_free(G_PARAM_SPEC_VALUE_TYPE(pspec), value_ptr);
  }
  return true;
}

class PopplerAnnotSquareSetInteriorColorTest_2118 : public ::testing::Test {
 protected:
  void SetUp() override { capture_.Install(); }
  void TearDown() override { capture_.Uninstall(); }

  GlibLogCapture capture_;
};

TEST_F(PopplerAnnotSquareSetInteriorColorTest_2118, NullAnnotEmitsCriticalAndReturns_2118) {
  capture_.Reset();

  PopplerColor c;
  c.red = 0x1234;
  c.green = 0x2345;
  c.blue = 0x3456;

  // Should not crash; should emit a critical due to g_return_if_fail.
  poppler_annot_square_set_interior_color(nullptr, &c);

  EXPECT_GE(capture_.critical_count(), 1)
      << "Expected a GLib CRITICAL log for null PopplerAnnotSquare.";
  if (capture_.critical_count() >= 1) {
    // Message text varies by GLib version; look for a hint that the type check failed.
    EXPECT_TRUE(capture_.last_message().find("POPPLER_IS_ANNOT_SQUARE") != std::string::npos ||
                capture_.last_message().find("assertion") != std::string::npos)
        << "Unexpected CRITICAL message: " << capture_.last_message();
  }
}

TEST_F(PopplerAnnotSquareSetInteriorColorTest_2118, ValidAnnotDoesNotEmitCritical_2118) {
  capture_.Reset();

  PopplerAnnotSquare* annot = NewAnnotSquareOrSkip();
  ASSERT_NE(annot, nullptr);

  PopplerColor c;
  c.red = 0x1111;
  c.green = 0x2222;
  c.blue = 0x3333;

  poppler_annot_square_set_interior_color(annot, &c);

  EXPECT_EQ(capture_.critical_count(), 0)
      << "Did not expect GLib CRITICAL logs for a valid PopplerAnnotSquare.";

  g_object_unref(annot);
}

TEST_F(PopplerAnnotSquareSetInteriorColorTest_2118, ValidAnnotNullColorDoesNotEmitCritical_2118) {
  capture_.Reset();

  PopplerAnnotSquare* annot = NewAnnotSquareOrSkip();
  ASSERT_NE(annot, nullptr);

  // Boundary: color pointer is NULL. Observable behavior is "no crash" and no g_return_if_fail here.
  poppler_annot_square_set_interior_color(annot, nullptr);

  EXPECT_EQ(capture_.critical_count(), 0)
      << "Did not expect GLib CRITICAL logs when color is NULL (unless API disallows it).";

  g_object_unref(annot);
}

TEST_F(PopplerAnnotSquareSetInteriorColorTest_2118, SetsInteriorColorIfReadableViaProperty_2118) {
  capture_.Reset();

  PopplerAnnotSquare* annot = NewAnnotSquareOrSkip();
  ASSERT_NE(annot, nullptr);

  const char* prop = FindInteriorColorPropertyName(G_OBJECT(annot));
  if (!prop) {
    g_object_unref(annot);
    GTEST_SKIP() << "No readable interior color property found on PopplerAnnotSquare.";
  }

  PopplerColor c;
  c.red = 0x00AA;
  c.green = 0x00BB;
  c.blue = 0x00CC;

  poppler_annot_square_set_interior_color(annot, &c);

  EXPECT_EQ(capture_.critical_count(), 0);

  PopplerColor got;
  got.red = got.green = got.blue = 0;

  if (!TryGetInteriorColor(G_OBJECT(annot), prop, &got)) {
    g_object_unref(annot);
    GTEST_SKIP() << "Interior color property exists but could not be retrieved via g_object_get().";
  }

  EXPECT_EQ(got.red, c.red);
  EXPECT_EQ(got.green, c.green);
  EXPECT_EQ(got.blue, c.blue);

  g_object_unref(annot);
}

}  // namespace