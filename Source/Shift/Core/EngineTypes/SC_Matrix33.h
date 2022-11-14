//ProjectFilter(Math)
#pragma once

class SC_Matrix33
{
public:
	union
	{
		float mData[9];
		float mData33[3][3];
		struct
		{
			SC_Vector mAxisX;
			SC_Vector mAxisY;
			SC_Vector mAxisZ;
		};
	};

public:
};