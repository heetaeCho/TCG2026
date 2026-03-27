// poppler_annot_get_border_width_test_2122.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cmath>
#include <limits>
#include <memory>

// ---- Minimal GLib-compatible types/macros (test-local stubs) ----
using gboolean = int;
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

// ---- Minimal dependency stubs matching the interface the function uses ----
class AnnotBorder {
public:
  virtual ~AnnotBorder() = default;
  virtual double getWidth() const = 0;
};

class Annot {
public:
  virtual ~Annot() = default;
  virtual AnnotBorder* getBorder() = 0;
};

struct _PopplerAnnot {
  std::shared_ptr<Annot> annot;
};
using PopplerAnnot = _PopplerAnnot;

// ---- Function under test (as provided) ----
gboolean poppler_annot_get_border_width(PopplerAnnot* poppler_annot, double* width) {
  AnnotBorder* b = poppler_annot->annot->getBorder();
  if (b) {
    *width = b->getWidth();
    return TRUE;
  }
  *width = 0.;
  return FALSE;
}

// ---- Test doubles ----
class FakeAnnotBorder final : public AnnotBorder {
public:
  explicit FakeAnnotBorder(double w) : w_(w) {}
  double getWidth() const override { return w_; }

private:
  double w_;
};

class MockAnnot final : public Annot {
public:
  MOCK_METHOD(AnnotBorder*, getBorder, (), (override));
};

class PopplerAnnotGetBorderWidthTest_2122 : public ::testing::Test {
protected:
  static PopplerAnnot MakePopplerAnnotWith(const std::shared_ptr<Annot>& a) {
    PopplerAnnot pa;
    pa.annot = a;
    return pa;
  }
};

// ---- Tests ----

TEST_F(PopplerAnnotGetBorderWidthTest_2122, ReturnsTrueAndWritesWidthWhenBorderExists_2122) {
  auto mock_annot = std::make_shared<MockAnnot>();
  FakeAnnotBorder border(2.5);

  EXPECT_CALL(*mock_annot, getBorder()).Times(1).WillOnce(::testing::Return(&border));

  PopplerAnnot pa = MakePopplerAnnotWith(mock_annot);
  double out = -123.0;

  gboolean ok = poppler_annot_get_border_width(&pa, &out);

  EXPECT_EQ(ok, TRUE);
  EXPECT_DOUBLE_EQ(out, 2.5);
}

TEST_F(PopplerAnnotGetBorderWidthTest_2122, ReturnsFalseAndWritesZeroWhenBorderIsNull_2122) {
  auto mock_annot = std::make_shared<MockAnnot>();

  EXPECT_CALL(*mock_annot, getBorder()).Times(1).WillOnce(::testing::Return(nullptr));

  PopplerAnnot pa = MakePopplerAnnotWith(mock_annot);
  double out = 9.0;

  gboolean ok = poppler_annot_get_border_width(&pa, &out);

  EXPECT_EQ(ok, FALSE);
  EXPECT_DOUBLE_EQ(out, 0.0);
}

TEST_F(PopplerAnnotGetBorderWidthTest_2122, PropagatesZeroWidthBorder_2122) {
  auto mock_annot = std::make_shared<MockAnnot>();
  FakeAnnotBorder border(0.0);

  EXPECT_CALL(*mock_annot, getBorder()).Times(1).WillOnce(::testing::Return(&border));

  PopplerAnnot pa = MakePopplerAnnotWith(mock_annot);
  double out = 1.0;

  gboolean ok = poppler_annot_get_border_width(&pa, &out);

  EXPECT_EQ(ok, TRUE);
  EXPECT_DOUBLE_EQ(out, 0.0);
}

TEST_F(PopplerAnnotGetBorderWidthTest_2122, PropagatesNegativeWidthBorder_2122) {
  auto mock_annot = std::make_shared<MockAnnot>();
  FakeAnnotBorder border(-3.75);

  EXPECT_CALL(*mock_annot, getBorder()).Times(1).WillOnce(::testing::Return(&border));

  PopplerAnnot pa = MakePopplerAnnotWith(mock_annot);
  double out = 0.0;

  gboolean ok = poppler_annot_get_border_width(&pa, &out);

  EXPECT_EQ(ok, TRUE);
  EXPECT_DOUBLE_EQ(out, -3.75);
}

TEST_F(PopplerAnnotGetBorderWidthTest_2122, PropagatesVeryLargeWidthBorder_2122) {
  auto mock_annot = std::make_shared<MockAnnot>();
  const double kLarge = std::numeric_limits<double>::max();
  FakeAnnotBorder border(kLarge);

  EXPECT_CALL(*mock_annot, getBorder()).Times(1).WillOnce(::testing::Return(&border));

  PopplerAnnot pa = MakePopplerAnnotWith(mock_annot);
  double out = 0.0;

  gboolean ok = poppler_annot_get_border_width(&pa, &out);

  EXPECT_EQ(ok, TRUE);
  EXPECT_DOUBLE_EQ(out, kLarge);
}

TEST_F(PopplerAnnotGetBorderWidthTest_2122, PropagatesNaNWidthBorder_2122) {
  auto mock_annot = std::make_shared<MockAnnot>();
  const double kNaN = std::numeric_limits<double>::quiet_NaN();
  FakeAnnotBorder border(kNaN);

  EXPECT_CALL(*mock_annot, getBorder()).Times(1).WillOnce(::testing::Return(&border));

  PopplerAnnot pa = MakePopplerAnnotWith(mock_annot);
  double out = 0.0;

  gboolean ok = poppler_annot_get_border_width(&pa, &out);

  EXPECT_EQ(ok, TRUE);
  EXPECT_TRUE(std::isnan(out));
}

#if GTEST_HAS_DEATH_TEST
TEST_F(PopplerAnnotGetBorderWidthTest_2122, DeathWhenWidthPointerIsNull_2122) {
  auto mock_annot = std::make_shared<MockAnnot>();
  FakeAnnotBorder border(1.0);

  EXPECT_CALL(*mock_annot, getBorder()).Times(1).WillOnce(::testing::Return(&border));

  PopplerAnnot pa = MakePopplerAnnotWith(mock_annot);

  ASSERT_DEATH((void)poppler_annot_get_border_width(&pa, nullptr), ".*");
}

TEST_F(PopplerAnnotGetBorderWidthTest_2122, DeathWhenPopplerAnnotIsNull_2122) {
  double out = 0.0;
  ASSERT_DEATH((void)poppler_annot_get_border_width(nullptr, &out), ".*");
}
#endif