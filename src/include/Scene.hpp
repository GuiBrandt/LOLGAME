//=============================================================================
// Scene.hpp
//
//      Header for scene context manipulation
//
//  @author     Brandt
//  @version    1.0
//  @date       2018-06-23
//=============================================================================
#ifndef __LOLGAME_SCENE__
#define __LOLGAME_SCENE__

#ifndef UNICODE
	#define UNICODE
#endif

#include <windows.h>

#include "GameObject.hpp"
//=============================================================================
// LolGame
//
//      Main namespace
//=============================================================================
namespace LolGame
{
    //=========================================================================
    // LolGame::Scene
    //
    //      Class used to represent and manipulate the game scenario.
    //=========================================================================
    class Scene
    {
        private:

            // Linked list class
            // This will be useful when we need to remove elements from the
            // objects list as we traverse it
            template < class A > class linked_list
            {
                public:
                    A data;
                    linked_list< A > *next = NULL;

                    linked_list< A > () { }
            };

            // Objects on the scene
            linked_list< const GameObject* >* __objects;

        public:

            // Current scene
            static Scene* current;

            // Constructor
            Scene();

            // Adds an object to the scene
            void add ( const GameObject* );

            // Renders the scene to a drawing context
            void render ( HDC& );
    };
}

#endif