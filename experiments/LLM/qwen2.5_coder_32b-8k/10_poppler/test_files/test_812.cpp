#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Annot.h"



using namespace testing;



class AnnotScreenTest_812 : public ::testing::Test {

protected:

    PDFDoc* docA;

    PDFRectangle rect;

    Object dictObject;

    Object obj;

    std::unique_ptr<AnnotScreen> annotScreen;



    void SetUp() override {

        docA = new PDFDoc();  // Assuming PDFDoc has a default constructor

        annotScreen = std::make_unique<AnnotScreen>(docA, &rect);

    }



    void TearDown() override {

        delete docA;

    }

};



TEST_F(AnnotScreenTest_812, GetAppearCharacs_ReturnsNonNullPointer_812) {

    EXPECT_NE(annotScreen->getAppearCharacs(), nullptr);

}



TEST_F(AnnotScreenTest_812, GetAppearCharacs_ConsistentAcrossCalls_812) {

    AnnotAppearanceCharacs* firstCall = annotScreen->getAppearCharacs();

    AnnotAppearanceCharacs* secondCall = annotScreen->getAppearCharacs();

    EXPECT_EQ(firstCall, secondCall);

}



// Assuming there are no boundary conditions or exceptional cases directly observable

// through the provided interface for getAppearCharacs function.

```


