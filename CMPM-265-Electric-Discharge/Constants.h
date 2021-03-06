#pragma once

const int Window_Width = 800;
const int Window_Height = 800;
const float Noise_X_Input_Dividend = 200.f;
const float Noise_Y_Invertal = 1.f;
const float Branching_Angle_Base = 10.f;
const int Branching_Angle_Margin = 20;
const int Branching_Probability = 500;
const int Branch_Length_Decrease_Base = 6;
const int Branch_Length_Decrease_Margin = 3;
const int Branch_Thickness_Decrease_Base = 6;
const int Branch_Thickness_Decrease_Margin = 3;
const int Amplitude_Base = 20;
const int Amplitude_Margin = 60;
const float Branching_Threshold = 3;
const float Storm_Duration = 0.1;
const int Storm_Fading_Rate = 800;
const int Lightning_Interval_Limit = 150;
const int Lightning_X_Base = 100;
const int Lightning_X_Range = 600;
const int Lightning_Y = 50;
const int Lightning_Direction_Base = 60;
const int Lightning_Direction_Range = 60;
const float Continuous_Discharge_Threshold = 50;
const float Continuous_Anode_Radius = 15;
const int Continuous_Anode_X = Window_Width / 2;
const int Continuous_Anode_Y = Window_Height / 2;
const int Menu_Option_Character_Size = 50;
const int Menu_Option_X = 100;
const int Menu_Option_Initial_Y = 200;
const int Menu_Option_Interval = 100;
const int Menu_Instruction_X = 100;
const int Menu_Instruction_Y = 700;
const int Instruction_Character_Size = 20;
const float PI = 3.14159265;
const float Degree_To_Radian = PI / 180;
enum Display { Menu, Demo, Storm, Continuous };