#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/crwimage_int.hpp"



namespace Exiv2 {

    namespace Internal {



        class CiffComponentTest_1770 : public ::testing::Test {

        protected:

            using UniquePtr = std::unique_ptr<CiffComponent>;

            CiffComponent component{1, 1};

        };



        TEST_F(CiffComponentTest_1770, AddComponent_ReturnsUniquePtrReference_1770) {

            auto newComponent = std::make_unique<CiffComponent>(2, 2);

            const auto& result = component.add(std::move(newComponent));

            EXPECT_NE(result.get(), nullptr);

        }



        TEST_F(CiffComponentTest_1770, AddNullComponent_ReturnsEmptyUniquePtrReference_1770) {

            UniquePtr newComponent = nullptr;

            const auto& result = component.add(std::move(newComponent));

            EXPECT_EQ(result.get(), nullptr);

        }



    } // namespace Internal

} // namespace Exiv2
