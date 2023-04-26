add_lib(src
        SOURCES
        model/pieces/Piece.cpp
        model/pieces/King.cpp
        model/pieces/Knight.cpp
        model/pieces/Bishop.cpp
        model/pieces/Rook.cpp
        model/pieces/Queen.cpp
        model/pieces/Pawn.cpp
        model/Board.cpp
        model/BoardSpot.cpp
        model/Move.cpp
        model/PositionFactory.cpp

        )

add_app(${PROJECT_NAME}
        run/main.cpp)



