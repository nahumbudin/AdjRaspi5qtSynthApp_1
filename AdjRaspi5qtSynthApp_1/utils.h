/**
*	@file		utils.h
*	@author		Nahum Budin
*	@date		12-Jul-2024
*	@version	1.0 
*
*	@brief		Utilities.
* 
*	History:\n
*/
#pragma once

#include <string>


std::string strip_client_name_prefix(std::string name);

std::string replace_white_spaces(std::string input_str);

int update_rotary_encoder_value(int prev_val, int new_rot_val, int *prev_rot_val, 
								int min_val, int max_valint, int inc_dec_value);

int normalize_slider_value(int new_value, int max_val, int min_val);
