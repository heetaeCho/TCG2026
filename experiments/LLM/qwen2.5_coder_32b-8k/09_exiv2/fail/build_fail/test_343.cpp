#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"

#include "tiffvisitor_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;



class MockTiffVisitor : public TiffVisitor {

public:

    MOCK_METHOD(void, visitSubIfd, (TiffSubIfd*), (override));

};



class TiffSubIfdTest_343 : public testing::Test {

protected:

    void SetUp() override {

        subIfd = std::make_unique<TiffSubIfd>(0x123, IfdId::rootIFD, IfdId::exifIFD);

    }



    std::unique_ptr<TiffSubIfd> subIfd;

    MockTiffVisitor mockVisitor;

};



TEST_F(TiffSubIfdTest_343, DoAcceptCallsVisitSubIfd_343) {

    EXPECT_CALL(mockVisitor, visitSubIfd(subIfd.get())).Times(1);

    subIfd->doAccept(mockVisitor);

}



TEST_F(TiffSubIfdTest_343, DoAcceptDoesNotTraverseWhenGoIsFalse_343) {

    mockVisitor.setGo(GoEvent::geTraverse, false);

    EXPECT_CALL(mockVisitor, visitSubIfd(subIfd.get())).Times(1);

    EXPECT_CALL(mockVisitor, go(GoEvent::geTraverse)).WillOnce(testing::Return(false));

    subIfd->doAccept(mockVisitor);

}



TEST_F(TiffSubIfdTest_343, DoAcceptCallsAcceptOnChildIfds_343) {

    auto child = std::make_unique<TiffComponent>(0x124, IfdId::rootIFD);

    subIfd->addChild(std::move(child));



    EXPECT_CALL(mockVisitor, visitSubIfd(subIfd.get())).Times(1);

    EXPECT_CALL(*subIfd->ifds_.front(), accept(_)).Times(1);



    subIfd->doAccept(mockVisitor);

}



TEST_F(TiffSubIfdTest_343, DoAcceptStopsTraversalWhenGoIsFalseAfterFirstVisit_343) {

    auto child = std::make_unique<TiffComponent>(0x124, IfdId::rootIFD);

    subIfd->addChild(std::move(child));



    mockVisitor.setGo(GoEvent::geTraverse, false);



    EXPECT_CALL(mockVisitor, visitSubIfd(subIfd.get())).Times(1);

    EXPECT_CALL(*subIfd->ifds_.front(), accept(_)).WillOnce([](TiffVisitor& visitor) {

        visitor.setGo(TiffVisitor::GoEvent::geTraverse, false);

    });

    EXPECT_CALL(mockVisitor, go(GoEvent::geTraverse)).WillOnce(testing::Return(true))

                                                   .WillOnce(testing::Return(false));



    subIfd->doAccept(mockVisitor);

}
