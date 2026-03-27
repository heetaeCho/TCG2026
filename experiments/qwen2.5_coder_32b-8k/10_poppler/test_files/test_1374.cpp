#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <poppler-form.h>



namespace Poppler {



class CryptoSignBackend {

public:

    virtual ~CryptoSignBackend() = default;

};



namespace CryptoSign {



class Factory {

public:

    static QVector<CryptoSignBackend*> getAvailable();

};



} // namespace CryptoSign



namespace {



QVector<CryptoSignBackend> convertToFrontend(CryptoSignBackend* backend) {

    if (backend) {

        return { *backend };

    }

    return {};

}



TEST(availableCryptoSignBackendsTest_1374, NoBackendsAvailable_1374) {

    EXPECT_CALL(MockCryptoSignFactory(), getAvailable()).WillOnce(testing::Return(QVector<CryptoSignBackend*>()));

    QVector<CryptoSignBackend> backends = availableCryptoSignBackends();

    EXPECT_TRUE(backends.isEmpty());

}



TEST(availableCryptoSignBackendsTest_1374, SingleBackendAvailable_1374) {

    auto mockBackend = std::make_unique<testing::NiceMock<CryptoSignBackend>>();

    EXPECT_CALL(MockCryptoSignFactory(), getAvailable()).WillOnce(testing::Return(QVector<CryptoSignBackend*>{ mockBackend.get() }));

    QVector<CryptoSignBackend> backends = availableCryptoSignBackends();

    EXPECT_EQ(backends.size(), 1);

}



TEST(availableCryptoSignBackendsTest_1374, MultipleBackendsAvailable_1374) {

    auto mockBackend1 = std::make_unique<testing::NiceMock<CryptoSignBackend>>();

    auto mockBackend2 = std::make_unique<testing::NiceMock<CryptoSignBackend>>();

    QVector<CryptoSignBackend*> availableBackends{ mockBackend1.get(), mockBackend2.get() };

    EXPECT_CALL(MockCryptoSignFactory(), getAvailable()).WillOnce(testing::Return(availableBackends));

    QVector<CryptoSignBackend> backends = availableCryptoSignBackends();

    EXPECT_EQ(backends.size(), 2);

}



TEST(availableCryptoSignBackendsTest_1374, ConvertToFrontendFails_1374) {

    auto mockBackend = std::make_unique<testing::NiceMock<CryptoSignBackend>>();

    EXPECT_CALL(MockCryptoSignFactory(), getAvailable()).WillOnce(testing::Return(QVector<CryptoSignBackend*>{ nullptr }));

    QVector<CryptoSignBackend> backends = availableCryptoSignBackends();

    EXPECT_TRUE(backends.isEmpty());

}



} // namespace



class MockCryptoSignFactory : public CryptoSign::Factory {

public:

    MOCK_STATIC_METHOD0(getAvailable, QVector<CryptoSignBackend*>());

};



}

```



Note: The above code assumes the use of `testing::NiceMock` for creating mock objects and `MOCK_STATIC_METHOD0` from Google Mock to mock static methods. However, as of the latest stable version (v1.13.0), Google Mock does not support mocking static methods directly. To work around this limitation, you would typically refactor your code to use dependency injection or provide an interface for the factory that can be mocked.


