// poppler-document_new_from_file_test_2139.cc
//
// Unit tests for poppler_document_new_from_file() (black-box via observable effects)
// Uses link-time/local stubs for external collaborators.
//
// TEST_ID: 2139

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::Eq;
using ::testing::InSequence;
using ::testing::NiceMock;
using ::testing::NotNull;
using ::testing::Return;
using ::testing::StrEq;

// -----------------------------
// Minimal GLib-ish surface
// -----------------------------
struct GError {
  int code = 0;
  std::string message;
};

static void g_set_error_literal(GError** error, int code, const char* msg) {
  if (!error) return;
  if (!*error) *error = new GError();
  (*error)->code = code;
  (*error)->message = msg ? msg : "";
}

// PopplerDocument opaque
struct PopplerDocument {
  int magic = 0;
};

// -----------------------------
// Minimal Poppler-ish deps
// -----------------------------
struct GooString {
  std::string s;
  GooString() = default;
  explicit GooString(const char* c) : s(c ? c : "") {}
  explicit GooString(std::string v) : s(std::move(v)) {}
};

enum PDFDocErrorCode {
  errNone = 0,
  errEncrypted = 1,
};

// Forward decl for error callback symbol used by GlobalParamsIniter.
extern "C" void _poppler_error_cb(int, const char*) {}

// A tiny "initer" type whose ctor is invoked by the function under test.
class GlobalParamsIniter {
 public:
  using ErrorCb = void (*)(int, const char*);
  explicit GlobalParamsIniter(ErrorCb /*cb*/) {}
  ~GlobalParamsIniter() = default;
};

// -----------------------------
// Mockable external collaborators
// -----------------------------
struct DepsMock {
  MOCK_METHOD(char*, FilenameFromUri, (const char* uri, void* dummy, GError** error));
  MOCK_METHOD(void, Free, (void* p));
  MOCK_METHOD(std::optional<GooString>, PasswordToLatin1, (const char* password));

  // We capture the PDFDoc* that was passed along, but the function signature uses unique_ptr.
  MOCK_METHOD(PopplerDocument*,
              NewFromPdfdoc,
              (std::unique_ptr<GlobalParamsIniter> initer,
               std::unique_ptr<class PDFDoc> doc,
               GError** error));
};

static DepsMock* g_deps_2139 = nullptr;

// -----------------------------
// Stubs with the same names used by the CUT
// -----------------------------
extern "C" char* g_filename_from_uri(const char* uri, char*, GError** error) {
  return g_deps_2139->FilenameFromUri(uri, nullptr, error);
}

extern "C" void g_free(void* p) { g_deps_2139->Free(p); }

// This is referenced by the CUT.
static std::optional<GooString> poppler_password_to_latin1(const char* password) {
  return g_deps_2139->PasswordToLatin1(password);
}

// This is referenced by the CUT.
static PopplerDocument* _poppler_document_new_from_pdfdoc(std::unique_ptr<GlobalParamsIniter> initer,
                                                         std::unique_ptr<class PDFDoc> doc,
                                                         GError** error) {
  return g_deps_2139->NewFromPdfdoc(std::move(initer), std::move(doc), error);
}

// -----------------------------
// Controllable PDFDoc test double
// -----------------------------
class PDFDoc {
 public:
  struct CtorRecord {
    std::string filename;
    std::string pw_user;
    std::string pw_owner;
    bool used_optional_pw = false;  // whether ctor was the optional<> overload
  };

  // Configuration for subsequent instances:
  struct Plan {
    bool is_ok = true;
    PDFDocErrorCode err = errNone;
  };

  static void Reset() {
    ctor_records().clear();
    plans().clear();
    created_ptrs().clear();
  }

  static void PushPlan(Plan p) { plans().push_back(p); }
  static const std::vector<CtorRecord>& Ctors() { return ctor_records(); }
  static size_t InstancesCreated() { return created_ptrs().size(); }

