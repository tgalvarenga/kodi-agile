/*
 *      Copyright (C) 2005-2017 Team Kodi
 *      http://kodi.tv
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with KODI; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "General.h"
#include "ControlButton.h"
#include "ControlEdit.h"
#include "ControlFadeLabel.h"
#include "ControlImage.h"
#include "ControlLabel.h"
#include "ControlProgress.h"
#include "ControlRadioButton.h"
#include "ControlRendering.h"
#include "ControlSettingsSlider.h"
#include "ControlSlider.h"
#include "ControlSpin.h"
#include "ControlTextBox.h"
#include "DialogContextMenu.h"
#include "DialogExtendedProgressBar.h"
#include "DialogFileBrowser.h"
#include "DialogKeyboard.h"
#include "DialogNumeric.h"
#include "DialogOK.h"
#include "DialogProgress.h"
#include "DialogSelect.h"
#include "DialogTextViewer.h"
#include "DialogYesNo.h"
#include "ListItem.h"
#include "Window.h"
#include "addons/kodi-addon-dev-kit/include/kodi/gui/General.h"

#include "addons/AddonDll.h"
#include "input/Key.h"
#include "guilib/GUIWindowManager.h"
#include "utils/log.h"

using namespace kodi; // addon-dev-kit namespace
using namespace kodi::gui; // addon-dev-kit namespace

namespace ADDON
{
int Interface_GUIGeneral::m_iAddonGUILockRef = 0;
};

extern "C"
{

namespace ADDON
{

  
int GetAddonGUIActionType(int kodiAction)
{
  switch (kodiAction)
  {
    case ACTION_NONE                   : return ADDON_ACTION_NONE;
    case ACTION_MOVE_LEFT              : return ADDON_ACTION_MOVE_LEFT;
    case ACTION_MOVE_RIGHT             : return ADDON_ACTION_MOVE_RIGHT;
    case ACTION_MOVE_UP                : return ADDON_ACTION_MOVE_UP;
    case ACTION_MOVE_DOWN              : return ADDON_ACTION_MOVE_DOWN;
    case ACTION_PAGE_UP                : return ADDON_ACTION_PAGE_UP;
    case ACTION_PAGE_DOWN              : return ADDON_ACTION_PAGE_DOWN;
    case ACTION_SELECT_ITEM            : return ADDON_ACTION_SELECT_ITEM;
    case ACTION_HIGHLIGHT_ITEM         : return ADDON_ACTION_HIGHLIGHT_ITEM;
    case ACTION_PARENT_DIR             : return ADDON_ACTION_PARENT_DIR;
    case ACTION_PREVIOUS_MENU          : return ADDON_ACTION_PREVIOUS_MENU;
    case ACTION_SHOW_INFO              : return ADDON_ACTION_SHOW_INFO;
    case ACTION_PAUSE                  : return ADDON_ACTION_PAUSE;
    case ACTION_STOP                   : return ADDON_ACTION_STOP;
    case ACTION_NEXT_ITEM              : return ADDON_ACTION_NEXT_ITEM;
    case ACTION_PREV_ITEM              : return ADDON_ACTION_PREV_ITEM;
    case ACTION_FORWARD                : return ADDON_ACTION_FORWARD;
    case ACTION_REWIND                 : return ADDON_ACTION_REWIND;
    case ACTION_SHOW_GUI               : return ADDON_ACTION_SHOW_GUI;
    case ACTION_ASPECT_RATIO           : return ADDON_ACTION_ASPECT_RATIO;
    case ACTION_STEP_FORWARD           : return ADDON_ACTION_STEP_FORWARD;
    case ACTION_STEP_BACK              : return ADDON_ACTION_STEP_BACK;
    case ACTION_BIG_STEP_FORWARD       : return ADDON_ACTION_BIG_STEP_FORWARD;
    case ACTION_BIG_STEP_BACK          : return ADDON_ACTION_BIG_STEP_BACK;
    case ACTION_SHOW_OSD               : return ADDON_ACTION_SHOW_OSD;
    case ACTION_SHOW_SUBTITLES         : return ADDON_ACTION_SHOW_SUBTITLES;
    case ACTION_NEXT_SUBTITLE          : return ADDON_ACTION_NEXT_SUBTITLE;
    case ACTION_PLAYER_DEBUG           : return ADDON_ACTION_PLAYER_DEBUG;
    case ACTION_NEXT_PICTURE           : return ADDON_ACTION_NEXT_PICTURE;
    case ACTION_PREV_PICTURE           : return ADDON_ACTION_PREV_PICTURE;
    case ACTION_ZOOM_OUT               : return ADDON_ACTION_ZOOM_OUT;
    case ACTION_ZOOM_IN                : return ADDON_ACTION_ZOOM_IN;
    case ACTION_TOGGLE_SOURCE_DEST     : return ADDON_ACTION_TOGGLE_SOURCE_DEST;
    case ACTION_SHOW_PLAYLIST          : return ADDON_ACTION_SHOW_PLAYLIST;
    case ACTION_QUEUE_ITEM             : return ADDON_ACTION_QUEUE_ITEM;
    case ACTION_REMOVE_ITEM            : return ADDON_ACTION_REMOVE_ITEM;
    case ACTION_SHOW_FULLSCREEN        : return ADDON_ACTION_SHOW_FULLSCREEN;
    case ACTION_ZOOM_LEVEL_NORMAL      : return ADDON_ACTION_ZOOM_LEVEL_NORMAL;
    case ACTION_ZOOM_LEVEL_1           : return ADDON_ACTION_ZOOM_LEVEL_1;
    case ACTION_ZOOM_LEVEL_2           : return ADDON_ACTION_ZOOM_LEVEL_2;
    case ACTION_ZOOM_LEVEL_3           : return ADDON_ACTION_ZOOM_LEVEL_3;
    case ACTION_ZOOM_LEVEL_4           : return ADDON_ACTION_ZOOM_LEVEL_4;
    case ACTION_ZOOM_LEVEL_5           : return ADDON_ACTION_ZOOM_LEVEL_5;
    case ACTION_ZOOM_LEVEL_6           : return ADDON_ACTION_ZOOM_LEVEL_6;
    case ACTION_ZOOM_LEVEL_7           : return ADDON_ACTION_ZOOM_LEVEL_7;
    case ACTION_ZOOM_LEVEL_8           : return ADDON_ACTION_ZOOM_LEVEL_8;
    case ACTION_ZOOM_LEVEL_9           : return ADDON_ACTION_ZOOM_LEVEL_9;
    case ACTION_CALIBRATE_SWAP_ARROWS  : return ADDON_ACTION_CALIBRATE_SWAP_ARROWS;
    case ACTION_CALIBRATE_RESET        : return ADDON_ACTION_CALIBRATE_RESET;
    case ACTION_ANALOG_MOVE            : return ADDON_ACTION_ANALOG_MOVE;
    case ACTION_ROTATE_PICTURE_CW      : return ADDON_ACTION_ROTATE_PICTURE_CW;
    case ACTION_ROTATE_PICTURE_CCW     : return ADDON_ACTION_ROTATE_PICTURE_CCW;
    case ACTION_SUBTITLE_DELAY_MIN     : return ADDON_ACTION_SUBTITLE_DELAY_MIN;
    case ACTION_SUBTITLE_DELAY_PLUS    : return ADDON_ACTION_SUBTITLE_DELAY_PLUS;
    case ACTION_AUDIO_DELAY_MIN        : return ADDON_ACTION_AUDIO_DELAY_MIN;
    case ACTION_AUDIO_DELAY_PLUS       : return ADDON_ACTION_AUDIO_DELAY_PLUS;
    case ACTION_AUDIO_NEXT_LANGUAGE    : return ADDON_ACTION_AUDIO_NEXT_LANGUAGE;
    case ACTION_CHANGE_RESOLUTION      : return ADDON_ACTION_CHANGE_RESOLUTION;

    case REMOTE_0                      : return ADDON_REMOTE_0;
    case REMOTE_1                      : return ADDON_REMOTE_1;
    case REMOTE_2                      : return ADDON_REMOTE_2;
    case REMOTE_3                      : return ADDON_REMOTE_3;
    case REMOTE_4                      : return ADDON_REMOTE_4;
    case REMOTE_5                      : return ADDON_REMOTE_5;
    case REMOTE_6                      : return ADDON_REMOTE_6;
    case REMOTE_7                      : return ADDON_REMOTE_7;
    case REMOTE_8                      : return ADDON_REMOTE_8;
    case REMOTE_9                      : return ADDON_REMOTE_9;

    case ACTION_PLAY                   : return ADDON_ACTION_PLAY;
    case ACTION_PLAYER_PROCESS_INFO    : return ADDON_ACTION_PLAYER_PROCESS_INFO;
    case ACTION_SMALL_STEP_BACK        : return ADDON_ACTION_SMALL_STEP_BACK;

    case ACTION_PLAYER_FORWARD         : return ADDON_ACTION_PLAYER_FORWARD;
    case ACTION_PLAYER_REWIND          : return ADDON_ACTION_PLAYER_REWIND;
    case ACTION_PLAYER_PLAY            : return ADDON_ACTION_PLAYER_PLAY;

    case ACTION_DELETE_ITEM            : return ADDON_ACTION_DELETE_ITEM;
    case ACTION_COPY_ITEM              : return ADDON_ACTION_COPY_ITEM;
    case ACTION_MOVE_ITEM              : return ADDON_ACTION_MOVE_ITEM;
    case ACTION_TAKE_SCREENSHOT        : return ADDON_ACTION_TAKE_SCREENSHOT;
    case ACTION_RENAME_ITEM            : return ADDON_ACTION_RENAME_ITEM;

    case ACTION_VOLUME_UP              : return ADDON_ACTION_VOLUME_UP;
    case ACTION_VOLUME_DOWN            : return ADDON_ACTION_VOLUME_DOWN;
    case ACTION_VOLAMP                 : return ADDON_ACTION_VOLAMP;
    case ACTION_MUTE                   : return ADDON_ACTION_MUTE;
    case ACTION_NAV_BACK               : return ADDON_ACTION_NAV_BACK;
    case ACTION_VOLAMP_UP              : return ADDON_ACTION_VOLAMP_UP;
    case ACTION_VOLAMP_DOWN            : return ADDON_ACTION_VOLAMP_DOWN;

    case ACTION_CREATE_EPISODE_BOOKMARK: return ADDON_ACTION_CREATE_EPISODE_BOOKMARK;
    case ACTION_CREATE_BOOKMARK        : return ADDON_ACTION_CREATE_BOOKMARK;

    case ACTION_CHAPTER_OR_BIG_STEP_FORWARD: return ADDON_ACTION_CHAPTER_OR_BIG_STEP_FORWARD;
    case ACTION_CHAPTER_OR_BIG_STEP_BACK: return ADDON_ACTION_CHAPTER_OR_BIG_STEP_BACK;

    case ACTION_CYCLE_SUBTITLE         : return ADDON_ACTION_CYCLE_SUBTITLE;

    case ACTION_MOUSE_LEFT_CLICK       : return ADDON_ACTION_MOUSE_LEFT_CLICK;
    case ACTION_MOUSE_RIGHT_CLICK      : return ADDON_ACTION_MOUSE_RIGHT_CLICK;
    case ACTION_MOUSE_MIDDLE_CLICK     : return ADDON_ACTION_MOUSE_MIDDLE_CLICK;
    case ACTION_MOUSE_DOUBLE_CLICK     : return ADDON_ACTION_MOUSE_DOUBLE_CLICK;
    case ACTION_MOUSE_WHEEL_UP         : return ADDON_ACTION_MOUSE_WHEEL_UP;
    case ACTION_MOUSE_WHEEL_DOWN       : return ADDON_ACTION_MOUSE_WHEEL_DOWN;
    case ACTION_MOUSE_DRAG             : return ADDON_ACTION_MOUSE_DRAG;
    case ACTION_MOUSE_MOVE             : return ADDON_ACTION_MOUSE_MOVE;
    case ACTION_MOUSE_LONG_CLICK       : return ADDON_ACTION_MOUSE_LONG_CLICK;

    case ACTION_BACKSPACE              : return ADDON_ACTION_BACKSPACE;
    case ACTION_SCROLL_UP              : return ADDON_ACTION_SCROLL_UP;
    case ACTION_SCROLL_DOWN            : return ADDON_ACTION_SCROLL_DOWN;
    case ACTION_ANALOG_FORWARD         : return ADDON_ACTION_ANALOG_FORWARD;
    case ACTION_ANALOG_REWIND          : return ADDON_ACTION_ANALOG_REWIND;

    case ACTION_MOVE_ITEM_UP           : return ADDON_ACTION_MOVE_ITEM_UP;
    case ACTION_MOVE_ITEM_DOWN         : return ADDON_ACTION_MOVE_ITEM_DOWN;
    case ACTION_CONTEXT_MENU           : return ADDON_ACTION_CONTEXT_MENU;

    case ACTION_SHIFT                  : return ADDON_ACTION_SHIFT;
    case ACTION_SYMBOLS                : return ADDON_ACTION_SYMBOLS;
    case ACTION_CURSOR_LEFT            : return ADDON_ACTION_CURSOR_LEFT;
    case ACTION_CURSOR_RIGHT           : return ADDON_ACTION_CURSOR_RIGHT;

    case ACTION_BUILT_IN_FUNCTION      : return ADDON_ACTION_BUILT_IN_FUNCTION;

    case ACTION_SHOW_OSD_TIME          : return ADDON_ACTION_SHOW_OSD_TIME;
    case ACTION_ANALOG_SEEK_FORWARD    : return ADDON_ACTION_ANALOG_SEEK_FORWARD;
    case ACTION_ANALOG_SEEK_BACK       : return ADDON_ACTION_ANALOG_SEEK_BACK;

    case ACTION_VIS_PRESET_SHOW        : return ADDON_ACTION_VIS_PRESET_SHOW;
    case ACTION_VIS_PRESET_NEXT        : return ADDON_ACTION_VIS_PRESET_NEXT;
    case ACTION_VIS_PRESET_PREV        : return ADDON_ACTION_VIS_PRESET_PREV;
    case ACTION_VIS_PRESET_LOCK        : return ADDON_ACTION_VIS_PRESET_LOCK;
    case ACTION_VIS_PRESET_RANDOM      : return ADDON_ACTION_VIS_PRESET_RANDOM;
    case ACTION_VIS_RATE_PRESET_PLUS   : return ADDON_ACTION_VIS_RATE_PRESET_PLUS;
    case ACTION_VIS_RATE_PRESET_MINUS  : return ADDON_ACTION_VIS_RATE_PRESET_MINUS;

    case ACTION_SHOW_VIDEOMENU         : return ADDON_ACTION_SHOW_VIDEOMENU;
    case ACTION_ENTER                  : return ADDON_ACTION_ENTER;

    case ACTION_INCREASE_RATING        : return ADDON_ACTION_INCREASE_RATING;
    case ACTION_DECREASE_RATING        : return ADDON_ACTION_DECREASE_RATING;

    case ACTION_NEXT_SCENE             : return ADDON_ACTION_NEXT_SCENE;
    case ACTION_PREV_SCENE             : return ADDON_ACTION_PREV_SCENE;

    case ACTION_NEXT_LETTER            : return ADDON_ACTION_NEXT_LETTER;
    case ACTION_PREV_LETTER            : return ADDON_ACTION_PREV_LETTER;

    case ACTION_JUMP_SMS2              : return ADDON_ACTION_JUMP_SMS2;
    case ACTION_JUMP_SMS3              : return ADDON_ACTION_JUMP_SMS3;
    case ACTION_JUMP_SMS4              : return ADDON_ACTION_JUMP_SMS4;
    case ACTION_JUMP_SMS5              : return ADDON_ACTION_JUMP_SMS5;
    case ACTION_JUMP_SMS6              : return ADDON_ACTION_JUMP_SMS6;
    case ACTION_JUMP_SMS7              : return ADDON_ACTION_JUMP_SMS7;
    case ACTION_JUMP_SMS8              : return ADDON_ACTION_JUMP_SMS8;
    case ACTION_JUMP_SMS9              : return ADDON_ACTION_JUMP_SMS9;

    case ACTION_FILTER_CLEAR           : return ADDON_ACTION_FILTER_CLEAR;
    case ACTION_FILTER_SMS2            : return ADDON_ACTION_FILTER_SMS2;
    case ACTION_FILTER_SMS3            : return ADDON_ACTION_FILTER_SMS3;
    case ACTION_FILTER_SMS4            : return ADDON_ACTION_FILTER_SMS4;
    case ACTION_FILTER_SMS5            : return ADDON_ACTION_FILTER_SMS5;
    case ACTION_FILTER_SMS6            : return ADDON_ACTION_FILTER_SMS6;
    case ACTION_FILTER_SMS7            : return ADDON_ACTION_FILTER_SMS7;
    case ACTION_FILTER_SMS8            : return ADDON_ACTION_FILTER_SMS8;
    case ACTION_FILTER_SMS9            : return ADDON_ACTION_FILTER_SMS9;

    case ACTION_FIRST_PAGE             : return ADDON_ACTION_FIRST_PAGE;
    case ACTION_LAST_PAGE              : return ADDON_ACTION_LAST_PAGE;

    case ACTION_AUDIO_DELAY            : return ADDON_ACTION_AUDIO_DELAY;
    case ACTION_SUBTITLE_DELAY         : return ADDON_ACTION_SUBTITLE_DELAY;
    case ACTION_MENU                   : return ADDON_ACTION_MENU;

    case ACTION_SET_RATING             : return ADDON_ACTION_SET_RATING;

    case ACTION_RECORD                 : return ADDON_ACTION_RECORD;

    case ACTION_PASTE                  : return ADDON_ACTION_PASTE;
    case ACTION_NEXT_CONTROL           : return ADDON_ACTION_NEXT_CONTROL;
    case ACTION_PREV_CONTROL           : return ADDON_ACTION_PREV_CONTROL;
    case ACTION_CHANNEL_SWITCH         : return ADDON_ACTION_CHANNEL_SWITCH;
    case ACTION_CHANNEL_UP             : return ADDON_ACTION_CHANNEL_UP;
    case ACTION_CHANNEL_DOWN           : return ADDON_ACTION_CHANNEL_DOWN;
    case ACTION_NEXT_CHANNELGROUP      : return ADDON_ACTION_NEXT_CHANNELGROUP;
    case ACTION_PREVIOUS_CHANNELGROUP  : return ADDON_ACTION_PREVIOUS_CHANNELGROUP;
    case ACTION_PVR_PLAY               : return ADDON_ACTION_PVR_PLAY;
    case ACTION_PVR_PLAY_TV            : return ADDON_ACTION_PVR_PLAY_TV;
    case ACTION_PVR_PLAY_RADIO         : return ADDON_ACTION_PVR_PLAY_RADIO;
    case ACTION_PVR_SHOW_TIMER_RULE    : return ADDON_ACTION_PVR_SHOW_TIMER_RULE;

    case ACTION_TOGGLE_FULLSCREEN      : return ADDON_ACTION_TOGGLE_FULLSCREEN;
    case ACTION_TOGGLE_WATCHED         : return ADDON_ACTION_TOGGLE_WATCHED;
    case ACTION_SCAN_ITEM              : return ADDON_ACTION_SCAN_ITEM;
    case ACTION_TOGGLE_DIGITAL_ANALOG  : return ADDON_ACTION_TOGGLE_DIGITAL_ANALOG;
    case ACTION_RELOAD_KEYMAPS         : return ADDON_ACTION_RELOAD_KEYMAPS;
    case ACTION_GUIPROFILE_BEGIN       : return ADDON_ACTION_GUIPROFILE_BEGIN;

    case ACTION_TELETEXT_RED           : return ADDON_ACTION_TELETEXT_RED;
    case ACTION_TELETEXT_GREEN         : return ADDON_ACTION_TELETEXT_GREEN;
    case ACTION_TELETEXT_YELLOW        : return ADDON_ACTION_TELETEXT_YELLOW;
    case ACTION_TELETEXT_BLUE          : return ADDON_ACTION_TELETEXT_BLUE;

    case ACTION_INCREASE_PAR           : return ADDON_ACTION_INCREASE_PAR;
    case ACTION_DECREASE_PAR           : return ADDON_ACTION_DECREASE_PAR;

    case ACTION_VSHIFT_UP              : return ADDON_ACTION_VSHIFT_UP;
    case ACTION_VSHIFT_DOWN            : return ADDON_ACTION_VSHIFT_DOWN;

    case ACTION_PLAYER_PLAYPAUSE       : return ADDON_ACTION_PLAYER_PLAYPAUSE;

    case ACTION_SUBTITLE_VSHIFT_UP     : return ADDON_ACTION_SUBTITLE_VSHIFT_UP;
    case ACTION_SUBTITLE_VSHIFT_DOWN   : return ADDON_ACTION_SUBTITLE_VSHIFT_DOWN;
    case ACTION_SUBTITLE_ALIGN         : return ADDON_ACTION_SUBTITLE_ALIGN;

    case ACTION_FILTER                 : return ADDON_ACTION_FILTER;

    case ACTION_SWITCH_PLAYER          : return ADDON_ACTION_SWITCH_PLAYER;

    case ACTION_STEREOMODE_NEXT        : return ADDON_ACTION_STEREOMODE_NEXT;
    case ACTION_STEREOMODE_PREVIOUS    : return ADDON_ACTION_STEREOMODE_PREVIOUS;
    case ACTION_STEREOMODE_TOGGLE      : return ADDON_ACTION_STEREOMODE_TOGGLE;
    case ACTION_STEREOMODE_SELECT      : return ADDON_ACTION_STEREOMODE_SELECT;
    case ACTION_STEREOMODE_TOMONO      : return ADDON_ACTION_STEREOMODE_TOMONO;
    case ACTION_STEREOMODE_SET         : return ADDON_ACTION_STEREOMODE_SET;

    case ACTION_SETTINGS_RESET         : return ADDON_ACTION_SETTINGS_RESET;
    case ACTION_SETTINGS_LEVEL_CHANGE  : return ADDON_ACTION_SETTINGS_LEVEL_CHANGE;

    case ACTION_TRIGGER_OSD            : return ADDON_ACTION_TRIGGER_OSD;
    case ACTION_INPUT_TEXT             : return ADDON_ACTION_INPUT_TEXT;
    case ACTION_VOLUME_SET             : return ADDON_ACTION_VOLUME_SET;
    case ACTION_TOGGLE_COMMSKIP        : return ADDON_ACTION_TOGGLE_COMMSKIP;

    case ACTION_TOUCH_TAP              : return ADDON_ACTION_TOUCH_TAP;
    case ACTION_TOUCH_TAP_TEN          : return ADDON_ACTION_TOUCH_TAP_TEN;
    case ACTION_TOUCH_LONGPRESS        : return ADDON_ACTION_TOUCH_LONGPRESS;
    case ACTION_TOUCH_LONGPRESS_TEN    : return ADDON_ACTION_TOUCH_LONGPRESS_TEN;

    case ACTION_GESTURE_NOTIFY         : return ADDON_ACTION_GESTURE_NOTIFY;
    case ACTION_GESTURE_BEGIN          : return ADDON_ACTION_GESTURE_BEGIN;
    case ACTION_GESTURE_ZOOM           : return ADDON_ACTION_GESTURE_ZOOM;
    case ACTION_GESTURE_ROTATE         : return ADDON_ACTION_GESTURE_ROTATE;
    case ACTION_GESTURE_PAN            : return ADDON_ACTION_GESTURE_PAN;

    case ACTION_GESTURE_SWIPE_LEFT     : return ADDON_ACTION_GESTURE_SWIPE_LEFT;
    case ACTION_GESTURE_SWIPE_LEFT_TEN : return ADDON_ACTION_GESTURE_SWIPE_LEFT_TEN;
    case ACTION_GESTURE_SWIPE_RIGHT    : return ADDON_ACTION_GESTURE_SWIPE_RIGHT;
    case ACTION_GESTURE_SWIPE_RIGHT_TEN: return ADDON_ACTION_GESTURE_SWIPE_RIGHT_TEN;
    case ACTION_GESTURE_SWIPE_UP       : return ADDON_ACTION_GESTURE_SWIPE_UP;
    case ACTION_GESTURE_SWIPE_UP_TEN   : return ADDON_ACTION_GESTURE_SWIPE_UP_TEN;
    case ACTION_GESTURE_SWIPE_DOWN     : return ADDON_ACTION_GESTURE_SWIPE_DOWN;
    case ACTION_GESTURE_SWIPE_DOWN_TEN : return ADDON_ACTION_GESTURE_SWIPE_DOWN_TEN;

    case ACTION_ANALOG_MOVE_X          : return ADDON_ACTION_ANALOG_MOVE_X;
    case ACTION_ANALOG_MOVE_Y          : return ADDON_ACTION_ANALOG_MOVE_Y;

    case ACTION_ERROR                  : return ADDON_ACTION_ERROR;
    case ACTION_NOOP:
    default:
      return ADDON_ACTION_NOOP;
  }
}

int GetKodiGUIActionType(int addonAction)
{
  switch (addonAction)
  {
    case ADDON_ACTION_NONE                   : return ACTION_NONE;
    case ADDON_ACTION_MOVE_LEFT              : return ACTION_MOVE_LEFT;
    case ADDON_ACTION_MOVE_RIGHT             : return ACTION_MOVE_RIGHT;
    case ADDON_ACTION_MOVE_UP                : return ACTION_MOVE_UP;
    case ADDON_ACTION_MOVE_DOWN              : return ACTION_MOVE_DOWN;
    case ADDON_ACTION_PAGE_UP                : return ACTION_PAGE_UP;
    case ADDON_ACTION_PAGE_DOWN              : return ACTION_PAGE_DOWN;
    case ADDON_ACTION_SELECT_ITEM            : return ACTION_SELECT_ITEM;
    case ADDON_ACTION_HIGHLIGHT_ITEM         : return ACTION_HIGHLIGHT_ITEM;
    case ADDON_ACTION_PARENT_DIR             : return ACTION_PARENT_DIR;
    case ADDON_ACTION_PREVIOUS_MENU          : return ACTION_PREVIOUS_MENU;
    case ADDON_ACTION_SHOW_INFO              : return ACTION_SHOW_INFO;
    case ADDON_ACTION_PAUSE                  : return ACTION_PAUSE;
    case ADDON_ACTION_STOP                   : return ACTION_STOP;
    case ADDON_ACTION_NEXT_ITEM              : return ACTION_NEXT_ITEM;
    case ADDON_ACTION_PREV_ITEM              : return ACTION_PREV_ITEM;
    case ADDON_ACTION_FORWARD                : return ACTION_FORWARD;
    case ADDON_ACTION_REWIND                 : return ACTION_REWIND;
    case ADDON_ACTION_SHOW_GUI               : return ACTION_SHOW_GUI;
    case ADDON_ACTION_ASPECT_RATIO           : return ACTION_ASPECT_RATIO;
    case ADDON_ACTION_STEP_FORWARD           : return ACTION_STEP_FORWARD;
    case ADDON_ACTION_STEP_BACK              : return ACTION_STEP_BACK;
    case ADDON_ACTION_BIG_STEP_FORWARD       : return ACTION_BIG_STEP_FORWARD;
    case ADDON_ACTION_BIG_STEP_BACK          : return ACTION_BIG_STEP_BACK;
    case ADDON_ACTION_SHOW_OSD               : return ACTION_SHOW_OSD;
    case ADDON_ACTION_SHOW_SUBTITLES         : return ACTION_SHOW_SUBTITLES;
    case ADDON_ACTION_NEXT_SUBTITLE          : return ACTION_NEXT_SUBTITLE;
    case ADDON_ACTION_PLAYER_DEBUG           : return ACTION_PLAYER_DEBUG;
    case ADDON_ACTION_NEXT_PICTURE           : return ACTION_NEXT_PICTURE;
    case ADDON_ACTION_PREV_PICTURE           : return ACTION_PREV_PICTURE;
    case ADDON_ACTION_ZOOM_OUT               : return ACTION_ZOOM_OUT;
    case ADDON_ACTION_ZOOM_IN                : return ACTION_ZOOM_IN;
    case ADDON_ACTION_TOGGLE_SOURCE_DEST     : return ACTION_TOGGLE_SOURCE_DEST;
    case ADDON_ACTION_SHOW_PLAYLIST          : return ACTION_SHOW_PLAYLIST;
    case ADDON_ACTION_QUEUE_ITEM             : return ACTION_QUEUE_ITEM;
    case ADDON_ACTION_REMOVE_ITEM            : return ACTION_REMOVE_ITEM;
    case ADDON_ACTION_SHOW_FULLSCREEN        : return ACTION_SHOW_FULLSCREEN;
    case ADDON_ACTION_ZOOM_LEVEL_NORMAL      : return ACTION_ZOOM_LEVEL_NORMAL;
    case ADDON_ACTION_ZOOM_LEVEL_1           : return ACTION_ZOOM_LEVEL_1;
    case ADDON_ACTION_ZOOM_LEVEL_2           : return ACTION_ZOOM_LEVEL_2;
    case ADDON_ACTION_ZOOM_LEVEL_3           : return ACTION_ZOOM_LEVEL_3;
    case ADDON_ACTION_ZOOM_LEVEL_4           : return ACTION_ZOOM_LEVEL_4;
    case ADDON_ACTION_ZOOM_LEVEL_5           : return ACTION_ZOOM_LEVEL_5;
    case ADDON_ACTION_ZOOM_LEVEL_6           : return ACTION_ZOOM_LEVEL_6;
    case ADDON_ACTION_ZOOM_LEVEL_7           : return ACTION_ZOOM_LEVEL_7;
    case ADDON_ACTION_ZOOM_LEVEL_8           : return ACTION_ZOOM_LEVEL_8;
    case ADDON_ACTION_ZOOM_LEVEL_9           : return ACTION_ZOOM_LEVEL_9;
    case ADDON_ACTION_CALIBRATE_SWAP_ARROWS  : return ACTION_CALIBRATE_SWAP_ARROWS;
    case ADDON_ACTION_CALIBRATE_RESET        : return ACTION_CALIBRATE_RESET;
    case ADDON_ACTION_ANALOG_MOVE            : return ACTION_ANALOG_MOVE;
    case ADDON_ACTION_ROTATE_PICTURE_CW      : return ACTION_ROTATE_PICTURE_CW;
    case ADDON_ACTION_ROTATE_PICTURE_CCW     : return ACTION_ROTATE_PICTURE_CCW;
    case ADDON_ACTION_SUBTITLE_DELAY_MIN     : return ACTION_SUBTITLE_DELAY_MIN;
    case ADDON_ACTION_SUBTITLE_DELAY_PLUS    : return ACTION_SUBTITLE_DELAY_PLUS;
    case ADDON_ACTION_AUDIO_DELAY_MIN        : return ACTION_AUDIO_DELAY_MIN;
    case ADDON_ACTION_AUDIO_DELAY_PLUS       : return ACTION_AUDIO_DELAY_PLUS;
    case ADDON_ACTION_AUDIO_NEXT_LANGUAGE    : return ACTION_AUDIO_NEXT_LANGUAGE;
    case ADDON_ACTION_CHANGE_RESOLUTION      : return ACTION_CHANGE_RESOLUTION;

    case REMOTE_0                      : return REMOTE_0;
    case REMOTE_1                      : return REMOTE_1;
    case REMOTE_2                      : return REMOTE_2;
    case REMOTE_3                      : return REMOTE_3;
    case REMOTE_4                      : return REMOTE_4;
    case REMOTE_5                      : return REMOTE_5;
    case REMOTE_6                      : return REMOTE_6;
    case REMOTE_7                      : return REMOTE_7;
    case REMOTE_8                      : return REMOTE_8;
    case REMOTE_9                      : return REMOTE_9;

    case ADDON_ACTION_PLAY                   : return ACTION_PLAY;
    case ADDON_ACTION_PLAYER_PROCESS_INFO    : return ACTION_PLAYER_PROCESS_INFO;
    case ADDON_ACTION_SMALL_STEP_BACK        : return ACTION_SMALL_STEP_BACK;

    case ADDON_ACTION_PLAYER_FORWARD         : return ACTION_PLAYER_FORWARD;
    case ADDON_ACTION_PLAYER_REWIND          : return ACTION_PLAYER_REWIND;
    case ADDON_ACTION_PLAYER_PLAY            : return ACTION_PLAYER_PLAY;

    case ADDON_ACTION_DELETE_ITEM            : return ACTION_DELETE_ITEM;
    case ADDON_ACTION_COPY_ITEM              : return ACTION_COPY_ITEM;
    case ADDON_ACTION_MOVE_ITEM              : return ACTION_MOVE_ITEM;
    case ADDON_ACTION_TAKE_SCREENSHOT        : return ACTION_TAKE_SCREENSHOT;
    case ADDON_ACTION_RENAME_ITEM            : return ACTION_RENAME_ITEM;

    case ADDON_ACTION_VOLUME_UP              : return ACTION_VOLUME_UP;
    case ADDON_ACTION_VOLUME_DOWN            : return ACTION_VOLUME_DOWN;
    case ADDON_ACTION_VOLAMP                 : return ACTION_VOLAMP;
    case ADDON_ACTION_MUTE                   : return ACTION_MUTE;
    case ADDON_ACTION_NAV_BACK               : return ACTION_NAV_BACK;
    case ADDON_ACTION_VOLAMP_UP              : return ACTION_VOLAMP_UP;
    case ADDON_ACTION_VOLAMP_DOWN            : return ACTION_VOLAMP_DOWN;

    case ADDON_ACTION_CREATE_EPISODE_BOOKMARK: return ACTION_CREATE_EPISODE_BOOKMARK;
    case ADDON_ACTION_CREATE_BOOKMARK        : return ACTION_CREATE_BOOKMARK;

    case ADDON_ACTION_CHAPTER_OR_BIG_STEP_FORWARD: return ACTION_CHAPTER_OR_BIG_STEP_FORWARD;
    case ADDON_ACTION_CHAPTER_OR_BIG_STEP_BACK: return ACTION_CHAPTER_OR_BIG_STEP_BACK;

    case ADDON_ACTION_CYCLE_SUBTITLE         : return ACTION_CYCLE_SUBTITLE;

    case ADDON_ACTION_MOUSE_LEFT_CLICK       : return ACTION_MOUSE_LEFT_CLICK;
    case ADDON_ACTION_MOUSE_RIGHT_CLICK      : return ACTION_MOUSE_RIGHT_CLICK;
    case ADDON_ACTION_MOUSE_MIDDLE_CLICK     : return ACTION_MOUSE_MIDDLE_CLICK;
    case ADDON_ACTION_MOUSE_DOUBLE_CLICK     : return ACTION_MOUSE_DOUBLE_CLICK;
    case ADDON_ACTION_MOUSE_WHEEL_UP         : return ACTION_MOUSE_WHEEL_UP;
    case ADDON_ACTION_MOUSE_WHEEL_DOWN       : return ACTION_MOUSE_WHEEL_DOWN;
    case ADDON_ACTION_MOUSE_DRAG             : return ACTION_MOUSE_DRAG;
    case ADDON_ACTION_MOUSE_MOVE             : return ACTION_MOUSE_MOVE;
    case ADDON_ACTION_MOUSE_LONG_CLICK       : return ACTION_MOUSE_LONG_CLICK;

    case ADDON_ACTION_BACKSPACE              : return ACTION_BACKSPACE;
    case ADDON_ACTION_SCROLL_UP              : return ACTION_SCROLL_UP;
    case ADDON_ACTION_SCROLL_DOWN            : return ACTION_SCROLL_DOWN;
    case ADDON_ACTION_ANALOG_FORWARD         : return ACTION_ANALOG_FORWARD;
    case ADDON_ACTION_ANALOG_REWIND          : return ACTION_ANALOG_REWIND;

    case ADDON_ACTION_MOVE_ITEM_UP           : return ACTION_MOVE_ITEM_UP;
    case ADDON_ACTION_MOVE_ITEM_DOWN         : return ACTION_MOVE_ITEM_DOWN;
    case ADDON_ACTION_CONTEXT_MENU           : return ACTION_CONTEXT_MENU;

    case ADDON_ACTION_SHIFT                  : return ACTION_SHIFT;
    case ADDON_ACTION_SYMBOLS                : return ACTION_SYMBOLS;
    case ADDON_ACTION_CURSOR_LEFT            : return ACTION_CURSOR_LEFT;
    case ADDON_ACTION_CURSOR_RIGHT           : return ACTION_CURSOR_RIGHT;

    case ADDON_ACTION_BUILT_IN_FUNCTION      : return ACTION_BUILT_IN_FUNCTION;

    case ADDON_ACTION_SHOW_OSD_TIME          : return ACTION_SHOW_OSD_TIME;
    case ADDON_ACTION_ANALOG_SEEK_FORWARD    : return ACTION_ANALOG_SEEK_FORWARD;
    case ADDON_ACTION_ANALOG_SEEK_BACK       : return ACTION_ANALOG_SEEK_BACK;

    case ADDON_ACTION_VIS_PRESET_SHOW        : return ACTION_VIS_PRESET_SHOW;
    case ADDON_ACTION_VIS_PRESET_NEXT        : return ACTION_VIS_PRESET_NEXT;
    case ADDON_ACTION_VIS_PRESET_PREV        : return ACTION_VIS_PRESET_PREV;
    case ADDON_ACTION_VIS_PRESET_LOCK        : return ACTION_VIS_PRESET_LOCK;
    case ADDON_ACTION_VIS_PRESET_RANDOM      : return ACTION_VIS_PRESET_RANDOM;
    case ADDON_ACTION_VIS_RATE_PRESET_PLUS   : return ACTION_VIS_RATE_PRESET_PLUS;
    case ADDON_ACTION_VIS_RATE_PRESET_MINUS  : return ACTION_VIS_RATE_PRESET_MINUS;

    case ADDON_ACTION_SHOW_VIDEOMENU         : return ACTION_SHOW_VIDEOMENU;
    case ADDON_ACTION_ENTER                  : return ACTION_ENTER;

    case ADDON_ACTION_INCREASE_RATING        : return ACTION_INCREASE_RATING;
    case ADDON_ACTION_DECREASE_RATING        : return ACTION_DECREASE_RATING;

    case ADDON_ACTION_NEXT_SCENE             : return ACTION_NEXT_SCENE;
    case ADDON_ACTION_PREV_SCENE             : return ACTION_PREV_SCENE;

    case ADDON_ACTION_NEXT_LETTER            : return ACTION_NEXT_LETTER;
    case ADDON_ACTION_PREV_LETTER            : return ACTION_PREV_LETTER;

    case ADDON_ACTION_JUMP_SMS2              : return ACTION_JUMP_SMS2;
    case ADDON_ACTION_JUMP_SMS3              : return ACTION_JUMP_SMS3;
    case ADDON_ACTION_JUMP_SMS4              : return ACTION_JUMP_SMS4;
    case ADDON_ACTION_JUMP_SMS5              : return ACTION_JUMP_SMS5;
    case ADDON_ACTION_JUMP_SMS6              : return ACTION_JUMP_SMS6;
    case ADDON_ACTION_JUMP_SMS7              : return ACTION_JUMP_SMS7;
    case ADDON_ACTION_JUMP_SMS8              : return ACTION_JUMP_SMS8;
    case ADDON_ACTION_JUMP_SMS9              : return ACTION_JUMP_SMS9;

    case ADDON_ACTION_FILTER_CLEAR           : return ACTION_FILTER_CLEAR;
    case ADDON_ACTION_FILTER_SMS2            : return ACTION_FILTER_SMS2;
    case ADDON_ACTION_FILTER_SMS3            : return ACTION_FILTER_SMS3;
    case ADDON_ACTION_FILTER_SMS4            : return ACTION_FILTER_SMS4;
    case ADDON_ACTION_FILTER_SMS5            : return ACTION_FILTER_SMS5;
    case ADDON_ACTION_FILTER_SMS6            : return ACTION_FILTER_SMS6;
    case ADDON_ACTION_FILTER_SMS7            : return ACTION_FILTER_SMS7;
    case ADDON_ACTION_FILTER_SMS8            : return ACTION_FILTER_SMS8;
    case ADDON_ACTION_FILTER_SMS9            : return ACTION_FILTER_SMS9;

    case ADDON_ACTION_FIRST_PAGE             : return ACTION_FIRST_PAGE;
    case ADDON_ACTION_LAST_PAGE              : return ACTION_LAST_PAGE;

    case ADDON_ACTION_AUDIO_DELAY            : return ACTION_AUDIO_DELAY;
    case ADDON_ACTION_SUBTITLE_DELAY         : return ACTION_SUBTITLE_DELAY;
    case ADDON_ACTION_MENU                   : return ACTION_MENU;

    case ADDON_ACTION_SET_RATING             : return ACTION_SET_RATING;

    case ADDON_ACTION_RECORD                 : return ACTION_RECORD;

    case ADDON_ACTION_PASTE                  : return ACTION_PASTE;
    case ADDON_ACTION_NEXT_CONTROL           : return ACTION_NEXT_CONTROL;
    case ADDON_ACTION_PREV_CONTROL           : return ACTION_PREV_CONTROL;
    case ADDON_ACTION_CHANNEL_SWITCH         : return ACTION_CHANNEL_SWITCH;
    case ADDON_ACTION_CHANNEL_UP             : return ACTION_CHANNEL_UP;
    case ADDON_ACTION_CHANNEL_DOWN           : return ACTION_CHANNEL_DOWN;
    case ADDON_ACTION_NEXT_CHANNELGROUP      : return ACTION_NEXT_CHANNELGROUP;
    case ADDON_ACTION_PREVIOUS_CHANNELGROUP  : return ACTION_PREVIOUS_CHANNELGROUP;
    case ADDON_ACTION_PVR_PLAY               : return ACTION_PVR_PLAY;
    case ADDON_ACTION_PVR_PLAY_TV            : return ACTION_PVR_PLAY_TV;
    case ADDON_ACTION_PVR_PLAY_RADIO         : return ACTION_PVR_PLAY_RADIO;
    case ADDON_ACTION_PVR_SHOW_TIMER_RULE    : return ACTION_PVR_SHOW_TIMER_RULE;

    case ADDON_ACTION_TOGGLE_FULLSCREEN      : return ACTION_TOGGLE_FULLSCREEN;
    case ADDON_ACTION_TOGGLE_WATCHED         : return ACTION_TOGGLE_WATCHED;
    case ADDON_ACTION_SCAN_ITEM              : return ACTION_SCAN_ITEM;
    case ADDON_ACTION_TOGGLE_DIGITAL_ANALOG  : return ACTION_TOGGLE_DIGITAL_ANALOG;
    case ADDON_ACTION_RELOAD_KEYMAPS         : return ACTION_RELOAD_KEYMAPS;
    case ADDON_ACTION_GUIPROFILE_BEGIN       : return ACTION_GUIPROFILE_BEGIN;

    case ADDON_ACTION_TELETEXT_RED           : return ACTION_TELETEXT_RED;
    case ADDON_ACTION_TELETEXT_GREEN         : return ACTION_TELETEXT_GREEN;
    case ADDON_ACTION_TELETEXT_YELLOW        : return ACTION_TELETEXT_YELLOW;
    case ADDON_ACTION_TELETEXT_BLUE          : return ACTION_TELETEXT_BLUE;

    case ADDON_ACTION_INCREASE_PAR           : return ACTION_INCREASE_PAR;
    case ADDON_ACTION_DECREASE_PAR           : return ACTION_DECREASE_PAR;

    case ADDON_ACTION_VSHIFT_UP              : return ACTION_VSHIFT_UP;
    case ADDON_ACTION_VSHIFT_DOWN            : return ACTION_VSHIFT_DOWN;

    case ADDON_ACTION_PLAYER_PLAYPAUSE       : return ACTION_PLAYER_PLAYPAUSE;

    case ADDON_ACTION_SUBTITLE_VSHIFT_UP     : return ACTION_SUBTITLE_VSHIFT_UP;
    case ADDON_ACTION_SUBTITLE_VSHIFT_DOWN   : return ACTION_SUBTITLE_VSHIFT_DOWN;
    case ADDON_ACTION_SUBTITLE_ALIGN         : return ACTION_SUBTITLE_ALIGN;

    case ADDON_ACTION_FILTER                 : return ACTION_FILTER;

    case ADDON_ACTION_SWITCH_PLAYER          : return ACTION_SWITCH_PLAYER;

    case ADDON_ACTION_STEREOMODE_NEXT        : return ACTION_STEREOMODE_NEXT;
    case ADDON_ACTION_STEREOMODE_PREVIOUS    : return ACTION_STEREOMODE_PREVIOUS;
    case ADDON_ACTION_STEREOMODE_TOGGLE      : return ACTION_STEREOMODE_TOGGLE;
    case ADDON_ACTION_STEREOMODE_SELECT      : return ACTION_STEREOMODE_SELECT;
    case ADDON_ACTION_STEREOMODE_TOMONO      : return ACTION_STEREOMODE_TOMONO;
    case ADDON_ACTION_STEREOMODE_SET         : return ACTION_STEREOMODE_SET;

    case ADDON_ACTION_SETTINGS_RESET         : return ACTION_SETTINGS_RESET;
    case ADDON_ACTION_SETTINGS_LEVEL_CHANGE  : return ACTION_SETTINGS_LEVEL_CHANGE;

    case ADDON_ACTION_TRIGGER_OSD            : return ACTION_TRIGGER_OSD;
    case ADDON_ACTION_INPUT_TEXT             : return ACTION_INPUT_TEXT;
    case ADDON_ACTION_VOLUME_SET             : return ACTION_VOLUME_SET;
    case ADDON_ACTION_TOGGLE_COMMSKIP        : return ACTION_TOGGLE_COMMSKIP;

    case ADDON_ACTION_TOUCH_TAP              : return ACTION_TOUCH_TAP;
    case ADDON_ACTION_TOUCH_TAP_TEN          : return ACTION_TOUCH_TAP_TEN;
    case ADDON_ACTION_TOUCH_LONGPRESS        : return ACTION_TOUCH_LONGPRESS;
    case ADDON_ACTION_TOUCH_LONGPRESS_TEN    : return ACTION_TOUCH_LONGPRESS_TEN;

    case ADDON_ACTION_GESTURE_NOTIFY         : return ACTION_GESTURE_NOTIFY;
    case ADDON_ACTION_GESTURE_BEGIN          : return ACTION_GESTURE_BEGIN;
    case ADDON_ACTION_GESTURE_ZOOM           : return ACTION_GESTURE_ZOOM;
    case ADDON_ACTION_GESTURE_ROTATE         : return ACTION_GESTURE_ROTATE;
    case ADDON_ACTION_GESTURE_PAN            : return ACTION_GESTURE_PAN;

    case ADDON_ACTION_GESTURE_SWIPE_LEFT     : return ACTION_GESTURE_SWIPE_LEFT;
    case ADDON_ACTION_GESTURE_SWIPE_LEFT_TEN : return ACTION_GESTURE_SWIPE_LEFT_TEN;
    case ADDON_ACTION_GESTURE_SWIPE_RIGHT    : return ACTION_GESTURE_SWIPE_RIGHT;
    case ADDON_ACTION_GESTURE_SWIPE_RIGHT_TEN: return ACTION_GESTURE_SWIPE_RIGHT_TEN;
    case ADDON_ACTION_GESTURE_SWIPE_UP       : return ACTION_GESTURE_SWIPE_UP;
    case ADDON_ACTION_GESTURE_SWIPE_UP_TEN   : return ACTION_GESTURE_SWIPE_UP_TEN;
    case ADDON_ACTION_GESTURE_SWIPE_DOWN     : return ACTION_GESTURE_SWIPE_DOWN;
    case ADDON_ACTION_GESTURE_SWIPE_DOWN_TEN : return ACTION_GESTURE_SWIPE_DOWN_TEN;

    case ADDON_ACTION_ANALOG_MOVE_X          : return ACTION_ANALOG_MOVE_X;
    case ADDON_ACTION_ANALOG_MOVE_Y          : return ACTION_ANALOG_MOVE_Y;

    case ADDON_ACTION_ERROR                  : return ACTION_ERROR;
    case ADDON_ACTION_NOOP:
    default:
      return ADDON_ACTION_NOOP;
  }
}

void Interface_GUIGeneral::Init(AddonGlobalInterface* addonInterface)
{
  addonInterface->toKodi->kodi_gui = (AddonToKodiFuncTable_kodi_gui*)malloc(sizeof(AddonToKodiFuncTable_kodi_gui));
  addonInterface->toKodi->kodi_gui->general.lock = lock;
  addonInterface->toKodi->kodi_gui->general.unlock = unlock;
  addonInterface->toKodi->kodi_gui->general.get_screen_height = get_screen_height;
  addonInterface->toKodi->kodi_gui->general.get_screen_width = get_screen_width;
  addonInterface->toKodi->kodi_gui->general.get_video_resolution = get_video_resolution;
  addonInterface->toKodi->kodi_gui->general.get_current_window_dialog_id = get_current_window_dialog_id;
  addonInterface->toKodi->kodi_gui->general.get_current_window_id = get_current_window_id;

  Interface_GUIControlButton::Init(addonInterface);
  Interface_GUIControlEdit::Init(addonInterface);
  Interface_GUIControlFadeLabel::Init(addonInterface);
  Interface_GUIControlImage::Init(addonInterface);
  Interface_GUIControlLabel::Init(addonInterface);
  Interface_GUIControlProgress::Init(addonInterface);
  Interface_GUIControlRadioButton::Init(addonInterface);
  Interface_GUIControlAddonRendering::Init(addonInterface);
  Interface_GUIControlSettingsSlider::Init(addonInterface);
  Interface_GUIControlSlider::Init(addonInterface);
  Interface_GUIControlSpin::Init(addonInterface);
  Interface_GUIControlTextBox::Init(addonInterface);
  Interface_GUIDialogContextMenu::Init(addonInterface);
  Interface_GUIDialogExtendedProgress::Init(addonInterface);
  Interface_GUIDialogFileBrowser::Init(addonInterface);
  Interface_GUIDialogKeyboard::Init(addonInterface);
  Interface_GUIDialogNumeric::Init(addonInterface);
  Interface_GUIDialogOK::Init(addonInterface);
  Interface_GUIDialogProgress::Init(addonInterface);
  Interface_GUIDialogSelect::Init(addonInterface);
  Interface_GUIDialogTextViewer::Init(addonInterface);
  Interface_GUIDialogYesNo::Init(addonInterface);
  Interface_GUIWindow::Init(addonInterface);
  Interface_GUIListItem::Init(addonInterface);

}

void Interface_GUIGeneral::DeInit(AddonGlobalInterface* addonInterface)
{
  if (addonInterface->toKodi && /* <-- Safe check, needed so long old addon way is present */
      addonInterface->toKodi->kodi_gui)
  {
    free(addonInterface->toKodi->kodi_gui);
    addonInterface->toKodi->kodi_gui = nullptr;
  }
}

