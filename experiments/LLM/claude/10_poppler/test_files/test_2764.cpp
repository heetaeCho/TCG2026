#include <gtest/gtest.h>

// We need to include the relevant headers for Poppler's LinkDestination
// Based on the partial code, we know LinkDestination and LinkDestinationPrivate exist
// in the Poppler namespace

#include "poppler-link.h"
#include "poppler-qt5.h"

using namespace Poppler;

// Test fixture for LinkDestination tests
class LinkDestinationTest_2764 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test default construction of LinkDestination
TEST_F(LinkDestinationTest_2764, DefaultConstruction_2764) {
    // Construct a LinkDestination with default/empty string
    LinkDestination dest(QString());
    
    // Based on the private defaults we can see:
    // kind = destXYZ, pageNum = 0, left = 0, bottom = 0, right = 0, top = 0
    // zoom = 1, changeLeft = true, changeTop = true, changeZoom = false
    
    EXPECT_EQ(dest.destinationType(), LinkDestination::destXYZ);
    EXPECT_EQ(dest.pageNumber(), 0);
    EXPECT_DOUBLE_EQ(dest.left(), 0.0);
    EXPECT_DOUBLE_EQ(dest.bottom(), 0.0);
    EXPECT_DOUBLE_EQ(dest.right(), 0.0);
    EXPECT_DOUBLE_EQ(dest.top(), 0.0);
    EXPECT_DOUBLE_EQ(dest.zoom(), 1.0);
    EXPECT_TRUE(dest.isChangeLeft());
    EXPECT_TRUE(dest.isChangeTop());
    EXPECT_FALSE(dest.isChangeZoom());
}

// Test copy construction of LinkDestination
TEST_F(LinkDestinationTest_2764, CopyConstruction_2764) {
    LinkDestination dest(QString());
    LinkDestination destCopy(dest);
    
    EXPECT_EQ(destCopy.destinationType(), dest.destinationType());
    EXPECT_EQ(destCopy.pageNumber(), dest.pageNumber());
    EXPECT_DOUBLE_EQ(destCopy.left(), dest.left());
    EXPECT_DOUBLE_EQ(destCopy.bottom(), dest.bottom());
    EXPECT_DOUBLE_EQ(destCopy.right(), dest.right());
    EXPECT_DOUBLE_EQ(destCopy.top(), dest.top());
    EXPECT_DOUBLE_EQ(destCopy.zoom(), dest.zoom());
    EXPECT_EQ(destCopy.isChangeLeft(), dest.isChangeLeft());
    EXPECT_EQ(destCopy.isChangeTop(), dest.isChangeTop());
    EXPECT_EQ(destCopy.isChangeZoom(), dest.isChangeZoom());
}

// Test assignment operator of LinkDestination
TEST_F(LinkDestinationTest_2764, AssignmentOperator_2764) {
    LinkDestination dest1(QString());
    LinkDestination dest2(QString());
    
    dest2 = dest1;
    
    EXPECT_EQ(dest2.destinationType(), dest1.destinationType());
    EXPECT_EQ(dest2.pageNumber(), dest1.pageNumber());
    EXPECT_DOUBLE_EQ(dest2.left(), dest1.left());
    EXPECT_DOUBLE_EQ(dest2.top(), dest1.top());
    EXPECT_DOUBLE_EQ(dest2.zoom(), dest1.zoom());
}

// Test destination type is destXYZ by default
TEST_F(LinkDestinationTest_2764, DefaultDestinationType_2764) {
    LinkDestination dest(QString());
    EXPECT_EQ(dest.destinationType(), LinkDestination::destXYZ);
}

// Test default page number is 0
TEST_F(LinkDestinationTest_2764, DefaultPageNumber_2764) {
    LinkDestination dest(QString());
    EXPECT_EQ(dest.pageNumber(), 0);
}

