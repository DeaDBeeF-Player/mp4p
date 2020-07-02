# MP4P

A library for working with ISO/IEC Base Media File Format, also known as MP4 files.

## Adding to your project

### macOS / Xcode

Drag the provided `mp4p.xcodeproj` into your project, and add the framework to the dependency, link and copy frameworks build phases.

### Other platforms

Add `include` and `src` folders to your build system

## Using from your code

Include the API header file: `#include <mp4p/mp4p.h>`

## Features

* Written in C, or more specifically C99
* Parsing most atoms / boxes necessary for handling AAC and ALAC files in MP4 container
* Finding and enumerating the atoms
* Reading and writing metadata in iTunes format
* AAC and ALAC audio-specific config
* Embedded album art support
* M4B chapter support
* Many useful atoms are converted into usable / editable C structs


