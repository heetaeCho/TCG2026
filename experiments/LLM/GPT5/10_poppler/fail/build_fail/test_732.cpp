// TEST_ID: 732
// File: AnnotStampImageHelper_test_732.cpp
//
// Unit tests for AnnotStampImageHelper (Poppler)
// Constraints followed:
// - Treat implementation as black box
// - Use only public interface
// - No private state access
// - Include normal/boundary/error/interaction where observable
//
// Note: This header depends on Poppler types (PDFDoc, Ref, ColorSpace, Object).
// These tests are written to compile in Poppler's test environment where those
// headers/types are available.

#include <gtest/gtest.h>

#include <climits>
#include <memory>
#include <vector>

#include "poppler/AnnotStampImageHelper.h"

// Include Poppler headers for types used by the interface.
// Adjust include paths if your build system exposes them differently.
#include "poppler/PDFDoc.h"
#include "poppler/Object.h"
#include "poppler/GlobalParams.h"  // often required to init Poppler in tests
#include "poppler/GooString.h"
#include "poppler/ColorSpace.h"

// A small helper fixture. We avoid assuming how PDFDoc is constructed in your
// tree; many Poppler test setups already provide a PDFDoc factory.
// If your project already has a standard test PDFDoc creator, swap it in here.
class AnnotStampImageHelperTest_732 : public ::testing::Test {
protected:
  // If a real PDFDoc is required by the implementation, you should replace this
  // with your project's standard way to create/open a minimal doc.
  PDFDoc* doc() const { return doc_.get(); }

  void SetUp() override {
    // Many Poppler builds require globalParams to be initialized for PDFDoc.
    // If your environment already does this, it should still be safe.
    if (!globalParams) {
      globalParams = std::make_unique<GlobalParams>().release();
    }

    // Create a PDFDoc in the least-assumptive way possible.
    // Some builds allow a null doc pointer; some don't.
    // We keep doc_ null here and structure tests so they can be disabled
    // easily if your implementation requires a real document.
    doc_.reset(nullptr);
  }

  void TearDown() override {
    // Keep globalParams alive; Poppler sometimes expects it to outlive docs.
  }

  std::unique_ptr<PDFDoc> doc_;
};

// ----------- Tests focused on observable getters (width/height) ------------

// Normal operation: width getter returns the width passed to ctor (observable).
TEST_F(AnnotStampImageHelperTest_732, GetWidthReturnsCtorWidth_732) {
  const int width = 10;
  const int height = 12;
  const int bpc = 8;

  std::vector<char> data(static_cast<size_t>(width * height * 3), 0x2A);

  // Choose a common colorspace. DeviceRGB is widely available.
  // (We do not infer internal behavior; we only need a value to pass.)
  ColorSpace cs = ColorSpace::DeviceRGB;

  // If your implementation requires a non-null PDFDoc, replace doc() with a real one.
  AnnotStampImageHelper helper(doc(), width, height, cs, bpc, data.data(),
                               static_cast<int>(data.size()));

  EXPECT_EQ(helper.getWidth(), width);
}

// Normal operation: height getter returns ctor height (observable).
TEST_F(AnnotStampImageHelperTest_732, GetHeightReturnsCtorHeight_732) {
  const int width = 7;
  const int height = 9;
  const int bpc = 8;

  std::vector<char> data(static_cast<size_t>(width * height * 3), 0);

  ColorSpace cs = ColorSpace::DeviceRGB;

  AnnotStampImageHelper helper(doc(), width, height, cs, bpc, data.data(),
                               static_cast<int>(data.size()));

  EXPECT_EQ(helper.getHeight(), height);
}

// Boundary condition: width = 0 should be observable through getWidth().
// We don't assume whether ctor accepts it; we only assert observable behavior if constructed.
TEST_F(AnnotStampImageHelperTest_732, ZeroWidthObservable_732) {
  const int width = 0;
  const int height = 5;
  const int bpc = 8;

  std::vector<char> data(static_cast<size_t>(height * 3), 0);

  ColorSpace cs = ColorSpace::DeviceRGB;

  AnnotStampImageHelper helper(doc(), width, height, cs, bpc, data.data(),
                               static_cast<int>(data.size()));

  EXPECT_EQ(helper.getWidth(), 0);
  EXPECT_EQ(helper.getHeight(), height);
}

// Boundary condition: height = 0 observable via getHeight().
TEST_F(AnnotStampImageHelperTest_732, ZeroHeightObservable_732) {
  const int width = 5;
  const int height = 0;
  const int bpc = 8;

  std::vector<char> data(static_cast<size_t>(width * 3), 0);

  ColorSpace cs = ColorSpace::DeviceRGB;

  AnnotStampImageHelper helper(doc(), width, height, cs, bpc, data.data(),
                               static_cast<int>(data.size()));

  EXPECT_EQ(helper.getWidth(), width);
  EXPECT_EQ(helper.getHeight(), 0);
}