//@{
void Interface_GUIGeneral::lock()
{
  if (m_iAddonGUILockRef == 0)
    g_graphicsContext.Lock();
  ++m_iAddonGUILockRef;
}

void Interface_GUIGeneral::unlock()
{
  if (m_iAddonGUILockRef > 0)
  {
    --m_iAddonGUILockRef;
    if (m_iAddonGUILockRef == 0)
      g_graphicsContext.Unlock();
  }
}
//@}

//@{
int Interface_GUIGeneral::get_screen_height(void* kodiBase)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "kodi::gui::%s - invalid data", __FUNCTION__);
    return -1;
  }

  return g_graphicsContext.GetHeight();
}

int Interface_GUIGeneral::get_screen_width(void* kodiBase)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "kodi::gui::%s - invalid data", __FUNCTION__);
    return -1;
  }

  return g_graphicsContext.GetWidth();
}

int Interface_GUIGeneral::get_video_resolution(void* kodiBase)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "kodi::gui::%s - invalid data", __FUNCTION__);
    return -1;
  }

  return (int)g_graphicsContext.GetVideoResolution();
}
//@}

//@{
int Interface_GUIGeneral::get_current_window_dialog_id(void* kodiBase)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "kodi::gui::%s - invalid data", __FUNCTION__);
    return -1;
  }

  CSingleLock gl(g_graphicsContext);
  return g_windowManager.GetTopMostModalDialogID();
}

int Interface_GUIGeneral::get_current_window_id(void* kodiBase)
{
  CAddonDll* addon = static_cast<CAddonDll*>(kodiBase);
  if (!addon)
  {
    CLog::Log(LOGERROR, "kodi::gui::%s - invalid data", __FUNCTION__);
    return -1;
  }

  CSingleLock gl(g_graphicsContext);
  return g_windowManager.GetActiveWindow();
}

//@}

} /* namespace ADDON */
} /* extern "C" */
