xmchord
=======

[![Platform](https://img.shields.io/badge/platform-linux-blue)](#)
[![License](https://img.shields.io/badge/License-new%20BSD-blue)](https://github.com/kstenschke/xmchord/blob/master/LICENSE)
[![Written in C++](https://img.shields.io/badge/written%20in-C++-blue)](#)  

[![Build Status](https://travis-ci.com/kstenschke/xmchord.svg?branch=master)](https://travis-ci.com/kstenschke/xmchord)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/kstenschke/xmchord.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/kstenschke/xmchord/context:cpp)
[![CodeFactor](https://www.codefactor.io/repository/github/kstenschke/xmchord/badge)](https://www.codefactor.io/repository/github/kstenschke/xmchord)


xmchord is a productivity tool for Linux desktops, that binds custom
actions to `chording*` events of mouse buttons and key presses: this way, 
mouse buttons become additional modifier keys. 

**`*Chording:`** Chording generally means pushing several keys or buttons
simultaneously to achieve a result.

xmchord comes with a comprehensive set of shortcut **actions to automate and speed-up
 user activities** that are common on the Linux desktop.


## Table of contents

* [What does it do?](#what-does-it-do)
* [Usage and arguments](#usage-and-arguments)
  * [Command: `help`](#command-help)
  * [Command: `debug`](#command-debug)
  * [Command: `actions`](#command-actions)
  * [Argument: `--keyboard`](#argument---keyboard)
  * [Command: `listDevices`](#command-listdevices)
  * [Command: `printPreferences`](#command-printpreferences)
  * [Command: `reset`](#command-reset)
  * [Command: `version`](#command-version)
* [Included shortcut actions](#included-shortcut-actions)
  * [Third party dependencies](#third-party-dependencies)
  * [Global actions](#global-actions-not-application-specific)
      + [Application launchers](#application-launchers)
      + [Various global actions](#various-global-actions)
  * [Application specific actions](#application-specific-actions)
    * [Chrome, Chromium and Firefox Web-Browser](#chrome-chromium-and-firefox-web-browser)
      + [Advanced browser action: Toggle URL sub string](#advanced-browser-action-toggle-url-sub-string)
    * [Claws Mail](#claws-mail)
    * [Gnome Terminal](#gnome-terminal)
      + [Terminal command snippets](#terminal-command-snippets)
    * [Gnome Screenshot](#gnome-screenshot)
    * [Mattermost Desktop Client](#mattermost-desktop-client)
    * [Thunderbird](#thunderbird)
  + [Advanced global-actions](#advanced-global-actions)  
    * [Open generic URL](#open-generic-url)
  * [Archived/inactive actions](#archivedinactive-actions)
* [Building xmchord from source](#building-xmchord-from-source)
* [Code Convention](#code-convention)
* [Contributing](#contributing)
* [Bug Reporting and Feature Requests](#bug-reporting-and-feature-requests)
* [Changelog](#changelog)
* [Third Party References](#third-party-references)
  * [Build tools and Continuous Integration](#build-tools-and-continuous-integration)
* [Author and License](#author-and-license)
* [Addendum I: Linux trackball configuration snippets](#addendum-i-linux-trackball-configuration-snippets)
* [Addendum II: Action shell scripting tricks](#addendum-ii-action-shell-scripting-tricks)
  * [1. User-specific actions](#1-user-specific-actions)
  * [2. Launching applications and switching windows](#2-launching-applications-and-switching-windows)
  * [3. Triggering window actions](#3-triggering-window-actions)
  * [4. Application specific shortcut actions](#4-application-specific-shortcut-actions)

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
 
Running `xmchord -k=/path/to/my/keyboard` or 
`xmchord --keyboard=/path/to/my/keyboard` selects the device at the given path
as the keyboard watcher's target.   
**Tip:** xmchord's device detection is looking for a matching substring, 
therefore the device-identifier can also be given w/o a path, e.g:
`xmchord -k=Logitech`.


### Command: `listDevices`

Running `xmchord listDevices` or `xmchord l` lists paths of available devices.


### Command: `printPreferences`

Running `xmchord printPreferences` or `xmchord p` outputs xmchord's preferences
if given, or a respective info if not.


### Command: `reset`

Running `xmchord reset` or `xmchord r` unsets xmchord's keyboard device 
preference.


### Command: `version`

Running `xmchord version` or  `xmchord v`, tests whether xmchord is available
and displays it's version number.


## Included shortcut actions

See files under `bin/actions`

The included shortcut actions are scripted for use with a 
[**Kensington Expert Mouse trackball**](https://www.kensington.com/p/products/control/trackballs/expert-mouse-wired-trackball), 
tested on Linux Mint Cinnamon, but should be compatible or easily
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
| [xclip](https://github.com/astrand/xclip)                       | Interface to X selections ("the clipboard") from the command line.                |


**Install dependencies that are not included in Linux Mint distribution by default:**  

````bash
sudo apt install aosd-cat feh xclip xdotool xsel -y
````


### Global actions (not application specific)

**Symbols are:**

◤ ◥ = Top buttons left / right  
◣ ◢  = Bottom buttons left / right


#### Application launchers

These actions launch applications, or bring re-focus their window, if already
running (like the behavior on Mac OS).  

| **Shortcut**                   | **Description**                                                     |
|--------------------------------|---------------------------------------------------------------------|
| ◤ + G                          | Summon default email client (like mail key on keyboard)             |
| ◤ + M                          | Bring Mattermost desktop client to front, launch if not yet running |
| ◤ + O                          | Bring Orange-player to front, launch if not yet running             |
| ◤ + W                          | Summon default web browser (like browser key on keyboard)           |
| ◣ + C                          | Launch or bring Chromium to front                                   |
| ◣ + D                          | Launch or bring DataGrip to front                                   |
| ◣ + F                          | Launch or bring Firefox to front                                    |
| ◣ + K                          | Launch or bring Kitematic to front                                  |
| ◣ + M                          | Launch or bring Claws Mail to front                                 |
| ◣ + Y                          | Bring CherryTree to front, launch if not yet running                |
| ◣ + Esc                        | Launch or bring System Monitor to front                             |
| ◣ + Numpad +                   | Launch [xshmenu](https://github.com/kstenschke/xshmenu)             |

#### Various global actions

| **Shortcut**                   | **Description**                                                                |
|--------------------------------|--------------------------------------------------------------------------------|
| ◤ + ←                          | Go to workspace left of current (Hit SUPER+SHIFT+Left)                         |
| ◤ + →                          | Go to workspace left of current (Hit SUPER+SHIFT+Right)                        |
| ◤ + ◣                          | Jump to next workspace                                                         |
| Right Shift + ◤ + ◣            | Jump to previous workspace                                                     |
| ◣ + ◢                          | Touch bottom-right hot-corner (E.g. expose windows)                            |
| ◣ + I                          | Display public and private IP and wifi MAC address, copy public IP address     |
| ◣ + L                          | Toggle keyboard backlight                                                      |
| ◣ + R                          | Toggle active window roll-up state                                             |
| ◣ + S                          | Toggle active window "roll-sideways" state                                     |
| ◣ + T                          | Toggle active window always-on-top state                                       |
| ◣ + U                          | Type current UNIX timestamp                                                    |
| ◣ + V                          | Toggle active window always-on-visible-workspace state                         |
| ◣ + W                          | Hit CTRL+W (close window)                                                      |
| ◣ + Ä                          | Type large A-umlaut (helpful e.g. on swiss keyboards)                          |
| ◣ + Ö                          | Type large O-umlaut (helpful e.g. on swiss keyboards)                          |
| ◣ + Ü                          | Type large U-umlaut (helpful e.g. on swiss keyboards)                          |
| ◣ + ←                          | Focus previous tab                                                             |
| ◣ + →                          | Focus next tab                                                                 |
| ◣ + ↑                          | Scroll to top (same as home key)                                               |
| ◣ + ↓                          | Scroll to bottom (same as end key)                                             |
| ◣ + Numpad 7                   | Tile active window to top-left 50% of screen                                   |
| ◣ + Numpad 8                   | Tile active window to top 50% of screen                                        |
| ◣ + Numpad 9                   | Tile active window to top-right 50% of screen                                  |
| ◣ + Numpad 6                   | Tile active window to right 50% of screen                                      |
| ◣ + Numpad 3                   | Tile active window to bottom-right 50% of screen                               |
| ◣ + Numpad 2                   | Tile active window to bottom 50% of screen                                     |
| ◣ + Numpad 1                   | Tile active window to bottom-left 50% of screen                                |
| ◣ + Numpad 4                   | Tile active window to left 50% of screen                                       |
| ◣ + Numpad 5                   | Maximize active window                                                         |
| ◣ + '                          | Output name of application of focused window (to terminal)                     |
| ◣ + $                          | Convert selected text to all upper/lower case                                  |
| ◣ + ENTER                      | Click left mouse button three times (select line)                              |
| &nbsp; &nbsp; ◢ + A            | Select all (same as CTRL+A)                                                    |
| &nbsp; &nbsp; ◢ + C            | Copy (same as CTRL+C)                                                          |
| &nbsp; &nbsp; ◢ + F            | Find (same as CTRL+F)                                                          |
| &nbsp; &nbsp; ◢ + V            | Paste (same as CTRL+V)                                                         |
| &nbsp; &nbsp; ◢ + X            | Cut (same as CTRL+X)                                                           |
| &nbsp; &nbsp; ◢ + Y            | Redo (same as CTRL+Y)                                                          |
| &nbsp; &nbsp; ◢ + Z            | Undo (same as CTRL+Z)                                                          |
| &nbsp; &nbsp; ◢ + Numpad 4     | Move active window to screen left of current                                   |
| &nbsp; &nbsp; ◢ + Numpad 6     | Move active window to screen right of current                                  |
| &nbsp; &nbsp; ◢ + Numpad Plus  | Zoom in (same as CTRL+Plus)                                                    |
| &nbsp; &nbsp; ◢ + Numpad Minus | Zoom out (same as CTRL+Minus)                                                  |
| &nbsp; &nbsp; ◢ + ↑            | Increase audio volume                                                          |
| &nbsp; &nbsp; ◢ + ↓            | Decrease audio volume                                                          |


### Application specific actions

For these actions to be triggered, a window of the respective application must
be focussed when the shortcut is fired.


#### Chrome, Chromium and Firefox Web-Browser

| **Shortcut**                 | **Description**                              |
|------------------------------|----------------------------------------------|
| ◤ + D                        | Show downloads                               |
| ◤ + R                        | Reload                                       |
| ◤ + L &nbsp; or &nbsp; ◤ + U | Focus URL field                              |
| ◣ + ←                        | Focus previous tab (browser and DevTools)    |
| ◣ + →                        | Focus next tab (browser and DevTools)        |
| Right-CTRL + ◣ + ←           | Focus previous tab, than reload it           |
| Right-CTRL + ◣ + →           | Focus next tab, than reload it               |
| ◣ + ,                        | Decrement numeric ending of current URL by 1 |
| ◣ + .                        | Increment numeric ending of current URL by 1 |
| ◣ + Backspace                | Remove trailing segment from current URL     |
| ◣ + C                        | Copy trailing segment of current URL         |
| ◣ + D                        | Duplicate active tab                         |
| ◣ + H                        | Toggle HTML "view-source" of current URL     |
| ◣ + N                        | Move active tab to new window                |
| ◣ + RETURN                   | Browse for selected text in new tab          |
| &nbsp; &nbsp; ◢ + ←          | Go URL backwards                             |
| &nbsp; &nbsp; ◢ + →          | Go URL forward                               |
| &nbsp; &nbsp; ◢ + F4         | Close active tab                             |


##### Advanced browser action: Toggle URL sub string

| **Shortcut**                   | **Description**             |
|--------------------------------|-----------------------------|
| ◣ + \[-\]                      | Toggle URL sub string       |

When running this action while the current browser URL contains one of two
sub strings, it is been replaced by the other and the browser reloaded.

The following environment variables must be set in your `/etc/environment`:

`sudo nano /etc/environment`

````sh
PATH="/usr/local/sbin:..."

XMCHORD_URL_SUBSTR_1='http://localhost'
XMCHORD_URL_SUBSTR_2='https://yoururl.com'
````

For changes to take effect after editing `/etc/environment` reload it and
restart xmchord.


#### Claws Mail

| **Shortcut**        | **Description**                                                |
|---------------------|----------------------------------------------------------------|
| ◣ + F | Open "Search Folder" popup                                                   |
| ◣ + H | Toggle "Hide read messages", precondition: "thread view" must be deactivated |


#### Gnome Terminal

| **Shortcut** | **Description**                                                |
|--------------|----------------------------------------------------------------|
| ◤            | Close active tab                                               |
| ◣ + F        | Open `Find` popup                                              |
| ◣ + Numpad / | Insert 40 empty lines (helpful to separate sections of output) |
| ◣ + ←        | Focus previous tab                                             |
| ◣ + →        | Focus next tab                                                 |
| ◣ + ↑        | Scroll to top                                                  |
| ◣ + ↓        | Scroll to bottom                                               |

#### Terminal command snippets

| **Shortcut**               | **Description**                                                                                         |
|----------------------------|---------------------------------------------------------------------------------------------------------|
| ◣ + C        | Type and execute command to `cd` into a favorite local path                                                           |
| ◣ + D        | Type `scp` command to recursively download remote directory                                                           |
| ◣ + L        | Shortcut to wipe a cache directory: Type and execute command to clean a preferred path by executing `rm -rf` upon it. |
| ◣ + S        | Type and execute command to connect to preferred SSH host and `cd` into preferred path                                |
| ◣ + SPACE    | Type `yes` and hit ENTER                                                                                              |
| ◣ + U        | Type `scp` command to recursively upload local directory to remote                                                    |
| ◣ + X        | Type `exit` and hit ENTER                                                                                             |

For the `cd`, `rm -rf`, `scp` and `ssh` shortcut snippets, the following environment variables 
must be set in your `/etc/environment`:

`sudo nano /etc/environment`

````sh
PATH="/usr/local/sbin:..."

XMCHORD_CD_FAVORITE=/home/john/Projects/myProject

XMCHORD_RM_FAVORITE=/home/john/Projects/myProject/var/cache

XMCHORD_SCP_REMOTE=johndoe@yourhost:/var/www
XMCHORD_SCP_LOCAL=/home/john/yourhost_var_www

XMCHORD_SSH_REMOTE=johndoe@yourhost
XMCHORD_SSH_REMOTE_NEEDS_CONFIRMATION=1
XMCHORD_SSH_REMOTE_PATH_INITIAL=/var/www
````

For changes to take effect, restart xmchord after editing your 
`/etc/environment`.


#### Gnome Screenshot

These actions automate the steps for transferring screenshots made with 
Gnome Screenshot into other applications.  
For them to work, the mouse must be hovering Gnome Screenshot's 
`copy to clipboard` button when fired. 

| **Shortcut**            | **Description**                                                                                                                                                                             |
|-------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| ◣ + AltGr | Click and hit [Esc] = Copy to clipboard and close Gnome Screenhot popup at once                                                                                                             |
| ◣ + G     | Click, hit [Esc], focus Gimp (if running) and paste image from clipboard as new image                                                                                                       |
| &nbsp; &nbsp; ◢ + V                   | **View as "sticky note:"** Click, hit [Esc], store clipboard to temporary image file and open image file in feh Image Viewer, Set feh window always-on-top and always-on-visible-workspace. |


#### Mattermost Desktop Client

| **Shortcut** | **Description**                                    |
|--------------|----------------------------------------------------|
| ◣ + M        | Open "direct messages" popup                       |
| ◣ + U        | Upload files                                       |
| ◣ + .        | Next unread channel                                |


#### Thunderbird

| **Shortcut** | **Description**               |
|--------------|-------------------------------|
| ◣ + B        | Open address book             |
| ◣ + F        | Open "Search Messages" popup  |


## Advanced global actions

These actions differ from the basic global actions, in that they require some manual configuration,
as described here.


### Open generic URL

This action adds text from a currently given text-selection to a preset URL, 
and loads the resulting URL in the web browser (chromium by default).

| **Shortcut**                   | **Description**                                                      |
|--------------------------------|----------------------------------------------------------------------|
| ◣ + O                          | Open generic URL in browser. Precondition: a text selection is given |

The following environment variable must be set in your `/etc/environment`:

`sudo nano /etc/environment`

````sh
PATH="/usr/local/sbin:..."

XMCHORD_GENERIC_URL='https://www.your-domain.com/?id=SELECTED_TEXT'
````

When running this action, ``SELECTED_TEXT`` will be replaced by your text 
selection.

For changes to take effect after editing `/etc/environment` reload it and
restart xmchord.

To use a different browser, edit script: ``0220022-24.sh``


### Archived/inactive actions

Some additional actions that aren't active by default can be found within
the ``actions/inactive`` directory.


## Building xmchord from source

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

[Expert Mouse® Trackball](https://www.kensington.com/p/products/electronic-control-solutions/trackball-products/expert-mouse-wireless-trackball/) 
is a registered trademark of Kensington Computer Products Group, a division of 
ACCO Brands

The example action for window arrangement uses splitDesk.sh, 
based on the 
[original script](https://gist.github.com/culyun/a7347a58168a75ba8c06f1ddd67cf06d) 
by Steve Simpson.


### Build tools and Continuous Integration

The following third party tools are used for building xmchord with automatic
control over code quality and standards: 

| Tool or Service                                       | Description                                                                          | License                                                                                                   |
| ----------------------------------------------------- | ------------------------------------------------------------------------------------ | --------------------------------------------------------------------------------------------------------- |
| [Clang](https://clang.llvm.org)                       | A C language family frontend for LLVM                                                | [Apache License](https://www.apache.org/licenses/)                                                        |      
| [Cmake](https://cmake.org)                            | Family of tools designed to build, test and package software                         | [New BSD License](https://en.wikipedia.org/wiki/New_BSD_License)                                          |      
| [Cppcheck](http://cppcheck.sourceforge.net/)          | Static analysis tool for C/C++ code                                                  | [GNU General Public License version 3](https://www.gnu.org/licenses/gpl-3.0.html)                         |      
| [cpplint](https://github.com/cpplint/cpplint)         | Static code checker for C++                                                          | [BSD-3 Clause](https://opensource.org/licenses/BSD-3-Clause)                                              |      
| [GCC](https://gcc.gnu.org)                            | GCC, the GNU Compiler Collection                                                     | [GNU General Public License version 3](https://gcc.gnu.org/onlinedocs/libstdc++/manual/appendix_gpl.html) |      
| [lgtm automated code review](https://lgtm.com/)       | Code analysis platform for finding zero-days and preventing critical vulnerabilities | [lgtm Terms of Service](https://lgtm.com/tos)                                                             |      
| [ShellCheck](https://github.com/koalaman/shellcheck)  | ShellCheck, a static analysis tool for shell scripts                                 | [GNU General Public License version 3](https://gcc.gnu.org/onlinedocs/libstdc++/manual/appendix_gpl.html) |      
| [Tavis CI](https://travis-ci.org/)                    | Test and Deploy Your Code with Confidence                                            | [Travis CI Contact & Legal Inquiries](https://www.ideracorp.com/legal/TravisCI)                           |      

Thanks a lot!


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


## Addendum I: Linux trackball configuration snippets

**Output list of devices:** ``xinput --list``  
**Output mouse buttons mapping:** ``xinput get-button-map <device-ID>``  
**Trace mouse button IDs:** ``xev``  

**Set speed and acceleration, buttons mapping and wheel emulation:**

```bash
#!/bin/bash

for id in `xinput --list|grep 'Kensington Expert Wireless TB Mouse'|perl -ne 'while (m/id=(\d+)/g){print "$1\n";}'`; do
  # set speed + accelleration
  xinput set-ptr-feedback $id 0 34 12

  # set top/left button to be middle-click
  xinput set-button-map $id 3 2 1 4 5 6 7 8 9 10 11 12  # left-handed: bottom-right is left-click

  # emulate mouse wheel on bottom/left (right-click) button + move
  xinput set-prop "pointer:Kensington Expert Wireless TB Mouse" "libinput Scroll Method Enabled" 0, 0, 1
	
  # on Kensington Expert Mouse, buttons are: 
  #   0 = no button needed
  #   2 = top/left
  #   8 = top/right
  #   1 = bottom/left
  #   8 1 = bottom buttons together
  #   8 2 = bottom right + top/left together

  # set bottom button to fire scroll-mode
  xinput set-prop "pointer:Kensington Expert Wireless TB Mouse" "libinput Button Scrolling Button" 1
    
  # map bottom-left button held to scroll
  xinput set-prop $id "Evdev Wheel Emulation Timeout" 300
done 
```


## Addendum II: Action shell scripting tricks

### 1. User-specific actions

**Problem:** xmchord runs as root, but some actions need to be run for a
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
