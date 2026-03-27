#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/qt5/src/poppler-page.cc"

using namespace Poppler;

class MockCallback {
public:
    MOCK_METHOD(void, call, (const QImage &image, const int &payload), ());
};

class QImageDumpingQPainterOutputDevTest : public ::testing::Test {
protected:
    QImageDumpingQPainterOutputDevTest() : mockCallback(new MockCallback()), 
                                           painter(nullptr), image(nullptr), dev(painter, image) {}

    MockCallback* mockCallback;
    QPainter* painter;
    QImage* image;
    QImageDumpingQPainterOutputDev dev;
};

TEST_F(QImageDumpingQPainterOutputDevTest, DumpCallsCallbackWhenConditionsMet_1438) {
    // Arrange
    int payload = 123;
    dev.partialUpdateCallback = [this](const QImage &img, const int &pld) {
        mockCallback->call(img, pld);
        return true;
    };
    dev.shouldDoPartialUpdateCallback = true;
    
    // Expect the callback to be called with the correct parameters
    EXPECT_CALL(*mockCallback, call(testing::_, testing::_))
        .WillOnce(testing::Invoke([&](const QImage &img, const int &pld) {
            EXPECT_EQ(pld, payload);
        }));

    // Act
    dev.dump();
}

TEST_F(QImageDumpingQPainterOutputDevTest, DumpDoesNotCallCallbackWhenConditionFails_1439) {
    // Arrange
    int payload = 123;
    dev.partialUpdateCallback = [this](const QImage &img, const int &pld) {
        mockCallback->call(img, pld);
        return false; // Simulate failure condition
    };
    dev.shouldDoPartialUpdateCallback = true;
    
    // Expect the callback to NOT be called
    EXPECT_CALL(*mockCallback, call(testing::_, testing::_)).Times(0);

    // Act
    dev.dump();
}

TEST_F(QImageDumpingQPainterOutputDevTest, DumpHandlesNullImageGracefully_1440) {
    // Arrange
    dev.partialUpdateCallback = nullptr;
    dev.shouldDoPartialUpdateCallback = false;  // Disable the callback for this test
    
    // Act and Assert (no crash should happen)
    EXPECT_NO_THROW(dev.dump());
}

TEST_F(QImageDumpingQPainterOutputDevTest, DumpHandlesNullCallbackGracefully_1441) {
    // Arrange
    dev.partialUpdateCallback = nullptr;
    dev.shouldDoPartialUpdateCallback = true;  // Callback should be checked
    
    // Expect the callback NOT to be called (because it's null)
    EXPECT_CALL(*mockCallback, call(testing::_, testing::_)).Times(0);

    // Act
    dev.dump();
}

TEST_F(QImageDumpingQPainterOutputDevTest, DumpHandlesWhenPartialUpdateCallbackIsDisabled_1442) {
    // Arrange
    dev.partialUpdateCallback = [this](const QImage &img, const int &pld) {
        mockCallback->call(img, pld);
        return true;
    };
    dev.shouldDoPartialUpdateCallback = false;  // Callback disabled
    
    // Expect the callback NOT to be called
    EXPECT_CALL(*mockCallback, call(testing::_, testing::_)).Times(0);

    // Act
    dev.dump();
}