  // Non-Win32 ctor used in CUT: PDFDoc(unique_ptr<GooString>, optional<GooString>, optional<GooString>)
  PDFDoc(std::unique_ptr<GooString> filename,
         std::optional<GooString> userPW,
         std::optional<GooString> ownerPW)
      : plan_(ConsumePlan()) {
    CtorRecord rec;
    rec.filename = filename ? filename->s : "";
    rec.pw_user = userPW ? userPW->s : "";
    rec.pw_owner = ownerPW ? ownerPW->s : "";
    rec.used_optional_pw = true;
    ctor_records().push_back(std::move(rec));
    created_ptrs().push_back(this);
  }

  // Retry ctor in CUT uses GooString(password) explicitly; provide overload to detect it.
  PDFDoc(std::unique_ptr<GooString> filename, const GooString& userPW, const GooString& ownerPW)
      : plan_(ConsumePlan()) {
    CtorRecord rec;
    rec.filename = filename ? filename->s : "";
    rec.pw_user = userPW.s;
    rec.pw_owner = ownerPW.s;
    rec.used_optional_pw = false;
    ctor_records().push_back(std::move(rec));
    created_ptrs().push_back(this);
  }

  bool isOk() const { return plan_.is_ok; }
  PDFDocErrorCode getErrorCode() const { return plan_.err; }

 private:
  static Plan ConsumePlan() {
    if (plans().empty()) return Plan{};
    Plan p = plans().front();
    plans().erase(plans().begin());
    return p;
  }

  static std::vector<CtorRecord>& ctor_records() {
    static std::vector<CtorRecord> v;
    return v;
  }
  static std::vector<Plan>& plans() {
    static std::vector<Plan> v;
    return v;
  }
  static std::vector<const PDFDoc*>& created_ptrs() {
    static std::vector<const PDFDoc*> v;
    return v;
  }

  Plan plan_;
};

// -----------------------------
// Function under test (included as-is)
// -----------------------------
PopplerDocument* poppler_document_new_from_file(const char* uri, const char* password, GError** error) {
  std::unique_ptr<PDFDoc> newDoc;
  char* filename;
  auto initer = std::make_unique<GlobalParamsIniter>(_poppler_error_cb);
  filename = g_filename_from_uri(uri, nullptr, error);
  if (!filename) {
    return nullptr;
  }
  const std::optional<GooString> password_g = poppler_password_to_latin1(password);
#ifdef G_OS_WIN32
  // Not exercised in these tests; keeping structure intact.
  wchar_t* filenameW;
  int length;
  length = MultiByteToWideChar(CP_UTF8, 0, filename, -1, nullptr, 0);
  filenameW = new WCHAR[length];
  if (!filenameW) return nullptr;
  length = MultiByteToWideChar(CP_UTF8, 0, filename, -1, filenameW, length);
  newDoc = std::make_unique<PDFDoc>(filenameW, length, password_g, password_g);
  if (!newDoc->isOk() && newDoc->getErrorCode() == errEncrypted && password) {
    newDoc = std::make_unique<PDFDoc>(filenameW, length, GooString(password), GooString(password));
  }
  delete[] filenameW;
#else
  newDoc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename), password_g, password_g);
  if (!newDoc->isOk() && newDoc->getErrorCode() == errEncrypted && password) {
    newDoc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename), GooString(password), GooString(password));
  }
#endif
  g_free(filename);
  return _poppler_document_new_from_pdfdoc(std::move(initer), std::move(newDoc), error);
}

// -----------------------------
// Tests
// -----------------------------
class PopplerDocumentNewFromFileTest_2139 : public ::testing::Test {
 protected:
  void SetUp() override {
    PDFDoc::Reset();
    g_deps_2139 = &deps_;
  }
  void TearDown() override { g_deps_2139 = nullptr; }

  NiceMock<DepsMock> deps_;
};

TEST_F(PopplerDocumentNewFromFileTest_2139, ReturnsNullWhenFilenameFromUriFails_2139) {
  GError* err = nullptr;

  EXPECT_CALL(deps_, FilenameFromUri(StrEq("bad://uri"), _, NotNull()))
      .WillOnce([](const char*, void*, GError** error) -> char* {
        g_set_error_literal(error, 7, "bad uri");
        return nullptr;
      });
  EXPECT_CALL(deps_, PasswordToLatin1(_)).Times(0);
  EXPECT_CALL(deps_, Free(_)).Times(0);
  EXPECT_CALL(deps_, NewFromPdfdoc(_, _, _)).Times(0);

  PopplerDocument* doc = poppler_document_new_from_file("bad://uri", "pw", &err);
  EXPECT_EQ(doc, nullptr);
  ASSERT_NE(err, nullptr);
  EXPECT_EQ(err->code, 7);
  EXPECT_EQ(err->message, "bad uri");

  delete err;
}

