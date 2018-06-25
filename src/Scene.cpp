//=============================================================================
// Scene.cpp
//
//      Implementation of the Scene context manipulation
//
//  @author     Brandt
//  @version    1.0
//  @date       2018-06-23
//=============================================================================
#include "include/Scene.hpp"
//=============================================================================
// Current scene
//=============================================================================
LolGame::Scene* LolGame::Scene::current = NULL;
//=============================================================================
// Constructor
//=============================================================================
LolGame::Scene::Scene ( )
{
    __objects = NULL;
}
//=============================================================================
// add
//
//      Adds an object to the scene
//
//  object  {GameObject*}   : Object to be added
//=============================================================================
void LolGame::Scene::add ( const GameObject* object )
{
    // Adds a new node at the beginning of the object linked list

    linked_list < const GameObject* > *node;

    node = new linked_list < const GameObject* >();
    node->data = object;
    node->next = this->__objects;

    this->__objects = node;
}
//=============================================================================
// render
//
//      Renders a single object to a drawing context
//
//  hDC     {HDC}           : Handle to a Drawing Context
//  object  {GameObject*}   : Object to be rendered
//=============================================================================
void render_object ( HDC& hDC, const LolGame::GameObject* object )
{
    HBITMAP hBmp = LolGame::BitmapManager::handle(object->get_bitmap());
    HDC hMemDC = CreateCompatibleDC(hDC);

    HBITMAP hOld = (HBITMAP)SelectObject(hMemDC, hBmp);

    BITMAP bmp;
    GetObject(hBmp, sizeof(BITMAP), &bmp);

    TransparentBlt(
        hDC,
        object->x, object->y,
        bmp.bmWidth, bmp.bmHeight,
        hMemDC,
        0, 0,
        bmp.bmWidth, bmp.bmHeight,
        RGB(255, 0, 255)
    );

    SelectObject(hMemDC, hOld);
    DeleteDC(hMemDC);
}
//=============================================================================
// render
//
//      Renders the scene to a drawing context
//
//  hDC     {HDC}   : Handle to a Drawing Context
//=============================================================================
void LolGame::Scene::render ( HDC& hDC )
{
    linked_list < const GameObject* > 
        *node = this->__objects, 
        *prev = NULL,
        *aux  = NULL;
        
    HDC hBuffer = CreateCompatibleDC(hDC);
    HBITMAP hBufferBmp = CreateCompatibleBitmap(hDC, 640, 480);
    HBITMAP hOld = (HBITMAP)SelectObject(hBuffer, hBufferBmp);

    while (node != NULL)
    {
        // Removes the node from the list if it's object is disposed
        if (node->data->is_disposed())
        {
            aux = node;

            if (prev != NULL)
                prev->next = node->next;

            else
                this->__objects = node->next;

            node = node->next;

            delete aux->data;
            delete aux;
        }

        // Otherwise, renders the object to the drawing context
        else
        {
            render_object(hBuffer, node->data);

            prev = node;
            node = node->next;
        }
    }

    BitBlt(
        hDC, 
        0, 0,
        640, 480,
        hBuffer,
        0, 0,
        SRCCOPY
    );
    
    SelectObject(hBuffer, hOld);
    DeleteObject(hBufferBmp);
    DeleteDC(hBuffer);
}