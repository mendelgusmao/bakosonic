#include "screen.h"

int oldChannel;
int oldBrightness;
int oldContrast;
int oldVertical;

void StandbyScreen::handle(TV &tv, const int key) {
  if (key != KEY_ONOFF) return;
  tv.toggle();
  Screen::index = SCREEN_MAIN;
}

void MainScreen::handle(TV &tv, const int key) {
  switch (key) {
  case KEY_ONOFF:
    tv.toggle();
    break;

  case KEY_CHAN_UP:
    ++tv.channel;
    tv.channel.write();
    break;

  case KEY_CHAN_DOWN:
    --tv.channel;
    tv.channel.write();
    break;

  case KEY_VOL_UP:
    ++tv.volume;
    tv.volume.write();
    break;

  case KEY_VOL_DOWN:
    --tv.volume;
    tv.volume.write();
    break;

  case KEY_SETUP:
    oldChannel = tv.channel.get();
    oldBrightness = tv.brightness.get();
    oldContrast = tv.contrast.get();
    oldVertical = tv.vertical.get();

    Screen::index = SCREEN_TUNING;
    break;	
  }
}

void TuningScreen::handle(TV &tv, const int key) {
  switch (key) {
  case KEY_ONOFF:
    tv.channel.write();
    Screen::index = SCREEN_MAIN;
    break;

  case KEY_CHAN_UP:
    ++tv.channel;
    break;

  case KEY_CHAN_DOWN:
    --tv.channel;
    break;

  case KEY_VOL_UP:
    ++tv.channel.tuning;
    break;

  case KEY_VOL_DOWN:
    --tv.channel.tuning;
    break;

  case KEY_SETUP:
    Screen::index = SCREEN_SETUP;
    break;  
  }
}

void SetupScreen::handle(TV &tv, const int key) {
  switch (key) {
  case KEY_ONOFF:
    tv.brightness.write();
    tv.contrast.write();
    tv.vertical.write();
    Screen::index = SCREEN_MAIN;
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
    tv.channel.set(oldChannel);
    tv.brightness.set(oldBrightness);
    tv.contrast.set(oldContrast);
    tv.vertical.set(oldVertical);

    Screen::index = SCREEN_MAIN;
    break;  
  }  
}


