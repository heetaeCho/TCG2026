#include <gtest/gtest.h>

#include <gmock/gmock.h>



namespace Exiv2 {

    class BasicIo {

    public:

        virtual void close() = 0;

    };



    class IoCloser {

    public:

        BasicIo & bio_;

        explicit IoCloser(BasicIo& bio) : bio_(bio) {}

        virtual ~IoCloser();

        void close();

    };

}



using namespace Exiv2;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(void, close, (), (override));

};



class IoCloserTest_60 : public ::testing::Test {

protected:

    std::unique_ptr<MockBasicIo> mock_bio_;

    IoCloser* io_closer_;



    void SetUp() override {

        mock_bio_ = std::make_unique<MockBasicIo>();

        io_closer_ = new IoCloser(*mock_bio_);

    }



    void TearDown() override {

        delete io_closer_;

    }

};



TEST_F(IoCloserTest_60, DestructorCallsClose_60) {

    EXPECT_CALL(*mock_bio_, close()).Times(1);

}



TEST_F(IoCloserTest_60, ExplicitCloseCallsCloseOnce_60) {

    EXPECT_CALL(*mock_bio_, close()).WillOnce(::testing::Return());

    io_closer_->close();

}
