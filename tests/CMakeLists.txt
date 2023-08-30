set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG} -w -O0 -g3 -no-pie")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_DEBUG} -w -O0 -g3 -no-pie")

include(GoogleTest)

add_test(ChessTest
        SOURCES
        BoardSpotTest.cpp
        BoardTest.cpp
        MoveTest.cpp
        piecesTests/KingTest.cpp
        piecesTests/KnightTest.cpp
        piecesTests/QueenTest.cpp
        piecesTests/BishopTest.cpp
        piecesTests/RookTest.cpp
        piecesTests/PawnTest.cpp
        DEPENDS
        src
        )