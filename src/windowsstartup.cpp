// SPDX-FileCopyrightText: 2026 Kushview, LLC
// SPDX-License-Identifier: GPL-3.0-or-later

#include "windowsstartup.hpp"

#include <string>

#include <juce_core/system/juce_TargetPlatform.h>

#if JUCE_WINDOWS
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

namespace element::windowsstartup {

namespace {

#if JUCE_WINDOWS
constexpr auto runKeyPath = L"Software\\Microsoft\\Windows\\CurrentVersion\\Run";
constexpr auto runValueName = L"Element";

juce::String launchCommand (bool startMinimizedToTray)
{
    auto command = juce::String ("\"")
                       + juce::File::getSpecialLocation (juce::File::currentExecutableFile).getFullPathName()
                       + "\"";
    if (startMinimizedToTray)
        command << " " << startMinimizedArgument;
    return command;
}
#endif

} // namespace

bool isEnabled()
{
#if JUCE_WINDOWS
    DWORD valueSize = 0;
    const auto result = ::RegGetValueW (HKEY_CURRENT_USER,
                                        runKeyPath,
                                        runValueName,
                                        RRF_RT_REG_SZ,
                                        nullptr,
                                        nullptr,
                                        &valueSize);
    return result == ERROR_SUCCESS && valueSize > sizeof (wchar_t);
#else
    return false;
#endif
}

bool setEnabled (bool enabled, bool startMinimizedToTray)
{
#if JUCE_WINDOWS
    HKEY key = nullptr;

    if (! enabled)
    {
        const auto openResult = ::RegOpenKeyExW (HKEY_CURRENT_USER,
                                                 runKeyPath,
                                                 0,
                                                 KEY_SET_VALUE,
                                                 &key);
        if (openResult == ERROR_FILE_NOT_FOUND)
            return true;
        if (openResult != ERROR_SUCCESS)
            return false;

        const auto deleteResult = ::RegDeleteValueW (key, runValueName);
        ::RegCloseKey (key);
        return deleteResult == ERROR_SUCCESS || deleteResult == ERROR_FILE_NOT_FOUND;
    }

    DWORD disposition = 0;
    const auto createResult = ::RegCreateKeyExW (HKEY_CURRENT_USER,
                                                 runKeyPath,
                                                 0,
                                                 nullptr,
                                                 0,
                                                 KEY_SET_VALUE,
                                                 nullptr,
                                                 &key,
                                                 &disposition);
    juce::ignoreUnused (disposition);
    if (createResult != ERROR_SUCCESS)
        return false;

    const std::wstring command = launchCommand (startMinimizedToTray).toWideCharPointer();
    const auto writeResult = ::RegSetValueExW (key,
                                               runValueName,
                                               0,
                                               REG_SZ,
                                               reinterpret_cast<const BYTE*> (command.c_str()),
                                               static_cast<DWORD> ((command.size() + 1) * sizeof (wchar_t)));
    ::RegCloseKey (key);
    return writeResult == ERROR_SUCCESS;
#else
    juce::ignoreUnused (enabled, startMinimizedToTray);
    return false;
#endif
}

bool shouldStartMinimizedToTray (const juce::String& commandLine)
{
    juce::StringArray arguments;
    arguments.addTokens (commandLine, " \t\r\n", "\"'");
    return arguments.contains (startMinimizedArgument);
}

} // namespace element::windowsstartup
