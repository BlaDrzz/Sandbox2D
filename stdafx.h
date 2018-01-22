#pragma once

#include "windows.h"

// std lib includes
#include <math.h>
#include <vector>			// std lib vector
#include <string>			// std lib to_string
#include <thread>
#include <future>
#include <sstream>			// std lib stringstream
#include <fstream>			// SVGParser
#include <istream>
#include <iomanip>			// precision
#include <stdio.h>		    // console
#include <iostream>
#include <streambuf>
#include <unordered_map>

// SDL
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

// S2D includes
#include "Sandbox2D/Structs.h"
#include "Sandbox2D/InputManager.h"
#include "Sandbox2D/TextUtils.h"
#include "Sandbox2D/Logging.h"
#include "Sandbox2D/Any.h"
#include "Sandbox2D/Font.h"
#include "Sandbox2D/Bitmap.h"
#include "Sandbox2D/Observer.h"
#include "Sandbox2D/GameSettings.h"
#include "Sandbox2D/GameState.h"
#include "Sandbox2D/Cache.h"
#include "Sandbox2D/Sandbox2D.h"
#include "Sandbox2D/Graphics.h"
#include "Sandbox2D/Widgets/Widget.h"

// Testing
#if TEST == 1
	#include "S2D\Tests.h"
#endif

