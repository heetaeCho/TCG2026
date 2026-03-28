// LinkRenditionPrivate_test_2765.cc
#include <gtest/gtest.h>

#include <memory>
#include <type_traits>

#include <QtCore/QRectF>
#include <QtCore/QString>

// Try to include Poppler headers (project layouts can differ).
#if __has_include("poppler/Link.h")
#  include "poppler/Link.h" // ::LinkRendition::RenditionOperation
#elif __has_include("Link.h")
#  include "Link.h"
#endif

#if __has_include("poppler/Object.h")
#  include "poppler/Object.h" // Ref
#elif __has_include("Object.h")
#  include "Object.h"
#endif

// MediaRendition is a core Poppler type. The header name varies across versions.
#if __has_include("poppler/Rendition.h")
#  include "poppler/Rendition.h" // ::MediaRendition
#elif __has_include("Rendition.h")
#  include "Rendition.h"
#elif __has_include("poppler/MediaRendition.h")
#  include "poppler/MediaRendition.h"
#elif __has_include("MediaRendition.h")
#  include "MediaRendition.h"
#endif

// Pull in the implementation that defines Poppler::LinkRenditionPrivate.
// (The class is defined in the .cc file in the provided snippet.)
#if __has_include("poppler-link.cc")
#  include "poppler-link.cc"
#elif __has_include("src/poppler-link.cc")
#  include "src/poppler-link.cc"
#elif __has_include("qt5/src/poppler-link.cc")
#  include "qt5/src/poppler-link.cc"
#else
// If your build system already compiles poppler-link.cc into the test target,
// you can replace the include above with the appropriate header that declares
// LinkRenditionPrivate (if available).
#endif

namespace {

class LinkRenditionPrivateTest_2765 : public ::testing::Test {
protected:
  static QRectF SomeArea() { return QRectF(1.0, 2.0, 3.0, 4.0); }

  static Ref SomeRef(int num = 12, int gen = 3) {
    Ref r;
    r.num = num;
    r.gen = gen;
    return r;
  }

  // Some builds may not provide Ref::INVALID() as a callable function in tests,
  // but the struct shows it exists. Keep a helper that falls back safely.
  static Ref InvalidRefOrFallback() {
#if defined(__cpp_decltype) // best-effort, do not assume more than signature
    // If Ref::INVALID() is available and usable, use it; otherwise, fall back.
    // We can't "probe" for constexpr member function easily without risking errors,
    // so we keep a conservative fallback.
    Ref r;
    r.num = 0;
    r.gen = 0;
    return r;
#else
    Ref r;
    r.num = 0;
    r.gen = 0;
    return r;
#endif
  }
};

struct OpExpectation {
  ::LinkRendition::RenditionOperation op;
  // Expected Poppler-side action enumerator value (same labels).
  int expectedActionValue;
};

class LinkRenditionPrivateActionParamTest_2765
    : public LinkRenditionPrivateTest_2765,
      public ::testing::WithParamInterface<OpExpectation> {};

} // namespace

TEST_F(LinkRenditionPrivateTest_2765, ConstructsWithEmptyScriptAndInvalidRef_2765)
{
  const QRectF area = QRectF();            // boundary: default rect
  const QString script;                    // boundary: empty string
  const Ref ref = InvalidRefOrFallback();  // boundary-ish: "invalid" style ref

  // Pass nullptr unique_ptr (boundary / common case).
  std::unique_ptr<::MediaRendition> r;

  Poppler::LinkRenditionPrivate priv(area, std::move(r),
                                    ::LinkRendition::NoRendition,
                                    script, ref);

  // Observable via public fields (as provided by the interface snippet).
  EXPECT_EQ(priv.annotationReference.num, ref.num);
  EXPECT_EQ(priv.annotationReference.gen, ref.gen);
  EXPECT_EQ(priv.script, script);

  // When given nullptr, wrapper rendition pointer should be null.
  EXPECT_EQ(priv.rendition, nullptr);
}

