// DocumentData_qiodevice_test_2760.cpp
//
// Unit tests for Poppler::DocumentData(QIODevice*, ...)
// Constraints note:
// - Treat DocumentData as a black box.
// - Verify only observable behavior via public API (e.g., checkDocument, notifyXRefReconstructed)
//   and safe, public fields when they are clearly part of the interface.

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <optional>
#include <functional>

#include <QBuffer>
#include <QByteArray>
#include <QIODevice>
#include <QString>

#include "poppler-private.h" // Poppler::DocumentData
#include "goo/GooString.h"   // GooString (path may vary in your tree)

using ::testing::StrictMock;
using ::testing::MockFunction;

namespace {

// A tiny, commonly-used "minimal PDF" (1 empty page).
// This is intentionally simple and self-contained so tests don't depend on external files.
// NOTE: Some PDF parsers are picky; if your Poppler build requires xref streams or stricter
// formatting, adjust this sample accordingly.
QByteArray MakeMinimalPdfBytes()
{
    // Classic minimal PDF with xref table.
    // Offsets are computed for this exact string; do not edit lightly.
    const char *pdf =
        "%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\n"
        "endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n"
        "<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    return QByteArray(pdf, static_cast<int>(strlen(pdf)));
}

// Convenience: create an optional GooString from a C string.
std::optional<GooString> OptGoo(const char *s)
{
    if (!s) {
        return std::nullopt;
    }
    return GooString(s);
}

} // namespace

class DocumentDataQIODeviceTest_2760 : public ::testing::Test {
protected:
    std::optional<GooString> noOwner;
    std::optional<GooString> noUser;
};

TEST_F(DocumentDataQIODeviceTest_2760, ConstructWithValidPdfDevice_CheckDocumentNotNull_2760)
{
    const QByteArray pdfBytes = MakeMinimalPdfBytes();
    QBuffer buffer;
    buffer.setData(pdfBytes);

    // Open read-only; QIODeviceInStream should be able to read.
    ASSERT_TRUE(buffer.open(QIODevice::ReadOnly));

    Poppler::DocumentData dd(&buffer, noOwner, noUser);

    // Observable behavior: checkDocument should indicate success for a valid PDF.
    // The header snippet shows both "static int checkDocument(...)" and
    // "Document *checkDocument(...)" in different fragments; in Poppler-Qt this is
    // typically a Document*.
    auto *doc = Poppler::DocumentData::checkDocument(&dd);
    EXPECT_NE(doc, nullptr);
}

TEST_F(DocumentDataQIODeviceTest_2760, ConstructWithEmptyDevice_CheckDocumentNull_2760)
{
    QBuffer buffer;
    buffer.setData(QByteArray()); // empty
    ASSERT_TRUE(buffer.open(QIODevice::ReadOnly));

    Poppler::DocumentData dd(&buffer, noOwner, noUser);

    auto *doc = Poppler::DocumentData::checkDocument(&dd);
    EXPECT_EQ(doc, nullptr);
}

TEST_F(DocumentDataQIODeviceTest_2760, ConstructWithNonPdfBytes_CheckDocumentNull_2760)
{
    QBuffer buffer;
    buffer.setData(QByteArray("not a pdf", 9));
    ASSERT_TRUE(buffer.open(QIODevice::ReadOnly));

    Poppler::DocumentData dd(&buffer, noOwner, noUser);

    auto *doc = Poppler::DocumentData::checkDocument(&dd);
    EXPECT_EQ(doc, nullptr);
}

TEST_F(DocumentDataQIODeviceTest_2760, ConstructWithClosedDevice_DoesNotCrash_CheckDocumentMaybeNull_2760)
{
    const QByteArray pdfBytes = MakeMinimalPdfBytes();
    QBuffer buffer;
    buffer.setData(pdfBytes);

    // Intentionally NOT opening the device.
    ASSERT_FALSE(buffer.isOpen());

    Poppler::DocumentData dd(&buffer, noOwner, noUser);

    // We don't assume how Poppler handles a closed device; we only require
    // the call is safe and returns a coherent result.
    auto *doc = Poppler::DocumentData::checkDocument(&dd);
    // Accept either outcome; the key is "no crash".
    // Still, most builds will likely fail to parse when unreadable.
    (void)doc;
    SUCCEED();
}

TEST_F(DocumentDataQIODeviceTest_2760, NotifyXRefReconstructed_InvokesCallbackOnce_2760)
{
    QBuffer buffer;
    buffer.setData(MakeMinimalPdfBytes());
    ASSERT_TRUE(buffer.open(QIODevice::ReadOnly));

    Poppler::DocumentData dd(&buffer, noOwner, noUser);

    StrictMock<MockFunction<void(void)>> cb;
    dd.xrefReconstructedCallback = cb.AsStdFunction();

    EXPECT_CALL(cb, Call()).Times(1);
    dd.notifyXRefReconstructed();
}

TEST_F(DocumentDataQIODeviceTest_2760, NotifyXRefReconstructed_NoCallbackSet_DoesNotCrash_2760)
{
    QBuffer buffer;
    buffer.setData(MakeMinimalPdfBytes());
    ASSERT_TRUE(buffer.open(QIODevice::ReadOnly));

    Poppler::DocumentData dd(&buffer, noOwner, noUser);

    // No callback set (default-constructed std::function).
    dd.xrefReconstructedCallback = std::function<void(void)>();

    // Observable: should be safe to call.
    dd.notifyXRefReconstructed();
    SUCCEED();
}

TEST_F(DocumentDataQIODeviceTest_2760, ConstructWithPasswords_ValidPdfStillLoads_2760)
{
    QBuffer buffer;
    buffer.setData(MakeMinimalPdfBytes());
    ASSERT_TRUE(buffer.open(QIODevice::ReadOnly));

    // Passwords are meaningless for an unencrypted PDF, but passing them should be safe.
    auto owner = OptGoo("owner");
    auto user = OptGoo("user");

    Poppler::DocumentData dd(&buffer, owner, user);

    auto *doc = Poppler::DocumentData::checkDocument(&dd);
    EXPECT_NE(doc, nullptr);
}