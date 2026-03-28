#include <gtest/gtest.h>

#include <gmock/gmock.h>



namespace Exiv2 {

    class BasicIo;

    using UniquePtr = std::unique_ptr<BasicIo>;

    class Image {

    public:

        using UniquePtr = std::unique_ptr<Image>;

        virtual ~Image() = default;

        virtual bool good() const = 0;

    };



    class WebPImage : public Image {

    public:

        WebPImage(UniquePtr io) : io_(std::move(io)) {}

        bool good() const override { return true; } // Simplified for testing

    private:

        UniquePtr io_;

    };



    Image::UniquePtr newWebPInstance(BasicIo::UniquePtr io, bool /*create*/);

}



using namespace Exiv2;

using ::testing::NiceMock;

using ::testing::Return;



class MockBasicIo : public BasicIo {

public:

    MOCK_CONST_METHOD0(good, bool());

};



class WebPImageTest_72 : public ::testing::Test {

protected:

    std::unique_ptr<MockBasicIo> mock_io_;

    void SetUp() override {

        mock_io_ = std::make_unique<NiceMock<MockBasicIo>>();

    }

};



TEST_F(WebPImageTest_72, NewWebPInstanceReturnsNonNullWhenIoIsGood_72) {

    EXPECT_CALL(*mock_io_, good()).WillOnce(Return(true));

    auto image = newWebPInstance(std::move(mock_io_), false);

    ASSERT_NE(image, nullptr);

}



TEST_F(WebPImageTest_72, NewWebPInstanceReturnsNullWhenIoIsNotGood_72) {

    EXPECT_CALL(*mock_io_, good()).WillOnce(Return(false));

    auto image = newWebPInstance(std::move(mock_io_), false);

    ASSERT_EQ(image, nullptr);

}
