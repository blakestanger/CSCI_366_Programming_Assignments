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
#include "Server.hpp"
#include <iostream>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <string>
#include <vector>

/**
 * Calculate the length of a file (helper function)
 *
 * @param file - the file whose length we want to query
 * @return length of the file in bytes
 */
//int get_file_length(ifstream *file){
//}


void Server::initialize(unsigned int board_size,
                        string p1_setup_board,
                        string p2_setup_board){

    this->board_size = board_size;
//    this->p1_setup_board =scan_setup_board(p1_setup_board);
//    this->p2_setup_board = scan_setup_board(p2_setup_board);
//
////    /mnt/c/Users/blake/Documents/CSCI_366_Programming_Assignments/test/tests.cpp:65: Failure
////    Expected: srv.initialize(10, "player_1.setup_board.txt", "player_2.setup_board.txt") doesn't throw an exception.
////    Actual: it throws std::exception-derived exception with description: "Incorrect board size".


    int file_length = 0;
    int file_length2 = 0;
    string line;
    string different_line;
ifstream sasquatch;
sasquatch.open(p1_setup_board);
if (!sasquatch){ throw ServerException("Unable to open P1 Board");}




    while(sasquatch>>line) {

       // cout << line << line.length();

        if (line.length()== board_size) {


            file_length++;


        } else {
            throw ServerException("PINKIncorrect board size");
        }
    }

        if (file_length != board_size){

            throw ServerException("GREENIncorrect board size");
        }


   //https://stackoverflow.com/questions/3482064/counting-the-number-of-lines-in-a-text-file
    //conversation with cooper.
    sasquatch.close();

    sasquatch.open(p2_setup_board);
    if(!sasquatch){throw ServerException("Bad P2 Setupboard");}



    while(sasquatch>> different_line) {

        if (different_line.length() == board_size) {

            file_length2++;


        } else {
            throw ServerException("REDIncorrect board size");
        }
    }
        if (file_length2 != board_size){

            throw ServerException("BLUEIncorrect board size");
        }

        //ok to assign board size now
        this->board_size = board_size;
    sasquatch.close();
}


Server::~Server() {
}


BitArray2D *Server::scan_setup_board(string setup_board_name){
}

int Server::evaluate_shot(unsigned int player, unsigned int x, unsigned int y) {
    /**
//    * Checks the coordinates of a shot against setup board of player
//    *
//    * Check that player number within bounds, checks that shot coordinates within bounds, determines if the shot
//    * results in a HIT, or a MISS.
//    * @param player - player number
//    * @param x - coordinate
//    * @param y - coordinate
//    * @return returns shot result as either HIT, MISS, or OUT_OF_BOUNDS
//    */



    if (player < 1) {
        throw invalid_argument("Player number not within bounds");
    }

    if (player > 2) {
        throw invalid_argument("Player number not within bounds");
    }


    if ((y < 0) || (y > board_size)) {
        return OUT_OF_BOUNDS;
    }
    if ((x < 0) || (x > board_size)) {
        return OUT_OF_BOUNDS;
    }



    switch (player) {
        case 2: {
            string line_length;
            fstream ANOTHER_SQUWATCH;
            ANOTHER_SQUWATCH.open("player_1.setup_board.text");
            ANOTHER_SQUWATCH >> line_length;
            int spot = (((line_length.length()-1 * y)) + x);
            int i = 0;

//            vector<vector<char>> STOP_BLOWING_HOLES_IN_MY_SHIP(board_size, vector<char>(board_size));
//            for (int j = 0; j <STOP_BLOWING_HOLES_IN_MY_SHIP.size() ; ++j) {
//                for (int k = 0; k <STOP_BLOWING_HOLES_IN_MY_SHIP[j].size() ; ++k) {
//                    p1_setup_board>>line_length;
//
//                }
//
//            }

            ANOTHER_SQUWATCH.seekg(spot, ios::beg);
            char at_position[2];
            ANOTHER_SQUWATCH.read(at_position, 1);
            at_position[1]=0;

            ANOTHER_SQUWATCH.close();

            //cout<<at_position<<"ATPOSITIOS"<<endl;

            while (i <= 4) {
                //cout<<SHIPS[i]<<"SHIPSBITCHES"<<endl;
                //cout<<at_position[0]<<"LOOKINGFORTHIS"<<endl;
                if (SHIPS[i] == at_position[0]) {
                    return HIT;
                }
                i++;
            }
            if(i==5){return MISS;}
            break;
        }
        case 1: {
            string HEAVY_METAL_BAND;
            fstream YETI;
            YETI.open("player_2.setup_board.txt");

            if(!YETI.good()){throw ServerException("900");}
            YETI >> HEAVY_METAL_BAND;
            int spoter = (((HEAVY_METAL_BAND.length()-1) * y) + x);
            int i = 0;



            YETI.seekg(spoter, ios::beg);
            char at_position2[2];

            YETI.read(at_position2, 1);
            at_position2[5];
            //cout<<spoter<<"SPOT"<<x<<'X'<<y<<'y'<<at_position2<<"ATPOSITION"<<"LINELENGTH:"<<HEAVY_METAL_BAND.length()<<endl;
            YETI.close();

            while (i <= 4) {
                if (SHIPS[i] == at_position2[0]) {
                    return HIT;
                }
                i++;
            }
            if(i==5){return MISS;}

        }
        default:
            cout << "HOW DID YOU REACH THIS?? YOU WERE NEVER SUPPOSED TO GET HERE> ";
            break;


    }
}



