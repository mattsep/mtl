#include "mtl/rng/Rng.ipp"

namespace mtl::rng {

template class Rng<DefaultRandomEngine>;
template class Rng<SplitMix64Engine>;

}  // namespace mtl::rng