// Test default zoom is 1.0
TEST_F(LinkDestinationTest_2764, DefaultZoom_2764) {
    LinkDestination dest(QString());
    EXPECT_DOUBLE_EQ(dest.zoom(), 1.0);
}

// Test default left is 0
TEST_F(LinkDestinationTest_2764, DefaultLeft_2764) {
    LinkDestination dest(QString());
    EXPECT_DOUBLE_EQ(dest.left(), 0.0);
}

// Test default top is 0
TEST_F(LinkDestinationTest_2764, DefaultTop_2764) {
    LinkDestination dest(QString());
    EXPECT_DOUBLE_EQ(dest.top(), 0.0);
}

// Test default bottom is 0
TEST_F(LinkDestinationTest_2764, DefaultBottom_2764) {
    LinkDestination dest(QString());
    EXPECT_DOUBLE_EQ(dest.bottom(), 0.0);
}

// Test default right is 0
TEST_F(LinkDestinationTest_2764, DefaultRight_2764) {
    LinkDestination dest(QString());
    EXPECT_DOUBLE_EQ(dest.right(), 0.0);
}

// Test default changeLeft is true
TEST_F(LinkDestinationTest_2764, DefaultChangeLeft_2764) {
    LinkDestination dest(QString());
    EXPECT_TRUE(dest.isChangeLeft());
}

// Test default changeTop is true
TEST_F(LinkDestinationTest_2764, DefaultChangeTop_2764) {
    LinkDestination dest(QString());
    EXPECT_TRUE(dest.isChangeTop());
}

// Test default changeZoom is false
TEST_F(LinkDestinationTest_2764, DefaultChangeZoom_2764) {
    LinkDestination dest(QString());
    EXPECT_FALSE(dest.isChangeZoom());
}

// Test toString produces a non-empty or consistent representation
TEST_F(LinkDestinationTest_2764, ToStringConsistency_2764) {
    LinkDestination dest(QString());
    QString str = dest.toString();
    
    // Reconstructing from the string should produce equivalent destination
    LinkDestination dest2(str);
    EXPECT_EQ(dest2.destinationType(), dest.destinationType());
    EXPECT_EQ(dest2.pageNumber(), dest.pageNumber());
    EXPECT_DOUBLE_EQ(dest2.left(), dest.left());
    EXPECT_DOUBLE_EQ(dest2.top(), dest.top());
    EXPECT_DOUBLE_EQ(dest2.zoom(), dest.zoom());
}

// Test constructing LinkDestination from a serialized string roundtrip
TEST_F(LinkDestinationTest_2764, RoundTripSerialization_2764) {
    LinkDestination original(QString());
    QString serialized = original.toString();
    LinkDestination reconstructed(serialized);
    
    EXPECT_EQ(reconstructed.destinationType(), original.destinationType());
    EXPECT_EQ(reconstructed.pageNumber(), original.pageNumber());
    EXPECT_DOUBLE_EQ(reconstructed.left(), original.left());
    EXPECT_DOUBLE_EQ(reconstructed.bottom(), original.bottom());
    EXPECT_DOUBLE_EQ(reconstructed.right(), original.right());
    EXPECT_DOUBLE_EQ(reconstructed.top(), original.top());
    EXPECT_DOUBLE_EQ(reconstructed.zoom(), original.zoom());
    EXPECT_EQ(reconstructed.isChangeLeft(), original.isChangeLeft());
    EXPECT_EQ(reconstructed.isChangeTop(), original.isChangeTop());
    EXPECT_EQ(reconstructed.isChangeZoom(), original.isChangeZoom());
}

// Test self-assignment
TEST_F(LinkDestinationTest_2764, SelfAssignment_2764) {
    LinkDestination dest(QString());
    dest = dest;
    
    EXPECT_EQ(dest.destinationType(), LinkDestination::destXYZ);
    EXPECT_EQ(dest.pageNumber(), 0);
    EXPECT_DOUBLE_EQ(dest.zoom(), 1.0);
}
