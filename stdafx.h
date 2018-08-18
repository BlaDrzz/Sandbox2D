#pragma once

// std lib includes
#include <cmath>
#include <vector>			// std lib vector
#include <string>			// std lib to_string
#include <thread>
#include <future>
#include <locale>
#include <cctype>
#include <sstream>			// std lib stringstream
#include <fstream>			// SVGParser
#include <istream>
#include <iomanip>			// precision
#include <cstdio>		    // console
#include <iostream>
#include <streambuf>
#include <algorithm> 
#include <functional> 
#include <unordered_map>

// SDL includes
#ifdef WIN32
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#endif

// Physics
#include <Box2D/Box2D.h>
#include "Sandbox2D/Structs.h"
#include "Sandbox2D/Geometry.h"
#include "Sandbox2D/Physics/Physics.h"
#include "Sandbox2D/Physics/PhysicsJoint.h"
#include "Sandbox2D/Physics/PhysicsObject.h"
#include "Sandbox2D/Physics/ContactListener.h"

// S2D includes
#include "Sandbox2D/InputManager.h"
#include "Sandbox2D/TextUtils.h"
#include "Sandbox2D/Logging.h"
#include "Sandbox2D/IniFile.h"
#include "Sandbox2D/Any.h"
#include "Sandbox2D/Font.h"
#include "Sandbox2D/Bitmap.h"
#include "Sandbox2D/Audio.h"
#include "Sandbox2D/GameSettings.h"
#include "Sandbox2D/GameState.h"
#include "Sandbox2D/Sandbox2D.h"
#include "Sandbox2D/Graphics.h"
#include "Sandbox2D/Widgets/Widget.h"