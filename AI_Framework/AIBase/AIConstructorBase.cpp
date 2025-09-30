#include "AIConstructorBase.h"
#include <iostream>

void AIConstructorBase::DefineAI()
{
	DefineActions();
	DefineConsiderations();
	DefineOptions();
}

std::vector<AIOptionBase*> AIConstructorBase::GetOptionVector(std::vector<std::string> _selectedoptions)
{

	std::vector<AIOptionBase*> _optionVector;

	// for all options in the request list, add from the unordered map
	for (const auto& optionID : _selectedoptions)
	{
		_optionVector.push_back(options[optionID]);
	}


	for (int i = 0; i < _optionVector.size(); i++)
	{
		if (_optionVector[i] == NULL)
		{
			std::cout << "ERROR Matching Options " << std::endl;
			std::cout << "Option being added: " << _selectedoptions[i] << std::endl;
		}
	
	}



	return _optionVector;
}


std::vector<AIOptionBase*> AIConstructorBase::GetOptionVector()
{

	std::vector<AIOptionBase*> _optionVector;

	// for all options in the request list, add from the unordered map
	for (const auto option: options)
	{
		_optionVector.push_back(option.second);
	}

	return _optionVector;
}


AIOptionBase* AIConstructorBase::GetOptionByName(std::string _optionName)
{

	return(options[_optionName]);
}
