#pragma once
#ifndef CGFGAME_H
#define CGFGAME_H

#include "CGFTypes.h"

namespace CGF
{
	class CGF_DLL CGFGame
	{
	public:

		virtual void Start() = 0;
		virtual void Update(float delta) = 0;
	};
}

#endif