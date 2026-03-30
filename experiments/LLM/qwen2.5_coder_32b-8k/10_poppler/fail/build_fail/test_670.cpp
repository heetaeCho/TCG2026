#include <gtest/gtest.h>

#include "Catalog.h"



class CatalogTest_670 : public ::testing::Test {

protected:

    void SetUp() override {

        // Assuming PDFDoc* docA is properly initialized in actual use

        // Here we are treating it as a black box, so no need to initialize it

        catalog = std::make_unique<Catalog>(nullptr);

    }



    void TearDown() override {

        catalog.reset();

    }



    std::unique_ptr<Catalog> catalog;

};



TEST_F(CatalogTest_670, IsOk_ReturnsTrueWhenCatalogIsInitializedProperly_670) {

    EXPECT_TRUE(catalog->isOk());

}



TEST_F(CatalogTest_670, GetNumPages_ReturnsNonNegativeNumber_670) {

    int numPages = catalog->getNumPages();

    EXPECT_GE(numPages, 0);

}



TEST_F(CatalogTest_670, GetPage_ReturnsNullptrForInvalidIndex_670) {

    Page* page = catalog->getPage(-1);

    EXPECT_EQ(page, nullptr);



    page = catalog->getPage(catalog->getNumPages());

    EXPECT_EQ(page, nullptr);

}



TEST_F(CatalogTest_670, GetPageRef_ReturnsNullptrForInvalidIndex_670) {

    Ref* ref = catalog->getPageRef(-1);

    EXPECT_EQ(ref, nullptr);



    ref = catalog->getPageRef(catalog->getNumPages());

    EXPECT_EQ(ref, nullptr);

}



TEST_F(CatalogTest_670, ReadMetadata_ReturnsNonNullGooStringPointer_670) {

    std::unique_ptr<GooString> metadata = catalog->readMetadata();

    EXPECT_NE(metadata.get(), nullptr);

}



TEST_F(CatalogTest_670, GetStructTreeRoot_ReturnsNullptrWhenNotAvailable_670) {

    StructTreeRoot* structTreeRoot = catalog->getStructTreeRoot();

    EXPECT_EQ(structTreeRoot, nullptr);

}



TEST_F(CatalogTest_670, GetMarkInfo_ReturnsZeroWhenNoMarksArePresent_670) {

    unsigned int markInfo = catalog->getMarkInfo();

    EXPECT_EQ(markInfo, 0U);

}



TEST_F(CatalogTest_670, FindPage_ReturnsNegativeOneForInvalidRef_670) {

    Ref invalidRef;

    int pageIndex = catalog->findPage(invalidRef);

    EXPECT_LT(pageIndex, 0);

}



TEST_F(CatalogTest_670, FindDest_ReturnsNullptrWhenNameDoesNotExist_670) {

    std::unique_ptr<GooString> nonExistentName = std::make_unique<GooString>("NonExistentName");

    std::unique_ptr<LinkDest> dest = catalog->findDest(nonExistentName.get());

    EXPECT_EQ(dest.get(), nullptr);

}



TEST_F(CatalogTest_670, GetDests_ReturnsNonNullObjectPointer_670) {

    Object* dests = catalog->getDests();

    EXPECT_NE(dests, nullptr);

}



TEST_F(CatalogTest_670, NumDests_ReturnsNonNegativeNumber_670) {

    int numDests = catalog->numDests();

    EXPECT_GE(numDests, 0);

}



TEST_F(CatalogTest_670, GetDestsName_ReturnsNullptrForInvalidIndex_670) {

    const char* name = catalog->getDestsName(-1);

    EXPECT_EQ(name, nullptr);



    name = catalog->getDestsName(catalog->numDests());

    EXPECT_EQ(name, nullptr);

}



TEST_F(CatalogTest_670, GetDestsDest_ReturnsNullptrForInvalidIndex_670) {

    std::unique_ptr<LinkDest> dest = catalog->getDestsDest(-1);

    EXPECT_EQ(dest.get(), nullptr);



    dest = catalog->getDestsDest(catalog->numDests());

    EXPECT_EQ(dest.get(), nullptr);

}



TEST_F(CatalogTest_670, GetDestNameTreeDest_ReturnsNullptrForInvalidIndex_670) {

    std::unique_ptr<LinkDest> dest = catalog->getDestNameTreeDest(-1);

    EXPECT_EQ(dest.get(), nullptr);



    dest = catalog->getDestNameTreeDest(catalog->numDestNameTree());

    EXPECT_EQ(dest.get(), nullptr);

}



TEST_F(CatalogTest_670, EmbeddedFile_ReturnsNullptrWhenNoFilesAreEmbedded_670) {

    std::unique_ptr<FileSpec> fileSpec = catalog->embeddedFile(0);

    EXPECT_EQ(fileSpec.get(), nullptr);

}



TEST_F(CatalogTest_670, HasEmbeddedFile_ReturnsFalseForNonExistentFileName_670) {

    bool hasFile = catalog->hasEmbeddedFile("NonExistentFile");

    EXPECT_FALSE(hasFile);

}



