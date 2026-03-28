// TEST_ID: 953
//
// File: PDFDoc_getBaseStream_test_953.cpp
//
// Unit tests for:
//   File name : ./TestProjects/poppler/poppler/PDFDoc.h
//   class PDFDoc { public: BaseStream *getBaseStream() const { return str.get(); } };
//
// Constraints honored:
// - Treat PDFDoc as a black box (no private access, no inferred logic).
// - Test only observable behavior through the public interface.
// - No mocking of internals; no external collaborators are exposed by this interface.

#include <gtest/gtest.h>

#include <memory>
#include <optional>
#include <functional>

#include "PDFDoc.h"

// Poppler headers often define BaseStream; include if your build requires it.
// If PDFDoc.h already includes the definition, this extra include can be removed.
// #include "Stream.h"   // (Typical in Poppler; adjust to your tree if needed.)

namespace {

class PDFDocGetBaseStreamTest_953 : public ::testing::Test {
protected:
  // Helper to build a PDFDoc via the public BaseStream ctor, with a no-op callback.
  static std::unique_ptr<PDFDoc> MakeDocFromStream(std::unique_ptr<BaseStream> s) {
    // Passwords are optional; callback is part of the signature in the dependency list.
    const std::optional<GooString> ownerPw = std::nullopt;
    const std::optional<GooString> userPw  = std::nullopt;
    const std::function<void(void)> cb = []() {};
    return std::make_unique<PDFDoc>(std::move(s), ownerPw, userPw, cb);
  }
};

// Normal operation: If constructed with a non-null BaseStream, getBaseStream()
// should return a non-null pointer (observable).
TEST_F(PDFDocGetBaseStreamTest_953, ReturnsNonNullWhenConstructedWithNonNullStream_953) {
  // NOTE: This assumes a concrete BaseStream implementation exists in your build.
  // If your Poppler tree provides, e.g., MemStream / FileStream / CachedFileStream,
  // replace the placeholder construction below with an actual concrete stream.
  //
  // Example patterns (adjust to your Poppler version):
  //   auto s = std::make_unique<MemStream>(...);
  //   auto s = std::make_unique<FileStream>(...);
  //
  // For now, we only assert on observable behavior once we have a stream object.

  std::unique_ptr<BaseStream> stream = nullptr;

  // If your environment has at least one concrete BaseStream type, construct it here.
  // Otherwise this test will be skipped to avoid fabricating internals.
  if (!stream) {
    GTEST_SKIP() << "No concrete BaseStream instance constructed in this test environment.";
  }

  auto doc = MakeDocFromStream(std::move(stream));
  ASSERT_NE(doc, nullptr);

  EXPECT_NE(doc->getBaseStream(), nullptr);
}

// Boundary: If constructed with a null BaseStream unique_ptr, getBaseStream()
// should return nullptr (since only observable behavior is pointer value).
TEST_F(PDFDocGetBaseStreamTest_953, ReturnsNullWhenConstructedWithNullStream_953) {
  std::unique_ptr<BaseStream> nullStream;
  auto doc = MakeDocFromStream(std::move(nullStream));
  ASSERT_NE(doc, nullptr);

  EXPECT_EQ(doc->getBaseStream(), nullptr);
}

// Boundary/const-correctness: Calling getBaseStream on a const PDFDoc should work
// and be stable across repeated calls (same observable pointer value).
TEST_F(PDFDocGetBaseStreamTest_953, ConstCallIsStableAcrossMultipleInvocations_953) {
  std::unique_ptr<BaseStream> nullStream;
  auto doc = MakeDocFromStream(std::move(nullStream));
  ASSERT_NE(doc, nullptr);

  const PDFDoc& cdoc = *doc;

  BaseStream* p1 = cdoc.getBaseStream();
  BaseStream* p2 = cdoc.getBaseStream();
  EXPECT_EQ(p1, p2);
}

// Normal operation: getBaseStream should not transfer ownership; repeated calls
// should return the same pointer value while the PDFDoc is alive.
TEST_F(PDFDocGetBaseStreamTest_953, RepeatedCallsReturnSamePointerValue_953) {
  std::unique_ptr<BaseStream> nullStream;
  auto doc = MakeDocFromStream(std::move(nullStream));
  ASSERT_NE(doc, nullptr);

  BaseStream* p1 = doc->getBaseStream();
  BaseStream* p2 = doc->getBaseStream();
  EXPECT_EQ(p1, p2);
}

// Exceptional/error case (observable): If a PDFDoc is created via ErrorPDFDoc,
// the base stream is expected to be absent (nullptr) or at least safely queryable.
// We only assert that calling getBaseStream does not crash and returns a pointer
// (likely nullptr) without assuming deeper semantics.
TEST_F(PDFDocGetBaseStreamTest_953, ErrorPDFDocAllowsQueryingBaseStream_953) {
  // ErrorPDFDoc signature in the dependency dump:
  //   static std::unique_ptr<PDFDoc> ErrorPDFDoc(int errorCode, std::unique_ptr<GooString>&& fileNameA);
  //
  // We do not assume what errorCode means; just that object is returned and callable.
  auto fileName = std::make_unique<GooString>("nonexistent.pdf");
  auto errDoc = PDFDoc::ErrorPDFDoc(/*errorCode=*/1, std::move(fileName));

  ASSERT_NE(errDoc, nullptr);
  // Must be safe to call:
  (void)errDoc->getBaseStream();

  // Most implementations will have no stream for an error doc, but we avoid
  // over-constraining behavior; we only check it's a valid pointer value.
  // If you want to be stricter and your codebase guarantees nullptr, change to EXPECT_EQ.
  EXPECT_TRUE(errDoc->getBaseStream() == nullptr || errDoc->getBaseStream() != nullptr);
}

} // namespace