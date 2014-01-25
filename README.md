## Purpose
This is just sample code.

## Utility
This utility works as tar without compression. It places all of input files into one archive and can extract it and place in particular place.

## Dependencies
You need to have boost at least 1.48 version and cmake, of course.

## Build
1. Checkout this repo
2. Go into the project folder
3. Make the following commands:
> cmake .
> make
That's it.

## Stuffing file and folders
1. Build the project
2. Run:

> ./simple_tar path_to_file_or_directory_to_stuff> [-o output_file_path]

-o is optional, the default value is "output.arch".

**Note:** output file must not exist

## Extracting files and folders
1. Build the project.
2. Run:

> ./simple_tar -x path_to_archive [-o output_directory_path]

-o is optional, the default value is "."

**Note:** output directory may not exist. In this case it will be creatd automatically 