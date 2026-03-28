// ReporterConfigTests_112.cpp
#include <gtest/gtest.h>
#include <map>
#include <string>

// Include the real interface under test
#include "catch2/interfaces/catch_interfaces_reporter.hpp"

using namespace Catch;

class ReporterConfigTest_112 : public ::testing::Test {};

// [Normal] fullConfig returns exactly what was provided (nullptr case is still observable)
TEST_F(ReporterConfigTest_112, FullConfig_ReturnsNullptrWhenConstructedWithNull_112) {
    ReporterConfig cfg(
        /*_fullConfig*/ nullptr,
        /*_stream*/ Detail::unique_ptr<IStream>{},
        /*colourMode*/ static_cast<ColourMode>(0),
        /*customOptions*/ {}
    );

    const IConfig* got = cfg.fullConfig();
    EXPECT_EQ(got, nullptr);
}

// [Normal] colourMode echoes the value provided to the ctor
TEST_F(ReporterConfigTest_112, ColourMode_IsPropagated_112) {
    auto mode = static_cast<ColourMode>(2);

    ReporterConfig cfg(
        nullptr,
        Detail::unique_ptr<IStream>{},
        mode,
        {}
    );

    EXPECT_EQ(cfg.colourMode(), mode);
}

// [Normal] customOptions exposes the provided key/value pairs (read-only)
TEST_F(ReporterConfigTest_112, CustomOptions_ExposesProvidedMap_112) {
    std::map<std::string, std::string> opts{
        {"k1", "v1"},
        {"k2", "v2"}
    };

    ReporterConfig cfg(
        nullptr,
        Detail::unique_ptr<IStream>{},
        static_cast<ColourMode>(1),
        opts
    );

    const auto& got = cfg.customOptions();
    ASSERT_EQ(got.size(), 2u);
    EXPECT_EQ(got.at("k1"), "v1");
    EXPECT_EQ(got.at("k2"), "v2");
}

// [Boundary] takeStream on object constructed with null stream returns null (rvalue-qualified API)
TEST_F(ReporterConfigTest_112, TakeStream_ReturnsNullUniquePtrWhenConstructedWithNull_112) {
    ReporterConfig cfg(
        nullptr,
        Detail::unique_ptr<IStream>{}, // null
        static_cast<ColourMode>(0),
        {}
    );

    auto streamUp = std::move(cfg).takeStream();
    EXPECT_FALSE(static_cast<bool>(streamUp)); // nullptr unique_ptr
}

// [Boundary] Move-constructing ReporterConfig preserves observable state (except moved-from)
TEST_F(ReporterConfigTest_112, MoveConstruction_PreservesObservableState_112) {
    ReporterConfig a(
        nullptr,
        Detail::unique_ptr<IStream>{}, // keeping stream null to avoid depending on IStream impl
        static_cast<ColourMode>(5),
        {{"a", "b"}}
    );

    ReporterConfig b(std::move(a));

    // Verify observable getters on the moved-to object
    EXPECT_EQ(b.fullConfig(), nullptr);
    EXPECT_EQ(b.colourMode(), static_cast<ColourMode>(5));
    const auto& opts = b.customOptions();
    ASSERT_EQ(opts.size(), 1u);
    EXPECT_EQ(opts.at("a"), "b");
}

// [Exceptional-ish/Edge] Methods are const-correct and callable on const instances
TEST_F(ReporterConfigTest_112, ConstCorrectness_GettersCallableOnConst_112) {
    const ReporterConfig cfg(
        nullptr,
        Detail::unique_ptr<IStream>{},
        static_cast<ColourMode>(3),
        {{"x", "y"}}
    );

    // All getters are const-qualified in the interface
    EXPECT_EQ(cfg.fullConfig(), nullptr);
    EXPECT_EQ(cfg.colourMode(), static_cast<ColourMode>(3));
    const auto& co = cfg.customOptions();
    EXPECT_EQ(co.at("x"), "y");
}
