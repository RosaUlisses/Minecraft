#include "Block.hpp"

const static float vertex_data[] = {
//   positions            texture
//   back
     0.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
     1.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     1.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.0f,  0.0f,  0.0f,  0.0f, 1.0f,

//   front
     1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
     0.0f,  1.0f,  1.0f,  0.0f, 0.0f,
     0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
     0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
     1.0f,  0.0f,  1.0f,  1.0f, 1.0f,
     1.0f,  1.0f,  1.0f,  1.0f, 0.0f,

//   left
     0.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
     0.0f,  1.0f,  1.0f,  1.0f, 0.0f,
     0.0f,  1.0f,  1.0f,  1.0f, 0.0f,
     0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
     0.0f,  0.0f,  0.0f,  0.0f, 1.0f,

//   right
     1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
     1.0f,  0.0f,  1.0f,  1.0f, 1.0f,
     1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     1.0f,  1.0f,  0.0f,  0.0f, 0.0f,
     1.0f,  1.0f,  1.0f,  1.0f, 0.0f,

//   bottom
     1.0f,  0.0f,  1.0f,  1.0f, 0.0f,
     0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
     0.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     1.0f,  0.0f,  1.0f,  1.0f, 0.0f,

//   top
     0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.0f,  1.0f,  1.0f,  0.0f, 0.0f,
     1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
     1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
     1.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
};

#define FRONT_FACE    0
#define BACK_FACE     1
#define LEFT_FACE     2
#define RIGHT_FACE    3
#define BOTTOM_FACE   4
#define UP_FACE       5



void Block::init_vertices() {

    int i = 0;
    while (i < 180) {
        vertice vert;
        vert.points = glm::vec3(vertex_data[i], vertex_data[i + 1], vertex_data[i + 2]);
        vert.texture = glm::vec2(vertex_data[i + 3], vertex_data[i + 4]);
        Block::vertices.push_back(vert);
        i = i + 5;
    }
}

void Block::set_texture(int texture_offset, int position) {

    float x = (texture_offset % 4) / 4.0;
    float y = (texture_offset / 4) / 4.0;


    if (Block::vertices[position].texture.x == 0.0)  Block::vertices[position].texture.x = x;
    if (Block::vertices[position].texture.y == 0.0)  Block::vertices[position].texture.y = y;
    if (Block::vertices[position].texture.x == 1.0)  Block::vertices[position].texture.x = x + 0.25;
    if (Block::vertices[position].texture.y == 1.0) {
        Block::vertices[position].texture.y = y + 0.25;
    }
}



Block::Block(std::string ID, int texture_offset) {

	Block::ID = ID;
    Block::init_vertices();
    for (int i = 0; i < Block::vertices.size(); i++) {
        Block::set_texture(texture_offset, i);
    }

}

Block::Block(std::string ID, int up_offset, int down_offset, int horizontal_offset) {

    Block::ID = ID;
    Block::init_vertices();

    for (int i = 0; i < Block::vertices.size(); i++) {
        
        if (i < 24) Block::set_texture(horizontal_offset, i);
        if (i < 30 && i >= 24) Block::set_texture(down_offset, i);
        if (i < 36 && i >= 30) Block::set_texture(up_offset, i);
    }

    
}

Block::Block(std::string ID, int vertical_offset, int horizontal_offset) {

    Block::ID = ID;
    Block::init_vertices();

    for (int i = 0; i < Block::vertices.size(); i++) {

        if (i < 30) Block::set_texture(horizontal_offset, i);
        if (i < 36 && i >= 30) Block::set_texture(vertical_offset, i);
    }
}



bool is_there_a_block(int matrix[X_DIMENSION][Y_DIMENSION][Z_DIMENSION], Coordinate coordinate) {

    if (coordinate.x < 0 || coordinate.x >= X_DIMENSION) return true;
    if (coordinate.y < 0 || coordinate.y >= Y_DIMENSION) return true;
    if (coordinate.z < 0 || coordinate.z >= Z_DIMENSION) return true;
        

    if (matrix[coordinate.x][coordinate.y][coordinate.z] == -1) return true;


    return false;
}



void Block::add_face(std::vector<vertice>* vertex_list, Coordinate coordinate, int face){

    int end = (face * 6) + 6;

    for (int i = face * 6; i < end; i++) {

        int x, y, z;
        vertice vertex;
        if (vertices[i].points.x == 0) x = coordinate.x;
        else x = coordinate.x + 1;

        if (vertices[i].points.y == 0) y = coordinate.y;
        else y = coordinate.y + 1;

        if (vertices[i].points.z == 0) z = coordinate.z;
        else z = coordinate.z + 1;


        vertex.points = glm::vec3(x, y, z);
        vertex.texture = glm::vec2(vertices[i].texture.x, vertices[i].texture.y);
        vertex_list->push_back(vertex);
    }
}


void Block::get_vertices(int matrix[X_DIMENSION] [Y_DIMENSION][Z_DIMENSION], Coordinate coordinate, Coordinate chunk_coordinate, std::vector<vertice>* vertex_list) {
    

    if (is_there_a_block(matrix, Coordinate(coordinate.x - chunk_coordinate.x, coordinate.y - chunk_coordinate.y, coordinate.z - 1 - chunk_coordinate.z))) {
        add_face(vertex_list, coordinate, FRONT_FACE);
    }

    if (is_there_a_block(matrix, Coordinate(coordinate.x - chunk_coordinate.x, coordinate.y - chunk_coordinate.y, coordinate.z + 1 - chunk_coordinate.z))) {
        add_face(vertex_list, coordinate, BACK_FACE);
    }

    if (is_there_a_block(matrix, Coordinate(coordinate.x - 1 - chunk_coordinate.x, coordinate.y - chunk_coordinate.y, coordinate.z - chunk_coordinate.z))) {
        add_face(vertex_list, coordinate, LEFT_FACE);
    }

    if (is_there_a_block(matrix, Coordinate(coordinate.x + 1 - chunk_coordinate.x, coordinate.y - chunk_coordinate.y, coordinate.z - chunk_coordinate.z))) {
        add_face(vertex_list, coordinate, RIGHT_FACE);
    }

    if (is_there_a_block(matrix, Coordinate(coordinate.x - chunk_coordinate.x, coordinate.y - 1 - chunk_coordinate.y, coordinate.z - chunk_coordinate.z))) {
        add_face(vertex_list, coordinate, BOTTOM_FACE);
    }

    if (is_there_a_block(matrix, Coordinate(coordinate.x - chunk_coordinate.x, coordinate.y + 1 - chunk_coordinate.y, coordinate.z - chunk_coordinate.z))) {
        add_face(vertex_list, coordinate, UP_FACE);
    }

}


