#include "protocol/metrics/influxdb/Point.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <locale>

namespace
{
const std::string measurementName{"dummyMeasurement"};
} // namespace

namespace protocol::metrics::influxdb
{
using namespace ::testing;

class PointTest : public Test
{
};

TEST_F(PointTest, toLineProtocol_shouldThrowIfNoFieldsAdded)
{
    Point sut{measurementName};
    EXPECT_THROW(sut.toLineProtocol(), std::runtime_error);
}

using SingleFieldParams = std::pair<Point::FieldValue, std::string>;
class ToLineProtocolWithSingleField : public PointTest, public WithParamInterface<SingleFieldParams>
{
};

TEST_P(ToLineProtocolWithSingleField, toLineProtocol_shouldSerializeMeasurementNameAndOneValue)
{
    const auto [value, expectedStr] = GetParam();
    Point sut{measurementName};
    sut.addField("val", value);
    EXPECT_THAT(sut.toLineProtocol(), MatchesRegex("dummyMeasurement val=" + expectedStr + " [0-9]+"));
}

INSTANTIATE_TEST_SUITE_P(
    ToLineProtocolWithSingleField,
    ToLineProtocolWithSingleField,
    Values(
        std::make_pair(Point::FieldValue{-420}, "-420"),
        std::make_pair(Point::FieldValue{0}, "0"),
        std::make_pair(Point::FieldValue{1}, "1"),
        std::make_pair(Point::FieldValue{0.0}, "0.000000"),
        std::make_pair(Point::FieldValue{46.2}, "46.200000"),
        std::make_pair(Point::FieldValue{0UL}, "0u"),
        std::make_pair(Point::FieldValue{2137UL}, "2137u"),
        std::make_pair(Point::FieldValue{""}, "\"\""),
        std::make_pair(Point::FieldValue{" "}, "\" \""),
        std::make_pair(Point::FieldValue{"test"}, "\"test\""),
        std::make_pair(Point::FieldValue{false}, "F"),
        std::make_pair(Point::FieldValue{true}, "T")));

TEST_F(PointTest, toLineProtocol_shouldSerializeFloatingPointRegardlessOfLocale)
{
    Point sut{measurementName};
    sut.addField("val", 46.2);
    std::setlocale(LC_NUMERIC, "pl_PL.UTF_8");
    std::locale::global(std::locale("pl_PL.UTF_8"));
    ASSERT_EQ(*std::localeconv()->decimal_point, ',');
    EXPECT_THAT(sut.toLineProtocol(), MatchesRegex("dummyMeasurement val=46\\.20* [0-9]+"));
    std::locale::global(std::locale("C"));
    std::setlocale(LC_NUMERIC, "C");
    ASSERT_EQ(*std::localeconv()->decimal_point, '.');
    EXPECT_THAT(sut.toLineProtocol(), MatchesRegex("dummyMeasurement val=46\\.20* [0-9]+"));
}

TEST_F(PointTest, toLineProtocol_shouldSerializeSingleTag)
{
    Point sut{measurementName};
    sut.addField("val", 1);
    sut.addTag("testTag", "foo");
    EXPECT_THAT(sut.toLineProtocol(), MatchesRegex("dummyMeasurement,testTag=foo val=1 [0-9]+"));
}

TEST_F(PointTest, toLineProtocol_shouldSerializeMultipleTags)
{
    Point sut{measurementName};
    sut.addField("val", 1);
    sut.addTag("testTag", "foo");
    sut.addTag("secondTag", "bar");
    sut.addTag("thirdTag", "baz");
    EXPECT_THAT(
        sut.toLineProtocol(), MatchesRegex("dummyMeasurement,testTag=foo,secondTag=bar,thirdTag=baz val=1 [0-9]+"));
}

TEST_F(PointTest, toLineProtocol_shouldSerializeMultipleFields)
{
    Point sut{measurementName};
    sut.addField("val", 1);
    sut.addField("secondField", 21.37);
    sut.addField("dummy", true);
    EXPECT_THAT(sut.toLineProtocol(), MatchesRegex("dummyMeasurement val=1,secondField=21.37,dummy=T [0-9]+"));
}
} // namespace protocol::metrics::influxdb
