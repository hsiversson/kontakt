#pragma once
#include "SAF_Application.h"

class Editor_Base : public SAF_ApplicationInterface
{
public:
	Editor_Base();
	~Editor_Base();

	bool Init() override;

	void Update() override;

	void Exit() override;
};

