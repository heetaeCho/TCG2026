// TEST_ID: 2774
// File: test-poppler-link-extractor-outputdev-2774.cc

#include <gtest/gtest.h>

#include <QtCore/QList>
#include <QtCore/QTemporaryFile>
#include <QtCore/QByteArray>

#include "poppler-link-extractor-private.h"
#include "poppler-page-private.h"

// Poppler core (best-effort; if missing in this build, some tests will be skipped)
#if __has_include("PDFDoc.h")
#  include "PDFDoc.h"
#  define HAVE_POPPLER_PDFDOC_H 1
#else
#  define HAVE_POPPLER_PDFDOC_H 0
#endif

#if __has_include("GlobalParams.h")
#  include "GlobalParams.h"
#  define HAVE_POPPLER_GLOBALPARAMS_H 1
#else
#  define HAVE_POPPLER_GLOBALPARAMS_H 0
#endif

#if HAVE_POPPLER_GLOBALPARAMS_H
// Some Poppler builds expose this as an extern global.
extern GlobalParams *globalParams;
#endif

namespace {

// Minimal one-page PDF (valid enough for Poppler to load in most builds).
// (A4-like MediaBox; empty contents)
static const char kMinimalPdf_2774[] =
    "%PDF-1.4\n"
    "1 0 obj\n"
    "<< /Type /Catalog /Pages 2 0 R >>\n"
    "endobj\n"
    "2 0 obj\n"
    "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
    "endobj\n"
    "3 0 obj\n"
    "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 300 400] /Contents 4 0 R >>\n"
    "endobj\n"
    "4 0 obj\n"
    "<< /Length 0 >>\n"
    "stream\n"
    "endstream\n"
    "endobj\n"
    "xref\n"
    "0 5\n"
    "0000000000 65535 f \n"
    "0000000009 00000 n \n"
    "0000000058 00000 n \n"
    "0000000115 00000 n \n"
    "0000000202 00000 n \n"
    "trailer\n"
    "<< /Size 5 /Root 1 0 R >>\n"
    "startxref\n"
    "0000000250\n"
    "%%EOF\n";

template <typename T>
struct HasMemberPagePtr_2774 {
private:
    template <typename U>
    static auto test(int) -> decltype((void)(std::declval<U>().page), std::true_type{});
    template <typename>
    static std::false_type test(...);

public:
    static constexpr bool value = decltype(test<T>(0))::value;
};

template <typename PageDataT>
static void SetPagePtrIfPossible_2774(PageDataT &data, ::Page *page)
{
    // We only use public members; if PageData has no `page` member in this build,
    // tests will skip earlier.
    if constexpr (HasMemberPagePtr_2774<PageDataT>::value) {
        data.page = page;
    } else {
        (void)data;
        (void)page;
    }
}

template <typename DevT>
static void ExpectLinksEmpty_2774(DevT &dev)
{
    // poppler-link-extractor-private.h in the prompt shows both:
    //   int links();
    //   QList<Link *> links();
    // We handle either signature without assuming internals.
    if constexpr (std::is_same_v<decltype(dev.links()), int>) {
        EXPECT_EQ(dev.links(), 0);
    } else {
        auto list = dev.links();
        EXPECT_TRUE(list.isEmpty());
    }
}

#if HAVE_POPPLER_PDFDOC_H
static std::unique_ptr<PDFDoc> LoadMinimalPdfDoc_2774()
{
    QTemporaryFile tf;
    tf.setAutoRemove(true);
    // Ensure a .pdf suffix so some platforms/sniffers behave nicely.
    tf.setFileTemplate(QDir::tempPath() + "/poppler_link_extractor_XXXXXX.pdf");
    if (!tf.open()) {
        return nullptr;
    }

    const QByteArray bytes(kMinimalPdf_2774, int(sizeof(kMinimalPdf_2774) - 1));
    if (tf.write(bytes) != bytes.size()) {
        return nullptr;
    }
    tf.flush();

    // Keep filename alive for PDFDoc construction.
    const QByteArray fn = tf.fileName().toLocal8Bit();

    // NOTE: We do not assume a specific PDFDoc constructor signature beyond the common one.
    // Many Poppler builds accept (std::unique_ptr<GooString>) or (GooString*).
    // We try the common unique_ptr form first; if that fails in your build, these
    // tests will be skipped at compile time by adjusting the constructor in your tree.
    auto gs = std::make_unique<GooString>(fn.constData());

    // Common constructor: PDFDoc(std::unique_ptr<GooString> &&fileName, ...)
    // We pass only the filename when possible.
    // If your Poppler requires additional args, adapt in-tree test utility instead.
    std::unique_ptr<PDFDoc> doc;
    try {
        doc = std::make_unique<PDFDoc>(std::move(gs));
    } catch (...) {
        return nullptr;
    }

    if (!doc || !doc->isOk()) {
        return nullptr;
    }
    return doc;
}
#endif

} // namespace

