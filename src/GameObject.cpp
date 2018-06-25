//=============================================================================
// GameObject.cpp
//
//      Implementation of game objects
//
//  @author     Brandt
//  @version    1.0
//  @date       2018-06-23
//=============================================================================
#include "include/GameObject.hpp"
//=============================================================================
// Constructor
//
//  x       {int}       : Object's X position on screen
//  y       {int}       : Object's Y position on screen
//  bitmap  {BMPID}     : Object's bitmap ID
//=============================================================================
LolGame::GameObject::GameObject ( int x, int y, const BMPID& bitmap )
{
    this->x = x;
    this->y = y;

    this->__bitmap = bitmap;
}
//=============================================================================
// Constructor
//
//  x       {int}       : Object's X position on screen
//  y       {int}       : Object's Y position on screen
//  bitmap  {BMPID}     : Object's bitmap ID
//  fsX     {int}       : Sprite frame X size
//  fsY     {int}       : Sprite frame Y size
//=============================================================================
LolGame::GameObject::GameObject ( 
    int x, int y,
    const BMPID& bitmap,
    int fsX, int fsY
) : GameObject(x, y, bitmap)
{
    this->__frameSizeX = fsX;
    this->__frameSizeY = fsY;
}
//=============================================================================
// get_frame_size_x
//
//      Gets the width of the object's frame. -1 if the object isn't a sprite.
//=============================================================================
int LolGame::GameObject::get_frame_size_x ( ) const
{
    return this->__frameSizeX;
}
//=============================================================================
// get_frame_size_y
//
//      Gets the height of the object's frame. -1 if the object isn't a sprite.
//=============================================================================
int LolGame::GameObject::get_frame_size_y ( ) const
{
    return this->__frameSizeY;
}
//=============================================================================
// get_bitmap
//
//      Gets the object's bitmap ID
//=============================================================================
BMPID LolGame::GameObject::get_bitmap ( ) const
{
    return this->__bitmap;
}
//=============================================================================
// dispose
//
//      Disposes the object
//=============================================================================
void LolGame::GameObject::dispose ( )
{
    this->__disposed = true;
}
//=============================================================================
// is_disposed
//
//      Checks whether an object is disposed
//=============================================================================
bool LolGame::GameObject::is_disposed ( ) const
{
    return this->__disposed;
}