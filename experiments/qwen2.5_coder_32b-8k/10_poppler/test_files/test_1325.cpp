#include <gtest/gtest.h>

#include "PSOutputDev.h"

#include "PDFDoc.h"



// Mock class for PDFDoc to satisfy constructor requirements.

class MockPDFDoc : public PDFDoc {

public:

    MockPDFDoc() {}

};



// Test fixture for PSOutputDev tests.

class PSOutputDevTest_1325 : public ::testing::Test {

protected:

    void SetUp() override {

        // Create an instance of PSOutputDev with mock PDFDoc and other required parameters.

        doc = new MockPDFDoc();

        psOutDev = new PSOutputDev("test.ps", doc, nullptr, std::vector<int>(), 

                                  static_cast<PSOutMode>(0), 595, 842, false, false, 

                                  0, 0, 595, 842, static_cast<PSForceRasterize>(0),

                                  false, nullptr, nullptr, static_cast<PSLevel>(0));

    }



    void TearDown() override {

        // Clean up the instance after each test.

        delete psOutDev;

        delete doc;

    }



    PSOutputDev* psOutDev;

    MockPDFDoc* doc;

};



// Test case for normal operation of setEmbedType1 with true.

TEST_F(PSOutputDevTest_1325, SetEmbedType1True_NormalOperation_1325) {

    psOutDev->setEmbedType1(true);

    EXPECT_TRUE(psOutDev->getEmbedType1());

}



// Test case for normal operation of setEmbedType1 with false.

TEST_F(PSOutputDevTest_1325, SetEmbedType1False_NormalOperation_1325) {

    psOutDev->setEmbedType1(false);

    EXPECT_FALSE(psOutDev->getEmbedType1());

}



// Test case for boundary condition of setEmbedType1 (repeated calls).

TEST_F(PSOutputDevTest_1325, SetEmbedType1Boundary_RepeatedCalls_1325) {

    psOutDev->setEmbedType1(true);

    EXPECT_TRUE(psOutDev->getEmbedType1());

    psOutDev->setEmbedType1(false);

    EXPECT_FALSE(psOutDev->getEmbedType1());

}



// Test case for exceptional or error cases (if applicable).

// Note: For this specific setter method, there are no observable exceptions.

```


