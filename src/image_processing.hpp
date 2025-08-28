#include <cstdint>

#include <array>
#include <expected>
#include <numeric>
#include <string>
#include <vector>

namespace not_sure {

	struct class_statistics {
		double foreground_probability;
		double background_probability;
		double foreground_mean;
		double background_mean;

		bool operator==( const class_statistics& other ) const {
			return foreground_probability == other.foreground_probability &&
				   background_probability == other.background_probability &&
				   foreground_mean == other.foreground_mean &&
				   background_mean == other.background_mean;
		}
	};

	using gray_scale_histogram = std::array<std::size_t,256>;

	using gray_scale_histogram_probabilities = std::array<double,256>;

	gray_scale_histogram get_gray_scale_histogram( const std::vector<std::vector<uint8_t>>& gray_scale_image );

	gray_scale_histogram_probabilities get_gray_scale_histogram_probabilities( const gray_scale_histogram& histogram );

	std::expected<class_statistics,std::string> get_class_statistics( const gray_scale_histogram_probabilities& probabilities, const uint8_t threshold );

	double get_between_class_variance( const class_statistics& statistics );

} // namespace not_sure