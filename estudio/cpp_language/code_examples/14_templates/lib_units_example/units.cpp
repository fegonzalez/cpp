#include "units.h"
BEGIN_NAMESPACE_INDRA

namespace Units {

  scalar convert_non_templated_debug(scalar value,
                                     scalar unit_origin_magnitude,
                                     scalar unit_destination_magnitude) {
    return (unit_origin_magnitude/unit_destination_magnitude)*value;
  }

  scalar convert_from_si_non_templated_debug(
    scalar value,
    scalar unit_destination_magnitude) {
    return convert_non_templated_debug(value, 1, unit_destination_magnitude);
  }

  scalar convert_to_si_non_templated_debug(
    scalar value,
    scalar unit_origin_magnitude) {
    return convert_non_templated_debug(value, unit_origin_magnitude, 1);
  }

}

END_NAMESPACE_INDRA
