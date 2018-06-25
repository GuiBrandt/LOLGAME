//=============================================================================
// BitmapManager.hpp
//
//      Header for bitmap loading and manipulation
//
//  @author     Brandt
//  @version    1.0
//  @date       2018-06-23
//=============================================================================
#ifndef __LOLGAME_BITMAP_MANAGER__
#define __LOLGAME_BITMAP_MANAGER__

#ifndef UNICODE
	#define UNICODE
#endif

#include <windows.h>
#include <unordered_map>

using namespace std;

typedef int BMPID;

//=============================================================================
// LolGame
//
//      Main namespace
//=============================================================================
namespace LolGame
{
    //=========================================================================
    // LolGame::BitmapManager
    //
    //      Class used to load images and store them as bitmaps
    //=========================================================================
    class BitmapManager
    {
        private:
            static unordered_map < BMPID, HBITMAP > __bitmaps;

        public:

            // Loads a bitmap
            static BMPID load ( const LPTSTR& );

            // Gets the handle to a bitmap
            static HBITMAP handle ( const BMPID& );

            // Frees a bitmap
            static void free ( const BMPID& );
    };
}
#endif