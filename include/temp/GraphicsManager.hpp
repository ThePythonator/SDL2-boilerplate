#pragma once

#include "SpritesheetManager.hpp"

#if defined(TARGET_32BLIT_HW)
#include "32BlitExtras.hpp"
#else
#include "SDLExtras.hpp"
#endif // TARGET_32BLIT_HW