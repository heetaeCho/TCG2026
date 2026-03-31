#include <gtest/gtest.h>
#include "Annot.h"

// Test fixture for AnnotPath
class AnnotPathTest_736 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default constructor creates an empty path
TEST_F(AnnotPathTest_736, DefaultConstructorCreatesEmptyPath_736) {
    AnnotPath path;
    EXPECT_EQ(path.getCoordsLength(), 0);
}

// Test that getCoordsLength returns 0 for default constructed path
TEST_F(AnnotPathTest_736, GetCoordsLengthReturnsZeroForDefault_736) {
    AnnotPath path;
    int length = path.getCoordsLength();
    EXPECT_GE(length, 0);
    EXPECT_EQ(length, 0);
}

// Test constructor with vector of AnnotCoord
TEST_F(AnnotPathTest_736, ConstructorWithVectorOfCoords_736) {
    std::vector<AnnotCoord> coords;
    coords.emplace_back(1.0, 2.0);
    coords.emplace_back(3.0, 4.0);
    coords.emplace_back(5.0, 6.0);

    AnnotPath path(std::move(coords));
    EXPECT_EQ(path.getCoordsLength(), 3);
}

// Test constructor with empty vector
TEST_F(AnnotPathTest_736, ConstructorWithEmptyVector_736) {
    std::vector<AnnotCoord> coords;
    AnnotPath path(std::move(coords));
    EXPECT_EQ(path.getCoordsLength(), 0);
}

// Test constructor with single coordinate
TEST_F(AnnotPathTest_736, ConstructorWithSingleCoord_736) {
    std::vector<AnnotCoord> coords;
    coords.emplace_back(10.0, 20.0);

    AnnotPath path(std::move(coords));
    EXPECT_EQ(path.getCoordsLength(), 1);
}

// Test getX and getY for valid coordinates
TEST_F(AnnotPathTest_736, GetXAndGetYReturnCorrectValues_736) {
    std::vector<AnnotCoord> coords;
    coords.emplace_back(1.5, 2.5);
    coords.emplace_back(3.5, 4.5);

    AnnotPath path(std::move(coords));
    EXPECT_EQ(path.getCoordsLength(), 2);
    EXPECT_DOUBLE_EQ(path.getX(0), 1.5);
    EXPECT_DOUBLE_EQ(path.getY(0), 2.5);
    EXPECT_DOUBLE_EQ(path.getX(1), 3.5);
    EXPECT_DOUBLE_EQ(path.getY(1), 4.5);
}

// Test getX and getY with first element
TEST_F(AnnotPathTest_736, GetXYFirstElement_736) {
    std::vector<AnnotCoord> coords;
    coords.emplace_back(100.0, 200.0);
    coords.emplace_back(300.0, 400.0);
    coords.emplace_back(500.0, 600.0);

    AnnotPath path(std::move(coords));
    EXPECT_DOUBLE_EQ(path.getX(0), 100.0);
    EXPECT_DOUBLE_EQ(path.getY(0), 200.0);
}

// Test getX and getY with last element
TEST_F(AnnotPathTest_736, GetXYLastElement_736) {
    std::vector<AnnotCoord> coords;
    coords.emplace_back(100.0, 200.0);
    coords.emplace_back(300.0, 400.0);
    coords.emplace_back(500.0, 600.0);

    AnnotPath path(std::move(coords));
    EXPECT_DOUBLE_EQ(path.getX(2), 500.0);
    EXPECT_DOUBLE_EQ(path.getY(2), 600.0);
}

// Test with negative coordinates
TEST_F(AnnotPathTest_736, NegativeCoordinates_736) {
    std::vector<AnnotCoord> coords;
    coords.emplace_back(-1.0, -2.0);
    coords.emplace_back(-3.0, -4.0);

    AnnotPath path(std::move(coords));
    EXPECT_EQ(path.getCoordsLength(), 2);
    EXPECT_DOUBLE_EQ(path.getX(0), -1.0);
    EXPECT_DOUBLE_EQ(path.getY(0), -2.0);
}

// Test with zero coordinates
TEST_F(AnnotPathTest_736, ZeroCoordinates_736) {
    std::vector<AnnotCoord> coords;
    coords.emplace_back(0.0, 0.0);

    AnnotPath path(std::move(coords));
    EXPECT_EQ(path.getCoordsLength(), 1);
    EXPECT_DOUBLE_EQ(path.getX(0), 0.0);
    EXPECT_DOUBLE_EQ(path.getY(0), 0.0);
}

// Test with large number of coordinates
TEST_F(AnnotPathTest_736, LargeNumberOfCoordinates_736) {
    std::vector<AnnotCoord> coords;
    const int numCoords = 1000;
    for (int i = 0; i < numCoords; ++i) {
        coords.emplace_back(static_cast<double>(i), static_cast<double>(i * 2));
    }

    AnnotPath path(std::move(coords));
    EXPECT_EQ(path.getCoordsLength(), numCoords);
    EXPECT_DOUBLE_EQ(path.getX(0), 0.0);
    EXPECT_DOUBLE_EQ(path.getY(0), 0.0);
    EXPECT_DOUBLE_EQ(path.getX(999), 999.0);
    EXPECT_DOUBLE_EQ(path.getY(999), 1998.0);
}

// Test with very small double values
TEST_F(AnnotPathTest_736, VerySmallDoubleValues_736) {
    std::vector<AnnotCoord> coords;
    coords.emplace_back(1e-15, 2e-15);

    AnnotPath path(std::move(coords));
    EXPECT_EQ(path.getCoordsLength(), 1);
    EXPECT_DOUBLE_EQ(path.getX(0), 1e-15);
    EXPECT_DOUBLE_EQ(path.getY(0), 2e-15);
}

// Test with very large double values
TEST_F(AnnotPathTest_736, VeryLargeDoubleValues_736) {
    std::vector<AnnotCoord> coords;
    coords.emplace_back(1e15, 2e15);

    AnnotPath path(std::move(coords));
    EXPECT_EQ(path.getCoordsLength(), 1);
    EXPECT_DOUBLE_EQ(path.getX(0), 1e15);
    EXPECT_DOUBLE_EQ(path.getY(0), 2e15);
}

// Test getCoordsLength is const-correct
TEST_F(AnnotPathTest_736, GetCoordsLengthIsConst_736) {
    std::vector<AnnotCoord> coords;
    coords.emplace_back(1.0, 2.0);
    const AnnotPath path(std::move(coords));
    EXPECT_EQ(path.getCoordsLength(), 1);
}

// Test multiple coordinate access in sequence
TEST_F(AnnotPathTest_736, SequentialCoordinateAccess_736) {
    std::vector<AnnotCoord> coords;
    coords.emplace_back(10.0, 20.0);
    coords.emplace_back(30.0, 40.0);
    coords.emplace_back(50.0, 60.0);
    coords.emplace_back(70.0, 80.0);
    coords.emplace_back(90.0, 100.0);

    AnnotPath path(std::move(coords));
    EXPECT_EQ(path.getCoordsLength(), 5);

    for (int i = 0; i < 5; ++i) {
        EXPECT_DOUBLE_EQ(path.getX(i), (i * 20.0) + 10.0);
        EXPECT_DOUBLE_EQ(path.getY(i), (i * 20.0) + 20.0);
    }
}
