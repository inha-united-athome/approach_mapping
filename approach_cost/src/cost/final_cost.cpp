#include "approach_cost/cost/final_cost.hpp"

#include <stdexcept>

namespace approach_cost
{

approach_map::GridDataF32 computeFinalCost(
  const CommonCostLayers & common_layers,
  const FinalCostConfig & config)
{
  switch (config.mode) {
    case ModeId::Mode1:
    case ModeId::Mode3:
    case ModeId::GpsrMapOnly:
    case ModeId::GpsrGoal:
      // Mode3 differs only in how the runner derives object_row_dir / target_point
      // (frozen robot-front frame). GPSR modes are handled by the runner around
      // goal publication / visited filtering. The cost composition itself is identical.
      return common_layers.cost_common;
    default:
      throw std::runtime_error("Unsupported final cost mode");
  }
}

}  // namespace approach_cost
