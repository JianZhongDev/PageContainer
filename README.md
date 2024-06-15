# PageContainer
PageContainer is a C++ data container class designed for quick data input and output without relying on the operating system's buffering.

Key features of PageContainer:

- Enables direct data reading and writing without system buffering.
- Stores data of any size in a buffer that is a multiple of the system's page size.
- Allows multiple PageContainer objects to be saved and accessed within a single file without extra metadata.
- Supports pointer-style data access and buffer input/output.

## Software Support

The module was created and tested using Visual Studio 2022 Community with the `Default (ISO C++14 Standard)` settings.

## How to use PageContainer

An example code demonstrating how to use PageContainer can be found in the [Demo.cpp](./PageContainer/PageContainer/Tests/Demo.cpp) file.

## Tutorial 

A comprehensive tutorial for PageContainer can be found in [my blog post](https://jianzhongdev.github.io/VisionTechInsights/posts/page_container_direct_data_io/)(URL: https://jianzhongdev.github.io/VisionTechInsights/posts/page_container_direct_data_io/ )

## License

Licensed under the [GPL-3.0 license](./LICENSE)