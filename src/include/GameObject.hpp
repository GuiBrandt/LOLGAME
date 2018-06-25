//=============================================================================
// GameObject.hpp
//
//      Header for game objects
//
//  @author     Brandt
//  @version    1.0
//  @date       2018-06-23
//=============================================================================
#ifndef __LOLGAME_GAME_OBJECT__
#define __LOLGAME_GAME_OBJECT__

#ifndef UNICODE
	#define UNICODE
#endif

#include <windows.h>
#include <tuple>

#include "BitmapManager.hpp"

using namespace std;
//=============================================================================
// LolGame
//
//      Main namespace
//=============================================================================
namespace LolGame
{
    //=========================================================================
    // LolGame::GameObject
    //
    //      Class used to represent game objects. Actually, this is just a 
    //      struct used to wrap a position and a bitmap.
    //=========================================================================
    class GameObject
    {
        private:
            bool            __disposed      = false;
            BMPID           __bitmap        = -1;

            int             __frameSizeX    = -1;
            int             __frameSizeY    = -1;

        public:
            // Object's position
            int x = 0;
            int y = 0;

            // Current animation frame
            unsigned int currentFrame = 0;

            // Constructors
            GameObject ( int, int, const BMPID& );
            GameObject ( int, int, const BMPID&, int, int );

            // Frame size getters
            int get_frame_size_x ( ) const;
            int get_frame_size_y ( ) const;

            // Bitmap getter
            BMPID get_bitmap ( ) const ;

            // Disposes the object
            void dispose ( );

            // Checks whether the object is disposed
            bool is_disposed ( ) const;
    };
}

#endif