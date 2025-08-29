#include <image_processing.hpp>

namespace not_sure {

	bool operator==( const gray_scale_image& gray, const binary_image& binary ) {
		if ( gray.m_pixels.size() != binary.m_pixels.size() ) return false;
	    if ( gray.m_width != binary.m_width || gray.m_height != binary.m_height ) return false;
	    for ( std::size_t i = 0; i < gray.m_pixels.size(); ++i ) {
	        uint8_t expected = ( binary.m_pixels[ i ] == binary_value::black ) ? 0 : 0xff;
	        if ( gray.m_pixels[ i ] != expected ) return false;
	    }
	    return true;
	}

	gray_scale_histogram get_gray_scale_histogram( const gray_scale_image& image ) {
		gray_scale_histogram histogram{}; 
	    for ( std::size_t i = 0; i < image.m_pixels.size(); ++i ) { 
	    	++histogram[ image.m_pixels[ i ] ]; 
	    }
		return histogram;
	}

	gray_scale_histogram_probabilities get_gray_scale_histogram_probabilities( const gray_scale_histogram& histogram ) {
		const std::size_t total_pixels = std::accumulate( histogram.begin(), histogram.end(), std::size_t{ 0 } );
		gray_scale_histogram_probabilities probabilities;
		for ( std::size_t i = 0; i < probabilities.size(); ++i ) {
			probabilities[ i ] = histogram[ i ] / static_cast<double>( total_pixels );
		}
		return probabilities;
	}

	std::expected<class_statistics,std::string> get_class_statistics( const gray_scale_histogram_probabilities& probabilities, const uint8_t threshold ) {
		if ( threshold > probabilities.size() ) {
			return std::unexpected( "Threshold is too high." );
		}
		class_statistics statistics;
		for ( std::size_t i = 0; i <= threshold; ++i ) {
			statistics.m_foreground_probability += probabilities[ i ];
			statistics.m_foreground_mean += i * probabilities[ i ];
		}
		if ( statistics.m_foreground_probability > 0.0 ) {
			statistics.m_foreground_mean /= statistics.m_foreground_probability;
		} else {
			statistics.m_foreground_mean = 0.0;
		}
		for ( std::size_t i = threshold + 1; i < probabilities.size(); ++i ) {
			statistics.m_background_probability += probabilities[ i ];
			statistics.m_background_mean += i * probabilities[ i ];
		} 
		if ( statistics.m_background_probability > 0.0 ) {
			statistics.m_background_mean /= statistics.m_background_probability;
		} else {
			statistics.m_background_mean = 0.0;
		}
		return statistics;
	}

	double get_between_class_variance( const class_statistics& statistics ) {
		return statistics.m_foreground_probability *
           	   statistics.m_background_probability *
           	 ( statistics.m_foreground_mean - statistics.m_background_mean ) *
             ( statistics.m_foreground_mean - statistics.m_background_mean );
	}

	std::expected<uint8_t,std::string> get_otsu_threshold( const gray_scale_image& image ) {
		auto histogram = get_gray_scale_histogram( image );
		auto probabilities = get_gray_scale_histogram_probabilities( histogram );
		uint8_t optimum_threshold{};
		double maximum_variance{};
		for ( std::size_t threshold = 0; threshold < 256; ++threshold ) {
			auto statistics_result = get_class_statistics( probabilities, threshold );
			if ( !statistics_result ) {
				return std::unexpected( statistics_result.error() );
			}
			auto variance = get_between_class_variance( statistics_result.value() );
			if ( variance > maximum_variance ) {
				maximum_variance = variance;
				optimum_threshold = threshold;
			}
		}
		return optimum_threshold;
	}

	std::expected<binary_image,std::string> apply_otsu_threshold( const gray_scale_image& image ) {
		binary_image result;
		result.m_width = image.m_width; 
		result.m_height = image.m_height;
		result.m_pixels.resize( image.m_pixels.size() );
		auto threshold_result = get_otsu_threshold( image );
		if ( !threshold_result ) {
			return std::unexpected( threshold_result.error() );
		}
		auto threshold = threshold_result.value();
		std::cout << static_cast<int>( threshold ) << std::endl;
		for ( std::size_t i = 0; i < image.m_pixels.size(); ++i ) {
			result.m_pixels[ i ] = image.m_pixels[ i ] <= threshold ? binary_value::black : binary_value::white;
		} 
	    return result;
	}

} // namespace not_sure