#include <gtest/gtest.h>

#include <gmock/gmock.h>



using namespace re2;



class ProgMock : public Prog {

public:

    MOCK_METHOD(int, start, (), (const));

    MOCK_METHOD(Inst*, inst, (int id), (const));

};



class FanoutTest_579 : public ::testing::Test {

protected:

    void SetUp() override {

        mock_prog = new NiceMock<ProgMock>();

        fanout.reset(new SparseArray<int>(mock_prog->size()));

    }



    void TearDown() override {

        delete mock_prog;

    }



    ProgMock* mock_prog;

    std::unique_ptr<SparseArray<int>> fanout;

};



TEST_F(FanoutTest_579, NormalOperation_579) {

    EXPECT_CALL(*mock_prog, start()).WillOnce(::testing::Return(0));

    EXPECT_CALL(*mock_prog, inst(0))

        .WillOnce(::testing::Invoke([](int id) -> Inst* {

            static Inst inst;

            inst.InitByteRange('a', 'z', 0, 1);

            return &inst;

        }));

    EXPECT_CALL(*mock_prog, inst(1))

        .WillOnce(::testing::Invoke([](int id) -> Inst* {

            static Inst inst;

            inst.InitMatch(0);

            return &inst;

        }));



    mock_prog->Fanout(fanout.get());



    EXPECT_EQ(fanout->has_index(0), true);

    EXPECT_EQ(fanout->get_existing(0), 1);

}



TEST_F(FanoutTest_579, BoundaryConditions_579) {

    EXPECT_CALL(*mock_prog, start()).WillOnce(::testing::Return(0));

    EXPECT_CALL(*mock_prog, inst(0))

        .WillOnce(::testing::Invoke([](int id) -> Inst* {

            static Inst inst;

            inst.InitByteRange('a', 'z', 0, 1);

            return &inst;

        }));



    mock_prog->Fanout(fanout.get());



    EXPECT_EQ(fanout->has_index(0), true);

    EXPECT_EQ(fanout->get_existing(0), 1);

}



TEST_F(FanoutTest_579, ExceptionalCases_579) {

    // Since the function does not throw exceptions based on provided information,

    // we cannot test exceptional cases directly. However, we can test for edge cases.

    EXPECT_CALL(*mock_prog, start()).WillOnce(::testing::Return(0));

    EXPECT_CALL(*mock_prog, inst(0))

        .WillOnce(::testing::Invoke([](int id) -> Inst* {

            static Inst inst;

            inst.InitFail();

            return &inst;

        }));



    mock_prog->Fanout(fanout.get());



    EXPECT_EQ(fanout->has_index(0), true);

    EXPECT_EQ(fanout->get_existing(0), 0); // No increment for kInstFail

}



TEST_F(FanoutTest_579, ExternalInteractions_579) {

    EXPECT_CALL(*mock_prog, start()).WillOnce(::testing::Return(0));

    EXPECT_CALL(*mock_prog, inst(0))

        .WillOnce(::testing::Invoke([](int id) -> Inst* {

            static Inst inst;

            inst.InitByteRange('a', 'z', 0, 1);

            return &inst;

        }));

    EXPECT_CALL(*mock_prog, inst(1))

        .WillOnce(::testing::Invoke([](int id) -> Inst* {

            static Inst inst;

            inst.InitMatch(0);

            return &inst;

        }));



    mock_prog->Fanout(fanout.get());



    EXPECT_EQ(fanout->has_index(0), true);

    EXPECT_EQ(fanout->get_existing(0), 1);

}
