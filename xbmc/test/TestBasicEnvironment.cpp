/*
 *      Copyright (C) 2005-2013 Team XBMC
 *      http://xbmc.org
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
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "TestBasicEnvironment.h"
#include "TestUtils.h"
#include "cores/DataCacheCore.h"
#include "cores/AudioEngine/Engines/ActiveAE/AudioDSPAddons/ActiveAEDSP.h"
#include "cores/AudioEngine/Interfaces/AE.h"
#include "ServiceBroker.h"
#include "filesystem/Directory.h"
#include "filesystem/File.h"
#include "filesystem/SpecialProtocol.h"
#include "powermanagement/PowerManager.h"
#include "settings/AdvancedSettings.h"
#include "settings/Settings.h"
#include "Util.h"
#include "Application.h"
#include "PlayListPlayer.h"
#include "interfaces/AnnouncementManager.h"
#include "addons/BinaryAddonCache.h"
#include "interfaces/python/XBPython.h"
#include "pvr/PVRManager.h"
#include "AppParamParser.h"

#if defined(TARGET_WINDOWS) || defined(TARGET_WIN10)
#include "platform/win32/WIN32Util.h"
#include "platform/win32/CharsetConverter.h"
#endif

#include <cstdio>
#include <cstdlib>
#include <climits>

void TestBasicEnvironment::SetUp()
{
  XFILE::CFile *f;

  g_application.m_ServiceManager.reset(new CServiceManager());
  if (!g_application.m_ServiceManager->InitStageOne())
    exit(1);

  /* NOTE: The below is done to fix memleak warning about uninitialized variable
   * in xbmcutil::GlobalsSingleton<CAdvancedSettings>::getInstance().
   */
  g_advancedSettings.Initialize();

  // Need to configure the network as some tests access the network member
  g_application.SetupNetwork();

  if (!CXBMCTestUtils::Instance().SetReferenceFileBasePath())
    SetUpError();
  CXBMCTestUtils::Instance().setTestFileFactoryWriteInputFile(
    XBMC_REF_FILE_PATH("xbmc/filesystem/test/reffile.txt")
  );

//for darwin set framework path - else we get assert
//in guisettings init below
#ifdef TARGET_DARWIN
  std::string frameworksPath = CUtil::GetFrameworksPath();
  CSpecialProtocol::SetXBMCFrameworksPath(frameworksPath);
#endif
  /**
   * @todo Something should be done about all the asserts in GUISettings so
   * that the initialization of these components won't be needed.
   */

  /* Create a temporary directory and set it to be used throughout the
   * test suite run.
   */
#ifdef TARGET_WINDOWS
  using KODI::PLATFORM::WINDOWS::FromW;
  std::wstring xbmcTempPath;
  TCHAR lpTempPathBuffer[MAX_PATH];
  if (!GetTempPath(MAX_PATH, lpTempPathBuffer))
    SetUpError();
  xbmcTempPath = lpTempPathBuffer;
  if (!GetTempFileName(xbmcTempPath.c_str(), L"xbmctempdir", 0, lpTempPathBuffer))
    SetUpError();
  DeleteFile(lpTempPathBuffer);
  if (!CreateDirectory(lpTempPathBuffer, NULL))
    SetUpError();
  CSpecialProtocol::SetTempPath(FromW(lpTempPathBuffer));
  CSpecialProtocol::SetProfilePath(FromW(lpTempPathBuffer));
#else
  char buf[MAX_PATH];
  char *tmp;
  strcpy(buf, "/tmp/xbmctempdirXXXXXX");
  if ((tmp = mkdtemp(buf)) == NULL)
    SetUpError();
  CSpecialProtocol::SetTempPath(tmp);
  CSpecialProtocol::SetProfilePath(tmp);
#endif

  /* Create and delete a tempfile to initialize the VFS (really to initialize
   * CLibcdio). This is done so that the initialization of the VFS does not
   * affect the performance results of the test cases.
   */
  /** @todo Make the initialization of the VFS here optional so it can be
   * testable in a test case.
   */
  f = XBMC_CREATETEMPFILE("");
  if (!f || !XBMC_DELETETEMPFILE(f))
  {
    TearDown();
    SetUpError();
  }
  g_powerManager.Initialize();
  g_application.m_ServiceManager->CreateAudioEngine();
  CServiceBroker::GetSettings().Initialize();

  if (!g_application.m_ServiceManager->InitStageTwo(CAppParamParser()))
    exit(1);

  g_application.m_ServiceManager->StartAudioEngine();
}

void TestBasicEnvironment::TearDown()
{
  g_application.m_ServiceManager->DeinitStageTwo();
  g_application.m_ServiceManager->DestroyAudioEngine();
  std::string xbmcTempPath = CSpecialProtocol::TranslatePath("special://temp/");
  XFILE::CDirectory::Remove(xbmcTempPath);
  CServiceBroker::GetSettings().Uninitialize();
  g_application.m_ServiceManager->DeinitStageOne();
}

void TestBasicEnvironment::SetUpError()
{
  fprintf(stderr, "Setup of basic environment failed.\n");
  exit(EXIT_FAILURE);
}
