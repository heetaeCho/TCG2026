// DocumentData_QByteArray_2761_test.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <QByteArray>

#include <optional>
#include <memory>

// Poppler / Qt6 private header under test
#include "poppler-private.h"

// GooString is part of poppler core
// (path may vary by build; "goo/GooString.h" is common in Poppler trees)
#include "goo/GooString.h"

using ::testing::MockFunction;
using ::testing::StrictMock;

namespace {

class DocumentDataTest_2761 : public ::testing::Test {
protected:
  static std::optional<GooString> OwnerPw(const char *s)
  {
    return s ? std::optional<GooString>(GooString(s)) : std::nullopt;
  }

  static std::optional<GooString> UserPw(const char *s)
  {
    return s ? std::optional<GooString>(GooString(s)) : std::nullopt;
  }

  static QByteArray MinimalPdfBytes()
  {
    // A tiny, commonly used "minimal PDF" payload for smoke-construction tests.
    // Intentionally not asserting parsing success (black-box); only that construction
    // and destruction are safe/observable through the public interface.
    static const char kMinimalPdf[] =
        "%PDF-1.1\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 1 1] >>\n"
        "endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000010 00000 n \n"
        "0000000060 00000 n \n"
        "0000000117 00000 n \n"
        "trailer\n"
        "<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n"
        "180\n"
        "%%EOF\n";
    return QByteArray(kMinimalPdf, static_cast<int>(sizeof(kMinimalPdf) - 1));
  }
};

TEST_F(DocumentDataTest_2761, ConstructWithEmptyData_DoesNotThrow_2761)
{
  const QByteArray empty;
  EXPECT_NO_THROW({
    Poppler::DocumentData data(empty, std::nullopt, std::nullopt);
  });
}

TEST_F(DocumentDataTest_2761, ConstructWithEmptyData_WithPasswords_DoesNotThrow_2761)
{
  const QByteArray empty;
  EXPECT_NO_THROW({
    Poppler::DocumentData data(empty, OwnerPw("owner"), UserPw("user"));
  });
}

TEST_F(DocumentDataTest_2761, ConstructWithMinimalPdf_DoesNotThrow_2761)
{
  const QByteArray pdf = MinimalPdfBytes();
  EXPECT_NO_THROW({
    Poppler::DocumentData data(pdf, std::nullopt, std::nullopt);
  });
}

TEST_F(DocumentDataTest_2761, ConstructWithMinimalPdf_WithPasswords_DoesNotThrow_2761)
{
  const QByteArray pdf = MinimalPdfBytes();
  EXPECT_NO_THROW({
    Poppler::DocumentData data(pdf, OwnerPw("owner"), UserPw("user"));
  });
}

TEST_F(DocumentDataTest_2761, NotifyXRefReconstructed_InvokesCallback_2761)
{
  Poppler::DocumentData data(MinimalPdfBytes(), std::nullopt, std::nullopt);

  StrictMock<MockFunction<void(void)>> cb;
  data.xrefReconstructedCallback = cb.AsStdFunction();

  EXPECT_CALL(cb, Call()).Times(1);
  data.notifyXRefReconstructed();
}

TEST_F(DocumentDataTest_2761, NotifyXRefReconstructed_NoCallback_DoesNotCrash_2761)
{
  Poppler::DocumentData data(MinimalPdfBytes(), std::nullopt, std::nullopt);

  // Ensure "unset" callback path is safe/observable.
  data.xrefReconstructedCallback = nullptr;

  EXPECT_NO_THROW({
    data.notifyXRefReconstructed();
  });
}

TEST_F(DocumentDataTest_2761, NotifyXRefReconstructed_CanBeCalledMultipleTimes_2761)
{
  Poppler::DocumentData data(MinimalPdfBytes(), std::nullopt, std::nullopt);

  StrictMock<MockFunction<void(void)>> cb;
  data.xrefReconstructedCallback = cb.AsStdFunction();

  EXPECT_CALL(cb, Call()).Times(2);
  data.notifyXRefReconstructed();
  data.notifyXRefReconstructed();
}

}  // namespace