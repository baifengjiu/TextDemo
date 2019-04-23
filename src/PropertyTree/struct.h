#pragma once
#include <string>
#include <map>
#include <vector>
#include <stdint.h> 
struct parameter
{
    // general
    uint32_t    id;
    std::string code;
    std::string name;
    std::string unit;

    //extraction
    std::string extractionType;	//提取类型：com,subcom,supercom,free,split
    //com,free,subcom,supercom
    std::string position;		//split只有这个
    std::string positions;		//free
    std::string format;			//类型
    std::string inversion;		//是否反转
    uint32_t    NbWords;
    uint32_t    NbBits;
    uint32_t    LsbPosBit;

    //只有欠采和超采的参数
    uint32_t    recurence;		//subcom,supercom
    uint32_t    majorPos;		//subcom

    //calibrationtFunc校准函数
    std::string calibrationtFuncName;					//校准函数名
    std::map<std::string, double> calibrationtParam;	//校准函数参数

    //processingFunc处理函数
    std::string processingFuncName;					//处理函数名
    std::map<std::string, double> 	processParam;	//处理函数参数

    //range范围
    std::vector<std::string>	range;

    //physicsDescription物理描述
    std::map<std::string, std::string>	physicsDes;	//物理描述

    //description
    std::string description;	//描述
};

