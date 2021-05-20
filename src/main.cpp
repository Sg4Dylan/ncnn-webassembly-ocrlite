#include <cstdio>
#include <iostream>
#include "main.h"
#include "OcrLite.h"
#include "OcrUtils.h"

static OcrLite* g_ocrlite = 0;

std::string ocr_detect(cv::Mat inputImg) {
    if (!g_ocrlite)
    {
        g_ocrlite = new OcrLite;
        g_ocrlite->setNumThread(1);
        g_ocrlite->initLogger(
                false,//isOutputConsole
                false,//isOutputPartImg
                false);//isOutputResultImg
        std::string modelsDir, modelDetPath, modelClsPath, modelRecPath, keysPath;
        modelsDir = "";
        modelDetPath = modelsDir + "dbnet_op";
        modelClsPath = modelsDir + "angle_op";
        modelRecPath = modelsDir + "crnn_lite_op";
        keysPath = modelsDir + "keys.txt";
        g_ocrlite->initModels(modelDetPath, modelClsPath, modelRecPath, keysPath);
    }
    int padding = 50;
    int maxSideLen = 720;
    float boxScoreThresh = 0.6f;
    float boxThresh = 0.3f;
    float unClipRatio = 2.0f;
    bool doAngle = true;
    bool mostAngle = true;
    cv::Mat rgbImage;
    cv::cvtColor(inputImg, rgbImage, cv::COLOR_RGBA2RGB);
    OcrResult result = g_ocrlite->detect(rgbImage, padding, maxSideLen,
                                      boxScoreThresh, boxThresh, unClipRatio, doAngle, mostAngle);
    for (const auto& text : result.textBlocks)
    {  
        std::cout << "Results: " << text.text << "\n";
    }
    return result.strRes;
}

extern "C" {

void ocrlite_ncnn(unsigned char* rgba_data, int w, int h, char *ret)
{
    // 输入图像数据
    cv::Mat rgb(h, w, CV_8UC4, (void*)rgba_data);
    std::string result = ocr_detect(rgb);
    strcpy(ret, result.c_str());
}

}
