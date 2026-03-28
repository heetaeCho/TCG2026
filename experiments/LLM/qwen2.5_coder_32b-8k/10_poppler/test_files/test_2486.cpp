#include <gtest/gtest.h>

#include "poppler-page.h"



class PopplerImageMappingTest_2486 : public ::testing::Test {

protected:

    void SetUp() override {

        mapping = poppler_image_mapping_new();

    }



    void TearDown() override {

        g_slice_free(PopplerImageMapping, mapping);

    }



    PopplerImageMapping* mapping;

};



TEST_F(PopplerImageMappingTest_2486, NewObjectIsNotNull_2486) {

    EXPECT_NE(mapping, nullptr);

}



// Assuming there are no observable side effects or additional methods to test,

// the above test case checks the basic operation of creating a new object.

```