TEST_F(PopplerDocumentNewFromFileTest_2139, SuccessPathCallsNewFromPdfdocAndFreesFilename_2139) {
  GError* err = nullptr;

  // Prepare PDFDoc to be OK on first construction.
  PDFDoc::PushPlan({/*is_ok=*/true, /*err=*/errNone});

  {
    InSequence s;

    EXPECT_CALL(deps_, FilenameFromUri(StrEq("file:///tmp/a.pdf"), _, NotNull()))
        .WillOnce([](const char*, void*, GError**) -> char* {
          // Return a heap string that must be freed by g_free.
          char* p = new char[16];
          std::snprintf(p, 16, "%s", "/tmp/a.pdf");
          return p;
        });

    EXPECT_CALL(deps_, PasswordToLatin1(StrEq("pw"))).WillOnce([](const char*) {
      return std::optional<GooString>(GooString("pw-latin1"));
    });

    EXPECT_CALL(deps_, Free(_)).WillOnce([](void* p) { delete[] static_cast<char*>(p); });

    EXPECT_CALL(deps_, NewFromPdfdoc(_, _, NotNull()))
        .WillOnce([](std::unique_ptr<GlobalParamsIniter> initer,
                     std::unique_ptr<PDFDoc> pdf,
                     GError**) -> PopplerDocument* {
          EXPECT_NE(initer, nullptr);
          EXPECT_NE(pdf, nullptr);

          auto* out = new PopplerDocument();
          out->magic = 123;
          return out;
        });
  }

  PopplerDocument* doc = poppler_document_new_from_file("file:///tmp/a.pdf", "pw", &err);
  ASSERT_NE(doc, nullptr);
  EXPECT_EQ(doc->magic, 123);

  // Verify the PDFDoc was constructed once and used the optional-password overload.
  ASSERT_EQ(PDFDoc::Ctors().size(), 1u);
  EXPECT_EQ(PDFDoc::Ctors()[0].filename, "/tmp/a.pdf");
  EXPECT_EQ(PDFDoc::Ctors()[0].pw_user, "pw-latin1");
  EXPECT_EQ(PDFDoc::Ctors()[0].pw_owner, "pw-latin1");
  EXPECT_TRUE(PDFDoc::Ctors()[0].used_optional_pw);

  delete doc;
  delete err;
}

TEST_F(PopplerDocumentNewFromFileTest_2139, EncryptedWithPasswordRetriesWithOriginalPassword_2139) {
  GError* err = nullptr;

  // First instance: not ok + encrypted; second instance: ok.
  PDFDoc::PushPlan({/*is_ok=*/false, /*err=*/errEncrypted});
  PDFDoc::PushPlan({/*is_ok=*/true, /*err=*/errNone});

  EXPECT_CALL(deps_, FilenameFromUri(StrEq("file:///tmp/enc.pdf"), _, NotNull()))
      .WillOnce([](const char*, void*, GError**) -> char* {
        char* p = new char[32];
        std::snprintf(p, 32, "%s", "/tmp/enc.pdf");
        return p;
      });

  // Even if latin1 conversion exists, retry should use the original password overload (non-optional).
  EXPECT_CALL(deps_, PasswordToLatin1(StrEq("pässwörd"))).WillOnce([](const char*) {
    return std::optional<GooString>(GooString("latin1-maybe-lossy"));
  });

  EXPECT_CALL(deps_, Free(_)).WillOnce([](void* p) { delete[] static_cast<char*>(p); });

  EXPECT_CALL(deps_, NewFromPdfdoc(_, _, NotNull()))
      .WillOnce([](std::unique_ptr<GlobalParamsIniter>, std::unique_ptr<PDFDoc> pdf, GError**) {
        EXPECT_NE(pdf, nullptr);
        return new PopplerDocument();
      });

  PopplerDocument* doc = poppler_document_new_from_file("file:///tmp/enc.pdf", "pässwörd", &err);
  ASSERT_NE(doc, nullptr);

  // Two constructions: first optional<> overload, then retry non-optional overload.
  ASSERT_EQ(PDFDoc::Ctors().size(), 2u);

  EXPECT_TRUE(PDFDoc::Ctors()[0].used_optional_pw);
  EXPECT_EQ(PDFDoc::Ctors()[0].pw_user, "latin1-maybe-lossy");

  EXPECT_FALSE(PDFDoc::Ctors()[1].used_optional_pw);
  EXPECT_EQ(PDFDoc::Ctors()[1].pw_user, "pässwörd");
  EXPECT_EQ(PDFDoc::Ctors()[1].pw_owner, "pässwörd");

  delete doc;
  delete err;
}

