#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming TakeGenerator is part of a namespace that needs to be included

namespace Catch { namespace Generators {



class MockIGenerator : public IGenerator<int> {

public:

    MOCK_METHOD(bool, next, (), (override));

    MOCK_METHOD(int const&, get, (), (const, override));

};



TEST_F(TakeGeneratorTest_920, NormalOperation_920) {

    MockIGenerator mock_generator;

    EXPECT_CALL(mock_generator, next()).WillOnce(testing::Return(true))

                                       .WillOnce(testing::Return(false));

    EXPECT_CALL(mock_generator, get()).WillOnce(testing::ReturnRef(42));



    TakeGenerator<int> take_gen(1, GeneratorWrapper<int>(std::move(mock_generator)));



    ASSERT_TRUE(take_gen.next());

    EXPECT_EQ(take_gen.get(), 42);

    ASSERT_FALSE(take_gen.next());

}



TEST_F(TakeGeneratorTest_920, BoundaryCondition_ZeroTarget_920) {

    MockIGenerator mock_generator;

    TakeGenerator<int> take_gen(0, GeneratorWrapper<int>(std::move(mock_generator)));



    EXPECT_FALSE(take_gen.next());

}



TEST_F(TakeGeneratorTest_920, BoundaryCondition_OneElement_920) {

    MockIGenerator mock_generator;

    EXPECT_CALL(mock_generator, next()).WillOnce(testing::Return(true))

                                       .WillOnce(testing::Return(false));

    EXPECT_CALL(mock_generator, get()).WillOnce(testing::ReturnRef(42));



    TakeGenerator<int> take_gen(1, GeneratorWrapper<int>(std::move(mock_generator)));



    ASSERT_TRUE(take_gen.next());

    EXPECT_EQ(take_gen.get(), 42);

    ASSERT_FALSE(take_gen.next());

}



TEST_F(TakeGeneratorTest_920, MultipleElements_UnderTarget_920) {

    MockIGenerator mock_generator;

    EXPECT_CALL(mock_generator, next()).WillOnce(testing::Return(true))

                                       .WillOnce(testing::Return(true))

                                       .WillOnce(testing::Return(false));

    EXPECT_CALL(mock_generator, get()).WillOnce(testing::ReturnRef(42))

                                       .WillOnce(testing::ReturnRef(24));



    TakeGenerator<int> take_gen(3, GeneratorWrapper<int>(std::move(mock_generator)));



    ASSERT_TRUE(take_gen.next());

    EXPECT_EQ(take_gen.get(), 42);

    ASSERT_TRUE(take_gen.next());

    EXPECT_EQ(take_gen.get(), 24);

    ASSERT_FALSE(take_gen.next());

}



TEST_F(TakeGeneratorTest_920, MultipleElements_ExceedTarget_920) {

    MockIGenerator mock_generator;

    EXPECT_CALL(mock_generator, next()).WillOnce(testing::Return(true))

                                       .WillOnce(testing::Return(true))

                                       .WillOnce(testing::Return(true));

    EXPECT_CALL(mock_generator, get()).WillOnce(testing::ReturnRef(42))

                                       .WillOnce(testing::ReturnRef(24));



    TakeGenerator<int> take_gen(2, GeneratorWrapper<int>(std::move(mock_generator)));



    ASSERT_TRUE(take_gen.next());

    EXPECT_EQ(take_gen.get(), 42);

    ASSERT_TRUE(take_gen.next());

    EXPECT_EQ(take_gen.get(), 24);

    ASSERT_FALSE(take_gen.next());

}



} } // namespace Catch::Generators
