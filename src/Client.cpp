//    Battleship game assignment for MSU CSCI 366
//    Copyright (C) 2020    Mike P. Wittie
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "common.hpp"
#include "Client.hpp"

Client::~Client() {

}

void Client::initialize(unsigned int player, unsigned int board_size) {
    string make_player_to_string = to_string(player);
    string nameofaDEMON = "player_" + make_player_to_string + ".action_board.json";

    if (player > 2) {throw ClientWrongPlayerNumberException();}

    if(player < 1 ){throw ClientWrongPlayerNumberException();}



        vector<int> ZELDA_IS_A_GREAT_GAME(board_size, 0);


        vector<vector<int>> board(board_size, ZELDA_IS_A_GREAT_GAME);

        ofstream file(nameofaDEMON);

        {
            cereal::JSONOutputArchive killer_queen(file);
            killer_queen(CEREAL_NVP(board));
        }
        this->player = player;
        this->board_size = board_size;

        initialized = true;

    }

void Client::fire(unsigned int x, unsigned int y) {

    if(x> board_size || y > board_size || x < 0 || y < 0) {
        throw ClientException("HEXES AND VYES ARE OUT OF LINE");
    }

    string name = "player_";
    name.append(to_string(player));
    name.append(".shot.json");



    /**
       * Fires a shot on the coordinate target and creates a player_#.shot.json file
       * @param x - coordinate
       * @param y - coordinate
       */



    ofstream fire_file(name);
    {
        cereal::JSONOutputArchive write_archive(fire_file);
        write_archive(CEREAL_NVP(x), CEREAL_NVP(y));


    }

}


bool Client::result_available() {
    /**
   * Checks if a result file is available for
   * @return true if result is available, false otherwise
   */
    string name = "player_";
    name.append(to_string(player));
    name.append(".result.json");

    std::ifstream f;
    f.open(name);
    if (f.good()){
        return true;
    }else{
        return false;
    }
}


int Client::get_result() {
    /**
 * Gets the result from the player_#.result.json
 * @return the result as either HIT, MISS, or OUT_OF_BOUNDS
 */

    int HIT_or_MISS_or_OUTOFBOUNDS;

    string name = "player_";
    name.append(to_string(player));
    name.append(".result.json");


    ifstream result_ifp(name);

    if (!result_ifp.good()){
        throw ClientException("The result file was no good in get_result");
    }

    cereal::JSONInputArchive read_archive(result_ifp);
    read_archive(HIT_or_MISS_or_OUTOFBOUNDS);

    result_ifp.close();

    remove(name.c_str());


   // https://stackoverflow.com/questions/28162563/c-code-to-test-for-positive-negative-using-switch-and

    switch(HIT_or_MISS_or_OUTOFBOUNDS) {

        case 0:
            return OUT_OF_BOUNDS;
        case 1:
            return HIT;
        case-1:
            return MISS;
        default:
            throw ClientException("problem with get_result");
    }


}



void Client::update_action_board(int result, unsigned int x, unsigned int y) {


    string number = to_string(player);
    string fileName = "player_" + number + ".action_board.json";


    ifstream file;
    file.open(fileName);

    if(!file){
        throw ClientException("trouble opening player action board in update_action board");
    }

    vector<vector<int>> board(board_size, vector<int>(board_size));


    cereal::JSONInputArchive jsonInputArchive(file);
    jsonInputArchive(board);

    board[y][x] = result;
    // this is backwards wtf??? http://www.cplusplus.com/forum/beginner/68340/

    file.close();

    ofstream outf(fileName);

    cereal::JSONOutputArchive headingOut(outf);
    headingOut(CEREAL_NVP(board));

}


string Client::render_action_board(){

   // char render_array[10][10];

   //cant use char_array have to use vector/.


    string name = "player_";
    string action = ".action_board.json";
    name.append(to_string(player));
    string bardoon = name + action;

    vector<vector<int>>Vitameatavegamin(board_size, vector<int>(board_size));

    ifstream TOVALHALLA(bardoon);

    cereal::JSONInputArchive THE_GREAT_LIBRARIAN(TOVALHALLA);

    THE_GREAT_LIBRARIAN(Vitameatavegamin);

string toret;
string babycakes;


    for(int i = 0; i<=this->board_size; i++){
        for (int j = 0; j <= this->board_size; ++j) {
           babycakes=  Vitameatavegamin[i][j];
            toret.append(babycakes);

        }
    }

    TOVALHALLA.close();
    return toret;
}