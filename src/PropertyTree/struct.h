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
    std::string extractionType;	//��ȡ���ͣ�com,subcom,supercom,free,split
    //com,free,subcom,supercom
    std::string position;		//splitֻ�����
    std::string positions;		//free
    std::string format;			//����
    std::string inversion;		//�Ƿ�ת
    uint32_t    NbWords;
    uint32_t    NbBits;
    uint32_t    LsbPosBit;

    //ֻ��Ƿ�ɺͳ��ɵĲ���
    uint32_t    recurence;		//subcom,supercom
    uint32_t    majorPos;		//subcom

    //calibrationtFuncУ׼����
    std::string calibrationtFuncName;					//У׼������
    std::map<std::string, double> calibrationtParam;	//У׼��������

    //processingFunc������
    std::string processingFuncName;					//��������
    std::map<std::string, double> 	processParam;	//����������

    //range��Χ
    std::vector<std::string>	range;

    //physicsDescription��������
    std::map<std::string, std::string>	physicsDes;	//��������

    //description
    std::string description;	//����
};

