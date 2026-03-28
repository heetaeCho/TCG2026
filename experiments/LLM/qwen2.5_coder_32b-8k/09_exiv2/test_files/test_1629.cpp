#include <gtest/gtest.h>

#include "tiffvisitor_int.hpp"



namespace Exiv2 {

namespace Internal {



class TiffFinderTest : public ::testing::Test {

protected:

    TiffFinder tiffFinder;



    TiffFinderTest() : tiffFinder(0, IfdId()) {}



    void SetUp() override {

        // Initialization if needed

    }

};



TEST_F(TiffFinderTest_1629, InitSetsTagAndGroup_1629) {

    uint16_t testTag = 34675;

    IfdId testGroup = IfdId::rootIFD;



    tiffFinder.init(testTag, testGroup);



    EXPECT_EQ(tiffFinder.result(), nullptr);

}



TEST_F(TiffFinderTest_1629, InitSetsGoTraverseTrue_1629) {

    uint16_t testTag = 34675;

    IfdId testGroup = IfdId::rootIFD;



    tiffFinder.init(testTag, testGroup);



    EXPECT_TRUE(tiffFinder.go(TiffVisitor::geTraverse));

}



TEST_F(TiffFinderTest_1629, ResultReturnsNullInitially_1629) {

    EXPECT_EQ(tiffFinder.result(), nullptr);

}



// Assuming TiffComponent is a mockable class

class MockTiffComponent : public TiffComponent {

public:

    MOCK_METHOD(void, accept, (TiffVisitor&), (override));

};



TEST_F(TiffFinderTest_1629, FindObjectSetsResult_1629) {

    auto* mockComponent = new MockTiffComponent();

    tiffFinder.findObject(mockComponent);



    EXPECT_EQ(tiffFinder.result(), mockComponent);

}



TEST_F(TiffFinderTest_1629, VisitEntryCallsAccept_1629) {

    auto* mockComponent = new MockTiffComponent();

    EXPECT_CALL(*mockComponent, accept(::testing::_)).Times(1);



    tiffFinder.visitEntry(reinterpret_cast<TiffEntry*>(mockComponent));

}



TEST_F(TiffFinderTest_1629, VisitDataEntryCallsAccept_1629) {

    auto* mockComponent = new MockTiffComponent();

    EXPECT_CALL(*mockComponent, accept(::testing::_)).Times(1);



    tiffFinder.visitDataEntry(reinterpret_cast<TiffDataEntry*>(mockComponent));

}



TEST_F(TiffFinderTest_1629, VisitImageEntryCallsAccept_1629) {

    auto* mockComponent = new MockTiffComponent();

    EXPECT_CALL(*mockComponent, accept(::testing::_)).Times(1);



    tiffFinder.visitImageEntry(reinterpret_cast<TiffImageEntry*>(mockComponent));

}



TEST_F(TiffFinderTest_1629, VisitSizeEntryCallsAccept_1629) {

    auto* mockComponent = new MockTiffComponent();

    EXPECT_CALL(*mockComponent, accept(::testing::_)).Times(1);



    tiffFinder.visitSizeEntry(reinterpret_cast<TiffSizeEntry*>(mockComponent));

}



TEST_F(TiffFinderTest_1629, VisitDirectoryCallsAccept_1629) {

    auto* mockComponent = new MockTiffComponent();

    EXPECT_CALL(*mockComponent, accept(::testing::_)).Times(1);



    tiffFinder.visitDirectory(reinterpret_cast<TiffDirectory*>(mockComponent));

}



TEST_F(TiffFinderTest_1629, VisitSubIfdCallsAccept_1629) {

    auto* mockComponent = new MockTiffComponent();

    EXPECT_CALL(*mockComponent, accept(::testing::_)).Times(1);



    tiffFinder.visitSubIfd(reinterpret_cast<TiffSubIfd*>(mockComponent));

}



TEST_F(TiffFinderTest_1629, VisitMnEntryCallsAccept_1629) {

    auto* mockComponent = new MockTiffComponent();

    EXPECT_CALL(*mockComponent, accept(::testing::_)).Times(1);



    tiffFinder.visitMnEntry(reinterpret_cast<TiffMnEntry*>(mockComponent));

}



TEST_F(TiffFinderTest_1629, VisitIfdMakernoteCallsAccept_1629) {

    auto* mockComponent = new MockTiffComponent();

    EXPECT_CALL(*mockComponent, accept(::testing::_)).Times(1);



    tiffFinder.visitIfdMakernote(reinterpret_cast<TiffIfdMakernote*>(mockComponent));

}



TEST_F(TiffFinderTest_1629, VisitBinaryArrayCallsAccept_1629) {

    auto* mockComponent = new MockTiffComponent();

    EXPECT_CALL(*mockComponent, accept(::testing::_)).Times(1);



    tiffFinder.visitBinaryArray(reinterpret_cast<TiffBinaryArray*>(mockComponent));

}



TEST_F(TiffFinderTest_1629, VisitBinaryElementCallsAccept_1629) {

    auto* mockComponent = new MockTiffComponent();

    EXPECT_CALL(*mockComponent, accept(::testing::_)).Times(1);



    tiffFinder.visitBinaryElement(reinterpret_cast<TiffBinaryElement*>(mockComponent));

}



}  // namespace Internal

}  // namespace Exiv2
