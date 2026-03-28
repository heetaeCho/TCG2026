#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/poppler/Annot.h"



using namespace testing;



TEST(AnnotColorTest_755, DefaultConstructorInitializesValuesToZero_755) {

    AnnotColor color;

    const std::array<double, 4>& values = color.getValues();

    EXPECT_EQ(values, std::array<double, 4>{0.0, 0.0, 0.0, 0.0});

}



TEST(AnnotColorTest_755, GrayConstructorSetsCorrectValues_755) {

    AnnotColor color(0.5);

    const std::array<double, 4>& values = color.getValues();

    EXPECT_EQ(values, std::array<double, 4>{0.5, 0.5, 0.5, 1.0});

}



TEST(AnnotColorTest_755, RGBConstructorSetsCorrectValues_755) {

    AnnotColor color(0.2, 0.3, 0.4);

    const std::array<double, 4>& values = color.getValues();

    EXPECT_EQ(values, std::array<double, 4>{0.2, 0.3, 0.4, 1.0});

}



TEST(AnnotColorTest_755, CMYKConstructorSetsCorrectValues_755) {

    AnnotColor color(0.1, 0.2, 0.3, 0.4);

    const std::array<double, 4>& values = color.getValues();

    EXPECT_EQ(values, std::array<double, 4>{0.1, 0.2, 0.3, 0.4});

}



// Since the Array constructor and adjustColor method are not observable through public functions or callbacks,

// we cannot directly test them based on the given interface.



TEST(AnnotColorTest_755, GetValuesReturnsConsistentData_755) {

    AnnotColor color(0.1, 0.2, 0.3);

    const std::array<double, 4>& values = color.getValues();

    EXPECT_EQ(values[0], 0.1);

    EXPECT_EQ(values[1], 0.2);

    EXPECT_EQ(values[2], 0.3);

    EXPECT_EQ(values[3], 1.0);



    const std::array<double, 4>& sameValues = color.getValues();

    EXPECT_EQ(sameValues, values);

}



// No observable exceptional or error cases through the provided interface.
