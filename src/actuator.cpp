#include "actuator.h"

using namespace DYNAMIXEL;

typedef struct ModelControlTableInfo{
  uint8_t index;
  uint16_t addr;
  uint8_t addr_length;
} ModelControlTableInfo_t;


const ModelControlTableInfo_t xl320_control_table[] = {
  {ControlTableItem::MODEL_NUMBER,           0, 2},
  {ControlTableItem::FIRMWARE_VERSION,       2, 1},
  {ControlTableItem::ID,                     3, 1},
  {ControlTableItem::BAUD_RATE,              4, 1},
  {ControlTableItem::RETURN_DELAY_TIME,      5, 1},
  {ControlTableItem::CW_ANGLE_LIMIT,         6, 2},
  {ControlTableItem::CCW_ANGLE_LIMIT,        8, 2},
  {ControlTableItem::CONTROL_MODE,          11, 1},
  {ControlTableItem::TEMPERATURE_LIMIT,     12, 1},
  {ControlTableItem::MIN_VOLTAGE_LIMIT,     13, 1},
  {ControlTableItem::MAX_VOLTAGE_LIMIT,     14, 1},
  {ControlTableItem::MAX_TORQUE,            15, 2},
  {ControlTableItem::STATUS_RETURN_LEVEL,   17, 1},
  {ControlTableItem::SHUTDOWN,              18, 1},
  {ControlTableItem::TORQUE_ENABLE,         24, 1},
  {ControlTableItem::DXL_LED,               25, 1},
  {ControlTableItem::D_GAIN,                27, 1},
  {ControlTableItem::I_GAIN,                28, 1},
  {ControlTableItem::P_GAIN,                29, 1},
  {ControlTableItem::GOAL_POSITION,         30, 2},
  {ControlTableItem::MOVING_SPEED,          32, 2},
  {ControlTableItem::TORQUE_LIMIT,          35, 2},
  {ControlTableItem::PRESENT_POSITION,      37, 2},  
  {ControlTableItem::PRESENT_SPEED,         39, 2},
  {ControlTableItem::PRESENT_LOAD,          41, 2},
  {ControlTableItem::PRESENT_VOLTAGE,       45, 1},
  {ControlTableItem::PRESENT_TEMPERATURE,   46, 1},
  {ControlTableItem::REGISTERED,            47, 1},
  {ControlTableItem::MOVING,                49, 1},    
  {ControlTableItem::HARDWARE_ERROR_STATUS, 50, 1},
  {ControlTableItem::PUNCH,                 51, 2},
  {ControlTableItem::LAST_DUMMY_ITEM,        0, 0}
};

