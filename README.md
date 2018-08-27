Direct Manipulation User Interface for a Simple 2D Image Compositor  

## User Stories

The following **required** functionality is completed:

* [x] The user can load one or more images (.jpg, and .pngformats are supported) individually from disk
* [x] Images can be overlapping
* [x] User should be able to select a single image and either move, rotate or scale the image anywhere on the Canvas
* [x] The user should be able to select a single image and delete it from the Canvas
* [x] The user should be able to control the stacking order of the images
* [x] The user should be able to save the composition to a disk file

## Usage

* Select an image using mouse. Yellow outline will appear indicating active selection.
* Control stacking order using mouse selection. Active image is brought to the top of the screen.
* Shortcut keys:
  * 'D', 'd' = delete selected image
  * 'F', 'f' = toggle full screen
  * 'R', 'r' = rotate selected images
  * 'S', 's' = save frame (saves files in assignment3/bin)
  * 'T', 't' = scale down selected image
  * 'U', 'u' = scale up selected image
  * Up arrow key = move selected image up
  * Down arrow key = move selected image down
  * Right arrow key = move selected image to the right
  * Left arrow key = move selected image to the left

## Sample Composition

Sample composition created using the image compositor.

<img src='https://github.com/shehbashahab/CS235-2DDirectManipulationUI/blob/master/bin/data/ExampleComposition.png'/>

## Open-source libraries used

- [openFrameworks](http://openframeworks.cc/) - openFrameworks is an open source C++ toolkit designed to assist the creative process by providing a simple and intuitive framework for experimentation.

## License

    Copyright 2017 Shehba Shahab

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
