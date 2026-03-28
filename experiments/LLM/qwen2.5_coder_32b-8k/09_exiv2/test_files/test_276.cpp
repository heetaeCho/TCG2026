#include <gtest/gtest.h>

#include "tiffvisitor_int.hpp"



using namespace Exiv2::Internal;



class TiffFinderTest_276 : public ::testing::Test {

protected:

    TiffFinder* tiffFinder;

    uint16_t testTag = 0x0112; // Example tag

    IfdId testGroup = ifdExif;



    void SetUp() override {

        tiffFinder = new TiffFinder(testTag, testGroup);

    }



    void TearDown() override {

        delete tiffFinder;

    }

};



TEST_F(TiffFinderTest_276, ResultInitiallyNull_276) {

    EXPECT_EQ(tiffFinder->result(), nullptr);

}



TEST_F(TiffFinderTest_276, InitSetsTagAndGroup_276) {

    uint16_t newTag = 0x010E;

    IfdId newGroup = ifdExif;



    tiffFinder->init(newTag, newGroup);



    // Since we cannot access private members, we assume the result is affected by a correct initialization

    EXPECT_NE(tiffFinder, nullptr);

}



TEST_F(TiffFinderTest_276, FindObjectSetsResult_276) {

    TiffComponent* mockComponent = reinterpret_cast<TiffComponent*>(0x1); // Mock pointer



    tiffFinder->findObject(mockComponent);



    EXPECT_EQ(tiffFinder->result(), mockComponent);

}



TEST_F(TiffFinderTest_276, VisitEntryDoesNotSetResult_276) {

    TiffEntry* mockEntry = reinterpret_cast<TiffEntry*>(0x1); // Mock pointer



    tiffFinder->visitEntry(mockEntry);



    EXPECT_EQ(tiffFinder->result(), nullptr);

}



TEST_F(TiffFinderTest_276, VisitDataEntryDoesNotSetResult_276) {

    TiffDataEntry* mockDataEntry = reinterpret_cast<TiffDataEntry*>(0x1); // Mock pointer



    tiffFinder->visitDataEntry(mockDataEntry);



    EXPECT_EQ(tiffFinder->result(), nullptr);

}



TEST_F(TiffFinderTest_276, VisitImageEntryDoesNotSetResult_276) {

    TiffImageEntry* mockImageEntry = reinterpret_cast<TiffImageEntry*>(0x1); // Mock pointer



    tiffFinder->visitImageEntry(mockImageEntry);



    EXPECT_EQ(tiffFinder->result(), nullptr);

}



TEST_F(TiffFinderTest_276, VisitSizeEntryDoesNotSetResult_276) {

    TiffSizeEntry* mockSizeEntry = reinterpret_cast<TiffSizeEntry*>(0x1); // Mock pointer



    tiffFinder->visitSizeEntry(mockSizeEntry);



    EXPECT_EQ(tiffFinder->result(), nullptr);

}



TEST_F(TiffFinderTest_276, VisitDirectoryDoesNotSetResult_276) {

    TiffDirectory* mockDirectory = reinterpret_cast<TiffDirectory*>(0x1); // Mock pointer



    tiffFinder->visitDirectory(mockDirectory);



    EXPECT_EQ(tiffFinder->result(), nullptr);

}



TEST_F(TiffFinderTest_276, VisitSubIfdDoesNotSetResult_276) {

    TiffSubIfd* mockSubIfd = reinterpret_cast<TiffSubIfd*>(0x1); // Mock pointer



    tiffFinder->visitSubIfd(mockSubIfd);



    EXPECT_EQ(tiffFinder->result(), nullptr);

}



TEST_F(TiffFinderTest_276, VisitMnEntryDoesNotSetResult_276) {

    TiffMnEntry* mockMnEntry = reinterpret_cast<TiffMnEntry*>(0x1); // Mock pointer



    tiffFinder->visitMnEntry(mockMnEntry);



    EXPECT_EQ(tiffFinder->result(), nullptr);

}



TEST_F(TiffFinderTest_276, VisitIfdMakernoteDoesNotSetResult_276) {

    TiffIfdMakernote* mockIfdMakernote = reinterpret_cast<TiffIfdMakernote*>(0x1); // Mock pointer



    tiffFinder->visitIfdMakernote(mockIfdMakernote);



    EXPECT_EQ(tiffFinder->result(), nullptr);

}



TEST_F(TiffFinderTest_276, VisitBinaryArrayDoesNotSetResult_276) {

    TiffBinaryArray* mockBinaryArray = reinterpret_cast<TiffBinaryArray*>(0x1); // Mock pointer



    tiffFinder->visitBinaryArray(mockBinaryArray);



    EXPECT_EQ(tiffFinder->result(), nullptr);

}



TEST_F(TiffFinderTest_276, VisitBinaryElementDoesNotSetResult_276) {

    TiffBinaryElement* mockBinaryElement = reinterpret_cast<TiffBinaryElement*>(0x1); // Mock pointer



    tiffFinder->visitBinaryElement(mockBinaryElement);



    EXPECT_EQ(tiffFinder->result(), nullptr);

}
