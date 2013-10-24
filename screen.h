#include "tv.h"

class Screen {
public:
  static int index;
  static Screen* screens[SCREENS];
  void handle(TV &tv, const int key);
};

class StandbyScreen : 
public Screen {
public:
  void handle(TV &tv, const int key);
};

class MainScreen : 
public Screen {
public:
  void handle(TV &tv, const int key);
};

class TuningScreen : 
public Screen {
public:
  void handle(TV &tv, const int key);
};

class SetupScreen : 
public Screen {
public:
  void handle(TV &tv, const int key);
};


