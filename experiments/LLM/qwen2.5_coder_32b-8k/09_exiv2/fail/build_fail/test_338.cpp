#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/tiffcomposite_int.hpp"

#include "./TestProjects/exiv2/src/tiffvisitor_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;



class MockTiffVisitor : public TiffVisitor {

public:

    MOCK_METHOD(void, visitEntry, (TiffEntry* object), (override));

};



class TiffEntryTest_338 : public ::testing::Test {

protected:

    std::unique_ptr<TiffEntry> tiffEntry;

    MockTiffVisitor mockVisitor;



    void SetUp() override {

        tiffEntry = std::make_unique<TiffEntry>();

    }

};



TEST_F(TiffEntryTest_338, DoAcceptCallsVisitEntry_338) {

    EXPECT_CALL(mockVisitor, visitEntry(_)).Times(1);

    tiffEntry->doAccept(mockVisitor);

}



// Additional test cases can be added if there are other public functions or observable behaviors

// to test based on the provided interface.



TEST_F(TiffEntryTest_338, DoAcceptDoesNotCallOtherVisitMethods_338) {

    EXPECT_CALL(mockVisitor, visitDataEntry(_)).Times(0);

    EXPECT_CALL(mockVisitor, visitImageEntry(_)).Times(0);

    EXPECT_CALL(mockVisitor, visitSizeEntry(_)).Times(0);

    EXPECT_CALL(mockVisitor, visitDirectory(_)).Times(0);

    EXPECT_CALL(mockVisitor, visitDirectoryNext(_)).Times(0);

    EXPECT_CALL(mockVisitor, visitDirectoryEnd(_)).Times(0);

    EXPECT_CALL(mockVisitor, visitSubIfd(_)).Times(0);

    EXPECT_CALL(mockVisitor, visitMnEntry(_)).Times(0);

    EXPECT_CALL(mockVisitor, visitIfdMakernote(_)).Times(0);

    EXPECT_CALL(mockVisitor, visitIfdMakernoteEnd(_)).Times(0);

    EXPECT_CALL(mockVisitor, visitBinaryArray(_)).Times(0);

    EXPECT_CALL(mockVisitor, visitBinaryArrayEnd(_)).Times(0);

    EXPECT_CALL(mockVisitor, visitBinaryElement(_)).Times(0);



    tiffEntry->doAccept(mockVisitor);

}
