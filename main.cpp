#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
#include "4char.h"
#include "5char.h"
#include "6char.h"
#include "7char.h"
#include "8char.h"

using namespace std;

// Colors and tweaks on printing text
#define DEFAULT "\033[0m"
#define UNDERLINE "\033[4m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"


// a struct to save player data
struct Player{
    bool isPlaying;           // boolean expression to see if player is playing game
    int streak;             // the current winning streak
    int highestWinStreak;   // historical highest win streak
    vector<int> record[5];  // vector array to store player results

    // initialize the Pllayer struct
    void init(){
        isPlaying = false;
        streak = 0;
        highestWinStreak = 0;
        for (int i = 0; i < 5; i++){
            record[i].clear();
        }

    }
    // add record to the struct
    // int wordlen: the length of the word that the user has chosen
    // int trial: the amount of tries for the user to win the game, 0 if failed
    void addRecord(int wordLen, int trial){
        if (trial != 0){
            streak += 1;
            record[wordLen - 4].push_back(trial);
        }

        if (trial == 0){
            streak = 0;
        }

        if (streak > highestWinStreak){
            highestWinStreak = streak;
        }
    }

    // load data from player.save to the struct
    void loadData(){
        ifstream fin;
        fin.open("player.save");
        if (fin.fail()){
            cout << "Error! player.save does not exist! (Ignore if you are a new player)" << endl;
            return;
        }
        else{
            string s;
            getline(fin, s);
            // load the boolean to check if player was playing
            if ("true" == s){
                isPlaying = true;
            }
            if ("false" == s){
                isPlaying = false;
            }

            // load the win streaks to the struct
            getline(fin, s);
            streak = stoi(s);
            getline(fin, s);
            highestWinStreak = stoi(s);

            // load the array of vectors to the array
            for (int i = 0; i < 5; i++){
                getline(fin, s);
                int vectorSize = stoi(s);
                for (int j = 0; j < vectorSize; j++){
                    getline(fin, s);
                    record[i].push_back(stoi(s));
                }
            }
        }
        fin.close();
    }

    // save data in player struct to a file named player.save
    void saveData(){
        // check if file exists
        ifstream fin("player.save");
        ofstream fout;
        if (fin){
            fin.close();
            remove("player.save");
            fout.open("player.save");
            
        }
        else{
            fin.close();
            // make new file
            fout.open("player.save");
        }


        // saving the state of current game
        if (isPlaying){
            fout << "true" <<"\n";
        }
        if (!isPlaying){
            fout << "false" << "\n";
        }

        // saving current win streak and highest win streak
        fout << streak << "\n";
        fout << highestWinStreak << "\n";

        // saving the vector with size then the data
        for (int i = 0; i < 5; i++){
            fout << record[i].size() << "\n";
            if (!record[i].empty()){
                for (int j = 0; j < record[i].size(); j++){
                    fout << record[i][j] << "\n";
                }
            }
        }
        fout.close();
    }

    void showStats(int wordLen){
        int total = 0;
        int totalSuccessful = 0;

        // set a loading screen for user to wait
        cout << "Loading...\n" << endl;
        cout << "Here is your stats of WORDLE of " << wordLen << " character:" << endl;
        if (record[wordLen-4].size() != 0){
            int count[6];       // counting the successful trials for length wordLen
            int percentage[6];  // percentage of successful trials to total
            // initialize array
            for (int i = 0; i < 6; i++){
                count[i] = 0;
            }
            // counting records
            for (int i = 0; i < record[wordLen-4].size(); i++){
                count[record[wordLen-4][i] - 1] ++;
            }

            // progress bar for desired length
            for (int i = 0; i < 6; i++){
                string percentageBar;
                percentage[i] = count[i] * 100/ record[wordLen - 4].size();
                count[i] = percentage[i]/2;

                for (int j = 0; j < 50; j++){
                    if (count[i] > j){
                        percentageBar += "@";
                    }
                    else{
                        percentageBar += " ";
                    }
                }
                cout << i+1 << " [" << percentageBar << "] " << percentage[i] << "%" << endl;
            }
            cout << endl;
        }
        else{
            cout << "Sorry! You haven't played once on this length of wordle!" << endl;
        }

        cout << "Brief summary on the success rate of all lengths:" << endl;
        for (int i = 0; i < 5; i++){
            // prevent the case of zero division
            if (record[i].size() != 0){
                int successful = 0;
                for (int j = 0; j < record[i].size(); j++){
                    if (record[i][j] != 0){
                        successful++;
                    }
                }

                // print the chance of winnin
                cout << "Your success rate on " << i+4 << " character is: " << successful * 100 / record[i].size() << "%." << endl;
                total += record[i].size();
                totalSuccessful += successful;
            }
            else{
                cout << "You haven't played the " << i+4 << " character version of wordle!" << endl;
            }
        }
        if (total == 0){
            cout << "You have not played the game once!" << endl ; 
        }
        else{
            cout << "Your Overall success rate is about: " << totalSuccessful / total << "%." << endl;
        }
        cout << "Current Win Streak: " << streak << endl;
        cout << "Highest Win Streak: " << highestWinStreak << endl;
    }
};