const ModelControlTableInfo_t control_table_2_0[] = {
  {ControlTableItem::MODEL_NUMBER,             0, 2},
  {ControlTableItem::MODEL_INFORMATION,        2, 4},
  {ControlTableItem::FIRMWARE_VERSION,         6, 1},
  {ControlTableItem::ID,                       7, 1},
  {ControlTableItem::BAUD_RATE,                8, 1},
  {ControlTableItem::RETURN_DELAY_TIME,        9, 1},
  {ControlTableItem::DRIVE_MODE,              10, 1},
  {ControlTableItem::OPERATING_MODE,          11, 1},
  {ControlTableItem::SECONDARY_ID,            12, 1},
  {ControlTableItem::PROTOCOL_VERSION,        13, 1},
  {ControlTableItem::HOMING_OFFSET,           20, 4},
  {ControlTableItem::MOVING_THRESHOLD,        24, 4},
  {ControlTableItem::TEMPERATURE_LIMIT,       31, 1},
  {ControlTableItem::MAX_VOLTAGE_LIMIT,       32, 2},
  {ControlTableItem::MIN_VOLTAGE_LIMIT,       34, 2},
  {ControlTableItem::PWM_LIMIT,               36, 2},
  {ControlTableItem::VELOCITY_LIMIT,          44, 4},
  {ControlTableItem::MAX_POSITION_LIMIT,      48, 4},
  {ControlTableItem::MIN_POSITION_LIMIT,      52, 4},
  {ControlTableItem::SHUTDOWN,                63, 1},
  {ControlTableItem::TORQUE_ENABLE,           64, 1},
  {ControlTableItem::DXL_LED,                 65, 1},
  {ControlTableItem::STATUS_RETURN_LEVEL,     68, 1},
  {ControlTableItem::REGISTERED_INSTRUCTION,  69, 1},
  {ControlTableItem::HARDWARE_ERROR_STATUS,   70, 1},
  {ControlTableItem::VELOCITY_I_GAIN,         76, 2},
  {ControlTableItem::VELOCITY_P_GAIN,         78, 2},
  {ControlTableItem::POSITION_D_GAIN,         80, 2},
  {ControlTableItem::POSITION_I_GAIN,         82, 2},
  {ControlTableItem::POSITION_P_GAIN,         84, 2},
  {ControlTableItem::FEEDFORWARD_2ND_GAIN,    88, 2},
  {ControlTableItem::FEEDFORWARD_1ST_GAIN,    90, 2},  
  {ControlTableItem::BUS_WATCHDOG,            98, 2},
  {ControlTableItem::GOAL_PWM,               100, 2},
  {ControlTableItem::GOAL_VELOCITY,          104, 4},
  {ControlTableItem::PROFILE_ACCELERATION,   108, 4},
  {ControlTableItem::PROFILE_VELOCITY,       112, 4},
  {ControlTableItem::GOAL_POSITION,          116, 4},
  {ControlTableItem::REALTIME_TICK,          120, 2},
  {ControlTableItem::MOVING,                 122, 1},    
  {ControlTableItem::MOVING_STATUS,          123, 1},    
  {ControlTableItem::PRESENT_PWM,            124, 2},
  {ControlTableItem::PRESENT_VELOCITY,       128, 4},
  {ControlTableItem::PRESENT_POSITION,       132, 4},
  {ControlTableItem::VELOCITY_TRAJECTORY,    136, 4},
  {ControlTableItem::POSITION_TRAJECTORY,    140, 4},  
  {ControlTableItem::PRESENT_INPUT_VOLTAGE,  144, 2},
  {ControlTableItem::PRESENT_TEMPERATURE,    146, 1},
  {ControlTableItem::LAST_DUMMY_ITEM,          0, 0}
};

const ModelControlTableInfo_t xl330_control_table[] = {
  {ControlTableItem::CURRENT_LIMIT,           38, 2},
  {ControlTableItem::GOAL_CURRENT,           102, 2},
  {ControlTableItem::PRESENT_CURRENT,        126, 2},
  {ControlTableItem::LAST_DUMMY_ITEM,          0, 0}
};


ControlTableItemInfo_t DYNAMIXEL::getControlTableItemInfo(uint16_t model_num, uint8_t control_item){
  uint8_t item_idx, i = 0;
  const ModelControlTableInfo_t *p_common_ctable = nullptr;
  const ModelControlTableInfo_t *p_dep_ctable = nullptr;
  ControlTableItemInfo_t item_info;
  memset(&item_info, 0, sizeof(item_info));

  switch(model_num){
    case XL320:
      p_common_ctable = xl320_control_table;
      break;   

    case XL330_M288:
    case XL330_M077:
    case XC330_M181:
    case XC330_M288:
    case XC330_T181:
    case XC330_T288:
      p_common_ctable = control_table_2_0;    
      p_dep_ctable = xl330_control_table;
      break;
    default:
      break;
  }

  if(p_common_ctable == nullptr){
    return item_info;
  }

  do{
    item_idx = p_common_ctable[i].index;
    if(item_idx == control_item) {
      item_info.addr = p_common_ctable[i].addr;
      item_info.addr_length = p_common_ctable[i].addr_length;
      break;
    }
    i++;
  }while(item_idx != ControlTableItem::LAST_DUMMY_ITEM);

  if(p_dep_ctable == nullptr) {
    return item_info;
  }

  i = 0;
  do{
    item_idx = p_dep_ctable[i].index;
    if(item_idx == control_item) {
      item_info.addr = p_dep_ctable[i].addr;
      item_info.addr_length = p_dep_ctable[i].addr_length;
      break;
    }
    i++;
  }while(item_idx != ControlTableItem::LAST_DUMMY_ITEM);

  return item_info;
}
