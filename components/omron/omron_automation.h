#pragma once

// An ESPHome automation trigger for every measurement the node harvests.
//
// Without this the only per-record sink is fire_homeassistant_event(), so a
// node with no API connection can surface nothing but the newest reading per
// user through its entities -- history_records is documented as "entities
// only ... which is all the entities can show anyway". That makes every record
// but the last unreachable on an install that deliberately runs without Home
// Assistant, which is a data-loss shape rather than a missing convenience:
// two measurements between polls and the earlier one is gone, with the cursor
// already advanced past it.
//
// The trigger rides the existing history queue, so it inherits that queue's
// invariant: the watermark reaches flash only once every record has left.

#include "esphome/core/automation.h"

#include "omron_measurement.h"

namespace esphome::omron {

class OmronMeasurementTrigger : public Trigger<uint8_t, const OmronMeasurement &> {
 public:
  void publish(uint8_t user, const OmronMeasurement &measurement) { this->trigger(user, measurement); }
};

}  // namespace esphome::omron
