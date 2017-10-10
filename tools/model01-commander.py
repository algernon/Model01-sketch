#! /usr/bin/env python
## model01-commander.py -- Model01 helper tool
## Copyright (C) 2017  Gergely Nagy
##
## This program is free software: you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <http://www.gnu.org/licenses/>.

import serial
import sys
import sh
import time

class AppSel (object):
    _appmap = {"music": ["rhythmbox", "spotify", "banshee", "kodi", "plex"],
               "chat": ["slack", "Mstdn"],
               "emacs": "emacs",
               "term": "gnome-terminal",
               "web": ["chrom", "Chrome"],
               "pwmgr": "keepass",
               "social": ["trunk.mad-scientist.club.Google-chrome", "tweetdeck"],
               "social2": ["Viber", "Signal"]}

    def select_only (self, apps):
        if isinstance (apps, list):
            for app in apps:
                if self.select (app):
                    break

        success = True
        try:
            sh.wmctrl ("-x", "-a", apps)
        except sh.ErrorReturnCode:
            success = False

        return success

    def select (self, apps):
        success = self.select_only (apps)

        sh.xdotool ("key", "Escape")
        return success

    def select_multi (self, app):
        if not app in self._appmap:
            return

        for a in self._appmap[app]:
            self.select_only (a)

        sh.xdotool ("key", "Escape")
        return True

    def select_social (self, app):
        return self.select_multi (app)

    def select_social2 (self, app):
        return self.select_multi (app)

    def switchTo (self, app):
        try:
            getattr(self, "select_" + app)(app)
        except AttributeError:
            if app in self._appmap:
                self.select (self._appmap[app])

class Commander (object):
    _appSel = AppSel ()

    def run (self):
        with serial.Serial ("/dev/ttyACM0", 9600, timeout = 1) as ser:
            while True:
                cmd = ser.readline ().strip ()
                if cmd.startswith ("appsel:"):
                    app = cmd[7:]
                    print "appsel: %s" % app
                    self._appSel.switchTo (app)

commander = Commander ()

while True:
    try:
        commander.run ()
    except Exception:
        print "WARNING: Connection to serial lost, sleeping 10s..."
        time.sleep (10)
        print "WARNING: Sleep over, resuming!"
        pass
