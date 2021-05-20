# ncnn-webassembly-ocrlite

### Requirements

 - [ncnn webassembly](https://github.com/Tencent/ncnn/releases/download/20210507/ncnn-20210507-webassembly.zip)
 - [opencv-mobile webassembly 3.4.13](https://github.com/nihui/opencv-mobile/releases/)

### Build

1. Install emscripten

```
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
./emsdk install 2.0.8
./emsdk activate 2.0.8
./emsdk_env.sh
```

2. Download and extract ncnn & OpenCV

```
Directory Tree

├─assets
├─demo
├─include
├─ncnn-static
│  └─webassembly
│      ├─basic
│      ├─simd
│      ├─simd-threads
│      └─threads
├─opencv-static
│  └─webassembly
│      ├─bin
│      ├─include
│      ├─lib
│      └─share
└─src
```

and  

Get missing `opencv2/imgcodecs.hpp` [Link](https://gitee.com/benjaminwan/ocr-lite-ncnn/attach_files/573151/download/opencv-3.4.13-staticLib.7z)   
Path: `opencv-static/webassembly/include/opencv2`


3. Build

```
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=/PATH_TO_EMSDK/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake -DCMAKE_BUILD_TYPE=Release -DOCR_STATIC=ON ..
make
```

### Demo

`demo/index.html`

![Demo](https://i.imgur.com/r05UJbi.png)

### References

 - [chineseocr_lite](https://github.com/DayBreak-u/chineseocr_lite)
 - [ncnn-webassembly-yolov5](https://github.com/nihui/ncnn-webassembly-yolov5)
 - [ncnn-webassembly-nanodet](https://github.com/nihui/ncnn-webassembly-nanodet)























