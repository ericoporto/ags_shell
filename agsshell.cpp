//
// ags_shell.cpp : Shell execute plugin for AGS
// Copyright (c) 2014 Michael "monkey_05_06" Rittenhouse
//
#include <cstdlib>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <ShellAPI.h>



#ifdef WINDOWS_VERSION
// DllMain - standard Windows DLL entry point.
// The AGS editor will cause this to get called when the editor first
// starts up, and when it shuts down at the end.
BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
  // we don't need to do anything here
  return TRUE;
}

#endif // WINDOWS_VERSION
#endif

#define THIS_IS_THE_PLUGIN
#include "agsplugin.h"


// ***** DESIGN TIME CALLS *******

IAGSEditor *editor;
const char *ourScriptHeader =
  "#define AGS_SHELL_VERSION 2\r\n"
  "import void ShellExecute(const string operation, const string file, const string parameters);\r\n";


int AGS_EditorStartup(IAGSEditor *lpEditor)
{
  // User has checked the plugin to use it in their game

  // If it's an earlier version than what we need, abort.
  if (lpEditor->version < 1)
    return -1;

  editor = lpEditor;
  editor->RegisterScriptHeader(ourScriptHeader);

  // Return 0 to indicate success
  return 0;
}

void AGS_EditorShutdown()
{
  // User has un-checked the plugin from their game
  editor->UnregisterScriptHeader(ourScriptHeader);
}

void AGS_EditorProperties(HWND parent)
{
  // User has chosen to view the Properties of the plugin
  // We could load up an options dialog or something here instead
}

int AGS_EditorSaveGame(char *buffer, int bufsize)
{
  // We don't want to save any persistent data
  return 0;
}

void AGS_EditorLoadGame(char *buffer, int bufsize)
{
  // Nothing to load for this dummy plugin
}

// ******* END DESIGN TIME  *******

// ****** RUN TIME ********

IAGSEngine *engine;

const char *AGS_GetPluginName() {
	return "AGS shell plugin";
}

void AGS_ShellExecute(char const *operation, char const *filename, char const *parameters)
{
#ifdef _WIN32
  ShellExecute(NULL, operation, filename, parameters, NULL, 0);
// WINDOWS_VERSION
#else 
  std::system(parameters);
#endif 
}

void AGS_EngineStartup(IAGSEngine *lpEngine)
{
  engine = lpEngine;

  // Make sure it's got the version with the features we need
  if (engine->version < 3)
  {
    engine->AbortGame ("Engine interface is too old, need newer version of AGS.");
  }

  engine->RegisterScriptFunction("ShellExecute", reinterpret_cast<void *>(AGS_ShellExecute));
}

void AGS_EngineShutdown()
{
  // no work to do here - but if we had created any dynamic sprites,
  // we should delete them here
}

int AGS_EngineOnEvent (int event, int data)
{
  return 0;
}

// *** END RUN TIME ****