// struct for storing game data
struct Game{
    string target;
    vector<string> trials;
    
    // initialize the Game struct
    void init(string t){
        target = t;
        trials.clear();
    };

    // accepts the colored string
    void addTrial(string trial){
        trials.push_back(trial);
    }

    // load the game from the round.save
    void loadTrial(){
        ifstream fin;
        fin.open("round.save");
        if (fin.fail()){
            cout << "Error! round.save does not exist! (ignore if you did not quit at the middle of the game)" << endl;
        }
        else{
            string s;
            getline(fin, s);
            // load the boolean to check if player was playing
            target = s;

            getline(fin, s);
            int vectorSize = stoi(s);
            // load the int array of total playtime
            for (int i = 0; i < vectorSize; i++) {
                getline(fin, s);
                trials.push_back(s);
            }
        }
    }

    // save the game to round.save
    void saveTrial(){
        ofstream fout("round.save");
        // saving the state of current game
        fout << target << "\n";

        // saving the size of trials and the words tried
        fout << trials.size() << "\n";
        for (int j = 0; j < trials.size(); j++){
            fout << trials[j] << "\n";
        }
    }

    // print all the attempts in the vector or hyphens
    void printResults(){
        int len = target.length();
        string empty;

        for(int i = 0; i < len; i++){
            empty += "-";
        }
        
        for (int i = 0; i < 6; i++){
            if (i < trials.size()){
                cout << trials[i] << endl;
            }
            else{
                cout << empty << endl;
            }
        }
    }
};



void startScreen(){
    cout << "###########################################" << endl;
    cout << "##            Upgraded Wordle            ##" << endl;
    cout << "##---------------------------------------##" << endl;
    cout << "##   Select from the following options   ##" << endl;
    cout << "##       1. Start New Game               ##" << endl;
    cout << "##       2. Load Game from save          ##" << endl;
    cout << "##       3. Check Player Stats           ##" << endl;
    cout << "##       4. How to Play                  ##" << endl;
    cout << "##       5. Save and Quit                ##" << endl;
    cout << "##                                       ##" << endl;
    cout << "###########################################" << endl;
}


// printing the rules of the game
void howToPlay(){
    cout << endl;
    cout << "Rules: " << endl;
    cout << "1. Guess the WORDLE of your desired length in six tries.\n" << endl;
    cout << "2. Each guess must be a valid five-letter word. Hit the enter button to submit.\n" << endl;
    cout << "3. After each guess, the color of the tiles will change to show how close your guess is to the word.\n" << endl;

    cout << "Examples:" << endl;
    cout << "Suppose the WORDLE is WRITE and the use input WHEAT." << endl;
    cout << "The output will be ";
    cout << GREEN << "W" << DEFAULT << "H" << YELLOW << "E" << DEFAULT << "A" << YELLOW << "T" << DEFAULT << endl;
    cout << endl;
    
    cout << "Explanation: " << endl;
    cout << "The letter W exists in the WORDLE and is located in the correct position." << endl;
    cout << "Hence, it will be shown in " << GREEN << "green" << DEFAULT << " color.\n" << endl;
    cout << "The letters E and T also exist in the WORDLE but aren't located in the correct position." << endl;
    cout << "Hence, they will be shown in " << YELLOW << "yellow" << DEFAULT << " color.\n" << endl;
    cout << "The letters H and A don't exist in the WORDLE." << endl;
    cout << "Hence, they will be shown in default color.\n" << endl;
    
}


string colorize(string target, string input){
    bool isInTarget = false;
    string s;
    int targetOccur[26];
        
    // initialize occurences 
    for (int i = 0; i < 26; i++){
        targetOccur[i] = 0;
    }

    // increment the count of character
    for (int i = 0; i < target.length(); i++){
        targetOccur[target[i] - 'A']++;
    }

    // add colors to the character according to the rules
    for (int i = 0; i < target.length(); i++){
        isInTarget = false;
        if (target[i] == input[i] && targetOccur[input[i] - 'A'] != 0){
            s += (string(GREEN) + input[i] + string(DEFAULT));
            targetOccur[input[i] - 'A']--;
        }

        else{
            for (int j = 0; j < target.length(); j++){
                if (input[i] == target[j] && i != j && targetOccur[input[i] - 'A'] != 0){
                    s += (string(YELLOW) + input[i] + string(DEFAULT));
                    targetOccur[input[i] - 'A']--;
                    isInTarget = true;
                    break;
                }
            }
            if (!isInTarget){
                s += input[i];
            }
        }
    }
    return s;
}

