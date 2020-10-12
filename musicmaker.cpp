#include <iostream>
#include <string.h>
#include <ctime>
#include <vector>

class Music {
public:
  int measures;
  int timeSig[2] = {4, 4};
  int key;
  int scale;
  std::vector<std::string> notes = {"A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#"};
  std::vector<std::string> chords = {"", "m", "7", "m7"};

  //use the circlular array algorithm to modify the notes vector to start with a given tonic
  std::vector<std::string> circle(int tonic){
    std::vector<std::string> newNotes;
    //Take the tonic and onward and put it at the front of the new vector
    for(int i = tonic; i < notes.size(); i++)
      newNotes.push_back(notes[i]);
    //Take the notes before the tonic and put it at the end of the new vector
    for(int i = 0; i < tonic; i++) newNotes.push_back(notes[i]);
    return newNotes;
  }

  //Will generate an array with notes in a scale based on a chord
  std::vector<int> calculateSteps(int chord){
    std::vector<int> steps;
    switch(chord){
      case 2:
      case 0:
        steps = {0, 2, 4, 5, 7, 9, 11};
        break;
      case 3:
      case 1:
        steps = {0, 2, 3, 5, 7, 8, 10};
    }
    return steps;
  }

  //Get all the details for the song
  void details(){
    //Setup random numbers
    srand(time(0));
    measures = (std::rand() % 9 + 8);
    int max = (notes.size());
    srand(time(0));
    key = (std::rand() % max);
    max = (chords.size());
    scale = std::rand() % max;
    std::string chord = chords[scale];

    //output basic details for debug purposes
    std::cout << measures << " " << timeSig[0] << "/" << timeSig[1] << " " << notes[key] << chord << std::endl;
  }
  //};

//class Chords : public Music {
//public:
    //Generates a random, simple, chord progression.
    std::vector<int> chordProgression(){
      std::vector<int> prog;
      switch(std::rand() % 3){
      case 0:
        prog = {0,5,1,4};
        break;
      case 1:
        prog = {1,4,0};
        break;
      case 2:
        prog = {5, 6, 0, 0};
        break;
      case 3:
        prog = {0, 3, 4, 0};
    }
    return prog;
  }

    //This should be in it's own function and return a vector with the scale.
    //it's here for proof of concept
    //This will also need a check for a 7th key. That will be added here
    void genChords(){
      std::vector<std::string> newNotes = circle(key);
      std::vector<int> steps = calculateSteps(scale);
      std::vector<int> prog = chordProgression();
      //get scale of the key
      std::vector<std::string> possibleChords;
      std::cout << "Order of scale" << std::endl;
      if (scale == 0 || scale == 2){
        for(int i = 0; i < steps.size(); i++){
          switch(i){
          case 1:
          case 2:
          case 5:
            possibleChords.push_back(newNotes[steps[i]] + "m");
            break;
          case 6:
            possibleChords.push_back(newNotes[steps[i]] + "dim");
          default:
            possibleChords.push_back(newNotes[steps[i]]);
          }
        }
      } else {
        for(int i = 0; i < steps.size(); i++){
          switch(i){
          case 2:
          case 5:
          case 6:
            possibleChords.push_back(newNotes[steps[i]]);
            break;
          case 1:
            possibleChords.push_back(newNotes[steps[i]] + "dim");
            break;
          default:
            possibleChords.push_back(newNotes[steps[i]] + "m");
          }
        }
      }
      for(int i = 0; i < possibleChords.size(); i++){
        std::cout << possibleChords[i] << std::endl;
      }
      //Get progression.
      std::cout << "Chord Progression" << std::endl;
      for(int i = 0; i < prog.size(); i++){
        std::cout << possibleChords[prog[i]] << std::endl;
      }
    }
};

class Bar : public Music {
  struct note {
    int length;
    std::string pitch;
  };

  //std::vector<std::string> genNotes(std::string chord){
    //Generate notes based on an inputted chord
    // }

};


int main(){
  Music music;
  //Chords chrd;
  music.details();
  music.genChords();
  return 0;
}
