#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming PopplerFontInfo and its related classes are declared somewhere in the codebase.

class PopplerFontInfo;

struct _PopplerFontInfoClass;



// Mocking any external collaborators if needed, but none are evident from the provided interface.



// Test fixture for PopplerFontInfo tests

class PopplerFontInfoTest_2232 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if necessary (though minimal based on given information)

    }



    void TearDown() override {

        // Teardown code if necessary (though minimal based on given information)

    }

};



// Test case for normal operation

TEST_F(PopplerFontInfoTest_2232, ClassInitSetsFinalizeFunction_2232) {

    PopplerFontInfoClass klass;

    GObjectClass* gobject_class = G_OBJECT_CLASS(&klass);



    // Initialize the class

    poppler_font_info_class_init(&klass);



    // Verify that the finalize function is set correctly

    EXPECT_NE(gobject_class->finalize, nullptr);

}



// Additional test cases for boundary conditions and error handling can be added if more information about the interface is available.

```


