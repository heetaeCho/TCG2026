// File: ImageOutputDev_test_2649.cpp

#include <gtest/gtest.h>

#include "TestProjects/poppler/utils/ImageOutputDev.h"

class ImageOutputDevTest_2649 : public ::testing::Test {};

TEST_F(ImageOutputDevTest_2649, UpsideDownReturnsTrue_2649) {
  ImageOutputDev dev;
  EXPECT_TRUE(dev.upsideDown());
}

TEST_F(ImageOutputDevTest_2649, UpsideDownIsStableAcrossMultipleCalls_2649) {
  ImageOutputDev dev;

  EXPECT_TRUE(dev.upsideDown());
  EXPECT_TRUE(dev.upsideDown());
  EXPECT_TRUE(dev.upsideDown());
}

TEST_F(ImageOutputDevTest_2649, UpsideDownDoesNotThrow_2649) {
  ImageOutputDev dev;
  EXPECT_NO_THROW({
    (void)dev.upsideDown();
  });
}

TEST_F(ImageOutputDevTest_2649, UpsideDownWorksForMultipleInstances_2649) {
  ImageOutputDev dev1;
  ImageOutputDev dev2;

  EXPECT_TRUE(dev1.upsideDown());
  EXPECT_TRUE(dev2.upsideDown());
}