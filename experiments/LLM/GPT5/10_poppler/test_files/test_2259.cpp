// poppler-document-ps-file-set-duplex-test_2259.cc
#include <gtest/gtest.h>

#include <glib.h>

// Forward declarations to satisfy the struct fields.
// We do not need real definitions for these tests.
struct _PopplerDocument;
struct PSOutputDev;

// The real codebase typically typedefs these like this.
typedef struct _PopplerPSFile PopplerPSFile;

// From: ./TestProjects/poppler/glib/poppler-private.h (provided)
struct _PopplerPSFile {
public:
  _PopplerDocument* document;
  PSOutputDev* out;
  char* filename;
  int first_page;
  int last_page;
  double paper_width;
  double paper_height;
  int duplex;
};

// Function under test (from poppler-document.cc)
extern "C" void poppler_ps_file_set_duplex(PopplerPSFile* ps_file, gboolean duplex);

namespace {

class ScopedGLogCatcher {
public:
  ScopedGLogCatcher() {
    prev_ = g_log_set_default_handler(&ScopedGLogCatcher::Handler, this);
  }

  ~ScopedGLogCatcher() {
    g_log_set_default_handler(prev_, nullptr);
  }

  bool SawCritical() const { return saw_critical_; }

private:
  static void Handler(const gchar* log_domain,
                      GLogLevelFlags log_level,
                      const gchar* message,
                      gpointer user_data) {
    (void)log_domain;
    (void)message;
    auto* self = static_cast<ScopedGLogCatcher*>(user_data);

    // g_return_if_fail logs at CRITICAL level.
    if (log_level & G_LOG_LEVEL_CRITICAL) {
      self->saw_critical_ = true;
    }
    // Swallow the log to avoid noisy test output / abort-on-critical setups.
  }

  GLogFunc prev_ = nullptr;
  bool saw_critical_ = false;
};

class PopplerPSFileSetDuplexTest_2259 : public ::testing::Test {
protected:
  static PopplerPSFile MakePsFile(PSOutputDev* out, int duplex_value) {
    PopplerPSFile ps{};
    ps.document = nullptr;
    ps.out = out;
    ps.filename = nullptr;
    ps.first_page = 0;
    ps.last_page = 0;
    ps.paper_width = 0.0;
    ps.paper_height = 0.0;
    ps.duplex = duplex_value;
    return ps;
  }
};

}  // namespace

TEST_F(PopplerPSFileSetDuplexTest_2259, SetsDuplexTrueWhenOutIsNull_2259) {
  PopplerPSFile ps = MakePsFile(/*out=*/nullptr, /*duplex_value=*/0);

  poppler_ps_file_set_duplex(&ps, TRUE);

  EXPECT_EQ(ps.duplex, 1);
}

TEST_F(PopplerPSFileSetDuplexTest_2259, SetsDuplexFalseWhenOutIsNull_2259) {
  PopplerPSFile ps = MakePsFile(/*out=*/nullptr, /*duplex_value=*/1);

  poppler_ps_file_set_duplex(&ps, FALSE);

  EXPECT_EQ(ps.duplex, 0);
}

TEST_F(PopplerPSFileSetDuplexTest_2259, CanToggleDuplexMultipleTimesWhenOutIsNull_2259) {
  PopplerPSFile ps = MakePsFile(/*out=*/nullptr, /*duplex_value=*/0);

  poppler_ps_file_set_duplex(&ps, TRUE);
  EXPECT_EQ(ps.duplex, 1);

  poppler_ps_file_set_duplex(&ps, FALSE);
  EXPECT_EQ(ps.duplex, 0);
}

TEST_F(PopplerPSFileSetDuplexTest_2259, DoesNotChangeDuplexAndLogsCriticalWhenOutIsNonNull_2259) {
  // Non-null out triggers g_return_if_fail(ps_file->out == nullptr).
  auto* fake_out = reinterpret_cast<PSOutputDev*>(0x1);
  PopplerPSFile ps = MakePsFile(/*out=*/fake_out, /*duplex_value=*/0);

  ScopedGLogCatcher catcher;
  poppler_ps_file_set_duplex(&ps, TRUE);

  // Should early-return without changing duplex.
  EXPECT_EQ(ps.duplex, 0);

  // Observable error behavior: a CRITICAL log should be emitted.
  EXPECT_TRUE(catcher.SawCritical());
}