//=============================================================================
// Scene.cpp
//
//      Implementation of the Bitmap Manager
//
//  @author     Brandt
//  @version    1.0
//  @date       2018-06-23
//=============================================================================
#include "include/BitmapManager.hpp"

#include <Wincodec.h>

#include <iostream>

#include <cstdlib>
#include <vector>

using namespace std;

//=============================================================================
// Bitmaps
//=============================================================================
unordered_map < BMPID, HBITMAP > LolGame::BitmapManager::__bitmaps;
//=============================================================================
// load
//
//      Loads a bitmap from an image file
//
//  filename    {LPTSTR}    : Image file name
//
//  Returns a BMPID that can be used to retrieve the loaded image bitmap handle
//=============================================================================
BMPID LolGame::BitmapManager::load ( const LPTSTR& filename )
{
    IWICImagingFactory *factory = NULL;
    IWICStream* stream;
    IWICBitmapDecoder *decoder = NULL;

    CoInitialize(NULL);

    HRESULT hr = CoCreateInstance(
                    CLSID_WICImagingFactory,
                    NULL,
                    CLSCTX_INPROC_SERVER,
                    IID_PPV_ARGS(&factory));

    if (SUCCEEDED(hr))
        hr = factory->CreateStream(&stream);
    else
        return -1;

    if (SUCCEEDED(hr))
        hr = stream->InitializeFromFilename(filename, GENERIC_READ);
    else
        return -2;

    if (SUCCEEDED(hr))
    {
        hr = factory->CreateDecoderFromStream(
            stream,
            NULL,
            WICDecodeOptions::WICDecodeMetadataCacheOnDemand,
            &decoder
        );
    }
    else
        return -3;

    if (SUCCEEDED(hr))
    {
        UINT frames = 0;

        hr = decoder->GetFrameCount(&frames);

        if (SUCCEEDED(hr) && (frames > 0))
        {
            UINT width = 0, height = 0;        
            IWICBitmapFrameDecode *wic_bitmap = NULL;

            hr = decoder->GetFrame(0, &wic_bitmap);

            if (SUCCEEDED(hr))
            {
                // Copies the loaded image's pixels to a buffer and creates
                // a HBITMAP from them
                UINT width = 0, height = 0;
                wic_bitmap->GetSize(&width, &height);

                std::vector<BYTE> buffer(width * height * 4);
                wic_bitmap->CopyPixels(NULL, width * 4, buffer.size(), buffer.data());

                HBITMAP hbmp = CreateBitmap(width, height, 1, 32, buffer.data());

                // Generates a new unique random ID
                BMPID id;
                do id = rand();
                while (__bitmaps.find(id) != __bitmaps.end() || id == 0);

                // Inserts the newly created bitmap into the bitmap list and 
                // returns its ID
                __bitmaps.insert({ id, hbmp });

                wic_bitmap->Release();

                return id;
            }
            else
                return -4;

        }
    }

    return -5;
}
//=============================================================================
// handle
//
//      Gets the handle to a bitmap from its ID
//
//  id  {BMPID} : Bitmap ID
//=============================================================================
HBITMAP LolGame::BitmapManager::handle ( const BMPID& id )
{
    return __bitmaps[id];
}
//=============================================================================
// free
//
//      Frees a bitmap
//
//  id  {BMPID} : Bitmap ID
//=============================================================================
void LolGame::BitmapManager::free ( const BMPID& id )
{
    DeleteObject(handle(id));
    __bitmaps.erase(id);
}