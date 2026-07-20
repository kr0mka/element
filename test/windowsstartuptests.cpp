// SPDX-FileCopyrightText: 2026 Kushview, LLC
// SPDX-License-Identifier: GPL-3.0-or-later

#include <boost/test/unit_test.hpp>

#include "windowsstartup.hpp"

using namespace element;

BOOST_AUTO_TEST_SUITE (WindowsStartupTests)

BOOST_AUTO_TEST_CASE (recognizes_exact_minimized_start_argument)
{
    BOOST_TEST (windowsstartup::shouldStartMinimized ("--start-minimized"));
    BOOST_TEST (windowsstartup::shouldStartMinimized (
        "\"C:\\Program Files\\Element\\element.exe\" --start-minimized"));
    BOOST_TEST (windowsstartup::shouldStartMinimized ("--start-minimized-to-tray"));
    BOOST_TEST (! windowsstartup::shouldStartMinimized ("--start-minimized-extra"));
    BOOST_TEST (! windowsstartup::shouldStartMinimized ("--start-minimized-to-tray-extra"));
    BOOST_TEST (! windowsstartup::shouldStartMinimized ("session.els"));
}

BOOST_AUTO_TEST_SUITE_END()
