// File: test_value_datavalue_tofloat_801.cpp
#include <gtest/gtest.h>

#include <cmath>
#include <limits>
#include <stdexcept>

#include "exiv2/value.hpp"

namespace {

// Helper: create a DataValue with a "safe" TypeId without depending on specific enum constants.
static Exiv2::TypeId AnyTypeId() {
  return static_cast<Exiv2::TypeId>(0);
}

class DataValueToFloatTest_801 : public ::testing::Test {
 protected:
  Exiv2::DataValue MakeWithValues(std::initializer_list<float> vals) {
    Exiv2::DataValue dv(AnyTypeId());
    dv.value_.clear();
    for (float v : vals) dv.value_.push_back(v);
    return dv;
  }
};

}  // namespace

TEST_F(DataValueToFloatTest_801, ReturnsFirstElement_801) {
  auto dv = MakeWithValues({1.25f, 2.5f});

  const float out0 = dv.toFloat(0);

  EXPECT_FLOAT_EQ(out0, 1.25f);
  EXPECT_TRUE(dv.ok());
}

TEST_F(DataValueToFloatTest_801, ReturnsSecondElement_801) {
  auto dv = MakeWithValues({-3.0f, 4.75f});

  const float out1 = dv.toFloat(1);

  EXPECT_FLOAT_EQ(out1, 4.75f);
  EXPECT_TRUE(dv.ok());
}

TEST_F(DataValueToFloatTest_801, Boundary_LastValidIndexReturnsValue_801) {
  auto dv = MakeWithValues({10.0f, 20.0f, 30.0f});

  const float last = dv.toFloat(2);

  EXPECT_FLOAT_EQ(last, 30.0f);
  EXPECT_TRUE(dv.ok());
}

TEST_F(DataValueToFloatTest_801, OutOfRangeIndexThrowsStdOutOfRange_801) {
  auto dv = MakeWithValues({1.0f});

  EXPECT_THROW((void)dv.toFloat(1), std::out_of_range);
}

TEST_F(DataValueToFloatTest_801, EmptyValueThrowsStdOutOfRange_801) {
  auto dv = MakeWithValues({});

  EXPECT_THROW((void)dv.toFloat(0), std::out_of_range);
}

TEST_F(DataValueToFloatTest_801, AfterOutOfRangeExceptionOkIsStillObservable_801) {
  auto dv = MakeWithValues({42.0f});

  try {
    (void)dv.toFloat(999);
    FAIL() << "Expected std::out_of_range";
  } catch (const std::out_of_range&) {
    // Observable state through the public interface.
    EXPECT_TRUE(dv.ok());
  } catch (...) {
    FAIL() << "Expected std::out_of_range";
  }
}

TEST_F(DataValueToFloatTest_801, HandlesNaNAndInfinityValues_801) {
  const float nanv = std::numeric_limits<float>::quiet_NaN();
  const float infv = std::numeric_limits<float>::infinity();

  auto dv = MakeWithValues({nanv, infv});

  const float out_nan = dv.toFloat(0);
  const float out_inf = dv.toFloat(1);

  EXPECT_TRUE(std::isnan(out_nan));
  EXPECT_TRUE(std::isinf(out_inf));
  EXPECT_TRUE(dv.ok());
}