#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming necessary headers and definitions for PopplerStructureElement and its dependencies are included



class PopplerStructureElementTest_2518 : public ::testing::Test {

protected:

    // Setup code, if any, can be placed here

};



TEST_F(PopplerStructureElementTest_2518, ClassInitializationSetsFinalizeFunction_2518) {

    // Arrange

    PopplerStructureElementClass klass;

    

    // Act

    poppler_structure_element_class_init(&klass);

    

    // Assert

    EXPECT_NE(klass.finalize, static_cast<GObjectFinalizeFunc>(nullptr));

}



// Additional test cases can be added here if there are more observable behaviors to test



```


