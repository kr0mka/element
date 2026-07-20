// SPDX-FileCopyrightText: 2026 Kushview, LLC
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <element/juce/core.hpp>

namespace element::windowsstartup {

/** Returns true when Element has a per-user Windows startup entry. */
bool isEnabled();

/** Creates, updates, or removes Element's per-user Windows startup entry. */
bool setEnabled (bool enabled);

} // namespace element::windowsstartup
