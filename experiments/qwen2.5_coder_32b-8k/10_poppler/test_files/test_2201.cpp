#include <gtest/gtest.h>

#include "poppler-document.h"



class PopplerDocumentTest : public ::testing::Test {

protected:

    // Mocking external collaborators or dependencies if needed.

    // None required in this case as per constraints.



    virtual void SetUp() override {

        // Setup code here, if any.

        // No setup is necessary for the given interface.

    }



    virtual void TearDown() override {

        // Teardown code here, if any.

        // No teardown is necessary for the given interface.

    }

};



TEST_F(PopplerDocumentTest_2201, NormalOperation_AllPermissionsGranted_2201) {

    PopplerDocument document;

    document.doc = new _PopplerDocument();

    ON_CALL(*document.doc, okToPrint()).WillByDefault(::testing::Return(true));

    ON_CALL(*document.doc, okToChange()).WillByDefault(::testing::Return(true));

    ON_CALL(*document.doc, okToCopy()).WillByDefault(::testing::Return(true));

    ON_CALL(*document.doc, okToAddNotes()).WillByDefault(::testing::Return(true));

    ON_CALL(*document.doc, okToFillForm()).WillByDefault(::testing::Return(true));

    ON_CALL(*document.doc, okToAccessibility()).WillByDefault(::testing::Return(true));

    ON_CALL(*document.doc, okToAssemble()).WillByDefault(::testing::Return(true));

    ON_CALL(*document.doc, okToPrintHighRes()).WillByDefault(::testing::Return(true));



    PopplerPermissions permissions = poppler_document_get_permissions(&document);

    EXPECT_EQ(permissions, POPPLER_PERMISSIONS_FULL);



    delete document.doc;

}



TEST_F(PopplerDocumentTest_2201, NormalOperation_NoPermissionsGranted_2201) {

    PopplerDocument document;

    document.doc = new _PopplerDocument();

    ON_CALL(*document.doc, okToPrint()).WillByDefault(::testing::Return(false));

    ON_CALL(*document.doc, okToChange()).WillByDefault(::testing::Return(false));

    ON_CALL(*document.doc, okToCopy()).WillByDefault(::testing::Return(false));

    ON_CALL(*document.doc, okToAddNotes()).WillByDefault(::testing::Return(false));

    ON_CALL(*document.doc, okToFillForm()).WillByDefault(::testing::Return(false));

    ON_CALL(*document.doc, okToAccessibility()).WillByDefault(::testing::Return(false));

    ON_CALL(*document.doc, okToAssemble()).WillByDefault(::testing::Return(false));

    ON_CALL(*document.doc, okToPrintHighRes()).WillByDefault(::testing::Return(false));



    PopplerPermissions permissions = poppler_document_get_permissions(&document);

    EXPECT_EQ(permissions, 0);



    delete document.doc;

}



TEST_F(PopplerDocumentTest_2201, BoundaryConditions_SinglePermissionGranted_2201) {

    PopplerDocument document;

    document.doc = new _PopplerDocument();

    ON_CALL(*document.doc, okToPrint()).WillByDefault(::testing::Return(true));

    ON_CALL(*document.doc, okToChange()).WillByDefault(::testing::Return(false));

    ON_CALL(*document.doc, okToCopy()).WillByDefault(::testing::Return(false));

    ON_CALL(*document.doc, okToAddNotes()).WillByDefault(::testing::Return(false));

    ON_CALL(*document.doc, okToFillForm()).WillByDefault(::testing::Return(false));

    ON_CALL(*document.doc, okToAccessibility()).WillByDefault(::testing::Return(false));

    ON_CALL(*document.doc, okToAssemble()).WillByDefault(::testing::Return(false));

    ON_CALL(*document.doc, okToPrintHighRes()).WillByDefault(::testing::Return(false));



    PopplerPermissions permissions = poppler_document_get_permissions(&document);

    EXPECT_EQ(permissions, POPPLER_PERMISSIONS_OK_TO_PRINT);



    delete document.doc;

}



TEST_F(PopplerDocumentTest_2201, BoundaryConditions_AllButOnePermissionGranted_2201) {

    PopplerDocument document;

    document.doc = new _PopplerDocument();

    ON_CALL(*document.doc, okToPrint()).WillByDefault(::testing::Return(true));

    ON_CALL(*document.doc, okToChange()).WillByDefault(::testing::Return(true));

    ON_CALL(*document.doc, okToCopy()).WillByDefault(::testing::Return(true));

    ON_CALL(*document.doc, okToAddNotes()).WillByDefault(::testing::Return(true));

    ON_CALL(*document.doc, okToFillForm()).WillByDefault(::testing::Return(true));

    ON_CALL(*document.doc, okToAccessibility()).WillByDefault(::testing::Return(true));

    ON_CALL(*document.doc, okToAssemble()).WillByDefault(::testing::Return(true));

    ON_CALL(*document.doc, okToPrintHighRes()).WillByDefault(::testing::Return(false));



    PopplerPermissions permissions = poppler_document_get_permissions(&document);

    EXPECT_EQ(permissions, POPPLER_PERMISSIONS_FULL ^ POPPLER_PERMISSIONS_OK_TO_PRINT_HIGH_RESOLUTION);



    delete document.doc;

}



TEST_F(PopplerDocumentTest_2201, ExceptionalCase_NullDocument_2201) {

    PopplerDocument* null_document = nullptr;



    PopplerPermissions permissions = poppler_document_get_permissions(null_document);

    EXPECT_EQ(permissions, POPPLER_PERMISSIONS_FULL); // Due to g_return_val_if_fail returning full permissions for null

}



// Note: The above test assumes that the function returns full permissions when a null document is passed,

// which is not ideal. In practice, this should be handled more gracefully.

```


