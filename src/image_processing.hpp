#include <cstdint>

#include <array>
#include <vector>

namespace not_sure {

	using gray_scale_histogram = std::array<std::size_t,256>;

	gray_scale_histogram get_gray_scale_histogram( std::vector<std::vector<uint8_t>> gray_scale_image );

} // namespace not_sure