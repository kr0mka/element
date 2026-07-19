// SPDX-FileCopyrightText: 2026 Kushview, LLC
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <element/juce/core.hpp>

namespace element::windowsstartup {

inline constexpr auto startMinimizedArgument = "--start-minimized-to-tray";

/** Returns true when Element has a per-user Windows startup entry. */
bool isEnabled();

/** Creates, updates, or removes Element's per-user Windows startup entry. */
bool setEnabled (bool enabled, bool startMinimizedToTray);

/** Returns true when the exact minimized-start argument is present. */
bool shouldStartMinimizedToTray (const juce::String& commandLine);

} // namespace element::windowsstartup
