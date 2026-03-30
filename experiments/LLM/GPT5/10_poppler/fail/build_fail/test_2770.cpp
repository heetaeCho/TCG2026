// DocumentData_ctor_test_2770.cpp
//
// Unit tests for Poppler::DocumentData (Qt5) constructor path-based overload.
//
// Constraints honored:
// - Treat implementation as black box (no internal-state inspection).
// - Test only observable behavior: construction/destruction should not throw/crash
//   for representative normal/boundary/error inputs.
// - No mocking of internal collaborators.

#include <gtest/gtest.h>

#include <QtCore/QByteArray>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QTemporaryDir>
#include <QtCore/QString>

#include <optional>
#include <string>

// Poppler / GooString
#include "GooString.h"

// Class under test (Qt5)
#include "poppler-private.h"

namespace {

// Builds a small, structurally valid PDF with correct xref offsets.
// This is just test data generation (not re-implementing Poppler logic).
static bool WriteMinimalPdfToFile(const QString &filePath)
{
    struct Obj {
        std::string s;
        size_t offset = 0;
    };

    std::string out;
    out.reserve(2048);

    out += "%PDF-1.4\n";

    Obj o1;
    o1.s =
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n";

    Obj o2;
    o2.s =
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n";

    Obj o3;
    o3.s =
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 4 0 R >>\n"
        "endobj\n";

    const std::string streamData = "BT /F1 24 Tf 72 120 Td (Hi) Tj ET\n";
    Obj o4;
    o4.s =
        "4 0 obj\n"
        "<< /Length " + std::to_string(streamData.size()) + " >>\n"
        "stream\n" + streamData +
        "endstream\n"
        "endobj\n";

    Obj objs[4] = {o1, o2, o3, o4};

    // Record offsets and append objects.
    for (auto &obj : objs) {
        obj.offset = out.size();
        out += obj.s;
    }

    const size_t xrefOffset = out.size();

    // xref table: 0..4 (5 entries). Entry 0 is the free object.
    auto pad10 = [](size_t v) {
        std::string n = std::to_string(v);
        if (n.size() < 10) n = std::string(10 - n.size(), '0') + n;
        return n;
    };

    out += "xref\n";
    out += "0 5\n";
    out += "0000000000 65535 f \n";
    out += pad10(objs[0].offset) + " 00000 n \n";
    out += pad10(objs[1].offset) + " 00000 n \n";
    out += pad10(objs[2].offset) + " 00000 n \n";
    out += pad10(objs[3].offset) + " 00000 n \n";

    out += "trailer\n";
    out += "<< /Size 5 /Root 1 0 R >>\n";
    out += "startxref\n";
    out += std::to_string(xrefOffset) + "\n";
    out += "%%EOF\n";

    QFile f(filePath);
    if (!f.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        return false;
    }
    const QByteArray bytes(out.data(), static_cast<int>(out.size()));
    const auto written = f.write(bytes);
    f.close();
    return written == bytes.size();
}

static std::optional<GooString> MakeOptGooString(const char *s)
{
    return std::optional<GooString>(GooString(s));
}

} // namespace

class DocumentDataTest_2770 : public ::testing::Test {
protected:
    QTemporaryDir dir;
};

TEST_F(DocumentDataTest_2770, ConstructWithValidMinimalPdf_NoThrow_2770)
{
    ASSERT_TRUE(dir.isValid());
    const QString pdfPath = dir.path() + QDir::separator() + "minimal.pdf";
    ASSERT_TRUE(WriteMinimalPdfToFile(pdfPath));

    const std::optional<GooString> owner = std::nullopt;
    const std::optional<GooString> user = std::nullopt;

    EXPECT_NO_THROW({
        Poppler::DocumentData data(pdfPath, owner, user);
        (void)data;
    });
}

TEST_F(DocumentDataTest_2770, ConstructWithNonexistentFilePath_NoThrow_2770)
{
    ASSERT_TRUE(dir.isValid());
    const QString missingPath = dir.path() + QDir::separator() + "does_not_exist.pdf";

    const std::optional<GooString> owner = std::nullopt;
    const std::optional<GooString> user = std::nullopt;

    // Error/boundary case: missing file. Observable expectation: should not crash/throw.
    EXPECT_NO_THROW({
        Poppler::DocumentData data(missingPath, owner, user);
        (void)data;
    });
}

TEST_F(DocumentDataTest_2770, ConstructWithEmptyFilePath_NoThrow_2770)
{
    const std::optional<GooString> owner = std::nullopt;
    const std::optional<GooString> user = std::nullopt;

    // Boundary: empty path string.
    EXPECT_NO_THROW({
        Poppler::DocumentData data(QString(), owner, user);
        (void)data;
    });
}

TEST_F(DocumentDataTest_2770, ConstructWithPasswordsProvided_NoThrow_2770)
{
    ASSERT_TRUE(dir.isValid());
    const QString pdfPath = dir.path() + QDir::separator() + "minimal_with_pw.pdf";
    ASSERT_TRUE(WriteMinimalPdfToFile(pdfPath));

    // Note: We are not asserting password correctness/locking behavior because it is not
    // observable via the provided interface snippet. We only verify construction is robust.
    const std::optional<GooString> owner = MakeOptGooString("owner-pass");
    const std::optional<GooString> user = MakeOptGooString("user-pass");

    EXPECT_NO_THROW({
        Poppler::DocumentData data(pdfPath, owner, user);
        (void)data;
    });
}

TEST_F(DocumentDataTest_2770, ConstructMultipleInstancesDifferentPaths_NoThrow_2770)
{
    ASSERT_TRUE(dir.isValid());

    const QString pdfPath1 = dir.path() + QDir::separator() + "a.pdf";
    const QString pdfPath2 = dir.path() + QDir::separator() + "b.pdf";
    ASSERT_TRUE(WriteMinimalPdfToFile(pdfPath1));
    ASSERT_TRUE(WriteMinimalPdfToFile(pdfPath2));

    const std::optional<GooString> none = std::nullopt;

    EXPECT_NO_THROW({
        Poppler::DocumentData d1(pdfPath1, none, none);
        Poppler::DocumentData d2(pdfPath2, none, none);
        (void)d1;
        (void)d2;
    });
}