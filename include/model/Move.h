

#pragma once

class Board;
class Move {
public:
    virtual bool makeIfIsLegal(Board &board) = 0;
    virtual bool revertIfWasMade(Board &board) = 0;

    virtual ~Move() = default;
};
