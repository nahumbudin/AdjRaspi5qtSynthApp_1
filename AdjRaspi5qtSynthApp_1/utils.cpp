/**
*	@file		utils.cpp
*	@author		Nahum Budin
*	@date		12-Jul-2024
*	@version	1.0 
*
*	@brief		Utilities.
* 
*	History:\n
*/

#include <bits/stdc++.h> 

#include "utils.h"

/**
 * Strips the client name prefix (prefix:name -> name)
 *
 * @param name the full client name 
 * @return the stripped name
 */
std::string strip_client_name_prefix(std::string name)
{
	int prefix_end = name.find_first_of(':');

	if (prefix_end != std::string::npos)
	{
		return name.substr(prefix_end + 1, name.length() - 1);
	}

	return name;
}

/**
 * Replaces whit spaces with a backslash and a space (abc de f -> abc\ de\ f)
 * @param input string 
 * @return replacement string
 */
std::string replace_white_spaces(std::string input_str)
{
	if (input_str == "")
	{
		return "";
	}
	
	std::string new_str = "";
	
	char in_array[input_str.length() + 1];
	
	strcpy(in_array, input_str.c_str());
	
	for (int i = 0; i < input_str.size(); i++)
	{
		if (in_array[i] == ' ')
		{
			new_str += '\\';
			new_str += " ";
		}
		else 
		{
			new_str += in_array[i];
		}
	}
	
	return new_str;
}

/**
 * Returns a new value for a rotary knob new entry.
 * Rotary wraparound at 127.
 * @param previous controled value
 * @param new rotary encoder value
 * @param pointer to previous rotary encoder
 * @param controled value minimum value
 * @param controled value maximum value
 * @param increment or decrement value for each call
 * @return new controled value
 */
int update_rotary_encoder_value(int prev_value,
	int new_rot_val, 
	int *prev_rot_val,
	int min_val,
	int max_val,
	int inc_dec_value)
{
	int new_value = prev_value;
	
	if (((new_rot_val - *prev_rot_val) > 0) && ((new_rot_val - *prev_rot_val) < 80))
	{
		/* CW */
		new_value = prev_value + inc_dec_value;
		if (new_value > max_val)
		{
			new_value = max_val;
		}
	}
	else
	{
		/* CCW */
		new_value = prev_value - inc_dec_value;
		if (new_value < min_val)
		{
			new_value = min_val;
		}
	}
	
	*prev_rot_val = new_rot_val;
	
	return new_value;
}

/**
 * Returns a new value for a slider new entry 0-100.
 * @param new slider value
 * @param normalized value maximum value
 * @param normalized value minimum value
 * @return new controled value
 */
int normalize_slider_value(int new_value, int max_val, int min_val)
{
	int normlized_value = (int)(((new_value / 100.0) * (max_val - min_val)) + min_val);	
	
	return normlized_value;
}
