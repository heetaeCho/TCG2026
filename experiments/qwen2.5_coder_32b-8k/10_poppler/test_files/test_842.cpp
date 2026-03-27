#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Annot.h"



// Mock class for AnnotColor to use in tests

class MockAnnotColor : public AnnotColor {

public:

    MOCK_METHOD(void, someMethod, (), (override));

};



TEST_F(AnnotGeometryTest_842, GetInteriorColor_ReturnsNullptrWhenNotSet_842) {

    AnnotGeometry annotGeometry(nullptr, nullptr, AnnotSubtype::square);

    EXPECT_EQ(annotGeometry.getInteriorColor(), nullptr);

}



TEST_F(AnnotGeometryTest_842, GetInteriorColor_ReturnsSetInteriorColor_842) {

    auto mockColor = std::make_unique<MockAnnotColor>();

    MockAnnotColor* mockColorPtr = mockColor.get();

    AnnotGeometry annotGeometry(nullptr, nullptr, AnnotSubtype::square);

    annotGeometry.setInteriorColor(std::move(mockColor));

    EXPECT_EQ(annotGeometry.getInteriorColor(), mockColorPtr);

}



TEST_F(AnnotGeometryTest_842, SetAndGetInteriorColor_MultipleTimes_842) {

    auto mockColor1 = std::make_unique<MockAnnotColor>();

    MockAnnotColor* mockColorPtr1 = mockColor1.get();

    auto mockColor2 = std::make_unique<MockAnnotColor>();

    MockAnnotColor* mockColorPtr2 = mockColor2.get();



    AnnotGeometry annotGeometry(nullptr, nullptr, AnnotSubtype::square);

    annotGeometry.setInteriorColor(std::move(mockColor1));

    EXPECT_EQ(annotGeometry.getInteriorColor(), mockColorPtr1);



    annotGeometry.setInteriorColor(std::move(mockColor2));

    EXPECT_EQ(annotGeometry.getInteriorColor(), mockColorPtr2);

}



// Assuming there are other methods in AnnotGeometry that can be tested similarly