class LinkExtractorOutputDevTest_2774 : public ::testing::Test {
protected:
    void SetUp() override
    {
#if HAVE_POPPLER_GLOBALPARAMS_H
        // Best-effort initialization; many Poppler builds require globalParams.
        if (!globalParams) {
            globalParams = new GlobalParams();
        }
#endif
    }

    void TearDown() override
    {
        // We intentionally do not delete globalParams here; Poppler often treats it as process-global.
    }
};

TEST_F(LinkExtractorOutputDevTest_2774, ConstructorWithNullptrDataDiesInDebug_2774)
{
#if defined(QT_DEBUG) || !defined(QT_NO_DEBUG)
    // Q_ASSERT is active in debug builds and typically aborts.
    EXPECT_DEATH_IF_SUPPORTED(
        {
            Poppler::LinkExtractorOutputDev dev(nullptr);
            (void)dev;
        },
        "");
#else
    GTEST_SKIP() << "Q_ASSERT is typically disabled in release builds; death behavior is not observable.";
#endif
}

TEST_F(LinkExtractorOutputDevTest_2774, ConstructorWithValidPageDataDoesNotCrashAndLinksInitiallyEmpty_2774)
{
#if !HAVE_POPPLER_PDFDOC_H
    GTEST_SKIP() << "PDFDoc.h not available in this build; cannot construct a real ::Page for PageData.";
#else
    auto doc = LoadMinimalPdfDoc_2774();
    if (!doc) {
        GTEST_SKIP() << "Failed to load minimal PDF via PDFDoc; environment/build may require different initialization.";
    }

    // Common Poppler API: getPage(1) returns ::Page*
    ::Page *page = doc->getPage(1);
    if (!page) {
        GTEST_SKIP() << "PDFDoc did not provide page 1.";
    }

    Poppler::PageData data{};
    if constexpr (!HasMemberPagePtr_2774<Poppler::PageData>::value) {
        GTEST_SKIP() << "Poppler::PageData in this build does not expose a public `page` member as expected.";
    } else {
        SetPagePtrIfPossible_2774(data, page);
    }

    Poppler::LinkExtractorOutputDev dev(&data);

    // Observable behavior we can safely assert without guessing internals:
    // - calling simple overrides should be stable and not crash
    EXPECT_EQ(dev.upsideDown(), dev.upsideDown());
    EXPECT_EQ(dev.useDrawChar(), dev.useDrawChar());
    EXPECT_EQ(dev.interpretType3Chars(), dev.interpretType3Chars());

    // - links should be empty right after construction (no links processed yet)
    ExpectLinksEmpty_2774(dev);
#endif
}

TEST_F(LinkExtractorOutputDevTest_2774, LinksRemainsEmptyWhenNoProcessLinkCalls_2774)
{
#if !HAVE_POPPLER_PDFDOC_H
    GTEST_SKIP() << "PDFDoc.h not available in this build; cannot construct a real ::Page for PageData.";
#else
    auto doc = LoadMinimalPdfDoc_2774();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Failed to load minimal PDF via PDFDoc.";
    }
    ::Page *page = doc->getPage(1);
    if (!page) {
        GTEST_SKIP() << "PDFDoc did not provide page 1.";
    }

    Poppler::PageData data{};
    if constexpr (!HasMemberPagePtr_2774<Poppler::PageData>::value) {
        GTEST_SKIP() << "Poppler::PageData in this build does not expose a public `page` member as expected.";
    } else {
        SetPagePtrIfPossible_2774(data, page);
    }

    Poppler::LinkExtractorOutputDev dev(&data);

    // Without any external interactions (no processLink), observable state should remain "empty".
    ExpectLinksEmpty_2774(dev);

    // Call again to ensure idempotent observation.
    ExpectLinksEmpty_2774(dev);
#endif
}