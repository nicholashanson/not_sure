#include <catch2/catch_all.hpp>

#include <vector>

#include <image_processing.hpp>

TEST_CASE( "Get Between Class Variance" ) {
    not_sure::class_statistics statistics = { 
        .foreground_probability = 0.25,
        .background_probability = 0.75,
        .foreground_mean = 0.0,
        .background_mean = 170.333333   
    }; 
    double expected_variance = 5439.0;
    auto actual_variance = not_sure::get_between_class_variance( statistics );
    REQUIRE( actual_variance == Catch::Approx( expected_variance ).epsilon( 0.01 ) );
}