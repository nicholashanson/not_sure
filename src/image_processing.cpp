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
		for ( std::size_t i = 0; i < threshold; ++i ) {
			statistics.foreground_probability += probabilities[ i ];
			statistics.foreground_mean += i * probabilities[ i ];
		}
		if ( statistics.foreground_probability > 0.0 ) {
			statistics.foreground_mean /= statistics.foreground_probability;
		}
		for ( std::size_t i = threshold; i < probabilities.size(); ++i ) {
			statistics.background_probability += probabilities[ i ];
			statistics.background_mean += i * probabilities[ i ];
		} 
		if ( statistics.background_probability > 0.0 ) {
			statistics.background_mean /= statistics.background_probability;
		}
		if ( statistics.background_probability + statistics.foreground_probability > 1.0 ) {
			return std::unexpected( "Total probability is greater than 1." );
		}
		return statistics;
	}

	double get_between_class_variance( const class_statistics& statistics ) {
		return statistics.foreground_probability *
           	   statistics.background_probability *
           	 ( statistics.foreground_mean - statistics.background_mean ) *
             ( statistics.foreground_mean - statistics.background_mean );
	}

} // namespace not_sure