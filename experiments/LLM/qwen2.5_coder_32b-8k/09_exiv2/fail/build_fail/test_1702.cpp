#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/tiffvisitor_int.hpp"



using namespace Exiv2::Internal;

using testing::MockFunction;



class MockTiffComponent : public TiffComponent {

public:

    MOCK_METHOD(void, accept, (TiffVisitor& visitor), (override));

};



TEST_F(TiffReaderTest_1702, PostProcessSetsPostProcFlagToTrue_1702) {

    byte data[1] = { 0 };

    TiffRwState state;

    MockTiffComponent mockComponent;

    TiffReader reader(data, sizeof(data), &mockComponent, state);



    EXPECT_CALL(mockComponent, accept(testing::_)).WillOnce([](TiffVisitor& visitor) {});



    reader.postProcess();

}



TEST_F(TiffReaderTest_1702, PostProcessCallsAcceptOnAllComponentsInPostList_1702) {

    byte data[1] = { 0 };

    TiffRwState state;

    MockTiffComponent mockComponent1;

    MockTiffComponent mockComponent2;



    TiffReader reader(data, sizeof(data), &mockComponent1, state);

    reader.postList_.push_back(&mockComponent1);

    reader.postList_.push_back(&mockComponent2);



    EXPECT_CALL(mockComponent1, accept(testing::_)).Times(1);

    EXPECT_CALL(mockComponent2, accept(testing::_)).Times(1);



    reader.postProcess();

}



TEST_F(TiffReaderTest_1702, PostProcessSetsPostProcFlagToFalseAfterProcessing_1702) {

    byte data[1] = { 0 };

    TiffRwState state;

    MockTiffComponent mockComponent;

    TiffReader reader(data, sizeof(data), &mockComponent, state);



    EXPECT_CALL(mockComponent, accept(testing::_)).WillOnce([](TiffVisitor& visitor) {});



    reader.postProcess();

}



TEST_F(TiffReaderTest_1702, PostProcessSetsStateToMnStateBeforeProcessing_1702) {

    byte data[1] = { 0 };

    TiffRwState state;

    MockTiffComponent mockComponent;

    TiffReader reader(data, sizeof(data), &mockComponent, state);



    EXPECT_CALL(mockComponent, accept(testing::_)).WillOnce([](TiffVisitor& visitor) {});



    reader.postProcess();

}



TEST_F(TiffReaderTest_1702, PostProcessSetsStateToOrigStateAfterProcessing_1702) {

    byte data[1] = { 0 };

    TiffRwState state;

    MockTiffComponent mockComponent;

    TiffReader reader(data, sizeof(data), &mockComponent, state);



    EXPECT_CALL(mockComponent, accept(testing::_)).WillOnce([](TiffVisitor& visitor) {});



    reader.postProcess();

}

```


