xmchord
=======

[![Build Status](https://travis-ci.com/kstenschke/xmchord.svg?branch=master)](https://travis-ci.com/kstenschke/xmchord)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/kstenschke/xmchord.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/kstenschke/xmchord/context:cpp)

xmchord is a productivity tool for Linux desktops, that binds custom
actions to `chording*` events of mouse buttons and key presses: this way, 
mouse buttons become additional modifier keys. 

**`*Chording:`** Chording generally means pushing several keys or buttons
simultaneously to achieve a result.

xmchord comes with a comprehensive set of shortcut actions to speed-up 
common user activities on the Linux desktop.


## Table of contents

* [What does it do?](#what-does-it-do)
* [Usage and arguments](#usage-and-arguments)
  * [Command: `help`](#command-help)
  * [Command: `debug`](#command-debug)
  * [Command: `actions`](#command-actions)
  * [Argument: `--keyboard`](#argument---keyboard)
  * [Command: `listDevices`](#command-listdevices)
  * [Command: `reset`](#command-reset)
  * [Command: `version`](#command-version)
* [Included shortcut actions](#included-shortcut-actions)
  * [Third party dependencies](#third-party-dependencies)
  * [Global actions](#global-actions-not-application-specific)
  * [Application specific actions](#application-specific-actions)
    * [Chromium and Firefox Web-Browser](#chromium-and-firefox-web-browser)
    * [Claws Mail](#claws-mail)
    * [Gnome Terminal](#gnome-terminal)
    * [Gnome Screenshot](#gnome-screenshot)
* [Action shell scripting tricks](#action-shell-scripting-tricks)
  * [1. User-specific actions](#1-user-specific-actions)
  * [2. Launching applications and switching windows](#2-launching-applications-and-switching-windows)
  * [3. Triggering window actions](#3-triggering-window-actions)
  * [4. Application specific shortcut actions](4-application-specific-shortcut-actions)
* [Building from source](#building-from-source)
* [Code Convention](#code-convention)
* [Contributing](#contributing)
* [Bug Reporting and Feature Requests](#bug-reporting-and-feature-requests)
* [Changelog](#changelog)
* [Third Party References](#third-party-references)
* [Author and License](#author-and-license)


## What does it do?

xmchord listens for events of mouse buttons pressed together with keyboard keys.
When observing a chording event, xmchord generates an identifier code for the
given combination (and order) of button/key presses. 
If there is a shell script file named by the current event code within 
xmchord's `actions` directory, it is executed.


## Usage and arguments

Usage is: `sudo xmchord` 

To ensure read-access to Linux device events, xmchord must be run with root
privileges (e.g. via`sudo`).
Action shell scripts that perform user specific tasks, therefor must take care 
of [running on that user's behalf](#1-user-specific-actions).


### Command: `help`

Running `xmchord help` or  `xmchord h`, displays a list and explanation of
available commands.


### Command: `debug`

Running `xmchord debug` or  `xmchord d`, activates tracing of event codes.
While in debug mode, action shell script files can be added without having to
stop and restart xmchord.

In regular mode, xmchord reduces processing time by indexing which actions are
available during startup.


### Command: `actions`

Running `xmchord actions` or `xmchord a`, lists all recognized action shell
scripts, including their inlined description comments (which must be prefixed 
with `#:`).


### Argument: `--keyboard`

xmchord by default installs its keyboard watcher upon the 1st keyboard device
found (e.g. on laptops the built-in one). This optional argument allows setting
a specific keyboard device to be used.
xmchord stores this device preference, so once it is set, xmchord continues
using that device when restarted later.  
 
Running `xmchord --keyboard=/path/to/my/keyboard` 
or `xmchord -k=/path/to/my/keyboard` selects the device at the given path as
the keyboard watcher's target.


### Command: `listDevices`

Running `xmchord listDevices` or `xmchord l` lists paths of available devices.
This is helpful when wanting to use a different than the default keyboard.


### Command: `reset`

Running `xmchord reset` or `xmchord r` removes the xmchord keyboard device 
preference, if it exists.


### Command: `version`

Running `xmchord version` or  `xmchord v`, tests whether xmchord is available
and displays it's version number.


## Included shortcut actions

See files under `bin/actions`

The included shortcut actions are scripted for use with a 
[**Kensington Expert Mouse**](https://www.kensington.com/p/products/control/trackballs/expert-mouse-wired-trackball) 
trackball, tested on Linux Mint Cinnamon, but should be compatible or easily
adjustable for other devices and Linux distributions and desktop environments.


### Third party dependencies

The following third party dependencies must be installed for
all included actions to work:

| Application                                                     | Description                                                                       |
|-----------------------------------------------------------------|-----------------------------------------------------------------------------------|
| [aosd-cat of libaosd](https://github.com/atheme-legacy/libaosd) | Display TEXT, or standard input, on top of display                                |
| [feh](https://feh.finalrewind.org/)                             | Image viewer aimed mostly at console users to simply display images w/o fancy GUI |
| [sed](https://manpages.debian.org/buster/sed/sed.1.en.html)     | Stream editor for filtering and transforming text                                 |
| [wmctrl](http://tripie.sweb.cz/utils/wmctrl/)                   | Command line tool to interact with an EWMH/NetWM compatible X Window Manager      |
| [xdotool](https://www.semicomplete.com/projects/xdotool/)       | Fake keyboard/mouse input, window management, and more                            |
| [xsel](https://linux.die.net/man/1/xsel)                        | Manipulate the X selection (Clipboard)                                            |


### Global actions (not application specific)

**Symbols are:**

◤ ◥ = Top buttons left / right  
◣ ◢ = Bottom buttons left / right

| **Shortcut**               | **Description**                                                                |
|----------------------------|--------------------------------------------------------------------------------|
| ◤ + ←                      | Move active window to screen left of current                                   |
| ◤ + →                      | Move active window to screen right of current                                  |
| ◤ + ◢                      | Jump to next workspace                                                         |
| Right Shift + ◤ + ◢        | Jump to previous workspace                                                     |
| ◣ + ◢                      | Touch bottom-right hot-corner (E.g. expose windows)                            |
| &nbsp; &nbsp; ◢ + Esc      | Launch or bring System Monitor to front                                        |
| &nbsp; &nbsp; ◢ + B        | Launch new terminal (bash)                                                     |
| &nbsp; &nbsp; ◢ + C        | Launch or bring Chromium to front                                              |
| &nbsp; &nbsp; ◢ + D        | Launch or bring DataGrip to front                                              |
| &nbsp; &nbsp; ◢ + F        | Launch or bring Firefox to front                                               |
| &nbsp; &nbsp; ◢ + K        | Launch or bring Kitematic to front                                             |
| &nbsp; &nbsp; ◢ + L        | Toggle keyboard backlight                                                      |
| &nbsp; &nbsp; ◢ + M        | Launch or bring Claws Mail to front                                            |
| &nbsp; &nbsp; ◢ + N        | Launch or bring Nemo file explorer to front                                    |
| &nbsp; &nbsp; ◢ + P        | Launch or bring Pidgin to front                                                |
| &nbsp; &nbsp; ◢ + R        | Toggle active window roll-up state                                             |
| &nbsp; &nbsp; ◢ + S        | Toggle active window "roll-sideways" state                                     |
| &nbsp; &nbsp; ◢ + T        | Toggle active window always-on-top state                                       |
| &nbsp; &nbsp; ◢ + U        | Type current UNIX timestamp                                                    |
| &nbsp; &nbsp; ◢ + V        | Toggle active window always-on-visible-workspace state                         |
| &nbsp; &nbsp; ◢ + W        | Hit CTRL+W (close window)                                                      |
| &nbsp; &nbsp; ◢ + Ä        | Type large A-umlaut (helpful e.g. on swiss keyboards)                          |
| &nbsp; &nbsp; ◢ + Ö        | Type large O-umlaut (helpful e.g. on swiss keyboards)                          |
| &nbsp; &nbsp; ◢ + Ü        | Type large U-umlaut (helpful e.g. on swiss keyboards)                          |
| &nbsp; &nbsp; ◢ + ←        | Focus previous tab                                                             |
| &nbsp; &nbsp; ◢ + →        | Focus next tab                                                                 |
| &nbsp; &nbsp; ◢ + ↑        | Scroll to top (same as home key)                                               |
| &nbsp; &nbsp; ◢ + ↓        | Scroll to bottom (same as end key)                                             |
| &nbsp; &nbsp; ◢ + Numpad 7 | Tile active window to top-left 50% of screen                                   |
| &nbsp; &nbsp; ◢ + Numpad 8 | Tile active window to top 50% of screen                                        |
| &nbsp; &nbsp; ◢ + Numpad 9 | Tile active window to top-right 50% of screen                                  |
| &nbsp; &nbsp; ◢ + Numpad 6 | Tile active window to right 50% of screen                                      |
| &nbsp; &nbsp; ◢ + Numpad 3 | Tile active window to bottom-right 50% of screen                               |
| &nbsp; &nbsp; ◢ + Numpad 2 | Tile active window to bottom 50% of screen                                     |
| &nbsp; &nbsp; ◢ + Numpad 1 | Tile active window to bottom-left 50% of screen                                |
| &nbsp; &nbsp; ◢ + Numpad 4 | Tile active window to left 50% of screen                                       |
| &nbsp; &nbsp; ◢ + Numpad 5 | Maximize active window                                                         |
| &nbsp; &nbsp; ◢ + '        | Output name of application of focused window (to terminal)                     |
| &nbsp; &nbsp; ◢ + $        | Convert selected text to all upper/lower case                                  |
| ◣ + A                      | Select all (same as CTRL+A)                                                    |
| ◣ + C                      | Copy (same as CTRL+C)                                                          |
| ◣ + F                      | Find (same as CTRL+F)                                                          |
| ◣ + V                      | Paste (same as CTRL+V)                                                         |
| ◣ + X                      | Cut (same as CTRL+X)                                                           |
| ◣ + Y                      | Redo (same as CTRL+Y)                                                          |
| ◣ + Z                      | Undo (same as CTRL+Z)                                                          |
| ◣ + Numpad 4               | Move active window to screen left of current                                   |
| ◣ + Numpad 6               | Move active window to screen right of current                                  |
| ◣ + Numpad Plus            | Zoom in (same as CTRL+Plus)                                                    |
| ◣ + Numpad Minus           | Zoom out (same as CTRL+Minus)                                                  |
| ◣ + ↑                      | Increase audio volume                                                          |
| ◣ + ↓                      | Decrease audio volume                                                          |


### Application specific actions

For these actions to be triggered, a window of the respective application must
be focussed when the shortcut is fired.


#### Chromium and Firefox Web-Browser

| **Shortcut**                 | **Description**                              |
|------------------------------|----------------------------------------------|
| ◤ + D                        | Show downloads                               |
| ◤ + R                        | Reload                                       |
| ◤ + L &nbsp; or &nbsp; ◤ + U | Focus URL field                              |
| &nbsp; &nbsp; ◢ + ←          | Focus previous tab (browser and DevTools)    |
| &nbsp; &nbsp; ◢ + →          | Focus next tab (browser and DevTools)        |
| &nbsp; &nbsp; ◢ + ,          | Decrement numeric ending of current URL by 1 |
| &nbsp; &nbsp; ◢ + .          | Increment numeric ending of current URL by 1 |
| &nbsp; &nbsp; ◢ + Backspace  | Remove trailing segment from current URL     |
| &nbsp; &nbsp; ◢ + C          | Copy trailing segment of current URL         |
| &nbsp; &nbsp; ◢ + D          | Duplicate active tab                         |
| &nbsp; &nbsp; ◢ + H          | Toggle HTML "view-source" of current URL     |
| ◣ + ←                        | Go URL backwards                             |
| ◣ + →                        | Go URL forward                               |
| ◣ + F4                       | Close active tab                             |


#### Claws Mail

| **Shortcut**        | **Description**            |
|---------------------|----------------------------|
| &nbsp; &nbsp; ◢ + F | Open "Search Folder" popup |
| &nbsp; &nbsp; ◢ + H | Toggle "Hide read threads" |


#### Gnome Terminal

| **Shortcut**               | **Description**                                                |
|----------------------------|----------------------------------------------------------------|
| ◤                          | Close active tab                                               |
| &nbsp; &nbsp; ◢ + F        | Open "Find" popup                                              |
| &nbsp; &nbsp; ◢ + Numpad / | Insert 40 empty lines (helpful to separate sections of output) |
| &nbsp; &nbsp; ◢ + ←        | Focus previous tab                                             |
| &nbsp; &nbsp; ◢ + →        | Focus next tab                                                 |
| &nbsp; &nbsp; ◢ + ↑        | Scroll to top                                                  |
| &nbsp; &nbsp; ◢ + ↓        | Scroll to bottom                                               |


#### Gnome Screenshot

These actions automate the steps for transferring screenshots made with 
Gnome Screenshot into other applications.  
For them to work, the mouse must be hovering Gnome Screenshot's 
[copy to clipboard] button when fired. 

| **Shortcut**            | **Description**                                                                                                                                                                             |
|-------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| &nbsp; &nbsp; ◢ + AltGr | Click and hit [Esc] = Copy to clipboard and close Gnome Screenhot popup at once                                                                                                             |
| &nbsp; &nbsp; ◢ + G     | Click, hit [Esc], focus Gimp (if running) and paste image from clipboard as new image                                                                                                       |
| ◣ + V                   | **View as "sticky note:"** Click, hit [Esc], store clipboard to temporary image file and open image file in feh Image Viewer, Set feh window always-on-top and always-on-visible-workspace. |


## Action shell scripting tricks

### 1. User-specific actions 

**Problem:** xmchord runs as root, but most actions need to be run for a
specific logged-in user.

E.g. Cinnamon's D-Bus methods require being launched by a specific user. 
The following script switches from root to original user, before triggering the
desired method:

```bash
#!/bin/bash
me=$SUDO_USER
sudo -u $me dbus-send --dest=org.Cinnamon --print-reply /org/Cinnamon org.Cinnamon.switchWorkspaceRight
```


### 2. Launching applications and switching windows

Shell scripts can detect whether an application is running already and using
e.g. [wmctrl](http://tripie.sweb.cz/utils/wmctrl/), bring a respective window
onto the active workspace, or launch the application (similar to the behavior
on Mac OS).

```bash
#!/bin/bash
if pidof -s evolution > /dev/null; then
  wmctrl -a Evolution
else
  me=$SUDO_USER
  sudo -u $me nohup evolution > /dev/null &
fi
```


### 3. Triggering window actions

Using e.g. [wmctrl](http://tripie.sweb.cz/utils/wmctrl/), shell scripts can
switch the active window's roll-up and always-on-top state:

```bash
#!/bin/bash
wmctrl -b toggle,shaded -r :ACTIVE:
```


```bash
#!/bin/bash
wmctrl -r :ACTIVE: -b toggle,above
```


### 4. Application specific shortcut actions

Using e.g. [xdotool](https://www.semicomplete.com/projects/xdotool/), shell
scripts can detect the currently focused window's application, and vary 
the triggered function accordingly. Xdotool also allows to trigger
key-combinations for various shortcuts:

```bash
#!/bin/bash
focusApplication=\
`cat /proc/$(xdotool getwindowpid $(xdotool getwindowfocus))/comm`

if [[ "$focusApplication" =~ "gnome-terminal-" ]]; then
  xdotool key Control_L+Page_Up
else
  xdotool key shift+ctrl+Tab
fi
```


## Building from source

```bash
cmake CMakeLists.txt; make
```


## Code Convention

The source code of xmchord follows the Google C++ Style Guide, see: 
https://google.github.io/styleguide/cppguide.html  
The source code of action shell script files follows the Google Shell Style
Guide, see https://google.github.io/styleguide/shell.xml


## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md)


## Bug Reporting and Feature Requests

If you find a bug or have an enhancement request, please file an issue on the
github repository.


## Changelog

See [CHANGELOG.md](CHANGELOG.md)


## Third Party References

The example action for window arrangement uses splitDesk.sh, 
based on the [original script](https://gist.github.com/culyun/a7347a58168a75ba8c06f1ddd67cf06d) by Steve Simpson.


## Author and License

Written by Kay Stenschke.
xmchord is licensed under the [New BSD License](http://opensource.org/licenses/BSD-3-Clause)


> Copyright (c), Kay Stenschke
> All rights reserved.
>
> Redistribution and use in source and binary forms, with or without modification,
> are permitted provided that the following conditions are met:
>
> 1. Redistributions of source code must retain the above copyright notice, this
>    list of conditions and the following disclaimer.
>
> 2. Redistributions in binary form must reproduce the above copyright notice,
>    this list of conditions and the following disclaimer in the documentation
>    and/or other materials provided with the distribution.
>
> 3. Neither the name of the copyright holder nor the names of its contributors
>    may be used to endorse or promote products derived from this software without
>    specific prior written permission.
>
> THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
> ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
> WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
> DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
> ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
> (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
>  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
> ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
> (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
> SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