TEST_F(PopplerDocumentNewFromFileTest_2139, EncryptedWithoutPasswordDoesNotRetry_2139) {
  GError* err = nullptr;

  // If password is null, retry must NOT occur even if encrypted.
  PDFDoc::PushPlan({/*is_ok=*/false, /*err=*/errEncrypted});

  EXPECT_CALL(deps_, FilenameFromUri(StrEq("file:///tmp/enc2.pdf"), _, NotNull()))
      .WillOnce([](const char*, void*, GError**) -> char* {
        char* p = new char[32];
        std::snprintf(p, 32, "%s", "/tmp/enc2.pdf");
        return p;
      });

  EXPECT_CALL(deps_, PasswordToLatin1(Eq(nullptr))).WillOnce(Return(std::optional<GooString>{}));

  EXPECT_CALL(deps_, Free(_)).WillOnce([](void* p) { delete[] static_cast<char*>(p); });

  EXPECT_CALL(deps_, NewFromPdfdoc(_, _, NotNull()))
      .WillOnce([](std::unique_ptr<GlobalParamsIniter>, std::unique_ptr<PDFDoc> pdf, GError**) {
        EXPECT_NE(pdf, nullptr);
        return new PopplerDocument();
      });

  PopplerDocument* doc = poppler_document_new_from_file("file:///tmp/enc2.pdf", nullptr, &err);
  ASSERT_NE(doc, nullptr);

  // Only one construction, and it must be the optional<> overload.
  ASSERT_EQ(PDFDoc::Ctors().size(), 1u);
  EXPECT_TRUE(PDFDoc::Ctors()[0].used_optional_pw);

  delete doc;
  delete err;
}

TEST_F(PopplerDocumentNewFromFileTest_2139, PropagatesErrorPointerToNewFromPdfdoc_2139) {
  GError* err = nullptr;

  PDFDoc::PushPlan({/*is_ok=*/true, /*err=*/errNone});

  EXPECT_CALL(deps_, FilenameFromUri(StrEq("file:///tmp/x.pdf"), _, NotNull()))
      .WillOnce([](const char*, void*, GError**) -> char* {
        char* p = new char[16];
        std::snprintf(p, 16, "%s", "/tmp/x.pdf");
        return p;
      });

  EXPECT_CALL(deps_, PasswordToLatin1(_)).WillOnce(Return(std::optional<GooString>{}));

  EXPECT_CALL(deps_, Free(_)).WillOnce([](void* p) { delete[] static_cast<char*>(p); });

  EXPECT_CALL(deps_, NewFromPdfdoc(_, _, NotNull()))
      .WillOnce([](std::unique_ptr<GlobalParamsIniter>, std::unique_ptr<PDFDoc>, GError** errorp) {
        // Observable interaction: the same address passed through.
        EXPECT_NE(errorp, nullptr);
        g_set_error_literal(errorp, 42, "from _poppler_document_new_from_pdfdoc");
        return new PopplerDocument();
      });

  PopplerDocument* doc = poppler_document_new_from_file("file:///tmp/x.pdf", nullptr, &err);
  ASSERT_NE(doc, nullptr);
  ASSERT_NE(err, nullptr);
  EXPECT_EQ(err->code, 42);
  EXPECT_EQ(err->message, "from _poppler_document_new_from_pdfdoc");

  delete doc;
  delete err;
}