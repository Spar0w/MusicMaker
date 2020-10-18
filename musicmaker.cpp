#include <iostream>
#include <string.h>
#include <ctime>
#include <unistd.h>
#include <vector>

class Music {
public:
  int measures;
  int timeSig[3] = {3, 4, 4};
  //int key;
  //int scale;
  std::vector<std::string> notes = {"A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#"};
  std::vector<std::string> orderedNotes;
  //enum notes{A, A#, B, C, C#, D, D#, E, F, F#, G, "G#"};}
  std::vector<std::string> chords = {"", "m", "7", "m7"};

  struct Note {
    float length;
    std::string pitch;
  };

  //use the circlular array algorithm to modify the notes vector to start with a given tonic
  std::vector<std::string> circle(int tonic, std::vector<std::string> notes){
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
        break;
    }
    return steps;
  }

};

class Chords : virtual public Music {
public:
    std::vector<std::string> possibleChords;

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
  std::vector<std::string> genChords(int key, int scale, std::vector<std::string> notes){
      std::vector<std::string> newNotes = circle(key, notes);
      std::vector<int> steps = calculateSteps(scale);
      std::vector<int> prog = chordProgression();
      //get scale of the key
      // std::vector<std::string> possibleChords;
      possibleChords.clear();
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
      //Get progression.
      std::vector<std::string> chords_used;
      for(int i = 0; i < prog.size(); i++){
        chords_used.push_back(possibleChords[prog[i]]);
      }
      orderedNotes = newNotes;
      return chords_used;
    }
};

class Song : virtual public Music, public Chords {
public:
  int key;
  int scale;
  int beats;

  //Get all the details for the song
  void details(){
    int tempo = rand() % 30 + 80;
    srand(time(0) * rand() % 10);
    beats = rand() % 2;
    //Setup random numbers
    measures = 16;//(std::rand() % 9 + 8);
    std::string chord = chords[scale];
    genChords(key, scale, notes);
      //output basic details for debug purposes
    std::cout << measures << " " << timeSig[beats] << "/" << timeSig[2] << " " << notes[key] << chord << " " << tempo << "bpm" << std::endl << std::endl;
  }

  void random_notes(){
    srand(time(0));
    float time = 0;
    std::vector<float> rythm = {0.5, 1, 2};
    std::vector<int> range = {4, 5, 6};
    while(time != timeSig[beats] || time > timeSig[beats]){
      if(time > timeSig[beats]){
        break;
      } else {
        float duration = rythm[rand() % rythm.size()];
        int note_num = rand() % possibleChords.size();
        std::cout << chord_note(possibleChords[note_num]);
        std::cout << " for " << duration << " beats ";
        std::cout << "at Interval: " << note_num;
        std::cout << "| Pitch: " << range[rand() % range.size()] << std::endl;
        time += duration;
      }
      //std::cout << time << " " << duration << std::endl; if this line is here, it just goes indefinetly?
    }
    std::cout << std::endl;
  }

  std::string chord_note(std::string chord){
    std::string new_chord = "aa";
    new_chord[0] = chord.front();
    if(chord[1]){
      switch(chord[1]){
        case '#':
          new_chord[1] = '#';
          break;
      default:
        new_chord = new_chord[0];
      }
    } else {
      return new_chord.erase(1);
    }
    return new_chord;
  }

  //return a vector of notes based on an inputted chord.
  //input chord -> generate notes that work in that chord (just genChords again) -> pick random notes in there -> return that vector
  std::vector<std::string> measure(std::string chord){
    std::vector<std::string> test_notes;
    std::vector<std::string> notes_played;
    for(int bars = 0; bars < 4; bars++){
      for (int i = 0; i < notes.size(); i++){
        if(chord_note(chord) == notes[i]){
          std::cout << "Found Chord: ";
          std::cout << chord_note(chord);
          std::cout << " at: " << i << std::endl;
          genChords(i, scale, orderedNotes);
          random_notes();
          sleep(2);
        }
      }
    }
    //std::cout << "Random note test" << std::endl;
    return notes_played;
  }

  void test(){
    details();
    std::vector<std::string> chrds = genChords(key, scale, notes);
    for(int i = 0; i < chrds.size(); i++){
      measure(chrds[i]);
    }
    std::cout << std::endl;
    std::cout << "Chord Progression" << std::endl;
    for(int i = 0; i < chrds.size(); i++){
      std::cout << chrds[i] << std::endl;
    }
    std::cout << std::endl;
    /* This exists for debug purposes
    std::cout << "Order of scale" << std::endl;
    for(int i = 0; i < possibleChords.size(); i++){
      std::cout << possibleChords[i] << std::endl;
    }
    //std::cout << "Random note test" << std::endl;
    //std::vector<std::string> notes = measure(6);
    for(int i = 0; i < notes.size(); i++){
      std::cout << notes[i] << std::endl;
      }*/
  }
};

int main(){
  Song song;
  srand(time(0));
  song.key = (std::rand() % song.notes.size());
  srand(time(0));
  song.scale = (std::rand() % song.chords.size());
  song.test();
  return 0;
}
