// File: new-quads-from-offset-cropbox-test_2456.cc

#include <gtest/gtest.h>

#include <glib.h>
#include <memory>
#include <vector>

#include "poppler/Annot.h"
#include "poppler/PDFRectangle.h"

// The function under test is implemented in poppler-page.cc (not necessarily exposed via a header).
// Declare it here so the test can link against the existing implementation.
extern AnnotQuadrilaterals *new_quads_from_offset_cropbox(const PDFRectangle *crop_box,
                                                         AnnotQuadrilaterals *quads,
                                                         gboolean add);

namespace {

struct QuadCoords {
  double x1, y1, x2, y2, x3, y3, x4, y4;
};

static AnnotQuadrilaterals *MakeQuads(const std::vector<QuadCoords> &quads) {
  using Q = AnnotQuadrilaterals::AnnotQuadrilateral;

  const int len = static_cast<int>(quads.size());
  std::unique_ptr<Q[]> arr;
  if (len > 0) {
    arr = std::make_unique<Q[]>(len);
    for (int i = 0; i < len; ++i) {
      const auto &q = quads[i];
      arr[i] = Q(q.x1, q.y1, q.x2, q.y2, q.x3, q.y3, q.x4, q.y4);
    }
  }
  return new AnnotQuadrilaterals(std::move(arr), len);
}

static void ExpectQuadEq(const AnnotQuadrilaterals *quads, int idx, const QuadCoords &expected) {
  ASSERT_NE(quads, nullptr);
  EXPECT_DOUBLE_EQ(quads->getX1(idx), expected.x1);
  EXPECT_DOUBLE_EQ(quads->getY1(idx), expected.y1);
  EXPECT_DOUBLE_EQ(quads->getX2(idx), expected.x2);
  EXPECT_DOUBLE_EQ(quads->getY2(idx), expected.y2);
  EXPECT_DOUBLE_EQ(quads->getX3(idx), expected.x3);
  EXPECT_DOUBLE_EQ(quads->getY3(idx), expected.y3);
  EXPECT_DOUBLE_EQ(quads->getX4(idx), expected.x4);
  EXPECT_DOUBLE_EQ(quads->getY4(idx), expected.y4);
}

class NewQuadsFromOffsetCropBoxTest_2456 : public ::testing::Test {};

}  // namespace

TEST_F(NewQuadsFromOffsetCropBoxTest_2456, AddOffsetsSingleQuadrilateral_2456) {
  PDFRectangle crop;
  crop.x1 = 10.0;
  crop.y1 = 20.0;

  AnnotQuadrilaterals *in = MakeQuads({QuadCoords{1, 2, 3, 4, 5, 6, 7, 8}});
  ASSERT_NE(in, nullptr);
  ASSERT_EQ(in->getQuadrilateralsLength(), 1);

  std::unique_ptr<AnnotQuadrilaterals> out(new_quads_from_offset_cropbox(&crop, in, TRUE));
  ASSERT_NE(out, nullptr);
  EXPECT_EQ(out->getQuadrilateralsLength(), 1);

  ExpectQuadEq(out.get(), 0, QuadCoords{
                               1 + 10, 2 + 20,
                               3 + 10, 4 + 20,
                               5 + 10, 6 + 20,
                               7 + 10, 8 + 20,
                           });

  delete in;
}

TEST_F(NewQuadsFromOffsetCropBoxTest_2456, SubtractOffsetsSingleQuadrilateral_2456) {
  PDFRectangle crop;
  crop.x1 = 10.0;
  crop.y1 = 20.0;

  AnnotQuadrilaterals *in = MakeQuads({QuadCoords{1, 2, 3, 4, 5, 6, 7, 8}});
  ASSERT_NE(in, nullptr);

  std::unique_ptr<AnnotQuadrilaterals> out(new_quads_from_offset_cropbox(&crop, in, FALSE));
  ASSERT_NE(out, nullptr);
  EXPECT_EQ(out->getQuadrilateralsLength(), 1);

  ExpectQuadEq(out.get(), 0, QuadCoords{
                               1 - 10, 2 - 20,
                               3 - 10, 4 - 20,
                               5 - 10, 6 - 20,
                               7 - 10, 8 - 20,
                           });

  delete in;
}