int Server::process_shot(unsigned int player) {
    int playercheck = player;
    /**
   * Processes a shot issued by player
   *
   * Gets the shot from player, extracts coordinates, passes the information of evaluate_shot, and writes the result
   * into player_#.result.json.
   * @param player - player number
   * @return returns SHOT_PROCESSED, or NO_SHOT_FILE if nothing to process
   */
    bool inbounds = false;
    bool xbound =false;
    bool ybound = false;

    string shooterMcGavin = (".shot.json");
    string walrus = (to_string(player));
    string name = "player_" + walrus + shooterMcGavin;



    string return_name = "player_"+to_string(player)+".result.json";








    if (playercheck < 1){
        throw invalid_argument("Sorry this is a two player game!");
    }

    if (playercheck > 2){
        throw invalid_argument("Sorry this is a two player game!");
    }



    ifstream shot_file;

    shot_file.open(name);
        if (!shot_file.good()){
            //cout<<"WORLDROAMERXV-LT"<<player;

            return NO_SHOT_FILE;
        }


        int x = 0, y = 0, result = 0;

        //cout << x << "THIS IS X"<<endl;
        //cout << y << "THIS IS Y"<<endl;
        cereal::JSONInputArchive read_archive(shot_file);
        read_archive(x, y);



    shot_file.close();
    remove(name.c_str());

        if (x < board_size && x > -1) {xbound = true;}
        if(y < board_size && y > -1)  {ybound = true;}
        if(ybound&&xbound){inbounds = true; }
//            cout << x << "NOW THIS IS X"<<endl;
//            cout << y << "NOW THIS IS Y"<<endl;
//            cout<< board_size << "THIS IS BOARD SIZE" <<endl;







        if (!inbounds) {

//            cout<<"TROUBLE";
            playercheck = 3;

        }

//    if(inbounds){cout<<"INBOUNDS"<<playercheck<<"PLAYER"<<endl; }
//    if(!inbounds){cout<<"OUTBOUNDS"<<playercheck<<"PLYAWER"<<endl;}


        switch (playercheck) {
            case 1:
                //cout<<"CASE1";
                result = evaluate_shot(playercheck, x, y);
                //cout<<"CASE1"<<result<<endl;
                break;
            case 2:
                result = evaluate_shot(playercheck, x, y);
                //cout<<"CASE2"<<result<<endl;
                break;
            case 3:
                result = OUT_OF_BOUNDS;
                //cout << "DIDWEMAKEITHERE"<<endl;
                break;
            default:
                throw ServerException("How did you get here this wasn't supposed to happen!");

        }
        //cout<<"tluser"<<result;

        ofstream get_me_outta_here;
        get_me_outta_here.open(return_name);
        {
            cereal::JSONOutputArchive king(get_me_outta_here);
            king(CEREAL_NVP(result));
        }


        return SHOT_FILE_PROCESSED;



}


