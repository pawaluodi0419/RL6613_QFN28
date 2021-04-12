/*
 * state_define.h
 *
 *  Created on: 2018-04-12
 *      Author: ashley_su
 */

#ifndef State_define_h_
#define State_define_h_


#define CLEAR_	                         0x00

//g_pattern_smbus_control_buf[0]//
#define smbus_road_waiting	             0x00
#define smbus_road_doing	             0x01
#define smbus_road_done_pass	         0x3f
#define smbus_road_done_fail	         0x1f


//g_pattern_smbus_control_buf[1]//
#define smbus_cmd_type_writemem	             0x18
#define smbus_cmd_type_writephy	             0x1B
#define smbus_cmd_type_writeefuse	         0x19

#define smbus_cmd_type_readmem	             0x38
#define smbus_cmd_type_readphy	             0x3B
#define smbus_cmd_type_readefuse	         0x39


//g_pattern_smbus_control_buf[2]//




#endif /* State_define_h_ */
