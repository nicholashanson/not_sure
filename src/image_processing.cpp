#include <image_processing.hpp>

namespace not_sure {

	gray_scale_histogram get_gray_scale_histogram( const std::vector<std::vector<uint8_t>>& gray_scale_image ) {
		gray_scale_histogram histogram{}; 
	    for (const auto& row : gray_scale_image) {
	        for ( auto pixel : row ) {
	            ++histogram[ pixel ]; 
	    	}
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

	std::expected<uint8_t,std::string> get_otsu_threshold( const std::vector<std::vector<uint8_t>> image ) {
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

} // namespace not_sure