#include <gtest/gtest.h>
#include "./TestProjects/poppler/poppler/ProfileData.h"

class ProfileDataTest_1056 : public ::testing::Test {
protected:
    ProfileData profileData;
};

TEST_F(ProfileDataTest_1056, getMax_ReturnsCorrectMaxValue_1056) {
    // Arrange
    profileData.addElement(10.0);
    profileData.addElement(20.0);
    profileData.addElement(30.0);

    // Act
    double result = profileData.getMax();

    // Assert
    EXPECT_EQ(result, 30.0);
}

TEST_F(ProfileDataTest_1056, getCount_ReturnsCorrectCount_1056) {
    // Arrange
    profileData.addElement(10.0);
    profileData.addElement(20.0);

    // Act
    int result = profileData.getCount();

    // Assert
    EXPECT_EQ(result, 2);
}

TEST_F(ProfileDataTest_1056, getTotal_ReturnsCorrectTotal_1056) {
    // Arrange
    profileData.addElement(5.0);
    profileData.addElement(15.0);

    // Act
    double result = profileData.getTotal();

    // Assert
    EXPECT_EQ(result, 20.0);
}

TEST_F(ProfileDataTest_1056, getMin_ReturnsCorrectMinValue_1056) {
    // Arrange
    profileData.addElement(50.0);
    profileData.addElement(20.0);
    profileData.addElement(30.0);

    // Act
    double result = profileData.getMin();

    // Assert
    EXPECT_EQ(result, 20.0);
}

TEST_F(ProfileDataTest_1056, getMax_WithNoElements_ReturnsZero_1056) {
    // Act
    double result = profileData.getMax();

    // Assert
    EXPECT_EQ(result, 0.0);
}

TEST_F(ProfileDataTest_1056, getMin_WithNoElements_ReturnsZero_1056) {
    // Act
    double result = profileData.getMin();

    // Assert
    EXPECT_EQ(result, 0.0);
}

TEST_F(ProfileDataTest_1056, addElement_IncreasesCountAndTotal_1056) {
    // Arrange
    profileData.addElement(10.0);

    // Act
    int count = profileData.getCount();
    double total = profileData.getTotal();

    // Assert
    EXPECT_EQ(count, 1);
    EXPECT_EQ(total, 10.0);
}

TEST_F(ProfileDataTest_1056, addElement_UpdatesMaxAndMin_1056) {
    // Arrange
    profileData.addElement(5.0);
    profileData.addElement(15.0);

    // Act
    double max = profileData.getMax();
    double min = profileData.getMin();

    // Assert
    EXPECT_EQ(max, 15.0);
    EXPECT_EQ(min, 5.0);
}

TEST_F(ProfileDataTest_1056, addElement_SingleElement_1056) {
    // Arrange
    profileData.addElement(10.0);

    // Act
    double max = profileData.getMax();
    double min = profileData.getMin();

    // Assert
    EXPECT_EQ(max, 10.0);
    EXPECT_EQ(min, 10.0);
}