#include <gtest/gtest.h>

#include "poppler-annot.h"



class PopplerAnnotMovieTest_2048 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialization code if needed

    }



    void TearDown() override {

        // Cleanup code if needed

    }

};



TEST_F(PopplerAnnotMovieTest_2048, FinalizeIsSet_2048) {

    PopplerAnnotMovieClass klass;

    poppler_annot_movie_class_init(&klass);

    EXPECT_EQ(klass.finalize, &poppler_annot_movie_finalize);

}

```


