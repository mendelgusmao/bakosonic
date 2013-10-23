#include "screen.h"

void StandbyScreen::handle(TV &tv, const int key) {
    if (key == KEY_ONOFF) tv.toggle();
}

void MainScreen::handle(TV &tv, const int key) {
  switch (key) {
  case KEY_ONOFF:
    tv.toggle();
    break;

  case KEY_CHAN_UP:
    ++tv.channel;
    tv.channel.write();
    tv.channel.apply();
    break;

  case KEY_CHAN_DOWN:
    --tv.channel;
    tv.channel.write();
    tv.channel.apply();
    break;

  case KEY_VOL_UP:
    ++tv.volume;
    tv.volume.write();
    tv.volume.apply();
    break;

  case KEY_VOL_DOWN:
    --tv.volume;
    tv.volume.write();
    tv.volume.apply();
    break;

  case KEY_SETUP:
    // change_screen(SCREEN_SETUP1);
    break;	
  }
}

void TuningScreen::handle(TV &tv, const int key) {
  switch (key) {
  case KEY_ONOFF:
    tv.channel.write();
    break;

  case KEY_CHAN_UP:
    ++tv.channel;
    tv.channel.apply();
    break;

  case KEY_CHAN_DOWN:
    --tv.channel;
    tv.channel.apply();
    break;

  case KEY_VOL_UP:
    ++tv.volume;
    tv.volume.apply();
    break;

  case KEY_VOL_DOWN:
    --tv.volume;
    tv.volume.apply();
    break;

  case KEY_SETUP:
    // change_screen(SCREEN_SETUP);
    break;  
  }
}

void SetupScreen::handle(TV &tv, const int key) {
  switch (key) {
  case KEY_ONOFF:
    break;

  case KEY_CHAN_UP:
    break;

  case KEY_CHAN_DOWN:
    break;

  case KEY_VOL_UP:
    break;

  case KEY_VOL_DOWN:
    break;

  case KEY_SETUP:
    // change_screen(SCREEN_MAIN);
    break;  
  }  
}
