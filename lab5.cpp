//Leila Lin
//9-19-2018
//This lab uses vectors and arrays to calculate the total score of bowling.
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;



int main(){

    vector<string> players; // vector used to store players
    string player; // string variable to store player's name
    vector<int> scores; // vector scores to store score for each player


    while(true){
        cout <<"Enter player's name (done for no more players): ";
        cin >> player;
        if(player == "done"){
            break; //if input is "done", no need to continue, no need to insert to an array
        }
        players.push_back(player);
        int rolls[22]={0}; // one-dimensional int array used to store score for each roll, the possible maximum rolls is 21, defined size as 22, because not using rolls[0]; we can do two-dimensional int array
        int roll=1; // initiate the value of roll as 1
        int frame=1; // initiate the value of frame as 1
        int score; // score for each roll
        for (int i=1; i<21; ++i){ // a for loop as required to take all input
            cout <<"Enter score for frame "<<frame<<", roll "<<roll<<": ";
            cin >> score;
            
            rolls[i] = score; // insert the score to the array

            if(score == 10){ // based on the rule of game, before frame 10, when the first hit is 10, bump the frame
                if (frame<10){ // frame 10 is different than frame 1 to 9
                    if (i % 2 == 1) {
                        ++i; //since it is a one-dimensional array, every two units is a frame, since it hits 10 in roll 1, move to next frame
                    }
                    ++frame;
                    roll = 1;
                } else { // in frame 10, even the roll 1 is 10 pins, still have to play roll 2
                    roll = 2; // bump the roll to roll 2
                }

            }else{
                if(i % 2 == 1){
                    roll = 2; // if current roll is one, then the coming roll is 2
                }else{
                    ++frame; // if it is roll 2, bump up frame,
                    roll = 1;// reset roll to 1
                }
            }
        }

        if (rolls[19]+rolls[20] >= 10){//if the sum of the score of frame 10's roll 1 and roll 2, is larger than 10, roll 3!
            frame = 10, roll = 3;
            cout <<"Enter score for frame "<<frame<<", roll "<<roll<<": ";
            cin >> score;
            rolls[21] = score;
        }

        vector<int> frame_scores; // used to store the calculated score of each frame
        // the score calculation is defined here, better to define a function
        for(int i = 1; i< 19; i += 2){ // i += 2, set up the step as 2, make sure each i will be the roll 1
            int frame_score=0; //for each frame, initiate the calculated as 0
            if (rolls[i]==10){ // Strike
                frame_score+=10; // if the roll 1 of each frame is 10, then add 10 at first
                if(rolls[i+2] == 10){ // if the score of the following roll 1 is 10, then add 10
                    frame_score += 10;
                    if(i<17){ //boundary check, if frame still within the 8 rounds, the i+2+2 works
                        frame_score += rolls[i+2+2];
                    } else{
                        frame_score += rolls[20];//for the 10th frame, even the score of roll 1 is 10, still need to do the roll 2, rolls[20] is the score of roll 2
                    }
                } else {
                    frame_score += rolls[i+2] + rolls[i+3];// if the following score of roll 1 is not 10, then these are following two shots
                }
            } else if(rolls[i]+rolls[i+1] == 10){ // Spare
                frame_score += 10;
                frame_score += rolls[i+2];
            } else {
                frame_score = rolls[i]+rolls[i+1];
            }
            frame_scores.push_back(frame_score);
        }
        // the last round
        if (rolls[19] == 10){
            frame_scores.push_back(10+rolls[20]+rolls[21]);
        } else if(rolls[19]+rolls[20] == 10){
            frame_scores.push_back(10+rolls[21]);
        }
        else {
            frame_scores.push_back(rolls[19]+rolls[20]);
        }
        int sum=0;
        for(int i: frame_scores){
            sum+=i;
        }
        scores.push_back(sum);

    }

    if(players.empty() || scores.empty()){
        return 0;
    }
//Better to define a function here to print those records
    unsigned int j=0;
    for(string plr: players){
        cout<<plr<< " scored "<<scores.at(j)<<endl;
        ++j; // j represents the location of the plr(player)
    }
//Better to define a function to get the min index, max index, min value, and max value
    int min = INT_MAX; // The built in max integer in c++
    int max =INT_MIN; // The built in min integer in c++
    unsigned int index_min=0;
    unsigned int index_max=0;
    unsigned int i =0;
    for(int score: scores){
        if (score < min){
            min=score;
            index_min = i;

        }
        if (score > max){
            max=score;
            index_max = i;

        }
        ++i;
    }
    cout<<players.at(index_min)<<" did the worst by scoring "<<min<<endl;
    cout<<players.at(index_max)<<" won the game by scoring "<<max<<endl;



}




