//=============================================================================
// LOLCODE.hpp
//
//      Header for the LOLCODE interpreter
//
//  @author     Brandt
//  @version    1.0
//  @date       2018-06-23
//=============================================================================
#include <string>
#include <vector>
#include <unordered_map>
//=============================================================================
// LolGame
//
//      Main namespace
//=============================================================================
namespace LolGame
{
    //=========================================================================
    // LolGame::LOLCODE
    //
    //      Interpreter for LOLCODE 1.4
    //      Includes some extra libraries for game-related stuff:
    //
    //      `PAINTIN` -> BitmapManager
    //      ```   
    //      CAN HAS PAINTIN? 
    //      
    //      I IZ LOADIN YR "image.png" BTW Loads "image.png" 
    //      ```
    //
    //      `GAEM` -> GameObject
    //      ```
    //      CAN HAS GAEM? 
    //      
    //      I IZ SHOWIN YR bitmap AN YR 0 AN YR 3 BTW Creates a new object  at 
    //                                            BTW (0, 3) using bitmap
    //
    //      I HAS A object ITZ IT
    //
    //      I IZ MOVIN YR objekt AN YR 5 AN YR 5 BTW Moves the created object to
    //                                           BTW (5, 5)
    //      ```
    //
    //      `SCENE` -> Scene
    //      ```
    //      CAN HAS SCENE? 
    //      
    //      I IZ CREATIN YR MainScene BTW Creates a new scene called "MainScene"
    //
    //      I IZ ADDIN YR object AN YR MainScene BTW Adds an object to the
    //                                           BTW "MainScene"
    //      ```
    //=========================================================================
    class LOLCODE
    {
        private:
            class LOLVALUE;

            typedef void * LOLANY;
            typedef LPCTSTR LOLNAME;
            typedef DWORD LOLMISTAKE;

            typedef int NUMBR_t;
            typedef double NUMBAR_t;
            typedef std::string YARN_t;
            typedef std::unordered_map < LOLNAME, LOLVALUE > BUKKIT_t;

            //=================================================================
            // LolGame::LOLCODE::LOLVALUE
            //
            //      Represents a value in LOLCODE. Values can be changed!
            //=================================================================
            class LOLVALUE 
            {
                public:
                    // Possible LOLVALUE types
                    enum LOLTYPE
                    {
                        NOOB,
                        NUMBR,
                        NUMBAR,
                        YARN,
                        BUKKIT
                    };

                    LOLTYPE type ( ) const;
                    LOLANY value ( ) const;

                    void set ( LOLANY );
                    void cast ( LOLTYPE ) throw ( LOLMISTAKE );

                    LOLVALUE ( LOLTYPE = NOOB );

                    ~LOLVALUE ( );

                private:
                    LOLTYPE __type;
                    LOLANY __value;
            };
            //=================================================================
            // LolGame::LOLCODE::LOLSCOPE
            //
            //      Represents a closed scope in LOLCODE
            //=================================================================
            class LOLSCOPE
            {
                private:
                    std::unordered_map < LOLNAME, LOLVALUE > __variables;

                public:
                    void set_var ( LOLNAME, LOLVALUE );
                    LOLVALUE get ( LOLNAME ) const;
            };
            //=================================================================
            // LolGame::LOLCODE::LOLFUNC
            //
            //      Represents a function in LOLCODE
            //=================================================================
            class LOLFUNC
            {
                private:
                    std::vector < LOLNAME > __arguments;

                public:
                    std::vector < LOLNAME > arguments ( );

                    LOLVALUE call ( std::vector < LOLVALUE > ) const 
                        throw ( LOLMISTAKE );
            };
            
            static std::unordered_map < LOLNAME, LOLFUNC > __functions;

            static LOLSCOPE __global_scope;
            static LOLSCOPE* __current_scope;
        
        public:
            // Runs some LOLCODE
            static void run ( std::string );
    };
}