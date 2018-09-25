#include <iostream>
#include "p1.h"
using namespace std;

int main(){
    int ipseed, rdnumber, endpoint;
    int score = 0;
    char proposed[10] = {0};
    char letter;
    string W;
        
    //Intiallize
    //randomly choose a word
    cout << "Please input seed: ";
    cin >> ipseed;
    p1_srand(ipseed);
    rdnumber = p1_rand() % nWords;
    W = words[rdnumber];

    //information of the word
    int len = W.size();

    //initialize a char for recording later
    char correct[len] = {0};
      
    //Main body of the game
    while (score <= 9){
        //progress of the game
        cout << "Score: " << score << endl;
        for (int i = 0; i < len; i++ ){
            (correct[i] == 0)? (cout << "_ ") : (cout << correct[i] << " ");
        }
        cout << endl << "Already proposed characters: " << endl;
        for (int i = 0; i < score; i++){
            cout << proposed[i] << " ";
        }
        
        //ask for input
        cout << endl << "Please enter a letter (a-z): ";
        cin >> letter;
        
        //judge the validation of input
        if (letter <= 'z' && letter >= 'a'){
            //judge the correctness of guess
            int judge = 0;
            for (int i = 0; i < len; i++){
                if (W[i] == letter){
                    judge = 1;
                    correct[i] = letter;
                }
            }

            //refresh information about proposed letters
            if (judge == 0){
                //check for repetition
                int r;
                for (r = 0; r < score; r++){
                    if (proposed[r] == letter){
                        break;
                    }
                }

                //list proposed letters in alphabetic order
                if (r == score){
                    //refresh the value of score
                    score ++;
                    if (score == 1){
                        proposed[0] = letter;
                    }
                    else if (letter > proposed[score - 2]){
                        proposed[score - 1] = letter;
                    }
                    else
                    {
                        for (int i = 0; i < score - 1; i++){
                            if (letter < proposed[i]){
                                endpoint = i;
                                for (int j = score - 1; i > endpoint; i --){
                                    proposed[j] = proposed[j - 1];
                                }
                                proposed[endpoint] = proposed[endpoint - 1];
                                break;
                            }
                        }
                    }
                }
            }

            //judge situation of the game (win)
            int j;
            for (j = 0; j < len; j++){
                if (correct[j] == 0){
                    break;
                }
            }
            if (j == len){
                cout << "The word was: " << W << "\nYou won!" << endl;
                break;
            }
        }
    }
    //judge situation of the game (lose)
    if (score == 10){
        cout << "The word was: " << W << "\nYou lost!" << endl;
    }
    return 0;
}