// Boundary condition: 1x1 image (smallest typical non-zero dimensions).
TEST_F(AnnotStampImageHelperTest_732, OneByOneImageObservable_732) {
  const int width = 1;
  const int height = 1;
  const int bpc = 8;

  std::vector<char> data(3, 0x7F);  // RGB pixel

  ColorSpace cs = ColorSpace::DeviceRGB;

  AnnotStampImageHelper helper(doc(), width, height, cs, bpc, data.data(),
                               static_cast<int>(data.size()));

  EXPECT_EQ(helper.getWidth(), 1);
  EXPECT_EQ(helper.getHeight(), 1);
}

// ----------------- Tests for Ref / soft mask constructor -------------------

// Normal operation: getRef() is stable across multiple calls.
TEST_F(AnnotStampImageHelperTest_732, GetRefIsStableAcrossCalls_732) {
  const int width = 3;
  const int height = 2;
  const int bpc = 8;

  std::vector<char> data(static_cast<size_t>(width * height * 3), 0x11);

  ColorSpace cs = ColorSpace::DeviceRGB;

  AnnotStampImageHelper helper(doc(), width, height, cs, bpc, data.data(),
                               static_cast<int>(data.size()));

  const Ref r1 = helper.getRef();
  const Ref r2 = helper.getRef();

  // We don't assume what the Ref contains, only that repeated calls return the same Ref.
  EXPECT_EQ(r1.num, r2.num);
  EXPECT_EQ(r1.gen, r2.gen);
}

// Normal operation: constructor that accepts a soft mask Ref still exposes width/height.
TEST_F(AnnotStampImageHelperTest_732, CtorWithSoftMaskRefKeepsDimensions_732) {
  const int width = 8;
  const int height = 6;
  const int bpc = 8;

  std::vector<char> data(static_cast<size_t>(width * height * 3), 0x22);

  ColorSpace cs = ColorSpace::DeviceRGB;

  Ref softMask{};
  softMask.num = 123;
  softMask.gen = 0;

  AnnotStampImageHelper helper(doc(), width, height, cs, bpc, data.data(),
                               static_cast<int>(data.size()), softMask);

  EXPECT_EQ(helper.getWidth(), width);
  EXPECT_EQ(helper.getHeight(), height);
}

// ----------------- Exceptional / error cases (observable) ------------------
//
// We cannot assume specific exception types or error signaling mechanisms.
// If your build uses exceptions, enable these as appropriate.
// If it signals errors by returning invalid Refs or similar, adapt checks accordingly.

// If dataLength is 0, construction may be rejected or may succeed (implementation-defined).
// We only check that, if it succeeds, getters are still consistent and no crash occurs.
TEST_F(AnnotStampImageHelperTest_732, ZeroDataLengthDoesNotBreakGettersIfConstructed_732) {
  const int width = 4;
  const int height = 4;
  const int bpc = 8;

  // Provide non-null pointer but zero length to separate "null data" from "empty data".
  char dummy = 0;

  ColorSpace cs = ColorSpace::DeviceRGB;

  AnnotStampImageHelper helper(doc(), width, height, cs, bpc, &dummy, 0);

  EXPECT_EQ(helper.getWidth(), width);
  EXPECT_EQ(helper.getHeight(), height);
}

// ----------------- External interaction verification (observable) ----------
//
// The only externally observable interaction exposed by the interface is
// removeAnnotStampImageObject(). We cannot directly observe side effects without
// the PDFDoc/Object APIs, but we can verify it is callable and is idempotent
// from the public interface perspective (no crash; getters stable).

TEST_F(AnnotStampImageHelperTest_732, RemoveAnnotStampImageObjectIsCallableAndKeepsGetters_732) {
  const int width = 5;
  const int height = 3;
  const int bpc = 8;

  std::vector<char> data(static_cast<size_t>(width * height * 3), 0x33);

  ColorSpace cs = ColorSpace::DeviceRGB;

  AnnotStampImageHelper helper(doc(), width, height, cs, bpc, data.data(),
                               static_cast<int>(data.size()));

  const int w_before = helper.getWidth();
  const int h_before = helper.getHeight();
  const Ref ref_before = helper.getRef();

  // Call removal once
  helper.removeAnnotStampImageObject();

  // Call removal again (idempotence-like behavior from interface standpoint)
  helper.removeAnnotStampImageObject();

  // From the public interface, width/height should remain consistent.
  EXPECT_EQ(helper.getWidth(), w_before);
  EXPECT_EQ(helper.getHeight(), h_before);

  // Ref stability is the only other observable. If implementation invalidates it,
  // this assertion may be too strict; remove/adjust if your semantics differ.
  const Ref ref_after = helper.getRef();
  EXPECT_EQ(ref_after.num, ref_before.num);
  EXPECT_EQ(ref_after.gen, ref_before.gen);
}