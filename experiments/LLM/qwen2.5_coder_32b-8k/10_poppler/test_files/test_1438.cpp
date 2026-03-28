#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mocking external dependencies

class MockPartialUpdateCallback {

public:

    MOCK_METHOD2(call, void(QImage&, int*));

};



// Test fixture for QImageDumpingQPainterOutputDev

class QImageDumpingQPainterOutputDevTest_1438 : public ::testing::Test {

protected:

    QImage image;

    int payload = 0;

    MockPartialUpdateCallback mockCallback;



    Poppler::QImageDumpingQPainterOutputDev* outputDev;



    void SetUp() override {

        QPainter painter(&image);

        outputDev = new Poppler::QImageDumpingQPainterOutputDev(&painter, &image);

        outputDev->setPartialUpdateCallback([this](QImage& img, int* p) { mockCallback.call(img, p); });

    }



    void TearDown() override {

        delete outputDev;

    }

};



// Test case: Normal operation with partial update callback

TEST_F(QImageDumpingQPainterOutputDevTest_1438, DumpCallsPartialUpdateCallbackWhenConditionMet_1438) {

    // Arrange

    bool shouldDoPartialUpdateCallback = true;

    outputDev->setShouldDoPartialUpdateCallback(shouldDoPartialUpdateCallback);



    EXPECT_CALL(mockCallback, call(::testing::Ref(image), ::testing::Pointee(payload)));



    // Act

    outputDev->dump();

}



// Test case: Normal operation without partial update callback

TEST_F(QImageDumpingQPainterOutputDevTest_1438, DumpDoesNotCallPartialUpdateCallbackWhenConditionNotMet_1438) {

    // Arrange

    bool shouldDoPartialUpdateCallback = false;

    outputDev->setShouldDoPartialUpdateCallback(shouldDoPartialUpdateCallback);



    EXPECT_CALL(mockCallback, call(::testing::Ref(image), ::testing::Pointee(payload))).Times(0);



    // Act

    outputDev->dump();

}



// Test case: Boundary condition with payload

TEST_F(QImageDumpingQPainterOutputDevTest_1438, DumpCallsPartialUpdateCallbackWithBoundaryPayloadValue_1438) {

    // Arrange

    bool shouldDoPartialUpdateCallback = true;

    int boundaryPayload = std::numeric_limits<int>::max();

    outputDev->setShouldDoPartialUpdateCallback(shouldDoPartialUpdateCallback);

    payload = boundaryPayload;



    EXPECT_CALL(mockCallback, call(::testing::Ref(image), ::testing::Pointee(boundaryPayload)));



    // Act

    outputDev->dump();

}



// Test case: Exceptional case with nullptr image (assuming this is an error condition)

TEST_F(QImageDumpingQPainterOutputDevTest_1438, DumpDoesNotCrashWithNullImagePointer_1438) {

    // Arrange

    bool shouldDoPartialUpdateCallback = true;

    outputDev->setShouldDoPartialUpdateCallback(shouldDoPartialUpdateCallback);

    outputDev->setImage(nullptr);



    EXPECT_CALL(mockCallback, call(::testing::Ref(image), ::testing::Pointee(payload))).Times(0);



    // Act & Assert (Expect no crash)

    outputDev->dump();

}



// Test case: Exceptional case with nullptr payload (assuming this is an error condition)

TEST_F(QImageDumpingQPainterOutputDevTest_1438, DumpDoesNotCrashWithNullPayloadPointer_1438) {

    // Arrange

    bool shouldDoPartialUpdateCallback = true;

    outputDev->setShouldDoPartialUpdateCallback(shouldDoPartialUpdateCallback);

    payload = 0;

    outputDev->setPayload(nullptr);



    EXPECT_CALL(mockCallback, call(::testing::Ref(image), ::testing::Pointee(payload))).Times(0);



    // Act & Assert (Expect no crash)

    outputDev->dump();

}
