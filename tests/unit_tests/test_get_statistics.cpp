#include <catch2/catch_all.hpp>

#include <vector>

#include <image_processing.hpp>

TEST_CASE( "Get Class Statistics" ) { 
    not_sure::gray_scale_histogram_probabilities probabilities{};
    probabilities[ 0 ] = 0.25;   
    probabilities[ 128 ] = 0.5;   
    probabilities[ 255 ] = 0.25; 
    not_sure::class_statistics statistics = { /* foreground probability */ 0.25, 
                                              /* background probability */ 0.75, 
                                              /* foreground mean */ 0.0, 
                                              /* background mena */ 170.333333 }; 
    not_sure::class_statistics expected_statistics( 0.25, 0.75, 0.0, 170.333333 ); 
    auto result = not_sure::get_class_statistics( probabilities, 10 );
    REQUIRE( result.has_value() == true );
    REQUIRE( result.value().m_foreground_probability == Catch::Approx( expected_statistics.m_foreground_probability ).epsilon( 0.02 ) );
    REQUIRE( result.value().m_background_probability == Catch::Approx( expected_statistics.m_background_probability ).epsilon( 0.02 ) );
    REQUIRE( result.value().m_foreground_mean == Catch::Approx( expected_statistics.m_foreground_mean ).margin( 0.01 ) );
    REQUIRE( result.value().m_background_mean == Catch::Approx( expected_statistics.m_background_mean ).epsilon( 0.02 ) );
}