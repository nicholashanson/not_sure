#include <catch2/catch_all.hpp>

#include <vector>

#include <image_processing.hpp>

TEST_CASE( "Get Class Statistics" ) { 
    not_sure::gray_scale_histogram_probabilities probabilities{};
    probabilities[ 0 ] = 0.25;   
    probabilities[ 128 ] = 0.5;   
    probabilities[ 255 ] = 0.25; 
    not_sure::class_statistics expected_statistics = { 
        .foreground_probability = 0.25,
        .background_probability = 0.75,
        .foreground_mean = 0.0,
        .background_mean = 170.333333   
    }; 
    auto result = not_sure::get_class_statistics( probabilities, 10 );
    REQUIRE( result.has_value() == true );
    REQUIRE( result.value().foreground_probability == Catch::Approx( expected_statistics.foreground_probability ) );
    REQUIRE( result.value().background_probability == Catch::Approx( expected_statistics.background_probability ) );
    REQUIRE( result.value().foreground_mean == Catch::Approx( expected_statistics.foreground_mean ) );
    REQUIRE( result.value().background_mean == Catch::Approx( expected_statistics.background_mean ) );
}