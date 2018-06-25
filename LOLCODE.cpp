//=============================================================================
// LOLCODE.cpp
//
//      Implementation of the LOLCODE interpreter
//
//  @author     Brandt
//  @version    1.0
//  @date       2018-06-23
//=============================================================================
#include "include/LOLCODE.hpp"
//=============================================================================
// LOLVALUE::LOLVALUE
//
//      Constructor
//
//  type    {LOLTYPE}   :   LOLVALUE type
//=============================================================================
LolGame::LOLCODE::LOLVALUE::LOLVALUE ( 
    LolGame::LOLCODE::LOLVALUE::LOLTYPE type = 
        LolGame::LOLCODE::LOLVALUE::LOLTYPE::NOOB
)
{
    __type = type;
    __value = nullptr;
}
//=============================================================================
// LOLVALUE::~LOLVALUE
//
//      Destructor
//=============================================================================
LolGame::LOLCODE::LOLVALUE::~LOLVALUE ( )
{
    if (__value != nullptr)
        delete __value;
}
//=============================================================================
// LOLVALUE::type
//
//      Gets the value's type
//=============================================================================
LolGame::LOLCODE::LOLVALUE::LOLTYPE LolGame::LOLCODE::LOLVALUE::type ( ) const
{
    return __type;
}
//=============================================================================
// LOLVALUE::value
//
//      Gets the value's inner value's pointer
//=============================================================================
LolGame::LOLCODE::LOLANY LolGame::LOLCODE::LOLVALUE::value ( ) const
{
    return __value;
}
//=============================================================================
// LOLVALUE::set
//
//      Sets the value's inner value
//
//  value   {LOLANY}    :   Pointer to the new value
//=============================================================================
void LolGame::LOLCODE::LOLVALUE::set ( LolGame::LOLCODE::LOLANY value )
{
    if (__value != nullptr)
        delete __value;

    __value = value;
}
//=============================================================================
// LOLVALUE::cast
//
//      Casts the value to another type of value
//
//  type    {LOLTYPE}   :   LOLVALUE type to cast to
//=============================================================================
void LolGame::LOLCODE::LOLVALUE::cast (
    LolGame::LOLCODE::LOLVALUE::LOLTYPE type
) throw ( LolGame::LOLCODE::LOLMISTAKE )
{
    // Don't cast if your are already of that type
    if (type == __type)
        return;

    // You can't convert BUKKIT to anything...
    if (__type == LolGame::LOLCODE::LOLVALUE::LOLTYPE::BUKKIT)
        throw -1;

    switch (type)
    {
        // Strings...
        case LolGame::LOLCODE::LOLVALUE::LOLTYPE::YARN:
        {
            std::string* yarn = new std::string;

            switch (__type)
            {                    
                case LolGame::LOLCODE::LOLVALUE::LOLTYPE::NUMBR:
                    yarn->append(std::to_string(*((NUMBR_t*) __value)));
                    break;
                    
                case LolGame::LOLCODE::LOLVALUE::LOLTYPE::NUMBAR:
                    yarn->append(std::to_string(*((NUMBAR_t*) __value)));
                    break;
            }

            this->set(yarn);
            break;
        }
            
        // Integers...
        case LolGame::LOLCODE::LOLVALUE::LOLTYPE::NUMBR:
        {
            NUMBR_t* numbr = new NUMBR_t;

            switch (__type)
            {                
                case LolGame::LOLCODE::LOLVALUE::LOLTYPE::YARN:
                    *numbr = (NUMBR_t) std::stol(*((YARN_t*) __value));
                    break;

                case LolGame::LOLCODE::LOLVALUE::LOLTYPE::NUMBAR:
                    *numbr = (NUMBR_t) *((NUMBAR_t*) __value);
                    break;
            }

            this->set(numbr);

            break;
        }

        // Floats...
        case LolGame::LOLCODE::LOLVALUE::LOLTYPE::NUMBAR:
        {
            NUMBAR_t* numbar = new NUMBAR_t;

            switch (__type)
            {                
                case LolGame::LOLCODE::LOLVALUE::LOLTYPE::YARN:
                    *numbar = (NUMBAR_t) std::stod(*((YARN_t*) __value));
                    break;

                case LolGame::LOLCODE::LOLVALUE::LOLTYPE::NUMBR:
                    *numbar = (NUMBAR_t) *((NUMBR_t*) __value);
                    break;
            }

            this->set(numbar);

            break;
        }

        // Can't cast to these
        case LolGame::LOLCODE::LOLVALUE::LOLTYPE::BUKKIT:
        case LolGame::LOLCODE::LOLVALUE::LOLTYPE::NOOB:
            throw -2;
    }
    
    // Success
    __type = type;
}