TEST_F(NewQuadsFromOffsetCropBoxTest_2456, AddOffsetsMultipleQuadrilateralsPreservesOrder_2456) {
  PDFRectangle crop;
  crop.x1 = -3.5;
  crop.y1 = 4.25;

  AnnotQuadrilaterals *in =
      MakeQuads({QuadCoords{0, 0, 1, 1, 2, 2, 3, 3}, QuadCoords{-10, 10, -9, 11, -8, 12, -7, 13}});
  ASSERT_NE(in, nullptr);
  ASSERT_EQ(in->getQuadrilateralsLength(), 2);

  std::unique_ptr<AnnotQuadrilaterals> out(new_quads_from_offset_cropbox(&crop, in, TRUE));
  ASSERT_NE(out, nullptr);
  EXPECT_EQ(out->getQuadrilateralsLength(), 2);

  ExpectQuadEq(out.get(), 0, QuadCoords{
                               0 + (-3.5), 0 + 4.25,
                               1 + (-3.5), 1 + 4.25,
                               2 + (-3.5), 2 + 4.25,
                               3 + (-3.5), 3 + 4.25,
                           });
  ExpectQuadEq(out.get(), 1, QuadCoords{
                               -10 + (-3.5), 10 + 4.25,
                               -9 + (-3.5), 11 + 4.25,
                               -8 + (-3.5), 12 + 4.25,
                               -7 + (-3.5), 13 + 4.25,
                           });

  delete in;
}

TEST_F(NewQuadsFromOffsetCropBoxTest_2456, SubtractOffsetsWithNegativeCropBoxCoordinates_2456) {
  // Boundary-style test: negative crop box origin values.
  PDFRectangle crop;
  crop.x1 = -100.0;
  crop.y1 = -200.0;

  AnnotQuadrilaterals *in = MakeQuads({QuadCoords{1, 2, 3, 4, 5, 6, 7, 8}});
  ASSERT_NE(in, nullptr);

  std::unique_ptr<AnnotQuadrilaterals> out(new_quads_from_offset_cropbox(&crop, in, FALSE));
  ASSERT_NE(out, nullptr);
  EXPECT_EQ(out->getQuadrilateralsLength(), 1);

  // Subtracting a negative means adding its magnitude.
  ExpectQuadEq(out.get(), 0, QuadCoords{
                               1 - (-100), 2 - (-200),
                               3 - (-100), 4 - (-200),
                               5 - (-100), 6 - (-200),
                               7 - (-100), 8 - (-200),
                           });

  delete in;
}

TEST_F(NewQuadsFromOffsetCropBoxTest_2456, ZeroQuadrilateralsReturnsEmpty_2456) {
  PDFRectangle crop;
  crop.x1 = 10.0;
  crop.y1 = 20.0;

  // Boundary case: input has zero quadrilaterals.
  AnnotQuadrilaterals *in = MakeQuads({});
  ASSERT_NE(in, nullptr);
  EXPECT_EQ(in->getQuadrilateralsLength(), 0);

  std::unique_ptr<AnnotQuadrilaterals> out(new_quads_from_offset_cropbox(&crop, in, TRUE));
  ASSERT_NE(out, nullptr);
  EXPECT_EQ(out->getQuadrilateralsLength(), 0);

  delete in;
}

TEST_F(NewQuadsFromOffsetCropBoxTest_2456, AddThenSubtractWithSameCropBoxRestoresOriginal_2456) {
  // Observable behavior: composing add then subtract should restore the original coordinates.
  PDFRectangle crop;
  crop.x1 = 12.75;
  crop.y1 = -8.5;

  const std::vector<QuadCoords> original = {
      QuadCoords{1.25, 2.5, 3.75, 4.0, -5.5, 6.25, 7.125, -8.875},
      QuadCoords{-1, -2, -3, -4, -5, -6, -7, -8},
  };

  std::unique_ptr<AnnotQuadrilaterals> in(MakeQuads(original));
  ASSERT_NE(in, nullptr);
  ASSERT_EQ(in->getQuadrilateralsLength(), 2);

  std::unique_ptr<AnnotQuadrilaterals> added(new_quads_from_offset_cropbox(&crop, in.get(), TRUE));
  ASSERT_NE(added, nullptr);
  ASSERT_EQ(added->getQuadrilateralsLength(), 2);

  std::unique_ptr<AnnotQuadrilaterals> restored(
      new_quads_from_offset_cropbox(&crop, added.get(), FALSE));
  ASSERT_NE(restored, nullptr);
  ASSERT_EQ(restored->getQuadrilateralsLength(), 2);

  ExpectQuadEq(restored.get(), 0, original[0]);
  ExpectQuadEq(restored.get(), 1, original[1]);
}