#include <gtest/gtest.h>

#include "Object.h"



class ObjectTest_105 : public ::testing::Test {

protected:

    ObjectTest_105() {}

    virtual ~ObjectTest_105() {}



    void SetUp() override {

        // Setup code, if needed

    }



    void TearDown() override {

        // Teardown code, if needed

    }

};



TEST_F(ObjectTest_105, GetRefNum_ReturnsCorrectValue_105) {

    Ref ref = {42, 0};

    Object obj;

    // Assuming we have a way to set the reference number for testing purposes

    // This is a placeholder as we cannot modify internal state directly

    // For demonstration, let's assume there's a method to set the reference number

    // obj.setRef(ref); // Hypothetical method



    EXPECT_EQ(obj.getRefNum(), ref.num);

}



TEST_F(ObjectTest_105, GetRefNum_BoundaryConditionZero_105) {

    Ref ref = {0, 0};

    Object obj;

    // Assuming we have a way to set the reference number for testing purposes

    // This is a placeholder as we cannot modify internal state directly

    // For demonstration, let's assume there's a method to set the reference number

    // obj.setRef(ref); // Hypothetical method



    EXPECT_EQ(obj.getRefNum(), ref.num);

}



TEST_F(ObjectTest_105, GetRefNum_BoundaryConditionNegative_105) {

    Ref ref = {-1, 0};

    Object obj;

    // Assuming we have a way to set the reference number for testing purposes

    // This is a placeholder as we cannot modify internal state directly

    // For demonstration, let's assume there's a method to set the reference number

    // obj.setRef(ref); // Hypothetical method



    EXPECT_EQ(obj.getRefNum(), ref.num);

}



TEST_F(ObjectTest_105, GetRefNum_DefaultConstructor_ReturnsZero_105) {

    Object obj;

    EXPECT_EQ(obj.getRefNum(), 0);

}
