#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "PDFDoc.h"

#include "XRef.h"



using ::testing::Return;

using ::testing::_;



class MockXRef : public XRef {

public:

    MOCK_METHOD(void, removeDocInfo, (), (override));

};



class PDFDocTest_974 : public ::testing::Test {

protected:

    std::unique_ptr<MockXRef> mockXRef = std::make_unique<MockXRef>();

    PDFDoc pdfDoc;

    

    void SetUp() override {

        // Simulate the setup of PDFDoc with a mock XRef object

        pdfDoc.xref = mockXRef.get();

    }

};



TEST_F(PDFDocTest_974, RemoveDocInfo_CallsRemoveDocInfoOnXRef_974) {

    EXPECT_CALL(*mockXRef, removeDocInfo()).Times(1);

    

    pdfDoc.removeDocInfo();

}



// Since the provided PDFDoc::removeDocInfo simply forwards to XRef::removeDocInfo,

// there are no other observable behaviors or error conditions to test in isolation.

```


