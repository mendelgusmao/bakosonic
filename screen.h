#include "tv.h"

class Screen {
public:
  static int index;
  void handle(TV &tv, const int key);
};

class StandbyScreen : 
public Screen {
public:
  static int index;
  void handle(TV &tv, const int key);
};

class MainScreen : 
public Screen {
public:
  static int index;
  void handle(TV &tv, const int key);
};

class TuningScreen : 
public Screen {
public:
  static int index;
  void handle(TV &tv, const int key);
};

class SetupScreen : 
public Screen {
public:
  static int index;
  void handle(TV &tv, const int key);
};


