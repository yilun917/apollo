/******************************************************************************
 * Copyright 2019 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

/**
 * @file
 **/

#include "modules/planning/scenarios/park/emergency_pull_over/stage_standby.h"

#include <string>
#include <vector>

#include "cyber/common/log.h"

#include "modules/planning/common/frame.h"
#include "modules/planning/common/planning_context.h"
#include "modules/planning/common/util/common.h"
#include "modules/planning/scenarios/util/util.h"
#include "modules/planning/tasks/deciders/path_bounds_decider/path_bounds_decider.h"

namespace apollo {
namespace planning {
namespace scenario {
namespace emergency_pull_over {

using apollo::common::TrajectoryPoint;

Stage::StageStatus EmergencyPullOverStageStandby::Process(
    const TrajectoryPoint& planning_init_point, Frame* frame) {
  ADEBUG << "stage: Stop";
  CHECK_NOTNULL(frame);

  scenario_config_.CopyFrom(GetContext()->scenario_config);

  bool plan_ok = ExecuteTaskOnReferenceLine(planning_init_point, frame);
  if (!plan_ok) {
    AERROR << "EmergencyPullOverStageStandby planning error";
  }

  // TODO(all): add a stop fence ahead of ADC

  return Stage::RUNNING;
}

Stage::StageStatus EmergencyPullOverStageStandby::FinishScenario() {
  // TODO(all): clear PlanningContext
  // PlanningContext::Instance()->mutable_planning_status()->clear_emergency_pull_over();

  next_stage_ = ScenarioConfig::NO_STAGE;
  return Stage::FINISHED;
}

Stage::StageStatus EmergencyPullOverStageStandby::FinishStage() {
  return FinishScenario();
}

}  // namespace emergency_pull_over
}  // namespace scenario
}  // namespace planning
}  // namespace apollo
