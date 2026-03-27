// DocumentDataTest_2759.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <type_traits>
#include <optional>

#include <QTemporaryFile>
#include <QFile>
#include <QColor>
#include <QString>

#include "poppler-private.h"

using ::testing::MockFunction;

namespace {

class DocumentDataTest_2759 : public ::testing::Test {
protected:
    static QString MakeTempFilePathWithContents(const QByteArray &bytes)
    {
        QTemporaryFile tmp;
        // Ensure it has a stable path we can pass to DocumentData.
        tmp.setAutoRemove(false);
        EXPECT_TRUE(tmp.open());
        EXPECT_GE(tmp.write(bytes), 0);
        tmp.flush();
        const QString path = tmp.fileName();
        tmp.close();
        return path;
    }
};

} // namespace

// Compile-time boundary: copy/assign are deleted (observable via type traits).
TEST(DocumentDataCompileTimeTest_2759, IsNotCopyableOrAssignable_2759)
{
    static_assert(!std::is_copy_constructible_v<Poppler::DocumentData>,
                  "Poppler::DocumentData must not be copy-constructible");
    static_assert(!std::is_copy_assignable_v<Poppler::DocumentData>,
                  "Poppler::DocumentData must not be copy-assignable");
}

// Normal operation: construction from a file path stores the path and creates a doc object.
TEST_F(DocumentDataTest_2759, CtorFromFilePathStoresPathAndCreatesDoc_2759)
{
    const QString path = MakeTempFilePathWithContents(QByteArray("%PDF-1.4\n%EOF\n"));

    Poppler::DocumentData data(path, std::nullopt, std::nullopt);

    // Based on the provided implementation snippet: m_filePath is set from filePath.
    EXPECT_EQ(data.m_filePath, path);

    // Also based on the snippet: doc is created with std::make_unique<PDFDoc>(...).
    // We only assert non-null (no assumptions about validity of the PDF content).
    ASSERT_NE(data.doc, nullptr);
}

// Boundary / error-ish: non-existent path should still be stored and should not prevent object creation.
TEST_F(DocumentDataTest_2759, CtorFromNonexistentPathStillStoresPath_2759)
{
    const QString bogusPath = QStringLiteral("this_file_should_not_exist_2759.pdf");

    Poppler::DocumentData data(bogusPath, std::nullopt, std::nullopt);

    EXPECT_EQ(data.m_filePath, bogusPath);
    ASSERT_NE(data.doc, nullptr);
}

// External interaction: notifyXRefReconstructed invokes the configured callback (if any).
TEST_F(DocumentDataTest_2759, NotifyXRefReconstructedInvokesCallback_2759)
{
    const QString path = MakeTempFilePathWithContents(QByteArray("%PDF-1.4\n%EOF\n"));
    Poppler::DocumentData data(path, std::nullopt, std::nullopt);

    MockFunction<void(void)> cb;
    data.xrefReconstructedCallback = cb.AsStdFunction();

    EXPECT_CALL(cb, Call()).Times(1);
    data.notifyXRefReconstructed();
}

// Boundary: notifyXRefReconstructed with no callback set should be safe (no crash).
TEST_F(DocumentDataTest_2759, NotifyXRefReconstructedWithoutCallbackIsSafe_2759)
{
    const QString path = MakeTempFilePathWithContents(QByteArray("%PDF-1.4\n%EOF\n"));
    Poppler::DocumentData data(path, std::nullopt, std::nullopt);

    data.xrefReconstructedCallback = nullptr;

    // Observable requirement: should not crash / throw.
    EXPECT_NO_THROW(data.notifyXRefReconstructed());
}

// Normal operation: setPaperColor updates the exposed paperColor state.
TEST_F(DocumentDataTest_2759, SetPaperColorUpdatesPaperColor_2759)
{
    const QString path = MakeTempFilePathWithContents(QByteArray("%PDF-1.4\n%EOF\n"));
    Poppler::DocumentData data(path, std::nullopt, std::nullopt);

    const QColor c1 = QColor::fromRgb(10, 20, 30);
    const QColor c2 = QColor::fromRgb(200, 150, 100);

    data.setPaperColor(c1);
    EXPECT_EQ(data.paperColor, c1);

    data.setPaperColor(c2);
    EXPECT_EQ(data.paperColor, c2);
}

// Boundary: fillMembers() should be callable repeatedly (black-box safety / idempotence expectation).
TEST_F(DocumentDataTest_2759, FillMembersIsCallableMultipleTimes_2759)
{
    const QString path = MakeTempFilePathWithContents(QByteArray("%PDF-1.4\n%EOF\n"));
    Poppler::DocumentData data(path, std::nullopt, std::nullopt);

    EXPECT_NO_THROW(data.fillMembers());
    EXPECT_NO_THROW(data.fillMembers());
}