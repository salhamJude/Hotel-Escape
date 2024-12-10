#pragma once

enum GridElement {
    PATH,
    WALL,
    PLAYER,
    DOOR,
    ESCAPE_DOOR,
    EMPTY,
    VISITED
};

enum Direction {
    UP = 1, 
    LEFT, 
    DOWN, 
    RIGHT, 
    UPLELFT, 
    UPRIGHT, 
    DOWNLEFT, 
    DOWNRIGHT};