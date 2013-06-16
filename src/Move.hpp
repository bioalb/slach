#ifndef _MOVE_HPP_
#define _MOVE_HPP_

#include <string>
#include <vector>
#include "SlachTypes.hpp"
#include "Square.hpp"

namespace slach
{

/**
 * The MOVE class
 */
class Move
{

private :

    Square* mpOrigin;
    Square* mpDestination;

public :

    Move() = default;
    Move(Square* pOrigin, Square* pDestination);

    ~Move();

    Square* GetOrigin() const;
    Square* GetDestination() const;

};
}
#endif //_MOVE_HPP_

