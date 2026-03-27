#include <gtest/gtest.h>

#include "TestProjects/poppler/qt5/src/poppler-document.h"



class PopplerDocumentTest_1359 : public ::testing::Test {

protected:

    // Setup and teardown methods can be used if necessary

};



TEST_F(PopplerDocumentTest_1359, IsCmsAvailable_ReturnsTrue_WhenCmsIsEnabled_1359) {

    #if USE_CMS

    EXPECT_TRUE(Poppler::isCmsAvailable());

    #endif

}



TEST_F(PopplerDocumentTest_1359, IsCmsAvailable_ReturnsFalse_WhenCmsIsDisabled_1359) {

    #ifndef USE_CMS

    EXPECT_FALSE(Poppler::isCmsAvailable());

    #endif

}
