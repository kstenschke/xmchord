xmchord Changelog
=================

V0.1.3 - 2020/03/20
-------------------
* Cleanup to more conform w/ code conventions


V0.1.3 - 2020/03/20
-------------------
* Added auto-detection of available keyboard device


V0.1.2 - 2020/03/19
-------------------
* Improved device compatibility: Add fallback to internal keyboard when no external keyboard present


V0.1.1 - 2019/12/06
-------------------
* Changed dependency: Default actions now use "notify-send" instead of osd-cat for notifications
* Added Travis CI build config: Compile using clang and gcc, run cppcheck
* Improved: Performance (use initialization lists, narrow-down variable scopes)
* Added zlib/zconf.h header to source


V0.1.0 - 2019/07/16
-------------------
* Added actions to increment/decrement audio volume
* Added actions to type uppercase umlauts (helpful on swiss keyboards)  
* Added browser actions to increment/decrement numeric ending of current url  
* Added emulations of most system-wide ctrl-key combinations  
* Added OSD info to example actions: toggle active window above / sticky, audio volume up / down  
* Improved window arrangement action to work w/ up to three monitors 


V0.0.1 - 2019/04/24
-------------------
* Initial release