// game function
void playGame(Player &user, Game &game){
    int trial = 0;
    string length;
    string userGuess;
    string colorizedGuess;

    // ask user for length of word
    cout << "Which character length of WORDLE do you want to play? (4-8): ";
    cin >> length;
    while (!("4" == length || "5" == length || "6" == length || "7" == length || "8" == length)){
        cout << "Invalid length! Please try again." << endl;
        cout << "Which character length of WORDLE do you want to play? (4-8): ";
        cin >> length;
    }
    user.isPlaying = true;
    
    // get the target string
    switch(stoi(length)){
        case 4:
            game.init(random4Word());
            break;
        case 5:
            game.init(random5Word());
            break;
        case 6:
            game.init(random6Word());
            break;
        case 7:
            game.init(random7Word());
            break;
        case 8:
            game.init(random8Word());
            break;

    };


    for (int i = 0; i < 6; i++){
        // input
        bool check = false;
        while (!check){
            cout << "Enter your guess in BLOCK letters: ";
            cin >> userGuess;

            if (userGuess == "QUIT"){
                cout << "Leaving now, saving data..." << endl;
                game.saveTrial();
                user.saveData();
                cout << "Your data has been saved. See you soon!" << endl;
                cout << "---------------------------------------------------" << endl;
                exit(0);
            }
            
            if (userGuess.length() != stoi(length)){
                cout << "Please enter your trial with correct length." << endl;
                cout << "---------------------------------------------------" << endl;
                continue;
            }

            if (all_of(userGuess.begin(), userGuess.end(), [](unsigned char c){return isalpha(c);})){
                if (all_of(userGuess.begin(), userGuess.end(), [](unsigned char c){return isupper(c);})){
                    break;
                }
            }
            cout << "Please enter BLOCK letters and try again. " << endl;
            cout << "---------------------------------------------------" << endl;
        }

        //checking if the words match and print the characters in colors if so
        colorizedGuess = colorize(game.target, userGuess);
        game.addTrial(colorizedGuess);
        
        game.printResults();
        if (userGuess == game.target){
            trial = i + 1;
            break;
        }
    }
    
    
    if (trial > 0 &&trial <= 6 ){
        cout << "Congratulations! You have guessed the correct word in " << trial << " times!" << endl;
        
        
    }
    else{
        trial = 0;
        cout << "Sorry, you have reached maximium tries!" << endl;
        cout << "The answer is " << game.target << "!" << endl;
    }
    // file saving
    user.addRecord(stoi(length), trial);
    user.isPlaying = false;

    cout << "Bringing you back to the Main Menu..." <<endl;
    cout << "---------------------------------------------------" << endl;
}



int main(){
    int trial = 0;
    string option;
    Player user;
    Game round;

    // print the main menu
    user.init();
    startScreen();

    cout << "Type Your Option (1-5): ";
    cin >> option;
    while (option != "5"){
        if (option == "1"){  //  1. Start New Game
            // force the user to load game
            ifstream finGame("round.save");
            if (finGame.good()){
                round.loadTrial();
            }
        
            

            // main game session goes here
            playGame(user, round);
        }


        else if (option == "2"){  // 2. Load Game from save
            user.loadData();
            round.loadTrial();
        }


        else if (option == "3"){  // 3. Check Player Stats
            string length;
            cout << "Which character length would you like to check? (4-8): ";
            cin >> length;
            while (true){
                if (length == "4" || length == "5" || length == "6" || length == "7" || length == "8"){
                    user.showStats(stoi(length));
                    break;
                }
                cout << "Invalid Option! Please try again." << endl;
                cout << "Which character length would you like to check? (4-8): ";
                cin >> length;
            }
        }


        else if (option == "4"){  // print the rules of the game
            howToPlay();
        }

        else{
            cout << "Invalid Option! Please try again." << endl; 
        }
        cout << "---------------------------------------------------" << endl;
        
        startScreen();
        cout << "Type Your Option (1-5): ";
        cin >> option;
    }
    user.saveData();
    cout << "Goodbye! Now Quitting..." << endl;
}