TEST_F(CatalogTest_670, GetJS_ReturnsEmptyStringWhenNoJavaScriptIsPresent_670) {

    std::string js = catalog->getJS(0);

    EXPECT_EQ(js, "");

}



TEST_F(CatalogTest_670, LabelToIndex_ReturnsFalseForNonExistentLabel_670) {

    int index;

    bool result = catalog->labelToIndex(GooString("NonExistentLabel"), &index);

    EXPECT_FALSE(result);

}



TEST_F(CatalogTest_670, IndexToLabel_ReturnsFalseForInvalidIndex_670) {

    GooString label;

    bool result = catalog->indexToLabel(-1, &label);

    EXPECT_FALSE(result);



    result = catalog->indexToLabel(catalog->getNumPages(), &label);

    EXPECT_FALSE(result);

}



TEST_F(CatalogTest_670, GetOutline_ReturnsNonNullObjectPointer_670) {

    Object* outline = catalog->getOutline();

    EXPECT_NE(outline, nullptr);

}



TEST_F(CatalogTest_670, GetAcroForm_ReturnsNonNullObjectPointer_670) {

    Object* acroForm = catalog->getAcroForm();

    EXPECT_NE(acroForm, nullptr);

}



TEST_F(CatalogTest_670, GetViewerPreferences_ReturnsNonNullViewerPreferencesPointer_670) {

    ViewerPreferences* viewerPrefs = catalog->getViewerPreferences();

    EXPECT_NE(viewerPrefs, nullptr);

}



TEST_F(CatalogTest_670, GetPageMode_ReturnsDefaultPageMode_670) {

    PageMode pageMode = catalog->getPageMode();

    EXPECT_EQ(pageMode, pageModeUseNone); // Assuming default is pageModeUseNone

}



TEST_F(CatalogTest_670, GetPageLayout_ReturnsDefaultPageLayout_670) {

    PageLayout pageLayout = catalog->getPageLayout();

    EXPECT_EQ(pageLayout, pageLayoutSinglePage); // Assuming default is pageLayoutSinglePage

}



TEST_F(CatalogTest_670, GetAdditionalAction_ReturnsNullptrForInvalidType_670) {

    std::unique_ptr<LinkAction> action = catalog->getAdditionalAction(static_cast<DocumentAdditionalActionsType>(-1));

    EXPECT_EQ(action.get(), nullptr);

}



TEST_F(CatalogTest_670, GetOpenAction_ReturnsNullptrWhenNoOpenActionIsSet_670) {

    const std::unique_ptr<LinkAction>& openAction = catalog->getOpenAction();

    EXPECT_EQ(openAction.get(), nullptr);

}



TEST_F(CatalogTest_670, GetDisplayProfile_ReturnsNonNullGfxLCMSProfilePointer_670) {

    GfxLCMSProfilePtr displayProfile = catalog->getDisplayProfile();

    EXPECT_NE(displayProfile.get(), nullptr);

}



TEST_F(CatalogTest_670, GetXYZ2DisplayTransforms_ReturnsNonNullTransformsPointer_670) {

    std::shared_ptr<GfxXYZ2DisplayTransforms> transforms = catalog->getXYZ2DisplayTransforms();

    EXPECT_NE(transforms.get(), nullptr);

}



TEST_F(CatalogTest_670, NumDestNameTree_ReturnsNonNegativeNumber_670) {

    int numEntries = catalog->numDestNameTree();

    EXPECT_GE(numEntries, 0);

}



TEST_F(CatalogTest_670, GetDestNameTreeName_ReturnsNullptrForInvalidIndex_670) {

    const GooString* name = catalog->getDestNameTreeName(-1);

    EXPECT_EQ(name, nullptr);



    name = catalog->getDestNameTreeName(catalog->numDestNameTree());

    EXPECT_EQ(name, nullptr);

}



TEST_F(CatalogTest_670, NumEmbeddedFiles_ReturnsNonNegativeNumber_670) {

    int numFiles = catalog->numEmbeddedFiles();

    EXPECT_GE(numFiles, 0);

}



TEST_F(CatalogTest_670, NumJS_ReturnsNonNegativeNumber_670) {

    int numScripts = catalog->numJS();

    EXPECT_GE(numScripts, 0);

}



TEST_F(CatalogTest_670, GetJSName_ReturnsNullptrForInvalidIndex_670) {

    const GooString* name = catalog->getJSName(-1);

    EXPECT_EQ(name, nullptr);



    name = catalog->getJSName(catalog->numJS());

    EXPECT_EQ(name, nullptr);

}



TEST_F(CatalogTest_670, GetOptContentConfig_ReturnsNonNullOCGsPointer_670) {

    const OCGs* optContentConfig = catalog->getOptContentConfig();

    EXPECT_NE(optContentConfig, nullptr);

}



TEST_F(CatalogTest_670, GetPDFMajorVersion_ReturnsNonNegativeNumber_670) {

    int majorVersion = catalog->getPDFMajorVersion();

    EXPECT_GE(majorVersion, 0);

}



TEST_F(CatalogTest_670, GetPDFMinorVersion_ReturnsNonNegativeNumber_670) {

    int minorVersion = catalog->getPDFMinorVersion();

    EXPECT_GE(minorVersion, 0);

}
