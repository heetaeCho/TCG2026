#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/tiffvisitor_int.hpp"

#include "./TestProjects/exiv2/src/tiffcomposite_int.hpp"



using namespace Exiv2::Internal;

using ::testing::MockFunction;



class MockTiffSubIfd : public TiffSubIfd {

public:

    MockTiffSubIfd(uint16_t tag, IfdId group, IfdId newGroup) : TiffSubIfd(tag, group, newGroup) {}



    MOCK_METHOD(void, doAccept, (TiffVisitor& visitor), (override));

};



class TiffEncoderTest_1673 : public ::testing::Test {

protected:

    MockFunction<void(TiffComponent*)> mockEncodeTiffComponent;

    TiffSubIfd* subIfd;

    TiffEncoder encoder;



    void SetUp() override {

        subIfd = new MockTiffSubIfd(0x1234, ifdExif, ifdGps);

        EXPECT_CALL(*subIfd, doAccept(::testing::_))

            .WillOnce(::testing::Invoke([this](TiffVisitor& visitor) {

                encoder.encodeTiffComponent(subIfd, nullptr);

            }));

    }



    void TearDown() override {

        delete subIfd;

    }

};



TEST_F(TiffEncoderTest_1673, VisitSubIfdCallsDoAccept_1673) {

    EXPECT_CALL(*subIfd, doAccept(::testing::_)).Times(1);

    encoder.visitSubIfd(subIfd);

}



TEST_F(TiffEncoderTest_1673, EncodeTiffComponentCalledOnVisit_1673) {

    EXPECT_CALL(mockEncodeTiffComponent, Call(subIfd));

    encoder.visitSubIfd(subIfd);

}