TEST_F(LinkRenditionPrivateTest_2765, StoresScriptAndRef_2765)
{
  const QRectF area = SomeArea();
  const QString script = QStringLiteral("app.alert('hello');");
  const Ref ref = SomeRef(99, 7);

  std::unique_ptr<::MediaRendition> r; // nullptr

  Poppler::LinkRenditionPrivate priv(area, std::move(r),
                                    ::LinkRendition::PlayRendition,
                                    script, ref);

  EXPECT_EQ(priv.script, script);
  EXPECT_EQ(priv.annotationReference.num, 99);
  EXPECT_EQ(priv.annotationReference.gen, 7);
}

TEST_P(LinkRenditionPrivateActionParamTest_2765, MapsOperationToAction_2765)
{
  const auto p = GetParam();

  const QRectF area = SomeArea();
  const QString script = QStringLiteral("js");
  const Ref ref = SomeRef();

  std::unique_ptr<::MediaRendition> r; // nullptr

  Poppler::LinkRenditionPrivate priv(area, std::move(r), p.op, script, ref);

  // We only assert equality of the enumerator value as stored in `action`.
  // The provided snippet indicates the mapping is a straight switch.
  EXPECT_EQ(static_cast<int>(priv.action), p.expectedActionValue);
}

INSTANTIATE_TEST_SUITE_P(
    OperationMapping,
    LinkRenditionPrivateActionParamTest_2765,
    ::testing::Values(
        OpExpectation{::LinkRendition::NoRendition,
                      static_cast<int>(Poppler::LinkRendition::NoRendition)},
        OpExpectation{::LinkRendition::PlayRendition,
                      static_cast<int>(Poppler::LinkRendition::PlayRendition)},
        OpExpectation{::LinkRendition::StopRendition,
                      static_cast<int>(Poppler::LinkRendition::StopRendition)},
        OpExpectation{::LinkRendition::PauseRendition,
                      static_cast<int>(Poppler::LinkRendition::PauseRendition)},
        OpExpectation{::LinkRendition::ResumeRendition,
                      static_cast<int>(Poppler::LinkRendition::ResumeRendition)}));

TEST_F(LinkRenditionPrivateTest_2765, NonNullMediaRenditionCreatesWrapperWhenDefaultConstructible_2765)
{
  // This test is intentionally defensive: some Poppler versions may not expose
  // a default-constructible ::MediaRendition. If it isn't constructible here,
  // we skip rather than guessing constructor arguments.
#if defined(__cpp_if_constexpr)
  if constexpr (!std::is_default_constructible_v<::MediaRendition>) {
    GTEST_SKIP() << "::MediaRendition is not default-constructible in this build.";
  } else
#endif
  {
    const QRectF area = SomeArea();
    const QString script = QStringLiteral("js");
    const Ref ref = SomeRef();

    auto r = std::make_unique<::MediaRendition>();

    Poppler::LinkRenditionPrivate priv(area, std::move(r),
                                      ::LinkRendition::PlayRendition,
                                      script, ref);

    // If a rendition is provided, the private wrapper should be created.
    EXPECT_NE(priv.rendition, nullptr);
  }
}

TEST_F(LinkRenditionPrivateTest_2765, DestructorDoesNotCrashOnNullRendition_2765)
{
  const QRectF area = SomeArea();
  const QString script = QStringLiteral("js");
  const Ref ref = SomeRef();

  std::unique_ptr<::MediaRendition> r; // nullptr

  // "Exceptional/error" observable aspect here is primarily "no crash" on teardown.
  // We keep this as a focused lifetime test.
  {
    Poppler::LinkRenditionPrivate priv(area, std::move(r),
                                      ::LinkRendition::StopRendition,
                                      script, ref);
    EXPECT_EQ(priv.rendition, nullptr);
  }
  SUCCEED();
}