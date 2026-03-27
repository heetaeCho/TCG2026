#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"

#include "tiffvisitor_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::NiceMock;



class MockTiffVisitor : public TiffVisitor {

public:

    MOCK_METHOD(void, visitEntry, (TiffEntry*), (override));

    MOCK_METHOD(void, visitDataEntry, (TiffDataEntry*), (override));

    MOCK_METHOD(void, visitImageEntry, (TiffImageEntry*), (override));

    MOCK_METHOD(void, visitSizeEntry, (TiffSizeEntry*), (override));

    MOCK_METHOD(void, visitDirectory, (TiffDirectory*), (override));

    MOCK_METHOD(void, visitDirectoryNext, (TiffDirectory*), (override));

    MOCK_METHOD(void, visitDirectoryEnd, (TiffDirectory*), (override));

    MOCK_METHOD(void, visitSubIfd, (TiffSubIfd*), (override));

    MOCK_METHOD(void, visitMnEntry, (TiffMnEntry*), (override));

    MOCK_METHOD(void, visitIfdMakernote, (TiffIfdMakernote*), (override));

    MOCK_METHOD(void, visitIfdMakernoteEnd, (TiffIfdMakernote*), (override));

    MOCK_METHOD(void, visitBinaryArray, (TiffBinaryArray*), (override));

    MOCK_METHOD(void, visitBinaryArrayEnd, (TiffBinaryArray*), (override));

    MOCK_METHOD(void, visitBinaryElement, (TiffBinaryElement*), (override));

};



class TiffComponentTest_337 : public ::testing::Test {

protected:

    TiffComponent component{123, IfdId::ifd0};

};



TEST_F(TiffComponentTest_337, AcceptCallsDoAcceptWhenGoTraverseIsTrue_337) {

    NiceMock<MockTiffVisitor> visitor;

    EXPECT_CALL(visitor, go(TiffVisitor::geTraverse)).WillOnce(::testing::Return(true));

    EXPECT_CALL(visitor, visitEntry(_)).Times(0);

    EXPECT_CALL(visitor, visitDataEntry(_)).Times(0);

    EXPECT_CALL(visitor, visitImageEntry(_)).Times(0);

    EXPECT_CALL(visitor, visitSizeEntry(_)).Times(0);

    EXPECT_CALL(visitor, visitDirectory(_)).Times(0);

    EXPECT_CALL(visitor, visitDirectoryNext(_)).Times(0);

    EXPECT_CALL(visitor, visitDirectoryEnd(_)).Times(0);

    EXPECT_CALL(visitor, visitSubIfd(_)).Times(0);

    EXPECT_CALL(visitor, visitMnEntry(_)).Times(0);

    EXPECT_CALL(visitor, visitIfdMakernote(_)).Times(0);

    EXPECT_CALL(visitor, visitIfdMakernoteEnd(_)).Times(0);

    EXPECT_CALL(visitor, visitBinaryArray(_)).Times(0);

    EXPECT_CALL(visitor, visitBinaryArrayEnd(_)).Times(0);

    EXPECT_CALL(visitor, visitBinaryElement(_)).Times(0);



    component.accept(visitor);

}



TEST_F(TiffComponentTest_337, AcceptDoesNotCallDoAcceptWhenGoTraverseIsFalse_337) {

    NiceMock<MockTiffVisitor> visitor;

    EXPECT_CALL(visitor, go(TiffVisitor::geTraverse)).WillOnce(::testing::Return(false));

    EXPECT_CALL(visitor, visitEntry(_)).Times(0);

    EXPECT_CALL(visitor, visitDataEntry(_)).Times(0);

    EXPECT_CALL(visitor, visitImageEntry(_)).Times(0);

    EXPECT_CALL(visitor, visitSizeEntry(_)).Times(0);

    EXPECT_CALL(visitor, visitDirectory(_)).Times(0);

    EXPECT_CALL(visitor, visitDirectoryNext(_)).Times(0);

    EXPECT_CALL(visitor, visitDirectoryEnd(_)).Times(0);

    EXPECT_CALL(visitor, visitSubIfd(_)).Times(0);

    EXPECT_CALL(visitor, visitMnEntry(_)).Times(0);

    EXPECT_CALL(visitor, visitIfdMakernote(_)).Times(0);

    EXPECT_CALL(visitor, visitIfdMakernoteEnd(_)).Times(0);

    EXPECT_CALL(visitor, visitBinaryArray(_)).Times(0);

    EXPECT_CALL(visitor, visitBinaryArrayEnd(_)).Times(0);

    EXPECT_CALL(visitor, visitBinaryElement(_)).Times(0);



    component.accept(visitor);

}
